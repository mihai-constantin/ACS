// TEMA 1 SPRC
// CONSTANTIN MIHAI - 341C1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define dmax 100
#define FILE_NAME_DIM 30

struct sensor_data_db {
    int data_id;
    int no_values;
    float* values;
};

typedef struct Database {
    struct sensor_data_db data[dmax];
    int no_entries; // lungimea vectorului data pentru clientul cu id-ul client_id
	unsigned long client_id;
    struct Database* next;
} Database;

void initDatabase (Database** list) {
    *list = NULL;
}

int isEmptyDatabase(Database* list) {
    if (!list) {
        return 1;
    }
    return 0;
}

void insertUserIntoDatabase(Database** list, int client_id) {
    Database* List = *list;

    Database* node_db = (Database*) malloc(sizeof(Database));
    node_db->no_entries = 0;
    node_db->client_id = client_id;
    node_db->next = NULL;

    Database* pred = NULL;
    if (isEmptyDatabase(List)) {
        *list = node_db;
    } else {
         while(List) {
            pred = List;
            List = List->next;
        }
        pred->next = node_db;
    }
}

void insertDataFromUserIntoDatabase(Database** list, struct sensor_data* argp) {
    Database* List = *list;
    while(List) {
        if (List->client_id == argp->client_id) {
            int no_entries = List->no_entries;
            if (!no_entries) {
                List->data[0].data_id = argp->data_id;
                List->data[0].no_values = argp->no_values;
                (List->data[0]).values = (float*) malloc((argp->no_values) * sizeof(float));
                for (int i = 0; i < argp->no_values; i++) {
                    (List->data[0]).values[i] = ((argp->values).values_val)[i];
                }
            } else {
                List->data[no_entries].data_id = argp->data_id;
                List->data[no_entries].no_values = argp->no_values;
                List->data[no_entries].values = (float*) malloc((argp->no_values) * sizeof(float));
                for (int i = 0; i < argp->no_values; i++) {
                    List->data[no_entries].values[i] = ((argp->values).values_val)[i];
                }
            }
            List->no_entries++;
            break;
        }
        List = List->next;
    }
}

void updateDataFromUserIntoDatabase(Database** list, struct sensor_data* argp) {
    Database* List = *list;
    while(List) {
        if (List->client_id == argp->client_id) {
            int no_entries = List->no_entries;
            for (int k = 0; k < List->no_entries; k++) {
                if (List->data[k].data_id == argp->data_id) {
                    List->data[k].no_values = argp->no_values;
                    free((List->data[k]).values);
                    (List->data[k]).values = (float*) malloc((argp->no_values) * sizeof(float));
                     for (int i = 0; i < argp->no_values; i++) {
                        (List->data[k]).values[i] = ((argp->values).values_val)[i];
                    }
                    return;
                }
            }
        }
        List = List->next;
    }
}

void deleteUserFromDatabase(Database** list, unsigned long client_id) {
    Database* List = *list;
    if (isEmptyDatabase(List)) {
        return;
    }

    if (List->client_id == client_id) {
        Database* aux = *list;
        *list = (*list)->next;
        free(aux);
    } else {
        Database* pred;
        Database* current;

        current = List;
        while (current && current->client_id != client_id) {
            pred = current;
            current = current->next;
        }
        pred->next = current->next;
        free(current);
    }
}

void deleteDataFromDatabase(Database** list_db, unsigned long client_id, int data_id) {
    Database* list = *list_db;
    int pos_entry = 0;
    while(list) {
        if (list->client_id == client_id) {    
            for (int k = 0; k < list->no_entries; k++) {
                if (list->data[k].data_id == data_id) {
                    pos_entry = k;
                }
            }
            for (int k = pos_entry; k < list->no_entries; k++) {
                list->data[k] = list->data[k + 1];
            }
            list->no_entries--;
        }
        list = list->next;
    }
}

struct sensor_data findEntryInDatabase(Database* list_db, unsigned long client_id, int data_id) {
    Database* list = list_db;
    struct sensor_data response;
    while(list) {
        if (list->client_id == client_id) {    
            response.client_id = client_id;
            for (int k = 0; k < list->no_entries; k++) {
                if (list->data[k].data_id == data_id) {
                    response.data_id = list->data[k].data_id;
                    response.no_values = list->data[k].no_values;
                    response.values.values_val = (float*) malloc(response.no_values * sizeof(float));
                    for (int i = 0; i < list->data[k].no_values; i++) {
                        response.values.values_val[i] = list->data[k].values[i];
                    }
                    response.values.values_len = response.no_values;
                    break;
                }
            }
        }
        list = list->next;
    }
    return response;
}

int containsEntry(Database* list_db, unsigned long client_id, int data_id) {
    Database* list = list_db;
    while(list) {
        if (list->client_id == client_id) {    
            for (int k = 0; k < list->no_entries; k++) {
                if (list->data[k].data_id == data_id) {
                    return 1;
                }
            }
        }
        list = list->next;
    }
    return 0;
}

