#include "DllGobangAI.h"
player::player()
{
	mystatus = 0;
	myid = 0;
	cmdi = 0;
	cmdj = 0;
	maxint = 10000000;
	minint = -10000000;
}
player::player(int sta, int id)
{
	mystatus = sta;
	cmdi = 0;
	cmdj = 0;
	maxint = (float)10000000;
	minint = (float)(-10000000);
	if (id == computer || id == person)
		myid = id;
	else{
		//报错
	}
}
float player::valuefunc(int *p, int &x, int &y, neuralnetworkofGobangBaseFeature & net){//估值函数
	//要根据我方执黑/白对+1-1进行转化：
	//默认我方（电脑） 白
	int r = notfinish;
	r = judge(p, x, y, 5);
	//baiwin=-1,heiwin=1
	if (r == (mystatus*(-1))) { /*printArray(p); system("pause");*/return net.getshuchu() + minint / 2; }
	else if (r == mystatus)  { /*printArray(p); system("pause");*/ return net.getshuchu() + maxint / 2; }
	int tmp[size*size];
	int i;
	if (mystatus == baistatus)
	{
		for (i = 0; i < size*size; i++)//我方执白，翻转之后在判断局势
		{
			if (p[i] == 0)
				tmp[i] = 0;
			else if (p[i]>0)
			{
				tmp[i] = -1;
			}
			else {
				tmp[i] = 1;
			}
		}
		net.getshuru(tmp);
	}
	else
	{
		net.getshuru(p);
	}
	net.cal_shuchu();
	float tmpf;
	tmpf = net.wofangf.willwin(true);
	tmpf -= net.duifangf.willwin(false);
	if (tmpf > 0.3) { /*printArray(tmp); system("pause"); */return net.getshuchu() + maxint / 100 * tmpf; }
	else if (tmpf < -0.3) { /*printArray(tmp); system("pause");*/ return net.getshuchu() + maxint / 100 * tmpf; }
	//cout << "valuefunc:" << net.getshuchu()<<endl;
	return net.getshuchu();
}
float player::max(float a, float b)
{
	if (a > b)
		return a;
	else return b;
}
float player::min(float a, float b)
{
	if (a < b)
		return a;
	else return b;
}
int player::judge(int *tmap, int &x, int &y, int lenlian)//判断棋局
{
	int countbailian = 0, countheilian = 0;
	int i, j;
	int lenhei = 0;
	int lenbai = 0;
	for (i = 0; i < size; i++)//扫描行
	{
		lenhei = 0;
		lenbai = 0;
		for (j = 0; j < size; j++){
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)//record for juece
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

		}
	}

	for (j = 0; j < size; j++)//扫描列
	{
		lenhei = 0;
		lenbai = 0;
		for (i = 0; i < size; i++)
		{
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)//record for juece
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

		}
	}

	for (i = 0; i < size; i++)//扫描左下半，右斜线
	{
		j = 0;
		lenhei = 0;
		lenbai = 0;
		int rec_i = i;
		while (i < size&&j < size)
		{
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)//record for juece
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

			i++;
			j++;
		}
		i = rec_i;
	}

	for (j = 1; j < size; j++)//扫描右上半，右斜线
	{
		i = 0;
		lenhei = 0;
		lenbai = 0;
		int rec_j = j;
		while (i < size - 1 && j < size)
		{
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)//record for juece
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

			i++;
			j++;
		}
		j = rec_j;
	}

	for (i = 0; i < size; i++)//扫描左上半，zuo斜线
	{
		lenhei = 0;
		lenbai = 0;
		j = 0;
		int rec_i = i;
		while (i >= 0 && j < size)
		{
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)//record for juece
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

			i--;
			j++;
		}
		i = rec_i;
	}
	for (j = 1; j < size; j++)//扫描右下半，zuo斜线
	{
		i = size - 1;
		lenhei = 0;
		lenbai = 0;
		int rec_j = j;
		while (i >= 1 && j < size)
		{
			if (tmap[i*size + j] >0)//黑子
			{
				if (tmap[i*size + j] != 1)//record for juece
				{
					x = i; y = j;
				}
				lenhei++;
				lenbai = 0;
			}
			else if (tmap[i*size + j] <0)//白子
			{
				if (tmap[i*size + j] != -1)
				{
					x = i; y = j;
				}
				lenbai++;
				lenhei = 0;
			}
			else{//空子
				lenhei = 0;
				lenbai = 0;
			}
			if (lenbai == lenlian)
			{
				//cout << "direction42bai" << endl;
				countbailian++;
			}

			if (lenhei == lenlian)
			{
				//cout << "direction42hei" << endl;
				countheilian++;
			}

			i--;
			j++;
		}
		j = rec_j;
	}
	if (countbailian > 0)
		return baiwin;
	if (countheilian > 0)
		return heiwin;
	return notfinish;
}
float player::search(int *p, int &ix, int &jy, int depth, int depthlimit, float rootvalue, neuralnetworkofGobangBaseFeature & net,int x_first_search_node,int y_first_search_node)//depth当前树的深度，根节点为0，depthlimit树深度的限制,如果层数是01234，则一共有5层.首次搜索rootvalue值任意
{

	float value = 0;
	//在 map 中用非-1，0，1的值标记临时的子，评估完后要清除
	//在 map 中第x层下展开的节点，在map中的子用1+x+1或-1-x-1标记
	//depth%2==0时，该自己下，取max，==1时，取min
	if (depth % 2 == 0){
		value = minint;
	}
	else{
		value = maxint;
	}
	if (depth == depthlimit - 1)
	{
		value = valuefunc(p, ix, jy, net);
		//cout << "cengshu" << depth << "zhi:" << value << endl;
		tmpcounter++;
		return value;
	}
	else
	{
		int x, y;
		//先搜右下角：
		for (x = x_first_search_node; x < size; x++)
		{
			for (y = y_first_search_node; y < size; y++)
			{
				if (p[x*size + y] == 0)//未下子
				{
					if (mystatus == heistatus)
					{
						if (depth % 2 == 0)
						{
							p[x*size + y] = 1 + depth + 1;
						}
						else
						{
							p[x*size + y] = -1 - depth - 1;
						}
					}
					else{
						if (depth % 2 == 0)
						{
							p[x*size + y] = -1 - depth - 1;
						}
						else{
							p[x*size + y] = 1 + depth + 1;
						}
					}
					if (depth % 2 == 0)
					{
						if (depth > 0 && rootvalue <= value)
						{
							p[x*size + y] = 0;
							// cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							float tmpvalue = value;
							value = max(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
							if (depth == 0 && fabs(tmpvalue - value) >= 0.001){//根节点更新值的时候，记录下落子的位置
								cmdi = x;
								cmdj = y;
							}
						}
					}
					else{//depth%2==1
						if (rootvalue >= value){
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							value = min(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
						}

					}
					p[x*size + y] = 0;

				}

			}
		}
		//再搜右上角：
		for (x = x_first_search_node; x >= 0; x--)
		{
			for (y = y_first_search_node; y < size; y++)
			{
				if (p[x*size + y] == 0)//未下子
				{
					if (mystatus == heistatus)
					{
						if (depth % 2 == 0)
						{
							p[x*size + y] = 1 + depth + 1;
						}
						else
						{
							p[x*size + y] = -1 - depth - 1;
						}
					}
					else{
						if (depth % 2 == 0)
						{
							p[x*size + y] = -1 - depth - 1;
						}
						else{
							p[x*size + y] = 1 + depth + 1;
						}
					}
					if (depth % 2 == 0)
					{
						if (depth > 0 && rootvalue <= value)
						{
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							float tmpvalue = value;
							value = max(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
							if (depth == 0 && fabs(tmpvalue - value) >= 0.001){//根节点更新值的时候，记录下落子的位置
								cmdi = x;
								cmdj = y;
							}
						}
					}
					else{//depth%2==1
						if (rootvalue >= value){
							p[x*size + y] = 0;
							//   cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							value = min(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
						}

					}
					p[x*size + y] = 0;

				}

			}
		}
		//再搜左上角：
		for (x = x_first_search_node; x >= 0; x--)
		{
			for (y = y_first_search_node; y >= 0; y--)
			{
				if (p[x*size + y] == 0)//未下子
				{
					if (mystatus == heistatus)
					{
						if (depth % 2 == 0)
						{
							p[x*size + y] = 1 + depth + 1;
						}
						else
						{
							p[x*size + y] = -1 - depth - 1;
						}
					}
					else{
						if (depth % 2 == 0)
						{
							p[x*size + y] = -1 - depth - 1;
						}
						else{
							p[x*size + y] = 1 + depth + 1;
						}
					}
					if (depth % 2 == 0)
					{
						if (depth > 0 && rootvalue <= value)
						{
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							float tmpvalue = value;
							value = max(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
							if (depth == 0 && fabs(tmpvalue - value) >= 0.001){//根节点更新值的时候，记录下落子的位置
								cmdi = x;
								cmdj = y;
							}
						}
					}
					else{//depth%2==1
						if (rootvalue >= value){
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							value = min(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
						}

					}
					p[x*size + y] = 0;

				}

			}
		}
		//再搜左下角：
		for (x = x_first_search_node; x < size; x++)
		{
			for (y = y_first_search_node; y >= 0; y--)
			{
				if (p[x*size + y] == 0)//未下子
				{
					if (mystatus == heistatus)
					{
						if (depth % 2 == 0)
						{
							p[x*size + y] = 1 + depth + 1;
						}
						else
						{
							p[x*size + y] = -1 - depth - 1;
						}
					}
					else{
						if (depth % 2 == 0)
						{
							p[x*size + y] = -1 - depth - 1;
						}
						else{
							p[x*size + y] = 1 + depth + 1;
						}
					}
					if (depth % 2 == 0)
					{
						if (depth > 0 && rootvalue <= value)
						{
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							float tmpvalue = value;
							value = max(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
							if (depth == 0 && fabs(tmpvalue - value) >= 0.001){//根节点更新值的时候，记录下落子的位置
								cmdi = x;
								cmdj = y;
							}
						}
					}
					else{//depth%2==1
						if (rootvalue >= value){
							p[x*size + y] = 0;
							//  cout << "cengshu" << depth << "zhi:" << value << endl;
							return value;
						}
						else{
							value = min(search(p, ix, jy, depth + 1, depthlimit, value, net), value);
						}

					}
					p[x*size + y] = 0;
				}
			}
		}
		// cout << "cengshu" << depth << "zhi:" << value << endl;
		return value;
	}
}
void player::computermakecmd(int *map, int &i, int &j, neuralnetworkofGobangBaseFeature & net){
	tmpcounter = 0;
	int x = 0, y = 0;
	clock_t start, end;
	start = clock();
	search(map, x, y, 0, 3, maxint, net);
	end = clock();
	std::cout << "3层用时：" << end - start << " , 结果：" << x << "  " << y << std::endl;
	/*int recx = x, recy = y;
	start = clock();
	search(map, x, y, 0, 5, maxint, net, recx, recy);
	end = clock();
	std::cout << "5层用时：" << end - start << " , 结果：" << x << "  " << y << std::endl;

	recx = x; recy = y;
	start = clock();
	search(map, x, y, 0, 5, maxint, net, recx, recy);
	end = clock();
	std::cout << "5层用时：" << end - start << " , 结果：" << x << "  " << y << std::endl;*/

	
	//先搜3层.此状态下该zijixia

	std::cout << cmdi << " asdjh " << cmdj << std::endl;
	if (map[cmdi*size + cmdj] != 0)
	{
		cmdi = x;
		cmdj = y;
		
	}
	else
	{
		std::cout << cmdi << "  " << cmdj << std::endl;
	}
	i = cmdi;
	j = cmdj;
	std::cout << "i,j=" << i << "  " << j << std::endl;



	int recx = cmdi, recy = cmdj;
	start = clock();
	search(map, x, y, 0, 5, maxint, net, recx, recy);
	end = clock();
	std::cout << "5层用时：" << end - start << " , 结果：" << cmdi << "  " << cmdj << std::endl;
	if (map[cmdi*size + cmdj] != 0)
	{
		cmdi = x;
		cmdj = y;

	}
	i = cmdi;
	j = cmdj;
	system("pause");
}
/*void waitpersonmakecmd(int *map, int &i, int &j){//等待出招
cout << "请输入坐标" << endl;
reinput:cin >> i >> j;
if (map[i*size + j] != 0 || i<0 || i>size - 1 || j<0 || j>size - 1)
{
cout << "坐标非法，请重新输入！" << endl;
goto reinput;
}
}*/
void player::setmyid(int id){//设置player的id，自己还是对手。
	if (id == computer || id == person){
		myid = id;
	}
	else{
		//id 值错误
	}
}