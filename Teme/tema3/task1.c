// CONSTANTIN MIHAI - 311 CD

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_header.h"

#define dmax 101

int main()
{
	FILE *in, *input, *output;

	in = fopen("input.txt", "r");

	int B, G, R, i, j;

	char *file;

	file = (char*)calloc(dmax, sizeof(char));

	fscanf(in, "%s", file); 

	fscanf(in, "%d %d %d", &B, &G, &R);

	input = fopen(file, "rb");

	// output

	char s[] = "_task1.bmp";

	int length = strlen(file);

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

	for(i = InfoHeader.height - 1; i >= 0; i--)
	{
		fread(bmp_Image, sizeof(unsigned char), 3 * InfoHeader.width, input);

		for(j = 0; j < 3 * InfoHeader.width; j++)
		{
			// verify if the pixel is colored
			if(((int)(bmp_Image[j]) != 255) || ((int)(bmp_Image[j + 1]) != 255) || ((int)(bmp_Image[j + 2]) != 255))
			{
				bmp_Image[j] = B;
				bmp_Image[j + 1] = G;
				bmp_Image[j + 2] = R;
			}

			j += 2;
		}

		char buf[4]={0}; 

		fwrite(bmp_Image, sizeof(unsigned char), 3 * InfoHeader.width, output);

		fwrite(buf, sizeof(char), padding, output); // add padding to output

		//move file point to the next line
		fseek(input, padding, SEEK_CUR);
	}

	fclose(in);
	fclose(input);
	fclose(output);

	return 0;
}