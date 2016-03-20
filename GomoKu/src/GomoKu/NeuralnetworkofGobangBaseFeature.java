package GomoKu;


public class NeuralnetworkofGobangBaseFeature {
	final public int size=15;
	final public int firstlayernode=96;
	final public int secondlayernode=96;
	public float shuru[];
	public float yinhanceng1[];
	public float shuchu;
	public float quanzhi1[][];
	public float quanzhi2[];
	public float learnrate;
	public Feature wofangf = new Feature(), duifangf = new Feature();
	//method:
public float getshuchu()
	{
		return shuchu;
	}
public void getshuru(int []map)
{
	wofangf.clear();
	duifangf.clear();
	wofangf.heiOrbai_extractfeature(map, size, 1);//前48个是我方特征
	wofangf.extend_feature(map, size, 1);
	wofangf.search_nodes(map, size,1);
	wofangf.input(shuru, 0);
	duifangf.heiOrbai_extractfeature(map, size, -1);
	duifangf.extend_feature(map, size, -1);
	duifangf.search_nodes(map, size,-1);
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
public void cal_shuchu()

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
public void feedback(float goal)

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
public NeuralnetworkofGobangBaseFeature()
{
	quanzhi1=new float[firstlayernode][secondlayernode];
	quanzhi2=new float[secondlayernode];
	shuru=new float[firstlayernode];
	yinhanceng1=new float[secondlayernode];
	int i, j;
	for (i = 0; i < 96; i++)
	{
		for (j = 0; j < 48; j++)
		{
			if (i < 48)
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

public NeuralnetworkofGobangBaseFeature(float tmp1[][], float tmp2[])
{
	quanzhi1=new float[firstlayernode][secondlayernode];
	quanzhi2=new float[secondlayernode];
	shuru=new float[firstlayernode];
	yinhanceng1=new float[secondlayernode];
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
public void TD_study(int step[][], int stepnum, boolean iswin)
{//最后一步不学习，含5个子的都不学习
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
		//writeMapIntoTXT(step[stepnum]);
		getshuru(step[stepnum]);
		cal_shuchu();
		feedback(expectedvalue);
		cal_shuchu();
		expectedvalue = shuchu;
		stepnum--;
	}
}
void writeMapIntoTXT(int step[])
{
	
	/*int k;
	for (k = 0; k < size*size; k++){
		write << inputarray[k];
		write << std::endl;
	}
	write.close();*/
}
}
