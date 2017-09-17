#include <stdio.h>
#include <windows.h>
#include <time.h>
#define X_MAP 100
#define Y_MAP 40

struct snake{
        int x;
        int y;
};
struct food{
        int x;
        int y;
}food;
struct snake node[100];	//�� 
int score = 0,length= 0;	//	��  ���ȣ�3+X�� 
int status;		//1:ײǽ 	2:ҧ�Լ� 
int time1 = 250;
int x_last,y_last;


void Pos(int x, int y)
{
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void Information()
{ 
	system("mode con cols=130 lines=130");
	Pos(X_MAP/3,Y_MAP/3);
	printf("�����ɽṹ���鹹�ɵ�̰���ߣ��� w s a d ���Ʒ���");
	Pos(X_MAP/3,Y_MAP/3+2);
	printf("��ϸ�����ģ��ɷ����ҵĲ���԰��");
	Pos(X_MAP/3,Y_MAP/3+4);
	printf("�û�����Magic����  http://www.cnblogs.com/magicxyx/");
	Pos(X_MAP/3,Y_MAP/3+6);
	printf("�緢��bug�����������뷨�ģ�Ҳ�ɷ������ҵ����䣺");
	Pos(X_MAP/3,Y_MAP/3+8);
	printf("www.magic_xyx@foxmail.com");
	Pos(X_MAP/3,Y_MAP/3+10);
	printf(" ");
	system("pause"); 
	system("cls");
	Pos(X_MAP+8,Y_MAP-30);
	printf("���ȣ�3 + 0 ");
	Pos(X_MAP+8,Y_MAP-28);
	printf("������ 0");
	Pos(X_MAP+8,Y_MAP-25);
	printf("���������ͣ");
	Pos(X_MAP+8,Y_MAP-23);
	printf("�����������"); 
	Pos(X_MAP+3,Y_MAP-20);
	printf("���������⣬�����½�����Ϸ");
	Pos(X_MAP+3,Y_MAP-18);
	printf("��������?...."); 
	Pos(X_MAP+3,Y_MAP-16);
	printf("�������ǵúú�����...");
}

void CreateMap()
{
	int i;
    for(i=0;i<X_MAP;i++)//���� 
    {
        Pos(i,1);//�ϱ߿� 
        printf("#");
        Pos(i,Y_MAP-1);//�±߿� 
        printf("#");
    }
    for(i=2;i<Y_MAP-1;i++)//���� 
    {
        Pos(0,i);//��߿� 
        printf("#"); 
		Pos(X_MAP-1,i);//�ұ߿� 
        printf("#");
    }
}

void InitializeSnake()
{
	int i;
    for(i=0;i<3;i++)
    {
        node[i].x = (X_MAP/2-i);
        node[i].y = Y_MAP/2;
        Pos(node[i].x,node[i].y);
        printf("o");
	}
}

void move(char ch)
{
	int i;

	int x2,y2;
	x_last = node[0].x;
	y_last = node[0].y;
	switch(ch)
	{
		case 'w':
			if(node[0].y-1==node[1].y)
				break;
			node[0].y-=1;
			break;
		case 's':
			if(node[0].y+1==node[1].y)
				break;
			node[0].y+=1;
			break;
		case 'a':
			if(node[0].x-1==node[1].x)
				break;
			node[0].x-=1;
			break;
		case 'd':
			if(node[0].x+1==node[1].x)
				break;
			node[0].x+=1;
			break;
	}
	Pos(node[0].x,node[0].y);
	printf("o");
	for(i=1;i<3+length;i++)
	{
		x2=node[i].x;
		y2=node[i].y;
		node[i].x=x_last;
		node[i].y=y_last;
		Pos(node[i].x,node[i].y);
		printf("o");
		x_last=x2;
		y_last=y2;
	}
	Pos(x_last,y_last);
	printf(" ");
	Pos(0,Y_MAP);
	
	
}

int ThroughWall()
{
	if(node[0].x==0||node[0].x==X_MAP-1 || 
		node[0].y==1||node[0].y==Y_MAP)
		{
			status=1;
			return 1;
		}
}

int BiteItself()
{
	int i;
	for(i=1;i<(3+length);i++)
		if(node[0].x==node[i].x && 
			node[0].y==node[i].y)
			{
				status = 2;
				return 1;
			}
	return 0;
}

void GameOver()
{
	Pos(X_MAP/2,Y_MAP/2);
	switch(status)
	{
		case 1:
			printf("ײǽ��������Ϸ����"); 
			break;
		case 2:
			printf("ҧ���Լ�����Ϸ����");
			break;
	}
	exit(0);
} 

void CreateFood()
{    
	int i;
    srand((unsigned int)time(0));
    while(1)
    {
        food.x = rand()%(X_MAP/2)+1;
        food.y = rand()%(Y_MAP/2)+2;
        for(i=0;i<3+length;i++)
            if(food.x==node[i].x && food.y==node[i].y)
            {
                i=-1;
                break;
            }
        if(i>=0)
        {
            Pos(food.x,food.y);
            printf("+");
            break; 
        }
    }
}

int EatFood()
{
	if(node[0].x==food.x && 
		node[0].y==food.y)
		{
			CreateFood();
			return 1;
		}
}

void RunGame()
{
	char ch;
	char direction = 'd'; 
	while(1)
    {
    	if(kbhit())
    	{
			ch = getch();
    		direction = ch; 
    	}
    	switch(direction)
    	{
    		case 'w':
    				move(direction);
    				break;
    		case 's':
    				move(direction);
    				break;
    		case 'a':
    				move(direction);
    				break;
    		case 'd':
    				move(direction);
    				break;
			default:
				continue;
		}
		
		if(EatFood()==1)
		{
			length++;
			score += 10;
			Pos(X_MAP+18,Y_MAP-30);
			printf("%d",length); 
			Pos(X_MAP+15,Y_MAP-28);
			printf("%d",score);
			if(time1>80)
    			time1 -= 10;
			node[2+length].x =x_last;
			node[2+length].y =y_last;
		}
		
		if(ThroughWall()==1)
			GameOver();
		if(BiteItself()==1)
			GameOver();
		Sleep(time1);
	}
    
}


int main (void)
{
	Information();
	CreateMap();
	InitializeSnake();   
    CreateFood();
	RunGame();
	
    return 0;
}
