#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define F_BALANCES "balance.csv"
#define F_INFO "info.csv"
#define LEN_NOMBRE 50
#define LEN_TARJETA 30
#define LEN_PIN 8
#define LEN_BUFFER 1024
#define NUM_USUARIOS 1
#define NUM_PERSONA 1
#define LEN_PASSWD 512
#define NUM_BALANCES 20
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


typedef struct usuarios_s{
    char nombre[LEN_NOMBRE];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];
    char actividad[30];
    int encontrado;
}usuarios_t;

typedef struct balance_estado_s{
    char nombre[LEN_NOMBRE];
    char no_tarjeta[LEN_TARJETA];
    char transaccion[100];    
    int encontrado;
}balance_est_t;

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
    fclose(fp_info_usuario);

    fputs("\n\t\t\tBalances en la cuenta", fp_estado);
    fputs("\nDinero disponile en su cuenta: ", fp_estado);
    fputs(monto_final, fp_estado);
    
    //PARTE MOVIMIENTOS DE DINERO, se tuvo que leer el archivo de balances porque la otra manera no funciona con fputs
    fputs("\n\n\t\t\tTodos los movimmientos realidos:\n", fp_estado);
    while (!balance1[0].encontrado && fgets(buffer, LEN_BUFFER, fp_balances) != NULL){
        
        char *p_nombre_b = strtok(buffer, ",");
        char *p_no_tarjeta_b = strtok(NULL, ",");
        char *p_transaccion_b = strtok(NULL, ",");

        strcpy(balance1->nombre, p_nombre_b);
        strcpy(balance1->no_tarjeta, p_no_tarjeta_b);
        strcpy(balance1->transaccion, p_transaccion_b);

        if(atoi(p_no_tarjeta_b) == no_tarejeta3){
            //printf("%s, %s, %s", balance1->nombre, balance1->no_tarjeta, balance1->transaccion);
            fputs(balance1->nombre, fp_estado); fputs(" -> ", fp_estado);
            fputs(balance1->transaccion, fp_estado);
        }

    }
    fclose(fp_balances);
    fclose(fp_estado);  //AÑADIR EL FSEEK
}



void main(void){
    char nombre[30];
    printf("Ingrese el nombre del archivo -> ");
    scanf("%s", nombre);
    estado_cuenta(198763, 10000.1, nombre);
}

/* 
            if(!strcmp(p_tarjeta, tarjeta) && !strcmp(p_pin, pin)){
                printf("Ingreso exitoso. Bienvenido %s \n", usuario->nombre);
                k = 0;
                validador = 1;
                no_tarjeta = atoi(p_tarjeta);
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
*/