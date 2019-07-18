#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define F_BALANCES "balance.csv"

void movimiento(int no_tarjeta){
    float monto = 0;
    char nombre[30];

    printf("Ingrese el monto que desea mover:  ");
    scanf("%f", &monto);

    printf("Ingrese su nombre sin espacios:  ");
    scanf("%s", nombre);

    FILE *fp_movimientos = fopen(F_BALANCES, "a");
    
    if(fp_movimientos == NULL){
        printf("No se puede acceder al archivo. \n");
    }
    else{
        fprintf(fp_movimientos, "%s,%d,%.2f\n", nombre, no_tarjeta, monto);
    }
}

void main(void){
    movimiento(198763);
}