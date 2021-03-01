// CONSTANTIN MIHAI - 311 CD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
void write(bool ok, int i, int j, int **bmp_matrix, FILE *out, int number)
{
	int lin, col;

	if(ok == true)
	{
		found = 1;

		fprintf(out, "%d", number);

		for(lin = i; lin <= i + 4; lin++)
		{	
			for(col = j; col <= j + 4; col++)
			{
				bmp_matrix[lin][col] = 0;
			}
		}
	}
}

int main()
{
	FILE *in, *input, *out;

	in = fopen("input.txt", "r");

	int i, j, col;

	char *file = (char*)calloc(dmax, sizeof(char));

	fscanf(in, "%s", file); 

	input = fopen(file, "rb");

	// output

	char s[] = "_task2.txt";

	int length = strlen(file);

	file[length - 4] = '\0';

	strcat(file, s);

	out = fopen(file, "w");

	bmp_fileheader FileHeader;
	bmp_infoheader InfoHeader;

	// read the bmp_fileheader
	fread(&FileHeader, sizeof(bmp_fileheader), 1, input);

	//read the bmp_infoheader
	fread(&InfoHeader, sizeof(bmp_infoheader), 1, input);

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
			}
			else
			{
				// 255 255 255
				bmp_matrix[i][col] = 0;
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

	for(j = InfoHeader.width - 1; j >= 0; j--)
	{
		for(i = 0; i < InfoHeader.height; i++)
		{
			if(bmp_matrix[i][j] == 1)
			{
				found = 0;

				if(bmp_matrix[i][j - 1] == 1 && j - 1 >= 0) 
				{
					// the number is 0, 2, 3, 5, 6, 7, 8 or 9

					// verify if the number is 0
					ok = valid(i, j - 4, bmp_matrix, Matrix_0);
					write(ok, i, j - 4, bmp_matrix, out, 0);

					//verify if the number is 2
					ok = valid(i, j - 4, bmp_matrix, Matrix_2);
					write(ok, i, j - 4, bmp_matrix, out, 2);

					//verify if the number is 3
					ok = valid(i, j - 4, bmp_matrix, Matrix_3);
					write(ok, i, j - 4, bmp_matrix, out, 3);

					//verify if the number is 5
					ok = valid(i, j - 4, bmp_matrix, Matrix_5);
					write(ok, i, j - 4, bmp_matrix, out, 5);

					//verify if the number is 6
					ok = valid(i, j - 4, bmp_matrix, Matrix_6);
					write(ok, i, j - 4, bmp_matrix, out, 6);

					//verify if the number is 7
					ok = valid(i, j - 4, bmp_matrix, Matrix_7);
					write(ok, i, j - 4, bmp_matrix, out, 7);

					//verify if the number is 8
					ok = valid(i, j - 4, bmp_matrix, Matrix_8);
					write(ok, i, j - 4, bmp_matrix, out, 8);

					//verify if the number is 9
					ok = valid(i, j - 4, bmp_matrix, Matrix_9);
					write(ok, i, j - 4, bmp_matrix, out, 9);
				}
				else
					if(bmp_matrix[i + 2][j - 1] == 1 && j - 1 >= 0 && i + 2 < InfoHeader.height)
					{
						// verify if the number is 4
						ok = valid(i, j - 4, bmp_matrix, Matrix_4);
						write(ok, i, j - 4, bmp_matrix, out, 4);
					}

				if(!found)
				{
					fprintf(out, "1");

					bmp_matrix[i][j] = 0;
					bmp_matrix[i + 1][j] = 0;
					bmp_matrix[i + 2][j] = 0;
					bmp_matrix[i + 3][j] = 0;
					bmp_matrix[i + 4][j] = 0;
				}
			}
		}
	}

	// close the files

	fclose(in);
	fclose(input);
	fclose(out);

	// now, the output file contains the reverse string

	// read in the output file
	in = fopen(file, "r");

	char *answer = (char*)calloc(dmax, sizeof(char));

	fscanf(in, "%s", answer);

	fclose(in);

	// write in the output file 
	out = fopen(file, "w");

	// write the reversed string
	for(i = strlen(answer) - 1; i >= 0; i--)
	{
		fprintf(out, "%c", answer[i]);
	}

	fclose(out);

	return 0;
}
