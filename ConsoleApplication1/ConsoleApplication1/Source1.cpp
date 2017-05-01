#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <thread>

using namespace std;
struct stack
{
	int x;
	int y;
	stack *next;
};

void makefield(char **&, int, int);
void showfield(char **, int, int, int);
void move(char **, const int, const int, HANDLE);
void add(stack*&, int, int);
void delstack(stack*&);


int main()
{


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
	char **field;
	makefield(field, 28, 60);
	showfield(field, 28, 60, 0);
	move(field, 28, 60, hConsole);

	cout << endl;
	_getch();
	return 0;


}


void makefield(char **& field, int n, int m)
{
	field = new char*[n];
	for (int i = 0; i < n; i++)
	{
		field[i] = new char[m];
	}
	for (int i = 0; i<n; i++)
		for (int j = 0; j < m; j++)
		{
			field[i][j] = ' ';
		}
	for (int i = 0; i < m; i++)
		field[0][i] = '1';
	for (int i = 0; i < n; i++)
		field[i][0] = '1';
	for (int i = 0; i < m; i++)
		field[n - 1][i] = '1';
	for (int i = 0; i < n; i++)
		field[i][m - 1] = '1';


}

void showfield(char **field, int n, int m, int counter)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << field[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "Your result is " << counter;
}



