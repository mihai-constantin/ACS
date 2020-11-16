struct sensor_data {
    unsigned long client_id;
    int data_id;
    int no_values;
    float values<>;
};

struct entry_info {
    unsigned long client_id;
    int data_id;
};

struct get_stat_entry {
    float minim;
    float maxim;
    float medie;
    float mediana;
    int error;
};

struct get_stat_entries {
    struct get_stat_entry values<>;
};

struct user_data {
    unsigned long client_id;
    string nume<>;
};

program TEMA_PROG {
    version TEMA_VERS {
        /*
         * @string: client_name
         * @return: client_id 
         *          ERROR, daca clientul este deja autentificat
         */
        unsigned long LOGIN(string) = 1;

        /*
         * @string: client_name
         * @return: client_id 
         *          ERROR, daca clientul nu este autentificat
         */
        unsigned long LOGOUT(string) = 2;

        /*
         *  @struct sensor_data: new entity to add into database
         *  @return: add_code (0/1)
         */
        unsigned long ADD(struct sensor_data) = 3;

        /*
         *  @struct sensor_data: new entity to update into database
         *  @return: update_code (0/1)
         */
        unsigned long UPDATE(struct sensor_data) = 4;

        /*
         *  @int: entity_id to delete from database
         *  @return: delete_code (0/1)
         */
        unsigned long DEL(struct entry_info) = 5;

        /*
        *  @int: entity_id to read from database
        *  @return: read_code (0/1)
        */
        struct sensor_data READ(struct entry_info) = 6;

        /*
         *  @int: entity_id for getting statistics about
         */
        struct get_stat_entry GET_STAT(struct entry_info) = 7;

        /*
         *  get statistics about all tables
         */
        struct get_stat_entries GET_STAT_ALL(unsigned long) = 8;
        
        /*
         *  @string: client_name
         *  @return: client_id
         */
        unsigned long GET_CLIENT_ID(string) = 9;

        /*
         *  print auth users and current database
         */
        void GET_STATUS() = 10;

        /*
         *  print auth users and current database
         */
        int FIND_ENTRY(struct entry_info) = 11;

        /*
         *  @int: client_id
         *  @return: status code
         */
        int STORE(struct user_data) = 12;

        /*
         *  @user_data: {client_name, client_id}
         *  @return: status code
         */
        int LOAD(struct user_data) = 13;

    } = 1;
} = 1;
