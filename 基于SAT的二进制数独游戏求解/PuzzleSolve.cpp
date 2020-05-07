#include"head.h"

CNF F, S;

extern int CHOOSE;
extern int ConflicCla[100];
extern int ConflicNum;
extern int* LearnCla[100];
extern int LearnNum;
extern int* VELUE;

extern int Order;
int* Subset = NULL;
int ClaNumber = 0;

int** Prepare()//准备，填充一个目标二维数组
{
	int** B = NULL, i = 0, j = 0;

	ClaNumber = 0;
	if (!(B = (int**)calloc(Order + 1, sizeof(int*))))//申请空间
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= Order; i++)//逐个申请空间
	{
		if (!(B[i] = (int*)calloc(Order + 1, sizeof(int))))
		{
			exit(OVERFLOW);
		}
		for (j = 1; j <= Order; j++)//填充数据
		{
			B[i][j] = i * 10 + j;
		}
	}
	return B;
}

void Constraint_1(SATFormula& Formula, int** B)//约束1
{
	int i = 0, j = 0, k = 0; P_ClauseList P = NULL;

	//行输入
	for (i = 1; i <= Order; i++)
	{
		for (j = 1; j <= Order - 2; j++)
		{
			//正输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			for (k = 0; k < 3; k++)
			{
				P->ClauseValue[k] = B[i][j + k];
			}
			P->ClauseValue[k] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			//负输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			for (k = 0; k < 3; k++)
			{
				P->ClauseValue[k] = -B[i][j + k];
			}
			P->ClauseValue[k] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;
		}
	}

	//列输入
	for (j = 1; j <= Order; j++)
	{
		for (i = 1; i <= Order - 2; i++)
		{
			//正输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			for (k = 0; k < 3; k++)
			{
				P->ClauseValue[k] = B[i + k][j];
			}
			P->ClauseValue[k] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			//负输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			for (k = 0; k < 3; k++)
			{
				P->ClauseValue[k] = -B[i + k][j];
			}
			P->ClauseValue[k] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;
		}
	}
	Formula.ClaNum = ClaNumber;
}

void Constraint_2(SATFormula& Formula, int** B)//约束2
{
	int i = 0, j = 0;	P_ClauseList P = NULL;	void (*Print)(int* Subset, SATFormula & Formula);

	if (Order == 4)
	{
		//行输入
		for (i = 1; i <= Order; i++)
		{
			//正输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = B[i][1];
			P->ClauseValue[1] = B[i][2];
			P->ClauseValue[2] = B[i][4];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = B[i][1];
			P->ClauseValue[1] = B[i][3];
			P->ClauseValue[2] = B[i][4];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			//负输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = -B[i][1];
			P->ClauseValue[1] = -B[i][2];
			P->ClauseValue[2] = -B[i][4];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = -B[i][1];
			P->ClauseValue[1] = -B[i][3];
			P->ClauseValue[2] = -B[i][4];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;
		}

		//列输入
		for (i = 1; i <= Order; i++)
		{
			//正输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = B[1][i];
			P->ClauseValue[1] = B[2][i];
			P->ClauseValue[2] = B[4][i];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = B[1][i];
			P->ClauseValue[1] = B[3][i];
			P->ClauseValue[2] = B[4][i];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			//负输入
			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = -B[1][i];
			P->ClauseValue[1] = -B[2][i];
			P->ClauseValue[2] = -B[4][i];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;

			if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
			{
				exit(OVERFLOW);
			}
			P->ClauseValue[0] = -B[1][i];
			P->ClauseValue[1] = -B[3][i];
			P->ClauseValue[2] = -B[4][i];
			P->ClauseValue[3] = 0;
			P->NextClause = Formula.FirstClause;
			Formula.FirstClause = P;
			ClaNumber++;
		}
		Formula.ClaNum = ClaNumber;
	}
	else
	{
		Print = Print_AddCla;//函数指针赋值
		if (!(Subset = (int*)calloc(Order / 2 + 1, sizeof(int))))
		{
			exit(OVERFLOW);
		}
		for (i = 1; i <= Order; i++)
		{
			Combine(B[i], Order, Order / 2 + 1, Formula, Print);//进行组合函数选取，用鸽巢原理选取
		}
		Formula.ClaNum = ClaNumber;//输入当前子句值
		free(Subset);//释放存储空间
		Subset = NULL;
	}
}