int loadDataFromFile(Database** list, char* client_name, unsigned long client_id) {
    FILE* in;
    char* filename = (char*) malloc(FILE_NAME_DIM * sizeof(char));
    strcpy(filename, client_name);
    strcat(filename, ".rpcdb");

    int ok = 0;
    if (access(filename, F_OK) != -1) {
        ok = 1; // file exists
    }

    in = fopen(filename, "ab+");

    // read input file line by line
    ssize_t read;
    size_t len = 0;
    char* line = NULL;
    struct sensor_data s_data;
    char* aux = (char*) malloc(500 * sizeof(char));

    while((read = getline(&line, &len, in)) != -1) {
        line[strlen(line) - 1] = '\0';
        s_data.client_id = client_id;
        strcpy(aux, line);
        const char* delims = " ";
        char* word = strtok(aux, delims);
        int word_idx = 0;
        while(word != NULL) {
            word_idx++;
            if (word_idx == 1) {
                s_data.data_id = atoi(word);
            } else if (word_idx == 2) {
                s_data.no_values = atoi(word);
                s_data.values.values_val = (float*) malloc(s_data.no_values * sizeof(float));
            } else if (word_idx >= 3) {
                s_data.values.values_val[word_idx - 3] = atof(word);
            }
            word = strtok(NULL, delims);
        }
        s_data.values.values_len = s_data.no_values;
        insertDataFromUserIntoDatabase(list, &s_data);
    }
    // close file descriptor
    fclose(in);
    return ok;
}

int storeDataIntoDatabase(Database* list_db, char* client_name, unsigned long client_id) {
    Database* list = list_db;
    FILE* out;
    char* filename = (char*) malloc(FILE_NAME_DIM * sizeof(char));
    strcpy(filename, client_name);
    strcat(filename, ".rpcdb");
    out = fopen(filename, "w");
    while(list) {
        if (list->client_id == client_id) {    
            for (int k = 0; k < list->no_entries; k++) {
                fprintf(out, "%d ", list->data[k].data_id);
                fprintf(out, "%d ", list->data[k].no_values);
                for (int i = 0; i < list->data[k].no_values; i++) {
                    fprintf(out, "%f ", list->data[k].values[i]);
                }
                fprintf(out, "\n");
            }
            free(filename);
            fclose(out);
            return 1;
        }
        list = list->next;
    }

    free(filename);
    fclose(out);
    return 0;
}

struct get_stat_entry get_statictics_from_database(Database* list_db, unsigned long client_id, int data_id) {
    Database* list = list_db;
    struct get_stat_entry response;
    float sum = 0;
    bool ok = false;
    while(list) {
        if (list->client_id == client_id) {    
            for (int k = 0; k < list->no_entries; k++) {
                if (list->data[k].data_id == data_id) {
                    ok = true;
                    response.minim = list->data[k].values[0];
                    response.maxim = list->data[k].values[0];
                    for (int i = 0; i < list->data[k].no_values; i++) {
                        if (list->data[k].values[i] > response.maxim) {
                            response.maxim = list->data[k].values[i];
                        }
                        if (list->data[k].values[i] < response.minim) {
                            response.minim = list->data[k].values[i];
                        }
                        sum += list->data[k].values[i];
                    }
                    response.medie = sum/list->data[k].no_values;
                    if (list->data[k].no_values % 2 == 0) {
                        response.mediana =  (list->data[k].values[list->data[k].no_values/2] + list->data[k].values[list->data[k].no_values/2 - 1])/2;
                    } else {
                        response.mediana =  list->data[k].values[list->data[k].no_values/2];
                    }
                    response.error = 0;
                    break;
                }
            }
        }
        list = list->next;
    }
    if (!ok) {
        response.error = 1;
    }
    return response;
}

struct get_stat_entries get_all_statistics(Database* list_db, unsigned long client_id) {
    struct get_stat_entries all_responses;

    Database* list = list_db;
    struct get_stat_entry response;
    float sum;
    while(list) {
        if (list->client_id == client_id) { 
            all_responses.values.values_len = list->no_entries;
            all_responses.values.values_val = (struct get_stat_entry *) malloc(all_responses.values.values_len * sizeof(struct get_stat_entry)); 
            for (int k = 0; k < list->no_entries; k++) {
                response.minim = list->data[k].values[0];
                response.maxim = list->data[k].values[0];
                sum = 0;
                for (int i = 0; i < list->data[k].no_values; i++) {
                    if (list->data[k].values[i] > response.maxim) {
                        response.maxim = list->data[k].values[i];
                    }
                    if (list->data[k].values[i] < response.minim) {
                        response.minim = list->data[k].values[i];
                    }
                    sum += list->data[k].values[i];
                }
                response.medie = sum/list->data[k].no_values;
                if (list->data[k].no_values % 2 == 0) {
                    response.mediana =  (list->data[k].values[list->data[k].no_values/2] + list->data[k].values[list->data[k].no_values/2 - 1])/2;
                } else {
                    response.mediana =  list->data[k].values[list->data[k].no_values/2];
                }
                all_responses.values.values_val[k] = response;
            }
        }
        list = list->next;
    }
    
    return all_responses;
}

void printDatabase(Database* list_db) {
    printf("-----   DATABASE    -----\n");
    Database* list = list_db;
    while(list) {
        printf("[Client %ld]\n", list->client_id);
        printf("no_entries: %d\n", list->no_entries);
        
        for (int k = 0; k < list->no_entries; k++) {
            printf("%d ", list->data[k].data_id);
            printf("%d ", list->data[k].no_values);
            for (int i = 0; i < list->data[k].no_values; i++) {
                printf("%f ", list->data[k].values[i]);
            }
            printf("\n");
        }
        list = list->next;
    }
}
