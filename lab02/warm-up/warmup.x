struct elem {
    int x;
    int y;
};

program WARMUP_PROG {
    version WARMUP_VERS {
        int GET_SUM(struct elem) = 1;
    } = 1;
} = 123456789;
