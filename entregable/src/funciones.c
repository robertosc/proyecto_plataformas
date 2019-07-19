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
    
    int finalizador = 0;
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
                if(!strcmp(TARJETA_ADMIN, tarjeta) && !strcmp(PIN_ADMIN, pin)){
                    printf("%s, %s, %s, %s", usuario->nombre, usuario->tarjeta, usuario->pin, usuario->actividad);
                    k = 0;
                    validador = 1;
                    finalizador = 1;
                    no_tarjeta = atoi(p_tarjeta);
                }
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

//FUNCION CONTAR LÍNEAS: esta para no tener que "batear" la cantidad de lineas y dar espacios adecuados
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

        reader = getc(fp); //Se usa para leer caracteres de un archivo
    }
    rewind(fp); //Devuelve el puntero al inicio
    fclose(fp);
    return counter + 1;
}


//LECTURA DE TODAAS LAS TRANSACCIONES
void estados_todos(void){
    balance_est_t balance1[NUM_USUARIOS];
    char monto_final[LEN_BUFFER];
    char buffer[LEN_BUFFER];

    FILE *fp_balances = fopen(F_BALANCES, "r");

    memset(balance1, 0, sizeof(balance_est_t)* NUM_USUARIOS);
    memset(buffer, 0, sizeof(char)*LEN_BUFFER);

    //Manejo de errores
    if((fp_balances) == NULL){
        printf("Hubo un error con los archivos, contacte con el centro de atención.");
        exit(0);
    }

    //Lo que se va a imprimir
    while (!balance1[0].encontrado && fgets(buffer, LEN_BUFFER, fp_balances) != NULL){
        char *p_nombre_b = strtok(buffer, ",");
        char *p_no_tarjeta_b = strtok(NULL, ",");
        char *p_transaccion_b = strtok(NULL, ",");

        strcpy(balance1->nombre, p_nombre_b);
        strcpy(balance1->no_tarjeta, p_no_tarjeta_b);
        strcpy(balance1->transaccion, p_transaccion_b);
        printf("%s, %s, %s", balance1->nombre, balance1->no_tarjeta, balance1->transaccion);

    }
    fseek(fp_balances, 0, SEEK_SET);

    fclose(fp_balances);  
} 


//MOVIMIENTOS DE UN USUARIO ESPECÍFICO
int balance(balance_t**tamano, int no_tarjeta1){
    int num_balances = countlines(F_BALANCES); //contamos lineas para dar tamaño
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t)); //Damos tamano exacto

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    printf("Estos son los movimientos de su cuenta: \n");
    for(int i; i < num_balances ; i++){  //Contamos hasta la cant de lineas exacta
        
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
float total = 0; //No deje declarar float dentro de balance total

float balance_total(balance_t**tamano, int no_tarjeta1){
    int num_balances = countlines(F_BALANCES);
    balance_t balance[num_balances];

    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //printf("\nActualmente su cuenta tiene: \n");
    for(int i; i < num_balances ; i++){
        
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

void total_cero(void){   //se usa para poner total en 0, no se logró de otra manera, si no, si
    total = 0;             //se usa balance_total varaias veces, da valores erroneos
}

