/* SPDX-License-Identifier: GPL-2.0 */

/* CONSTANTIN MIHAI - 336CA */

#define BUFSIZE 256
#define ERROR_CODE 12

static int startsWith(const char *a, const char *b)
{
	if (!strncmp(a, b, strlen(b)))
		return 1;

	return 0;
}

static int replace(char *key, char *value, char *buf, char *new_buf)
{
	int i, inString;
	int *in_string = (int *) malloc(BUFSIZE * sizeof(int));
	unsigned int j;

	if (in_string == NULL)
		return 0;

	// create in_string
	inString = 0;
	for (j = 0; j < strlen(buf); j++) {
		if (buf[j] == '"') {
			if (!inString)
				inString = 1;
			else
				inString = 0;
		}
		in_string[j] = inString;
	}

	i = 0;
	while (*buf) {
		// compare the substring with the result
		if (strstr(buf, key) == buf && in_string[i] == 0) {
			strcpy(&new_buf[i], value);
			i += strlen(value);
			buf += strlen(key);
		} else
			new_buf[i++] = *buf++;
	}

	new_buf[i] = '\0';

	free(in_string);

	return 1;
}
