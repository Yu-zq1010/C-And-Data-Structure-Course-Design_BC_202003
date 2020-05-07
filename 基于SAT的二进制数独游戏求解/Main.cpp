#include"head.h"
#include<stdio.h>

int* VELUE = NULL;
int CHOOSE = 2;
int ConflicCla[100] = { 0 };
int ConflicNum = 1;
int* LearnCla[100] = { 0 };
int LearnNum = 0;
int Time = 0;
int Order = 0;

int main()
{
	int op_Menu = 1, op_SAT = 1, op_Puzzle = 1, op_CreatePuzzle = 1, i = 0, n = 0, tem[10] = { 0 }, * Puzzle = NULL, ** B = NULL;	CNF F, S;	clock_t Start = 0, Finish = 0, Duration = 0;	SATFormula Formula;		P_ClauseList P = NULL;	char filename[20] = { 0 }, temporary[10] = { 0 };
	while (op_Menu)//显示菜单界面
	{
		system("cls");	printf("\n\n");
		printf("       Menu for Binary Puzzle based on SAT problem \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. SATSolve         2. PuzzleSolve\n");
		printf("    	               0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("                    请选择你的操作[0~2]:");
		scanf("%d", &op_Menu);
		switch (op_Menu)
		{
		case 1://SAT问题求解
			op_SAT = 1;
			while (op_SAT)//SAT问题
			{
				system("cls");	printf("\n\n");//SAT问题菜单
				printf("               Menu for SAT problem solve \n");
				printf("------------------------------------------------------\n");
				printf("    	  1. ImportCNF         2. ExportCNF\n");
				printf("    	  3. DeleteCNF         4. DPLL\n");
				printf("    	               0. Back\n");
				printf("------------------------------------------------------\n");
				printf("                    请选择你的操作[0~4]:");
				scanf("%d", &op_SAT);
				switch (op_SAT)
				{
				case 1://输入CNF文件名称，导入CNF
					printf("请输入想验证的文件名：");
					scanf("%s", filename);

					if (CreateAdjacencyList(filename, F))
					{
						printf("创建邻接表成功");
					}
					else
					{
						printf("创建邻接表失败");
					}
					getchar(); getchar();
					break;//end of case 1

				case 2://输出CNF公式
					Copy(S, F);
					ExportCNF(S);
					DeleteCNF(S);
					getchar(); getchar();
					break;//end of case 2

				case 3://删除CNF公式
					DeleteCNF(F);
					printf("删除CNF公式成功");
					getchar(); getchar();
					break;//end of case 3

				case 4://求解SAT问题
					printf("请选择算法 :\n1 .时序回溯\n2.非时序回溯 + 字句学习 : ");
					scanf("%d", &n);
					printf("\n请选择选取办法 :\n1.没有赋值的第一个文字\n2.JW选取办法 : ");
					scanf("%d", &CHOOSE);
					switch (n)
					{
					case 1://时序回溯求解
						Copy(S, F);//复制F，创建副本S
						i = ExistSingle(S);//查找单子句
						Start = clock();//计时开始
						if (DPLL(S, i))//调用DPLL进行求解
						{
							Finish = clock();//计时结束
							printf("\n求解成功，当前SAT问题的解为：\n");
							for (i = 1; i <= S.LitNum; i++)//在屏幕上输出
							{
								printf("%d : %d\n", i, VELUE[i]);
							}
							Duration = Finish - Start;//计算所需时间
							printf("求解所用时间为 %ld 毫秒\n", Duration);
							SATSove_FileSave(filename, 1, Duration, S.LitNum);//问题答案文件保存
							DeleteCNF(S);//删除副本
							free(VELUE);
							VELUE = NULL;
						}
						else
						{
							Finish = clock();//计时结束
							printf("求解失败，当前SAT问题无解\n");
							Duration = Finish - Start;//计算求解时间
							printf("求解所用时间为 %ld 毫秒\n", Duration);
							SATSove_FileSave(filename, 0, Duration, S.LitNum);//文件保存
							DeleteCNF(S);
						}
						break;

					case 2://非时序回溯+子句学习求解
						Copy(S, F);//复制F，创建副本S
						Reversal(S);//翻转副本S
						for (i = 0; i < 100; i++)//准备工作，清空学习子句数组
						{
							if (LearnCla[i] != NULL)
							{
								free(LearnCla[i]);
								LearnCla[i] = NULL;
							}
						}
						for (i = 0; i < 100; i++)
						{
							ConflicCla[i] = 0;
						}
						i = BetterExistSingle(S);//查找单子句
						LearnNum = 0;
						ConflicNum = 1;
						Time = 0;

						Start = clock();//计时开始
						if (BetterDPLL(S, i, 1) > 0)//调用优化方法求解
						{
							Finish = clock();//计时结束
							printf("求解成功，当前SAT问题的解为：\n");
							for (i = 1; i <= S.LitNum; i++)//在屏幕上输出
							{
								printf("%d : %d\n", i, VELUE[i]);
							}
							Duration = Finish - Start;//计算求解时间
							printf("求解所用时间为 %ld 毫秒\n", Duration);
							SATSove_FileSave(filename, 1, Duration, S.LitNum);//文件保存
							DeleteCNF(S);//删除副本S
							free(VELUE);
							VELUE = NULL;
						}
						else
						{
							Finish = clock();//计时结束
							printf("求解失败，当前SAT问题无解\n");
							Duration = Finish - Start;//计算求解时间
							printf("求解所用时间为 %ld 毫秒\n", Duration);
							SATSove_FileSave(filename, 0, Duration, S.LitNum);//文件保存
							DeleteCNF(S);//删除副本S
						}
						break;
					default:
						printf("输入不合法");
						break;
					}
					getchar(); getchar();
					break;//end of case 4

				case 0:
					break;
				default:
					printf("请输入 0 ~ 4 之间的操作数");
					getchar(); getchar();
					break;
				}
			}
			break;

		case 2://数独问题求解
			op_Puzzle = 1;
			while (op_Puzzle)//数独问题
			{
				system("cls");	printf("\n\n");//数独问题菜单
				printf("              Menu for Binary Puzzle solve \n");
				printf("------------------------------------------------------\n");
				printf("    	  1. CreatePuzzle          2. CheckPuzzle\n");
				printf("    	  3. SolvePuzzle\n");
				printf("    	               0. Back\n");
				printf("------------------------------------------------------\n");
				printf("                    请选择你的操作[0~3]:");
				scanf("%d", &op_Puzzle);
				switch (op_Puzzle)
				{
				case 1://创建新数独
					op_CreatePuzzle = 1;
					while (op_CreatePuzzle)//创建数独
					{
						system("cls");	printf("\n\n");//创建数独菜单
						printf("               Menu for CreatePuzzle \n");
						printf("------------------------------------------------------\n");
						printf("    	         1. By yourselve\n");
						printf("         2. ComputerRandom(Base on Digging holes)\n");
						printf("    	             0. Back\n");
						printf("------------------------------------------------------\n");
						printf("                    请选择你的操作[0~2]:");
						scanf("%d", &op_CreatePuzzle);
						switch (op_CreatePuzzle)
						{
						case 1://用户自己输入数独
							//询问数独阶数
							printf("输入您想求解的数独阶数：");
							scanf("%d", &Order);
							if (Order % 2 != 0)
							{
								printf("输入不合法，请输入偶数阶数独");
								getchar(); getchar();
								break;
							}
							
							//准备
							B = Prepare();
							if (Puzzle != NULL)
							{
								free(Puzzle);
								Puzzle = 0;
							}
							if (!(Puzzle = (int*)calloc(Order * Order, sizeof(int))))
							{
								exit(OVERFLOW);
							}
							for (i = 0; i < Order * Order; i++)
							{
								Puzzle[i] = 0;
							}

							//输入用户想解决的数独
							printf("请输入原始数独，以 '0' 结尾：");
							scanf("%d", &tem[0]);//读取
							while (tem[0] != 0)//放入子句集和棋盘数Puzzle
							{
								AddClause(tem, 1, Formula);//添加进公式集
								if (tem[0] > 0)//若当前位置为1
								{
									//计算棋盘位置
									i = tem[0] % 10;
									n = (tem[0] - i) / 10;
									n = (n - 1) * Order + i - 1;
									Puzzle[n] = tem[0];//放入
								}
								else//若为0
								{
									//计算棋盘位置
									i = (-tem[0]) % 10;
									n = ((-tem[0]) - i) / 10;
									n = (n - 1) * Order + i - 1;
									Puzzle[n] = tem[0];//放入
								}
								scanf("%d", &tem[0]);
							}

							Constraint_1(Formula, B);
							Constraint_2(Formula, B);
							Constraint_3(Formula, B);
							Convert(Formula);

							//询问保存文件名称
							printf("请输入想保存的文件编号：");
							scanf("%s", temporary);
							strcpy(filename, "Puzzle_");
							strcat(filename, temporary);
							strcat(filename, ".cnf");
							if (PuzzleSAT_FileSave(Formula, filename))//调用函数保存
							{
								printf("已经成功创建数独CNF，并将其保存在文件 %s 中", filename);
							}

							//结束
							FormulaDelete(Formula);//删除子句集
							for (i = 0; i <= Order; i++)//释放准备数组B
							{
								free(B[i]);
							}
							free(B);
							B = NULL;
							op_CreatePuzzle = 0;//返回上级菜单
							getchar(); getchar();
							break;//end of case 1

						case 2://挖洞生成数独
							//询问数独阶数
							printf("输入您想求解的数独阶数（当前只支持6阶和8阶）：");
							scanf("%d", &Order);
							if (Order % 2 != 0)
							{
								printf("输入不合法，请输入偶数阶数独");
								getchar(); getchar();
								break;
							}

							//询问保存文件名称
							printf("请输入想保存的文件编号：");
							scanf("%s", temporary);
							strcpy(filename, "Puzzle_");
							strcat(filename, temporary);
							strcat(filename, ".cnf");

							//准备
							B = Prepare();
							if (Puzzle != NULL)
							{
								free(Puzzle);
								Puzzle = 0;
							}
							if (!(Puzzle = (int*)calloc(Order * Order, sizeof(int))))
							{
								exit(OVERFLOW);
							}
							for (i = 0; i < Order * Order; i++)
							{
								Puzzle[i] = -1;
							}

							while (!Las_vegas(Formula, B, Puzzle, filename));//利用拉斯维加斯算法不断尝试生成完整终局，并放入棋盘数组Puzzle带出
							DiggingHole(Formula, B, Puzzle, filename);//利用挖洞算法对终局进行挖洞，形成空局
							op_CreatePuzzle = 0;//返回上层菜单
							getchar(); getchar();
							break;//end of case 2

						case 0:
							break;
						default:
							printf("请输入 0 ~ 2之间的操作数");
							getchar(); getchar();
							break;
						}
					}
					break;
				case 2://查看当前数独
					printf("希望求解的数独为：\n");
					for (i = 0; i < Order * Order; i++)//逐个输出当前的数独棋盘
					{
						if (i % Order == 0)
						{
							printf("\n");
						}
						if (Puzzle[i] > 0)//若棋盘内容大于0
						{
							printf("1 ");//输出1
						}
						else if (Puzzle[i] < 0)//若小于0
						{
							printf("0 ");//输出0
						}
						else//若没有
						{
							printf("# ");//输出#
						}
					}
					getchar(); getchar();
					break;//end of case 2

				case 3://求解数独
					CHOOSE = 2;//默认选取办法为JW选取办法
					//解决问题
					CreateAdjacencyList(filename, F);
					Copy(S, F);
					Reversal(S);
					for (i = 0; i < 100; i++)
					{
						if (LearnCla[i] != NULL)
						{
							free(LearnCla[i]);
							LearnCla[i] = NULL;
						}
					}
					for (i = 0; i < 100; i++)
					{
						ConflicCla[i] = 0;
					}
					i = BetterExistSingle(S);
					LearnNum = 0;
					ConflicNum = 1;
					Time = 0;

					Start = clock();
					if (BetterDPLL(S, i, 1) > 0)
					{
						Finish = clock();
						printf("求解成功，当前数独的解为：\n");
						for (i = 1; i <= Order * Order; i++)
						{
							if (i % Order == 1)
							{
								printf("\n");
							}
							printf("%d ", VELUE[i]);
						}
						Duration = Finish - Start;
						printf("\n求解所用时间为 %ld 毫秒\n", Duration);
						SATSove_FileSave(filename, 1, Duration, S.LitNum);//保存文件
						DeleteCNF(S);
						free(VELUE);
						VELUE = NULL;
					}
					else
					{
						Finish = clock();
						printf("求解失败，当前数独无解\n");
						Duration = Finish - Start;
						printf("求解所用时间为 %ld 毫秒\n", Duration);
						SATSove_FileSave(filename, 0, Duration, S.LitNum);
						DeleteCNF(S);
					}
					getchar(); getchar();
					break;//end of case 3

				case 0:
					break;
				default:
					printf("请输入 0 ~ 3 之间的操作数");
					getchar(); getchar();
					break;
				}
			}
			break;

		case 0:
			break;
		default:
			printf("请输入 0 ~ 4 之间的操作数");
			getchar(); getchar();
			break;
		}
	}
}
