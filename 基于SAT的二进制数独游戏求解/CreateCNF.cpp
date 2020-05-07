#include"head.h"


status CreateAdjacencyList(char* filename, CNF& F)
{
	char s[4];	int i = 0, j = 0, k = 0;/*计数器*/	int a = 0, n[50] = { 0 }, * Cla = NULL; FILE* fp = NULL;

	if ((fp = fopen(filename, "r")) == NULL)//如果filename文件打开失败
	{
		return ERROR;
	}

	for (; s[0] != 'p'; fscanf(fp, "%c", &s[0]));//逐个读取文件中的元素，直到遇到以p为开始的正文

	fscanf(fp, "%s", s);
	if (s[0] == 'c' && s[1] == 'n' && s[2] == 'f')//若是cnf文件
	{
		fscanf(fp, "%d", &F.LitNum);
		fscanf(fp, "%d", &F.ClaNum);
		if (!(F.Letters = (LitList)calloc(2 * F.LitNum + 1, sizeof(Litnode))))//动态分配数组
		{
			exit(OVERFLOW);
		}
		for (i = 0; i < F.ClaNum; i++)//循环输入第i个子句
		{
			j = 0;//初始化计数器
			fscanf(fp, "%d", &a);
			while (a != 0)//逐个录入每个子句的文字
			{
				n[j] = a;
				j++;//统计每个子句的文字个数
				fscanf(fp, "%d", &a);
			}
			if (!(Cla = (int*)calloc(j + 1, sizeof(int))))//动态分配数组
			{
				exit(OVERFLOW);
			}
			Cla[0] = j;//将标志位设置为子句长度，大于0表明则该子句存在
			for (k = 0; k < j; k++)//将保存好的数放在动态数组中
			{
				Cla[k + 1] = n[k];
			}
			for (k = 1; k < j + 1; k++)//构建每个文字的邻接表
			{
				ClaNode* L;//创建新的结点，方便插入
				if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
				{
					exit(OVERFLOW);
				}
				L->clause = Cla;
				L->ClaNum = Cla[0];
				if (Cla[k] > 0 && NotSameNum(Cla, k))//若该文字为正文字
				{
					L->NextCla = F.Letters[Cla[k]].FirstCla;
					F.Letters[Cla[k]].FirstCla = L;
				}
				else if (Cla[k] < 0 && NotSameNum(Cla, k))//若为负文字
				{
					L->NextCla = F.Letters[F.LitNum - Cla[k]].FirstCla;
					F.Letters[F.LitNum - Cla[k]].FirstCla = L;
				}
			}
		}
		for (i = 1; i <= 2 * F.LitNum; i++)
		{
			F.Letters[i].value = Undefine;
		}
		return OK;
	}
	else
	{
		return ERROR;//不是cnf文件，创建失败
	}
}