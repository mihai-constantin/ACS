#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define min(a,b) ((a < b) ? a : b)
#define numberOfTests 100

const int size[numberOfTests][2] ={ {40, 5}, {80, 7}, {20, 12}, {64, 16}, {92, 17}, {49, 16}, {66, 17}, {99, 19}, {83, 21}, {63, 19}};


const int digits[10][6][6] = {
    {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// ZERO
    {{0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}},	// ONE
    {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// TWO
    {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// THREE
    {{0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}},	// FOUR
    {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}},	// FIVE
    {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}},	// SIX
    {{0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// SEVEN
    {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// EIGHT
    {{1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}},	// NINE
};

// Informs the compiler to not add padding for these structs
#pragma pack(1)

typedef struct {
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   imageDataOffset; /* Offset to the start of image data */
} bmp_fileheader;


typedef struct {
    unsigned int   biSize; /* Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes;
    unsigned short bitPix;
    unsigned int   biCompression;
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} bmp_infoheader;


typedef struct {
    unsigned char R,G,B;
} pixel;


typedef struct {
    bmp_fileheader fileHeader;
    bmp_infoheader infoHeader;
    pixel** bitmap;
} bmp_image;


#pragma pack()

bmp_image* create_image(int width, int height) {
    bmp_image *image = (bmp_image*) malloc(sizeof(bmp_image));
    int i, j;

    int padding = 4 - (image->infoHeader.width * 3) % 4;
    if (padding == 4)
	padding = 0;

    image->fileHeader.fileMarker1 = 'B';
    image->fileHeader.fileMarker2 = 'M';
    image->fileHeader.bfSize = (width * 3 + padding) * height + 54;
    image->fileHeader.unused1 = 0;
    image->fileHeader.unused2 = 0;
    image->fileHeader.imageDataOffset = 54;

    image->infoHeader.biSize = 40;
    image->infoHeader.height = height;
    image->infoHeader.width = width;
    image->infoHeader.planes = 1;

    image->infoHeader.bitPix = 24;
    image->infoHeader.biCompression = 0;
    image->infoHeader.biSizeImage = (width * 3 + padding) * height; 
    image->infoHeader.biXPelsPerMeter = 0;
    image->infoHeader.biYPelsPerMeter = 0;
    image->infoHeader.biClrUsed = 0;
    image->infoHeader.biClrImportant = 0;


    image->bitmap = (pixel**) malloc(height * sizeof(pixel*));
    for (i = 0; i < height; i++) {
	image->bitmap[i] = (pixel*) malloc((image->infoHeader.width + padding) * sizeof(pixel));
	for (j = 0; j < image->infoHeader.width + padding; j++) {
	    image->bitmap[i][j].R = 255;
	    image->bitmap[i][j].G = 255;
	    image->bitmap[i][j].B = 255;
	}
    }

    return image;
}

void add_digit(bmp_image *im, int digit, int start_i, int start_j, int B, int G, int R, int **ok, int *empty, int bad_pixel_percentage) {
    int i, j;

    // check if we have enough space to fill the new digit
    if (start_i + 4 >= im->infoHeader.height) return;
    if (start_j + 4 >= im->infoHeader.width) return;

    // check if the required space is not occupied by another digit
    for (i = -1; i <= 5; i++)
	for (j = -1; j <= 5; j++) {
	    if (start_i + i <= 0 || start_i + i >= im->infoHeader.height) continue;
	    if (start_j + j <= 0 || start_j + j >= im->infoHeader.width) continue;

	    if (ok[start_i + i][start_j + j] == 1) return;
	}

    // add to the image the new constructed digit
    for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
	    if (digits[digit][i][j] == 1) {
		im->bitmap[start_i + i][start_j + j].R = R;
		im->bitmap[start_i + i][start_j + j].G = G;
		im->bitmap[start_i + i][start_j + j].B = B;
	    }

    if (rand() % 10 < bad_pixel_percentage) {
	int bad_pixel_i = rand() % 5;
	int bad_pixel_j = rand() % 5;

	if (digit == 1) bad_pixel_j = rand() % 2 + 3;
	if (digit == 7) {
	    if (rand() % 2) bad_pixel_j = rand() % 2 + 3;
	    else bad_pixel_i = rand() % 2 + 3;
	}

	if (digits[digit][bad_pixel_i][bad_pixel_j] == 1) {
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].R = 255;
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].G = 255;
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].B = 255;
	} else {
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].R = R;
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].G = G;
	    im->bitmap[start_i + bad_pixel_i][start_j + bad_pixel_j].B = B;
	}
    }


    // update the boolean matrix
    for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
	    ok[start_i + i][start_j + j] = 1;
    *empty = 0;
}


bmp_image* readBMP(char *s) {
    int i;
    FILE *f = fopen(s, "rb");
    if (!f) {
	printf("File not found!\n");
	return NULL;
    }

    bmp_image *image = (bmp_image*) malloc(sizeof(bmp_image));

    fread(&image->fileHeader,sizeof(bmp_fileheader),1,f);
    fread(&image->infoHeader,sizeof(bmp_infoheader),1,f);

    int padding = 4 - (image->infoHeader.width * 3) % 4;
    if (padding == 4)
	padding = 0;

    image->bitmap = (pixel**) malloc(image->infoHeader.height * sizeof(pixel*));
    for (i=0;i<image->infoHeader.height;i++)
    {
	image->bitmap[i] = (pixel*) malloc((image->infoHeader.width + padding) * sizeof(pixel));
	fread(image->bitmap[i],sizeof(pixel),image->infoHeader.width,f);
    }

    fclose(f);
    return image;
}

void writeBMP(bmp_image* image, char *s)
{
    int i,j;
    FILE *f = fopen(s,"wb");

    fwrite(&image->fileHeader,14,1,f);
    fwrite(&image->infoHeader,sizeof(bmp_infoheader),1,f);

    int padding = 4 - (image->infoHeader.width * 3) % 4;
    if (padding == 4)
	padding = 0;
    char paddingPixel = 0;

    for (i=0;i<image->infoHeader.height;i++)
    {
	fwrite(image->bitmap[i],sizeof(pixel),image->infoHeader.width,f);
	for (j=1;j<=padding;j++)
	    fwrite(&paddingPixel,sizeof(char),1,f);
    }

    fclose(f);
    return;
}


void freeImage(bmp_image** image)
{
    int i;

    for (i=0;i<(*image)->infoHeader.height;i++)
	free((*image)->bitmap[i]);
    free((*image)->bitmap);

    free(*image);
}

int isWhite(pixel P) {
    if (P.R != 255) return 0;
    if (P.G != 255) return 0;
    if (P.B != 255) return 0;
    return 1;
}

void print_im(bmp_image *im) {
//    printf("FILE HEADER\n");
//
//    printf("fileMarker1       -> %d\n", im->fileHeader.fileMarker1);
//    printf("fileMarker2       -> %d\n", im->fileHeader.fileMarker2);
//    printf("bfSize            -> %d\n", im->fileHeader.bfSize);
//    printf("unused1           -> %d\n", im->fileHeader.unused1);
//    printf("unused2           -> %d\n", im->fileHeader.unused2);
//    printf("image data offset -> %d\n", im->fileHeader.imageDataOffset);

    printf("\n\nINFO HEADER\n");
    printf("biSize            -> %d\n", im->infoHeader.biSize);
    printf("width             -> %d\n", im->infoHeader.width);
    printf("height            -> %d\n", im->infoHeader.height);
    printf("planes            -> %d\n", im->infoHeader.planes);
    printf("bitPix            -> %d\n", im->infoHeader.bitPix);
    printf("biCompression     -> %d\n", im->infoHeader.biCompression);
    printf("biSizeImage       -> %d\n", im->infoHeader.biSizeImage);
    printf("biXPelsPerMeter   -> %d\n", im->infoHeader.biXPelsPerMeter);
    printf("biYPelsPerMeter   -> %d\n", im->infoHeader.biYPelsPerMeter);
    printf("biClrUsed         -> %d\n", im->infoHeader.biClrUsed);
    printf("biClrImportant    -> %d\n", im->infoHeader.biClrImportant);
    
}

char* int_to_string(int nr) {
    char *result = (char*) malloc(5);
    int cnt = 0, i;

    while (nr) {
	result[cnt++] = nr % 10 + '0';
	nr /=10;
    }
    result[cnt] = '\0';
    for (i = 0; i < cnt / 2; i++) {
	char aux = result[i];
	result[i] = result[cnt - i - 1];
	result[cnt - i - 1] = aux;
    }
    return result;
}

void generate_tests(char *captcha_name, int bad_pixel_percentage, int lights_percentage) {

    int test;
    srand(time(NULL));
    
    for (test = 0; test < numberOfTests; test++) {
	int maxDigit = min(test / 10 + 1, 9);
	int width = size[test % 10][0];
	int height = size[test % 10][1];
	char image_name[20];
	strcpy(image_name, captcha_name);
	strcat(image_name, int_to_string(test + 1));
	strcat(image_name, ".bmp");

	bmp_image *image = create_image(width, height);
	int i, j;
	int **ok = (int**) malloc(height * sizeof(int*));
	for (i = 0; i < height; i++)
	    ok[i] = (int*) calloc(width, sizeof(int));

	int empty = 1;
	for (i = 0; i < width - 5; i++) {
		int type = rand() % 101;
	    int digit = rand() % (maxDigit + 1);
	    int x_position = rand() % height;
	    int y_position = i;

	    int R = rand() % 255;
	    int G = rand() % 255;
	    int B = rand() % 255;

	    int pr = rand() % 10;
	    if (empty || pr < (test / 10) % 5 + 2) 
	        if(type >= lights_percentage) {
	            add_digit(image, digit, x_position, y_position, R, G, B, ok, &empty, bad_pixel_percentage);
	        } else {
	            int tr = 1;
	            for (i = -1; i <= 5; i++)
	            for (j = -1; j <= 5; j++) {
	                if (x_position + i <= 0 || x_position + i >= image->infoHeader.height) continue;
	                if (y_position + j <= 0 || y_position + j >= image->infoHeader.width) continue;
	                if (ok[x_position + i][y_position + j] == 1) {
	                    tr = 0;
	                    break;
	                }
	            }
	            if(tr) {
    	            image->bitmap[x_position][y_position].R = R;
    		        image->bitmap[x_position][y_position].G = G;
    		        image->bitmap[x_position][y_position].B = B;
    		        ok[x_position][y_position] = 1;
	            }
	        }
	}

	writeBMP(image, image_name);	
    }
}

void generate_input_files() {
    int test;
    for (test = 0; test < numberOfTests; test++) {
	char input_name[20] = "input";
	strcat(input_name, int_to_string(test + 1));
	strcat(input_name, ".txt");

	char captcha[20] = "captcha";
	strcat(captcha, int_to_string(test + 1));
	strcat(captcha, ".bmp");

	char captchaB[20] = "captchaB";
	strcat(captchaB, int_to_string(test + 1));
	strcat(captchaB, ".bmp");

	FILE *f = fopen(input_name, "w");
	
	fprintf(f, "%s\n", captcha);
	int R = rand() % 255;
	int G = rand() % 255;
	int B = rand() % 255;
	fprintf(f, "%d %d %d\n", R, G, B);

	int i, first = 1;
	int *digits = (int*) calloc(10, sizeof(int));
	for (i = 0; i < 10; i++) {
	    int digit = rand() % 10;
	    if (digits[digit]) continue;

	    // chance of 50% to remove a digit that may exist in the test
	    // and 5% chance to remove non-existing digit
	    int pr;
	    if (digit <= test + 1) pr = 50;
	    else pr = 5;
	    
	    if (rand() % 100 < pr) {
		if (!first) fprintf(f, " ");
		first = 0;
		fprintf(f, "%d", digit);
		digits[digit] = 1;
	    }
	}
	fprintf(f, "\n");
	fprintf(f, "%s\n", captchaB);

	fclose(f);
    }
}

int main() {

    char captcha_name[20] = "captchaB";
    generate_tests(captcha_name, 0, 25);
//    generate_tests();
//    generate_input_files();
}