void move(char** field, const int n, const int m, HANDLE hConsole)
{
	srand(time(NULL));
	int counter = 0;
	char a = 254;
	field[rand() % 27 + 1][rand() % 59 + 1] = a;
	stack *spisok = NULL;
	COORD position = { 0,0 };
	for (int i = 0; i < 3; i++)
	{
		field[n / 2 + i][m / 2] = 'O';
	}

	SetConsoleCursorPosition(hConsole, position);
	showfield(field, 28, 60, counter);

	int i = n / 2, j = m / 2;
	for (int k = 0; k < 3; k++)
	{
		add(spisok, j, i + k);
	}
	stack *k = spisok;
	int h = 50;

	while (true)
	{
		switch (_getch())
		{
		case 'w':
		{


			while (!kbhit())
			{


				if (k == NULL)
				{
					k = spisok;
				}



				i--;

				if (field[i][j] == 'O' || field[i][j] == '1')
					return;

				if (field[i][j] == a)
				{
					counter++;
					field[i][j] = 'O';
					field[k->y][k->x] = 'O';
					int u, v;
					u = rand() % 27 + 1;
					v = rand() % 59 + 1;
					if (field[u][v] == 'O' || field[u][v] == '1')
					{
						while (field[u][v] == 'O' || field[u][v] == '1')
						{
							u = rand() % 27 + 1;
							v = rand() % 59 + 1;
						}
						field[u][v] = a;

					}
					else field[u][v] = a;
					if (k == spisok)
					{
						stack *t = new stack;
						t->x = j;
						t->y = i;
						t->next = spisok;
						spisok = t;

						Sleep(h);
						SetConsoleCursorPosition(hConsole, position);

						showfield(field, 28, 60, counter);

						continue;
					}

					stack *t;
					t = spisok;
					while (t->next != k)
						t = t->next;
					t = new stack;
					t->next = k->next;
					t->x = j;
					t->y = i;
					k->next = t;

					Sleep(h);
					SetConsoleCursorPosition(hConsole, position);
					showfield(field, 28, 60, counter);


					continue;
				}
				field[k->y][k->x] = ' ';
				k->x = j;
				k->y = i;
				k = k->next;
				field[i][j] = 'O';
				Sleep(h);
				SetConsoleCursorPosition(hConsole, position);
				showfield(field, 28, 60, counter);


			}
		}; break;
		case 'a':
		{

			while (!kbhit())
			{

				if (k == NULL)
				{
					k = spisok;
				}
				j--;
				if (field[i][j] == 'O' || field[i][j] == '1')
					return;
				if (field[i][j] == a)
				{
					counter++;
					field[i][j] = 'O';
					field[k->y][k->x] = 'O';
					int u, v;
					u = rand() % 27 + 1;
					v = rand() % 59 + 1;
					if (field[u][v] == 'O' || field[u][v] == '1')
					{
						while (field[u][v] == 'O' || field[u][v] == '1')
						{
							u = rand() % 27 + 1;
							v = rand() % 59 + 1;
						}
						field[u][v] = a;

					}
					else field[u][v] = a;
					if (k == spisok)
					{
						stack *t = new stack;
						t->x = j;
						t->y = i;
						t->next = spisok;
						spisok = t;

						Sleep(h);
						SetConsoleCursorPosition(hConsole, position);
						showfield(field, 28, 60, counter);

						continue;
					}

					stack *t;
					t = spisok;
					while (t->next != k)
						t = t->next;
					t = new stack;
					t->next = k->next;
					t->x = j;
					t->y = i;
					k->next = t;

					Sleep(h);
					SetConsoleCursorPosition(hConsole, position);
					showfield(field, 28, 60, counter);

					continue;
				}


				field[k->y][k->x] = ' ';

				k->x = j;
				k->y = i;
				k = k->next;
				field[i][j] = 'O';
				Sleep(h);
				SetConsoleCursorPosition(hConsole, position);

				showfield(field, 28, 60, counter);

			}
		}; break;
		case 'd':
		{

			while (!kbhit())
			{


				if (k == NULL)
				{
					k = spisok;
				}

				j++;
				if (field[i][j] == 'O' || field[i][j] == '1')
					return;
				if (field[i][j] == a)
				{
					counter++;
					field[i][j] = 'O';
					field[k->y][k->x] = 'O';
					int u, v;
					u = rand() % 27 + 1;
					v = rand() % 59 + 1;
					if (field[u][v] == 'O' || field[u][v] == '1')
					{
						while (field[u][v] == 'O' || field[u][v] == '1')
						{
							u = rand() % 27 + 1;
							v = rand() % 59 + 1;
						}
						field[u][v] = a;

					}
					else field[u][v] = a;
					if (k == spisok)
					{
						stack *t = new stack;
						t->x = j;
						t->y = i;
						t->next = spisok;
						spisok = t;

						Sleep(h);
						SetConsoleCursorPosition(hConsole, position);
						showfield(field, 28, 60, counter);

						continue;
					}

					stack *t;
					t = spisok;
					while (t->next != k)
						t = t->next;
					t = new stack;
					t->next = k->next;
					t->x = j;
					t->y = i;
					k->next = t;

					Sleep(h);
					SetConsoleCursorPosition(hConsole, position);
					showfield(field, 28, 60, counter);

					continue;
				}
				field[k->y][k->x] = ' ';
				k->x = j;
				k->y = i;
				k = k->next;
				field[i][j] = 'O';
				Sleep(h);
				SetConsoleCursorPosition(hConsole, position);
				showfield(field, 28, 60, counter);

			}
		}; break;
		case's':
		{

			while (!kbhit())
			{

				if (k == NULL)
				{
					k = spisok;
				}

				i++;
				if (field[i][j] == 'O' || field[i][j] == '1')
					return;
				if (field[i][j] == a)
				{
					counter++;
					field[i][j] = 'O';
					field[k->y][k->x] = 'O';
					int u, v;
					u = rand() % 27 + 1;
					v = rand() % 59 + 1;
					if (field[u][v] == 'O' || field[u][v] == '1')
					{
						while (field[u][v] == 'O' || field[u][v] == '1')
						{
							u = rand() % 27 + 1;
							v = rand() % 59 + 1;
						}
						field[u][v] = a;

					}
					else field[u][v] = a;


					if (k == spisok)
					{
						stack *t = new stack;
						t->x = j;
						t->y = i;
						t->next = spisok;
						spisok = t;

						Sleep(h);
						SetConsoleCursorPosition(hConsole, position);
						showfield(field, 28, 60, counter);

						continue;
					}

					stack *t;
					t = spisok;
					while (t->next != k)
						t = t->next;
					t = new stack;
					t->next = k->next;
					t->x = j;
					t->y = i;
					k->next = t;

					Sleep(h);
					SetConsoleCursorPosition(hConsole, position);
					showfield(field, 28, 60, counter);

					continue;
				}
				field[k->y][k->x] = ' ';
				k->x = j;
				k->y = i;
				k = k->next;
				field[i][j] = 'O';
				Sleep(h);
				SetConsoleCursorPosition(hConsole, position);

				showfield(field, 28, 60, counter);

			}

		}; break;

		}


	}


	delstack(spisok);


}

void add(stack*&spisok, int x, int y)
{
	stack *s = new stack;
	s->x = x;
	s->y = y;
	s->next = spisok;
	spisok = s;
}

void delstack(stack*&spisok)
{
	while (spisok != NULL)
	{
		stack *s = spisok;
		spisok = spisok->next;
		delete s;
	}



}