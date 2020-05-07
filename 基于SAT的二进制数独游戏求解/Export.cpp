#include"head.h"

extern int* VELUE;

void ExportCNF(CNF F)
{
	int i = 0, j = 0;	ClaNode* P = NULL;

	for (i = 1; i <= 2 * F.LitNum; i++)
	{
		P = F.Letters[i].FirstCla;
		while (P != NULL)
		{
			if (P->clause[0] > 0 && i == MinNum(P->clause, F.LitNum))//����ʽF�ĵ�i�����ֵ��Ӿ�û�б�ɾ���Ҳ�Ϊ��,����û�б����
			{
				for (j = 1; j <= P->clause[0]; j++)//�������Ӿ���Ԫ��
				{
					printf("%d ", P->clause[j]);
				}
				printf("\n");
			}
			P = P->NextCla;
		}
	}
	printf("����������Ѿ��������CNF��ʽ");
}

void ExportSAT(SATFormula Formula)
{
	P_ClauseList P = NULL;	int i = 0;
	P = Formula.FirstClause;
	while (P != NULL)
	{
		for (i = 0;; i++)
		{
			if (P->ClauseValue[i] != 0)
			{
				printf("%d ", P->ClauseValue[i]);
			}
			else
			{
				break;
			}
		}
		printf("\n");
		P = P->NextClause;
	}
	printf("ClaNum = %d\n", Formula.ClaNum);
	printf("LitNum = %d", Formula.LitNum);
}

status PuzzleSAT_FileSave(SATFormula Formula, char* filename)
{
	P_ClauseList P = NULL;	int i = 0;	FILE* fp = NULL;

	if ((fp = fopen(filename, "w")) == NULL)//���filename�ļ���ʧ��
	{
		return ERROR;
	}
	fprintf(fp, "%s", "p cnf ");//��ſ�ʼ��־
	fprintf(fp, "%d ", Formula.LitNum);//���������
	fprintf(fp, "%d\n", Formula.ClaNum);//����Ӿ���

	P = Formula.FirstClause;//ָ���һ���Ӿ�
	while (P != NULL)//���������Ӿ�
	{
		for (i = 0;; i++)//��������ǰ�Ӿ���������
		{
			if (P->ClauseValue[i] != 0)//����ǰ���ֲ�Ϊ0
			{
				fprintf(fp, "%d ", P->ClauseValue[i]);//���
			}
			else//��Ϊ0
			{
				break;//��ǰ�Ӿ����
			}
		}
		fprintf(fp, "%d\n", 0);//����س�
		P = P->NextClause;//��һ���Ӿ�
	}
	fclose(fp);//�ر��ļ�
	return OK;
}

void SATSove_FileSave(char* filename, int s, long t, int NUM)
{
	char savefile[20] = { 0 };	int i = 0, S_len = 0;	FILE* fp = NULL;

	S_len = strlen(filename);//�����ǰ�ļ�������
	for (i = 0; i < S_len - 3; i++)//���ļ������Ƶ���Ҫ������ļ����У��������ַ�����CNF����Ҫ
	{
		savefile[i] = filename[i];
	}
	savefile[i] = '\0';//���������־
	strcat(savefile, "res");//����res
	fp = fopen(savefile, "w");//����Ҫд����ļ�

	fprintf(fp, "%c", 's');//�����ַ�'s'
	fprintf(fp, "%7d\n", s);//����s��ֵ����������û�н�

	if (s == 0)//���޽�
	{
		fprintf(fp, "%c\n", 'v');//����'v'�ַ�
		fprintf(fp, "%c", 't');//����'t'�ַ�
		fprintf(fp, "%7ld", t);//����t��ֵ
	}

	else if (s == 1)//���н�
	{
		fprintf(fp, "%c", 'v');//����'v'�ַ�

		if (VELUE[1] == 0)//Ϊ�˻س����������ȷ����һ���ַ�������һ������Ϊ��
		{
			fprintf(fp, "%7d", -1);//����-1
		}
		else//��Ϊ���ȷ��
		{
			fprintf(fp, "%7d", 1);//����1
		}
		for (i = 2; i <= NUM; i++)//ѭ������ʣ�����ֵĽ�
		{
			if (i % 10 == 1)//ÿ��10�����ֻ���
			{
				fprintf(fp,"%s","\n");
			}
			if (VELUE[i] == 0)
			{
				fprintf(fp, "%8d", -i);//Ϊ�˶��䣬����8������
			}
			else
			{
				fprintf(fp, "%8d", i);
			}
		}
		fprintf(fp, "\n%c", 't');//����'t'�ַ�
		fprintf(fp, "%7ld", t);//����t��ֵ
	}
	fclose(fp);//�ر��ļ�
	printf("�ѽ�������浽�ļ� %s ��", savefile);//�����ʾ
}