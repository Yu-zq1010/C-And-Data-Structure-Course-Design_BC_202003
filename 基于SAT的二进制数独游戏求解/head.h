#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define Undefine -1
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DELETE -1
#define MaxLearnClaNum 31

typedef int status;

/*--------------------CNF��ʽ�Ĵ洢��ʾ-----------------*/
typedef struct ClaNode {
	int* clause = NULL;//���������ֵ��Ӿ�,�������ʾ����
	int ClaNum = 0;
	struct ClaNode* NextCla = NULL;//ָ����һ���Ӿ�
}ClaNode;

typedef struct Litnode {
	int value = Undefine;//�����ֵ���ֵ��1Ϊ�棬0Ϊ�٣�-1Ϊδ��ֵ
	int Deep = 0;//���ֵľ�����ȣ����ڳ�ͻѧϰ
	ClaNode* CLA = NULL;
	ClaNode* FirstCla = NULL;//ָ����������ֵĵ�һ���Ӿ�
}Litnode, * LitList;

typedef struct CNFType {
	LitList Letters = NULL;//�������飬��̬����ռ�
	int LitNum = 0, ClaNum = 0;//��ʽ�е����������Ӿ���
}CNF;
/*----------------------end------------------------*/

/*----------����������ת���ɵ�SAT��ʽ�洢�ṹ--------*/
typedef struct P_ClauseNode {
	int ClauseValue[10] = { 0 };//�Ӿ�����
	P_ClauseNode* NextClause = NULL;//ָ����һ���Ӿ�
}P_ClauseNode, * P_ClauseList;

typedef struct SATFormula {
	P_ClauseList FirstClause = NULL;//ָ���һ���Ӿ�
	int LitNum = 0;//�Ӿ��������Ŀ
	int ClaNum = 0;//�Ӿ���Ӿ���Ŀ
}SATFormula;
/*----------------------end------------------------*/

/*---------------------��������--------------------*/
status CreateAdjacencyList(char* filename, CNF& F);//����CNF��ʽ
void ExportCNF(CNF F);//����ڲ��ṹ���ȶ���ȷ��
status DPLL(CNF F, int i);//DPLL�㷨
void BCP(CNF& F, int i);//����Լ������
status Choose_1(CNF F);//��һ��ѡ�����
status Choose_2(CNF F);//�ڶ���ѡ����ԣ�JWѡ����� 
void DeleteCNF(CNF& F);//ɾ����ʽ
void SATSove_FileSave(char* filename, int s, long t, int NUM);//����Ϊ.res�ļ�

			/*--------��ʱ����� �Ӿ�ѧϰ----------*/
status BetterDPLL(CNF& F, int i, int Deep);//�Ż�DPLL�㷨
void BetterBCP(CNF& F, int i, int Deep);//�Ż�����Լ������
void Reversal(CNF& F);//��ת
status BetterExistSingle(CNF F);//��֤F����û�е��Ӿ���ڣ����򷵻���ֵ��û�з���FALSE
status BetterEmptyCla(CNF F, int Key);//��֤�Ƿ��п��Ӿ�
void BetterCopy(CNF& S, CNF F);//�Ż�����ʹ�õĸ��ƺ���
void SearchConflic(CNF F, ClaNode* P, int key);
void AddLearnCla(CNF& F);//��ѧϰ�Ӿ���ӵ�F��
/*-------���ߺ���-------*/
int MinNum(int* N, int m);//�ҵ�����N������ �� ��Сֵ ��
int BetterMinNum(CNF F, int ClaNum, int* N);//�Ż�����ʹ�õĲ���������Сֵ
void Copy(CNF& S, CNF F);//����ʽF�����ݸ��Ƹ�S���浱ǰ״̬
status ExistSingle(CNF F);//��֤F����û�е��Ӿ���ڣ����򷵻���ֵ��û�з���FALSE
status EmptyCNF(CNF F);//��֤��ʽ�Ƿ�Ϊ��
status EmptyCla(CNF F, int Key);//��֤�Ƿ��п��Ӿ�
int NotSameNum(int* N, int n);//��֤����N���ڵ�n����֮ǰ��û��������ȵ���
status NotSameCla(ClaNode* P, ClaNode* N);//��֤�Ƿ��������Ӿ����
status Opposite_SAT(int LitNum, int Key);//��keyֵȡ�෴

/*-------------------������⺯��----------------*/
int** Prepare();//׼�������һ��Ŀ���ά����
void Constraint_1(SATFormula& Formula, int** B);//Լ��1
void Constraint_2(SATFormula& Formula, int** B);//Լ��2
void Constraint_3(SATFormula& Formula, int** B);//Լ��3
void Convert(SATFormula& Formula);//ת����������ij��ʽת��Ϊ������ʽ
status Las_vegas(SATFormula& Formula, int** B, int* Puzzle, char* filename);//��˹ά��˹�㷨��������������������
void DiggingHole(SATFormula& Formula, int** B, int* Puzzle,char* filename);//�ڶ���������
void ExportSAT(SATFormula Formula);//�������Ĺ�ʽ
status PuzzleSAT_FileSave(SATFormula Formula, char* filename);//�����ʽ���ļ���
void FormulaDelete(SATFormula& Formula);//ɾ������Ĺ�ʽ
/*-------���ߺ���-------*/
void Combine(int s[], int n, int k, SATFormula& Formula, void (*Print)(int* Subset, SATFormula& Formula));//Լ��2�н�����Ϻ���
void Print_AddCla(int* Subset, SATFormula& Formula);//��ѡȡ��������Ϻ�����ӵ���ʽ����
void AddClause(int* Subset, int n, SATFormula& Formula);//��ѡȡ�������Ӿ���ӵ���ʽ����
/*------------------end-----------------------*/