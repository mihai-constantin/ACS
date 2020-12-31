#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
void f() {
    printf("_WIN32\n");
}
#elif defined __unix__
void f() {
    printf("__unix__\n");
}
#elif defined __APPLE__
void f() {
    printf("__APPLE__\n");
}
#endif

int main(int argc, char const *argv[])
{
    f();
    return 0;
}
