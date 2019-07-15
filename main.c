#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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


//MENÚ
enum opciones_e{
    oper_sacar = 1,
    oper_deposit = 2,
    oper_movimientos = 3,
    oper_salir = 4,
    oper_max
};

typedef struct opciones_s{
    enum opciones_e opciones;
    char *texto;
}opciones_t;

opciones_t opciones[oper_max] = {
    {.opciones = oper_sacar, .texto = "Retirar dinero de mi cuenta."},
    {.opciones = oper_deposit, .texto = "Depositar dinero a mi cuenta"},
    {.opciones = oper_movimientos, .texto = "Mostrar mis movimientos de dinero"},
    {.opciones = oper_salir, .texto = "Salir de mi cuenta."}
};


//FUNCION CONTAR LÍNEAS
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

//LECTURA DE TRANSACCIONES
typedef struct balance_s{
    char nombre[100];
    float transaccion;
}balance_t;

int balance(balance_t**tamano){
    int num_balances = NUM_BALANCES;   //MODIFICAR PARA USAR CON FUNCION CONTAR LINEAS
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_INFO, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    for(int i; i < NUM_BALANCES ; i++){
        int var = fscanf(f_p, "%[^,], %f", balance[i].nombre, &balance[i].transaccion); //& solo para int y float, ya char es un puntero
        printf("%s, %.2f", balance[i].nombre, balance[i].transaccion);
    }
}


//FUNCION DE INGRESO
typedef struct usuarios_s{
    char nombre[LEN_NOMBRE];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];
    char actividad[30];
    int encontrado;
}usuarios_t;

int ingreso(void){
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
        
        while(!usuario[0].encontrado && fgets(buffer, LEN_BUFFER, fp_usuarios) != NULL){
            int j= 0;

            char *p_nombre = strtok(buffer, ",");
            char *p_tarjeta = strtok(NULL, ",");
            char *p_pin = strtok(NULL, ",");
            char *p_actividad = strtok(NULL, ",");

            strcpy(usuario->nombre, p_nombre);
            strcpy(usuario->tarjeta, p_tarjeta);
            strcpy(usuario->pin, p_pin);
            strcpy(usuario->actividad, p_actividad);

            //printf("%s, %s, %s, %s", usuario->nombre, usuario->tarjeta, usuario->pin, usuario->actividad);

            if(!strcmp(p_tarjeta, tarjeta) && !strcmp(p_pin, pin)){
                printf("Ingreso exitoso. Bienvenido %s. \n\n", usuario->nombre);
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


void main(void){
    int no_tarjeta = ingreso();

    printf("Su número de tarjeta es: %d\n\n", no_tarjeta);
    
    printf("Seleccione qué desea hacer: \n");
    for (int i = 0; i < oper_max -1 ; i++){
        printf("%d. %s \n", (opciones[i].opciones), opciones[i].texto);
    }
}