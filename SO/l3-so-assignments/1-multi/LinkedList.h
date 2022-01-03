/* SPDX-License-Identifier: GPL-2.0 */

/* CONSTANTIN MIHAI - 336CA */

typedef struct Directory {
	char *path;
	struct Directory *next;
} Directory;

static int addDirectory(Directory **directories, char *path)
{
	Directory *directory;
	Directory *it;
	Directory *prev;

	directory = (Directory *) malloc(sizeof(Directory));
	if (directory == NULL)
		return 0;

	directory->path = path;
	directory->next = NULL;

	if ((*directories) == NULL) {
		*directories = directory;
		return 1;
	}

	it = *directories;
	prev = NULL;

	while (it != NULL) {
		prev = it;
		it = it->next;
	}

	prev->next = directory;

	return 1;
}

static void freeDirectory(Directory *directories)
{
	Directory *tmp;

	while (directories != NULL) {
		tmp = directories;
		directories = directories->next;
		free(tmp);
	}

	free(directories);
}
