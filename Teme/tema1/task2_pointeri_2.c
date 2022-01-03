// CONSTANTIN MIHAI - 311CD

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

// AFISEZ TABLA CURENTA

void print_matrix(int x, int y, char c, int N, int M,
	int x1, int y1, char c1, int x2, int y2, char c2, int x3, int y3, char c3)
{
	char C;
	int i, j;

	for(i = 0; i <= N + 1; i++)
	{
		for(j = 0; j <= M + 1; j++)
		{
			if(i == 0 || i == N + 1 || j == 0 || j == M + 1)
			{
				C = '*';
			}
			else
			{
				if(i == x && j == y)
				{
					switch(c)
					{
						case 'w':
						{
							C = '^';
							break;
						}

						case 'a':
						{
							C = '<';
							break;
						}

						case 's':
						{
							C = 'v';
							break;
						}

						case 'd':
						{
							C = '>';
							break;
						}
					}
				}
				else
				{
					if((i == x1 && j == y1) || (i == x2 && j == y2) || (i == x3 && j == y3))
					{
						C = 'x';
					}
					else
						C = ' ';
				}
			}

			printf("%c", C);
		}

		printf("\n");
	}
}

// VERIFIC DACA SUNT IN INTERIORUL TABLEI DE JOC

bool valid(int x, int y, int N, int M)
{
	if(x >= 1 && x <= N && y >= 1 && y <= M)
	{
		return true;
	}

	return false;
}

// 	VERIFIC DACA JOCUL POATE CONTINUA

bool GAME(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if( (x == x1 && y == y1) || (x == x2 && y == y2) || (x == x3 && y == y3) )
	{
		return true;
	}

	return false;
}

// CALCULEZ DISTANTA DINTRE POZITIA PERSONAJULUI SI OBSTACOL

int distance(int x_p, int y_p, int x_obs, int y_obs)
{
	return abs(x_p - x_obs) + abs(y_p - y_obs);
}

// ALEG COORDONATELE CARE MINIMIZEAZA DISTANTA DINTRE PERSONAJ SI OBSTACOL

void mv_obs(int x, int y, int x1, int y1, int *p1, int *p2)
{
	int dist, dist_min;

	dist_min = distance(x, y, x1 - 1, y1 - 1);

	*p1 = x1 - 1;
	*p2 = y1 - 1;

	dist = distance(x, y, x1 - 1, y1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1 - 1;
		*p2 = y1;
	}

	dist = distance(x, y, x1 - 1, y1 + 1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1 - 1;
		*p2 = y1 + 1;
	}

	dist = distance(x, y, x1, y1 + 1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1;
		*p2 = y1 + 1;
	}

	dist = distance(x, y, x1 + 1, y1 + 1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1 + 1;
		*p2 = y1 + 1;
	}

	dist = distance(x, y, x1 + 1, y1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1 + 1;
		*p2 = y1;
	}

	dist = distance(x, y, x1 + 1, y1 - 1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1 + 1;
		*p2 = y1 - 1;
	}

	dist = distance(x, y, x1, y1 - 1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1;
		*p2 = y1 - 1;
	}

	dist = distance(x, y, x1, y1);

	if(dist < dist_min)
	{
		dist_min = dist;

		*p1 = x1;
		*p2 = y1;
	}
}

// AFLU NOILE POZITII ALE OBSTACOLELOR

void obs_mobil(int x, int y, int *x1, int *y1, char c1, int *x2, int *y2, char c2, int *x3, int *y3, char c3)
{
    int X1, Y1, X2, Y2, X3, Y3;

    if(c1 == 'm')
    {
        mv_obs(x, y, *x1, *y1, &X1, &Y1);

        // AM GASIT NOILE COORDONATE

        *x1 = X1;
        *y1 = Y1;
    }

    if(c2 == 'm')
    {
        mv_obs(x, y, *x2, *y2, &X2, &Y2);

        // AM GASIT NOILE COORDONATE

        *x2 = X2;
        *y2 = Y2;
    }

    if(c3 == 'm')
    {
        mv_obs(x, y, *x3, *y3, &X3, &Y3);

        // AM GASIT NOILE COORDONATE

        *x3 = X3;
        *y3 = Y3;
    }
}

