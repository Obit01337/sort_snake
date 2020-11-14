#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int **mx = nullptr;
int n;
int input_check();
void memmory_for_matrix();
void order_matrix();
void inicialisation_matrix();
void print_matrix();
void snake();
void input_for_n();

int main()
{
	input_for_n();
	memmory_for_matrix();
	int type;
	do
	{
		system("cls");
		printf_s("Type '1' if you want fill matrix or '2' if you want auto-filled matrix: ");
		scanf_s("%d", &type);
	} while (!(type == 1 || type == 2));
	if (type == 1)
	{
		inicialisation_matrix();
	}
	else if (type == 2)
	{
		order_matrix();
	}
	system("cls");
	print_matrix();
	printf_s("\n");
	snake();
	print_matrix();
	for (int i = 0; i < n; i++)
		free(mx[i]);
	free(mx);
	return 0;
}

void input_for_n()
{
	do
	{
		system("cls");
		printf_s("Enter size of matrix\n");
		n = input_check();
	} while (!n || n <= 0);
	rewind(stdin);
}

int input_check()
{
	int num;
	do
	{
		printf_s("Enterence ");
		rewind(stdin);
	} while (!scanf_s("%d", &num));
	system("cls");
	return num;
}

void memmory_for_matrix()
{
	mx = (int**)malloc(n * sizeof(int*));
	if (!mx)
	{
		printf_s("Not enough memmory");
		exit(1);
	}
	for (int i = 0; i < n; i++)
	{
		*(mx+i) = (int*)malloc(n * sizeof(int));
		if (!(mx+i))
		{
			if (i == 0)
			{
				free(mx);
					printf_s("Not enough memmory");
					exit(144);
			}
			for (int j = i-1; j >= 0; j--)
			{
				free(mx[j]);
			}
			free(mx);
			printf_s("Not enough memmory");
			exit(144);
		}
	}
}

void order_matrix()
{
	int rost = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			mx[i][j] = 1 + rost;
			rost++;
		}
}

void inicialisation_matrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf_s("mx[%d][%d]\n ", i, j);
			mx[i][j] = input_check();
		}
	}
}

void print_matrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf_s("%5d", mx[i][j]);
		}
		printf_s("\n");
	}
}

void snake()
{
	int top = 0, left = 0, right = n, bot = n;
	char c = 't';
	for (int i = 0; i < 2 * n - 1; i++)
	{
		switch (c)
		{
		case 't':
			for (int j = left; j < right; j++)
			{
				for (int k = j; k < right; k++)
				{
					if (mx[top][k] < mx[top][j])
					{
						mx[top][k] += mx[top][j];
						mx[top][j] = mx[top][k] - mx[top][j];
						mx[top][k] -= mx[top][j];
					}
				}
				for (int i = top + 1; i < bot; i++)
					for (int k = left; k < right; k++)
					{
						if (mx[i][k] < mx[top][j])
						{
							mx[i][k] += mx[top][j];
							mx[top][j] = mx[i][k] - mx[top][j];
							mx[i][k] -= mx[top][j];
						}
					}
			}
			top++;
			c = 'r';
			break;
		case 'r':
			for (int i = top; i < bot; i++)
			{
				for (int k = i; k < bot; k++)
				{
					if (mx[k][right - 1] < mx[i][right - 1])
					{
						mx[k][right - 1] += mx[i][right - 1];
						mx[i][right - 1] = mx[k][right - 1] - mx[i][right - 1];
						mx[k][right - 1] -= mx[i][right - 1];
					}
				}
				for (int k = top; k < bot; k++)
					for (int j = left; j < right - 1; j++)
					{
						if (mx[k][j] < mx[i][right - 1])
						{
							mx[k][j] += mx[i][right - 1];
							mx[i][right - 1] = mx[k][j] - mx[i][right - 1];
							mx[k][j] -= mx[i][right - 1];
						}
					}
			}
			right--;
			c = 'b';
			break;
		case 'b':
			for (int j = right - 1; j >= left; j--)
			{
				for (int k = j; k > left; k--)
				{
					if (mx[bot - 1][k] < mx[bot - 1][j])
					{
						mx[bot - 1][k] += mx[bot - 1][j];
						mx[bot - 1][j] = mx[bot - 1][k] - mx[bot - 1][j];
						mx[bot - 1][k] -= mx[bot - 1][j];
					}
				}
				for (int i = top; i < bot - 1; i++)
					for (int k = left; k < right; k++)
					{
						if (mx[i][k] < mx[bot - 1][j])
						{
							mx[i][k] += mx[bot - 1][j];
							mx[bot - 1][j] = mx[i][k] - mx[bot - 1][j];
							mx[i][k] -= mx[bot - 1][j];
						}
					}
			}
			bot--;
			c = 'l';
			break;
		case 'l':
			for (int i = bot - 1; i >= top; i--)
			{
				for (int k = i; k > top; k--)
				{
					if (mx[k][left] < mx[i][left])
					{
						mx[k][left] += mx[i][left];
						mx[i][left] = mx[k][left] - mx[i][left];
						mx[k][left] -= mx[i][left];
					}
				}
				for (int k = top; k < bot; k++)
					for (int j = left + 1; j < right; j++)
					{
						if (mx[k][j] < mx[i][left])
						{
							mx[k][j] += mx[i][left];
							mx[i][left] = mx[k][j] - mx[i][left];
							mx[k][j] -= mx[i][left];
						}
					}
			}
			left++;
			c = 't';
			break;
		default:
			printf_s("Somthing goes wrong!");
			exit(150);
		}
	}
}