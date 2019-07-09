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
    char nombre[100];
    float transaccion;
}balance_t;


int countlines(char*filename){
    FILE *fp = fopen(filename, "r");
    char reader;
    int counter = 0;

    if(fp == NULL){
        printf("Error de archivo.");
        return 0;
    }

    reader = getc(fp);
    while (reader != EOF){
        if(reader == 'n'){
            counter++;
        }

        reader = getc(fp); //used to read char from files
    }
    rewind(fp);
    fclose(fp);
    return counter;
}


int balance(balance_t**tamano){
    int num_balances = countlines(F_BALANCES) + 1;
    //printf("%d", num_balances);
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    for(int i; i < num_balances ; i++){
        int var = fscanf(f_p, "%[^,], %f", balance[i].nombre, &balance[i].transaccion); //& solo para int y float, ya char es un puntero
        printf("%s, %f", balance[i].nombre, balance[i].transaccion);
    }
    printf("\n");
}

void main(){
    balance_t *tamano = NULL;
    balance(&tamano);
}