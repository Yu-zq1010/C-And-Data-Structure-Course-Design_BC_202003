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

	while (i)//���Ӿ䴫��
	{
		BetterBCP(F, i, Deep);//����BCP����
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
		i = BetterExistSingle(F);//���²��ҵ��Ӿ�
	}//while

	int v = 0, Difference = 0;	CNF S;

	AddLearnCla(F);//��ѧϰ�Ӿ���ӵ��Ӿ伯��
	switch (CHOOSE)
	{
	case 1:
		v = Choose_1(F);//��һ��ѡȡ����
		break;
	case 2:
		v = Choose_2(F);//�ڶ���ѡȡ����
		if (v == 0)
		{
			exit(-5);
		}
		break;
	default:
		break;
	}

	BetterCopy(S, F);//���浱ǰ��ʽ����
	if ((Difference = BetterDPLL(F, v, Deep + 1)) > 0)//�ڵ�һ��֧������ 
	{
		DeleteCNF(S);//ɾ��������ʽ��S
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
			v = Opposite_SAT(F.LitNum, v);//ȡv���෴
			AddLearnCla(S);
			if ((Difference = BetterDPLL(S, v, Deep + 1)) > 0)//���ݵ���vִ�з�֧���Եĳ�̬������һ��֧
			{
				DeleteCNF(S);//ɾ��������ʽ��S
				return TRUE;
			}
			else
			{
				DeleteCNF(S);//ɾ��������ʽ��S
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

	P = F.Letters[i].FirstCla;//Pָ���Ӿ����ֵĵ�һ���Ӿ���
	F.Letters[i].value = TRUE;//���Ӿ�����ֵΪ��
	F.Letters[i].Deep = Deep;//��ǰ�������
	while (P != NULL)//���Ӿ䲻Ϊ��ʱ 
	{
		P->clause[0] = DELETE;//ɾ�����������ֵ��Ӿ�
		P = P->NextCla;
	}
	OppNum = Opposite_SAT(F.LitNum, i);//ȡi���෴��
	F.Letters[OppNum].value = FALSE;//���Ӿ���෴����ֵΪ��
	F.Letters[OppNum].Deep = Deep;//��ǰ�������
	P = F.Letters[OppNum].FirstCla;//��PΪ�����ֵ��෴���ֵĵ�һ���Ӿ�
	while (P != NULL)
	{
		if (P->clause[0] > 0)
		{
			for (j = 1, n = 0; j <= P->ClaNum; j++)//����������Ӿ�
			{
				if (F.Letters[P->clause[j]].value == FALSE) //�ҵ����෴����
				{
					n += 1;//��¼Ҫɾ����������Ŀ
				}
			}
			P->clause[0] = P->ClaNum - n;//���Ӿ��е�������Ŀ���и���
		}
		P = P->NextCla;
	}
}

status BetterExistSingle(CNF F)
{
	int i = 0, j = 0;	ClaNode* P = NULL;

	for (i = 1; i <= 2 * F.LitNum; i++)//�������ÿ�����ֵ��ڽ�����
	{
		if (F.Letters[i].value == Undefine)
		{
			P = F.Letters[i].FirstCla;//Pָ��ǰ���ֵĵ�һ���Ӿ���
			while (P != NULL)//�����Ӿ����ʱ
			{
				if (P->clause[0] == 1)//���ҵ����Ӿ�ʱ
				{
					if (P->ClaNum != 1)
					{
						F.Letters[i].CLA = P;
						F.Letters[Opposite_SAT(F.LitNum, i)].CLA = P;
					}
					return i;
				}
				P = P->NextCla;//��ѯ��һ���Ӿ�
			}
		}
	}
	return FALSE;//û�е��Ӿ��򷵻�FALSE
}

status BetterEmptyCla(CNF F, int Key)
{
	ClaNode* P = NULL;	int Deep = 0, MaxDeep = 0, i = 0, j = 0, N[MaxLearnClaNum] = { 0 }, * Cla = NULL;

	Key = Opposite_SAT(F.LitNum, Key);
	P = F.Letters[Key].FirstCla;//Pָ��ǰ���ֵĵ�һ���Ӿ���
	while (P != NULL)//����ǰ�Ӿ䲻Ϊ��
	{
		if (P->clause[0] == 0)//���ǿ��Ӿ�
		{
			for (i = 0; i < 100; i++)
			{
				ConflicCla[i] = 0;
			}
			ConflicNum = 1;
			for (i = 1; i <= P->ClaNum; i++)
			{
				SearchConflic(F, P, P->clause[i]);//Ѱ���̺�ͼ�е�û��ǰ���Ľ��
			}
			for (i = 1, j = 0; i < ConflicNum && j < MaxLearnClaNum; i++)//ֻ���泤�Ȳ�����10��ѧϰ�Ӿ�
			{
				if (NotSameNum(ConflicCla, i) == TRUE)//�ų��ظ��Ľ��
				{
					if (F.Letters[ConflicCla[i]].value == TRUE)
					{
						ConflicCla[i] = Opposite_SAT(F.LitNum, ConflicCla[i]);
					}
					N[j] = ConflicCla[i];//��������ʱ������
					j++;//ͳ��ѧϰ�Ӿ�ĸ���
				}
			}
			if (i == 100 || j == 0 || j == MaxLearnClaNum)
			{
				return TRUE;
			}

			if (!(Cla = (int*)calloc(j + 1, sizeof(int))))//����ռ�
			{
				exit(OVERFLOW);
			}
			Cla[0] = j;
			for (i = 1; i <= j; i++)
			{
				Cla[i] = N[i - 1];//��ѧϰ�����Ӿ䱣����������
			}
			for (i = 1, MaxDeep = 0; i <= Cla[0]; i++)//ͳ��ѧϰ�Ӿ������Ĳ���
			{
				if (F.Letters[Cla[i]].Deep > MaxDeep)
				{
					MaxDeep = F.Letters[Cla[i]].Deep;
				}
			}
			Deep = F.Letters[Key].Deep - MaxDeep;//�����뵱ǰ�Ĳ�����
			LearnCla[LearnNum % 100] = Cla;//��ѧϰ�����Ӿ䱣��������ѧϰ�Ӿ����
			LearnNum++;
			return Deep + 1;//������Ȳ�
		}
		P = P->NextCla;
	}
	return FALSE;
}

void BetterCopy(CNF& S, CNF F)
{
	int i = 0, j = 0, k = 0, num = 0, Num = 0, * Cla = NULL;	ClaNode* P = NULL;

	S.LitNum = F.LitNum;//����������Ŀ
	if (!(S.Letters = (LitList)calloc(2 * S.LitNum + 1, sizeof(Litnode))))//��̬��������
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * S.LitNum; i++)//����ÿ�����ֵ���Ϣ
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
					if (i == BetterMinNum(F, P->ClaNum, P->clause))//����ʽF�ĵ�i�����ֵ��Ӿ�û�б�ɾ���Ҳ�Ϊ��,����û�б����
					{
						if (!(Cla = (int*)calloc(P->ClaNum + 1, sizeof(int))))//��̬��������
						{
							exit(OVERFLOW);
						}
						for (j = 0; j <= P->ClaNum; j++)//�������Ӿ���Ԫ��
						{
							Cla[j] = P->clause[j];
						}
						for (k = 1; k <= P->ClaNum; k++)//����ÿ�����ֵ��ڽӱ�
						{
							if (F.Letters[Cla[k]].value != FALSE)
							{
								ClaNode* L;//�����µĽ�㣬�������

								if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
								{
									exit(OVERFLOW);
								}
								L->clause = Cla;
								L->ClaNum = P->ClaNum;//�����Ӿ������ֵ���Ŀ
								if (NotSameNum(Cla, k))//��������Ϊ������
								{
									L->NextCla = S.Letters[Cla[k]].FirstCla;
									S.Letters[Cla[k]].FirstCla = L;
								}
							}
						}
						num += 1;//ͳ���Ӿ���Ŀ
					}
				}
				P = P->NextCla;
			}
		}
	}
	S.ClaNum = num;//�Ӿ���Ŀ
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
		if (LearnCla[i] != NULL)//��ǰѧϰ�Ӿ����
		{
			P = LearnCla[i];
			n++;//�Ӿ�����һ
			if (!(Cla = (int*)calloc(P[0] + 1, sizeof(int))))//����ռ�
			{
				exit(OVERFLOW);
			}

			for (j = 0; j <= P[0]; j++)//��ѧϰ�־临��
			{
				Cla[j] = P[j];
			}

			for (j = 1; j <= P[0]; j++)
			{
				if (F.Letters[Cla[j]].value == TRUE)//������Ӿ������Ѿ��ж�Ϊ��
				{
					Cla[0] = DELETE;//���Ӿ�ɾ��
					break;
				}
				else if (F.Letters[Cla[j]].value == FALSE)//��Ϊ��
				{
					Cla[0] -= 1;//�Ӿ�����������һ
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
		F.ClaNum += n;//���Ӿ������
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