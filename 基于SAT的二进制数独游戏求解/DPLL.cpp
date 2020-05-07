#include"head.h"

extern int* VELUE;
extern int CHOOSE;

status DPLL(CNF F, int i)
{
	int j = 0, n = 0;	ClaNode* P = NULL;

	while (i)//单子句传播
	{
		BCP(F, i);
		if (EmptyCNF(F))
		{
			VELUE = (int*)calloc(2 * F.LitNum + 1, sizeof(int));
			for (j = 1; j <= 2 * F.LitNum; j++)
			{
				VELUE[j] = F.Letters[j].value;
			}
			return TRUE;
		}
		else if (EmptyCla(F, i))
		{
			return FALSE;
		}
		i = ExistSingle(F);//重新查找单子句
	}//while

	int v = 0;	CNF S;

	switch (CHOOSE)
	{
	case 1:
		v = Choose_1(F);//第一个选取策略
		break;
	case 2:
		v = Choose_2(F);//第二个选取策略
		break;
	default:
		break;
	}
	Copy(S, F);//保存当前公式副本
	if (DPLL(F, v))//在第一分支中搜索 
	{
		DeleteCNF(S);;//删除副本公式集S
		return TRUE;
	}
	else
	{
		v = Opposite_SAT(F.LitNum, v);//取v的相反
		if (DPLL(S, v))//回溯到对v执行分支策略的初态进入另一分支
		{
			DeleteCNF(S);//删除副本公式集S
			return TRUE;
		}
		else
		{
			DeleteCNF(S);//删除副本公式集S
			return FALSE;
		}
	}
}

void BCP(CNF& F, int i)
{
	int j = 0, n = 0, OppNum = 0;	ClaNode* P = NULL;

	if (i < 0)
	{
		i = F.LitNum - i;
	}
	P = F.Letters[i].FirstCla;//P指向单子句文字的第一个子句结点
	F.Letters[i].value = TRUE;//单子句文字值为真
	if (i <= F.LitNum)//若为正文字
	{
		F.Letters[i + F.LitNum].value = FALSE;//单子句的负文字值为假
	}
	else//若为负文字
	{
		F.Letters[i - F.LitNum].value = FALSE;//单子句的正文字值为假
	}
	while (P != NULL)//当子句不为空时 
	{
		P->clause[0] = DELETE;//删除包含该文字的子句
		P = P->NextCla;
	}
	if (i <= F.LitNum)//若该文字为正文字
	{
		P = F.Letters[i + F.LitNum].FirstCla;//令P为该文字的负文字的第一个子句
		while (P != NULL)
		{
			for (j = 1, n = 0; j <= P->clause[0]; j++)//逐个遍历该子句
			{
				if (P->clause[j] == -i) //找到该负文字
				{
					P->clause[j] = 0;//删除
					n += 1;//记录要删除的文字数目
				}
				else if (P->clause[j] == 0)//如果已经被删除
				{
					P->clause[0] += 1;//则总数加一
					n += 1;//待删除数加一
				}
			}
			P->clause[0] -= n;//将子句中的文字数目进行更改
			P = P->NextCla;
		}
	}
	else//若该文字为负文字
	{
		P = F.Letters[i - F.LitNum].FirstCla;//令P为该文字的正文字的第一个子句
		while (P != NULL) {
			for (j = 1, n = 0; j <= P->clause[0]; j++)//逐个遍历该子句
			{
				if (P->clause[j] == i - F.LitNum)//找到该正文字
				{
					P->clause[j] = 0;//删除
					n += 1; //记录要删除的文字数目
				}
				else if (P->clause[j] == 0)//如果已经被删除
				{
					P->clause[0] += 1;//则总数加一
					n += 1;//待删除数加一
				}
			}
			P->clause[0] -= n;//将子句中的文字数目进行更改
			P = P->NextCla;
		}
	}
}

status ExistSingle(CNF F)
{
	int i = 0, j = 0;	ClaNode* P = NULL;

	for (i = 1; i <= 2 * F.LitNum; i++)//逐个遍历每个文字的邻接链表
	{
		if (F.Letters[i].value == Undefine)
		{
			P = F.Letters[i].FirstCla;//P指向当前文字的第一个子句结点
			while (P != NULL)//当该子句存在时
			{
				if (P->clause[0] == 1)//当找到单子句时
				{
					return i;//返回该单子句
				}
				P = P->NextCla;//查询下一个子句
			}
		}
	}
	return FALSE;//没有单子句则返回FALSE
}

status EmptyCNF(CNF F)
{
	int i = 0;	ClaNode* P = NULL;

	for (i = 1; i <= 2 * F.LitNum; i++)//逐个遍历每个文字的邻接链表
	{
		if (F.Letters[i].value != TRUE)
		{
			P = F.Letters[i].FirstCla;//P指向当前文字的第一个子句结点
			while (P != NULL)//若当前子句不为空
			{
				if (P->clause[0] >= 0)//且没有被删除或为空子句
				{
					return FALSE;//则当前公式不为空，返回FAlSE
				}
				P = P->NextCla;
			}
		}
	}
	return TRUE;
}

