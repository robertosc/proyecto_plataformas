#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "archivo.h"


//FUNCIÓN DE INGRESO
int ingreso(int opcion){  
    usuarios_t usuario[NUM_USUARIOS];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];

    char buffer[LEN_BUFFER];
    FILE *fp_usuarios = fopen(F_INFO, "r");
    memset(usuario, 0, sizeof(usuarios_t)* NUM_USUARIOS);
    memset(buffer, 0, sizeof(char)*LEN_BUFFER);
    
    int k=1;
    int validador = 0;
    int no_tarjeta = 0;
    while(k){
        printf("Ingrese su numero de tarjeta:  ");
        scanf("%s", tarjeta);
        printf("Ingrese su número de pin:  ");
        scanf("%s", pin);
        
        printf("\n");

        while(!usuario[0].encontrado && fgets(buffer, LEN_BUFFER, fp_usuarios) != NULL){

            char *p_nombre = strtok(buffer, ",");
            char *p_tarjeta = strtok(NULL, ",");
            char *p_pin = strtok(NULL, ",");
            char *p_actividad = strtok(NULL, ",");

            strcpy(usuario->nombre, p_nombre);
            strcpy(usuario->tarjeta, p_tarjeta);
            strcpy(usuario->pin, p_pin);
            strcpy(usuario->actividad, p_actividad);

            if(opcion == 1){
                if(!strcmp(p_tarjeta, tarjeta) && !strcmp(p_pin, pin)){
                    printf("Ingreso exitoso. Bienvenido %s. \n", usuario->nombre);
                    k = 0;
                    validador = 1;
                    no_tarjeta = atoi(p_tarjeta);
                }
            }
            else if (opcion == 2){
                printf("%s, %s, %s, %s", usuario->nombre, usuario->tarjeta, usuario->pin, usuario->actividad);
                k = 0;
                validador = 1;
            }

            else{
                printf("Error. Opción no disponible.");
                exit(0);
            }
            
        }
    if (validador==0){
        printf("ERROR. NÚMERO DE TARJETA O PIN.\n");
    }
    fseek(fp_usuarios, 0, SEEK_SET);
    }

fclose(fp_usuarios);
return no_tarjeta;
}

//FUNCION CONTAR LÍNEAS
int countlines(char*nombre_archivo){   //Se puede poner como argumento "char*filename" para hacer la función más general 
    FILE *fp = fopen(nombre_archivo, "r");
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


//LECTURA DE TODAAS LAS TRANSACCIONES
int balances_todos(balance_t**tamano){
    int num_balances = countlines(F_BALANCES);
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



//MOVIMIENTOS DE UN USUARIO ESPECÍFICO
int balance(balance_t**tamano, int no_tarjeta1){
    int num_balances = countlines(F_BALANCES);
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    printf("Estos son los movimientos de su cuenta: \n");
    for(int i; i < num_balances ; i++){
        
        int var = fscanf(f_p, "%[^,], %[^,], %f", balance[i].nombre, balance[i].no_tarjeta, &balance[i].transaccion); //& solo para int y float, ya char es un puntero

        if(atoi(balance[i].no_tarjeta) == no_tarjeta1){
            printf("%s -> %.2f", balance[i].nombre, balance[i].transaccion);
        }


        //printf("%s, %.2f", balance[i].no_tarjeta, balance[i].transaccion);
    }
    printf("\n");
    rewind(f_p);
    fclose(f_p);
}

//FUNCIÓN PARA MOSTRAR BALANCE TOTAL
float total = 0;

float balance_total(balance_t**tamano, int no_tarjeta1){
    int num_balances = NUM_BALANCES;
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    //printf("\nActualmente su cuenta tiene: \n");
    for(int i; i < NUM_BALANCES ; i++){
        
        int var = fscanf(f_p, "%[^,], %[^,], %f", balance[i].nombre, balance[i].no_tarjeta, &balance[i].transaccion); //& solo para int y float, ya char es un puntero

        if(atoi(balance[i].no_tarjeta) == no_tarjeta1){
            total = total + balance[i].transaccion;
        }
        //printf("%s, %.2f", balance[i].no_tarjeta, balance[i].transaccion);
    }
    //printf("%.2f", total);
    printf("\n");
    rewind(f_p);
    fclose(f_p);
    return total;
}
