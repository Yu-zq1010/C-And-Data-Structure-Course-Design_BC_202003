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
	while (op_Menu)//��ʾ�˵�����
	{
		system("cls");	printf("\n\n");
		printf("       Menu for Binary Puzzle based on SAT problem \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. SATSolve         2. PuzzleSolve\n");
		printf("    	               0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("                    ��ѡ����Ĳ���[0~2]:");
		scanf("%d", &op_Menu);
		switch (op_Menu)
		{
		case 1://SAT�������
			op_SAT = 1;
			while (op_SAT)//SAT����
			{
				system("cls");	printf("\n\n");//SAT����˵�
				printf("               Menu for SAT problem solve \n");
				printf("------------------------------------------------------\n");
				printf("    	  1. ImportCNF         2. ExportCNF\n");
				printf("    	  3. DeleteCNF         4. DPLL\n");
				printf("    	               0. Back\n");
				printf("------------------------------------------------------\n");
				printf("                    ��ѡ����Ĳ���[0~4]:");
				scanf("%d", &op_SAT);
				switch (op_SAT)
				{
				case 1://����CNF�ļ����ƣ�����CNF
					printf("����������֤���ļ�����");
					scanf("%s", filename);

					if (CreateAdjacencyList(filename, F))
					{
						printf("�����ڽӱ�ɹ�");
					}
					else
					{
						printf("�����ڽӱ�ʧ��");
					}
					getchar(); getchar();
					break;//end of case 1

				case 2://���CNF��ʽ
					Copy(S, F);
					ExportCNF(S);
					DeleteCNF(S);
					getchar(); getchar();
					break;//end of case 2

				case 3://ɾ��CNF��ʽ
					DeleteCNF(F);
					printf("ɾ��CNF��ʽ�ɹ�");
					getchar(); getchar();
					break;//end of case 3

				case 4://���SAT����
					printf("��ѡ���㷨 :\n1 .ʱ�����\n2.��ʱ����� + �־�ѧϰ : ");
					scanf("%d", &n);
					printf("\n��ѡ��ѡȡ�취 :\n1.û�и�ֵ�ĵ�һ������\n2.JWѡȡ�취 : ");
					scanf("%d", &CHOOSE);
					switch (n)
					{
					case 1://ʱ��������
						Copy(S, F);//����F����������S
						i = ExistSingle(S);//���ҵ��Ӿ�
						Start = clock();//��ʱ��ʼ
						if (DPLL(S, i))//����DPLL�������
						{
							Finish = clock();//��ʱ����
							printf("\n���ɹ�����ǰSAT����Ľ�Ϊ��\n");
							for (i = 1; i <= S.LitNum; i++)//����Ļ�����
							{
								printf("%d : %d\n", i, VELUE[i]);
							}
							Duration = Finish - Start;//��������ʱ��
							printf("�������ʱ��Ϊ %ld ����\n", Duration);
							SATSove_FileSave(filename, 1, Duration, S.LitNum);//������ļ�����
							DeleteCNF(S);//ɾ������
							free(VELUE);
							VELUE = NULL;
						}
						else
						{
							Finish = clock();//��ʱ����
							printf("���ʧ�ܣ���ǰSAT�����޽�\n");
							Duration = Finish - Start;//�������ʱ��
							printf("�������ʱ��Ϊ %ld ����\n", Duration);
							SATSove_FileSave(filename, 0, Duration, S.LitNum);//�ļ�����
							DeleteCNF(S);
						}
						break;

					case 2://��ʱ�����+�Ӿ�ѧϰ���
						Copy(S, F);//����F����������S
						Reversal(S);//��ת����S
						for (i = 0; i < 100; i++)//׼�����������ѧϰ�Ӿ�����
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
						i = BetterExistSingle(S);//���ҵ��Ӿ�
						LearnNum = 0;
						ConflicNum = 1;
						Time = 0;

						Start = clock();//��ʱ��ʼ
						if (BetterDPLL(S, i, 1) > 0)//�����Ż��������
						{
							Finish = clock();//��ʱ����
							printf("���ɹ�����ǰSAT����Ľ�Ϊ��\n");
							for (i = 1; i <= S.LitNum; i++)//����Ļ�����
							{
								printf("%d : %d\n", i, VELUE[i]);
							}
							Duration = Finish - Start;//�������ʱ��
							printf("�������ʱ��Ϊ %ld ����\n", Duration);
							SATSove_FileSave(filename, 1, Duration, S.LitNum);//�ļ�����
							DeleteCNF(S);//ɾ������S
							free(VELUE);
							VELUE = NULL;
						}
						else
						{
							Finish = clock();//��ʱ����
							printf("���ʧ�ܣ���ǰSAT�����޽�\n");
							Duration = Finish - Start;//�������ʱ��
							printf("�������ʱ��Ϊ %ld ����\n", Duration);
							SATSove_FileSave(filename, 0, Duration, S.LitNum);//�ļ�����
							DeleteCNF(S);//ɾ������S
						}
						break;
					default:
						printf("���벻�Ϸ�");
						break;
					}
					getchar(); getchar();
					break;//end of case 4

				case 0:
					break;
				default:
					printf("������ 0 ~ 4 ֮��Ĳ�����");
					getchar(); getchar();
					break;
				}
			}
			break;

		case 2://�����������
			op_Puzzle = 1;
			while (op_Puzzle)//��������
			{
				system("cls");	printf("\n\n");//��������˵�
				printf("              Menu for Binary Puzzle solve \n");
				printf("------------------------------------------------------\n");
				printf("    	  1. CreatePuzzle          2. CheckPuzzle\n");
				printf("    	  3. SolvePuzzle\n");
				printf("    	               0. Back\n");
				printf("------------------------------------------------------\n");
				printf("                    ��ѡ����Ĳ���[0~3]:");
				scanf("%d", &op_Puzzle);
				switch (op_Puzzle)
				{
				case 1://����������
					op_CreatePuzzle = 1;
					while (op_CreatePuzzle)//��������
					{
						system("cls");	printf("\n\n");//���������˵�
						printf("               Menu for CreatePuzzle \n");
						printf("------------------------------------------------------\n");
						printf("    	         1. By yourselve\n");
						printf("         2. ComputerRandom(Base on Digging holes)\n");
						printf("    	             0. Back\n");
						printf("------------------------------------------------------\n");
						printf("                    ��ѡ����Ĳ���[0~2]:");
						scanf("%d", &op_CreatePuzzle);
						switch (op_CreatePuzzle)
						{
						case 1://�û��Լ���������
							//ѯ����������
							printf("����������������������");
							scanf("%d", &Order);
							if (Order % 2 != 0)
							{
								printf("���벻�Ϸ���������ż��������");
								getchar(); getchar();
								break;
							}
							
							//׼��
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

							//�����û�����������
							printf("������ԭʼ�������� '0' ��β��");
							scanf("%d", &tem[0]);//��ȡ
							while (tem[0] != 0)//�����Ӿ伯��������Puzzle
							{
								AddClause(tem, 1, Formula);//��ӽ���ʽ��
								if (tem[0] > 0)//����ǰλ��Ϊ1
								{
									//��������λ��
									i = tem[0] % 10;
									n = (tem[0] - i) / 10;
									n = (n - 1) * Order + i - 1;
									Puzzle[n] = tem[0];//����
								}
								else//��Ϊ0
								{
									//��������λ��
									i = (-tem[0]) % 10;
									n = ((-tem[0]) - i) / 10;
									n = (n - 1) * Order + i - 1;
									Puzzle[n] = tem[0];//����
								}
								scanf("%d", &tem[0]);
							}

							Constraint_1(Formula, B);
							Constraint_2(Formula, B);
							Constraint_3(Formula, B);
							Convert(Formula);

							//ѯ�ʱ����ļ�����
							printf("�������뱣����ļ���ţ�");
							scanf("%s", temporary);
							strcpy(filename, "Puzzle_");
							strcat(filename, temporary);
							strcat(filename, ".cnf");
							if (PuzzleSAT_FileSave(Formula, filename))//���ú�������
							{
								printf("�Ѿ��ɹ���������CNF�������䱣�����ļ� %s ��", filename);
							}

							//����
							FormulaDelete(Formula);//ɾ���Ӿ伯
							for (i = 0; i <= Order; i++)//�ͷ�׼������B
							{
								free(B[i]);
							}
							free(B);
							B = NULL;
							op_CreatePuzzle = 0;//�����ϼ��˵�
							getchar(); getchar();
							break;//end of case 1

						case 2://�ڶ���������
							//ѯ����������
							printf("������������������������ǰֻ֧��6�׺�8�ף���");
							scanf("%d", &Order);
							if (Order % 2 != 0)
							{
								printf("���벻�Ϸ���������ż��������");
								getchar(); getchar();
								break;
							}

							//ѯ�ʱ����ļ�����
							printf("�������뱣����ļ���ţ�");
							scanf("%s", temporary);
							strcpy(filename, "Puzzle_");
							strcat(filename, temporary);
							strcat(filename, ".cnf");

							//׼��
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

							while (!Las_vegas(Formula, B, Puzzle, filename));//������˹ά��˹�㷨���ϳ������������վ֣���������������Puzzle����
							DiggingHole(Formula, B, Puzzle, filename);//�����ڶ��㷨���վֽ����ڶ����γɿվ�
							op_CreatePuzzle = 0;//�����ϲ�˵�
							getchar(); getchar();
							break;//end of case 2

						case 0:
							break;
						default:
							printf("������ 0 ~ 2֮��Ĳ�����");
							getchar(); getchar();
							break;
						}
					}
					break;
				case 2://�鿴��ǰ����
					printf("ϣ����������Ϊ��\n");
					for (i = 0; i < Order * Order; i++)//��������ǰ����������
					{
						if (i % Order == 0)
						{
							printf("\n");
						}
						if (Puzzle[i] > 0)//���������ݴ���0
						{
							printf("1 ");//���1
						}
						else if (Puzzle[i] < 0)//��С��0
						{
							printf("0 ");//���0
						}
						else//��û��
						{
							printf("# ");//���#
						}
					}
					getchar(); getchar();
					break;//end of case 2

				case 3://�������
					CHOOSE = 2;//Ĭ��ѡȡ�취ΪJWѡȡ�취
					//�������
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
						printf("���ɹ�����ǰ�����Ľ�Ϊ��\n");
						for (i = 1; i <= Order * Order; i++)
						{
							if (i % Order == 1)
							{
								printf("\n");
							}
							printf("%d ", VELUE[i]);
						}
						Duration = Finish - Start;
						printf("\n�������ʱ��Ϊ %ld ����\n", Duration);
						SATSove_FileSave(filename, 1, Duration, S.LitNum);//�����ļ�
						DeleteCNF(S);
						free(VELUE);
						VELUE = NULL;
					}
					else
					{
						Finish = clock();
						printf("���ʧ�ܣ���ǰ�����޽�\n");
						Duration = Finish - Start;
						printf("�������ʱ��Ϊ %ld ����\n", Duration);
						SATSove_FileSave(filename, 0, Duration, S.LitNum);
						DeleteCNF(S);
					}
					getchar(); getchar();
					break;//end of case 3

				case 0:
					break;
				default:
					printf("������ 0 ~ 3 ֮��Ĳ�����");
					getchar(); getchar();
					break;
				}
			}
			break;

		case 0:
			break;
		default:
			printf("������ 0 ~ 4 ֮��Ĳ�����");
			getchar(); getchar();
			break;
		}
	}
}
