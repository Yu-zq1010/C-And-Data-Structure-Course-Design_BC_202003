#include"head.h"

extern int* VELUE;
extern int CHOOSE;
extern int ConflicCla[100];
extern int ConflicNum;
extern int* LearnCla[100];
extern int LearnNum;

status BetterDPLL(CNF& F, int i, int Deep)
{
	int j = 0, DifferenceDeep = 0;	ClaNode* P = NULL;

	while (i)//单子句传播
	{
		BetterBCP(F, i, Deep);//进行BCP过程
		if (EmptyCNF(F))
		{
			if (!(VELUE = (int*)calloc(2 * F.LitNum + 1, sizeof(int))))
			{
				exit(OVERFLOW);
			}
			for (j = 1; j <= 2 * F.LitNum; j++)
			{
				VELUE[j] = F.Letters[j].value;
			}
			return TRUE;
		}
		else if ((DifferenceDeep = BetterEmptyCla(F, i)) > 0)
		{
			return 1 - DifferenceDeep;
		}
		i = BetterExistSingle(F);//重新查找单子句
	}//while

	int v = 0, Difference = 0;	CNF S;

	AddLearnCla(F);//将学习子句添加到子句集中
	switch (CHOOSE)
	{
	case 1:
		v = Choose_1(F);//第一个选取策略
		break;
	case 2:
		v = Choose_2(F);//第二个选取策略
		if (v == 0)
		{
			exit(-5);
		}
		break;
	default:
		break;
	}

	BetterCopy(S, F);//保存当前公式副本
	if ((Difference = BetterDPLL(F, v, Deep + 1)) > 0)//在第一分支中搜索 
	{
		DeleteCNF(S);//删除副本公式集S
		return TRUE;
	}
	else
	{
		if (Difference != 0)
		{
			return Difference + 1;
		}
		else
		{
			v = Opposite_SAT(F.LitNum, v);//取v的相反
			AddLearnCla(S);
			if ((Difference = BetterDPLL(S, v, Deep + 1)) > 0)//回溯到对v执行分支策略的初态进入另一分支
			{
				DeleteCNF(S);//删除副本公式集S
				return TRUE;
			}
			else
			{
				DeleteCNF(S);//删除副本公式集S
				if (Difference == 0)
				{
					return Difference;
				}
				else
				{
					return Difference + 1;
				}
			}
		}
	}
}

void BetterBCP(CNF& F, int i, int Deep)
{
	int j = 0, n = 0, OppNum = 0;	ClaNode* P = NULL;

	P = F.Letters[i].FirstCla;//P指向单子句文字的第一个子句结点
	F.Letters[i].value = TRUE;//单子句文字值为真
	F.Letters[i].Deep = Deep;//当前决策深度
	while (P != NULL)//当子句不为空时 
	{
		P->clause[0] = DELETE;//删除包含该文字的子句
		P = P->NextCla;
	}
	OppNum = Opposite_SAT(F.LitNum, i);//取i的相反数
	F.Letters[OppNum].value = FALSE;//单子句的相反文字值为假
	F.Letters[OppNum].Deep = Deep;//当前决策深度
	P = F.Letters[OppNum].FirstCla;//令P为该文字的相反文字的第一个子句
	while (P != NULL)
	{
		if (P->clause[0] > 0)
		{
			for (j = 1, n = 0; j <= P->ClaNum; j++)//逐个遍历该子句
			{
				if (F.Letters[P->clause[j]].value == FALSE) //找到该相反文字
				{
					n += 1;//记录要删除的文字数目
				}
			}
			P->clause[0] = P->ClaNum - n;//将子句中的文字数目进行更改
		}
		P = P->NextCla;
	}
}

status BetterExistSingle(CNF F)
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
					if (P->ClaNum != 1)
					{
						F.Letters[i].CLA = P;
						F.Letters[Opposite_SAT(F.LitNum, i)].CLA = P;
					}
					return i;
				}
				P = P->NextCla;//查询下一个子句
			}
		}
	}
	return FALSE;//没有单子句则返回FALSE
}

status BetterEmptyCla(CNF F, int Key)
{
	ClaNode* P = NULL;	int Deep = 0, MaxDeep = 0, i = 0, j = 0, N[MaxLearnClaNum] = { 0 }, * Cla = NULL;

	Key = Opposite_SAT(F.LitNum, Key);
	P = F.Letters[Key].FirstCla;//P指向当前文字的第一个子句结点
	while (P != NULL)//若当前子句不为空
	{
		if (P->clause[0] == 0)//若是空子句
		{
			for (i = 0; i < 100; i++)
			{
				ConflicCla[i] = 0;
			}
			ConflicNum = 1;
			for (i = 1; i <= P->ClaNum; i++)
			{
				SearchConflic(F, P, P->clause[i]);//寻找蕴含图中的没有前驱的结点
			}
			for (i = 1, j = 0; i < ConflicNum && j < MaxLearnClaNum; i++)//只保存长度不大于10的学习子句
			{
				if (NotSameNum(ConflicCla, i) == TRUE)//排除重复的结点
				{
					if (F.Letters[ConflicCla[i]].value == TRUE)
					{
						ConflicCla[i] = Opposite_SAT(F.LitNum, ConflicCla[i]);
					}
					N[j] = ConflicCla[i];//保存在临时数组中
					j++;//统计学习子句的个数
				}
			}
			if (i == 100 || j == 0 || j == MaxLearnClaNum)
			{
				return TRUE;
			}

			if (!(Cla = (int*)calloc(j + 1, sizeof(int))))//申请空间
			{
				exit(OVERFLOW);
			}
			Cla[0] = j;
			for (i = 1; i <= j; i++)
			{
				Cla[i] = N[i - 1];//将学习到的子句保存在数组中
			}
			for (i = 1, MaxDeep = 0; i <= Cla[0]; i++)//统计学习子句中最大的层数
			{
				if (F.Letters[Cla[i]].Deep > MaxDeep)
				{
					MaxDeep = F.Letters[Cla[i]].Deep;
				}
			}
			Deep = F.Letters[Key].Deep - MaxDeep;//计算与当前的层数差
			LearnCla[LearnNum % 100] = Cla;//将学习到的子句保存在整个学习子句库中
			LearnNum++;
			return Deep + 1;//返回深度差
		}
		P = P->NextCla;
	}
	return FALSE;
}

