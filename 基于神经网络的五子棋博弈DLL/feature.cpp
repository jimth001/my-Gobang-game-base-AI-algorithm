#include "DllGobangAI.h"
float feature::willwin(bool isyourturn)
{
	if (isyourturn == true)
	{
		if (alive[3].num > 0 || halfalive[3].num>0)//1
		{
			//cout << "5.5route:" << endl;
			return 5.5;
		}
		else if (alive33 > 0 || alive23 > 0 || halfalive33 > 0 || vir_alive33 > 0 || vir_alive23 > 0 || vir_halfalive23 > 0 || vir_halfalive33 > 0 || vir_halfdead33>0)//xiabu*4 2
		{
			//cout << "4.5route:" << endl;
			//cout << alive33 << " " << alive23 << " " << vir_halfdead33 << " " << vir_halfalive33 << " " << vir_halfalive23 << " " << vir_halfdead33 << " " << alive23 << " " << vir_alive23 << " " << halfalive33 << endl;
			return 4.5;
		}
		else if (vir_alive22 > 0)//xiabushuangsan 3
		{
			//cout << "3.5route:" << endl;
			return 3.5;
		}
		else {
			return 0;
		}
	}
	else{
		if (alive[3].num>0 || halfalive34>0 || halfalive44>0 || halfdead44>0 || vir_halfalive34>0 || vir_halfalive44>0 || vir_halfdead44>0)//1
		{
			//cout << "5route:" << endl;
			return 5;
		}
		else if (alive33 > 0 || vir_alive33 > 0)//xiabu*4 2b
		{
			//cout << "4route:" << endl;
			//cout << alive33 << " " << alive23 << " " << vir_halfdead33 << " " << vir_halfalive33 << " " << vir_halfalive23 << " " << vir_halfdead33 << " " << alive23 << " " << vir_alive23 << " " << halfalive33 << endl;
			return 4;
		}
		/*else if (vir_alive22 > 0 )//xiabushuangsan 3
		{
		cout << "3route:" << endl;
		return 3;
		}*/
		else { return 0; }
	}
}
float feature::count_win_num(bool isyourturn)
{
	float rst = 0;
	if (isyourturn == true)
	{
		rst = rst + (float)5.5*(alive[3].num + halfalive[3].num);
		rst += (float)4.5*(alive33 + alive23 + halfalive33 + vir_alive33 + vir_alive23 + vir_halfalive23 + vir_halfalive33 + vir_halfdead33);
		rst += (float)3.5*vir_alive22;
		
	}
	else{
		rst -= (float)5 * (alive[3].num + halfalive34 + halfalive44 + halfdead44 + vir_halfalive34 + vir_halfalive44 + vir_halfdead44);
		rst -= (float)4 * (alive33 + vir_alive33);
		
	}
	return rst;
}
feature::feature(){
	dead[0].num = 0;
	dead[1].num = 0;
	dead[2].num = 0;
	dead[3].num = 0;
	halfalive[0].num = 0;
	halfalive[1].num = 0;
	halfalive[2].num = 0;
	halfalive[3].num = 0;
	alive[0].num = 0;
	alive[1].num = 0;
	alive[2].num = 0;
	alive[3].num = 0;
	vir_halfdead22 = 0; vir_halfdead23 = 0; vir_halfdead24 = 0; vir_halfdead33 = 0; vir_halfdead34 = 0; vir_halfdead44 = 0;
	vir_halfalive22 = 0; vir_halfalive23 = 0; vir_halfalive24 = 0; vir_halfalive33 = 0; vir_halfalive34 = 0; vir_halfalive44 = 0;
	vir_alive22 = 0; vir_alive23 = 0; vir_alive24 = 0; vir_alive33 = 0; vir_alive34 = 0; vir_alive44 = 0;
	halfdead22 = 0; halfdead23 = 0; halfdead24 = 0; halfdead33 = 0; halfdead34 = 0; halfdead44 = 0;
	halfalive22 = 0; halfalive23 = 0; halfalive24 = 0; halfalive33 = 0; halfalive34 = 0; halfalive44 = 0;
	alive22 = 0; alive23 = 0; alive24 = 0; alive33 = 0; alive34 = 0; alive44 = 0;
}
bool feature::vaild_ij_check(int t)//false是非法
{
	if (t<0 || t>14)
		return false;
	else return true;
}
void feature::heiOrbai_extractfeature(int *map, int size, int color)//提取基本特征，提取特征之前必须先判正负，不然此函数会数组越界
{
	int i, j;
	//行扫描：
	for (i = 0; i < size; i++)
	{
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		for (j = 0; j < size; j++)//扫描行
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sy == 0 || (last != color&&last != 0))
						start_dead = true;
				}

				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)
				{
					if (map[i*size + j] == 0){
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction1;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction1;
							alive[len - 1].num++;
						}
					}
					else{
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction1;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction1;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction1;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction1;
				halfalive[len - 1].num++;
			}
		}
	}
	//列扫描：
	for (j = 0; j < size; j++)
	{
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		for (i = 0; i < size; i++)//扫描lie
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sx == 0 || (last != color&&last != 0))//判断开头是否被堵
						start_dead = true;
				}
				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)//搜寻串长大于0
				{
					if (map[i*size + j] == 0){//结尾通
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction2;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction2;
							alive[len - 1].num++;
						}
					}
					else{//结尾被堵
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction2;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction2;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction2;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction2;
				halfalive[len - 1].num++;
			}
		}
	}
	//左上->右下扫描：
	//下半部分：
	for (i = 0; i < size; i++)
	{
		j = 0;
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		int rec_i = i;
		while (i < size&&j < size)//扫描3 xia
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sy == 0 || (last != color&&last != 0))//判断开头是否被堵
						start_dead = true;
				}
				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)//搜寻串长大于0
				{
					if (map[i*size + j] == 0){//结尾通
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction3;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction3;
							alive[len - 1].num++;
						}
					}
					else{//结尾被堵
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction3;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction3;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
			i++;
			j++;
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction3;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction3;
				halfalive[len - 1].num++;
			}
		}
		i = rec_i;
	}
	//上半部分：
	for (j = 1; j < size; j++)
	{
		i = 0;
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		int rec_j = j;
		while (i < size - 1 && j < size)//扫描3 shang
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sx == 0 || (last != color&&last != 0))//判断开头是否被堵
						start_dead = true;
				}
				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)//搜寻串长大于0
				{
					if (map[i*size + j] == 0){//结尾通
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction3;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction3;
							alive[len - 1].num++;
						}
					}
					else{//结尾被堵
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction3;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction3;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
			i++;
			j++;
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction3;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction3;
				halfalive[len - 1].num++;
			}
		}
		j = rec_j;
	}
	//左下->右上扫描：
	//下半部分：
	for (j = 0; j < size; j++)
	{
		i = size - 1;
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		int rec_j = j;
		while (i >= 0 && j < size)//扫描4 xia
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sx == size - 1 || (last != color&&last != 0))//判断开头是否被堵
						start_dead = true;
				}
				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)//搜寻串长大于0
				{
					if (map[i*size + j] == 0){//结尾通
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction4;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction4;
							alive[len - 1].num++;
						}
					}
					else{//结尾被堵
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction4;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction4;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
			i--;
			j++;
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction4;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction4;
				halfalive[len - 1].num++;
			}
		}
		j = rec_j;
	}
	//上半部分：
	for (i = 0; i < size - 1; i++)
	{
		j = 0;
		int len = 0;
		int last = color;
		int sx, sy, ex, ey;
		bool start_dead = false;
		int rec_i = i;
		while (i >= 0 && j < size - 1)//扫描4 shang
		{
			if (map[i*size + j] == color)
			{

				if (len == 0)
				{
					sx = i;
					sy = j;
					if (sy == 0 || (last != color&&last != 0))//判断开头是否被堵
						start_dead = true;
				}
				len++;
				ex = i;
				ey = j;
				last = color;
			}
			else{
				if (len > 0)//搜寻串长大于0
				{
					if (map[i*size + j] == 0){//结尾通
						if (start_dead == true){
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction4;
							halfalive[len - 1].num++;
						}
						else {
							int id = alive[len - 1].num;
							alive[len - 1].starti[id] = sx;
							alive[len - 1].startj[id] = sy;
							alive[len - 1].endi[id] = ex;
							alive[len - 1].endj[id] = ey;
							alive[len - 1].direction[id] = direction4;
							alive[len - 1].num++;
						}
					}
					else{//结尾被堵
						if (start_dead == true){
							int id = dead[len - 1].num;
							dead[len - 1].starti[id] = sx;
							dead[len - 1].startj[id] = sy;
							dead[len - 1].endi[id] = ex;
							dead[len - 1].endj[id] = ey;
							dead[len - 1].direction[id] = direction4;
							dead[len - 1].num++;
						}
						else {
							int id = halfalive[len - 1].num;
							halfalive[len - 1].starti[id] = sx;
							halfalive[len - 1].startj[id] = sy;
							halfalive[len - 1].endi[id] = ex;
							halfalive[len - 1].endj[id] = ey;
							halfalive[len - 1].direction[id] = direction4;
							halfalive[len - 1].num++;
						}
					}
				}
				len = 0;
				last = map[i*size + j];
			}
			i--;
			j++;
		}
		if (len > 0)
		{
			if (start_dead == true)
			{
				int id = dead[len - 1].num;
				dead[len - 1].starti[id] = sx;
				dead[len - 1].startj[id] = sy;
				dead[len - 1].endi[id] = ex;
				dead[len - 1].endj[id] = ey;
				dead[len - 1].direction[id] = direction4;
				dead[len - 1].num++;
			}
			else{
				int id = halfalive[len - 1].num;
				halfalive[len - 1].starti[id] = sx;
				halfalive[len - 1].startj[id] = sy;
				halfalive[len - 1].endi[id] = ex;
				halfalive[len - 1].endj[id] = ey;
				halfalive[len - 1].direction[id] = direction4;
				halfalive[len - 1].num++;
			}
		}
		i = rec_i;
	}
}
void feature::extend_feature(int *map, int size, int color)//特征自扩展,输入自扩展的棋谱，棋盘大小，要扩展的子（黑or白）
{
	int number;
	int i, k;
	//半活棋检查：
	for (k = 0; k < 4; k++){
		number = halfalive[k].num;
		for (i = 0; i < number; i++)
		{
			int tmpi;
			int tmpj;
			switch (halfalive[k].direction[i])
			{
			case 1:tmpi = halfalive[k].starti[i];
				tmpj = halfalive[k].startj[i];
				while (tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
						break;
					tmpj--;
				}
				halfalive[k].vir_si[i] = tmpi;
				halfalive[k].vir_sj[i] = tmpj + 1;
				tmpi = halfalive[k].endi[i];
				tmpj = halfalive[k].endj[i];
				while (tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpj++;
				}
				halfalive[k].vir_ei[i] = tmpi;
				halfalive[k].vir_ej[i] = tmpj - 1;
				break;
			case 2:tmpi = halfalive[k].starti[i];
				tmpj = halfalive[k].startj[i];
				while (tmpi >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
						break;
					tmpi--;
				}
				halfalive[k].vir_si[i] = tmpi + 1;
				halfalive[k].vir_sj[i] = tmpj;
				tmpi = halfalive[k].endi[i];
				tmpj = halfalive[k].endj[i];
				while (tmpi < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
				}
				halfalive[k].vir_ei[i] = tmpi - 1;
				halfalive[k].vir_ej[i] = tmpj;
				break;
			case 3:tmpi = halfalive[k].starti[i];
				tmpj = halfalive[k].startj[i];
				while (tmpi >= 0 && tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi--;
					tmpj--;
				}
				halfalive[k].vir_si[i] = tmpi + 1;
				halfalive[k].vir_sj[i] = tmpj + 1;
				tmpi = halfalive[k].endi[i];
				tmpj = halfalive[k].endj[i];
				while (tmpi < size&&tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
					tmpj++;
				}
				halfalive[k].vir_ei[i] = tmpi - 1;
				halfalive[k].vir_ej[i] = tmpj - 1;
				break;
			case 4:tmpi = halfalive[k].starti[i];
				tmpj = halfalive[k].startj[i];
				while (tmpi < size && tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
					tmpj--;
				}
				halfalive[k].vir_si[i] = tmpi - 1;
				halfalive[k].vir_sj[i] = tmpj + 1;
				tmpi = halfalive[k].endi[i];
				tmpj = halfalive[k].endj[i];
				while (tmpi >= 0 && tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi--;
					tmpj++;
				}
				halfalive[k].vir_ei[i] = tmpi + 1;
				halfalive[k].vir_ej[i] = tmpj - 1;
				break;
			default:
				break;
			}
		}
	}
	//活棋检查：
	for (k = 0; k < 4; k++){
		number = alive[k].num;
		for (i = 0; i < number; i++)
		{
			int tmpi;
			int tmpj;
			switch (alive[k].direction[i])
			{
			case 1:tmpi = alive[k].starti[i];
				tmpj = alive[k].startj[i];
				while (tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
						break;
					tmpj--;
				}
				alive[k].vir_si[i] = tmpi;
				alive[k].vir_sj[i] = tmpj + 1;
				tmpi = alive[k].endi[i];
				tmpj = alive[k].endj[i];
				while (tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpj++;
				}
				alive[k].vir_ei[i] = tmpi;
				alive[k].vir_ej[i] = tmpj - 1;
				break;
			case 2:tmpi = alive[k].starti[i];
				tmpj = alive[k].startj[i];
				while (tmpi >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
						break;
					tmpi--;
				}
				alive[k].vir_si[i] = tmpi + 1;
				alive[k].vir_sj[i] = tmpj;
				tmpi = alive[k].endi[i];
				tmpj = alive[k].endj[i];
				while (tmpi < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
				}
				alive[k].vir_ei[i] = tmpi - 1;
				alive[k].vir_ej[i] = tmpj;
				break;
			case 3:tmpi = alive[k].starti[i];
				tmpj = alive[k].startj[i];
				while (tmpi >= 0 && tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi--;
					tmpj--;
				}
				alive[k].vir_si[i] = tmpi + 1;
				alive[k].vir_sj[i] = tmpj + 1;
				tmpi = alive[k].endi[i];
				tmpj = alive[k].endj[i];
				while (tmpi < size&&tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
					tmpj++;
				}
				alive[k].vir_ei[i] = tmpi - 1;
				alive[k].vir_ej[i] = tmpj - 1;
				break;
			case 4:tmpi = alive[k].starti[i];
				tmpj = alive[k].startj[i];
				while (tmpi < size && tmpj >= 0)//反向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi++;
					tmpj--;
				}
				alive[k].vir_si[i] = tmpi - 1;
				alive[k].vir_sj[i] = tmpj + 1;
				tmpi = alive[k].endi[i];
				tmpj = alive[k].endj[i];
				while (tmpi >= 0 && tmpj < size)//正向扫描
				{
					
					if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
						break;
					tmpi--;
					tmpj++;
				}
				alive[k].vir_ei[i] = tmpi + 1;
				alive[k].vir_ej[i] = tmpj - 1;
				break;
			default:
				break;
			}
		}
	}
}
void feature::search_nodes(int *map, int size)//求交叉点，确定双三，三四个数
{
	int i, j, k;
	int sum = 0;//所有活棋和半活棋的数量
	sum += halfalive[1].num;
	sum += halfalive[2].num;
	sum += halfalive[3].num;
	sum += alive[1].num;
	sum += alive[2].num;
	sum += alive[3].num;
	sumforsearch *p = NULL;
	p = (struct sumforsearch *)malloc(sum*sizeof(sumforsearch));
	k = 0;
	//预处理1，半活棋和活棋放到sumforsearch里，处理掉不能成五子的
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < halfalive[i].num; j++)
		{
			if (abs(halfalive[i].vir_si[j] - halfalive[i].vir_ei[j]) >= 4 || abs(halfalive[i].vir_sj[j] - halfalive[i].vir_ej[j]) >= 4)
			{
				p[k].len = i + 1;//实长度
				p[k].vir_si = halfalive[i].vir_si[j];//虚坐标
				p[k].vir_sj = halfalive[i].vir_sj[j];
				p[k].vir_ei = halfalive[i].vir_ei[j];
				p[k].vir_ej = halfalive[i].vir_ej[j];
				p[k].direction = halfalive[i].direction[j];
				p[k].isalive = false;
				p[k].virlen = abs(halfalive[i].vir_si[j] - halfalive[i].vir_ei[j]) + 1;//虚长度
				if (p[k].virlen == 1)
				{
					p[k].virlen = abs(halfalive[i].vir_sj[j] - halfalive[i].vir_ej[j]) + 1;
				}
				k++;
			}
		}
	}
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < alive[i].num; j++)
		{
			if (abs(alive[i].vir_si[j] - alive[i].vir_ei[j]) >= 4 || abs(alive[i].vir_sj[j] - alive[i].vir_ej[j]) >= 4)//虚长度为5，即s-e==4，虚长度>=5才有成的可能
			{
				p[k].len = i + 1;//实长度
				p[k].vir_si = alive[i].vir_si[j];//虚坐标
				p[k].vir_sj = alive[i].vir_sj[j];
				p[k].vir_ei = alive[i].vir_ei[j];
				p[k].vir_ej = alive[i].vir_ej[j];
				p[k].direction = alive[i].direction[j];
				p[k].isalive = true;
				p[k].virlen = abs(alive[i].vir_si[j] - alive[i].vir_ei[j]) + 1;//虚长度
				if (p[k].virlen == 1)
				{
					p[k].virlen = abs(alive[i].vir_sj[j] - alive[i].vir_ej[j]) + 1;
				}
				k++;
			}
		}
	}
	sum = k;//此时sum是p数组中有效值的个数
	//预处理2,更新sumforsearch里连棋的实际长度
	for (i = 0; i < sum; i++)
	{
		int tmpi;
		int tmpj;
		int counter;
		switch (p[i].direction)
		{
		case 1:tmpj = p[i].vir_sj, counter = 0;
			while (tmpj <= p[i].vir_ej)
			{
				if (map[p[i].vir_si*size + tmpj] != 0)
				{
					counter++;
				}
				tmpj++;
			}
			p[i].len = counter;
			break;
		case 2:tmpi = p[i].vir_si, counter = 0;
			while (tmpi <= p[i].vir_ei)
			{
				if (map[tmpi*size + p[i].vir_sj] != 0)
				{
					counter++;
				}
				tmpi++;
			}
			p[i].len = counter;
			break;
		case 3:tmpi = p[i].vir_si, tmpj = p[i].vir_sj, counter = 0;
			while (tmpi <= p[i].vir_ei&&tmpj <= p[i].vir_ej)
			{
				if (map[tmpi*size + tmpj] != 0)
				{
					counter++;
				}
				tmpi++;
				tmpj++;
			}
			p[i].len = counter;
			break;
		case 4:tmpi = p[i].vir_si, tmpj = p[i].vir_sj, counter = 0;
			while (tmpi >= p[i].vir_ei&&tmpj <= p[i].vir_ej)
			{
				if (map[tmpi*size + tmpj] != 0)
				{
					counter++;
				}
				tmpi--;
				tmpj++;
			}
			p[i].len = counter;
			break;
		default:
			break;
		}
	}
	//两两匹配，求交点
	for (i = 0; i < sum; i++)
	{
		for (j = i + 1; j < sum; j++)
		{
			int judge = is_crossing(p[i].vir_si, p[i].vir_sj, p[i].vir_ei, p[i].vir_ej, p[j].vir_si, p[j].vir_sj, p[j].vir_ei, p[j].vir_ej, map, p[i].direction, p[j].direction);
			if (judge == 0)
			{
				//无交点
			}
			else if (judge == 1)
			{
				//交点是实点
				switch (p[i].len)
				{
				case 2:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive22++;
							}
							else{//zhenjia
								halfalive22++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive22++;
							}
							else{//jiajia
								halfdead22++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive23++;
							}
							else{//zhenjia
								halfalive23++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive23++;
							}
							else{//jiajia
								halfdead23++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive24++;
							}
							else{//zhenjia
								halfalive24++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive24++;
							}
							else{//jiajia
								halfdead24++;
							}
						}
					}
					break;
				case 3:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive23++;
							}
							else{//zhenjia
								halfalive23++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive23++;
							}
							else{//jiajia
								halfdead23++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive33++;
							}
							else{//zhenjia
								halfalive33++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive33++;
							}
							else{//jiajia
								halfdead33++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive34++;
							}
							else{//zhenjia
								halfalive34++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive34++;
							}
							else{//jiajia
								halfdead34++;
							}
						}
					}
					break;
				case 4:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive24++;
							}
							else{//zhenjia
								halfalive24++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive24++;
							}
							else{//jiajia
								halfdead24++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive34++;
							}
							else{//zhenjia
								halfalive34++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								halfalive34++;
							}
							else{//jiajia
								halfdead34++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								alive44++;
							}
							else{//zhenjia
								halfalive44++;
							}
						}
						else
						{
							//1322
							;
							if (p[j].isalive == true)//zhenjia
							{
								halfalive44++;
							}
							else{//jiajia
								halfdead44++;
							}
						}
					}
					break;
				default:
					break;
				}
			}
			else//judge==2
			{
				//交点是虚点
				switch (p[i].len)
				{
				case 2:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive22++;
							}
							else{//zhenjia
								vir_halfalive22++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive22++;
							}
							else{//jiajia
								vir_halfdead22++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive23++;
							}
							else{//zhenjia
								vir_halfalive23++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive23++;
							}
							else{//jiajia
								vir_halfdead23++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive24++;
							}
							else{//zhenjia
								vir_halfalive24++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive24++;
							}
							else{//jiajia
								vir_halfdead24++;
							}
						}
					}
					break;
				case 3:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive23++;
							}
							else{//zhenjia
								vir_halfalive23++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive23++;
							}
							else{//jiajia
								vir_halfdead23++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive33++;
							}
							else{//zhenjia
								vir_halfalive33++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive33++;
							}
							else{//jiajia
								vir_halfdead33++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive34++;
							}
							else{//zhenjia
								vir_halfalive34++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive34++;
							}
							else{//jiajia
								vir_halfdead34++;
							}
						}
					}
					break;
				case 4:
					if (p[j].len == 2)//pi =2 ;pj==2
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive24++;
							}
							else{//zhenjia
								vir_halfalive24++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive24++;
							}
							else{//jiajia
								vir_halfdead24++;
							}
						}
					}
					else if (p[j].len == 3)//pi 2 pj 3
					{
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive34++;
							}
							else{//zhenjia
								vir_halfalive34++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive34++;
							}
							else{//jiajia
								vir_halfdead34++;
							}
						}
					}
					else {//p[j].len==4
						if (p[i].isalive == true)
						{
							if (p[j].isalive == true)//zhenzhen
							{
								vir_alive44++;
							}
							else{//zhenjia
								vir_halfalive44++;
							}
						}
						else
						{
							if (p[j].isalive == true)//zhenjia
							{
								vir_halfalive44++;
							}
							else{//jiajia
								vir_halfdead44++;
							}
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
	free(p);
}
int feature::is_crossing(int si, int sj, int ei, int ej, int sx, int sy, int ex, int ey, int *map, int d1, int d2)//0没有交点，1交点是实点，2交点是虚点
{
	int len1 = max(abs(si - ei) + 1, abs(sj - ej) + 1);
	int len2 = max(abs(sx - ex) + 1, abs(sy - ey) + 1);
	int i, j;
	for (i = 0; i < len1; i++)
	{
		int recsx = sx, recsy = sy;
		for (j = 0; j < len2; j++)
		{
			if (si == sx&&sj == sy)
			{
				if (map[si*size + sj] == 0)
				{
					//cout << "222" << endl;
					return 2;
				}
				else
				{
					//cout << "111" << endl;
					return 1;
				}
			}
			switch (d2)
			{
			case 1:sy++; break;
			case 2:sx++; break;
			case 3:sx++; sy++; break;
			case 4:sx--; sy++; break;
			default:
				break;
			}
		}
		sx = recsx;
		sy = recsy;
		switch (d1)
		{
		case 1:sj++; break;
		case 2:si++; break;
		case 3:si++; sj++; break;
		case 4:si--; sj++; break;
		default:
			break;
		}
	}
	return 0;
}
int feature::max(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}
void feature::clear()
{
	dead[0].num = 0;
	dead[1].num = 0;
	dead[2].num = 0;
	dead[3].num = 0;
	halfalive[0].num = 0;
	halfalive[1].num = 0;
	halfalive[2].num = 0;
	halfalive[3].num = 0;
	alive[0].num = 0;
	alive[1].num = 0;
	alive[2].num = 0;
	alive[3].num = 0;
	vir_halfdead22 = 0; vir_halfdead23 = 0; vir_halfdead24 = 0; vir_halfdead33 = 0; vir_halfdead34 = 0; vir_halfdead44 = 0;
	vir_halfalive22 = 0; vir_halfalive23 = 0; vir_halfalive24 = 0; vir_halfalive33 = 0; vir_halfalive34 = 0; vir_halfalive44 = 0;
	vir_alive22 = 0; vir_alive23 = 0; vir_alive24 = 0; vir_alive33 = 0; vir_alive34 = 0; vir_alive44 = 0;
	halfdead22 = 0; halfdead23 = 0; halfdead24 = 0; halfdead33 = 0; halfdead34 = 0; halfdead44 = 0;
	halfalive22 = 0; halfalive23 = 0; halfalive24 = 0; halfalive33 = 0; halfalive34 = 0; halfalive44 = 0;
	alive22 = 0; alive23 = 0; alive24 = 0; alive33 = 0; alive34 = 0; alive44 = 0;
}
void feature::input(float shuru[], int pyl)//输入数组和偏移量
{
	int i;
	for (i = 0; i < 4; i++)
	{
		shuru[i + pyl] = (float)dead[i].num;
	}
	for (i = 0; i < 4; i++)
	{
		shuru[i + 4 + pyl] = (float)halfalive[i].num;
	}
	for (i = 0; i < 4; i++)
	{
		shuru[i + 8 + pyl] = (float)alive[i].num;
	}
	shuru[12 + pyl] = (float)vir_halfdead22, shuru[13 + pyl] = (float)vir_halfdead23, shuru[14 + pyl] = (float)vir_halfdead24, shuru[size + pyl] = (float)vir_halfdead33, shuru[16 + pyl] = (float)vir_halfdead34, shuru[17 + pyl] = (float)vir_halfdead44;
	shuru[18 + pyl] = (float)vir_halfalive22, shuru[19 + pyl] = (float)vir_halfalive23, shuru[20 + pyl] = (float)vir_halfalive24, shuru[21 + pyl] = (float)vir_halfalive33, shuru[22 + pyl] = (float)vir_halfalive34, shuru[23 + pyl] = (float)vir_halfalive44;
	shuru[24 + pyl] = (float)vir_alive22, shuru[25 + pyl] = (float)vir_alive23, shuru[26 + pyl] = (float)vir_alive24, shuru[27 + pyl] = (float)vir_alive33, shuru[28 + pyl] = (float)vir_alive34, shuru[29 + pyl] = (float)vir_alive44;
	shuru[30 + pyl] = (float)halfdead22, shuru[31 + pyl] = (float)halfdead23, shuru[32 + pyl] = (float)halfdead24, shuru[33 + pyl] = (float)halfdead33, shuru[34 + pyl] = (float)halfdead34, shuru[35 + pyl] = (float)halfdead44;
	shuru[36 + pyl] = (float)halfalive22, shuru[37 + pyl] = (float)halfalive23, shuru[38 + pyl] = (float)halfalive24, shuru[39 + pyl] = (float)halfalive33, shuru[40 + pyl] = (float)halfalive34, shuru[41 + pyl] = (float)halfalive44;
	shuru[42 + pyl] = (float)alive22, shuru[43 + pyl] = (float)alive23, shuru[44 + pyl] = (float)alive24, shuru[45 + pyl] = (float)alive33, shuru[46 + pyl] = (float)alive34, shuru[47 + pyl] = (float)alive44;
}