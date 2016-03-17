#include "DllGobangAI.h"
void  test()
{
	std::cout << "hello" << std::endl;
}

AIforGobangGame*   createInstanceOfAI(int status, int turn, const char * src,int search_para)
{
	return new AIforGobangGame(status, turn, src,search_para);
}
	int AIforGobangGame::judge_result(int *map)//判断当前棋局是baiwin还是heiwin还是尚未结束
	{
		int i, j;
		int lenhei = 0;
		int lenbai = 0;
		for (i = 0; i < size; i++)//扫描行
		{
			lenhei = 0;
			lenbai = 0;
			for (j = 0; j < size; j++){
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
			}
		}

		for (j = 0; j < size; j++)//扫描列
		{
			lenhei = 0;
			lenbai = 0;
			for (i = 0; i < size; i++)
			{
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
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
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
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
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
				i++;
				j++;
			}
			j = rec_j;
		}

		for (i = 0; i < size; i++)//扫描左上半，右斜线
		{
			lenhei = 0;
			lenbai = 0;
			j = 0;
			int rec_i = i;
			while (i >= 0 && j < size)
			{
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
				i--;
				j++;
			}
			i = rec_i;
		}
		for (j = 1; j < size; j++)//扫描右下半，右斜线
		{
			i = size - 1;
			lenhei = 0;
			lenbai = 0;
			int rec_j = j;
			while (i >= 1 && j < size)
			{
				if (map[i*size + j] == heizi)//黑子
				{
					lenhei++;
					lenbai = 0;
				}
				else if (map[i*size + j] == baizi)//白子
				{
					lenbai++;
					lenhei = 0;
				}
				else{//空子
					lenhei = 0;
					lenbai = 0;
				}
				if (lenhei == 5)
					return heiwin;
				else if (lenbai == 5)
					return baiwin;
				i--;
				j++;
			}
			j = rec_j;
		}
		return notfinish;
	}
	void AIforGobangGame::record(int *map,int this_turn)//记录中己方子为1，不论黑白
	{
		int *tmp = (int *)malloc(size*size*sizeof(int));//记录对手下完的局面
		int k;
		bool is_init_map = true;//判断是否为初始局面。即无子状态。
		if (myStatus == p.baistatus)//如果AI执白棋，记录棋局时先翻转
		{
			for (k = 0; k < size*size; k++)
			{
				tmp[k] = map[k] * (-1);
				if (map[k] != 0)
				{
					is_init_map = false;
				}
			}
			
		}
		else {
			for (k = 0; k < size*size; k++)
			{
				tmp[k] = map[k];
				if (map[k] != 0)
				{
					is_init_map = false;
				}
			}
			
		}
		if (is_init_map==true)//初始局面不记录
		{
			free(tmp);
		}
		else//不是初始局面，记录
		{
			stepmap[this_turn*size*size+step[this_turn]] = tmp;
			step[this_turn]++;
			/*std::cout << "map 000:" << std::endl;
			//调试代码段
			for (int x = 0; x < 15; x++)
			{
				for (int y = 0; y < 15; y++)
				{

					std::cout << tmp[x*size + y] << "  ";
				}
				std::cout << std::endl;
			}*/
		}
	}
	void AIforGobangGame::init()
	{
		iswin = false;
		step[0] = 0;
		step[1] = 0;
	}
	AIforGobangGame::AIforGobangGame(int status, int turn, float qz1[96][48], float qz2[48], int search_para)
	{
		search_layer = search_para;
		myStatus = status;
		p = player(myStatus, 0,search_para);
		mynet = neuralnetworkofGobangBaseFeature(qz1, qz2);
		AIturn = turn;
		step[0] = 0;
		step[1] = 0;
	}
	AIforGobangGame::AIforGobangGame(int status, int turn, neuralnetworkofGobangBaseFeature &net, int search_para)
	{
		search_layer = search_para;
		myStatus = status;
		p = player(myStatus, 0,search_para);
		mynet = net;
		AIturn = turn;
		step[0] = 0;
		step[1] = 0;
	}
	AIforGobangGame::AIforGobangGame(int status, int turn, const char * src, int search_para)//status是AI的状态，表示执白还是执黑，turn是轮到AI下的时候轮换变量应该等于的值。如果自己实现控制流程也可弃用此变量
		//建议使用1和-1作为轮换变量，变更时*-1，1为黑，-1为白，初始为1
		//status必须为1或-1，黑棋为1，白棋为-1
		//src为权值文件路径，文件不存在时自动新建网络
	{
		search_layer = search_para;
		myStatus = status;
		p = player(myStatus, 0,search_para);
		AIturn = turn;
		step[0] = 0;
		step[1] = 0;
		bool isexist = false;
		std::fstream file;
		file.open(src, std::ios::_Nocreate | std::ios::in);
		isexist = file.is_open();
		if (isexist == true)
		{
			float tmp1[96][48];
			float tmp2[48];
			int i, j;
			for (i = 0; i < 96; i++)
			{
				for (j = 0; j < 48; j++)
				{
					file >> tmp1[i][j];
				}
			}
			for (i = 0; i < 48; i++)
			{
				file >> tmp2[i];
			}
			mynet = neuralnetworkofGobangBaseFeature(tmp1, tmp2);
		}
		else{
			mynet = neuralnetworkofGobangBaseFeature();
		}
		file.close();
	}
	void AIforGobangGame::makecmd(int *map, int &i, int &j)//对方未成五子时才会调用，因此只会记录未成五子的棋局
	{
		record(map,0);
		p.computermakecmd(map, i, j, mynet);//i,j为做出的决策，不改变map
		map[i*size + j] = myStatus;//下了子之后的局面
		record(map, 1);//记录
		map[i*size + j] = 0;//还原map
	}
	void AIforGobangGame::saveWeight(const char * src)//导出权值
	{
		std::fstream file;
		file.open(src, std::fstream::out | std::ios_base::trunc);
		int i, j;
		for (i = 0; i < 96; i++)
		{
			for (j = 0; j < 48; j++)
			{
				file << std::fixed << std::setprecision(2) << mynet.quanzhi1[i][j];
				file << std::endl;
			}
		}
		for (i = 0; i < 48; i++)
		{

			file << std::fixed << std::setprecision(2) << mynet.quanzhi2[i];
			file << std::endl;

		}
		file.close();
	}
	void AIforGobangGame::judge_iswin(int winner)//对iswin进行设置
	{
		if (myStatus == winner)
		{
			iswin = true;
		}
		else{
			iswin = false;
		}
	}
	void AIforGobangGame::TD_study()
	{
		mynet.TD_study(stepmap, step[(search_layer + 1) % 2], iswin);//只记录了未成五子的棋局，因此没有step和step-1之分
		for (int r = 0; r < step[0]; r++)//学习完毕，释放空间
		{
			free(stepmap[r]);
			
		}
		for (int r = 0; r < step[1]; r++)//学习完毕，释放空间
		{
			free(stepmap[size*size+r]);

		}
		
	}
	int AIforGobangGame::judge(int *map)//判断棋局状态
	{
		int s;
		int tmp_judge = judge_result(map);
		for (s = 0; s < size*size; s++)//扫描棋盘是否已满
		{
			if (map[s] == 0)
				break;
		}
		if (s == size*size&&tmp_judge == notfinish)//棋盘已满并且尚未结束，drawgame
		{
			tmp_judge = drawgame;
		}
		return tmp_judge;
	}