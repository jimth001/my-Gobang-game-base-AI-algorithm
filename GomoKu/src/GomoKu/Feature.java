package GomoKu;

import java.util.ArrayList;
import java.util.Iterator;
import javax.swing.JOptionPane;

class  Dead{
	public int num;
	final public int size=100;
	public int starti[], startj[];
	public int endi[], endj[];
	public int direction[];
	public Dead()
	{
		num=0;
		starti=new int [size];
		startj=new int [size];
		endi=new int [size];
		endj=new int [size];
		direction=new int [size];
	}
	/*public:
	void add(int x, int y, int d){
	i[num] = x;
	i[num] = y;
	direction[num] = d;
	}*/
};
class Halfalive{
	public int num;
	final public int size=100;
	public int starti[], startj[];
	public int endi[], endj[];
	public int direction[];
	public int vir_si[], vir_sj[], vir_ei[], vir_ej[];
	public Halfalive()
	{
		num=0;
		starti=new int [size];
		startj=new int [size];
		endi=new int [size];
		endj=new int [size];
		direction=new int [size];
		vir_si=new int [size];
		vir_sj=new int [size];
		vir_ei=new int [size];
		vir_ej=new int [size];
	}
};
class Alive{
	public int num;
	final public int size=100;
	public int starti[], startj[];
	public int endi[], endj[];
	public int direction[];
	public int vir_si[], vir_sj[], vir_ei[], vir_ej[];
	public Alive()
	{
		num=0;
		starti=new int [size];
		startj=new int [size];
		endi=new int [size];
		endj=new int [size];
		direction=new int [size];
		vir_si=new int [size];
		vir_sj=new int [size];
		vir_ei=new int [size];
		vir_ej=new int [size];
	}
};
class Sumforsearch{
	public int len;//真实长度 =2就是长度为2
	public int vir_si, vir_sj, vir_ei, vir_ej;
	public int virlen;
	public int direction;
	public boolean isalive;
	public Sumforsearch()
	{
		
	}
};
class Feature{//描述一方的特征。整盘棋需要两个描述对象。
	final public int size=15;
	//method:
public Dead dead[];
public Halfalive halfalive[];
public Alive alive[];
public int vir_halfdead22, vir_halfdead23, vir_halfdead24, vir_halfdead33, vir_halfdead34, vir_halfdead44;
public int vir_halfalive22, vir_halfalive23, vir_halfalive24, vir_halfalive33, vir_halfalive34, vir_halfalive44;
public int vir_alive22, vir_alive23, vir_alive24, vir_alive33, vir_alive34, vir_alive44;
public int halfdead22, halfdead23, halfdead24, halfdead33, halfdead34, halfdead44;
public int halfalive22, halfalive23, halfalive24, halfalive33, halfalive34, halfalive44;
public int alive22, alive23, alive24, alive33, alive34, alive44;
public int direction1 = 1;//横
public int direction2 = 2;//竖
public int direction3 = 3;//左下斜
public int direction4 = 4;//右上斜
public float willwin(boolean isyourturn)

{
	if (isyourturn == true)
	{
		if (alive[3].num > 0 || halfalive[3].num>0)//1
		{
			//cout << "5.5route:" << endl;
			return (float) 5.5;
		}
		else if (alive33 > 0 || alive23 > 0 || halfalive33 > 0 || vir_alive33 > 0 || vir_alive23 > 0 || vir_halfalive23 > 0 || vir_halfalive33 > 0 || vir_halfdead33>0)//xiabu*4 2
		{
			//cout << "4.5route:" << endl;
			//cout << alive33 << " " << alive23 << " " << vir_halfdead33 << " " << vir_halfalive33 << " " << vir_halfalive23 << " " << vir_halfdead33 << " " << alive23 << " " << vir_alive23 << " " << halfalive33 << endl;
			return (float) 4.5;
		}
		else if (vir_alive22 > 0)//xiabushuangsan 3
		{
			//cout << "3.5route:" << endl;
			return (float) 3.5;
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
public float count_win_num(boolean isyourturn)
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
public Feature()
{
	dead=new Dead[4];
	halfalive=new Halfalive[4];
	alive=new Alive[4];
	int i;
	for(i=0;i<4;i++)
	{
		dead[i]=new Dead();
		halfalive[i]=new Halfalive();
		alive[i]=new Alive();
	}
	
	
	
	vir_halfdead22 = 0; vir_halfdead23 = 0; vir_halfdead24 = 0; vir_halfdead33 = 0; vir_halfdead34 = 0; vir_halfdead44 = 0;
	vir_halfalive22 = 0; vir_halfalive23 = 0; vir_halfalive24 = 0; vir_halfalive33 = 0; vir_halfalive34 = 0; vir_halfalive44 = 0;
	vir_alive22 = 0; vir_alive23 = 0; vir_alive24 = 0; vir_alive33 = 0; vir_alive34 = 0; vir_alive44 = 0;
	halfdead22 = 0; halfdead23 = 0; halfdead24 = 0; halfdead33 = 0; halfdead34 = 0; halfdead44 = 0;
	halfalive22 = 0; halfalive23 = 0; halfalive24 = 0; halfalive33 = 0; halfalive34 = 0; halfalive44 = 0;
	alive22 = 0; alive23 = 0; alive24 = 0; alive33 = 0; alive34 = 0; alive44 = 0;
}
public boolean vaild_ij_check(int t)
//false是非法
{
	if (t<0 || t>14)
		return false;
	else return true;
}
public void heiOrbai_extractfeature(int []map, int size, int color)
//提取基本特征，提取特征之前必须先判正负，不然此函数会数组越界
{
	int i, j;
	//行扫描：
	for (i = 0; i < size; i++)
	{
		int len = 0;
		int last = color;
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
		int sx=0; int sy=0;int ex=0;int ey=0;
		boolean start_dead = false;
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
public void extend_feature(int []map, int size, int color)
//特征自扩展,输入自扩展的棋谱，棋盘大小，要扩展的子（黑or白）
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
				while (tmpj < size)
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
				while (tmpi < size)
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
				while (tmpj < size)
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
					
					try {
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
						tmpi--;
					} catch (java.lang.ArrayIndexOutOfBoundsException e) {
						// TODO: handle exception
						JOptionPane.showMessageDialog(null, tmpi+"  "+tmpj+"  "+map.length, tmpi+"  "+tmpj+"  "+map.length, JOptionPane.ERROR_MESSAGE); 
					}
				}
				alive[k].vir_si[i] = tmpi + 1;
				alive[k].vir_sj[i] = tmpj;
				tmpi = alive[k].endi[i];
				tmpj = alive[k].endj[i];
				while (tmpi < size)
				{
					
					try {
						if (map[tmpi*size + tmpj] != 0 && map[tmpi*size + tmpj] != color)
							break;
						tmpi++;
					} catch (java.lang.ArrayIndexOutOfBoundsException e) {
						// TODO: handle exception
						JOptionPane.showMessageDialog(null, tmpi+"  "+tmpj+"  "+map.length, tmpi+"  "+tmpj+"  "+map.length, JOptionPane.ERROR_MESSAGE); 
					}
					
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
public void search_nodes(int []map, int size,int color)//求交叉点，确定双三，三四个数
{
	/*//调试信息start
	system("cls");
	for (int r1 = 0; r1 < size; r1++)
	{
		for (int r2 = 0; r2 < size; r2++)
		{
			std::cout << map[r1*size + r2] <<"  ";
		}
		std::cout << std::endl;
	}
	//调试信息end*/
	int i, j, k;
	int sum = 0;//所有活棋和半活棋的数量
	sum += halfalive[0].num;
	sum += halfalive[1].num;
	sum += halfalive[2].num;
	sum += halfalive[3].num;
	sum += alive[0].num;
	sum += alive[1].num;
	sum += alive[2].num;
	sum += alive[3].num;
	//
	//..
	ArrayList<Sumforsearch> p =new ArrayList<Sumforsearch>(sum);
	//System.out.println(p.size());
	//sumforsearch *p = NULL;
	//p = (struct sumforsearch *)malloc(sum*sizeof(sumforsearch));
	k = 0;
	//预处理1，半活棋和活棋放到sumforsearch里，处理掉不能成五子的
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < halfalive[i].num; j++)
		{
			if (Math.abs(halfalive[i].vir_si[j] - halfalive[i].vir_ei[j]) >= 4 || Math.abs(halfalive[i].vir_sj[j] - halfalive[i].vir_ej[j]) >= 4)
			{
				p.add(new Sumforsearch());
				p.get(k).len = i + 1;//实长度//................................................
				p.get(k).vir_si = halfalive[i].vir_si[j];//虚坐标
				p.get(k).vir_sj = halfalive[i].vir_sj[j];
				p.get(k).vir_ei = halfalive[i].vir_ei[j];
				p.get(k).vir_ej = halfalive[i].vir_ej[j];
				p.get(k).direction = halfalive[i].direction[j];
				p.get(k).isalive = false;
				p.get(k).virlen = Math.abs(halfalive[i].vir_si[j] - halfalive[i].vir_ei[j]) + 1;//虚长度
				if (p.get(k).virlen == 1)
				{
					p.get(k).virlen = Math.abs(halfalive[i].vir_sj[j] - halfalive[i].vir_ej[j]) + 1;
				}
				k++;
			}
		}
	}
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < alive[i].num; j++)
		{
			if (Math.abs(alive[i].vir_si[j] - alive[i].vir_ei[j]) >= 4 || Math.abs(alive[i].vir_sj[j] - alive[i].vir_ej[j]) >= 4)//虚长度为5，即s-e==4，虚长度>=5才有成的可能
			{
				p.add(new Sumforsearch());
				p.get(k).len = i + 1;//实长度
				p.get(k).vir_si = alive[i].vir_si[j];//虚坐标
				p.get(k).vir_sj = alive[i].vir_sj[j];
				p.get(k).vir_ei = alive[i].vir_ei[j];
				p.get(k).vir_ej = alive[i].vir_ej[j];
				p.get(k).direction = alive[i].direction[j];
				p.get(k).isalive = true;
				p.get(k).virlen = Math.abs(alive[i].vir_si[j] - alive[i].vir_ei[j]) + 1;//虚长度
				if (p.get(k).virlen == 1)
				{
					p.get(k).virlen = Math.abs(alive[i].vir_sj[j] - alive[i].vir_ej[j]) + 1;
				}
				k++;
			}
		}
	}
	//System.out.println(p.size());
	
	sum = k;//此时sum是p数组中有效值的个数
	//消除等价P【k】：hash位图
	char hash_array[] = new char[7500];
	for(int tc=0;tc<7500;tc++)
	{
		hash_array[tc]=0;
	}
	int hash_value_of_ij;
	//Vector<Sumforsearch> tmp_p= new Vector<Sumforsearch>();
	Iterator<Sumforsearch> sListIterator = p.iterator();
	while (sListIterator.hasNext())
	{
		Sumforsearch tmp_Sumforsearch=sListIterator.next();
		hash_value_of_ij = tmp_Sumforsearch.vir_si * 15 * 15 * 15 + tmp_Sumforsearch.vir_sj * 15 * 15 + tmp_Sumforsearch.vir_ei * 15 + tmp_Sumforsearch.vir_ej;
		int ts, tmod;
		ts = hash_value_of_ij / 8;
		tmod = hash_value_of_ij % 8;
		char tmp_ym = (char)(Math.pow(2,tmod));//掩码
		char tmp = (char) (hash_array[ts] &tmp_ym);
		char t_judge = 0;
		if (tmp == t_judge)//不存在
		{
			hash_array[ts] = (char) (hash_array[ts] | tmp_ym);
		}
		else{
			sListIterator.remove();
		}
	}
	//
	sum = p.size();
	//预处理2,更新sumforsearch里连棋的实际长度--------important!
	for (i = 0; i < sum; i++)
	{
		int counter;
		boolean meet_space = false;
		boolean find_next_s = false;
		int nextsj ,nextsi;
		int tsj, tej, tsi, tei;
		boolean first_save = false;
		int circle_times;//循环控制变量
		switch (p.get(i).direction)
		{
		case 1: counter = 0;
			tsj = p.get(i).vir_sj;
			tej = p.get(i).vir_sj;
			meet_space = false;
			find_next_s = false;
			first_save = false;
			nextsj = p.get(i).vir_sj;
			circle_times = p.get(i).vir_ej;
			while (tej<=circle_times)
			{
				if (map[p.get(i).vir_si*size + tej] != 0)//有子
				{
					counter++;
					if (find_next_s == false)//没找到开头
					{
						if (meet_space == false)//没遇到空格
						{
							nextsj = tej;
						}
						else{
							nextsj = tej;
							find_next_s = true;
						}
						
					}
					tej++;
				}
				else{//此时tej指向空格
					if (meet_space == false)
					{
						if (counter == 0)
						{
							while (tej <= circle_times&&map[p.get(i).vir_si*size + tej] == 0)
							{
								tej++;
								tsj++;
							}
						}
						else
						{
							meet_space = true;
							tej++;
						}
					}
					else{
						if (counter == 1)
						{
							tsj++;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
							continue;
						}
						if (first_save==false)
						{
							p.get(i).len = counter;
							p.get(i).vir_ej = nextsj;
							p.get(i).vir_sj = tsj;
							if (tsj == 0 ||(tsj>=0&& map[p.get(i).vir_si*size + tsj - 1] != 0))
							{
								p.get(i).isalive = false;
							}
							else{
								p.get(i).isalive = true;
							}
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
						else{
							p.add(new Sumforsearch());
							p.get(p.size() - 1).vir_sj = tsj;
							p.get(p.size() - 1).vir_ej = nextsj;
							p.get(p.size() - 1).vir_si = p.get(i).vir_si;
							p.get(p.size() - 1).vir_ei = p.get(i).vir_ei;
							p.get(p.size() - 1).direction = p.get(i).direction;
							p.get(p.size() - 1).isalive = true;
							p.get(p.size() - 1).len = counter;
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
					}
				}
				/*if (map[p.get(i).vir_si*size + tmpj] != 0)//此处没必要要color
				{
					counter++;
				}
				tmpj++;*/
				
			}
			//p.get(i).len = counter;
			if (counter > 1)
			{
				if (first_save == false)
				{
					p.get(i).len = counter;
					p.get(i).vir_sj = tsj;
					p.get(i).vir_ej = nextsj;
					if (nextsj == size - 1 || (nextsj < size - 1 && map[p.get(i).vir_si*size + nextsj + 1] != 0))
					{
						p.get(i).isalive = false;
					}
					else
					{
						if (tsj == 0 || (tsj >= 0 && map[p.get(i).vir_si*size + tsj - 1] != 0))
						{
							p.get(i).isalive = false;
						}
						else{
							p.get(i).isalive = true;
						}
					}
				}
				else{
					p.add(new Sumforsearch());
					p.get(p.size() - 1).vir_sj = tsj;
					p.get(p.size() - 1).vir_ej = nextsj;
					p.get(p.size() - 1).vir_si = p.get(i).vir_si;
					p.get(p.size() - 1).vir_ei = p.get(i).vir_ei;
					p.get(p.size() - 1).direction = p.get(i).direction;
					if (nextsj == size-1 ||(nextsj<size-1&& map[p.get(i).vir_si*size + nextsj+1] != 0))
					{
						p.get(p.size() - 1).isalive = false;
					}
					else
					{
						p.get(p.size() - 1).isalive = true;
					}
					p.get(p.size() - 1).len = counter;
				}
			}
			
			break;
		case 2:counter = 0;
			tsi = p.get(i).vir_si;
			tei = p.get(i).vir_si;
			meet_space = false;
			find_next_s = false;
			nextsi = p.get(i).vir_si;
			first_save = false;
			circle_times = p.get(i).vir_ei;
			while (tei <= circle_times)
			{
				if (map[tei*size + p.get(i).vir_sj] != 0)//有子
				{
					counter++;
					if (find_next_s == false)//没找到开头
					{
						if (meet_space == false)//没遇到空格
						{
							nextsi = tei;
						}
						else{
							nextsi = tei;
							find_next_s = true;
						}

					}
					tei++;
				}
				else{//此时tej指向空格
					if (meet_space == false)
					{
						if (counter == 0)
						{
							while (tei <= circle_times&&map[p.get(i).vir_sj + tei*size] == 0)
							{
								tei++;
								tsi++;
							}
						}
						else
						{
							meet_space = true;
							tei++;
						}
					}
					else{
						if (counter == 1)
						{
							tsi++;
							tei = tsi;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
							continue;
						}
						if (first_save==false)
						{
							p.get(i).len = counter;
							p.get(i).vir_si = tsi;
							p.get(i).vir_ei = nextsi;
							if (tsi == 0 ||(tsi-1>=0&& map[(tsi-1)*size + p.get(i).vir_sj] != 0))
							{
								p.get(i).isalive = false;
							}
							else{
								p.get(i).isalive = true;
							}
							tsi = nextsi;
							tei = tsi;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
						else{
							p.add(new Sumforsearch());
							p.get(p.size() - 1).vir_sj = p.get(i).vir_sj;
							p.get(p.size() - 1).vir_ej = p.get(i).vir_ej;
							p.get(p.size() - 1).vir_si = tsi;
							p.get(p.size() - 1).vir_ei = nextsi;
							p.get(p.size() - 1).direction = p.get(i).direction;
							p.get(p.size() - 1).isalive = true;
							p.get(p.size() - 1).len = counter;
							tsi = nextsi;
							tei = tsi;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
					}
				}
				/*if (map[p.get(i).vir_si*size + tmpj] != 0)//此处没必要要color
				{
				counter++;
				}
				tmpj++;*/

			}
			//p.get(i).len = counter;
			if (counter > 1)
			{
				if (first_save == false)
				{
					p.get(i).len = counter;
					p.get(i).vir_si = tsi;
					p.get(i).vir_ei = nextsi;
					if (nextsi == size - 1 || (nextsi < size - 1 && map[p.get(i).vir_sj + (nextsi + 1)*size] != 0))
					{
						p.get(i).isalive = false;
					}
					else
					{
						if (tsi == 0 || (tsi - 1 >= 0 && map[(tsi - 1)*size + p.get(i).vir_sj] != 0))
						{
							p.get(i).isalive = false;
						}
						else{
							p.get(i).isalive = true;
						}
					}
				}
				else{
					p.add(new Sumforsearch());
					p.get(p.size() - 1).vir_sj = p.get(i).vir_sj;
					p.get(p.size() - 1).vir_ej = p.get(i).vir_ej;
					p.get(p.size() - 1).vir_si = tsi;
					p.get(p.size() - 1).vir_ei = nextsi;
					p.get(p.size() - 1).direction = p.get(i).direction;
					if (nextsi == size-1 || (nextsi<size-1&&map[p.get(i).vir_sj + (nextsi+1)*size] != 0))
					{
						p.get(p.size() - 1).isalive = false;
					}
					else
					{
						p.get(p.size() - 1).isalive = true;
					}
					p.get(p.size() - 1).len = counter;
				}
			}
			
			//........
			/*tmpi = p.get(i).vir_si, counter = 0;
			while (tmpi <= p.get(i).vir_ei)
			{
				if (map[tmpi*size + p.get(i).vir_sj] == 0)
				{
					counter++;
				}
				tmpi++;
			}
			p.get(i).len = counter;*/
			break;
		case 3://tmpi = p.get(i).vir_si, tmpj = p.get(i).vir_sj, counter = 0;
			counter = 0;
			tsi = p.get(i).vir_si;
			tei = p.get(i).vir_si;
			tsj = p.get(i).vir_sj;
			tej = p.get(i).vir_sj;
			meet_space = false;
			find_next_s = false;
			first_save = false;
			nextsj = p.get(i).vir_sj;
			nextsi = p.get(i).vir_si;
			circle_times = p.get(i).vir_ei;
			while (tei <= circle_times)
			{
				if (map[tei*size + tej] != 0)//有子
				{
					counter++;
					if (find_next_s == false)//没找到开头
					{
						if (meet_space == false)//没遇到空格
						{
							nextsi = tei;
							nextsj = tej;
						}
						else{
							nextsi = tei;
							nextsj = tej;
							find_next_s = true;
						}

					}
					tei++;
					tej++;
				}
				else{//此时tej指向空格
					if (meet_space == false)
					{
						if (counter == 0)
						{
							while (tei <= circle_times&&map[tei*size + tej] == 0)
							{
								tej++;
								tei++;
								tsi++;
								tsj++;
							}
						}
						else
						{
							meet_space = true;
							tei++;
							tej++;
						}
					}
					else{
						if (counter == 1)
						{
							tsi ++;
							tei = tsi;
							tsj ++;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true; 
							continue;
						}
						if (first_save == false)//
						{
							p.get(i).len = counter;
							p.get(i).vir_si = tsi;
							p.get(i).vir_sj = tsj;
							p.get(i).vir_ei = nextsi;
							p.get(i).vir_ej = nextsj;
							if (tsi == 0 ||tsj==0 || (tsi > 0&&tsj>0 && map[(tsi - 1)*size + tsj-1] != 0))//
							{
								p.get(i).isalive = false;
							}
							else{
								p.get(i).isalive = true;
							}
							tsi = nextsi;
							tei = tsi;
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
						else{
							p.add(new Sumforsearch());
							p.get(p.size() - 1).vir_sj = tsj;
							p.get(p.size() - 1).vir_ej = nextsj;
							p.get(p.size() - 1).vir_si = tsi;
							p.get(p.size() - 1).vir_ei = nextsi;
							p.get(p.size() - 1).direction = p.get(i).direction;
							p.get(p.size() - 1).isalive = true;
							p.get(p.size() - 1).len = counter;
							tsi = nextsi;
							tei = tsi;
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
					}
				}
			}
			if (counter > 1)//记录最后一个连棋，长度大于1才记录
			{
				if (first_save==false)//两坐标同时变化，判断一个就可以
				{
					p.get(i).len = counter;
					p.get(i).vir_sj = tsj;
					p.get(i).vir_si = tsi;
					p.get(i).vir_ej = nextsj;
					p.get(i).vir_ei = nextsi;
					if (nextsi == size - 1 || nextsj == size - 1 || (nextsi < size - 1 && nextsj < size - 1 && map[(nextsi + 1)*size + nextsj + 1] != 0))
					{
						p.get(i).isalive = false;
					}
					else
					{
						if (tsi == 0 || tsj == 0 || (tsi > 0 && tsj>0 && map[(tsi - 1)*size + tsj - 1] != 0))//
						{
							p.get(i).isalive = false;
						}
						else{
							p.get(i).isalive = true;
						}
					}
				}
				else{
					p.add(new Sumforsearch());
					p.get(p.size() - 1).vir_sj = tsj;
					p.get(p.size() - 1).vir_ej = nextsj;
					p.get(p.size() - 1).vir_si = tsi;
					p.get(p.size() - 1).vir_ei = nextsi;
					p.get(p.size() - 1).direction = p.get(i).direction;
					if (nextsi == size-1 || nextsj == size-1 ||(nextsi<size-1&&nextsj<size-1&& map[(nextsi+1)*size + nextsj+1] != 0))
					{
						p.get(p.size() - 1).isalive = false;
					}
					else
					{
						p.get(p.size() - 1).isalive = true;
					}
					p.get(p.size() - 1).len = counter;
				}
			}
			
			//.........
			/*while (tmpi <= p.get(i).vir_ei&&tmpj <= p.get(i).vir_ej)
			{
				if (map[tmpi*size + tmpj] != 0)
				{
					counter++;
				}
				
				tmpi++;
				tmpj++;
			}
			p.get(i).len = counter;*/
			break;
		case 4://tmpi = p.get(i).vir_si, tmpj = p.get(i).vir_sj, counter = 0;
			counter = 0;
			tsi = p.get(i).vir_si;
			tei = p.get(i).vir_si;
			tsj = p.get(i).vir_sj;
			tej = p.get(i).vir_sj;
			meet_space = false;
			find_next_s = false;
			first_save = false;
			nextsj = p.get(i).vir_sj;
			nextsi = p.get(i).vir_si;
			circle_times = p.get(i).vir_ej;
			while (tej <= circle_times)
			{
				if (map[tei*size + tej] != 0)//有子
				{
					counter++;
					if (find_next_s == false)//没找到开头
					{
						if (meet_space == false)//没遇到空格
						{
							nextsi = tei;
							nextsj = tej;
						}
						else{
							nextsi = tei;
							nextsj = tej;
							find_next_s = true;
						}

					}
					tei--;
					tej++;
				}
				else{//此时tej指向空格
					if (meet_space == false)
					{
						if (counter == 0)
						{
							while (tej <= circle_times&&map[tei*size + tej] == 0)
							{
								tsi--;
								tsj++;
								tej++;
								tei--;
							}
						}
						else
						{
							meet_space = true;
							tei--;
							tej++;
						}
					}
					else{
						if (counter == 1)
						{
							tsi--;
							tei = tsi;
							tsj++;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
							continue;
						}
						if (first_save == false)//两坐标同时变化，判断一个就可以
						{
							p.get(i).len = counter;
							p.get(i).vir_si = tsi;
							p.get(i).vir_sj = tsj;
							p.get(i).vir_ei = nextsi;
							p.get(i).vir_ej = nextsj;
							if (tsi == size-1 || tsj == 0 || (tsi <size && tsj > 0 && map[(tsi+1)*size + tsj - 1] != 0))//
							{
								p.get(i).isalive = false;
							}
							else{
								p.get(i).isalive = true;
							}
							tsi = nextsi;
							tei = tsi;
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
						else{
							p.add(new Sumforsearch());
							p.get(p.size() - 1).vir_sj = tsj;
							p.get(p.size() - 1).vir_ej = nextsj;
							p.get(p.size() - 1).vir_si = tsi;
							p.get(p.size() - 1).vir_ei = nextsi;
							p.get(p.size() - 1).direction = p.get(i).direction;
							p.get(p.size() - 1).isalive = true;
							p.get(p.size() - 1).len = counter;
							tsi = nextsi;
							tei = tsi;
							tsj = nextsj;
							tej = tsj;
							meet_space = false;
							find_next_s = false;
							counter = 0;
							first_save = true;
						}
					}
				}
			}
			if (counter > 1)
			{
				if (first_save==false)//两坐标同时变化，判断一个就可以
				{
					p.get(i).len = counter;
					p.get(i).vir_sj = tsj;
					p.get(i).vir_si = tsi;
					p.get(i).vir_ej = nextsj;
					p.get(i).vir_ei = nextsi;
					if (nextsi == 0 || nextsj == size - 1 || (nextsi >= 1 && nextsj < size - 1 && map[(nextsi - 1)*size + nextsj + 1] != 0))
					{
						p.get(i).isalive = false;
					}
					else
					{
						if (tsi == size - 1 || tsj == 0 || (tsi <size && tsj > 0 && map[(tsi + 1)*size + tsj - 1] != 0))//
						{
							p.get(i).isalive = false;
						}
						else{
							p.get(i).isalive = true;
						}
					}
				}
				else{
					p.add(new Sumforsearch());
					p.get(p.size() - 1).vir_sj = tsj;
					p.get(p.size() - 1).vir_ej = nextsj;
					p.get(p.size() - 1).vir_si = tsi;
					p.get(p.size() - 1).vir_ei = nextsi;
					p.get(p.size() - 1).direction = p.get(i).direction;
					if (nextsi == 0 || nextsj == size-1 ||(nextsi>=1&&nextsj<size-1&& map[(nextsi-1)*size + nextsj+1] != 0))
					{
						p.get(p.size() - 1).isalive = false;
					}
					else
					{
						p.get(p.size() - 1).isalive = true;
					}
					p.get(p.size() - 1).len = counter;
				}
			}
			
			//..............................................................
			/*while (tmpi >= p.get(i).vir_ei&&tmpj <= p.get(i).vir_ej)
			{
				if (map[tmpi*size + tmpj] != 0)
				{
					counter++;
				}
				tmpi--;
				tmpj++;
			}
			p.get(i).len = counter;*/
			break;
		default:
			break;
		}
	}
	sum = p.size();//更新sum值
	//两两匹配，求交点
	for (i = 0; i < sum; i++)
	{
		for (j = i + 1; j < sum; j++)
		{
			int judge = is_crossing(p.get(i).vir_si, p.get(i).vir_sj, p.get(i).vir_ei, p.get(i).vir_ej, p.get(j).vir_si, p.get(j).vir_sj, p.get(j).vir_ei, p.get(j).vir_ej, map, p.get(i).direction, p.get(j).direction,color);
			if (judge == 0)
			{
				//无交点
			}
			else if (judge == 1)
			{
				//交点是实点
				switch (p.get(i).len)
				{
				case 2:
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive22++;
							}
							else{//zhenjia
								halfalive22++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive22++;
							}
							else{//jiajia
								halfdead22++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive23++;
							}
							else{//zhenjia
								halfalive23++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive23++;
							}
							else{//jiajia
								halfdead23++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive24++;
							}
							else{//zhenjia
								halfalive24++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
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
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive23++;
							}
							else{//zhenjia
								halfalive23++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive23++;
							}
							else{//jiajia
								halfdead23++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive33++;
							}
							else{//zhenjia
								halfalive33++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive33++;
							}
							else{//jiajia
								halfdead33++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive34++;
							}
							else{//zhenjia
								halfalive34++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
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
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive24++;
							}
							else{//zhenjia
								halfalive24++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive24++;
							}
							else{//jiajia
								halfdead24++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								alive34++;
							}
							else{//zhenjia
								halfalive34++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								halfalive34++;
							}
							else{//jiajia
								halfdead34++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
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
							if (p.get(j).isalive == true)//zhenjia
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
				switch (p.get(i).len)
				{
				case 2:
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive22++;
							}
							else{//zhenjia
								vir_halfalive22++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive22++;
							}
							else{//jiajia
								vir_halfdead22++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive23++;
							}
							else{//zhenjia
								vir_halfalive23++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive23++;
							}
							else{//jiajia
								vir_halfdead23++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive24++;
							}
							else{//zhenjia
								vir_halfalive24++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
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
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive23++;
							}
							else{//zhenjia
								vir_halfalive23++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive23++;
							}
							else{//jiajia
								vir_halfdead23++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive33++;
							}
							else{//zhenjia
								vir_halfalive33++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive33++;
							}
							else{//jiajia
								vir_halfdead33++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive34++;
							}
							else{//zhenjia
								vir_halfalive34++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
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
					if (p.get(j).len == 2)//pi =2 ;pj==2
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive24++;
							}
							else{//zhenjia
								vir_halfalive24++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive24++;
							}
							else{//jiajia
								vir_halfdead24++;
							}
						}
					}
					else if (p.get(j).len == 3)//pi 2 pj 3
					{
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive34++;
							}
							else{//zhenjia
								vir_halfalive34++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
							{
								vir_halfalive34++;
							}
							else{//jiajia
								vir_halfdead34++;
							}
						}
					}
					else {//p.get(j).len==4
						if (p.get(i).isalive == true)
						{
							if (p.get(j).isalive == true)//zhenzhen
							{
								vir_alive44++;
							}
							else{//zhenjia
								vir_halfalive44++;
							}
						}
						else
						{
							if (p.get(j).isalive == true)//zhenjia
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
	//free(p);
}
public int is_crossing(int si, int sj, int ei, int ej, int sx, int sy, int ex, int ey, int []map, int d1, int d2,int color)//0没有交点，1交点是实点，2交点是虚点
{
	int p;
	int x=0;
	int y=0;
	si = -si + 14;//转换坐标象限
	ei = -ei + 14;//转换坐标象限
	sx = -sx + 14;//转换坐标象限
	ex = -ex + 14;//转换坐标象限
	switch (d1)
	{
	case 1:switch (d2)
		{
			case 1:return 0; 
			case 2:x = si; y = sy; break;
			case 3:x = si; p = sx + sy; y = p - x; break;
			case 4:x = si; p = sx - sy; y = x - p; break;
			default:break;
		}
		break;
	case 2:switch (d2)
		{
			case 1:x = sx; y = sj; break;
			case 2:return 0; 
			case 3:y = sj; p = sx + sy; x = p - y; break;
			case 4:y = sj; p = sx - sy; x = y + p; break;
			default:break;
		}
		break;
	case 3:switch (d2)
		{
			case 1:x = sx; p = si + sj; y = p - x; break;
			case 2:y = sy; p = si + sj; x = p - y; break;
			case 3:return 0; 
			case 4:int q; p = si + sj; q = sx - sy; x = (p + q) / 2; y = (p - q) / 2; break;
			default:break;
		}
		break;
	case 4:switch (d2)
		{
			case 1:x = sx; p = si - sj; y = x - p; break;
			case 2:y = sy; p = si - sj; x = p + y; break;
			case 3:return 0; 
			case 4:int q; p = sx + sy; q = si - sj; x = (p + q) / 2; y = (p - q) / 2; break;
			default:break;
		}
		break;
	default:break;
	}
	//计算交点坐标完毕，将坐标象限转换回去：
	si = -si + 14;//转换坐标象限
	ei = -ei + 14;//转换坐标象限
	sx = -sx + 14;//转换坐标象限
	ex = -ex + 14;//转换坐标象限
	x = -x + 14;//转换坐标象限
	if (x >= 0 && x < size&&y >= 0 && y < size)//坐标合法，在棋盘内
	{
		int min_distance_a = min(max(Math.abs(x - si), Math.abs(y - sj)), max(Math.abs(x - ei), Math.abs(y - ej)));
		int min_distance_b = min(max(Math.abs(x - sx), Math.abs(y - sy)), max(Math.abs(x - ex), Math.abs(y - ey)));
		if (min_distance_a <=2&& min_distance_b <= 2)
		{
			if (map[x*size + y] == color)
			{
				return 1;
			}
			else if (map[x*size + y] == 0)
			{
				return 2;
			}
		}
	}
	return 0;
}
public int max(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}
public int min(int a, int b)
{
	if (a < b)
		return a;
	else return b;
}
public void clear()

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
public void input(float shuru[], int pyl)
//输入数组和偏移量
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
	shuru[12 + pyl] = (float)vir_halfdead22; shuru[13 + pyl] = (float)vir_halfdead23; shuru[14 + pyl] = (float)vir_halfdead24; shuru[size + pyl] = (float)vir_halfdead33; shuru[16 + pyl] = (float)vir_halfdead34; shuru[17 + pyl] = (float)vir_halfdead44;
	shuru[18 + pyl] = (float)vir_halfalive22; shuru[19 + pyl] = (float)vir_halfalive23; shuru[20 + pyl] = (float)vir_halfalive24; shuru[21 + pyl] = (float)vir_halfalive33; shuru[22 + pyl] = (float)vir_halfalive34; shuru[23 + pyl] = (float)vir_halfalive44;
	shuru[24 + pyl] = (float)vir_alive22; shuru[25 + pyl] = (float)vir_alive23; shuru[26 + pyl] = (float)vir_alive24; shuru[27 + pyl] = (float)vir_alive33; shuru[28 + pyl] = (float)vir_alive34; shuru[29 + pyl] = (float)vir_alive44;
	shuru[30 + pyl] = (float)halfdead22; shuru[31 + pyl] = (float)halfdead23; shuru[32 + pyl] = (float)halfdead24; shuru[33 + pyl] = (float)halfdead33; shuru[34 + pyl] = (float)halfdead34; shuru[35 + pyl] = (float)halfdead44;
	shuru[36 + pyl] = (float)halfalive22; shuru[37 + pyl] = (float)halfalive23; shuru[38 + pyl] = (float)halfalive24; shuru[39 + pyl] = (float)halfalive33; shuru[40 + pyl] = (float)halfalive34; shuru[41 + pyl] = (float)halfalive44;
	shuru[42 + pyl] = (float)alive22; shuru[43 + pyl] = (float)alive23; shuru[44 + pyl] = (float)alive24; shuru[45 + pyl] = (float)alive33; shuru[46 + pyl] = (float)alive34; shuru[47 + pyl] = (float)alive44;
}
};
