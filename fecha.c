#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include <time.h>

#define LEN_TIEMPO 20

char *tiempo(int opcion){
    char *horarios = malloc(LEN_TIEMPO);

    time_t fecha;
    struct tm *tm;  //la estructura debe llamarse tm o no funciona al usarla en strftime()

    fecha = time(NULL);

    tm = localtime(&fecha);

    if(opcion == 1){
        strftime(horarios, 100, "%d/%m/%Y", tm);
        return horarios;
    }

    else if (opcion == 2){
        strftime(horarios, 100, "%l:%M:%S", tm);
        return horarios;
    }
}

void main(void){
    char *hola = tiempo(1);
    printf("%s", hola);

    char *adios = tiempo(2);
    printf("%s", adios);

}

