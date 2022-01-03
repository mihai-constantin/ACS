// TEMA 1 SPRC
// CONSTANTIN MIHAI - 341C1

#include "tema.h"
#include "list.h"
#include "database.h"
#include <stdbool.h>

int idx_client = 1;
struct UsersList* usersList;
struct Database* database;

// GET STATUS
void* get_status_1_svc(void* argp, struct svc_req* rqstp) {
	printList(usersList);
	printf("\n");
	printDatabase(database);
	printf("\n\n");
}

// GET_CLIET_ID
u_long* get_client_id_1_svc(char** client_name, struct svc_req* rqstp) {
	static u_long  result;
	result = getClientId(usersList, *client_name);
	return &result;
}

// LOGIN
u_long* login_1_svc(char** client_name, struct svc_req* rqstp) {
	static u_long  client_id;

	if (contains(usersList, *client_name) == 1) {
		client_id = 0;
		return &client_id;
	}

	// create user node
	struct user_info user;
	user.client_name = (char*) malloc(USERNAME_LENGTH * sizeof(char));
	strcpy(user.client_name, *client_name);
	user.client_id = idx_client;
	client_id = idx_client;

	if (idx_client == 1) { // first user logged
		init(&usersList); // init usersList
		initDatabase(&database); // init database
	}

	// insert user into userList and into database
	insert(&usersList, user);
	insertUserIntoDatabase(&database, user.client_id);
	printf("[after LOGIN command]\n");

	idx_client++;
	return &client_id;
}

// LOGOUT
u_long* logout_1_svc(char** client_name, struct svc_req* rqstp) {
	static u_long  client_id;
	client_id = delete(&usersList, *client_name); // delete user from usersList
	deleteUserFromDatabase(&database, client_id); // delete user data from database
	printf("[after LOGOUT command]\n");
	printf("[logout] [%ld] %s\n", client_id, *client_name);
	return &client_id;
}

// LOAD
int* load_1_svc(struct user_data* user_data, struct svc_req* rqstp) {
	static int result;
	result = loadDataFromFile(&database, user_data->nume, user_data->client_id);
	printf("[after LOAD command]\n");
	return &result;
}

// ADD
int* find_entry_1_svc(struct entry_info* argp, struct svc_req* rqstp) {
	static int  result;
	result = containsEntry(database, argp->client_id, argp->data_id);
	return &result;
}

u_long* add_1_svc(struct sensor_data* argp, struct svc_req *rqstp) {
	static u_long  result;
	printf("[after ADD command]\n");
	insertDataFromUserIntoDatabase(&database, argp);
	return &result;
}

// UPDATE
u_long* update_1_svc(struct sensor_data *argp, struct svc_req *rqstp) {
	static u_long  result;
	printf("[after UPDATE command]\n");
	updateDataFromUserIntoDatabase(&database, argp);
	return &result;
}

// READ
struct sensor_data* read_1_svc(struct entry_info *argp, struct svc_req *rqstp) {
	static struct sensor_data result;
	printf("[after READ command]\n");
	result = findEntryInDatabase(database, argp->client_id, argp->data_id);
	return &result;
}

// DELETE
u_long* del_1_svc(struct entry_info* argp, struct svc_req *rqstp) {
	static u_long  result;
	printf("[after DELETE command]\n");
	deleteDataFromDatabase(&database, argp->client_id, argp->data_id);
	return &result;
}

// STORE
int* store_1_svc(struct user_data* user_data, struct svc_req* rqstp) {
	static int result;
	printf("[after STORE command]\n");
	result = storeDataIntoDatabase(database, user_data->nume, user_data->client_id);
	return &result;
}

// GET_STAT
struct get_stat_entry* get_stat_1_svc(struct entry_info *argp, struct svc_req *rqstp) {
	static struct get_stat_entry  result;
	printf("[after GET_STAT command]\n");
	result = get_statictics_from_database(database, argp->client_id, argp->data_id);
	return &result;
}

// GET_STAT_ALL
struct get_stat_entries* get_stat_all_1_svc(u_long* argp, struct svc_req *rqstp) {
	static get_stat_entries  result;
	printf("[after GET_STAT_ALL command]\n");
	result = get_all_statistics(database,  *argp);
	return &result;
}
