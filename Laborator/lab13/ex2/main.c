#include <stdio.h>

#define GIGEL 1

#ifdef CHANGE
#undef GIGEL
#define GIGEL 0
#endif

int main(int argc, char const *argv[])
{
    printf("GIGEL = %d\n", GIGEL);
    return 0;
}
