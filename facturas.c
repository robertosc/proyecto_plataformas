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

int balances_todos(balance_t**tamano){  //HACER CAMBIOS EN EL MAIN
    int num_balances = countlines();
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
}

typedef struct usuarios_s{
    char nombre[LEN_NOMBRE];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];
    char actividad[30];
    int encontrado;
}usuarios_t;

int estado_cuenta(int no_tarejeta3, float balance_total){
    usuarios_t usuario[NUM_USUARIOS];

    char archivo_estado[30];
    char *fecha = tiempo(1);
    char *hora = tiempo(2);
    char buffer[LEN_BUFFER];

    printf("Ingrese el nombre con el que desea guardar el estado de cuenta con terminación .txt -> ");
    scanf("%s", archivo_estado);

    FILE *fp_estado = fopen(archivo_estado, "w");


    FILE *fp_info_usuario = fopen(F_INFO, "r");
    memset(usuario, 0, sizeof(usuarios_t)* NUM_USUARIOS);
    memset(buffer, 0, sizeof(char)*LEN_BUFFER);

    //Manejo de errores
    if((fp_estado == NULL) || (fp_info_usuario == NULL)){
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
        int j= 0;

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
    fclose(fp_estado);
    fclose(fp_info_usuario);
}


void main(void){
    estado_cuenta(198763, 10000);
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