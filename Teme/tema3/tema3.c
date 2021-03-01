// CONSTANTIN MIHAI - 336CA

#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "helper.h"
#define MASTER 0

#define length 50
#define maxFilters 100

int max(int x, int y) {
	return x > y ? x : y;
}

int min(int x, int y) {
	return x < y ? x : y;
}

unsigned char** alloc_matrix(int height, int width, bool colored) {
	unsigned char **bit_map = (unsigned char**)calloc(height, sizeof(unsigned char*));
	for(int i = 0; i < height; i++) {
		if(!colored) {
			bit_map[i] = (unsigned char*)calloc(width, sizeof(unsigned char));
		}
		else {
			bit_map[i] = (unsigned char*)calloc(3 * width, sizeof(unsigned char));
		}
	}

	return bit_map;
}

char* create_input_image(char *argv[]) {
	char *input_image = (char*)calloc(length, sizeof(char));
	char *dot = strrchr(argv[1], '.');

	if(dot && !strcmp(dot, ".pgm")) {
		strcpy(input_image, "./input/PGM/");
		input_image = strcat(input_image, argv[1]);
	}
	else if(dot && !strcmp(dot, ".pnm")) {
		strcpy(input_image, "./input/PNM/");
		input_image = strcat(input_image, argv[1]);
	}

	return input_image;
}

char* create_output_image(char *argv[]) {
	char *output_image = (char*)calloc(length, sizeof(char));
	char *dot = strrchr(argv[1], '.');

	if(dot && !strcmp(dot, ".pgm")) {
		strcpy(output_image, "./output/PGM/");
		output_image = strcat(output_image, argv[2]);
	}
	else if(dot && !strcmp(dot, ".pnm")) {
		strcpy(output_image, "./output/PNM/");
		output_image = strcat(output_image, argv[2]);
	}

	return output_image;
}

char** create_filters(int argc, char *argv[]) {
	char **filters = (char**)calloc(maxFilters, sizeof(char*));
	for(int i = 0; i < argc - 3; i++) {
		filters[i] = (char*)calloc(10, sizeof(char));
	}

	for(int i = 0; i < argc - 3; i++) {
		strcpy(filters[i], argv[i + 3]);
		if(strcmp(filters[i], "smooth") && strcmp(filters[i], "blur") && strcmp(filters[i], "sharpen")
			&& strcmp(filters[i], "mean") && strcmp(filters[i], "emboss")) {
			printf("Invalid filter: %s\n", filters[i]);
			exit(0);
		}
	}

	return filters;
}

