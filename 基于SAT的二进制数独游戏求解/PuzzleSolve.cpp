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

int** Prepare()//׼�������һ��Ŀ���ά����
{
	int** B = NULL, i = 0, j = 0;

	ClaNumber = 0;
	if (!(B = (int**)calloc(Order + 1, sizeof(int*))))//����ռ�
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= Order; i++)//�������ռ�
	{
		if (!(B[i] = (int*)calloc(Order + 1, sizeof(int))))
		{
			exit(OVERFLOW);
		}
		for (j = 1; j <= Order; j++)//�������
		{
			B[i][j] = i * 10 + j;
		}
	}
	return B;
}

void Constraint_1(SATFormula& Formula, int** B)//Լ��1
{
	int i = 0, j = 0, k = 0; P_ClauseList P = NULL;

	//������
	for (i = 1; i <= Order; i++)
	{
		for (j = 1; j <= Order - 2; j++)
		{
			//������
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

			//������
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

	//������
	for (j = 1; j <= Order; j++)
	{
		for (i = 1; i <= Order - 2; i++)
		{
			//������
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

			//������
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

void Constraint_2(SATFormula& Formula, int** B)//Լ��2
{
	int i = 0, j = 0;	P_ClauseList P = NULL;	void (*Print)(int* Subset, SATFormula & Formula);

	if (Order == 4)
	{
		//������
		for (i = 1; i <= Order; i++)
		{
			//������
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

			//������
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

		//������
		for (i = 1; i <= Order; i++)
		{
			//������
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

			//������
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
		Print = Print_AddCla;//����ָ�븳ֵ
		if (!(Subset = (int*)calloc(Order / 2 + 1, sizeof(int))))
		{
			exit(OVERFLOW);
		}
		for (i = 1; i <= Order; i++)
		{
			Combine(B[i], Order, Order / 2 + 1, Formula, Print);//������Ϻ���ѡȡ���ø볲ԭ��ѡȡ
		}
		Formula.ClaNum = ClaNumber;//���뵱ǰ�Ӿ�ֵ
		free(Subset);//�ͷŴ洢�ռ�
		Subset = NULL;
	}
}

void Constraint_3(SATFormula& Formula, int** B)//Լ��3
{
	int i = 0, j = 0, k = 0, n = 0, t = 0, o = 0, num = 0;

	if (!(Subset = (int*)calloc(Order + 1, sizeof(int))))
	{
		exit(OVERFLOW);
	}
	for (i = 1; i < 3; i++)//�л���
	{
		for (j = 1; j < Order; j++)//��һ����ֵ
		{
			for (k = j + 1; k <= Order; k++)//�ڶ�����ֵ
			{
				n = i * 100 + j * 10 + k;

				//ת��157= -[1571,1572,��,1578]
				Subset[0] = -n;//ѡȡԼ�����У�-157,-1571,-1572,��,-1578���Ӿ�
				for (num = 1; num <= Order; num++)
				{
					Subset[num] = -(n * 10 + num);
				}
				AddClause(Subset, num, Formula);//��Ӹ��Ӿ�

				Subset[0] = n;//ѡȡԼ�����У�1571,157��,��1572,157������1578,157��
				for (num = 1; num <= Order; num++)
				{
					Subset[1] = (n * 10 + num);
					AddClause(Subset, 2, Formula);//��Ӹ��Ӿ�
				}

				//ת��15711= 51,71��15710= -51,-71��1571= 15711,15710
				for (num = 1; num <= Order; num++)//��1��8
				{
					//ת��1571= 15711,15710
					Subset[0] = -(n * 10 + num);//-1571
					Subset[1] = (n * 100 + num * 10 + 1);//15711
					Subset[2] = (n * 100 + num * 10 + 0);//15710
					AddClause(Subset, 3, Formula);//���1571��15711��15710
					for (t = 0; t < 3; t++)
					{
						Subset[t] = -Subset[t];//ʹ�Ӿ�������Ԫ��ֵֵ��ת
					}
					AddClause(Subset, 2, Formula);//��Ӹ��Ӿ�1571��-15711
					Subset[1] = Subset[2];//��-71���ڵڶ���
					AddClause(Subset, 2, Formula);//��Ӹ��Ӿ�1571��-15710

					//ת��15711= 51,71��15710= -51,-71
					for (o = 0; o < 2; o++)//oΪ��ĩλʱ0����1
					{
						if (i == 1)//��Ϊ������Ƚ�
						{
							if (o == 0)//��Ϊ0
							{
								Subset[0] = (n * 100 + num * 10 + o);//15710
								Subset[1] = (j * 10 + num);//51
								Subset[2] = (k * 10 + num);//71
								AddClause(Subset, 3, Formula);//���15710��51��71
							}
							else//��Ϊ1
							{
								Subset[0] = (n * 100 + num * 10 + o);//15711
								Subset[1] = -(j * 10 + num);//-51
								Subset[2] = -(k * 10 + num);//-71
								AddClause(Subset, 3, Formula);//��Ӹ��Ӿ�15711��-51��-71
							}
						}
						else//��Ϊ������Ƚ�
						{
							if (o == 0)//��Ϊ0
							{
								Subset[0] = (n * 100 + num * 10 + o);//25710
								Subset[1] = (num * 10 + j);//15
								Subset[2] = (num * 10 + k);//17
								AddClause(Subset, 3, Formula);//���25710��15��17
							}
							else//��Ϊ1
							{
								Subset[0] = (n * 100 + num * 10 + o);//15711
								Subset[1] = -(num * 10 + j);//-15
								Subset[2] = -(num * 10 + k);//-17
								AddClause(Subset, 3, Formula);//��Ӹ��Ӿ�25711��-15��-17
							}
						}
						for (t = 0; t < 3; t++)
						{
							Subset[t] = -Subset[t];//ʹ�Ӿ�������Ԫ��ֵֵ��ת
						}
						AddClause(Subset, 2, Formula);//��Ӹ��Ӿ�-15710��-51
						Subset[1] = Subset[2];//��-71���ڵڶ���
						AddClause(Subset, 2, Formula);//��Ӹ��Ӿ�-15710��-71
					}
				}
			}
		}
	}
	Formula.ClaNum = ClaNumber;//�����Ӿ�����
	free(Subset);//�ͷŴ洢�ռ�
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
			if (n == 0)//�����˽�������
			{
				break;
			}

			//�ж�����
			if (n > 0)//��Ҫת���������0
			{
				Subset[SIGN] = 1;//����λΪ����
			}
			else//��Ҫת�����С��0
			{
				Subset[SIGN] = 0;//����λΪ����
				n = -n;//תΪ����
			}

			//��ʼת��
			if (n < 100)//��λ��
			{
				Subset[2] = n % 10;//��λ��
				Subset[1] = (n - Subset[2]) / 10;//ʮλ��
				Subset[RESULT] = (Subset[1] - 1) * Order + Subset[2];
			}
			else if (n < 1000)//��λ��
			{
				Subset[3] = n % 10;//��λ��
				Subset[2] = (n % 100 - Subset[3]) / 10;//ʮλ��
				Subset[1] = (n - Subset[2] * 10 - Subset[3]) / 100;//��λ��
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
			else if (n < 10000)//��λ��
			{
				Subset[4] = n % 10;//��λ��
				Subset[3] = (n % 100 - Subset[4]) / 10;//ʮλ��
				Subset[2] = (n % 1000 - Subset[3] * 10 - Subset[4]) / 100;//��λ��
				Subset[1] = (n - Subset[2] * 100 - Subset[3] * 10 - Subset[4]) / 1000;//ǧλ��
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
			else//��λ��
			{
				Subset[5] = n % 10;//��λ��
				Subset[4] = (n % 100 - Subset[5]) / 10;//ʮλ��
				Subset[3] = (n % 1000 - Subset[4] * 10 - Subset[5]) / 100;//��λ��
				Subset[2] = (n % 10000 - Subset[3] * 100 - Subset[4] * 10 - Subset[5]) / 1000;//ǧλ��
				Subset[1] = (n - Subset[2] * 1000 - Subset[3] * 100 - Subset[4] * 10 - Subset[5]) / 10000;//��λ��
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

			//���ת��
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

	for (i = 0; i < Order * Order; i++)//ѭ���ڶ������ݼ�Ҷ����ÿ����Ԫ��ֻ��һ��
	{
		//׼������
		FormulaDelete(Formula);//ɾ����һ���Ĺ�ʽ
		Constraint_1(Formula, B);//��������Լ��
		Constraint_2(Formula, B);
		Constraint_3(Formula, B);
		Puzzle[i] = -Puzzle[i];//����ǰλ�÷�ת
		for (j = 0; j < Order * Order; j++)//��ӵ���ʽ��
		{
			AddClause(Puzzle + j, 1, Formula);
		}
		Convert(Formula);//ת��
		PuzzleSAT_FileSave(Formula, filename);//�������ļ���

		//�������
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
			Puzzle[i] = -Puzzle[i];//���н������ڶ�����ԭ����λ�ò���
		}
		else
		{
			Puzzle[i] = 0;//���޽���˵����Ψһ�⣬����ȥ��
		}
	}

	//�������������ںõ�������CNF��ʽ����
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
	printf("��������������������浽�ļ� %s ��", filename);
}

status Las_vegas(SATFormula& Formula, int** B, int* Puzzle, char* filename)//��˹ά��˹�㷨�����������������
{
	int i = 0, j = 0, n = 0, ran = 0;

	if (Order == 6)//��������6�����̣����9��
	{
		n = 9;
	}
	else if (Order == 8)//����8�����̣����19��
	{
		n = 19;
	}
	for (i = 0; i < n; i++)
	{
		ran = rand() % (Order * Order);//���ȷ������λ��
		Puzzle[ran] = rand() % 2;//���ȷ������ֵ
	}
	for (i = 1; i <= Order * Order; i++)//��������������ת��Ϊij��ʽ�����ڼ���
	{
		if (i % Order != 0)//��ת���Ĳ������һ����
		{
			if (Puzzle[i - 1] == 0)//���������Ϊ0
			{
				Puzzle[i - 1] = -(i % Order + ((i - i % Order) / Order + 1) * 10);
			}
			else if (Puzzle[i - 1] == 1)//���������Ϊ1
			{
				Puzzle[i - 1] = (i % Order + ((i - i % Order) / Order + 1) * 10);
			}
			else//��û�з�����
			{
				Puzzle[i - 1] = 0;
			}
		}
		else//��ת���������һ����
		{
			if (Puzzle[i - 1] == 0)//���������Ϊ0
			{
				Puzzle[i - 1] = -(Order + (i / Order) * 10);
			}
			else if (Puzzle[i - 1] == 1)//���������Ϊ1
			{
				Puzzle[i - 1] = (Order + (i / Order) * 10);
			}
			else//��û�з�����
			{
				Puzzle[i - 1] = 0;
			}
		}
	}

	//ת��ΪCNF��ʽ������
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

	//���м���
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

	if (BetterDPLL(S, j, 1) > 0)//������ɹ������ɹ�����һ���վ�
	{
		for (i = 1; i <= Order * Order; i++)//�������ת��Ϊij��ʽ���������
		{
			if (i % Order != 0)//���÷���β��Ԫ��
			{
				if (VELUE[i] == 0)//��ǰ��Ϊ0
				{
					Puzzle[i - 1] = -(i % Order + ((i - i % Order) / Order + 1) * 10);
				}
				else//��ǰ�ⲻ��0
				{
					Puzzle[i - 1] = (i % Order + ((i - i % Order) / Order + 1) * 10);
				}
			}
			else//��βԪ��
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
		return OK;//���سɹ�
	}
	else//��û�гɹ�
	{
		for (i = 0; i < Order * Order; i++)
		{
			Puzzle[i] = -1;//�������
		}
		return ERROR;//����ʧ��
	}
}

void FormulaDelete(SATFormula& Formula)
{
	P_ClauseList P = NULL, S = NULL;

	P = Formula.FirstClause;
	while (P != NULL)//ѭ���ͷŹ�ʽ��
	{
		S = P->NextClause;
		free(P);
		P = S;
	}
	Formula.FirstClause = NULL;
	Formula.ClaNum = 0;//�Ӿ�������
	Formula.LitNum = 0;//����������
	ClaNumber = 0;
}

void Combine(int s[], int n, int k, SATFormula& Formula, void (*Print)(int* Subset, SATFormula& Formula))
{
	if (k == 0)//���Ҫ��ѡȡ����ĿΪ��
	{
		Print(Subset, Formula);//��ӡѡȡ����
		return;
	}

	for (int i = n; i >= k; i--)//�ӵ�n����ʼ����ѡȡ
	{
		Subset[k - 1] = s[i];//��ѡȡ��������ѡȡ����֮��
		if (k > 1)
		{
			Combine(s, i - 1, k - 1, Formula, Print);//ѡȡ֮���һ����
		}
		else//��ѡȡ��Ϊ���ʱ��
		{
			Print(Subset, Formula);//��ӡѡȡ����
		}
	}
}

void Print_AddCla(int* Subset, SATFormula& Formula)//��ѡȡ������뵽��ʽ����
{
	int k = 0;	P_ClauseList P = NULL;

	//������
	//������
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

	//������
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

	//������
	//������
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

	//������
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

	if (!(P = (P_ClauseList)malloc(sizeof(P_ClauseNode))))//����ռ�
	{
		exit(OVERFLOW);
	}
	if (Subset[0] != 0)//����ʽ�Ӿ䲻Ϊ��ʱ
	{
		for (k = 0; k < n; k++)//�������ʽ�Ӿ��е��������
		{
			P->ClauseValue[k] = Subset[k];
		}
		P->ClauseValue[k] = 0;//���ý�β��־
		P->NextClause = Formula.FirstClause;//���ӵ��Ӿ伯��
		Formula.FirstClause = P;
		ClaNumber++;//�Ӿ�����һ
	}
	Formula.ClaNum = ClaNumber;//�����Ӿ���
}