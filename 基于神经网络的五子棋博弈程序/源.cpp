#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;
int tmpcounter = 0;
const int size = 15;
const char * input_src = "e:\\input.txt";
const char * quanzhi_src = "e:\\quanzhi.txt";
void writeMapIntoTXT(int *inputarray, const char *src = input_src)//将inputarray数组写到路径为src的txt中
{
	fstream write;
	write.open(src, fstream::out | ios::app);
	int k;
	for (k = 0; k < size*size; k++){
		write << inputarray[k];
		write << endl;
	}
	write.close();
}
void printArray(int *inputarray)
{
	int i = 0, r = 0;
	for (i = 0; i < size*size; i++)
	{
		cout << inputarray[i] << " ";
		r++;
		if (r == size){
			r = 0;
			cout << endl;
		}
	}
}
struct  dead{
	int num;
	int starti[100], startj[100];
	int endi[100], endj[100];
	int direction[100];
	/*public:
	void add(int x, int y, int d){
	i[num] = x;
	i[num] = y;
	direction[num] = d;
	}*/
};
struct halfalive{
	int num;
	int starti[100], startj[100];
	int endi[100], endj[100];
	int direction[100];
	int vir_si[100], vir_sj[100], vir_ei[100], vir_ej[100];
};
struct alive{
	int num;
	int starti[100], startj[100];
	int endi[100], endj[100];
	int direction[100];
	int vir_si[100], vir_sj[100], vir_ei[100], vir_ej[100];
};
struct sumforsearch{
	int len;//真实长度 =2就是长度为2
	int vir_si, vir_sj, vir_ei, vir_ej;
	int virlen;
	int direction;
	bool isalive;
};
class feature{//描述一方的特征。整盘棋需要两个描述对象。
public:
	dead dead[4];
	halfalive halfalive[4];
	alive alive[4];
	int vir_halfdead22, vir_halfdead23, vir_halfdead24, vir_halfdead33, vir_halfdead34, vir_halfdead44;
	int vir_halfalive22, vir_halfalive23, vir_halfalive24, vir_halfalive33, vir_halfalive34, vir_halfalive44;
	int vir_alive22, vir_alive23, vir_alive24, vir_alive33, vir_alive34, vir_alive44;
	int halfdead22, halfdead23, halfdead24, halfdead33, halfdead34, halfdead44;
	int halfalive22, halfalive23, halfalive24, halfalive33, halfalive34, halfalive44;
	int alive22, alive23, alive24, alive33, alive34, alive44;
	int direction1 = 1;//横
	int direction2 = 2;//竖
	int direction3 = 3;//左下斜
	int direction4 = 4;//右上斜
	float willwin(bool isyourturn)
	{
		if (isyourturn == true)
		{
			if (alive[3].num > 0 || halfalive[3].num>0)//1
			{
				//cout << "5.5route:" << endl;
				return 5.5;
			}
			else if (alive33 > 0 || alive23 > 0 || halfalive33 > 0 || vir_alive33 > 0 || vir_alive23 > 0 || vir_halfalive23 > 0 || vir_halfalive33 > 0 || vir_halfdead33)//xiabu*4 2
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
	feature(){
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
	bool vaild_ij_check(int t)//false是非法
	{
		if (t<0 || t>14)
			return false;
		else return true;
	}
	void heiOrbai_extractfeature(int *map, int size, int color)//提取基本特征，提取特征之前必须先判正负，不然此函数会数组越界
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
	void extend_feature(int *map, int size, int color)//特征自扩展,输入自扩展的棋谱，棋盘大小，要扩展的子（黑or白）
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
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
							break;
					}
					halfalive[k].vir_si[i] = tmpi;
					halfalive[k].vir_sj[i] = tmpj + 1;
					tmpi = halfalive[k].endi[i];
					tmpj = halfalive[k].endj[i];
					while (tmpj < size)
					{
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					halfalive[k].vir_ei[i] = tmpi;
					halfalive[k].vir_ej[i] = tmpj - 1;
					break;
				case 2:tmpi = halfalive[k].starti[i];
					tmpj = halfalive[k].startj[i];
					while (tmpi >= 0)//反向扫描
					{
						tmpi--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
							break;
					}
					halfalive[k].vir_si[i] = tmpi + 1;
					halfalive[k].vir_sj[i] = tmpj;
					tmpi = halfalive[k].endi[i];
					tmpj = halfalive[k].endj[i];
					while (tmpi < size)
					{
						tmpi++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					halfalive[k].vir_ei[i] = tmpi - 1;
					halfalive[k].vir_ej[i] = tmpj;
					break;
				case 3:tmpi = halfalive[k].starti[i];
					tmpj = halfalive[k].startj[i];
					while (tmpi >= 0 && tmpj >= 0)//反向扫描
					{
						tmpi--;
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					halfalive[k].vir_si[i] = tmpi + 1;
					halfalive[k].vir_sj[i] = tmpj + 1;
					tmpi = halfalive[k].endi[i];
					tmpj = halfalive[k].endj[i];
					while (tmpi < size&&tmpj < size)//正向扫描
					{
						tmpi++;
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					halfalive[k].vir_ei[i] = tmpi - 1;
					halfalive[k].vir_ej[i] = tmpj - 1;
					break;
				case 4:tmpi = halfalive[k].starti[i];
					tmpj = halfalive[k].startj[i];
					while (tmpi < size && tmpj >= 0)//反向扫描
					{
						tmpi++;
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					halfalive[k].vir_si[i] = tmpi - 1;
					halfalive[k].vir_sj[i] = tmpj + 1;
					tmpi = halfalive[k].endi[i];
					tmpj = halfalive[k].endj[i];
					while (tmpi >= 0 && tmpj < size)//正向扫描
					{
						tmpi--;
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
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
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
							break;
					}
					alive[k].vir_si[i] = tmpi;
					alive[k].vir_sj[i] = tmpj + 1;
					tmpi = alive[k].endi[i];
					tmpj = alive[k].endj[i];
					while (tmpj < size)
					{
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					alive[k].vir_ei[i] = tmpi;
					alive[k].vir_ej[i] = tmpj - 1;
					break;
				case 2:tmpi = alive[k].starti[i];
					tmpj = alive[k].startj[i];
					while (tmpi >= 0)//反向扫描
					{
						tmpi--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)//当前点是对方的棋子时退出
							break;
					}
					alive[k].vir_si[i] = tmpi + 1;
					alive[k].vir_sj[i] = tmpj;
					tmpi = alive[k].endi[i];
					tmpj = alive[k].endj[i];
					while (tmpi < size)
					{
						tmpi++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					alive[k].vir_ei[i] = tmpi - 1;
					alive[k].vir_ej[i] = tmpj;
					break;
				case 3:tmpi = alive[k].starti[i];
					tmpj = alive[k].startj[i];
					while (tmpi >= 0 && tmpj >= 0)//反向扫描
					{
						tmpi--;
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					alive[k].vir_si[i] = tmpi + 1;
					alive[k].vir_sj[i] = tmpj + 1;
					tmpi = alive[k].endi[i];
					tmpj = alive[k].endj[i];
					while (tmpi < size&&tmpj < size)//正向扫描
					{
						tmpi++;
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					alive[k].vir_ei[i] = tmpi - 1;
					alive[k].vir_ej[i] = tmpj - 1;
					break;
				case 4:tmpi = alive[k].starti[i];
					tmpj = alive[k].startj[i];
					while (tmpi < size && tmpj >= 0)//反向扫描
					{
						tmpi++;
						tmpj--;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
					}
					alive[k].vir_si[i] = tmpi - 1;
					alive[k].vir_sj[i] = tmpj + 1;
					tmpi = alive[k].endi[i];
					tmpj = alive[k].endj[i];
					while (tmpi >= 0 && tmpj < size)//正向扫描
					{
						tmpi--;
						tmpj++;
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
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
	void search_nodes(int *map, int size)//求交叉点，确定双三，三四个数
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
				if (abs(halfalive[i].vir_si - halfalive[i].vir_ei) >= 4 || abs(halfalive[i].vir_sj - halfalive[i].vir_ej) >= 4)
				{
					p[k].len = i + 1;//实长度
					p[k].vir_si = halfalive[i].vir_si[j];//虚坐标
					p[k].vir_sj = halfalive[i].vir_sj[j];
					p[k].vir_ei = halfalive[i].vir_ei[j];
					p[k].vir_ej = halfalive[i].vir_ej[j];
					p[k].direction = halfalive[i].direction[j];
					p[k].isalive = false;
					p[k].virlen = abs(halfalive[i].vir_si - halfalive[i].vir_ei) + 1;//虚长度
					if (p[k].virlen == 1)
					{
						p[k].virlen = abs(halfalive[i].vir_sj - halfalive[i].vir_ej) + 1;
					}
					k++;
				}
			}
		}
		for (i = 1; i < 4; i++)
		{
			for (j = 0; j < alive[i].num; j++)
			{
				if (abs(alive[i].vir_si - alive[i].vir_ei) >= 4 || abs(alive[i].vir_sj - alive[i].vir_ej) >= 4)
				{
					p[k].len = i + 1;//实长度
					p[k].vir_si = alive[i].vir_si[j];//虚坐标
					p[k].vir_sj = alive[i].vir_sj[j];
					p[k].vir_ei = alive[i].vir_ei[j];
					p[k].vir_ej = alive[i].vir_ej[j];
					p[k].direction = alive[i].direction[j];
					p[k].isalive = true;
					p[k].virlen = abs(alive[i].vir_si - alive[i].vir_ei) + 1;//虚长度
					if (p[k].virlen == 1)
					{
						p[k].virlen = abs(alive[i].vir_sj - alive[i].vir_ej) + 1;
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
	int is_crossing(int si, int sj, int ei, int ej, int sx, int sy, int ex, int ey, int *map, int d1, int d2)//0没有交点，1交点是实点，2交点是虚点
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
	int max(int a, int b)
	{
		if (a > b)
			return a;
		else return b;
	}
	void clear()
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
	void input(float shuru[], int pyl)//输入数组和偏移量
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
};
class neuralnetworkofGobangBaseFeature{
public:
	float shuru[96];
	float yinhanceng1[48];
	float shuchu;
	float quanzhi1[96][48];
	float quanzhi2[48];
	float learnrate;
	feature wofangf = feature(), duifangf = feature();
	float getshuchu()
	{
		return shuchu;
	}
	void getshuru(int  *map)
	{
		wofangf.clear();
		duifangf.clear();
		wofangf.heiOrbai_extractfeature(map, size, 1);//前48个是我方特征
		wofangf.extend_feature(map, size, 1);
		wofangf.search_nodes(map, size);
		wofangf.input(shuru, 0);
		duifangf.heiOrbai_extractfeature(map, size, -1);
		duifangf.extend_feature(map, size, -1);
		duifangf.search_nodes(map, size);
		duifangf.input(shuru, 48);
		int i;
		float sum = 0;
		for (i = 0; i < 96; i++)
		{
			sum += shuru[i];
		}
		for (i = 0; i < 96; i++)
		{
			shuru[i] /= sum;
		}
	}
	void cal_shuchu()
	{
		int i, j;
		for (i = 0; i < 48; i++)
		{
			yinhanceng1[i] = 0;
			for (j = 0; j < 96; j++)
			{
				yinhanceng1[i] += shuru[j] * quanzhi1[j][i];
			}
		}
		shuchu = 0;
		for (i = 0; i < 48; i++)
		{
			shuchu = yinhanceng1[i] * quanzhi2[i];
		}
	}
	void feedback(float goal)
	{
		int i, j;
		for (i = 0; i < 96; i++)
		{
			for (j = 0; j < 48; j++)
			{
				quanzhi1[i][j] -= learnrate*(shuchu - goal)*quanzhi2[j] * shuru[i];
			}
		}
		for (i = 0; i < 48; i++)
		{
			quanzhi2[i] -= learnrate*(shuchu - goal)*yinhanceng1[i];
		}
	}
	neuralnetworkofGobangBaseFeature()
	{
		int i, j;
		for (i = 0; i < 96; i++)
		{
			for (j = 0; j < 48; j++)
			{
				if (i<48)
					quanzhi1[i][j] = (float)(0.01);
				else
					quanzhi1[i][j] = (float)(-0.01);
			}
		}
		for (i = 0; i < 48; i++)
		{
			quanzhi2[i] = (float)0.01;
		}
		learnrate = (float)0.5;
	}
	neuralnetworkofGobangBaseFeature(float tmp1[96][48], float tmp2[48])
	{
		int i, j;
		for (i = 0; i < 96; i++)
		{
			for (j = 0; j < 48; j++)
			{
				quanzhi1[i][j] = tmp1[i][j];
			}
		}
		for (i = 0; i < 48; i++)
		{
			quanzhi2[i] = tmp2[i];
		}
		learnrate = (float)0.5;
	}
	void TD_study(int **step, int stepnum, bool iswin){//最后一步不学习，含5个子的都不学习
		cout << "learning,please waiting" << endl;
		float expectedvalue;
		stepnum--;//此时stepnum是数组中最后一个值

		if (iswin == true)
		{
			expectedvalue = 1;
		}
		else{
			expectedvalue = -1;
		}
		while (stepnum >= 0)
		{
			writeMapIntoTXT(step[stepnum]);
			getshuru(step[stepnum]);
			cal_shuchu();
			feedback(expectedvalue);
			cal_shuchu();
			expectedvalue = shuchu;
			stepnum--;
		}
		cout << "learning finish" << endl;
	}
};
class player{
public:int mystatus;//身份，黑棋还是白棋
	   int myid;//id为0代表己方，为1代表对手
	   static const int computer = 0;
	   static const int person = 1;
	   int cmdi, cmdj;
	   float maxint;
	   float minint;
	   static const int heistatus = 1;
	   static const int baistatus = -1;

	   static const int heiwin = 1;//黑赢
	   static const int baiwin = -1;
	   static const int drawgame = 0;//平局
	   static const int notfinish = 9;//尚未结束
	   static const int heizi = 1;
	   static const int baizi = -1;
	   static const int nilzi = 0;
	   player()
	   {
		   mystatus = 0;
		   myid = 0;
		   cmdi = 0;
		   cmdj = 0;
		   maxint = 10000000;
		   minint = -10000000;
	   }
	   player(int sta, int id)
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
	   float valuefunc(int *p, int &x, int &y, neuralnetworkofGobangBaseFeature & net){//估值函数
		   //要根据我方执黑/白对+1-1进行转化：
		   //默认我方（电脑） 白
		   int r = notfinish;
		   r = judge(p, x, y, 5);
		   if (r == (mystatus*(-1))) { /*printArray(p); system("pause");*/return net.getshuchu() + minint / 2; }
		   else if (r == mystatus)  { /*printArray(p); system("pause");*/ return net.getshuchu() + maxint / 2; }
		   int tmp[size*size];
		   int i;
		   if (mystatus = baistatus)
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
	   float max(float a, float b)
	   {
		   if (a > b)
			   return a;
		   else return b;
	   }
	   float min(float a, float b)
	   {
		   if (a < b)
			   return a;
		   else return b;
	   }
	   int judge(int *tmap, int &x, int &y, int lenlian)//判断棋局
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
	   float search(int *p, int &ix, int &jy, int depth, int depthlimit, float rootvalue, neuralnetworkofGobangBaseFeature & net)//depth当前树的深度，根节点为0，depthlimit树深度的限制,如果层数是01234，则一共有5层.首次搜索rootvalue值任意
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
			   for (x = size / 2; x < size; x++)
			   {
				   for (y = size / 2; y < size; y++)
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
			   for (x = size / 2; x >= 0; x--)
			   {
				   for (y = size / 2; y < size; y++)
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
			   for (x = size / 2; x >= 0; x--)
			   {
				   for (y = size / 2; y >= 0; y--)
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
			   for (x = size / 2; x < size; x++)
			   {
				   for (y = size / 2; y >= 0; y--)
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
	   void computermakecmd(int *map, int &i, int &j, neuralnetworkofGobangBaseFeature & net){
		   tmpcounter = 0;
		   int x = 0, y = 0;
		   search(map, x, y, 0, 3, maxint, net);
		   cout << "搜索完毕" << endl;//先搜3层.此状态下该zijixia
		   system("pause");
		   if (map[cmdi*size + cmdj] != 0)
		   {
			   cmdi = x;
			   cmdj = y;
		   }
		   i = cmdi;
		   j = cmdj;
	   }
	   void waitpersonmakecmd(int *map, int &i, int &j){//等待出招
		   cout << "请输入坐标" << endl;
	   reinput:cin >> i >> j;
		   if (map[i*size + j] != 0 || i<0 || i>size - 1 || j<0 || j>size - 1)
		   {
			   cout << "坐标非法，请重新输入！" << endl;
			   goto reinput;
		   }
	   }
	   void setmyid(int id){//设置player的id，自己还是对手。
		   if (id == computer || id == person){
			   myid = id;
		   }
		   else{
			   //id 值错误
		   }
	   }
};
//。。
class AIforGobangGame
{
private:
	int myStatus;
	int *stepmap[size*size];//更改棋盘大小的话，此处需要更改
	int step;
	player p;
	neuralnetworkofGobangBaseFeature mynet;
	bool iswin;

public:
	int AIturn;
	AIforGobangGame()
	{

	}
	void init()
	{
		iswin = false;
		step = 0;
	}
	AIforGobangGame(int status, int turn, float qz1[96][48], float qz2[48])
	{
		myStatus = status;
		p = player(myStatus, 0);
		mynet = neuralnetworkofGobangBaseFeature(qz1, qz2);
		AIturn = turn;
		step = 0;
	}
	AIforGobangGame(int status, int turn, neuralnetworkofGobangBaseFeature &net)
	{
		myStatus = status;
		p = player(myStatus, 0);
		mynet = net;
		AIturn = turn;
		step = 0;
	}
	~AIforGobangGame()
	{

	}
	void record(int *map)//记录中己方子为1，不论黑白
	{
		int *tmp = (int *)malloc(size*size*sizeof(int));//记录对手下完的局面
		int k;
		if (myStatus == p.baistatus)//如果AI执白棋，记录棋局时先翻转
		{
			for (k = 0; k < size*size; k++)
			{
				tmp[k] = map[k] * (-1);
			}
		}
		else {
			for (k = 0; k < size*size; k++)
			{
				tmp[k] = map[k];
			}
		}
		stepmap[step] = tmp;
		step++;
	}
	void makecmd(int *map, int &i, int &j)//对方未成五子时才会调用，因此只会记录未成五子的棋局
	{
		record(map);
		p.computermakecmd(map, i, j, mynet);
	}
	void saveWeight()//导出权值
	{
		fstream file;
		file.open(quanzhi_src, fstream::out | ios_base::trunc);
		int i, j;
		for (i = 0; i < 96; i++)
		{
			for (j = 0; j < 48; j++)
			{
				file << fixed << setprecision(2) << mynet.quanzhi1[i][j];
				file << endl;
			}
		}
		for (i = 0; i < 48; i++)
		{

			file << fixed << setprecision(2) << mynet.quanzhi2[i];
			file << endl;

		}
		file.close();
	}
	void judge_iswin(int winner)
	{
		if (myStatus == winner)
		{
			iswin = true;
		}
		else{
			iswin = false;
		}
	}
	void TD_study()
	{
		mynet.TD_study(stepmap, step, iswin);//只记录了未成五子的棋局，因此没有step和step-1之分
		for (int r = 0; r < step; r++)//学习完毕，释放空间
		{
			cout << "release memory..." << endl;
			free(stepmap[r]);
			cout << "release memory finish" << endl;
		}
	}
};
class GobangGame
{
	friend class player;
private:
	int *map;//黑棋用 -1表示，白棋用1表示，无子用0表示
	int turns;//记录轮到谁下棋的标志。1先-1后
	AIforGobangGame myAI;
	player person;
public:
	static const int heiturn = 1;//轮到黑
	static const int baiturn = -1;//轮到白
	static const int heiwin = 1;//黑赢
	static const int baiwin = -1;
	static const int drawgame = 0;//平局
	static const int notfinish = 9;//尚未结束
	static const int heizi = 1;
	static const int baizi = -1;
	static const int nilzi = 0;
	static const int heistatus = 1;
	static const int baistatus = -1;
	GobangGame(int status, neuralnetworkofGobangBaseFeature net){
		map = (int*)malloc(size*size*sizeof(int));
		turns = 1;
		myAI = AIforGobangGame(status, status, net);
		person = player(status*(-1), 1);// 人
	}
	void init()
	{
		initmap();
		turns = 1;
		myAI.init();
	}
	void initmap()//初始化棋盘
	{
		int i, j;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				map[i*size + j] = 0;
			}
		}
	}
	~GobangGame(){
		free(map);
	}
	void nextturn()//计算下次轮到谁
	{
		turns = turns*(-1);
	}
	int judge()//判断棋局
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
	bool movement(int who, int i, int j)//一方行动
	{
		if (map[i*size + j] == nilzi){
			if (who == heiturn)
			{
				map[i*size + j] = heizi;
			}
			else if (who == baiturn){
				map[i*size + j] = baizi;
			}
			else{
				//wrong
			}
			nextturn();
			return true;
		}
		else{
			return false;//此处不能落子
		}
	}
	int * getmap()
	{
		return map;
	}
	void updateUI()
	{
		system("cls");
		int r = 0, i;
		for (i = 0; i < size*size; i++)
		{
			if (map[i] == 0)
				cout << "." << " ";
			else if (map[i] == 1)
				cout << "*" << " ";
			else cout << "o" << " ";
			r++;
			if (r == size){
				r = 0;
				cout << endl;
			}
		}
	}
	void controller()//博弈流程控制,一局
	{
		int tmp_judge = notfinish;
		while (tmp_judge == notfinish)
		{
			if (turns == myAI.AIturn)//轮到电脑下
			{
				//cout << turns << endl;
				int i = 0, j = 0;
				myAI.makecmd(map, i, j);
				map[i*size + j] = myAI.AIturn;

				//update UI:
				updateUI();

			}
			else//轮到玩家下
			{
				//cout << turns << endl;
				int i = 0, j = 0;
				person.waitpersonmakecmd(map, i, j);
				map[i*size + j] = turns;
				updateUI();
			}
			tmp_judge = judge();
			nextturn();
			int s;
			for (s = 0; s < size*size; s++)//扫描棋盘是否已满
			{
				if (map[s] == 0)
					break;
			}
			if (s == size*size&&tmp_judge == notfinish)//棋盘已满并且尚未结束，drawgame
			{
				tmp_judge = drawgame;
				break;
			}
		}
		if (tmp_judge == heiwin){
			//黑棋赢
			cout << "heiwin" << endl;
		}
		else if (tmp_judge == baiwin){
			//白棋赢
			cout << "baiwin" << endl;
		}
		else if (tmp_judge == drawgame)
		{
			cout << "drawgame" << endl;//平局不学习
		}
		if (tmp_judge == myAI.AIturn)
		{
			cout << "you lose" << endl;
			myAI.judge_iswin(tmp_judge);
			myAI.TD_study();
		}
		else{
			cout << "you win" << endl;
			myAI.judge_iswin(tmp_judge);
			myAI.TD_study();
		}


	}
};
void test2(){
	srand(time(NULL));
	int inputarray[size*size] = { 0 };
	bool isexist;
	fstream read;
	read.open(input_src, ios::_Nocreate | ios::in);
	for (int i = 0; i < size*size; i++)
	{
		read >> inputarray[i];
	}
	fstream file;
	file.open(quanzhi_src, ios::_Nocreate | ios::in);
	isexist = file.is_open();
	neuralnetworkofGobangBaseFeature mynet;
	if (isexist == true)
	{
		cout << "quanzhi.txt存在" << endl;
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
	fstream input;
	input.open(input_src, ios::_Nocreate | ios::in);
	int i = 0, r = 0;
	for (i = 0; i < size*size; i++)
	{
		cout << inputarray[i] << " ";
		r++;
		if (r == size){
			r = 0;
			cout << endl;
		}
	}
	float reward = 0;
	mynet.getshuru(inputarray);
	do
	{
		mynet.cal_shuchu();
		cout << fixed << setprecision(2) << mynet.getshuchu() << endl;
		cin >> reward;
		if (fabs(reward) < 0.01) {
			if (!input.eof()){
				for (int i = 0; i < size*size; i++)//读新棋局
				{
					read >> inputarray[i];
				}
				//显示：
				for (int i = 0; i < size*size; i++)
				{
					cout << inputarray[i] << " ";
					r++;
					if (r == size){
						r = 0;
						cout << endl;
					}
				}
				//重置神经网络的输入：
				mynet.getshuru(inputarray);
				continue;
			}
			else{
				break;
			}
		}
		if (fabs(reward - 99999)<0.01) break;
		mynet.feedback(reward);
	} while (1);
	read.close();
	file.open(quanzhi_src, fstream::out | ios_base::trunc);
	int j;
	for (i = 0; i < 96; i++)
	{
		for (j = 0; j < 48; j++)
		{
			file << fixed << setprecision(2) << mynet.quanzhi1[i][j];
			file << endl;
		}
	}
	for (i = 0; i < 48; i++)
	{

		file << fixed << setprecision(2) << mynet.quanzhi2[i];
		file << endl;
	}
	input.close();
	file.close();
}
void pvc()//人机对弈
{
	cout << "欢迎使用本程序，本程序采用行列坐标输入，默认您执黑先行，祝您玩得愉快！如果期待后续版本，请关注本人git:https://github.com/jimth001/my-Gobang-game-base-AI-algorithm " << endl;
	cout << "作者：王运里" << endl;
	bool isexist = false;
	fstream file;
	file.open(quanzhi_src, ios::_Nocreate | ios::in);
	isexist = file.is_open();
	neuralnetworkofGobangBaseFeature mynet;
	if (isexist == true)
	{
		cout << "quanzhi.txt存在" << endl;
		system("pause");
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
	player com = player(1, 0);//电脑执白
	int AIstatus = -1;
	int restart = 1;
	while (restart == 1)
	{
		GobangGame *ga = new GobangGame(AIstatus, mynet);//size*size 电脑执白
		ga->init();
		ga->controller();
		cout << "重来请输入1" << endl;
		cin >> restart;
		delete ga;
		//ga.init();
	}

}
int main()
{
	pvc();//基于神经网络2的人机对弈
	//test2();//强化学习训练神经网络2
	return 0;
}