float calculate_new_pixel(int i, int j, unsigned char **bit_map, char **filters, int k, int width, int height) {
	int dlin[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dcol[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	int x[9] = {2, 2, 2, 1, 1, 1, 0, 0, 0};
	int y[9] = {2, 1, 0, 2, 1, 0, 2, 1, 0};

	float P = 0;
	int lin, col;
	for(int l = 0; l < 9; l++) {
		lin = i + dlin[l];
		col = j + dcol[l];
		if(lin >= 0 && lin < height && col >= 0 && col < width) {
			if(!strcmp(filters[k], "smooth")) {
				P += bit_map[lin][col] * smooth[x[l]][y[l]];
			}
			else if(!strcmp(filters[k], "blur")) {
				P += bit_map[lin][col] * blur[x[l]][y[l]];
			} 
			else if(!strcmp(filters[k], "sharpen")) {
				P += bit_map[lin][col] * sharpen[x[l]][y[l]];
			}
			else if(!strcmp(filters[k], "mean")) {
				P += bit_map[lin][col] * mean[x[l]][y[l]];
			}
			else if(!strcmp(filters[k], "emboss")) {
				P += bit_map[lin][col] * emboss[x[l]][y[l]];
			}
		}
	}

	if(P > 255.f) {
		P = 255.f;
	}
	else if (P < 0.f) {
		P = 0.f;
	}

	return P;
}

float calculate_new_pixel_R(int i, int j, unsigned char **bit_map, char **filters, int k, int width, int height) {
	float R = 0;
	int lin, col, x, y;
	for(lin = i - 1, x = 2; x >= 0; lin++, x--) {
		for(col = j - 3, y = 2; y >= 0; col += 3, y--) {
			if(lin >= 0 && lin < height && col >= 0 && col < 3 * width) {
				if(!strcmp(filters[k], "smooth")) {
					R += bit_map[lin][col] * smooth[x][y];
				}
				else if(!strcmp(filters[k], "blur")) {
					R += bit_map[lin][col] * blur[x][y];
				} 
				else if(!strcmp(filters[k], "sharpen")) {
					R += bit_map[lin][col] * sharpen[x][y];
				}
				else if(!strcmp(filters[k], "mean")) {
					R += bit_map[lin][col] * mean[x][y];
				}
				else if(!strcmp(filters[k], "emboss")) {
					R += bit_map[lin][col] * emboss[x][y];
				}
			}
		}
	}
	return R;
}

float calculate_new_pixel_G(int i, int j, unsigned char **bit_map, char **filters, int k, int width, int height) {
	float G = 0;
	int lin, col, x, y;
	for(lin = i - 1, x = 2; x >= 0; lin++, x--) {
		for(col = j - 3, y = 2; y >= 0; col += 3, y--) {
			if(lin >= 0 && lin < height && col >= 0 && col < 3 * width) {
				if(!strcmp(filters[k], "smooth")) {
					G += bit_map[lin][col + 1] * smooth[x][y];
				}
				else if(!strcmp(filters[k], "blur")) {
					G += bit_map[lin][col + 1] * blur[x][y];
				} 
				else if(!strcmp(filters[k], "sharpen")) {
					G += bit_map[lin][col + 1] * sharpen[x][y];
				}
				else if(!strcmp(filters[k], "mean")) {
					G += bit_map[lin][col + 1] * mean[x][y];
				}
				else if(!strcmp(filters[k], "emboss")) {
					G += bit_map[lin][col + 1] * emboss[x][y];
				}
			}
		}
	}
	return G;
}

float calculate_new_pixel_B(int i, int j, unsigned char **bit_map, char **filters, int k, int width, int height) {
	float B = 0;
	int lin, col, x, y;
	for(lin = i - 1, x = 2; x >= 0; lin++, x--) {
		for(col = j - 3, y = 2; y >= 0; col += 3, y--) {
			if(lin >= 0 && lin < height && col >= 0 && col < 3 * width) {
				if(!strcmp(filters[k], "smooth")) {
					B += bit_map[lin][col + 2] * smooth[x][y];
				}
				else if(!strcmp(filters[k], "blur")) {
					B += bit_map[lin][col + 2] * blur[x][y];
				} 
				else if(!strcmp(filters[k], "sharpen")) {
					B += bit_map[lin][col + 2] * sharpen[x][y];
				}
				else if(!strcmp(filters[k], "mean")) {
					B += bit_map[lin][col + 2] * mean[x][y];
				}
				else if(!strcmp(filters[k], "emboss")) {
					B += bit_map[lin][col + 2] * emboss[x][y];
				}
			}
		}
	}
	return B;
}

int main(int argc, char *argv[])
{	
	int nProcesses, rank;
	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // printf("Hello from %i/%i\n", rank, nProcesses);

	char *input_image = create_input_image(argv);
	char *output_image = create_output_image(argv);

	FILE *in, *out;
	in = fopen(input_image, "rb"); // ./input/PGM/darth-vader.pgm
	out = fopen(output_image, "wb"); // ./output/PGM/darth-vader_out.pgm

	// save filters
	char **filters = create_filters(argc, argv);

	// read from input_image
	size_t len;

	char *T = (char*)calloc(length, sizeof(char));
	char *junk_line = (char*)calloc(length, sizeof(char));	

	len = 0;
	getline(&T, &len, in);

	len = 0;
	getline(&junk_line, &len, in);

	int width, height, maxValue;
	fscanf(in, "%d", &width);
	fscanf(in, "%d\n", &height);
	fscanf(in, "%d\n", &maxValue);

	unsigned char **bit_map;
	unsigned char **new_bit_map;

	char *dot = strrchr(input_image, '.');
	if(dot && !strcmp(dot, ".pgm")) {	
		// white-black image
		bit_map = alloc_matrix(height, width, 0);
		new_bit_map = alloc_matrix(height, width, 0);

		// read matrix from input_image
		for(int i = 0; i < height; i++) {
			fread(bit_map[i], sizeof(unsigned char), width, in);
		}
	}
	else {
		// colored image -> 3 channels
		bit_map = alloc_matrix(height, width, 1);
		new_bit_map = alloc_matrix(height, width, 1);

		// read matrix from input_image
		for(int i = 0; i < height; i++) {
			fread(bit_map[i], sizeof(unsigned char), 3 * width, in);
		}
	}

	// calculate left index and right index for every process
	int st = rank * ceil((double)height / nProcesses);
	int dr = fmin(height , (rank + 1) * ceil((double)height / nProcesses));

	// PGM/PNM
	if(dot && !strcmp(dot, ".pgm")) {
		// aply filters on input_image
		for(int k = 0; k < argc - 3; k++) {
			for(int i = st; i < dr; i++) {
				for(int j = 0; j < width; j++) {
					float P = calculate_new_pixel(i, j, bit_map, filters, k, width, height);
					new_bit_map[i][j] = (unsigned char)P;
				}
			}

			// copy new_bit_map to bit_map
			for(int i = st; i < dr; i++) {
				for(int j = 0; j < width; j++) {
					bit_map[i][j] = new_bit_map[i][j];
				}
			}

			// send to MASTER
			if(rank != MASTER) {
    			for(int i = st; i < dr; i++) {
	        		MPI_Send(bit_map[i], width, MPI_BYTE, MASTER, i, MPI_COMM_WORLD);
    			}
			}

			// receive
			if(rank == MASTER) {
				int end = fmin(height , (rank + 1) * ceil((double)height / nProcesses));
				for(int i = 0; i < height - end; i++) {
		        	unsigned char v[width];
					MPI_Status mpi_status;
	        		MPI_Recv(v, width, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &mpi_status);
	        		int tag = mpi_status.MPI_TAG;
	        		for(int j = 0; j < width; j++) {
	        			bit_map[tag][j] = v[j];
	        		}
    			}
    		}

    		// broadcast
			for(int i = 0; i < height; i++) {
				MPI_Bcast(bit_map[i], width, MPI_BYTE, MASTER, MPI_COMM_WORLD);
			}
		}

		MPI_Barrier (MPI_COMM_WORLD);

		if(rank == MASTER) {
			// write to output_image
			fprintf(out, "%s", T);
			fprintf(out, "%s", junk_line);
			fprintf(out, "%d %d\n", width, height);
			fprintf(out, "%d\n", maxValue);
			for(int i = 0; i < height; i++) {
				fwrite(bit_map[i], sizeof(unsigned char), width, out);
			}
		}
	}
	else {
		// aply filters on input_image
		for(int k = 0; k < argc - 3; k++) {
			for(int i = st; i < dr; i++) {
				for(int j = 0; j < 3 * width; j += 3) {
					float R = calculate_new_pixel_R(i, j, bit_map, filters, k, width, height);
					float G = calculate_new_pixel_G(i, j, bit_map, filters, k, width, height);
					float B = calculate_new_pixel_B(i, j, bit_map, filters, k, width, height);

					new_bit_map[i][j] = R < 0 ? 0 : min(R, 255);
					new_bit_map[i][j + 1] = G < 0 ? 0 : min(G, 255);
					new_bit_map[i][j + 2] = B < 0 ? 0 : min(B, 255);
				}
			}

			// copy new_bit_map to bit_map
			for(int i = st; i < dr; i++) {
				for(int j = 0; j < 3 * width; j += 3) {
					bit_map[i][j] = new_bit_map[i][j];
					bit_map[i][j + 1] = new_bit_map[i][j + 1];
					bit_map[i][j + 2] = new_bit_map[i][j + 2];
				}
			}

			if(rank != MASTER) {
    			for(int i = st; i < dr; i++) {
	        		MPI_Send(bit_map[i], 3 * width, MPI_BYTE, MASTER, i, MPI_COMM_WORLD);
    			}
			}

			// receive
			if(rank == MASTER) {
				int end = fmin(height , (rank + 1) * ceil((double)height / nProcesses));
				for(int i = 0; i < height - end; i++) {
		        	unsigned char v[3 * width];
					MPI_Status mpi_status;
	        		MPI_Recv(v, 3 * width, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &mpi_status);
	        		int tag = mpi_status.MPI_TAG;
	        		for(int j = 0; j < 3 * width; j++) {
	        			bit_map[tag][j] = v[j];
	        		}
    			}
    		}

    		// broadcast
			for(int i = 0; i < height; i++) {
				MPI_Bcast(bit_map[i], 3 * width, MPI_BYTE, MASTER, MPI_COMM_WORLD);
			}
		}

		MPI_Barrier (MPI_COMM_WORLD);

		if(rank == MASTER) {
			// write to output_image
			fprintf(out, "%s", T);
			fprintf(out, "%s", junk_line);
			fprintf(out, "%d %d\n", width, height);
			fprintf(out, "%d\n", maxValue);
			for(int i = 0; i < height; i++) {
				fwrite(bit_map[i], sizeof(unsigned char), 3 * width, out);
			}
		}
	}

    MPI_Finalize();
	return 0;
}