void solve(int x, int y, int N, int M,
	int x1, int y1, char c1, int x2, int y2, char c2, int x3, int y3, char c3)
{
	char c, c_pred;
	bool ok, GAME_OVER;
	int NR = 0; // NR = NUMARUL TABLEI AFISATE (IN AFARA DE CEA INITIALA)

	c_pred = 's'; // CARACTERUL PRECEDENT

	scanf("%c", &c); // CITIRE ENTER

	while( scanf("%c", &c) && c != 'q')
	{
		ok = false;
		GAME_OVER = false; // PRESUPUN CA JOCUL POATE CONTINUA

		NR++;

		switch(c)
		{
			case 'w':
			{
				ok = valid(x - 1, y, N, M); // VERIFIC DACA MA POT DEPLASA

				if(ok) // DACA MA POT DEPLASA
				{
					x = x - 1;
				}
				else // DACA NU, TABLA URMATOARE VA FI IDENTICA CU CEA PRECEDENTA
				{
					c = c_pred;
				}

				if(NR % 2 == 0) // OBSTACOLELE MOBILE SE VOR MISCA O DATA LA 2 TURE
				{
					obs_mobil(x, y, &x1, &y1, c1, &x2, &y2, c2, &x3, &y3, c3);
				}

				GAME_OVER = GAME(x, y, x1, y1, x2, y2, x3, y3);

				if(GAME_OVER)
				{
					printf("GAME OVER\n");
					return;
				}
				else
				{
					print_matrix(x, y, c, N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3);
				}

				break;
			}

			case 'a':
			{
				ok = valid(x, y - 1, N, M); // VERIFIC DACA MA POT DEPLASA

				if(ok)
				{
					y = y - 1;
				}
				else
				{
					c = c_pred;
				}

				if(NR % 2 == 0)
				{
					obs_mobil(x, y, &x1, &y1, c1, &x2, &y2, c2, &x3, &y3, c3);
				}

				GAME_OVER = GAME(x, y, x1, y1, x2, y2, x3, y3);

				if(GAME_OVER)
				{
					printf("GAME OVER\n");
					return;
				}
				else
				{
					print_matrix(x, y, c, N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3);
				}

				break;
			}

			case 's':
			{
				ok = valid(x + 1, y, N, M); // VERIFIC DACA MA POT DEPLASA

				if(ok)
				{
					x = x + 1;
				}
				else
				{
					c = c_pred;
				}

				if(NR % 2 == 0)
				{
					obs_mobil(x, y, &x1, &y1, c1, &x2, &y2, c2, &x3, &y3, c3);
				}

				GAME_OVER = GAME(x, y, x1, y1, x2, y2, x3, y3);

				if(GAME_OVER)
				{
					printf("GAME OVER\n");
					return;
				}
				else
				{
					print_matrix(x, y, c, N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3);
				}

				break;
			}

			case 'd':
			{
				ok = valid(x, y + 1, N, M); // VERIFIC DACA MA POT DEPLASA

				if(ok)
				{
					y = y + 1;
				}
				else
				{
					c = c_pred;
				}

				if(NR % 2 == 0)
				{
					obs_mobil(x, y, &x1, &y1, c1, &x2, &y2, c2, &x3, &y3, c3);
				}

				GAME_OVER = GAME(x, y, x1, y1, x2, y2, x3, y3);

				if(GAME_OVER)
				{
					printf("GAME OVER\n");
					return;
				}
				else
				{
					print_matrix(x, y, c, N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3);
				}

				break;
			}
		}

		c_pred = c;

		scanf("%c", &c); // CITIRE ENTER

		if(x == N && y == M)
		{
			printf("GAME COMPLETED\n");
			break;
		}
	}
}

int main()
{
	int N, M, x, y, P;

	scanf("%d %d", &N, &M); // DIMENSIUNE TABLA

	scanf("%d %d", &x, &y); // POZITIE INITIALA

	scanf("%d", &P); // NR OBSTACOLE

	int x1, x2, x3, y1, y2, y3;
    char c, c1, c2, c3;

    // INITIALIZAM COORDONATELE OBSTACOLELOR CU -1 SI TIPUL LOR CU '0'

	x1 = y1 = -1;
	x2 = y2 = -1;
	x3 = y3 = -1;

	c1 = c2 = c3 = '0';

	if(P > 0)
	{
		scanf("%c", &c); // CITIRE ENTER
	}

	if(P == 1)
	{
		scanf("%d %d %c", &x1, &y1, &c1);
	}
	else
		if(P == 2)
		{
			scanf("%d %d %c", &x1, &y1, &c1);

			scanf("%c", &c); // CITIRE ENTER

			scanf("%d %d %c", &x2, &y2, &c2);
		}
		else
			if(P == 3)
			{
				scanf("%d %d %c", &x1, &y1, &c1);

				scanf("%c", &c); // CITIRE ENTER

				scanf("%d %d %c", &x2, &y2, &c2);

				scanf("%c", &c); // CITIRE ENTER

				scanf("%d %d %c", &x3, &y3, &c3);
			}


	print_matrix(y, x, 's', N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3); // AFISARE TABLA INITIALA

	solve(y, x, N, M, x1, y1, c1, x2, y2, c2, x3, y3, c3);

	return 0;
}
