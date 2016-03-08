#include "DllGobangAI.h"
void writeMapIntoTXT(int *inputarray, const char *src)//将inputarray数组写到路径为src的txt中
{
	std::fstream write;
	write.open(src, std::fstream::out | std::ios::app);
	int k;
	for (k = 0; k < size*size; k++){
		write << inputarray[k];
		write << std::endl;
	}
	write.close();
}