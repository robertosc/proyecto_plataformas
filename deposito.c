#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define F_INFO "info.csv"
#define F_BALANCES "balance.csv"


//FUNCIÓN PARA DEPOSITARLE DINERO A ALGUIEN MÁS

void deposito(void){
    float monto = 0;
    char nombre[30];
    char tarjeta[30];

    printf("Ingrese el número de tarjeta de la persona a la que desea depositar dinero:  ");
    scanf("%s", tarjeta);
    
    printf("Ingrese el monto que desea depositar:  ");
    scanf("%f", &monto);

    printf("Ingrese su nombre sin espacios:  ");
    scanf("%s", nombre);

    FILE *fp_movimientos = fopen(F_BALANCES, "a");
    if(monto > 0){
        if(fp_movimientos == NULL){
            printf("No se puede acceder al archivo. \n");
        }
        else{
            fprintf(fp_movimientos, "%s,%s,%.2f\n", nombre, tarjeta, monto);
        }
    }
    else{
        printf("El monto a depositar debe ser una cantidad positiva.\n");
    }
}


void main(void){
    deposito();
}