void Constraint_3(SATFormula& Formula, int** B)//约束3
{
	int i = 0, j = 0, k = 0, n = 0, t = 0, o = 0, num = 0;

	if (!(Subset = (int*)calloc(Order + 1, sizeof(int))))
	{
		exit(OVERFLOW);
	}
	for (i = 1; i < 3; i++)//列或行
	{
		for (j = 1; j < Order; j++)//第一个数值
		{
			for (k = j + 1; k <= Order; k++)//第二个数值
			{
				n = i * 100 + j * 10 + k;

				//转换157= -[1571,1572,…,1578]
				Subset[0] = -n;//选取约束三中（-157,-1571,-1572,…,-1578）子句
				for (num = 1; num <= Order; num++)
				{
					Subset[num] = -(n * 10 + num);
				}
				AddClause(Subset, num, Formula);//添加该子句

				Subset[0] = n;//选取约束三中（1571,157）,（1572,157）…（1578,157）
				for (num = 1; num <= Order; num++)
				{
					Subset[1] = (n * 10 + num);
					AddClause(Subset, 2, Formula);//添加该子句
				}

				//转换15711= 51,71和15710= -51,-71和1571= 15711,15710
				for (num = 1; num <= Order; num++)//从1到8
				{
					//转化1571= 15711,15710
					Subset[0] = -(n * 10 + num);//-1571
					Subset[1] = (n * 100 + num * 10 + 1);//15711
					Subset[2] = (n * 100 + num * 10 + 0);//15710
					AddClause(Subset, 3, Formula);//添加1571，15711，15710
					for (t = 0; t < 3; t++)
					{
						Subset[t] = -Subset[t];//使子句数组中元素值值翻转
					}
					AddClause(Subset, 2, Formula);//添加该子句1571，-15711
					Subset[1] = Subset[2];//将-71放在第二个
					AddClause(Subset, 2, Formula);//添加该子句1571，-15710

					//转化15711= 51,71和15710= -51,-71
					for (o = 0; o < 2; o++)//o为最末位时0还是1
					{
						if (i == 1)//若为两行相比较
						{
							if (o == 0)//若为0
							{
								Subset[0] = (n * 100 + num * 10 + o);//15710
								Subset[1] = (j * 10 + num);//51
								Subset[2] = (k * 10 + num);//71
								AddClause(Subset, 3, Formula);//添加15710，51，71
							}
							else//若为1
							{
								Subset[0] = (n * 100 + num * 10 + o);//15711
								Subset[1] = -(j * 10 + num);//-51
								Subset[2] = -(k * 10 + num);//-71
								AddClause(Subset, 3, Formula);//添加该子句15711，-51，-71
							}
						}
						else//若为两列相比较
						{
							if (o == 0)//若为0
							{
								Subset[0] = (n * 100 + num * 10 + o);//25710
								Subset[1] = (num * 10 + j);//15
								Subset[2] = (num * 10 + k);//17
								AddClause(Subset, 3, Formula);//添加25710，15，17
							}
							else//若为1
							{
								Subset[0] = (n * 100 + num * 10 + o);//15711
								Subset[1] = -(num * 10 + j);//-15
								Subset[2] = -(num * 10 + k);//-17
								AddClause(Subset, 3, Formula);//添加该子句25711，-15，-17
							}
						}
						for (t = 0; t < 3; t++)
						{
							Subset[t] = -Subset[t];//使子句数组中元素值值翻转
						}
						AddClause(Subset, 2, Formula);//添加该子句-15710，-51
						Subset[1] = Subset[2];//将-71放在第二个
						AddClause(Subset, 2, Formula);//添加该子句-15710，-71
					}
				}
			}
		}
	}
	Formula.ClaNum = ClaNumber;//放入子句总数
	free(Subset);//释放存储空间
	Subset = NULL;
}

