#ifdef  _DLL_Gobang_AI_API
#define DLL_Gobang_AI_API  _declspec(dllimport) 
#else
#define DLL_Gobang_AI_API  _declspec(dllexport)
#endif

#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
extern int tmpcounter ;
static const int size = 15;
static const char * input_src = "e:\\input.txt";
static const char * quanzhi_src = "e:\\quanzhi.txt";
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
void writeMapIntoTXT(int *inputarray, const char *src = input_src);
typedef class AIforGobangGame AI;
extern "C"  DLL_Gobang_AI_API void  test();
extern "C"  DLL_Gobang_AI_API AI*  createInstanceOfAI(int status, int turn, const char * src);
class DLL_Gobang_AI_API feature{//描述一方的特征。整盘棋需要两个描述对象。
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
	float willwin(bool isyourturn);
	feature();
	bool vaild_ij_check(int t);
	void heiOrbai_extractfeature(int *map, int size, int color);
	void extend_feature(int *map, int size, int color);
	void search_nodes(int *map, int size);
	int is_crossing(int si, int sj, int ei, int ej, int sx, int sy, int ex, int ey, int *map, int d1, int d2);
	int max(int a, int b);
	void clear();
	void input(float shuru[], int pyl);
};
class DLL_Gobang_AI_API neuralnetworkofGobangBaseFeature{
public:
	float shuru[96];
	float yinhanceng1[48];
	float shuchu;
	float quanzhi1[96][48];
	float quanzhi2[48];
	float learnrate;
	feature wofangf = feature(), duifangf = feature();
	float getshuchu();
	void getshuru(int  *map);
	void cal_shuchu();
	void feedback(float goal);
	neuralnetworkofGobangBaseFeature();
	neuralnetworkofGobangBaseFeature(float tmp1[96][48], float tmp2[48]);
	void TD_study(int **step, int stepnum, bool iswin);
};
class DLL_Gobang_AI_API player{
public:int mystatus;//身份，黑棋还是白棋
	   int myid;//id为0代表己方，为1代表对手
	   static const int computer = 0;
	   static const int person = 1;
	   int cmdi;//用于记录搜索结果，除非局面为必输，否则一定会更新
	   int cmdj;//用于记录搜索结果，若局面为必输，则cmdi，cmdj不更新，维持上次决策值不变。此时需要下一个子，这个子由search中引用的参数x，y决定
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
	   player();
	   player(int sta, int id);
	   float valuefunc(int *p, int &x, int &y, neuralnetworkofGobangBaseFeature & net);
	   float max(float a, float b);
	   float min(float a, float b);
	   int judge(int *tmap, int &x, int &y, int lenlian);
	   float search(int *p, int &ix, int &jy, int depth, int depthlimit, float rootvalue, neuralnetworkofGobangBaseFeature & net, int x_first_search_node = size / 2, int y_first_search_node = size / 2);
	   void computermakecmd(int *map, int &i, int &j, neuralnetworkofGobangBaseFeature & net);
	   void setmyid(int id);
};
class DLL_Gobang_AI_API AIforGobangGame
{
private:
	int myStatus;
	int *stepmap[size*size];
	int step;
	player p;
	neuralnetworkofGobangBaseFeature mynet;
	bool iswin;
	int judge_result(int *map);
	void record(int *map);
public:
	//常量部分：
	static const int heiwin = 1;//黑赢
	static const int baiwin = -1;
	static const int drawgame = 0;//平局
	static const int notfinish = 9;//尚未结束
	static const int heizi = 1;
	static const int baizi = -1;
	static const int nilzi = 0;
	//
	int AIturn;
	void init();
	AIforGobangGame(int status, int turn, float qz1[96][48], float qz2[48]);
	AIforGobangGame(int status, int turn, neuralnetworkofGobangBaseFeature &net);
	AIforGobangGame(int status, int turn, const char * src);
	void makecmd(int *map, int &i, int &j);
	void saveWeight(const char * src);
	void judge_iswin(int winner);
	void TD_study();
	int judge(int *map);
};
