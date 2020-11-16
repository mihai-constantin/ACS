// TEMA 1 SPRC
// CONSTANTIN MIHAI - 341C1

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tema.h"
#include "list.h"
#include "database.h"

#define LENGTH_MAX 500

bool login(char* command, CLIENT* clnt) {
	char* client_name = command + 6;
	u_long* client_id;

	client_id = login_1(&client_name, clnt);
	if (client_id == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	get_status_1((void*)client_name, clnt);

	if (*client_id == 0) {
		printf("User %s is already logged in!\n", client_name);
		return false;
	}
	printf("User %s logged in successfully with id = %ld!\n", client_name, *client_id);
	return true;
}

void logout(char* client_name, CLIENT* clnt) {
	u_long* client_id;
	client_id = logout_1(&client_name, clnt);
	if (client_id == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	get_status_1((void*)client_name, clnt);
}

void load_data(char* client_name, CLIENT* clnt) {
	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	struct user_data user_data;
	user_data.nume = client_name;
	user_data.client_id = *client_id;

	int* load_status = load_1(&user_data, clnt);
	if (*load_status == 0) {
		printf("%s.rpcdb file was created successfully!\n", client_name);
	} else {
		printf("Get data from %s.rpcdb file!\n", client_name);
	}
	get_status_1((void*)client_name, clnt);
}

void add_new_entry(char* client_name, char* command, CLIENT* clnt) {
	u_long* client_id;
	struct sensor_data s_data;
	client_id = get_client_id_1(&client_name, clnt);
	s_data.client_id = *client_id;

	// iterate through add command arguments
	char* aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	strcpy(aux, command);

	const char* delims = " ";
	char* word = strtok(aux, delims);
	int word_idx = 0;
	while(word != NULL) {
		word_idx++;
		if (word_idx == 2) {
			s_data.data_id = atoi(word);
		} else if (word_idx == 3) {
			s_data.no_values = atoi(word);
			s_data.values.values_val = (float*) malloc(s_data.no_values * sizeof(float));
		} else if (word_idx >= 4) {
			s_data.values.values_val[word_idx - 4] = atof(word);
		}
		word = strtok(NULL, delims);
	}
	s_data.values.values_len = s_data.no_values;

	struct entry_info entry_info;
	entry_info.client_id = *client_id;
	entry_info.data_id = s_data.data_id;
	int* found_data_id = find_entry_1(&entry_info, clnt);
	if (*found_data_id == 0) {
		printf("New entry with id = %d was added successfully into database!\n", entry_info.data_id);
		client_id = add_1(&s_data, clnt);
	} else {
		printf("Entry with id = %d was update successfully into database!\n", entry_info.data_id);
		client_id = update_1(&s_data, clnt);
	}

	if (client_id == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	get_status_1((void*)client_name, clnt);
}

void update_new_entry(char* client_name, char* command, CLIENT* clnt) {
	u_long* client_id;
	struct sensor_data s_data;
	client_id = get_client_id_1(&client_name, clnt);
	s_data.client_id = *client_id;

	// iterate through add command arguments
	char* aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	strcpy(aux, command);

	const char* delims = " ";
	char* word = strtok(aux, delims);
	int word_idx = 0;
	while(word != NULL) {
		word_idx++;
		if (word_idx == 2) {
			s_data.data_id = atoi(word);
		} else if (word_idx == 3) {
			s_data.no_values = atoi(word);
			s_data.values.values_val = (float*) malloc(s_data.no_values * sizeof(float));
		} else if (word_idx >= 4) {
			s_data.values.values_val[word_idx - 4] = atof(word);
		}
		word = strtok(NULL, delims);
	}
	s_data.values.values_len = s_data.no_values;

	struct entry_info entry_info;
	entry_info.client_id = *client_id;
	entry_info.data_id = s_data.data_id;

	int* found_data_id = find_entry_1(&entry_info, clnt);
	if (*found_data_id == 0) {
		client_id = add_1(&s_data, clnt);
		printf("New entry with id = %d was added successfully into database!\n", entry_info.data_id);
	} else {
		client_id = update_1(&s_data, clnt);
		printf("Entry with id = %d was update successfully into database!\n", entry_info.data_id);
	}
	if (client_id == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	get_status_1((void*)client_name, clnt);
}

void read_entry(char* client_name, char* command, CLIENT* clnt) {
	struct entry_info entry_info;

	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	char* aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	strcpy(aux, command);

	const char* delims = " ";
	char* word = strtok(aux, delims);
	int word_idx = 0;

	while(word != NULL) {
		word_idx++;
		if (word_idx == 2) {
			entry_info.data_id = atoi(word);
		}
		word = strtok(NULL, delims);
	}

	entry_info.client_id = *client_id;

	int* found_data_id = find_entry_1(&entry_info, clnt);
	if (*found_data_id == 0) {
		printf("No entry with id = %d was found!\n", entry_info.data_id);
	} else {
		struct sensor_data* read_entry = read_1(&entry_info, clnt);
		if (read_entry == (struct sensor_data *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		printf("Entry found: ");
		printf("%d %d", read_entry->data_id, read_entry->no_values);
		for (int i = 0; i < read_entry->no_values; i++) {
			printf("%f ", read_entry->values.values_val[i]);
		}
		printf("\n");
	}
	get_status_1((void*)client_name, clnt);
}

void delete_entry(char* client_name, char* command, CLIENT* clnt) {
	struct entry_info entry_info;

	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	char* aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	strcpy(aux, command);

	const char* delims = " ";
	char* word = strtok(aux, delims);
	int word_idx = 0;

	while(word != NULL) {
		word_idx++;
		if (word_idx == 2) {
			entry_info.data_id = atoi(word);
		}
		word = strtok(NULL, delims);
	}

	entry_info.client_id = *client_id;

	int* found_data_id = find_entry_1(&entry_info, clnt);
	if (*found_data_id == 0) {
		printf("Client [%ld] has no entry with id = %d\n", entry_info.client_id, entry_info.data_id);
	} else {
		u_long* client_id = del_1(&entry_info, clnt);
		if (client_id == (u_long *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		printf("Entry with id = %d successfully deleted from client %ld!\n", entry_info.data_id, entry_info.client_id);
	}
	get_status_1((void*)client_name, clnt);
}

void store_data(char* client_name, CLIENT* clnt) {
	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	struct user_data user_data;
	user_data.nume = client_name;
	user_data.client_id = *client_id;
	int* store_status = store_1(&user_data, clnt);
	if (*store_status == 0) {
		printf("Store failed!\n");
	} else {
		printf("Store was successful!\n");
	}
	get_status_1((void*)client_name, clnt);
}

void get_stat(char* client_name, char* command, CLIENT* clnt) {
	struct entry_info entry_info;

	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	char* aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	strcpy(aux, command);

	const char* delims = " ";
	char* word = strtok(aux, delims);
	int word_idx = 0;

	while(word != NULL) {
		word_idx++;
		if (word_idx == 2) {
			entry_info.data_id = atoi(word);
		}
		word = strtok(NULL, delims);
	}

	entry_info.client_id = *client_id;

	struct get_stat_entry* get_stat_entry = get_stat_1(&entry_info, clnt);
	if (get_stat_entry == (struct get_stat_entry *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	if (get_stat_entry->error == 1) {
		printf("Client [%ld] has no entry with id = %d\n", entry_info.client_id, entry_info.data_id);
	} else {
		printf("minim: %f\n", get_stat_entry->minim);
		printf("maxim: %f\n", get_stat_entry->maxim);
		printf("medie: %f\n", get_stat_entry->medie);
		printf("mediana: %f\n", get_stat_entry->mediana);
	}
}

void get_stat_all(char* client_name, CLIENT* clnt) {
	u_long* client_id;
	client_id = get_client_id_1(&client_name, clnt);

	struct get_stat_entries* get_stat_entries = get_stat_all_1(client_id, clnt);
	if (get_stat_entries == (struct get_stat_entries *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printf("[get_stat_all]\n");
	int i;
	for (i = 0; i < get_stat_entries->values.values_len; i++) {
		printf("Entry [%d]\n", i);
		struct get_stat_entry current_entry = get_stat_entries->values.values_val[i];
		printf("minim: %f\n", current_entry.minim);
		printf("maxim: %f\n", current_entry.maxim);
		printf("medie: %f\n", current_entry.medie);
		printf("mediana: %f\n", current_entry.mediana);
	}
}

void tema_prog_1(char *host) {
	CLIENT *clnt;

#ifndef	DEBUG
	clnt = clnt_create (host, TEMA_PROG, TEMA_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	bool auth = false; // presupun ca la inceput clientul nu este autentificat
	bool loaded = false;
	char* command = (char*) malloc(LENGTH_MAX * sizeof(char));
	char* user_logged = (char*) malloc(USERNAME_LENGTH * sizeof(char));
	char *aux = (char*) malloc(LENGTH_MAX * sizeof(char));
	char* filename = (char*) malloc((USERNAME_LENGTH + 7) * sizeof(char));
	FILE* fp;

	// get commands from client until he exits
	while(1) {
		fgets(command, LENGTH_MAX, stdin); // read command from stdin
		command[strlen(command) - 1] = '\0';

		strcpy(aux, command);
		char* p = strtok(aux, " "); // get command type
		if (!strcmp(p, "login")) {
			auth = login(command, clnt);
			if (auth) {
				strcpy(user_logged, command + 6);
				user_logged[strlen(command) - 6] = '\0';
			}
		} else  if (!strcmp(p, "logout")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else {
				logout(user_logged, clnt);
				printf("User %s was logged out!\n", user_logged);
				auth = false;
			}
		} else if (!strcmp(p, "load")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else {
				loaded = true;
				load_data(user_logged, clnt);
			}
		} else if (!strcmp(p, "add")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				add_new_entry(user_logged, command, clnt);
			}
		} else if (!strcmp(p, "update")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				update_new_entry(user_logged, command, clnt);
			}
		} else if (!strcmp(p, "read")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				read_entry(user_logged, command, clnt);
			}
		} else if (!strcmp(p, "del")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				delete_entry(user_logged, command, clnt);
			}
		} else if (!strcmp(p, "get_stat")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				get_stat(user_logged, command, clnt);
			}
		} else if (!strcmp(p, "get_stat_all")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				get_stat_all(user_logged, clnt);
			}
		} else if (!strcmp(p, "store")) {
			if (!auth) {
				printf("User must be logged in!\n");
			} else if (!loaded) {
				printf("First use load command!\n");
			} else {
				store_data(user_logged, clnt);
			}
		} else if (!strcmp(p, "exit")) {
			if (auth) {
				printf("User must be logged out!\n");
			} else {
				printf("Goodby!\n");
				break;
			}
		} else {
			printf("Invalid command!\n");
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int main (int argc, char *argv[])
{
	char *host;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	tema_prog_1(host);
	exit (0);
}
