#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;
class chessboard;
class chess//基类，棋子
{
protected:
	int id;//确定属于哪个玩家的棋子 player1 为 1 player2 为 -1
public:
	chess(int i) { id = i; };
	virtual bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c) = 0;//对棋子移动进行判断.
	virtual char* getname() = 0;
	int getid() { return id; }//确定属于哪个玩家的棋子 player1 为 1 player2 为 -1
	virtual~chess() {};//析构
};
//下面为棋盘的实现。
class chessboard
{
private:
	chess* c[10][9];//动态多态,调用棋子
public:
	chessboard() { memset(c, 0, sizeof(c)); }//全部初始化为空指针。
	chess* get(int x, int y) { return c[x][y]; }//调用返回棋子指针
	bool test(int x, int y)//探测棋盘上是否有棋子
	{
		if (c[x][y] == 0)
			return false;
		else
		{
			return true;
		}
	};
	void show();//打印棋盘。
	void initialize();//棋盘的初始化。
	bool move(int start_x, int start_y, int end_x, int end_y);//对棋子进行移动。
	~chessboard();//游戏结束对棋盘进行析构。
	static int player;//区分两位玩家。
	static int flag;//区分回合游戏结束与否
};
int chessboard::player = 1;
int chessboard::flag = 1;
bool chessboard::move(int start_x, int start_y, int end_x, int end_y)
{
	if (c[start_x][start_y] != 0)
	{
		if ((start_x >= 0 && start_x < 10) && (start_y >= 0 && start_y < 9) && (end_x >= 0 && end_x < 10) && (end_y >= 0 && end_y < 9))//判断起始位置和终止位置是否越界
		{
			if (c[start_x][start_y]->getid() == player)//判断是否为己方棋子
			{
				if (c[start_x][start_y]->judge_move(start_x, start_y, end_x, end_y, *this))//判断是否移动正确
				{
					if (c[end_x][end_y] != 0)//吃棋子
					{
						delete[] c[end_x][end_y];
						c[end_x][end_y] = c[start_x][start_y];
						c[start_x][start_y] = 0;
						player *= -1;
						return true;
					}
					else
					{
						c[end_x][end_y] = c[start_x][start_y];
						c[start_x][start_y] = 0;
						player *= -1;
						return true;
					}
				}
				else
				{
					cout << "移动错误,请按象棋规则移动" << endl;
					return false;
				}
			}
			else
			{
				cout << "不是您操作的回合" << endl;
				return false;
			}
		}
		else
		{
			cout << "操作越界" << endl;
			return false;
		}
	}
	else
	{
		cout << "不能操作没有棋子的格子" << endl;
		return false;
	}
}
void chessboard::show()//棋盘打印
{
	cout << "  0 1 2 3 4 5 6 7 8" << endl;
	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) { cout << "———-楚------河————" << endl; }//棋盘中间用楚河分隔。
		cout << a[i] << " ";
		for (int j = 0; j < 9; j++)
		{
			if (c[i][j] != 0)
			{
				cout << c[i][j]->getname();
			}
			else
				cout << "十";
		}
		cout << endl;
	}
}
chessboard::~chessboard()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (c[i][j] != 0)
			{
				delete[] c[i][j];
				c[i][j] = 0;
			}
		}
	}
}
//下面是各种棋子的实现.
class general :public chess	//将军的实现。
{
private:
	char name[6];
public:
	general(int i) :chess(i)
	{
		if (i == 1)//玩家不同棋子名字不同
		{
			strcpy_s(name, 3, "将");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "帅");
		}
	}
	char* getname()
	{
		return name;
	}
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if ((end_y >= 3 && end_y <= 5) && end_x % 7 >= 0 && end_x % 7 <= 2)//由象棋棋盘，将（帅）的y坐标比在3 5之间 x坐标在 （0，2）（7 9）之间模7可以同时控制在02之间
		{
			if (Mx * Mx + My * My == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	~general() { chessboard::flag = 0; }//将军被消灭，游戏结束。
};
class guarder :public chess
{
private:
	char name[6];
public:
	guarder(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "士");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "仕");
		}
	}
	char* getname()
	{
		return name;
	}
	bool  judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if ((end_y >= 3 && end_y <= 5) && end_x % 7 >= 0 && end_x % 7 <= 2)//由象棋棋盘，士(仕)的y坐标比在3 5之间 x坐标在 （0，2）（7 9）之间模7可以同时控制在02之间
		{
			if (Mx * Mx + My * My == 2)//仕只可沿斜线走
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			return false;
		}
	}
};
class army :public chess
{
private:
	char name[6];
public:
	army(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "卒");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "兵");
		}
	}
	char* getname() { return name; }
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (id == 1)
		{
			if (start_x >= 5)
			{
				if (Mx == -1 && My == 0)//未过河前只能向前走
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (start_x < 5)
			{
				if (fabs(Mx) + fabs(My) == 1 && Mx != 1)//过河后可以向左右移动，但不能后退
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		if (id == -1)
		{
			if (start_x <= 5)
			{
				if (Mx == 1 && My == 0)//未过河前只能向前走
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (start_x >= 5)
			{
				if (fabs(Mx) + fabs(My) == 1 && Mx != -1)//过河后可以向左右移动，但不能后退
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
};
class artillery :public chess
{
private:
	char name[6];
public:
	artillery(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "炮");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "軳");
		}
	}
	char* getname() { return name; }
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (!(Mx && My) && (Mx + My))//初步判断
		{
			int rack = 0;
			if (My == 0)
			{
				int dir = Mx > 0 ? 1 : -1;//判断行走方向
				for (int i = 1; i < fabs(Mx); i++)//对行走方向进行遍历
				{
					if (c.test(start_x + dir * i, start_y))
					{
						rack++;//找到棋子则自增。
					}
				}
			}
			else if (Mx == 0)
			{
				int dir = My > 0 ? 1 : -1;
				for (int i = 1; i < fabs(My); i++)
				{
					if (c.test(start_x, start_y + dir * i))
					{
						rack++;
					}
				}
			}
			if (c.test(end_x, end_y) == 0)
			{
				if (rack == 0)//目标地无棋子，且中间没有棋子间隔
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (rack == 1)//目标地有棋子，且中间有一个棋子。
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
};
class car :public chess
{
private:
	char name[6];
public:
	car(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "車");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "车");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (!(Mx && My) && (Mx + My))//只能朝一个方向走。
		{
			if (My == 0)
			{
				int dir = Mx > 0 ? 1 : -1;//方向
				for (int i = 1; i < fabs(Mx); i++)
				{
					if (c.test(start_x + dir * i, start_y))//对行走方向进行遍历
					{
						return false;
					}
					else
						return true;
				}
			}
			if (Mx == 0)
			{
				int dir = My > 0 ? 1 : -1;
				for (int i = 1; i < fabs(My); i++)
				{
					if (c.test(start_x, start_y + dir * i))//对行走方向进行遍历
					{
						return false;
					}
					else
						return true;
				}
			}
		}
		return false;
	}
};
class horse :public chess
{
private:
	char name[6];
public:
	horse(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "馬");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "马");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (Mx * Mx + My * My == 5 && c.test(start_x + Mx / 2, start_y + My / 2) == 0)//进行马走日的判断，且不被棋子別住。
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
class elephant :public chess
{
private:
	char name[6];
public:
	elephant(int i) :chess(i)
	{
		if (i == 1)
		{
			strcpy_s(name, 3, "象");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "相");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (Mx * Mx + My * My == 8 && c.test(start_x + Mx / 2, start_y + My / 2) == 0 && start_x / 5 == end_x / 5)//象走田，不能被田字中间阻挡,且不能过河。
		{
			return true;
		}
		else
			return false;
	}
};

void chessboard::initialize()
{
	c[0][0] = new car(-1);        c[0][8] = new car(-1);
	c[9][0] = new car(1);        c[9][8] = new car(1);
	//车初始化
	c[0][1] = new horse(-1);       c[0][7] = new horse(-1);
	c[9][1] = new horse(1);       c[9][7] = new horse(1);
	//马初始化
	c[0][2] = new elephant(-1);    c[0][6] = new elephant(-1);
	c[9][2] = new elephant(1);    c[9][6] = new elephant(1);
	//象初始化
	c[0][3] = new guarder(-1);       c[0][5] = new guarder(-1);
	c[9][3] = new guarder(1);       c[9][5] = new guarder(1);
	//士初始化
	c[0][4] = new general(-1);     c[9][4] = new general(1);
	//将初始化
	c[2][1] = new artillery(-1);      c[2][7] = new artillery(-1);
	c[7][1] = new artillery(1);      c[7][7] = new artillery(1);
	//軳初始化
	c[3][0] = new army(-1);     c[3][2] = new army(-1);
	c[3][4] = new army(-1);     c[3][6] = new army(-1);
	c[3][8] = new army(-1);     c[6][8] = new army(1);
	c[6][0] = new army(1);     c[6][2] = new army(1);
	c[6][4] = new army(1);     c[6][6] = new army(1);
	//兵初始化
}
int main(void)
{
	chessboard c;
	c.initialize();
	c.show();
	int start_x, start_y, end_x, end_y;
	do {
		do
		{
			if (chessboard::player == 1)
			{
				cout << "请玩家1进行操作" << endl;
			}
			else if (chessboard::player == -1)
			{
				cout << "请玩家2进行操作" << endl;
			}
			cout << "请输入想要操作棋子的起始坐标和终止坐标(x,y)注意：(纵轴为x,横轴为y)" << endl;
			cin >> start_x >> start_y >> end_x >> end_y;
		} while (c.move(start_x, start_y, end_x, end_y) == 0);
		system("cls");
		c.show();
	} while (chessboard::flag != 0);
	if (chessboard::player == 1)
	{
		cout << "游戏结束 获胜玩家为：玩家1" << endl;
	}
	else
	{
		cout << "游戏结束 获胜玩家为：玩家2" << endl;
	}
}