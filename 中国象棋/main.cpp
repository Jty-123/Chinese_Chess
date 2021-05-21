#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;
class chessboard;
class chess//���࣬����
{
protected:
	int id;//ȷ�������ĸ���ҵ����� player1 Ϊ 1 player2 Ϊ -1
public:
	chess(int i) { id = i; };
	virtual bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c) = 0;//�������ƶ������ж�.
	virtual char* getname() = 0;
	int getid() { return id; }//ȷ�������ĸ���ҵ����� player1 Ϊ 1 player2 Ϊ -1
	virtual~chess() {};//����
};
//����Ϊ���̵�ʵ�֡�
class chessboard
{
private:
	chess* c[10][9];//��̬��̬,��������
public:
	chessboard() { memset(c, 0, sizeof(c)); }//ȫ����ʼ��Ϊ��ָ�롣
	chess* get(int x, int y) { return c[x][y]; }//���÷�������ָ��
	bool test(int x, int y)//̽���������Ƿ�������
	{
		if (c[x][y] == 0)
			return false;
		else
		{
			return true;
		}
	};
	void show();//��ӡ���̡�
	void initialize();//���̵ĳ�ʼ����
	bool move(int start_x, int start_y, int end_x, int end_y);//�����ӽ����ƶ���
	~chessboard();//��Ϸ���������̽���������
	static int player;//������λ��ҡ�
	static int flag;//���ֻغ���Ϸ�������
};
int chessboard::player = 1;
int chessboard::flag = 1;
bool chessboard::move(int start_x, int start_y, int end_x, int end_y)
{
	if (c[start_x][start_y] != 0)
	{
		if ((start_x >= 0 && start_x < 10) && (start_y >= 0 && start_y < 9) && (end_x >= 0 && end_x < 10) && (end_y >= 0 && end_y < 9))//�ж���ʼλ�ú���ֹλ���Ƿ�Խ��
		{
			if (c[start_x][start_y]->getid() == player)//�ж��Ƿ�Ϊ��������
			{
				if (c[start_x][start_y]->judge_move(start_x, start_y, end_x, end_y, *this))//�ж��Ƿ��ƶ���ȷ
				{
					if (c[end_x][end_y] != 0)//������
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
					cout << "�ƶ�����,�밴��������ƶ�" << endl;
					return false;
				}
			}
			else
			{
				cout << "�����������Ļغ�" << endl;
				return false;
			}
		}
		else
		{
			cout << "����Խ��" << endl;
			return false;
		}
	}
	else
	{
		cout << "���ܲ���û�����ӵĸ���" << endl;
		return false;
	}
}
void chessboard::show()//���̴�ӡ
{
	cout << "  0 1 2 3 4 5 6 7 8" << endl;
	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) { cout << "������-��------�ӡ�������" << endl; }//�����м��ó��ӷָ���
		cout << a[i] << " ";
		for (int j = 0; j < 9; j++)
		{
			if (c[i][j] != 0)
			{
				cout << c[i][j]->getname();
			}
			else
				cout << "ʮ";
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
//�����Ǹ������ӵ�ʵ��.
class general :public chess	//������ʵ�֡�
{
private:
	char name[6];
public:
	general(int i) :chess(i)
	{
		if (i == 1)//��Ҳ�ͬ�������ֲ�ͬ
		{
			strcpy_s(name, 3, "��");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "˧");
		}
	}
	char* getname()
	{
		return name;
	}
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if ((end_y >= 3 && end_y <= 5) && end_x % 7 >= 0 && end_x % 7 <= 2)//���������̣�����˧����y�������3 5֮�� x������ ��0��2����7 9��֮��ģ7����ͬʱ������02֮��
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
	~general() { chessboard::flag = 0; }//������������Ϸ������
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
			strcpy_s(name, 3, "ʿ");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "��");
		}
	}
	char* getname()
	{
		return name;
	}
	bool  judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if ((end_y >= 3 && end_y <= 5) && end_x % 7 >= 0 && end_x % 7 <= 2)//���������̣�ʿ(��)��y�������3 5֮�� x������ ��0��2����7 9��֮��ģ7����ͬʱ������02֮��
		{
			if (Mx * Mx + My * My == 2)//��ֻ����б����
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
			strcpy_s(name, 3, "��");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "��");
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
				if (Mx == -1 && My == 0)//δ����ǰֻ����ǰ��
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
				if (fabs(Mx) + fabs(My) == 1 && Mx != 1)//���Ӻ�����������ƶ��������ܺ���
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
				if (Mx == 1 && My == 0)//δ����ǰֻ����ǰ��
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
				if (fabs(Mx) + fabs(My) == 1 && Mx != -1)//���Ӻ�����������ƶ��������ܺ���
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
			strcpy_s(name, 3, "��");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "�N");
		}
	}
	char* getname() { return name; }
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (!(Mx && My) && (Mx + My))//�����ж�
		{
			int rack = 0;
			if (My == 0)
			{
				int dir = Mx > 0 ? 1 : -1;//�ж����߷���
				for (int i = 1; i < fabs(Mx); i++)//�����߷�����б���
				{
					if (c.test(start_x + dir * i, start_y))
					{
						rack++;//�ҵ�������������
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
				if (rack == 0)//Ŀ��������ӣ����м�û�����Ӽ��
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
				if (rack == 1)//Ŀ��������ӣ����м���һ�����ӡ�
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
			strcpy_s(name, 3, "܇");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "��");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (!(Mx && My) && (Mx + My))//ֻ�ܳ�һ�������ߡ�
		{
			if (My == 0)
			{
				int dir = Mx > 0 ? 1 : -1;//����
				for (int i = 1; i < fabs(Mx); i++)
				{
					if (c.test(start_x + dir * i, start_y))//�����߷�����б���
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
					if (c.test(start_x, start_y + dir * i))//�����߷�����б���
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
			strcpy_s(name, 3, "�R");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "��");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (Mx * Mx + My * My == 5 && c.test(start_x + Mx / 2, start_y + My / 2) == 0)//���������յ��жϣ��Ҳ������ӄeס��
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
			strcpy_s(name, 3, "��");
		}
		if (i == -1)
		{
			strcpy_s(name, 3, "��");
		}
	}
	char* getname() { return name; };
	bool judge_move(int start_x, int start_y, int end_x, int end_y, chessboard& c)
	{
		int Mx = end_x - start_x; int My = end_y - start_y;
		if (Mx * Mx + My * My == 8 && c.test(start_x + Mx / 2, start_y + My / 2) == 0 && start_x / 5 == end_x / 5)//��������ܱ������м��赲,�Ҳ��ܹ��ӡ�
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
	//����ʼ��
	c[0][1] = new horse(-1);       c[0][7] = new horse(-1);
	c[9][1] = new horse(1);       c[9][7] = new horse(1);
	//���ʼ��
	c[0][2] = new elephant(-1);    c[0][6] = new elephant(-1);
	c[9][2] = new elephant(1);    c[9][6] = new elephant(1);
	//���ʼ��
	c[0][3] = new guarder(-1);       c[0][5] = new guarder(-1);
	c[9][3] = new guarder(1);       c[9][5] = new guarder(1);
	//ʿ��ʼ��
	c[0][4] = new general(-1);     c[9][4] = new general(1);
	//����ʼ��
	c[2][1] = new artillery(-1);      c[2][7] = new artillery(-1);
	c[7][1] = new artillery(1);      c[7][7] = new artillery(1);
	//�N��ʼ��
	c[3][0] = new army(-1);     c[3][2] = new army(-1);
	c[3][4] = new army(-1);     c[3][6] = new army(-1);
	c[3][8] = new army(-1);     c[6][8] = new army(1);
	c[6][0] = new army(1);     c[6][2] = new army(1);
	c[6][4] = new army(1);     c[6][6] = new army(1);
	//����ʼ��
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
				cout << "�����1���в���" << endl;
			}
			else if (chessboard::player == -1)
			{
				cout << "�����2���в���" << endl;
			}
			cout << "��������Ҫ�������ӵ���ʼ�������ֹ����(x,y)ע�⣺(����Ϊx,����Ϊy)" << endl;
			cin >> start_x >> start_y >> end_x >> end_y;
		} while (c.move(start_x, start_y, end_x, end_y) == 0);
		system("cls");
		c.show();
	} while (chessboard::flag != 0);
	if (chessboard::player == 1)
	{
		cout << "��Ϸ���� ��ʤ���Ϊ�����1" << endl;
	}
	else
	{
		cout << "��Ϸ���� ��ʤ���Ϊ�����2" << endl;
	}
}