status EmptyCla(CNF F, int Key)
{
	int i = 0, j = 0, n = 0;	ClaNode* P = NULL;

	Key = Opposite_SAT(F.LitNum, Key);
	P = F.Letters[Key].FirstCla;//P指向当前文字的第一个子句结点
	while (P != NULL)//若当前子句不为空
	{
		if (P->clause[0] == 0)//若是空子句
		{
			return TRUE;//则找到空子句，返回TRUE
		}
		P = P->NextCla;
	}
	return FALSE;
}

void DeleteCNF(CNF& F)
{
	int i = 0, j = 0, n = 0, ** T = NULL;	ClaNode* P = NULL, * Q = NULL, * R = NULL, * S = NULL;

	if (!(T = (int**)calloc(F.ClaNum, sizeof(int*))))//动态分配数组
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * F.LitNum; i++)//逐个收集每个子句空间的地址
	{
		P = F.Letters[i].FirstCla;//指向文字链表的第一个结点
		while (P != NULL)//当结点存在时
		{
			P->clause[0] = 1;
			P = P->NextCla;
		}
	}
	for (i = 1, n = 0; i <= 2 * F.LitNum; i++)//逐个收集每个子句空间的地址
	{
		P = F.Letters[i].FirstCla;//指向文字链表的第一个结点
		while (P != NULL)//当结点存在时
		{
			if (P->clause[0] != DELETE)
			{
				T[n] = P->clause;//将存储空间的指针放入数组中保存
				P->clause[0] = DELETE;//利用标志位确定是否被统计过
				n++;
			}
			P = P->NextCla;
		}
	}
	for (n = 0; n < F.ClaNum; n++)//循环释放所有子句的存储空间
	{
		free(T[n]);
	}
	free(T);//释放指针数组
	for (i = 1; i <= 2 * F.LitNum; i++)//删除全部文字链表
	{
		P = F.Letters[i].FirstCla;//指向文字链表的第一个结点
		while (P != NULL)//当结点存在时
		{
			Q = P->NextCla;
			free(P);
			P = Q;
		}
	}
	free(F.Letters);
	F.Letters = NULL;
	F.ClaNum = 0;
	F.LitNum = 0;
}

void Copy(CNF& S, CNF F)/*感觉这里有问题*/
{
	int i = 0, j = 0, k = 0, num = 0, Num = 0, * Cla = NULL;	ClaNode* P = NULL;

	S.LitNum = F.LitNum;//复制文字数目
	if (!(S.Letters = (LitList)calloc(2 * S.LitNum + 1, sizeof(Litnode))))//动态分配数组
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * S.LitNum; i++)//将F的每个文字的真值复制
	{
		S.Letters[i].value = F.Letters[i].value;
		S.Letters[i].FirstCla = NULL;
	}
	for (i = 1; i <= 2 * S.LitNum; i++)
	{
		if (F.Letters[i].value == Undefine)
		{
			Num = 0;
			P = F.Letters[i].FirstCla;
			while (P != NULL)
			{
				if (P->clause[0] > 0)//当公式F的第i个文字的子句没有被删除且不为空,并且没有被输出
				{
					Num += 1;
					if (i == MinNum(P->clause, F.LitNum))
					{
						if (!(Cla = (int*)calloc(P->clause[0] + 1, sizeof(int))))//动态分配数组
						{
							exit(OVERFLOW);
						}
						Cla[0] = P->clause[0];
						for (j = 1, k = 1; k <= P->clause[0]; j++)//逐个输出子句内元素
						{
							if (P->clause[j] != 0)
							{
								Cla[k] = P->clause[j];
								k++;
							}
						}
						for (k = 1; k <= Cla[0]; k++)//构建每个文字的邻接表
						{
							ClaNode* L;//创建新的结点，方便插入
							if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
							{
								exit(OVERFLOW);
							}
							L->clause = Cla;
							L->ClaNum = P->ClaNum;//复制子句中文字的数目
							if (Cla[k] > 0 && NotSameNum(Cla, k))//若该文字为正文字
							{
								L->NextCla = S.Letters[Cla[k]].FirstCla;
								S.Letters[Cla[k]].FirstCla = L;
							}
							else if (Cla[k] < 0 && NotSameNum(Cla, k))//若为负文字
							{
								L->NextCla = S.Letters[S.LitNum - Cla[k]].FirstCla;
								S.Letters[S.LitNum - Cla[k]].FirstCla = L;
							}
						}
						num += 1;//统计子句数目
					}
				}
				P = P->NextCla;
			}
		}
		S.ClaNum = num;//子句数目
	}
}

int MinNum(int* N, int m)
{
	int i = 0, j = 0, * Num = NULL;
	if (!(Num = (int*)calloc(N[0], sizeof(int))))//动态分配数组
	{
		exit(OVERFLOW);
	}
	for (i = 1, j = 0; j < N[0]; i++)
	{
		if (N[i] < 0)
		{
			Num[j] = m - N[i];
			j++;
		}
		else if (N[i] > 0)
		{
			Num[j] = N[i];
			j++;
		}
	}
	for (i = 1, j = Num[0]; i < N[0]; i++)
	{
		if (j > Num[i])
		{
			j = Num[i];
		}
	}
	free(Num);
	return j;
}