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
         */
        unsigned long LOGIN(string) = 1;

        /*
         * @string: client_name
         * @return: client_id 
         */
        unsigned long LOGOUT(string) = 2;

        /*
         *  @struct sensor_data: new entity to add into database
         *  @return: client_id
         */
        unsigned long ADD(struct sensor_data) = 3;

        /*
         *  @struct sensor_data: new entity to update into database
         *  @return: client_id
         */
        unsigned long UPDATE(struct sensor_data) = 4;

        /*
         *  @truct entry_info: entity to delete from database
         *  @return: client_id
         */
        unsigned long DEL(struct entry_info) = 5;

        /*
        *  @struct entry_info: entity to read from database
        *  @return: data to be sent to client
        */
        struct sensor_data READ(struct entry_info) = 6;

        /*
         *  @truct entry_info: entity for getting statistics about
         *  @return: statistics about entry
         */
        struct get_stat_entry GET_STAT(struct entry_info) = 7;

        /*
         *  @unsigned long: client_id
         *  @return: get statistics about all tables
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
         *  @struct entry_info: entity to search for
         *  @int: 1 in case entry was found, 0 otherwise
         */
        int FIND_ENTRY(struct entry_info) = 11;

        /*
         *  @struct user_data: current user data
         *  @return: status code for store operation
         */
        int STORE(struct user_data) = 12;

        /*
         *  @struct user_data: current user data
         *  @return: status code for load operation
         */
        int LOAD(struct user_data) = 13;

    } = 1;
} = 1;
