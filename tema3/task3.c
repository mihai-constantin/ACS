// CONSTANTIN MIHAI - 311 CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bmp_header.h"

#define dmax 101

int found;

/* searching for a digit in bmp_matrix */
bool valid(int i, int j, int **bmp_matrix, int Matrix[5][5])
{
	int lin, col, line, column;

	line = 0;

	for(lin = i; lin <= i + 4; lin++)
	{
		column = 0;

		for(col = j; col <= j + 4; col++)
		{
			if(bmp_matrix[lin][col] != Matrix[line][column])
			{
				return false;
			}

			column++;
		}

		line++;
	}

	return true;
}

/* set 0 on elements from bmp_matrix */
void write_2(bool ok, int i, int j, int **bmp_matrix)
{
	int lin, col;

	if(ok == true)
	{
		found = 1;

		for(lin = i; lin <= i + 4; lin++)
		{	
			for(col = j; col <= j + 4; col++)
			{
				bmp_matrix[lin][col] = 0;
			}
		}
	}
}

/* copy the content from bmp_matrix to bmp_new_matrix */
void write_3(int i, int j, int **bmp_new_matrix, int **bmp_matrix)
{
	int lin, col;

	for(lin = i; lin <= i + 4; lin++)
	{	
		for(col = j; col <= j + 4; col++)
		{
			bmp_new_matrix[lin][col] = bmp_matrix[lin][col];
		}
	}
}

