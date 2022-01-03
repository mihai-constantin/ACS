// SPDX-License-Identifier: GPL-2.0

/* CONSTANTIN MIHAI - 336CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"
#include "util.h"
#include "LinkedList.h"

static HashTable * hashMap;
static Directory *directories;

static char buf[BUFSIZE];
static char new_buf[BUFSIZE];

static int READ_FROM_FILE;
static int WRITE_TO_FILE;

static char *input;
static char *output;

static int output_param;

int cpp(FILE *fd_src, FILE *fd_dst);

int addNode(Key key, Value value)
{
	int ret;

	if (value == NULL)
		ret = put(hashMap, key, "");
	else
		ret = put(hashMap, key, value);

	return ret;
}

int parseArguments(int argc, char const *argv[])
{
	int i, ret;
	char *key;
	char *value;
	char *dir;
	char *myString;

	directories = NULL;

	for (i = 1; i < argc; i++) {

		if (!strcmp(argv[i], "-D")) { /* -D <SYMBOL>[=<MAPPING>] */
			key = strtok((char *)argv[i + 1], "=");
			value = strtok(NULL, "=");
			ret = addNode(key, value);
			if (!ret)
				return -1;

			i++; /* sar peste urmatorul argument */
		} else if (startsWith(argv[i], "-D")) {
			/* -D<SYMBOL>[=<MAPPING>] */
			myString = (char *) calloc(100, sizeof(char));
			if (myString == NULL)
				return -1;

			strcpy(myString, argv[i] + 2);
			key = strtok(myString, "=");
			value = strtok(NULL, "=");
			ret = addNode(key, value);
			if (!ret)
				return -1;

			if (myString != NULL)
				free(myString);

		} else if (!strcmp(argv[i], "-I")) { /* [-I <DIR>] */
			dir = strtok((char *)argv[i + 1], " ");
			addDirectory(&directories, dir);
			i++; /* sar peste urmatorul argument */
		} else if (startsWith(argv[i], "-I")) { /* [-I<DIR>] */
			strcpy(dir, argv[i] + 2);
			addDirectory(&directories, dir);
		} else {
			break;
		}
	}

	return i;
}

int parseInputAndOutput(int i, int argc, char const *argv[])
{
	int j;

	input  = (char *) calloc(100, sizeof(char));
	if (input == NULL)
		return ERROR_CODE;

	output = (char *) calloc(100, sizeof(char));
	if (output == NULL)
		return ERROR_CODE;

	if (output_param) {

		if (!startsWith(argv[i], "-o")) {
			if (!startsWith(argv[i + 1], "-o")) {
				/* multiple input files */
				return ERROR_CODE;
			}
			strcpy(input, argv[i]);
			READ_FROM_FILE = 1;
		}

		/* determin fisierul de iesire */
		for (j = i; j < argc; j++) {
			if (!strcmp(argv[j], "-o")) {
				if (j != argc - 2) {
					/* multiple output files */
					return ERROR_CODE;
				}
				strcpy(output, argv[j + 1]);
				WRITE_TO_FILE = 1;
			} else if (startsWith(argv[j], "-o")) {
				if (j != argc - 1) {
					/* multiple output files */
					return ERROR_CODE;
				}
				strcpy(output, argv[j] + 2);
				WRITE_TO_FILE = 1;
			}
		}
	} else { /* nu am "-o" */

		if (i != argc) {

			/* am un singur argument in plus -> output */
			if (i + 1 == argc) {
				strcpy(input, argv[i]);
				READ_FROM_FILE = 1;
			} else if (i + 2 == argc) {
				/* am doua argumente in plus */
				strcpy(input, argv[i]);
				READ_FROM_FILE = 1;
				strcpy(output, argv[i + 1]);
				WRITE_TO_FILE = 1;
			} else if (i + 2 < argc) {
				/* multiple files */
				return ERROR_CODE;
			}
		}
	}

	return 0;
}

void freeMemory(void)
{
	freeHashTable(hashMap);

	if (directories != NULL)
		freeDirectory(directories);

	if (input != NULL)
		free(input);

	if (output != NULL)
		free(output);
}

void closeFiles(FILE *fd_src, FILE *fd_dst)
{
	if (READ_FROM_FILE)
		fclose(fd_src);

	if (WRITE_TO_FILE)
		fclose(fd_dst);
}

