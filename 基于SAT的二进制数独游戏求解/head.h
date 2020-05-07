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

/*--------------------CNF公式的存储表示-----------------*/
typedef struct ClaNode {
	int* clause = NULL;//包涵该文字的子句,以数组表示数据
	int ClaNum = 0;
	struct ClaNode* NextCla = NULL;//指向下一个子句
}ClaNode;

typedef struct Litnode {
	int value = Undefine;//该文字的真值，1为真，0为假，-1为未赋值
	int Deep = 0;//文字的决策深度，用于冲突学习
	ClaNode* CLA = NULL;
	ClaNode* FirstCla = NULL;//指向包含该文字的第一条子句
}Litnode, * LitList;

typedef struct CNFType {
	LitList Letters = NULL;//文字数组，动态分配空间
	int LitNum = 0, ClaNum = 0;//公式中的文字数和子句数
}CNF;
/*----------------------end------------------------*/

/*----------二进制数独转化成的SAT公式存储结构--------*/
typedef struct P_ClauseNode {
	int ClauseValue[10] = { 0 };//子句数组
	P_ClauseNode* NextClause = NULL;//指向下一个子句
}P_ClauseNode, * P_ClauseList;

typedef struct SATFormula {
	P_ClauseList FirstClause = NULL;//指向第一个子句
	int LitNum = 0;//子句的文字数目
	int ClaNum = 0;//子句的子句数目
}SATFormula;
/*----------------------end------------------------*/

/*---------------------函数声明--------------------*/
status CreateAdjacencyList(char* filename, CNF& F);//创建CNF公式
void ExportCNF(CNF F);//输出内部结构，比对正确性
status DPLL(CNF F, int i);//DPLL算法
void BCP(CNF& F, int i);//布尔约束传播
status Choose_1(CNF F);//第一个选择策略
status Choose_2(CNF F);//第二个选择策略，JW选择策略 
void DeleteCNF(CNF& F);//删除公式
void SATSove_FileSave(char* filename, int s, long t, int NUM);//保存为.res文件

			/*--------非时序回溯 子句学习----------*/
status BetterDPLL(CNF& F, int i, int Deep);//优化DPLL算法
void BetterBCP(CNF& F, int i, int Deep);//优化布尔约束传播
void Reversal(CNF& F);//翻转
status BetterExistSingle(CNF F);//验证F中有没有单子句存在，有则返回其值，没有返回FALSE
status BetterEmptyCla(CNF F, int Key);//验证是否有空子句
void BetterCopy(CNF& S, CNF F);//优化函数使用的复制函数
void SearchConflic(CNF F, ClaNode* P, int key);
void AddLearnCla(CNF& F);//将学习子句添加到F中
/*-------工具函数-------*/
int MinNum(int* N, int m);//找到数组N包含的 “ 最小值 ”
int BetterMinNum(CNF F, int ClaNum, int* N);//优化函数使用的查找数组最小值
void Copy(CNF& S, CNF F);//将公式F的内容复制给S保存当前状态
status ExistSingle(CNF F);//验证F中有没有单子句存在，有则返回其值，没有返回FALSE
status EmptyCNF(CNF F);//验证公式是否为空
status EmptyCla(CNF F, int Key);//验证是否有空子句
int NotSameNum(int* N, int n);//验证数组N中在第n个数之前有没有与其相等的数
status NotSameCla(ClaNode* P, ClaNode* N);//验证是否有两个子句相等
status Opposite_SAT(int LitNum, int Key);//将key值取相反

/*-------------------数独求解函数----------------*/
int** Prepare();//准备，填充一个目标二维数组
void Constraint_1(SATFormula& Formula, int** B);//约束1
void Constraint_2(SATFormula& Formula, int** B);//约束2
void Constraint_3(SATFormula& Formula, int** B);//约束3
void Convert(SATFormula& Formula);//转换函数，将ij形式转换为数字形式
status Las_vegas(SATFormula& Formula, int** B, int* Puzzle, char* filename);//拉斯维加斯算法，用于随机生成完整棋局
void DiggingHole(SATFormula& Formula, int** B, int* Puzzle,char* filename);//挖洞生成数独
void ExportSAT(SATFormula Formula);//输出保存的公式
status PuzzleSAT_FileSave(SATFormula Formula, char* filename);//输出公式到文件中
void FormulaDelete(SATFormula& Formula);//删除保存的公式
/*-------工具函数-------*/
void Combine(int s[], int n, int k, SATFormula& Formula, void (*Print)(int* Subset, SATFormula& Formula));//约束2中进行组合函数
void Print_AddCla(int* Subset, SATFormula& Formula);//将选取出来的组合函数添加到公式集里
void AddClause(int* Subset, int n, SATFormula& Formula);//将选取出来的子句添加到公式集里
/*------------------end-----------------------*/