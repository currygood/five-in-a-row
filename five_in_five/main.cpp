#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>

//进度：1.怎么新创建一个窗口	

int count_all=0;
//各选手占据的位置记录，也是为了方便判断谁连了5个：     1是占据了，0是没  
char player1[10][10] = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0} };      
char player2[10][10] = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0} };

int test_over();
void init();
bool isEmpty(int x, int y);
void put_other_WarnWindows();

int main()
{
	int i, j, count=1, memory_x, memory_y;
	init();
	ExMessage m;
	while (1)
	{
		peekmessage(&m, EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN)
		{
			if (count % 2 == 0)
			{
				continue;
			}
			for (i = 0; i < 10; i++)
			{
				if (m.x > i * 80 && m.x < (i + 1) * 80)
				{
					memory_x = i;
				}
				if(m.y > i * 80 && m.y < (i + 1) * 80)
				{
					memory_y = i;
				}
			}
			if (isEmpty(memory_x, memory_y)==false)
			{
				continue;
			}
			count++;
			count_all++;
			player1[memory_x][memory_y] = 1;
			circle((memory_x * 80 + (memory_x + 1) * 80)/2, (memory_y * 80 + (memory_y + 1) * 80)/2, 30);
		}
		if (m.message == WM_RBUTTONDOWN)
		{
			if (count % 2 != 0)
			{
				continue;
			}
			for (i = 0; i < 10; i++)
			{
				if (m.x > i * 80 && m.x < (i + 1) * 80)
				{
					memory_x = i;
				}
				if (m.y > i * 80 && m.y < (i + 1) * 80)
				{
					memory_y = i;
				}
			}
			if (isEmpty(memory_x, memory_y) == false)
			{
				continue;
			}
			count++;
			count_all++;
			player2[memory_x][memory_y] = 1;
			line((memory_x * 80 + (memory_x + 1) * 80)/ 2 - 30, (memory_y * 80 + (memory_y + 1) * 80)/2 - 30, (memory_x * 80 + (memory_x + 1) * 80)/2 + 30, (memory_y * 80 + (memory_y + 1) * 80) / 2 + 30);
			line((memory_x * 80 + (memory_x + 1) * 80) / 2 - 30, (memory_y * 80 + (memory_y + 1) * 80) / 2 + 30, (memory_x * 80 + (memory_x + 1) * 80) / 2 + 30, (memory_y * 80 + (memory_y + 1) * 80) / 2 - 30);
		}
		if (test_over() == 1)
		{
			printf("Player1 win!\n");
			break;
		}
		else if (test_over() == 2)
		{
			printf("Player2 win!\n");
			break;
		}
		else if (test_over() == 3)
		{
			printf("Dead heat!\n");
			break;
		}
	}
	Sleep(2000);
	closegraph();
	return 0;
}

int test_over()
{
	int i, j,k,l;  //i,j判断横竖的。k，l用于判断斜着的是否5个相连
	int memory_x1 = 0;     //1,2是选手序号
	int memory_y1 = 0;
	int memory_x2 = 0;
	int memory_y2 = 0;
	int memory_1right_oblique = 0;   //bolique 是斜着的
	int memory_1left_oblique = 0;
	int memory_2right_oblique = 0;
	int memory_2left_oblique = 0;
	//   这个是‘\’ 反斜杠
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = i, l = j; k < 10, l < 10; k++, l++)
			{   //选手1
				if (player1[k][l] == 1)
				{
					memory_1left_oblique++;
					if (memory_1left_oblique == 5)
					{
						return 1;
					}
				}
				if (player1[k][l] != 1)
				{
					memory_1left_oblique = 0;
				}
				//选手2
				if (player2[k][l] == 1)
				{
					memory_2left_oblique++;
					if (memory_2left_oblique == 5)
					{
						return 2;
					}
				}
				if (player2[k][l] != 1)
				{
					memory_2left_oblique = 0;
				}
			}
		}
	}
	//   这个是‘/’ 斜杠
	for (i = 10; i > 3; i--)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = i, l = j; k >= 0, l < 10; k--, l++)
			{
				//选手1
				if (player1[k][l] == 1)
				{
					memory_1right_oblique++;
					if (memory_1right_oblique == 5)
					{
						return 1;
					}
				}
				if (player1[k][l] != 1)
				{
					memory_1right_oblique = 0;
				}
				//选手2
				if (player2[k][l] == 1)
				{
					memory_2right_oblique++;
					if (memory_2right_oblique == 5)
					{
						return 2;
					}
				}
				if (player2[k][l] != 1)
				{
					memory_2right_oblique = 0;
				}
			}
		}
	}
	//这个是横竖
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//player1  win?
			if (player1[i][j] == 1)
			{
				memory_y1 += 1;
				if (memory_y1 == 5)
				{
					return 1;
				}
			}
			if (player1[j][i] == 1)
			{
				memory_x1 += 1;
				if (memory_x1 == 5)
				{
					return 1;
				}
			}
			if (player1[i][j] != 1)
			{
				memory_y1 = 0;
			}
			if (player1[j][i] != 1)
			{
				memory_x1 = 0;
			}

			//player2  win?
			if (player2[i][j] == 1)
			{
				memory_y2 += 1;
				if (memory_y2 == 5)
				{
					return 2;
				}
			}
			if (player2[j][i] == 1)
			{
				memory_x2 += 1;
				if (memory_x2 == 5)
				{
					return 2;
				}
			}
			if (player2[i][j] != 1)
			{
				memory_y2 = 0;
			}
			if (player2[j][i] != 1)
			{
				memory_x2 = 0;
			}
		}
	}
	if (count_all == 100)
	{
		return 3;
	}
}

void init()
{
	initgraph(801, 801, EX_SHOWCONSOLE);
	setlinecolor(RED);
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			rectangle(0, 0, 80 * (j + 1), 80 * (i + 1));
		}
	}
}

bool isEmpty(int x,int y)
{
	if (player1[x][y]==1||player2[x][y]==1)
	{
		put_other_WarnWindows();
		return false;
	}
	else
	{
		return true;
	}
}

void put_other_WarnWindows()
{
	printf("You can't put your chess in used!\n");
}