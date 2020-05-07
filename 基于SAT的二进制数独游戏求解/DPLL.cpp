#include"head.h"

extern int* VELUE;
extern int CHOOSE;

status DPLL(CNF F, int i)
{
	int j = 0, n = 0;	ClaNode* P = NULL;

	while (i)//���Ӿ䴫��
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
		i = ExistSingle(F);//���²��ҵ��Ӿ�
	}//while

	int v = 0;	CNF S;

	switch (CHOOSE)
	{
	case 1:
		v = Choose_1(F);//��һ��ѡȡ����
		break;
	case 2:
		v = Choose_2(F);//�ڶ���ѡȡ����
		break;
	default:
		break;
	}
	Copy(S, F);//���浱ǰ��ʽ����
	if (DPLL(F, v))//�ڵ�һ��֧������ 
	{
		DeleteCNF(S);;//ɾ��������ʽ��S
		return TRUE;
	}
	else
	{
		v = Opposite_SAT(F.LitNum, v);//ȡv���෴
		if (DPLL(S, v))//���ݵ���vִ�з�֧���Եĳ�̬������һ��֧
		{
			DeleteCNF(S);//ɾ��������ʽ��S
			return TRUE;
		}
		else
		{
			DeleteCNF(S);//ɾ��������ʽ��S
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
	P = F.Letters[i].FirstCla;//Pָ���Ӿ����ֵĵ�һ���Ӿ���
	F.Letters[i].value = TRUE;//���Ӿ�����ֵΪ��
	if (i <= F.LitNum)//��Ϊ������
	{
		F.Letters[i + F.LitNum].value = FALSE;//���Ӿ�ĸ�����ֵΪ��
	}
	else//��Ϊ������
	{
		F.Letters[i - F.LitNum].value = FALSE;//���Ӿ��������ֵΪ��
	}
	while (P != NULL)//���Ӿ䲻Ϊ��ʱ 
	{
		P->clause[0] = DELETE;//ɾ�����������ֵ��Ӿ�
		P = P->NextCla;
	}
	if (i <= F.LitNum)//��������Ϊ������
	{
		P = F.Letters[i + F.LitNum].FirstCla;//��PΪ�����ֵĸ����ֵĵ�һ���Ӿ�
		while (P != NULL)
		{
			for (j = 1, n = 0; j <= P->clause[0]; j++)//����������Ӿ�
			{
				if (P->clause[j] == -i) //�ҵ��ø�����
				{
					P->clause[j] = 0;//ɾ��
					n += 1;//��¼Ҫɾ����������Ŀ
				}
				else if (P->clause[j] == 0)//����Ѿ���ɾ��
				{
					P->clause[0] += 1;//��������һ
					n += 1;//��ɾ������һ
				}
			}
			P->clause[0] -= n;//���Ӿ��е�������Ŀ���и���
			P = P->NextCla;
		}
	}
	else//��������Ϊ������
	{
		P = F.Letters[i - F.LitNum].FirstCla;//��PΪ�����ֵ������ֵĵ�һ���Ӿ�
		while (P != NULL) {
			for (j = 1, n = 0; j <= P->clause[0]; j++)//����������Ӿ�
			{
				if (P->clause[j] == i - F.LitNum)//�ҵ���������
				{
					P->clause[j] = 0;//ɾ��
					n += 1; //��¼Ҫɾ����������Ŀ
				}
				else if (P->clause[j] == 0)//����Ѿ���ɾ��
				{
					P->clause[0] += 1;//��������һ
					n += 1;//��ɾ������һ
				}
			}
			P->clause[0] -= n;//���Ӿ��е�������Ŀ���и���
			P = P->NextCla;
		}
	}
}

status ExistSingle(CNF F)
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
					return i;//���ظõ��Ӿ�
				}
				P = P->NextCla;//��ѯ��һ���Ӿ�
			}
		}
	}
	return FALSE;//û�е��Ӿ��򷵻�FALSE
}

