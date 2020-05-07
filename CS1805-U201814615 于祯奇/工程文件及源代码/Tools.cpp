#include"head.h"

void Reversal(CNF& F)
{
	int i = 0, j = 0;	ClaNode* P = NULL;
	for (i = 1; i <= 2 * F.LitNum; i++)
	{
		P = F.Letters[i].FirstCla;
		while (P != NULL)
		{
			for (j = 1; j <= P->ClaNum; j++)
			{
				if (P->clause[j] < 0)
				{
					P->clause[j] = F.LitNum - P->clause[j];
				}
			}
			P = P->NextCla;
		}
	}
}

status Opposite_SAT(int LitNum, int Key)
{
	if (Key <= LitNum)
	{
		Key = Key + LitNum;
	}
	else
	{
		Key = Key - LitNum;
	}
	return Key;
}


int NotSameNum(int* N, int n)
{
	int i = 0;
	for (i = 1; i < n; i++)
	{
		if (N[i] == N[n])
		{
			return FALSE;
		}
	}
	return TRUE;
}