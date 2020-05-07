#include"head.h"


status CreateAdjacencyList(char* filename, CNF& F)
{
	char s[4];	int i = 0, j = 0, k = 0;/*������*/	int a = 0, n[50] = { 0 }, * Cla = NULL; FILE* fp = NULL;

	if ((fp = fopen(filename, "r")) == NULL)//���filename�ļ���ʧ��
	{
		return ERROR;
	}

	for (; s[0] != 'p'; fscanf(fp, "%c", &s[0]));//�����ȡ�ļ��е�Ԫ�أ�ֱ��������pΪ��ʼ������

	fscanf(fp, "%s", s);
	if (s[0] == 'c' && s[1] == 'n' && s[2] == 'f')//����cnf�ļ�
	{
		fscanf(fp, "%d", &F.LitNum);
		fscanf(fp, "%d", &F.ClaNum);
		if (!(F.Letters = (LitList)calloc(2 * F.LitNum + 1, sizeof(Litnode))))//��̬��������
		{
			exit(OVERFLOW);
		}
		for (i = 0; i < F.ClaNum; i++)//ѭ�������i���Ӿ�
		{
			j = 0;//��ʼ��������
			fscanf(fp, "%d", &a);
			while (a != 0)//���¼��ÿ���Ӿ������
			{
				n[j] = a;
				j++;//ͳ��ÿ���Ӿ�����ָ���
				fscanf(fp, "%d", &a);
			}
			if (!(Cla = (int*)calloc(j + 1, sizeof(int))))//��̬��������
			{
				exit(OVERFLOW);
			}
			Cla[0] = j;//����־λ����Ϊ�Ӿ䳤�ȣ�����0��������Ӿ����
			for (k = 0; k < j; k++)//������õ������ڶ�̬������
			{
				Cla[k + 1] = n[k];
			}
			for (k = 1; k < j + 1; k++)//����ÿ�����ֵ��ڽӱ�
			{
				ClaNode* L;//�����µĽ�㣬�������
				if (!(L = (ClaNode*)malloc(sizeof(ClaNode))))
				{
					exit(OVERFLOW);
				}
				L->clause = Cla;
				L->ClaNum = Cla[0];
				if (Cla[k] > 0 && NotSameNum(Cla, k))//��������Ϊ������
				{
					L->NextCla = F.Letters[Cla[k]].FirstCla;
					F.Letters[Cla[k]].FirstCla = L;
				}
				else if (Cla[k] < 0 && NotSameNum(Cla, k))//��Ϊ������
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
		return ERROR;//����cnf�ļ�������ʧ��
	}
}