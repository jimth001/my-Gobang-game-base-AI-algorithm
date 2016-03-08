/*class GobangGame
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
void save()
{
myAI.saveWeight(quanzhi_src);
}
};
void BP_learn(){
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
}*/
/*void pvc()//人机对弈
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
ga->save();
delete ga;
}

}*/


/*void printArray(int *inputarray)
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
}*/