status EmptyCNF(CNF F)
{
	int i = 0;	ClaNode* P = NULL;

	for (i = 1; i <= 2 * F.LitNum; i++)//�������ÿ�����ֵ��ڽ�����
	{
		if (F.Letters[i].value != TRUE)
		{
			P = F.Letters[i].FirstCla;//Pָ��ǰ���ֵĵ�һ���Ӿ���
			while (P != NULL)//����ǰ�Ӿ䲻Ϊ��
			{
				if (P->clause[0] >= 0)//��û�б�ɾ����Ϊ���Ӿ�
				{
					return FALSE;//��ǰ��ʽ��Ϊ�գ�����FAlSE
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
	P = F.Letters[Key].FirstCla;//Pָ��ǰ���ֵĵ�һ���Ӿ���
	while (P != NULL)//����ǰ�Ӿ䲻Ϊ��
	{
		if (P->clause[0] == 0)//���ǿ��Ӿ�
		{
			return TRUE;//���ҵ����Ӿ䣬����TRUE
		}
		P = P->NextCla;
	}
	return FALSE;
}

void DeleteCNF(CNF& F)
{
	int i = 0, j = 0, n = 0, ** T = NULL;	ClaNode* P = NULL, * Q = NULL, * R = NULL, * S = NULL;

	if (!(T = (int**)calloc(F.ClaNum, sizeof(int*))))//��̬��������
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * F.LitNum; i++)//����ռ�ÿ���Ӿ�ռ�ĵ�ַ
	{
		P = F.Letters[i].FirstCla;//ָ����������ĵ�һ�����
		while (P != NULL)//��������ʱ
		{
			P->clause[0] = 1;
			P = P->NextCla;
		}
	}
	for (i = 1, n = 0; i <= 2 * F.LitNum; i++)//����ռ�ÿ���Ӿ�ռ�ĵ�ַ
	{
		P = F.Letters[i].FirstCla;//ָ����������ĵ�һ�����
		while (P != NULL)//��������ʱ
		{
			if (P->clause[0] != DELETE)
			{
				T[n] = P->clause;//���洢�ռ��ָ����������б���
				P->clause[0] = DELETE;//���ñ�־λȷ���Ƿ�ͳ�ƹ�
				n++;
			}
			P = P->NextCla;
		}
	}
	for (n = 0; n < F.ClaNum; n++)//ѭ���ͷ������Ӿ�Ĵ洢�ռ�
	{
		free(T[n]);
	}
	free(T);//�ͷ�ָ������
	for (i = 1; i <= 2 * F.LitNum; i++)//ɾ��ȫ����������
	{
		P = F.Letters[i].FirstCla;//ָ����������ĵ�һ�����
		while (P != NULL)//��������ʱ
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

void Copy(CNF& S, CNF F)/*�о�����������*/
{
	int i = 0, j = 0, k = 0, num = 0, Num = 0, * Cla = NULL;	ClaNode* P = NULL;

	S.LitNum = F.LitNum;//����������Ŀ
	if (!(S.Letters = (LitList)calloc(2 * S.LitNum + 1, sizeof(Litnode))))//��̬��������
	{
		exit(OVERFLOW);
	}
	for (i = 1; i <= 2 * S.LitNum; i++)//��F��ÿ�����ֵ���ֵ����
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
				if (P->clause[0] > 0)//����ʽF�ĵ�i�����ֵ��Ӿ�û�б�ɾ���Ҳ�Ϊ��,����û�б����
				{
					Num += 1;
					if (i == MinNum(P->clause, F.LitNum))
					{
						if (!(Cla = (int*)calloc(P->clause[0] + 1, sizeof(int))))//��̬��������
						{
							exit(OVERFLOW);
						}
						Cla[0] = P->clause[0];
						for (j = 1, k = 1; k <= P->clause[0]; j++)//�������Ӿ���Ԫ��
						{
							if (P->clause[j] != 0)
							{
								Cla[k] = P->clause[j];
								k++;
							}
						}
						for (k = 1; k <= Cla[0]; k++)//����ÿ�����ֵ��ڽӱ�
						{
							ClaNode* L;//�����µĽ�㣬�������
							if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
							{
								exit(OVERFLOW);
							}
							L->clause = Cla;
							L->ClaNum = P->ClaNum;//�����Ӿ������ֵ���Ŀ
							if (Cla[k] > 0 && NotSameNum(Cla, k))//��������Ϊ������
							{
								L->NextCla = S.Letters[Cla[k]].FirstCla;
								S.Letters[Cla[k]].FirstCla = L;
							}
							else if (Cla[k] < 0 && NotSameNum(Cla, k))//��Ϊ������
							{
								L->NextCla = S.Letters[S.LitNum - Cla[k]].FirstCla;
								S.Letters[S.LitNum - Cla[k]].FirstCla = L;
							}
						}
						num += 1;//ͳ���Ӿ���Ŀ
					}
				}
				P = P->NextCla;
			}
		}
		S.ClaNum = num;//�Ӿ���Ŀ
	}
}

int MinNum(int* N, int m)
{
	int i = 0, j = 0, * Num = NULL;
	if (!(Num = (int*)calloc(N[0], sizeof(int))))//��̬��������
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