int main()
{
	FILE *in, *input, *output;

	in = fopen("input.txt", "r");

	int B, G, R, i, j, lin, col, length, sol;

	char *file = (char*)calloc(dmax, sizeof(char));
	char *string = (char*)calloc(dmax, sizeof(char));

	fscanf(in, "%s", file); 

	fscanf(in, "%d %d %d", &B, &G, &R);

	// read the enter 
	char enter;
	fscanf(in, "%c", &enter);

	fgets(string, dmax, in);

	int number[10] = {0}; // number[i] == 1 means that digit i must be eliminated

	length = strlen(string);

	for(i = 0; i < length; i++)
	{
		if(string[i] >= '0' && string[i] <= '9')
		{
			sol = string[i] - '0';
			number[sol] = 1;
		}
	}

	input = fopen(file, "rb");

	// output

	char s[] = "_task3.bmp";

	length = strlen(file);

	file[length - 4] = '\0';

	strcat(file, s);

	output = fopen(file, "wb");

	bmp_fileheader FileHeader;
	bmp_infoheader InfoHeader;

	// read the bmp_fileheader
	fread(&FileHeader, sizeof(bmp_fileheader), 1, input);

	//write the bmp_fileheader
	fwrite(&FileHeader, sizeof(bmp_fileheader), 1, output);

	//read the bmp_infoheader
	fread(&InfoHeader, sizeof(bmp_infoheader), 1, input);

	//write the bmp_infoheader
	fwrite(&InfoHeader, sizeof(bmp_infoheader), 1, output);

	// move file point to the begging of bitmap data
	fseek(input, FileHeader.imageDataOffset, SEEK_SET);

	int padding = InfoHeader.width % 4; // formula for padding

	unsigned char *bmp_Image;

	// allocate enough memory for bmp_Image 
	bmp_Image = (unsigned char*)calloc(3 * InfoHeader.width, sizeof(unsigned char));

	int **bmp_matrix;

	// allocate enough memory for bmp_matrix
	bmp_matrix = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		bmp_matrix[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// matrix Blue
	int **Blue = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		Blue[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// matrix Green
	int **Green = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		Green[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// matrix Red
	int **Red = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		Red[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// bmp_new_matrix
	int **bmp_new_matrix = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		bmp_new_matrix[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	char character;

	for(i = InfoHeader.height - 1; i >= 0; i--)
	{
		fread(bmp_Image, sizeof(unsigned char), 3 * InfoHeader.width, input);

		col = 0;

		for(j = 0; j < 3 * InfoHeader.width; j++)
		{
			// verify if the pixel is colored
			if(((int)(bmp_Image[j]) != 255) || ((int)(bmp_Image[j + 1]) != 255) || ((int)(bmp_Image[j + 2]) != 255))
			{
				bmp_matrix[i][col] = 1;

				Blue[i][col] = (int)(bmp_Image[j]);
				Green[i][col] = (int)(bmp_Image[j + 1]);
				Red[i][col] = (int)(bmp_Image[j + 2]);
			}
			else
			{
				// 255 255 255
				bmp_matrix[i][col] = 0;
				
				character = bmp_Image[j];
			}

			j += 2;

			col++;
		}

		//move file point to the next line
		fseek(input, padding, SEEK_CUR);
	}

	int Matrix_0[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int Matrix_2[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};
	int Matrix_3[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int Matrix_4[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}};
	int Matrix_5[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int Matrix_6[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int Matrix_7[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}};
	int Matrix_8[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int Matrix_9[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};

	bool ok;

	int NR_CIF = 0;
	int NR_CIF_LEFT = 0;

	element *pos_cif, *pos_cif_left;

	pos_cif = (element*)calloc(dmax, sizeof(element));
	pos_cif_left = (element*)calloc(dmax, sizeof(element));

	for(j = InfoHeader.width - 1; j >= 0; j--)
	{
		for(i = 0; i < InfoHeader.height; i++)
		{
			if(bmp_matrix[i][j] == 1)
			{
				NR_CIF++;

				pos_cif[NR_CIF].x = i;
				pos_cif[NR_CIF].y = j - 4;

				found = 0;

				if(bmp_matrix[i][j - 1] == 1 && j - 1 >= 0) 
				{
					// the number is 0, 2, 3, 5, 6, 7, 8 or 9

					// verify if the number is 0
					ok = valid(i, j - 4, bmp_matrix, Matrix_0);

					if(!number[0] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 2
					ok = valid(i, j - 4, bmp_matrix, Matrix_2);

					if(!number[2] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 3
					ok = valid(i, j - 4, bmp_matrix, Matrix_3);

					if(!number[3] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 5
					ok = valid(i, j - 4, bmp_matrix, Matrix_5);

					if(!number[5] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 6
					ok = valid(i, j - 4, bmp_matrix, Matrix_6);

					if(!number[6] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 7
					ok = valid(i, j - 4, bmp_matrix, Matrix_7);

					if(!number[7] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 8
					ok = valid(i, j - 4, bmp_matrix, Matrix_8);

					if(!number[8] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);

					//verify if the number is 9
					ok = valid(i, j - 4, bmp_matrix, Matrix_9);

					if(!number[9] && ok)
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					write_2(ok, i, j - 4, bmp_matrix);
				}
				else
					if(bmp_matrix[i + 2][j - 1] == 1 && j - 1 >= 0 && i + 2 < InfoHeader.height)
					{
						// verify if the number is 4
						ok = valid(i, j - 4, bmp_matrix, Matrix_4);

						if(!number[4] && ok)
						{
							NR_CIF_LEFT++;

							write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

							pos_cif_left[NR_CIF_LEFT].x = i;
							pos_cif_left[NR_CIF_LEFT].y = j - 4;
						}

						write_2(ok, i, j - 4, bmp_matrix);
					}

				if(!found)
				{
					if(!number[1])
					{
						NR_CIF_LEFT++;

						write_3(i, j - 4, bmp_new_matrix, bmp_matrix);

						pos_cif_left[NR_CIF_LEFT].x = i;
						pos_cif_left[NR_CIF_LEFT].y = j - 4;
					}

					bmp_matrix[i][j] = 0;
					bmp_matrix[i + 1][j] = 0;
					bmp_matrix[i + 2][j] = 0;
					bmp_matrix[i + 3][j] = 0;
					bmp_matrix[i + 4][j] = 0;
				}
			}
		}
	}

	// final_bmp_matrix
	int **final_bmp_matrix = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		final_bmp_matrix[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// final_Blue
	int **final_Blue = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		final_Blue[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// final_Green
	int **final_Green = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		final_Green[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// final_Red
	int **final_Red = (int**)calloc(InfoHeader.height + 1, sizeof(int*));

	for(i = 0; i < InfoHeader.height; i++)
	{
		final_Red[i] = (int*)calloc(InfoHeader.width + 1, sizeof(int));
	}

	// move the digits to the right positions

	int Q = NR_CIF;

	int line, column;

	for(i = NR_CIF_LEFT; i >= 1; i--)
	{	
		line = pos_cif_left[i].x;

		for(lin = pos_cif[Q].x; lin <= pos_cif[Q].x + 4; lin++)
		{
			column = pos_cif_left[i].y;

			for(col = pos_cif[Q].y; col <= pos_cif[Q].y + 4; col++)
			{
				final_bmp_matrix[lin][col] = bmp_new_matrix[line][column];

				if(final_bmp_matrix[lin][col] == 1) // pixel is colored
				{
					final_Green[lin][col] = Green[line][column];
					final_Red[lin][col] = Red[line][column];
					final_Blue[lin][col] = Blue[line][column];
				}

				column++;
			}

			line++;
		}

		Q--;
	}

	//write in the output file
	for(i = InfoHeader.height - 1; i >= 0; i--)
	{
		for(j = 0; j < InfoHeader.width; j++)
		{
			if(final_bmp_matrix[i][j] == 0)
			{
				fwrite(&character, sizeof(char), 1, output);
				fwrite(&character, sizeof(char), 1, output);
				fwrite(&character, sizeof(char), 1, output);
			}
			else
			{
				fwrite(&final_Blue[i][j], sizeof(unsigned char), 1, output);
				fwrite(&final_Green[i][j], sizeof(unsigned char), 1, output);
				fwrite(&final_Red[i][j], sizeof(unsigned char), 1, output);
			}
		}

		char buf[4] = {0};
		
		fwrite(buf, sizeof(char), padding, output); // add padding to output
	}

	// close the files
	fclose(in);
	fclose(input);
	fclose(output);

	return 0;
}