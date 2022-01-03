// CONSTANTIN MIHAI - 311 CD

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp_header.h"

#define dmax 101

bool distance(int x1, int y1, int x2, int y2)
{
	int d = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

	if(d <= 49) return true;

	return false;
}

int main()
{
	FILE *in, *input, *output;

	in = fopen("input.txt", "r");

	int i, j, length, col;

	char *file = (char*)calloc(dmax, sizeof(char));

	for(i = 1; i <= 4; i++)
	{
		fgets(file, dmax, in);
	}

	length = strlen(file);

	file[length - 1] = '\0';

	input = fopen(file, "rb");

	// output

	char s[] = "_bonus.bmp";

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

	element_2 *pos_pixels_isolated;

	pos_pixels_isolated = (element_2*)calloc(dmax, sizeof(element_2));

	int isolated = 0;

	for(i = InfoHeader.height - 1; i >= 0; i--)
	{
		for(j = 0; j < InfoHeader.width; j++)
		{
			if(bmp_matrix[i][j] == 1)
			{
				// verify if the pixel is isolated

				bool ok = true;

				if(i - 1 >= 0)
					if(bmp_matrix[i - 1][j] == 1)
						ok = false;

				if(i + 1 < InfoHeader.height)
					if(bmp_matrix[i + 1][j] == 1)
						ok = false;

				if(j - 1 >= 0)
					if(bmp_matrix[i][j - 1] == 1)
						ok = false;

				if(j + 1 < InfoHeader.width)
					if(bmp_matrix[i][j + 1] == 1)
						ok =false;

				if(ok)
				{
					isolated++;

					pos_pixels_isolated[isolated].x = i;
					pos_pixels_isolated[isolated].y = j;

					pos_pixels_isolated[isolated].Blue = Blue[i][j];
					pos_pixels_isolated[isolated].Green = Green[i][j];
					pos_pixels_isolated[isolated].Red = Red[i][j];

					bmp_matrix[i][j] = 0; // set 0 on (i, j) position in bmp_matrix
				} 
			}
		}
	}

	int B, G, R, k, nr;

	// solution

	for(i = 0; i < InfoHeader.height; i++)
	{
		for(j = 0; j < InfoHeader.width; j++)
		{
			if(bmp_matrix[i][j] == 1)
			{
				B = Blue[i][j];
				G = Green[i][j];
				R = Red[i][j];

				nr = 1;

				// the pixel is colored and it is part of a digit

				for(k = 1; k <= isolated; k++)
				{
					if(distance(i, j, pos_pixels_isolated[k].x, pos_pixels_isolated[k].y))
					{
						nr++;

						B += pos_pixels_isolated[k].Blue;
						G += pos_pixels_isolated[k].Green;
						R += pos_pixels_isolated[k].Red;
					}	
				}

				Blue[i][j] = B / nr;
				Green[i][j] = G / nr;
				Red[i][j] = R / nr;
			}
		}
	}

	for(i = 1; i <= isolated; i++)
	{
		bmp_matrix[ pos_pixels_isolated[i].x ][ pos_pixels_isolated[i].y ] = 1;
	}

	// write in the output file
	for(i = InfoHeader.height - 1; i >= 0; i--)
	{
		for(j = 0; j < InfoHeader.width; j++)
		{
			if(bmp_matrix[i][j] == 0)
			{
				fwrite(&character, sizeof(char), 1, output);
				fwrite(&character, sizeof(char), 1, output);
				fwrite(&character, sizeof(char), 1, output);
			}
			else
			{
				fwrite(&Blue[i][j], sizeof(unsigned char), 1, output);
				fwrite(&Green[i][j], sizeof(unsigned char), 1, output);
				fwrite(&Red[i][j], sizeof(unsigned char), 1, output);
			}
		}

		char buf[4] = {0};
		
		fwrite(buf, sizeof(char), padding, output); // add padding to output
	}

	return 0;
}