int replaceKeyValue(void)
{
	int i, ret;
	Element *it;

	for (i = 0; i < hashMap->size; i++) {
		it = hashMap->elements[i];

		while (it != NULL) {
			if (!startsWith(buf, "#ifdef")
					&& !startsWith(buf, "#undef")) {
				ret = replace(it->key, it->value, buf, new_buf);
				if (!ret)
					return 0;

				strcpy(buf, new_buf);
			}
			it = it->next;
		}
	}

	return 1;
}

int include_task(FILE *fd, FILE *fd_dst, char *header_file,
				char *current_directory, char *path, int *write)
{
	int pos = 0, found, t;

	/* include */
	if (startsWith(buf, "#include")) {

		strcpy(header_file, buf + 10);
		header_file[strlen(header_file) - 1] = '\0';

		if (READ_FROM_FILE) {
			for (t = strlen(input) - 1; t >= 0; t--) {
				if (input[t] == '/') {
					pos = t;
					break;
				}
			}

			/* current directory to search in */
			strcpy(current_directory, input);
			current_directory[pos] = '\0';
			header_file[strlen(header_file) - 1] = '\0';

			/* concatenare director cu file header */
			strcat(path, current_directory);
			strcat(path, "/");
			strcat(path, header_file);

			found = 0;

			fd = fopen(path, "r");
			if (fd == NULL) {
				/* caut in lista de directoare */
				Directory *it = directories;

				while (it != NULL) {
					strcpy(path, it->path);
					strcat(path, "/");
					strcat(path, header_file);

					fd = fopen(path, "r");
					if (fd && !found) {
						found = 1;
						cpp(fd, fd_dst);
						*write = 0;
					}

					it = it->next;
				}

			} else {
				/* am reusit sa deschid fisierul */
				found = 1;
				cpp(fd, fd_dst);
				*write = 0;
			}

			if (!found)
				return 0;
		} else {
			found = 0;

			/* stdin -> caut in directorul curent */
			header_file[strlen(header_file) - 1] = '\0';
			fd = fopen(header_file, "r");
			if (fd == NULL) {

				Directory *it = directories;

				while (it != NULL) {
					strcpy(path, it->path);
					strcat(path, "/");
					strcat(path, header_file);

					fd = fopen(path, "r");
					if (fd != NULL && !found) {
						found = 1;
						cpp(fd, fd_dst);
						*write = 0;
					}

					it = it->next;
				}
			} else {
				/* am reusit sa deschid fisierul */
				found = 1;
				cpp(fd, fd_dst);
				*write = 0;
			}

			if (!found)
				return 0;
		}
	}

	return 1;
}

void freeData(FILE *fd, char *newKey, char *newValue, char *current_directory,
				char *path, char *cond, char *copie,
				char *ifn_key, char *def_var, char *header_file)
{
	if (newKey != NULL)
		free(newKey);

	if (newValue != NULL)
		free(newValue);

	if (current_directory != NULL)
		free(current_directory);

	if (path != NULL)
		free(path);

	if (cond != NULL)
		free(cond);

	if (copie != NULL)
		free(copie);

	if (ifn_key != NULL)
		free(ifn_key);

	if (def_var != NULL)
		free(def_var);

	if (header_file != NULL)
		free(header_file);

	if (fd != NULL)
		fclose(fd);
}

void undefine_task(int in_ifdef, int *write)
{
	char *key;

	if (startsWith(buf, "#undef") && !in_ifdef) {

		*write = 0;
		key = strtok(buf + 7, " ");
		key[strlen(key) - 1] = '\0';
		deleteNode(hashMap, key);
	}
}

void ifdef_task(char *def_var, int *write, int *in_ifdef, int *block_ifdef)
{
	if (startsWith(buf, "#ifdef")) {

		*write = 0;
		*in_ifdef = 1;

		strcpy(def_var, buf + 7);
		def_var[strlen(def_var) - 1] = '\0';

		if (exists(hashMap, def_var))
			*block_ifdef = 1;
	}
}

void ifndef_task(char *ifn_key, int *dummy)
{
	if (startsWith(buf, "#ifndef")) {
		strcpy(ifn_key, buf + 8);
		ifn_key[strlen(ifn_key) - 1] = '\0';

		if (exists(hashMap, ifn_key))
			*dummy = 1;
	}
}

