struct student {
    string nume<>;
    string grupa<>;
};

program CHECKPROG_PROG {
    version CHECKVERS_VERS {
        string GRADE(struct student) = 1;
    } = 1;
} = 0x31234567;