void Convert(SATFormula& Formula)
{
	int i = 0, j = 0, k = 0, n = 0, Basic = 0, SIGN = 0, RESULT = 6;	P_ClauseList P = NULL;

	if (!(Subset = (int*)calloc(7, sizeof(int))))
	{
		exit(OVERFLOW);
	}

	P = Formula.FirstClause;
	while (P != NULL)
	{
		for (i = 0;; i++)
		{
			n = P->ClauseValue[i];
			if (n == 0)//遇到了结束符号
			{
				break;
			}

			//判断正负
			if (n > 0)//想要转变的数大于0
			{
				Subset[SIGN] = 1;//符号位为正数
			}
			else//想要转变的数小于0
			{
				Subset[SIGN] = 0;//符号位为正数
				n = -n;//转为正数
			}

			//开始转换
			if (n < 100)//两位数
			{
				Subset[2] = n % 10;//个位数
				Subset[1] = (n - Subset[2]) / 10;//十位数
				Subset[RESULT] = (Subset[1] - 1) * Order + Subset[2];
			}
			else if (n < 1000)//三位数
			{
				Subset[3] = n % 10;//个位数
				Subset[2] = (n % 100 - Subset[3]) / 10;//十位数
				Subset[1] = (n - Subset[2] * 10 - Subset[3]) / 100;//百位数
				switch (Subset[1])
				{
				case 1:
					Basic = Order * Order;
					Subset[RESULT] = (Basic + Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2]);
					break;
				case 2:
					Basic = Order * Order + Order * (Order - 1) / 2;
					Subset[RESULT] = (Basic + Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2]);
					break;
				default:
					break;
				}
			}
			else if (n < 10000)//四位数
			{
				Subset[4] = n % 10;//个位数
				Subset[3] = (n % 100 - Subset[4]) / 10;//十位数
				Subset[2] = (n % 1000 - Subset[3] * 10 - Subset[4]) / 100;//百位数
				Subset[1] = (n - Subset[2] * 100 - Subset[3] * 10 - Subset[4]) / 1000;//千位数
				switch (Subset[1])
				{
				case 1:
					Basic = Order * Order + Order * (Order - 1);
					Subset[RESULT] = (Basic + (Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2] - 1) * Order + Subset[4]);
					break;
				case 2:
					Basic = Order * Order + Order * (Order - 1) + Order * (Order - 1) / 2 * Order;
					Subset[RESULT] = (Basic + (Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2] - 1) * Order + Subset[4]);
					break;
				default:
					break;
				}
			}
			else//五位数
			{
				Subset[5] = n % 10;//个位数
				Subset[4] = (n % 100 - Subset[5]) / 10;//十位数
				Subset[3] = (n % 1000 - Subset[4] * 10 - Subset[5]) / 100;//百位数
				Subset[2] = (n % 10000 - Subset[3] * 100 - Subset[4] * 10 - Subset[5]) / 1000;//千位数
				Subset[1] = (n - Subset[2] * 1000 - Subset[3] * 100 - Subset[4] * 10 - Subset[5]) / 10000;//万位数
				switch (Subset[1])
				{
				case 1:
					Basic = Order * Order + Order * (Order - 1) + Order * (Order - 1) * Order;
					Subset[RESULT] = (Basic + ((Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2] - 1) * Order + Subset[4] - 1) * 2 + Subset[5] + 1);
					break;
				case 2:
					Basic = Order * Order + Order * (Order - 1) + Order * (Order - 1) * Order * 2;
					Subset[RESULT] = (Basic + ((Order * (Subset[2] - 1) - (Subset[2] - 1) * Subset[2] / 2 + Subset[3] - Subset[2] - 1) * Order + Subset[4] - 1) * 2 + Subset[5] + 1);
					break;
				default:
					break;
				}
			}

			//完成转换
			if (Subset[SIGN] == 1)
			{
				P->ClauseValue[i] = Subset[RESULT];
			}
			else
			{
				P->ClauseValue[i] = -Subset[RESULT];
			}
		}
		P = P->NextClause;
	}
	Formula.LitNum = Order * Order + Order * (Order - 1) * (Order * 3 + 1);
}