int if_task(char *cond, int *write, int *in_if, int *block,
			int *write_block, int *dummy, int in_else)
{
	int cont = 0;

	if (startsWith(buf, "#if ")) {
		*write = 0;
		*in_if = 1;

		strcpy(cond, buf + 4);
		cond[strlen(cond) - 1] = '\0';
		if (strcmp(cond, "0"))
			*block = 1;
	} else if (*in_if && startsWith(buf, "#elif")) {
		*write = 0;
		strcpy(cond, buf + 6);
		cond[strlen(cond) - 1] = '\0';

		if (strcmp(cond, "0"))
			*block = 1;
	} else if (*in_if && *block) {
		/* asta o sa afisez */
		*write_block = 1;

		if (startsWith(buf, "#el")) {
			*block = 0;
			*dummy = 1;
			// continue;
			cont = 1;
		}
	} else if (*in_if && *block == 0) {
		if (in_else && *write_block == 0)
			*write = 1;
		else
			*write = 0;
	}

	return cont;
}

int cpp(FILE *fd_src, FILE *fd_dst)
{
	int in_main = 0;
	int in_if = 0;
	int in_define = 0;
	int in_ifdef = 0;
	int block = 0;
	int write_block = 0;
	int in_else = 0;
	int block_ifdef = 0;
	int else_in_ifdef = 0;
	int multiple_define = 0;
	int dummy = 0;
	int write, ret, cont;
	unsigned int l;

	char *key;
	char *newKey;
	char *newValue;
	char *current_directory;
	char *path;
	char *cond;
	char *def_var;
	char *ifn_key;
	char *copie;
	char *header_file;

	FILE *fd = NULL;

	newKey = (char *) calloc(100, sizeof(char));
	if (newKey == NULL)
		return 0;

	newValue = (char *) calloc(100, sizeof(char));
	if (newValue == NULL)
		return 0;

	current_directory = (char *) calloc(100, sizeof(char));
	if (current_directory == NULL)
		return 0;

	path = (char *) calloc(100, sizeof(char));
	if (path == NULL)
		return 0;

	cond = (char *) calloc(100, sizeof(char));
	if (cond == NULL)
		return 0;

	def_var = (char *) calloc(100, sizeof(char));
	if (def_var == NULL)
		return 0;

	ifn_key = (char *) calloc(100, sizeof(char));
	if (ifn_key == NULL)
		return 0;

	copie = (char *) calloc(100, sizeof(char));
	if (copie == NULL)
		return 0;

	header_file = (char *) calloc(100, sizeof(char));
	if (header_file == NULL)
		return 0;

	/* procesare buffer */
	while (fgets(buf, sizeof(buf), fd_src) != NULL) {

		if (dummy == 1 && startsWith(buf, "#endif")) {
			dummy = 0;
			in_if = 0;
			continue;
		}

		if (dummy == 1)
			continue;

		write = 1; /* presupun ca scriu linia curenta */

		ifndef_task(ifn_key, &dummy);

		ret = include_task(fd, fd_dst,
				header_file, current_directory, path, &write);
		if (!ret)
			return 0;

		if (startsWith(buf, "int main"))
			in_main = 1;

		if (startsWith(buf, "#if "))
			in_if = 1;

		/* verific daca incepe cu define */
		if (!else_in_ifdef && startsWith(buf, "#define") == 1) {

			/* am ceva de dinainte */
			if (in_define == 1) {

				/* parcurg "valoarea" */
				char *p = strtok(newValue, " ");

				strcpy(copie, "");
				while (p != NULL) {
					if (exists(hashMap, p))
						strcat(copie, get(hashMap, p));
					else
						strcat(copie, p);
					p = strtok(NULL, " ");
					if (p != NULL)
						strcat(copie, " ");
				}

				strcpy(newValue, copie);

				if (exists(hashMap, newValue)) {
					ret = addNode(newKey,
							get(hashMap, newValue));
					if (!ret)
						return 0;
				} else {
					ret = addNode(newKey, newValue);
					if (!ret)
						return 0;
				}
			}

			write = 0;
			in_define = 1;

			key = strtok(buf + 8, "\n ");

			strcpy(newKey, key);
			strcpy(newValue, buf + 8 + strlen(key) + 1);

			if (strlen(newValue) != 0) {
				newValue[strlen(newValue) - 1] = '\0';

				if (newValue[strlen(newValue) - 1] == 92) {
					multiple_define = 1;
					newValue[strlen(newValue) - 1] = '\0';
				}
			}

		} else if (in_define == 1 && !startsWith(buf, "#")
					&& !in_main && multiple_define) {
			/* define pe mai multe linii */

			/* caut primul caracter diferit de ' ' */
			for (l = 0; l < strlen(buf); l++) {
				if (buf[l] != ' ')
					break;
			}

			strcat(newValue, buf + l);

			if (strlen(newValue) != 0) {
				newValue[strlen(newValue) - 1] = '\0';
				if (newValue[strlen(newValue) - 1] == 92)
					newValue[strlen(newValue) - 1] = ' ';
			}

			write = 0;
		} else {
			/* add to hashMap */
			if (in_define == 1) {

				char *p = strtok(newValue, " ");

				strcpy(copie, "");
				while (p != NULL) {
					if (exists(hashMap, p))
						strcat(copie, get(hashMap, p));
					else
						strcat(copie, p);

					p = strtok(NULL, " ");
					if (p != NULL)
						strcat(copie, " ");
				}

				strcpy(newValue, copie);

				if (exists(hashMap, newValue)) {
					ret = addNode(newKey,
							get(hashMap, newValue));
					if (!ret)
						return 0;
				} else {
					ret = addNode(newKey, newValue);
					if (!ret)
						return 0;
				}
			}
			in_define = 0;
		}

		if (!strcmp(buf, "\n") && !in_main)
			write = 0;

		/* verific daca incepe cu #undef */
		undefine_task(in_ifdef, &write);

		/* afisare current buf */
		if (write == 1) {

			/* define -> inlocuim fiecare key cu value */
			ret = replaceKeyValue();
			if (!ret)
				return 0;

			cont = if_task(cond, &write, &in_if, &block,
					&write_block, &dummy, in_else);
			if (cont == 1)
				continue;

			if (in_if && startsWith(buf, "#endif")) {
				write = 0;
				in_if = 0;
			}

			if (startsWith(buf, "#else")) {
				write = 0;
				in_else = 1;
			}

			ifdef_task(def_var, &write, &in_ifdef, &block_ifdef);

			if (in_ifdef && startsWith(buf, "#endif")) {
				write = 0;
				in_ifdef = 0;
				else_in_ifdef = 0;
			}

			if (in_ifdef && !block_ifdef)
				write = 0;

			if (in_ifdef && startsWith(buf, "#else")) {
				write = 0;
				else_in_ifdef = 1;
			}

			if (in_ifdef && startsWith(buf, "#undef")) {

				if (block_ifdef) {
					key = strtok(buf + 7, " ");
					key[strlen(key) - 1] = '\0';
					deleteNode(hashMap, key);

				}
				write = 0;
			}

			if (write == 1 && !startsWith(buf, "#"))
				fputs(buf, fd_dst);

			if (!in_if)
				write = 1;

			if (!in_ifdef)
				write = 1;
		}
	}

	freeData(fd, newKey, newValue, current_directory, path,
				cond, copie, ifn_key, def_var, header_file);

	return 1;
}

int main(int argc, char const *argv[])
{
	int i, j, ret;
	long hashSize = 10;

	FILE *fd_src;
	FILE *fd_dst;

	ret = initHashTable(&hashMap, hashSize, &hashCode);
	if (!ret)
		return ERROR_CODE;

	i  = parseArguments(argc, argv);
	if (i == -1)
		return ERROR_CODE;

	for (j = i; j < argc; j++) {
		if (startsWith(argv[j], "-o"))
			output_param = 1;
	}

	ret = parseInputAndOutput(i, argc, argv);
	if (ret == ERROR_CODE)
		return ERROR_CODE;

	if (READ_FROM_FILE) {
		fd_src = fopen(input, "r");
		if (fd_src == NULL)
			return ERROR_CODE;
	} else {
		fd_src = stdin;
	}

	if (WRITE_TO_FILE) {
		fd_dst = fopen(output, "a");
		if (fd_dst == NULL)
			return ERROR_CODE;
	} else {
		fd_dst = stdout;
	}

	ret = cpp(fd_src, fd_dst);
	if (!ret)
		return ERROR_CODE;

	freeMemory();
	closeFiles(fd_src, fd_dst);

	return 0;
}
