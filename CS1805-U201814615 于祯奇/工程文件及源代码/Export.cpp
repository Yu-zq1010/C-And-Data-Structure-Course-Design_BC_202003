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
			if (P->clause[0] > 0 && i == MinNum(P->clause, F.LitNum))//当公式F的第i个文字的子句没有被删除且不为空,并且没有被输出
			{
				for (j = 1; j <= P->clause[0]; j++)//逐个输出子句内元素
				{
					printf("%d ", P->clause[j]);
				}
				printf("\n");
			}
			P = P->NextCla;
		}
	}
	printf("输出结束，已经输出所有CNF公式");
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

	if ((fp = fopen(filename, "w")) == NULL)//如果filename文件打开失败
	{
		return ERROR;
	}
	fprintf(fp, "%s", "p cnf ");//存放开始标志
	fprintf(fp, "%d ", Formula.LitNum);//存放文字数
	fprintf(fp, "%d\n", Formula.ClaNum);//存放子句数

	P = Formula.FirstClause;//指向第一个子句
	while (P != NULL)//遍历所有子句
	{
		for (i = 0;; i++)//逐个输出当前子句所有文字
		{
			if (P->ClauseValue[i] != 0)//若当前文字不为0
			{
				fprintf(fp, "%d ", P->ClauseValue[i]);//输出
			}
			else//若为0
			{
				break;//当前子句结束
			}
		}
		fprintf(fp, "%d\n", 0);//放入回车
		P = P->NextClause;//下一个子句
	}
	fclose(fp);//关闭文件
	return OK;
}

void SATSove_FileSave(char* filename, int s, long t, int NUM)
{
	char savefile[20] = { 0 };	int i = 0, S_len = 0;	FILE* fp = NULL;

	S_len = strlen(filename);//求出当前文件名长度
	for (i = 0; i < S_len - 3; i++)//将文件名复制到想要保存的文件名中，后三个字符即“CNF”不要
	{
		savefile[i] = filename[i];
	}
	savefile[i] = '\0';//放入结束标志
	strcat(savefile, "res");//放入res
	fp = fopen(savefile, "w");//打开想要写入的文件

	fprintf(fp, "%c", 's');//放入字符's'
	fprintf(fp, "%7d\n", s);//放入s的值，即问题有没有解

	if (s == 0)//若无解
	{
		fprintf(fp, "%c\n", 'v');//放入'v'字符
		fprintf(fp, "%c", 't');//放入't'字符
		fprintf(fp, "%7ld", t);//放入t的值
	}

	else if (s == 1)//若有解
	{
		fprintf(fp, "%c", 'v');//放入'v'字符

		if (VELUE[1] == 0)//为了回车数量，现先放入第一个字符，若第一个文字为假
		{
			fprintf(fp, "%7d", -1);//放入-1
		}
		else//若为真或不确定
		{
			fprintf(fp, "%7d", 1);//放入1
		}
		for (i = 2; i <= NUM; i++)//循环放入剩下文字的解
		{
			if (i % 10 == 1)//每隔10个文字换行
			{
				fprintf(fp,"%s","\n");
			}
			if (VELUE[i] == 0)
			{
				fprintf(fp, "%8d", -i);//为了对其，保存8个长度
			}
			else
			{
				fprintf(fp, "%8d", i);
			}
		}
		fprintf(fp, "\n%c", 't');//放入't'字符
		fprintf(fp, "%7ld", t);//放入t的值
	}
	fclose(fp);//关闭文件
	printf("已将结果保存到文件 %s 中", savefile);//输出提示
}