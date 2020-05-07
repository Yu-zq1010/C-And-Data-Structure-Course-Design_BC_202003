#include"head.h"

extern int Time;

status Choose_1(CNF F)
{
	int i = 0;
	for (i = 1; i <= 2 * F.LitNum; i++)//遍历每个文字
	{
		if (F.Letters[i].value == Undefine)//如果该文字没有被赋值
		{
			return i;//返回该文字的序号
		}
	}
}

status Choose_2(CNF F)
{
	int i = 0, Need = 0;	double n = 0, J = 0, Jmax = 0;	ClaNode* P = NULL;
	for (i = 1; i <= 2 * F.LitNum; i++)//遍历每个文字
	{
		if (F.Letters[i].value == Undefine)//如果该文字没有被赋值
		{
			J = 0;
			P = F.Letters[i].FirstCla;//P指向文字的第一个子句
			while (P != NULL)//当存在子句时
			{
				if (P->clause[0] > 0)//当子句没有被删除或不为空
				{
					n = pow(2, -P->clause[0]);//n为2的负当前子句数目次方
					J = J + n;//J的值为所有子句n值的和
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