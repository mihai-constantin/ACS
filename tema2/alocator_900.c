// CONSTANTIN MIHAI - 311CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

unsigned char *Arena; // ZONA DE MEMORIE
uint32_t N;  // NR OCTETI Arena

int *empty; // empty[i] = '0' <=> OCTETUL DE LA POSITIA i ESTE LIBER

uint32_t ind_start, ind_start_pred;

uint32_t nr_bloc;

uint32_t START_BLOC; // POZITIA PRIMULUI OCTET AL PRIMULUI BLOC DE LA UN MOMENT DAT

void INITIALIZE()
{
	Arena = (unsigned char*)calloc(N, sizeof(unsigned char));

	empty = (int*)calloc(N, sizeof(int));

	START_BLOC = 0;
}

void FINALIZE()
{
	free(Arena);
	free(empty);
}

void DUMP()
{
	uint32_t i;

	if(N > 0) // Arena ARE CEL PUTIN UN OCTET
	{
		printf("%08X\t", 0); // AFISAREA INDICELUI PRIMULUI BLOC
	}

	for(i = 0; i < N; i++)
	{
		printf("%02X ", Arena[i]);

		if(((i + 1) % 8) == 0 && ((i + 1) % 16) != 0)
		{
			printf(" ");
		}
		
		if((i + 1) % 16 == 0 && i != 0)
		{
			printf("\n");
			
			if((i + 1) != N)
			{
				printf("%08X\t", (i + 1));
			}
		}
	}

	if((N % 16) != 0) // DACA NR DE OCTETI AI ARENEI NU ESTE UN MULTIPLU DE 16, MAI AFISAM UN '\n'
	{
		printf("\n");
	}
}

// "IMPARTIM" NR size IN 4 OCTETI

void write(uint32_t first, uint32_t last, uint32_t size)
{
	uint32_t i, nr = -1;

	for(i = first; i <= last; i++)
	{
		nr++;
		Arena[i] = *((unsigned char *)&size + nr);
	}
}

void ALLOC(uint32_t size) // size - NR OCTETI DIMENSIUNE DATE
{
	// CAUT IN Arena O ZONA LIBERA DE DIMENSIUNE (12 + size) OCTETI DE LA STANGA LA DREAPTA

	uint32_t i, nr, pos, j, pos2;
	uint32_t dim = 12 + size;

	nr = 0;

	bool ok = false, gasit;

	for(i = 0; i < N; i++)
	{
		if(empty[i] == 0)
		{
			nr++;

			if(nr == dim) // AM GASIT O ZONA LIBERA DE (12 + size) OCTETI
			{
				ok = true;
				break;
			}
		}
		else
		{
			if(nr < dim) 
			{
				nr = 0;
			}
		}
	}

	if(ok) // AM GASIT O ZONA LIBERA DE (12 + size) OCTETI
	{
		// VERIFIC DACA FAC ALLOC PE PRIMUL BLOC

		pos = i; // POZITIA ULTIMULUI OCTET DIN ZONA LIBERA GASITA

		ind_start = pos - dim + 1; // POZITIA PRIMULUI OCTET DIN ZONA LIBERA GASITA

		if((pos < START_BLOC) || (pos - dim + 1) == START_BLOC)
		{
			// FAC ALLOC PE PRIMUL BLOC

			//CAUT URMATORUL BLOC

			gasit = false;

			for(j = pos + 1; j < N; j++)
			{
				if(empty[j] != 0)
				{
					gasit = true;
					break;
				}
			}

			// j - POZITIA PRIMULUI OCTET DIN BLOCUL URMATOR

			if(gasit == true)
			{
				write(ind_start, ind_start + 3, j);
			}

			START_BLOC = pos - dim + 1;
		
			write(ind_start + 8, ind_start + 11, size);
		}
		else
		{
			// VREAU SA VERIFIC DACA FAC ALLOC PE ULTIMUL BLOC

			gasit = true;

			for(j = pos + 1; j < N; j++)
			{
				if(empty[j] != 0)
				{
					gasit = false;
					break;
				}
			}

			if(gasit == true)
			{
				// FAC ALLOC PE ULTIMUL BLOC

				// CAUT BLOCUL PRECEDENT

				gasit = false;

				for(j = ind_start - 1; !gasit; j--)
				{
					if(empty[j] != 0)
					{
						gasit = true;
					}
				}

				// j - POZITIA ULTIMULUI OCTET DIN BLOCUL PRECEDENT

				pos2 = j;

				while(empty[j] == empty[pos2])
				{
					if(j == 0) 
					{
						break;
					}	

					j--;
				}

				uint32_t ans = j;

				if(ans != 0)
				{
					ans += 1;
				}

				// ans - POZITIA PRIMULUI OCTET DIN BLOCUL PRECEDENT

				write(ans, ans + 3, ind_start);

				write(ind_start + 4, ind_start + 7, ans);

				write(ind_start + 8, ind_start + 11, size);
			}
			else
			{
				// FAC ALLOC PE UN BLOC CU 2 VECINI

				// CAUT BLOCUL PRECEDENT

				gasit = false;

				for(j = ind_start - 1; !gasit; j--)
				{
					if(empty[j] != 0)
					{
						gasit = true;
					}
				}  

				// j - POZITIA ULTIMULUI OCTET DIN BLOCUL PRECEDENT

				pos2 = j;

				while(empty[j] == empty[pos2])
				{
					if(j == 0) 
					{
						break;
					}	

					j--;
				}

				uint32_t ans = j;

				if(ans != 0)
				{
					ans += 1;
				}

				// ans - POZITIA PRIMULUI OCTET DIN BLOCUL PRECEDENT

				write(ans, ans + 3, ind_start);
				write(ind_start + 4, ind_start + 7, ans);

				// CAUT BLOCUL URMATOR

				for(j = pos + 1; j < N; j++)
				{
					if(empty[j] != 0)
					{
						break;
					}
				}

				// j - POZITIA PRIMULUI OCTET DIN BLOCUL URMATOR

				write(ind_start, ind_start + 3, j);
				write(ind_start + 8, ind_start + 11, size);

				write(j + 4, j + 7, ind_start);
			}
		}

		uint32_t ind_start_date = pos - size + 1;  // POZITIA PRIMULUI OCTET DIN SECTIUNEA DE DATE A ZONEI LIBERE GASITE
	
		printf("%d\n", ind_start_date);

		// ZONA DEVINE OCUPATA

		nr_bloc++;

		for(i = ind_start; i <= pos; i++)
		{
			empty[i] = nr_bloc;
		}
	}
	else
	{
		printf("0\n");
	}
}

