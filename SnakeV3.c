/*---------------------------------------------------------------- 
// 版权所有。  
// 
// 文件名： SnakeV3.c 
// 文件功能描述：贪吃蛇v3 
// author：Magic激流 
// 时间：2018-8-10 
//----------------------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#define WIDTH 60	//宽 
#define HEIGHT 30	//高 
#define SPACE 0
#define NODE 1
#define FOOD 2
#define WALL 3

typedef struct {
	int x;
	int y;
}Place;		//坐标 

typedef struct node{
	Place place;
	struct node *next;
}Node;		//节点 

typedef struct snake{
	Node *head;
	int size;	//长度 
}Snake;		//指向一条蛇 

typedef Place Food;

Snake snake;
Food food = {0,0};
int length = -1;
int score = -10;
int speed = 250;

void Pos(int x, int y);
void Information();
void Initialize(Snake *psnake);
void PrintIn(int size,int x,int y);
void CreateMap(void);
void AfterEatFood();
bool InitializeSnake(Snake *psnake);
void CreateFood(void);
void AddNode(Snake *psnake);
void RenewSnake(Snake *psnake); 
Node * GetTail(Snake *psnake);
bool ThroughWall(Snake *psnake);
bool BiteItself(Snake *psnake); 
void RunGame(void);

int main (void)
{
	Initialize(&snake);
	system("mode con cols=95 lines=40");
	Information();
	CreateMap();
	
	if(InitializeSnake(&snake) == false)
	{
		Pos(25,10);
		printf("初始化蛇身错误！");
		exit(0);
	}
	CreateFood();
	
	RunGame();
	
	return 0;
}

void Pos(int x, int y)
{
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void PrintIn(int size,int x,int y)
{
	//size
	//清除节点：0	打印蛇身：1		
	//打印食物：2	打印墙壁：3 
	char *arr[4] = {" ","⊙","●","■"};
	Pos(x,y);
	printf("%s",arr[size]);
}

void Information()
{
	Pos(WIDTH/3,HEIGHT/3);
	printf("这是由链表构成的贪吃蛇，由 w s a d （小写）控制方向");
	Pos(WIDTH/3,HEIGHT/3+2);
	printf("详细代码和模块可访问我的博客园：");
	Pos(WIDTH/3,HEIGHT/3+4);
	printf("用户名：Magic激流  http://www.cnblogs.com/magicxyx/");
	Pos(WIDTH/3,HEIGHT/3+6);
	printf("如发现bug或者有其他想法的，也可发送至我的邮箱：");
	Pos(WIDTH/3,HEIGHT/3+8);
	printf("www.magic_xyx@foxmail.com");
	Pos(WIDTH/3,HEIGHT/3+10);
	printf("进入游戏前请切换成英文输入");
	Pos(WIDTH/3,HEIGHT/3+12);
	system("pause"); 
	system("cls");
	Pos(WIDTH+10,HEIGHT-20);
	printf("长度：3 + 0 ");
	Pos(WIDTH+10,HEIGHT-18);
	printf("分数：0");
	Pos(WIDTH+10,HEIGHT-16);
	printf("速度：0"); 
	Pos(WIDTH+10,HEIGHT-14);
	printf("按空格键暂停");
	Pos(WIDTH+5,HEIGHT-12);
	printf("按任意方向键(非反方向)继续"); 	
}

void AfterEatFood()
{
	Pos(WIDTH+20,HEIGHT-20);
    printf("%d = %d",++length,snake.size);
	Pos(WIDTH+16,HEIGHT-18);
    if(speed>150)
    	score += 10;
    else
    	score += 20;
	printf("%d",score);
    if(speed>100)
    	speed-=5;
    Pos(WIDTH+16,HEIGHT-16);
    printf("%d",speed);
}

void CreateMap(void)
{
	int i;
	for(i=0;i<WIDTH;i+=2)// 上下30 宽 
	{
		PrintIn(WALL,i,0);
		PrintIn(WALL,i,HEIGHT-1);
	}
	for(i=1;i<HEIGHT-1;i++)//左右 28+2 高 
	{
		PrintIn(WALL,0,i);
		PrintIn(WALL,WIDTH-2,i);
	}
}

bool InitializeSnake(Snake *psnake)
{
	Node *pnew;
	Node *scan;
	 
	for(int i = 0;i<3;i++)
	{
		scan = (psnake->head);
		pnew = (Node *)malloc(sizeof(Node));
		if(pnew == NULL)
		{
			printf("pnew == NULL");
			system("pause");
			return false; 
		}
		pnew->place.x = 28-2*i;
		pnew->place.y = 14;
		pnew->next = NULL;
		psnake->size++;
		PrintIn(NODE,pnew->place.x,pnew->place.y);
		if(scan == NULL)
			 psnake->head = pnew;
		else
		{
			while(scan->next != NULL)
				scan = scan->next;
			scan->next = pnew;
		}
	}
	return true;
}

void Initialize(Snake *psnake)
{
	psnake->head = NULL;
	psnake->size = 0;
}

void CreateFood(void)
{ 
	int flag = 0;
	srand((unsigned int)time(0));
    while(1)
    {
    	do{
        	food.x = rand()%(WIDTH-5)+2;
        }while(food.x%2!=0);
		food.y = rand()%(HEIGHT-2)+1;
        Node *scan = snake.head;
        while(scan !=NULL)
        {
        	if(scan->place.x == food.x &&
				scan->place.y == food.y)
				{
					flag = -1;
					break;
				}
        	scan = scan->next;
		}
        if(flag>=0)
        {
        	PrintIn(FOOD,food.x,food.y);
            break;
        }
    }
    AfterEatFood();
}

Node * GetTail(Snake *psnake)
{
	Node *scan = psnake->head;
	while(scan->next != NULL)
		scan = scan->next;
	return scan;
}

void AddNode(Snake *psnake)
{
	psnake->size++;	
	Node *tailnode = GetTail(psnake);
	Node *pnew = pnew = (Node *)malloc(sizeof(Node));
	if(pnew == NULL)
	{
		Pos(10,10);
		printf("add_pnew is NULL");
		exit(0);
	}
	tailnode->next = pnew;
	pnew->next = NULL;
}

bool ThroughWall(Snake *psnake)
{
	if(psnake->head->place.x == 0 || psnake->head->place.x == WIDTH-2 ||
		psnake->head->place.y == 0 || psnake->head->place.y == HEIGHT-1)
		{
			Pos(25,15);
			printf("撞墙，游戏结束！");
			return true;
		}
	else
	{
		Pos(0,HEIGHT);
		printf(" ");	//将闪烁不停的光变放到地图外面---迷之操作=。= 
		return false;
	}
}

bool BiteItself(Snake *psnake)
{
	Node *scan = psnake->head;
	
	while(scan->next != NULL)
	{
		scan = scan->next;
		if(scan->place.x == psnake->head->place.x &&
			scan->place.y == psnake->head->place.y)
		{
			Pos(25,15);
			printf("咬到自身，游戏结束！");
			return true;
		}
	}
	return false;
}

void RenewSnake(Snake *psnake)
{
	int x_index[2] = {0,0},y_index[2] = {0,0};
	Node *scan = psnake->head;
	
	int i = 1;
	x_index[i%2] = scan->place.x;
	y_index[i%2] = scan->place.y;
	
	for(i = 1;i<psnake->size;i++)
	{	
		x_index[(i+1)%2] = scan->next->place.x;
		y_index[(i+1)%2] = scan->next->place.y;
		
		scan->next->place.x = x_index[i%2];
		scan->next->place.y = y_index[i%2];
		
		scan = scan->next;
	}
}

void RunGame(void)
{
	char ch,direction = ' ';
	char charr[5] = {'w','s','a','d',' '};
	int dir_value[2][4] = {
		{0,0,-2,2},
		{-1,1,0,0}
	};
	
	Pos(10,10);
	printf("请在英文状态下按下方向键开始游戏"); 
	Sleep(1800);
	Pos(10,10);
	printf("                                 ");
	
	while(true)
	{
		int flag = 0;
		if(kbhit())
			ch = getch();
		for(int i = 0;i<5;i++)	//判断输入是否为规定的五个字符 
		{
			if(ch == charr[i])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)	//确认输入正常 
		{
			if(!(direction-ch==4||direction-ch==-4||direction-ch==3||direction-ch==-3))
			{	//排除与方向相反的输入 
				direction = ch;
			}
			else if(ch == ' ')
				continue;
		}
		
		switch(direction)
		{
			case 'w':
				PrintIn(NODE,snake.head->place.x+dir_value[0][0],snake.head->place.y+dir_value[1][0]);
				if(snake.head->place.x+dir_value[0][0] == food.x && snake.head->place.y+dir_value[1][0] == food.y)
				{
					AddNode(&snake);	//尾插法
					CreateFood();
				}
				else
				{
					Node *tail = GetTail(&snake);
					PrintIn(SPACE,tail->place.x,tail->place.y);
				}
				RenewSnake(&snake);
				snake.head->place.x += dir_value[0][0];
				snake.head->place.y += dir_value[1][0];
				break;
			case 's':
				PrintIn(NODE,snake.head->place.x+dir_value[0][1],snake.head->place.y+dir_value[1][1]);
				if(snake.head->place.x+dir_value[0][1] == food.x && snake.head->place.y+dir_value[1][1] == food.y)
				{
					AddNode(&snake);
					CreateFood();
				}
				else
				{
					Node *tail = GetTail(&snake);
					PrintIn(SPACE,tail->place.x,tail->place.y);
				}
				RenewSnake(&snake);
				snake.head->place.x += dir_value[0][1];
				snake.head->place.y += dir_value[1][1];
				break;
			case 'a':
				PrintIn(NODE,snake.head->place.x+dir_value[0][2],snake.head->place.y+dir_value[1][2]);
				if(snake.head->place.x+dir_value[0][2] == food.x && snake.head->place.y+dir_value[1][2] == food.y)
				{
					AddNode(&snake);
					CreateFood();
				}
				else
				{
					Node *tail = GetTail(&snake);
					PrintIn(SPACE,tail->place.x,tail->place.y);
				}
				RenewSnake(&snake);
				snake.head->place.x += dir_value[0][2];
				snake.head->place.y += dir_value[1][2];
				break;
			case 'd':
				PrintIn(NODE,snake.head->place.x+dir_value[0][3],snake.head->place.y+dir_value[1][3]);
				if(snake.head->place.x+dir_value[0][3] == food.x && snake.head->place.y+dir_value[1][3] == food.y)
				{
					AddNode(&snake);
					CreateFood();				
				}
				else
				{
					Node *tail = GetTail(&snake);
					PrintIn(SPACE,tail->place.x,tail->place.y);
				}
				RenewSnake(&snake);
				snake.head->place.x += dir_value[0][3];
				snake.head->place.y += dir_value[1][3];
				break;
		}
		if(ThroughWall(&snake) == true)
		{
			Pos(0,30);
			system("pause");
			exit(0); 
		}
		if(BiteItself(&snake)==true)
		{
			Pos(0,30);
			system("pause");
			exit(0); 
		}		
		Sleep(speed);
	}
}