void DiggingHole(SATFormula& Formula, int** B, int* Puzzle, char* filename)
{
	int i = 0, j = 0;

	for (i = 0; i < Order * Order; i++)//循环挖洞，根据剪叶规则，每个单元格只挖一次
	{
		//准备工作
		FormulaDelete(Formula);//删除上一步的公式
		Constraint_1(Formula, B);//进行三个约束
		Constraint_2(Formula, B);
		Constraint_3(Formula, B);
		Puzzle[i] = -Puzzle[i];//将当前位置翻转
		for (j = 0; j < Order * Order; j++)//添加到公式集
		{
			AddClause(Puzzle + j, 1, Formula);
		}
		Convert(Formula);//转换
		PuzzleSAT_FileSave(Formula, filename);//保存在文件中

		//求解数独
		CreateAdjacencyList(filename, F);
		Copy(S, F);
		Reversal(S);
		for (j = 0; j < 100; j++)
		{
			if (LearnCla[j] != NULL)
			{
				free(LearnCla[j]);
				LearnCla[j] = NULL;
			}
		}
		for (j = 0; j < 100; j++)
		{
			ConflicCla[j] = 0;
		}
		j = BetterExistSingle(S);
		LearnNum = 0;
		ConflicNum = 1;
		CHOOSE = 2;

		if (BetterDPLL(S, j, 1) > 0)
		{
			Puzzle[i] = -Puzzle[i];//若有解则不能挖洞，将原来的位置补回
		}
		else
		{
			Puzzle[i] = 0;//若无解则说明有唯一解，可以去掉
		}
	}

	//结束工作，将挖好的数独的CNF公式保存
	FormulaDelete(Formula);
	Constraint_1(Formula, B);
	Constraint_2(Formula, B);
	Constraint_3(Formula, B);
	for (j = 0; j < Order * Order; j++)
	{
		AddClause(Puzzle + j, 1, Formula);
	}
	Convert(Formula);
	PuzzleSAT_FileSave(Formula, filename);
	printf("已随机生成数独，并保存到文件 %s 中", filename);
}

status Las_vegas(SATFormula& Formula, int** B, int* Puzzle, char* filename)//拉斯维加斯算法，用来随机生成终盘
{
	int i = 0, j = 0, n = 0, ran = 0;

	if (Order == 6)//若想生成6阶棋盘，随机9个
	{
		n = 9;
	}
	else if (Order == 8)//生成8阶棋盘，随机19个
	{
		n = 19;
	}
	for (i = 0; i < n; i++)
	{
		ran = rand() % (Order * Order);//随机确定棋盘位置
		Puzzle[ran] = rand() % 2;//随机确定放入值
	}
	for (i = 1; i <= Order * Order; i++)//逐个将放入的数字转化为ij形式，便于计算
	{
		if (i % Order != 0)//若转化的不是最后一个数
		{
			if (Puzzle[i - 1] == 0)//若放入的数为0
			{
				Puzzle[i - 1] = -(i % Order + ((i - i % Order) / Order + 1) * 10);
			}
			else if (Puzzle[i - 1] == 1)//若放入的数为1
			{
				Puzzle[i - 1] = (i % Order + ((i - i % Order) / Order + 1) * 10);
			}
			else//若没有放入数
			{
				Puzzle[i - 1] = 0;
			}
		}
		else//若转化的是最后一个数
		{
			if (Puzzle[i - 1] == 0)//若放入的数为0
			{
				Puzzle[i - 1] = -(Order + (i / Order) * 10);
			}
			else if (Puzzle[i - 1] == 1)//若放入的数为1
			{
				Puzzle[i - 1] = (Order + (i / Order) * 10);
			}
			else//若没有放入数
			{
				Puzzle[i - 1] = 0;
			}
		}
	}

	//转化为CNF公式并保存
	FormulaDelete(Formula);
	Constraint_1(Formula, B);
	Constraint_2(Formula, B);
	Constraint_3(Formula, B);
	for (j = 0; j < Order * Order; j++)
	{
		AddClause(Puzzle + j, 1, Formula);
	}
	Convert(Formula);
	PuzzleSAT_FileSave(Formula, filename);

	//进行计算
	CreateAdjacencyList(filename, F);
	Copy(S, F);
	Reversal(S);
	for (j = 0; j < 100; j++)
	{
		if (LearnCla[j] != NULL)
		{
			free(LearnCla[j]);
			LearnCla[j] = NULL;
		}
	}
	for (j = 0; j < 100; j++)
	{
		ConflicCla[j] = 0;
	}
	j = BetterExistSingle(S);
	LearnNum = 0;
	ConflicNum = 1;
	CHOOSE = 2;

	if (BetterDPLL(S, j, 1) > 0)//若计算成功，即成功生成一个终局
	{
		for (i = 1; i <= Order * Order; i++)//逐个将解转化为ij形式，方便计算
		{
			if (i % Order != 0)//放置非行尾的元素
			{
				if (VELUE[i] == 0)//当前解为0
				{
					Puzzle[i - 1] = -(i % Order + ((i - i % Order) / Order + 1) * 10);
				}
				else//当前解不是0
				{
					Puzzle[i - 1] = (i % Order + ((i - i % Order) / Order + 1) * 10);
				}
			}
			else//行尾元素
			{
				if (VELUE[i] == 0)
				{
					Puzzle[i - 1] = -(Order + (i / Order) * 10);
				}
				else
				{
					Puzzle[i - 1] = (Order + (i / Order) * 10);
				}
			}
		}
		return OK;//返回成功
	}
	else//若没有成功
	{
		for (i = 0; i < Order * Order; i++)
		{
			Puzzle[i] = -1;//清空棋盘
		}
		return ERROR;//返回失败
	}
}

