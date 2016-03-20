package GomoKu;
class Result{
	int x;int y;
	public Result()
	{
		x=0;y=0;
	}
	public void set(int i,int j)
	{
		x=i;
		y=j;
	}
	public int getx()
	{
		return x;
	}
	public int gety()
	{
		return y;
	}
}
public class AIforGobangGame {
final public int size=15;
private int myStatus;
private int stepmap[][][];
private int step[];
private Player p;
private NeuralnetworkofGobangBaseFeature mynet;
private boolean iswin;
private myIO myio;
private String encodingType;
int search_layer;
private int judge_result(int []map)//判断当前棋局是baiwin还是heiwin还是尚未结束
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
private void record(int []map,int this_turn)//记录中己方子为1，不论黑白
//记录中己方子为1，不论黑白
	{
		//int *tmp = (int *)malloc(size*size*sizeof(int));//记录对手下完的局面
		int tmp[]=new int[size*size];
		int k;
		boolean is_init_map = true;//判断是否为初始局面。即无子状态。
		if (myStatus == Player.baistatus)//如果AI执白棋，记录棋局时先翻转
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
			//free(tmp);
		}
		else//不是初始局面，记录
		{
			stepmap[this_turn][step[this_turn]] = tmp;
			step[this_turn]++;
		}
	}
//常量部分：
public static final int heiwin = 1;//黑赢
public static final int baiwin = -1;
public static final int drawgame = 0;//平局
public static final int notfinish = 9;//尚未结束
public static final int heizi = 1;
public static final int baizi = -1;
public static final int nilzi = 0;
//method:
public int AIturn;
public void init()
{
	iswin = false;
	step[0]=0;step[1]=0;
}
public AIforGobangGame(int status, int turn, float qz1[][], float qz2[],String encode,int search_para)
{
	search_layer=search_para;
	encodingType=encode;
	myio=new myIO(1);
	stepmap=new int [2][size*size][size*size];
	myStatus = status;
	p = new Player(myStatus, 0,search_para);
	mynet = new NeuralnetworkofGobangBaseFeature(qz1, qz2);
	AIturn = turn;
	step = new int[2];
	step[0]=0;step[1]=0;
}
public AIforGobangGame(int status, int turn, NeuralnetworkofGobangBaseFeature net,String encode,int search_para)
{
	search_layer=search_para;
	encodingType=encode;
	myio=new myIO(1);
	stepmap=new int [2][size*size][size*size];
	myStatus = status;
	p = new Player(myStatus, 0,search_para);
	mynet = net;
	AIturn = turn;
	step = new int[2];
	step[0]=0;step[1]=0;
}
public AIforGobangGame(int status, int turn, String src,String encode,int search_para)//status是AI的状态，表示执白还是执黑，turn是轮到AI下的时候轮换变量应该等于的值。如果自己实现控制流程也可弃用此变量
//建议使用1和-1作为轮换变量，变更时*-1，1为黑，-1为白，初始为1
//status必须为1或-1，黑棋为1，白棋为-1
//src为权值文件路径，文件不存在时自动新建网络
{
	search_layer=search_para;
	stepmap=new int[2][size*size][size*size];
myStatus = status;
encodingType=encode;
p = new Player(myStatus, 0,search_para);
AIturn = turn;
step = new int[2];
step[0]=0;step[1]=0;
boolean isexist = false;
myio=new myIO(1);
isexist = myIO.isFileExist(src);

if (isexist == true)
{
	myio.startRead(src, encodingType, 0);
	float tmp1[][]=new float[96][48];
	float tmp2[]=new float [48];
	int i, j;
	for (i = 0; i < 96; i++)
	{
		for (j = 0; j < 48; j++)
		{
			tmp1[i][j]=Float.parseFloat(myio.readOneSentence(0));
		}
	}
	for (i = 0; i < 48; i++)
	{
		tmp2[i]=Float.parseFloat(myio.readOneSentence(0));
	}
	mynet =new NeuralnetworkofGobangBaseFeature(tmp1, tmp2);
	myio.endRead(0);
}
else{
	mynet =new NeuralnetworkofGobangBaseFeature();
}

}
public void makecmd(int []map, Result rst)//对方未成五子时才会调用，因此只会记录未成五子的棋局
{
	record(map,0);
	p.computermakecmd(map, rst, mynet);//i,j为做出的决策，不改变map
	map[rst.x*size + rst.y] = myStatus;//下了子之后的局面
	record(map, 1);//记录
	map[rst.x*size + rst.y] = 0;//还原map
}
public void saveWeight(String src)//导出权值
{
	myio.startWrite(src, encodingType, 0);
	int i, j;
	for (i = 0; i < 96; i++)
	{
		for (j = 0; j < 48; j++)
		{
			myio.writeOneString(String.valueOf(mynet.quanzhi1[i][j])+"\r\n", 0);
		}
	}
	for (i = 0; i < 48; i++)
	{
		myio.writeOneString(String.valueOf(mynet.quanzhi2[i])+"\r\n", 0);
	}
	myio.endWrite(0);
}
public void judge_iswin(int winner)//对iswin进行设置
{
	if (myStatus == winner)
	{
		iswin = true;
	}
	else{
		iswin = false;
	}
}
public void TD_study()
{
	mynet.TD_study(stepmap[(search_layer + 1) % 2], step[(search_layer + 1) % 2], iswin);//只记录了未成五子的棋局，因此没有step和step-1之分
}
public int judge(int []map)//判断棋局状态
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
}