void BetterCopy(CNF& S, CNF F)
{
	int i = 0, j = 0, k = 0, num = 0, Num = 0, * Cla = NULL;	ClaNode* P = NULL;

	S.LitNum = F.LitNum;//复制文字数目
	if (!(S.Letters = (LitList)calloc(2 * S.LitNum + 1, sizeof(Litnode))))//动态分配数组
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * S.LitNum; i++)//复制每个文字的信息
	{
		S.Letters[i].value = F.Letters[i].value;
		S.Letters[i].Deep = F.Letters[i].Deep;
		S.Letters[i].CLA = F.Letters[i].CLA;
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
				if (P->clause[0] > 0)
				{
					Num += 1;
					if (i == BetterMinNum(F, P->ClaNum, P->clause))//当公式F的第i个文字的子句没有被删除且不为空,并且没有被输出
					{
						if (!(Cla = (int*)calloc(P->ClaNum + 1, sizeof(int))))//动态分配数组
						{
							exit(OVERFLOW);
						}
						for (j = 0; j <= P->ClaNum; j++)//逐个输出子句内元素
						{
							Cla[j] = P->clause[j];
						}
						for (k = 1; k <= P->ClaNum; k++)//构建每个文字的邻接表
						{
							if (F.Letters[Cla[k]].value != FALSE)
							{
								ClaNode* L;//创建新的结点，方便插入

								if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
								{
									exit(OVERFLOW);
								}
								L->clause = Cla;
								L->ClaNum = P->ClaNum;//复制子句中文字的数目
								if (NotSameNum(Cla, k))//若该文字为正文字
								{
									L->NextCla = S.Letters[Cla[k]].FirstCla;
									S.Letters[Cla[k]].FirstCla = L;
								}
							}
						}
						num += 1;//统计子句数目
					}
				}
				P = P->NextCla;
			}
		}
	}
	S.ClaNum = num;//子句数目
}

void SearchConflic(CNF F, ClaNode* P, int key)
{
	int i = 0;

	for (i = 1; i <= P->ClaNum; i++)
	{
		if (P->clause[i] != key && ConflicNum < 100 && P->ClaNum != 1)
		{
			if (F.Letters[P->clause[i]].CLA == NULL)
			{
				ConflicCla[ConflicNum] = P->clause[i];
				ConflicNum++;
			}
			else
			{
				SearchConflic(F, F.Letters[P->clause[i]].CLA, Opposite_SAT(F.LitNum, P->clause[i]));
			}
		}
	}
}

void AddLearnCla(CNF& F)
{
	int i = 0, j = 0, n = 0, * Cla = NULL, * P = NULL;	ClaNode* N = NULL;

	for (i = 0; i < 100; i++)
	{
		if (LearnCla[i] != NULL)//当前学习子句存在
		{
			P = LearnCla[i];
			n++;//子句数加一
			if (!(Cla = (int*)calloc(P[0] + 1, sizeof(int))))//分配空间
			{
				exit(OVERFLOW);
			}

			for (j = 0; j <= P[0]; j++)//将学习字句复制
			{
				Cla[j] = P[j];
			}

			for (j = 1; j <= P[0]; j++)
			{
				if (F.Letters[Cla[j]].value == TRUE)//如果在子句中有已经判断为真
				{
					Cla[0] = DELETE;//将子句删除
					break;
				}
				else if (F.Letters[Cla[j]].value == FALSE)//若为假
				{
					Cla[0] -= 1;//子句中文字数减一
				}
			}
			for (j = 1; j <= P[0]; j++)
			{
				if (!(N = (ClaNode*)malloc(sizeof(ClaNode))))
				{
					exit(OVERFLOW);
				}

				N->ClaNum = P[0];
				N->clause = Cla;
				N->NextCla = F.Letters[Cla[j]].FirstCla;
				F.Letters[Cla[j]].FirstCla = N;
			}
		}
		F.ClaNum += n;//将子句数添加
	}
}

status NotSameCla(ClaNode* P, ClaNode* N)
{
	int i = 0;

	while (P != NULL)
	{
		if (P->ClaNum != N->ClaNum)
		{
			P = P->NextCla;
			continue;
		}
		else
		{
			for (i = 1; i <= P->ClaNum; i++)
			{
				if (P->clause[i] != N->clause[i])
				{
					break;
				}
			}
			if (i > P->ClaNum)
			{
				return FALSE;
			}
		}
		P = P->NextCla;
	}
	return TRUE;
}

int BetterMinNum(CNF F, int ClaNum, int* N)
{
	int i = 0, j = 0;

	for (i = 1, j = 1000000; i <= ClaNum; i++)
	{
		if (j > N[i] && F.Letters[N[i]].value != FALSE)
		{
			j = N[i];
		}
	}
	return j;
}