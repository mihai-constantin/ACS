// TEMA 1 SPRC
// CONSTANTIN MIHAI - 341C1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define USERNAME_LENGTH 20

struct user_info {
    char* client_name;
    unsigned long client_id;
};

typedef struct UsersList {
    struct user_info user_info;
    struct UsersList* next;
} UsersList;

void init(UsersList** list) {
    *list = NULL;
}

int isEmpty(UsersList* list) {
    if (!list) {
        return 1;
    }
    return 0;
}

int contains(UsersList* usersList, char* client_name) {
    UsersList* list = usersList;
    while(list) {
        if (!strcmp(list->user_info.client_name, client_name)) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void insert(UsersList** list, struct user_info user) {
    UsersList* List = *list;

    // create user node
    struct UsersList* node = (struct UsersList*) malloc(sizeof(struct UsersList));
    node->user_info.client_id = user.client_id;
    node->user_info.client_name = (char*) malloc(USERNAME_LENGTH * sizeof(char));
    strcpy(node->user_info.client_name, user.client_name);
    node->next = NULL;

    UsersList* pred = NULL;
    if (isEmpty(List)) {
        *list = node;
    } else {
        while(List) {
            pred = List;
            List = List->next;
        }
        pred->next = node;
    }
}

unsigned long getClientId(UsersList* usersList, char* client_name) {
    UsersList* list = usersList;

    while(list) {
        if (!strcmp(list->user_info.client_name, client_name)) {
            return list->user_info.client_id;
        }
        list = list->next;
    }
}

unsigned long delete(UsersList** list, char* client_name) {
    UsersList* List = *list;
    unsigned int client_id;

    if (!strcmp(List->user_info.client_name, client_name)) {
        client_id = List->user_info.client_id;
        UsersList* aux = *list;
        *list = (*list)->next;
        free(aux);
    } else {
        UsersList* current;
        UsersList* pred;

        current = List;
        while(current && strcmp(current->user_info.client_name, client_name)) {
            pred = current;
            current = current->next;
        }
        client_id = current->user_info.client_id;
        pred->next = current->next;
        free(current);
    }

    return client_id;
}

void printList(UsersList* list) {
    printf("-----   Users logged    -----\n");
    while(list) {
        printf("[%ld] %s\n", list->user_info.client_id, list->user_info.client_name);
        list = list->next;
    }
}
