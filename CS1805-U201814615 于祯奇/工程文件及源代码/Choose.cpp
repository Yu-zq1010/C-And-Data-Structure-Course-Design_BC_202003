#include"head.h"

extern int Time;

status Choose_1(CNF F)
{
	int i = 0;
	for (i = 1; i <= 2 * F.LitNum; i++)//����ÿ������
	{
		if (F.Letters[i].value == Undefine)//���������û�б���ֵ
		{
			return i;//���ظ����ֵ����
		}
	}
}

status Choose_2(CNF F)
{
	int i = 0, Need = 0;	double n = 0, J = 0, Jmax = 0;	ClaNode* P = NULL;
	for (i = 1; i <= 2 * F.LitNum; i++)//����ÿ������
	{
		if (F.Letters[i].value == Undefine)//���������û�б���ֵ
		{
			J = 0;
			P = F.Letters[i].FirstCla;//Pָ�����ֵĵ�һ���Ӿ�
			while (P != NULL)//�������Ӿ�ʱ
			{
				if (P->clause[0] > 0)//���Ӿ�û�б�ɾ����Ϊ��
				{
					n = pow(2, -P->clause[0]);//nΪ2�ĸ���ǰ�Ӿ���Ŀ�η�
					J = J + n;//J��ֵΪ�����Ӿ�nֵ�ĺ�
				}
				P = P->NextCla;
			}
			if (J > Jmax)
			{
				Jmax = J;
				Need = i;
			}
		}
	}
	return Need;
}