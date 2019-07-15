#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define F_INFO "info.csv"
#define F_BALANCES "balance.csv"
#define NUM_PERSONA 1
#define LEN_BUFFER 1024
#define LEN_PASSWD 512
#define NUM_BALANCES 20


typedef struct balance_s{
    char nombre[30];
    char no_tarjeta[30];
    float transaccion;
}balance_t;

float total = 0;

int balance_total(balance_t**tamano, int no_tarjeta1){
    int num_balances = NUM_BALANCES;
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    printf("Actualmente su cuenta tiene: \n");
    for(int i; i < NUM_BALANCES ; i++){
        
        int var = fscanf(f_p, "%[^,], %[^,], %f", balance[i].nombre, balance[i].no_tarjeta, &balance[i].transaccion); //& solo para int y float, ya char es un puntero

        if(atoi(balance[i].no_tarjeta) == no_tarjeta1){
            total = total + balance[i].transaccion;
        }


        //printf("%s, %.2f", balance[i].no_tarjeta, balance[i].transaccion);
    }
    printf("%.2f", total);
    printf("\n");
    rewind(f_p);
}

void main(){
    balance_t *tamano = NULL;
    balance_total(&tamano, 198763);
}