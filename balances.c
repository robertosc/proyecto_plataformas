#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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

int countlines(void){  //Se puede poner como argumento "char*filename" para hacer la función más general
    FILE *fp = fopen(F_BALANCES, "r");
    char reader;
    int counter = 0;

    if(fp == NULL){
        printf("Error de archivo.");
        return 0;
    }

    reader = getc(fp);
    while (reader != EOF){
        if(reader == '\n'){
            counter++;
        }

        reader = getc(fp); //used to read char from files
    }
    rewind(fp);
    fclose(fp);
    return counter + 1;
}

int balances_todos(balance_t**tamano){  //HACER CAMBIOS EN EL MAIN
    int num_balances = countlines()-1;
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    for(int i; i < num_balances ; i++){
        
        int var = fscanf(f_p, "%[^,], %[^,], %f", balance[i].nombre, balance[i].no_tarjeta, &balance[i].transaccion); //& solo para int y float, ya char es un puntero
        
        printf("%s, %s, %.2f",balance[i].nombre, balance[i].no_tarjeta, balance[i].transaccion);
    }

    rewind(f_p);
    fclose(f_p);
}

void main(){
    balance_t *tamano1 = NULL;
    balances_todos(&tamano1);
}


//usar rewind(fp);