#include <stdio.h>
#include <stdlib.h>
 
typedef union {
    int Wind_Chill;
    char Heat_Index;
} Condition;
 
typedef struct {
    float temp;
    Condition feels_like;
} Temperature;
 
int main() {
 
    Temperature *tmp;
    tmp = (Temperature *)malloc(sizeof(Temperature));
 
    printf("\nAddress of Temperature = %p", tmp);
    printf("\nAddress of temp = %p, feels_like = %p", &(*tmp).temp, &(*tmp).feels_like);
    printf("\nWind_Chill = %p, Heat_Index= %p\n", &((*tmp).feels_like).Wind_Chill, &((*tmp).feels_like).Heat_Index);

    tmp->feels_like.Heat_Index = 'a';
    printf("Heat_Index: %c\n", tmp->feels_like.Heat_Index);
    printf("Wind_Chill: %d\n", tmp->feels_like.Wind_Chill);

    tmp->feels_like.Wind_Chill = 65;
    printf("Heat_Index: %c\n", tmp->feels_like.Heat_Index);
    printf("Wind_Chill: %d\n", tmp->feels_like.Wind_Chill);

    return 0;
}