void FormulaDelete(SATFormula& Formula)
{
	P_ClauseList P = NULL, S = NULL;

	P = Formula.FirstClause;
	while (P != NULL)//循环释放公式集
	{
		S = P->NextClause;
		free(P);
		P = S;
	}
	Formula.FirstClause = NULL;
	Formula.ClaNum = 0;//子句数清零
	Formula.LitNum = 0;//符号数清零
	ClaNumber = 0;
}

void Combine(int s[], int n, int k, SATFormula& Formula, void (*Print)(int* Subset, SATFormula& Formula))
{
	if (k == 0)//如果要想选取的数目为零
	{
		Print(Subset, Formula);//打印选取数组
		return;
	}

	for (int i = n; i >= k; i--)//从第n个开始往后选取
	{
		Subset[k - 1] = s[i];//将选取的数放入选取数组之中
		if (k > 1)
		{
			Combine(s, i - 1, k - 1, Formula, Print);//选取之后的一个数
		}
		else//当选取数为零的时候
		{
			Print(Subset, Formula);//打印选取数组
		}
	}
}

void Print_AddCla(int* Subset, SATFormula& Formula)//将选取数组放入到公式集中
{
	int k = 0;	P_ClauseList P = NULL;

	//行输入
	//正输入
	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
	{
		exit(OVERFLOW);
	}
	for (k = 0; k < Order / 2 + 1; k++)
	{
		P->ClauseValue[k] = Subset[k];
	}
	P->ClauseValue[k] = 0;
	P->NextClause = Formula.FirstClause;
	Formula.FirstClause = P;
	ClaNumber++;

	//负输入
	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
	{
		exit(OVERFLOW);
	}
	for (k = 0; k < Order / 2 + 1; k++)
	{
		P->ClauseValue[k] = -Subset[k];
	}
	P->ClauseValue[k] = 0;
	P->NextClause = Formula.FirstClause;
	Formula.FirstClause = P;
	ClaNumber++;

	//列输入
	//正输入
	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
	{
		exit(OVERFLOW);
	}
	for (k = 0; k < Order / 2 + 1; k++)
	{
		P->ClauseValue[k] = (Subset[k] - Subset[k] % 10) / 10 + ((Subset[k] % 10) * 10);
	}
	P->ClauseValue[k] = 0;
	P->NextClause = Formula.FirstClause;
	Formula.FirstClause = P;
	ClaNumber++;

	//负输入
	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))
	{
		exit(OVERFLOW);
	}
	for (k = 0; k < Order / 2 + 1; k++)
	{
		P->ClauseValue[k] = -((Subset[k] - Subset[k] % 10) / 10 + ((Subset[k] % 10) * 10));
	}
	P->ClauseValue[k] = 0;
	P->NextClause = Formula.FirstClause;
	Formula.FirstClause = P;
	ClaNumber++;
}

void AddClause(int* Subset, int n, SATFormula& Formula)
{
	int  k = 0;	P_ClauseList P = NULL;

	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))//申请空间
	{
		exit(OVERFLOW);
	}
	if (Subset[0] != 0)//当公式子句不为空时
	{
		for (k = 0; k < n; k++)//逐个将公式子句中的内容添加
		{
			P->ClauseValue[k] = Subset[k];
		}
		P->ClauseValue[k] = 0;//放置结尾标志
		P->NextClause = Formula.FirstClause;//链接到子句集中
		Formula.FirstClause = P;
		ClaNumber++;//子句数加一
	}
	Formula.ClaNum = ClaNumber;//放入子句数
}