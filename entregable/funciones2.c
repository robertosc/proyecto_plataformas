#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "archivo.h"

//FUNCIÓN PARA IMPRIMIR EL TIEMPO
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

//FUNCIÓN PARA MOSTRAR ESTADOS DE CUENTA
int estado_cuenta(int no_tarejeta3, float balance_total, char archivo_estado[30]){
    usuarios_t usuario[NUM_USUARIOS];
    balance_est_t balance1[NUM_USUARIOS];

    char monto_final[LEN_BUFFER];
    char *fecha = tiempo(1);
    char *hora = tiempo(2);
    char buffer[LEN_BUFFER];
    
    FILE *fp_estado = fopen(archivo_estado, "w");
    FILE *fp_info_usuario = fopen(F_INFO, "r");
    FILE *fp_balances = fopen(F_BALANCES, "r");

    memset(usuario, 0, sizeof(usuarios_t)* NUM_USUARIOS);
    memset(balance1, 0, sizeof(balance_est_t)* NUM_USUARIOS);
    memset(buffer, 0, sizeof(char)*LEN_BUFFER);

    //PASAMOS BALANCE_TOTAL A STRING CON SPRINTF
    sprintf(monto_final, "%.3f", balance_total);

    //Manejo de errores
    if((fp_estado == NULL) || (fp_info_usuario == NULL) || (fp_balances) == NULL){
        printf("Hubo un error con los archivos, contacte con el centro de atención.");
        exit(0);
    }

    //Lo que se va a imprimir
    fputs("\t\t\tEstado de cuenta.\nEmitido el día: ", fp_estado);
    fputs(fecha, fp_estado); 
    fputs(" A las: ", fp_estado); 
    fputs(hora, fp_estado);
    fputs("\n\n\t\t\tInformación de usuario:\n", fp_estado);


    while(!usuario[0].encontrado && fgets(buffer, LEN_BUFFER, fp_info_usuario) != NULL){

        char *p_nombre = strtok(buffer, ",");
        char *p_tarjeta = strtok(NULL, ",");
        char *p_pin = strtok(NULL, ",");
        char *p_actividad = strtok(NULL, ",");

        strcpy(usuario->nombre, p_nombre);
        strcpy(usuario->tarjeta, p_tarjeta);
        strcpy(usuario->pin, p_pin);
        strcpy(usuario->actividad, p_actividad);

        if(atoi(p_tarjeta)== no_tarejeta3){
            fputs("Nombre: ", fp_estado);
            fputs(usuario->nombre, fp_estado);

            fputs("\nNúmero de tarjeta: ", fp_estado);
            fputs(usuario->tarjeta, fp_estado);

            fputs("\nEstado: ", fp_estado);
            fputs(usuario->actividad, fp_estado);
        }
    }

    fputs("\n\t\t\tBalances en la cuenta", fp_estado);
    fputs("\nDinero disponile en su cuenta: ", fp_estado);
    fputs(monto_final, fp_estado);
    
    //PARTE MOVIMIENTOS DE DINERO, se tuvo que leer el archivo de balances porque la otra manera no funciona con fputs
    fputs("\n\n\t\t\tTodos los movimientos realidos:\n", fp_estado);
    while (!balance1[0].encontrado && fgets(buffer, LEN_BUFFER, fp_balances) != NULL){
        
        char *p_nombre_b = strtok(buffer, ",");
        char *p_no_tarjeta_b = strtok(NULL, ",");
        char *p_transaccion_b = strtok(NULL, ",");

        strcpy(balance1->nombre, p_nombre_b);
        strcpy(balance1->no_tarjeta, p_no_tarjeta_b);
        strcpy(balance1->transaccion, p_transaccion_b);

        if(atoi(p_no_tarjeta_b) == no_tarejeta3){
            //printf("%s, %s, %s", balance1->nombre, balance1->no_tarjeta, balance1->transaccion);
            fputs(balance1->nombre, fp_estado); 
            fputs(" -> ", fp_estado);
            fputs(balance1->transaccion, fp_estado);
        }

    }
    fseek(fp_balances, 0, SEEK_SET);
    fseek(fp_estado, 0, SEEK_SET);
    fseek(fp_info_usuario, 0, SEEK_SET);

    fclose(fp_info_usuario);
    fclose(fp_balances);
    fclose(fp_estado);  
}

//AÑADIR LÍNEAS PARA TRANSACCIONES
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
        fprintf(fp_movimientos, "%s,%d,%.3f\n", nombre, no_tarjeta, monto);
    }

    fclose(fp_movimientos);
}

//FUNCIÓN PARA DEPOSITARLE DINERO A ALGUIEN MAS
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

    fclose(fp_movimientos);
}

