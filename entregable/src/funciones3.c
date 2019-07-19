#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "archivo.h"

void add_user(void){
    char nombre[LEN_NOMBRE];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];

    printf("Ingrese el nombre del nuevo usuario sin espacios -> ");
    scanf("%s", nombre);

    printf("Ingrese un número de tarjeta -> ");
    scanf("%s", tarjeta);

    printf("Ingrese el pin para esta cuenta -> ");
    scanf("%s", pin);
    FILE *fp_info = fopen(F_INFO, "a");
    
    if(fp_info == NULL){
        printf("No se puede acceder al archivo. \n");
    }
    else{
        fprintf(fp_info, "%s,%s,%s,activo\n", nombre, tarjeta, pin);
    }
    fclose(fp_info);
}

int ingreso_admin(void){
    char tarjerta_ad[LEN_TARJETA];
    char pin[LEN_PIN];
    printf("Ingrese su número de tarjeta (admin) -> ");
    scanf("%s",tarjerta_ad);
    printf("Ingrese su número de pin (admin) -> ");
    scanf("%s", pin);

    if(!strcmp(TARJETA_ADMIN, tarjerta_ad) && !strcmp(PIN_ADMIN, pin)){
        return 1;
    }
    else{
        return 0;
    }
}