/*
	SnakeV2.0��ʽ�� 
*/ 
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 

#define LONG 60
#define WIDTH 30

typedef struct node{
	int x;
	int y;
}Node;


Node snake[60];
Node food;
int length = 0;
int score = 0;
int speed = 250;

void Pos(int x,int y);
void Information();
void CreateMap();
void InitializeSnake();
void PrintSnake();
void CreateFood(); 
void RunGame();
void AfterEatFood();
int ThroughWall();
int BiteItself();

int main (void)
{ 
	system("mode con cols=90 lines=35");
	Information();
	CreateMap();
	InitializeSnake();   
	CreateFood();
	RunGame();
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

void AfterEatFood()
{
	Pos(LONG+20,WIDTH-20);
    printf("%d",length);
	Pos(LONG+16,WIDTH-18);
    printf("%d",score);
    if(speed>100)
    	speed-=5;
    Pos(LONG+16,WIDTH-16);
    printf("%d",speed);
}

void CreateFood()
{
	int i;
	srand((unsigned int)time(0));
    while(1)
    {
    	do{
        	food.x = rand()%(LONG/2-6)+2;
        }while(food.x%2!=0);
		food.y = rand()%(WIDTH-2)+1;
        for(i=0;i<3+length;i++)
            if(food.x==snake[i].x && food.y==snake[i].y)
            {
                i=-1;
                break;
            }
        if(i>=0)
        {
            Pos(food.x,food.y);
            printf("��");
            break; 
        }
    }
    AfterEatFood(); 
}

void Information()
{
	Pos(LONG/3,WIDTH/3);
	printf("�����ɽṹ���鹹�ɵ�̰���ߣ��� w s a d ���Ʒ���");
	Pos(LONG/3,WIDTH/3+2);
	printf("��ϸ�����ģ��ɷ����ҵĲ���԰��");
	Pos(LONG/3,WIDTH/3+4);
	printf("�û�����Magic����  http://www.cnblogs.com/magicxyx/");
	Pos(LONG/3,WIDTH/3+6);
	printf("�緢��bug�����������뷨�ģ�Ҳ�ɷ������ҵ����䣺");
	Pos(LONG/3,WIDTH/3+8);
	printf("www.magic_xyx@foxmail.com");
	Pos(LONG/3,WIDTH/3+10);
	printf("������Ϸǰ���л���Ӣ������");
	Pos(LONG/3,WIDTH/3+12);
	system("pause"); 
	system("cls");
	Pos(LONG+10,WIDTH-20);
	printf("���ȣ�3 + 0 ");
	Pos(LONG+10,WIDTH-18);
	printf("������0");
	Pos(LONG+10,WIDTH-16);
	printf("�ٶȣ�0"); 
	Pos(LONG+10,WIDTH-14);
	printf("���ո����ͣ");
	Pos(LONG+8,WIDTH-12);
	printf("�����ⷽ�������"); 	
}

void CreateMap()
{
	int i;
	for(i=0;i<LONG;i+=2)
	{
		Pos(i,0);
		printf("��");
		Pos(i,WIDTH-1);
		printf("��");
	}
	for(i=1;i<WIDTH-1;i++)
	{
		Pos(0,i);
		printf("��");
		Pos(LONG-2,i);
		printf("��");
	}
}

void InitializeSnake()
{
	int i;
	for(i=0;i<3;i++)
    {
        snake[i].x = (LONG/2-i*2);
        snake[i].y = WIDTH/2;
        Pos(snake[i].x,snake[i].y);
        printf("��");
	}
}

void PrintSnake()
{
	int i;
	for(i=0;i<=2+length;i++)
	{
		Pos(snake[i].x,snake[i].y);
		printf("��");
	}	
}

int ThroughWall()
{
	if(snake[0].x==0 || snake[0].x==58 ||
		snake[0].y==0 || snake[0].y==29)
		{
			Pos(25,15);
			printf("ײǽ ��Ϸ����");
			return 1;
		}
}

int BiteItself()
{
	int i;
	for(i=3;i<=2+length;i++)
		if((snake[0].x==snake[i].x) && (snake[0].y==snake[i].y))
		{
			Pos(25,15);
			printf("ҧ���Լ� ��Ϸ����");
			return 1;
		}
}

void RunGame()
{
	int i;
	char ch,direction='d';
	while(1)
	{
		if(kbhit())
			ch = getch();
		if(ch=='w'&&direction!='s')
			direction = ch;
		else if(ch=='s'&&direction!='w')
			direction = ch;
		else if(ch=='a'&&direction!='d')
			direction = ch;
		else if(ch=='d'&&direction!='a')
			direction = ch;
		else if(ch==' ')
			continue;
		switch(direction)
		{
		case 'w':
			if(snake[0].x==food.x && snake[0].y-1==food.y)
			{
				length++;
				score+=10;
				snake[2+length].x = snake[2+length-1].x;
				snake[2+length].y = snake[2+length-1].y;
				for(i=length+3-2;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
				CreateFood();
			}
			else
			{
				Pos(snake[2+length].x,snake[2+length].y);
				printf(" ");
				for(i=length+3-1;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
			}
			snake[0].y -=1;
			break;
		case 's':
			if(snake[0].x==food.x && snake[0].y+1==food.y)
			{
				length++;
				score+=10;
				snake[2+length].x = snake[2+length-1].x;
				snake[2+length].y = snake[2+length-1].y;
				for(i=length+3-2;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
				CreateFood();
			}
			else
			{
				Pos(snake[2+length].x,snake[2+length].y);
				printf(" ");
				for(i=length+3-1;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
			}
			snake[0].y +=1;
			break;
		case 'a':
			if(snake[0].x-2==food.x && snake[0].y==food.y)
			{
				length++;
				score+=10;
				snake[2+length].x = snake[2+length-1].x;
				snake[2+length].y = snake[2+length-1].y;
				for(i=length+3-2;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
				CreateFood();
			}
			else
			{
				Pos(snake[2+length].x,snake[2+length].y);
				printf(" ");
				for(i=length+3-1;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
			}
			snake[0].x -=2;
			break;
		case 'd':
			if(snake[0].x+2==food.x && snake[0].y==food.y)
			{
				length++;
				score+=10;
				snake[2+length].x = snake[2+length-1].x;
				snake[2+length].y = snake[2+length-1].y;
				for(i=length+3-2;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
				CreateFood();
			}
			else
			{
				Pos(snake[2+length].x,snake[2+length].y);
				printf(" ");
				for(i=length+3-1;i>0;i--)
				{
					snake[i].x = snake[i-1].x;
					snake[i].y = snake[i-1].y;
				}
			}
			snake[0].x +=2;
		}
		PrintSnake();
		if(ThroughWall()==1)
		{
			Pos(25,WIDTH);
			exit(0); 
		}
		if(BiteItself()==1)
		{
			Pos(25,WIDTH);
			exit(0); 
		}		
		Pos(0,WIDTH);
		Sleep(speed); 
	}
}