// AFLAM CE VALOARE SE AFLA PE OCTETII DE LA POZITIILE [first - last]

uint32_t Length(uint32_t first, uint32_t last)
{
	uint32_t val, ans, i, nr;

	nr = ans = 0;

	for(i = first; i <= last; i++)
	{
		val = Arena[i];

		ans += val * pow(16, 2 * nr);

		nr++;
	}

	return ans;
}

void FREE(uint32_t index)
{ 
	uint32_t i, first;
	uint32_t val = Length(index - 12, index - 9); // POZITIA PRIMULUI OCTET AL BLOCULUI URMATOR
	uint32_t lung = Length(index - 8, index - 5); // POZITIA PRIMULUI OCTET AL BLOCULUI PRECEDENT
	uint32_t last = Length(index - 4, index - 1); // LUNGIMEA SECTIUNII DE DATE A BLOCULUI CE VA FI ELIBERAT

	first = index - 12; // POZITIA PRIMULUI OCTET DIN BLOCUL CE VA FI ELIBERAT

	if(index - 12 == START_BLOC) //DAU FREE PRIMULUI BLOC DIN Arena
	{
		START_BLOC = val; // MODIFICAM INDICELE DE START AL PRIMULUI BLOC DIN Arena

		write(START_BLOC + 4, START_BLOC + 7, 0);
	}
	else
	{
		// DACA SCOATEM UN BLOC, VECINII SE SCHIMBA

		write(lung, lung + 3, val); // INDEXUL BLOCULUI URMATOR

		write(val + 4, val + 7, lung); // INDEXUL BLOCULUI PRECEDENT
	}

	// ELIBERAM ZONA

	for(i = first; i <= index + last - 1; i++)
	{
		empty[i] = 0;
		Arena[i] = 0;
	}
}

void FILL(uint32_t index, uint32_t size, uint32_t value)
{
	uint32_t i, nr = 0;
	bool ok = false;

	do
	{
		uint32_t length = Length(index - 4, index - 1);

		for(i = index; i <= index + length - 1; i++)
		{
			Arena[i] = value;

			nr++;

			if(nr == size) 
			{
				ok = true;
				break;
			}
		}

		if((Length(index - 12, index - 9) + 12) > index)
		{
			index = Length(index - 12, index - 9) + 12; // INDEXUL DE START AL SECTIUNII DE DATE AL URMATORULUI BLOC
		}
		
	}while(ok == false);
}

void parse_command(char *line)
{
	const char *delims = " \n";

	char *cmd_name = strtok(line, delims);

	if(!strcmp(cmd_name, "INITIALIZE"))
	{
		char *size_str = strtok(NULL, delims);
		uint32_t size = atoi(size_str);

		N = size;

		INITIALIZE();
	}
	else
		if(!strcmp(cmd_name, "FINALIZE"))
		{
			FINALIZE();
		}
		else
			if(!strcmp(cmd_name, "DUMP"))
			{	
				DUMP();
			}
			else
				if(!strcmp(cmd_name, "ALLOC"))
				{
					char *size_str = strtok(NULL, delims);
					uint32_t size = atoi(size_str);

					ALLOC(size);
				}
				else
					if(!strcmp(cmd_name, "FREE"))
					{
						char *index_str = strtok(NULL, delims);
						uint32_t index = atoi(index_str);

						FREE(index);
					}
					else
						if(!strcmp(cmd_name, "FILL"))
						{
							char *index_str = strtok(NULL, delims);
							uint32_t index = atoi(index_str);

							char *size_str = strtok(NULL, delims);
							uint32_t size = atoi(size_str);

							char *value_str = strtok(NULL, delims);
							uint32_t value = atoi(value_str);

							FILL(index, size, value);
						}
}

void read()
{
	ssize_t input;
	char *line = NULL;
	size_t length;

	while( (input = getline(&line, &length, stdin)) != -1 ) // CITIRE LINIE CU LINIE
	{
		printf("%s", line);

		parse_command(line);
	}

	free(line);
}

int main()
{
	read();

	return 0;
}