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

#define CONTRASENA_ADMINISTRADOR "IngresoAdmin"

//MENÚ
enum opciones_e{
    oper_balance_total = 1,
    oper_transaccion = 2,
    oper_deposito = 3,
    oper_movimientos = 4,
    oper_salir = 5,
    oper_max
};

typedef struct opciones_s{
    enum opciones_e opciones;
    char *texto;
}opciones_t;

opciones_t opciones[oper_max] = {
    {.opciones = oper_balance_total, .texto = "Mostrar mi balance actual."},
    {.opciones = oper_transaccion, .texto = "Depositar o retirar dinero de mi cuenta."},
    {.opciones = oper_deposito, .texto = "Depositar dinero a alguien más"},
    {.opciones = oper_movimientos, .texto = "Mostrar mis movimientos de dinero"},
    {.opciones = oper_salir, .texto = "Salir de mi cuenta."}
};

//FUNCIÓN PARA IMPRIMIR EL TIEMPO (IMPORTANTE HACER FREE A HORARIOS)
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
typedef struct balance_s{
    char nombre[30];
    char no_tarjeta[30];
    float transaccion;
}balance_t;

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
}


//MOVIMIENTOS DE UN USUARIO ESPECÍFICO
int balance(balance_t**tamano, int no_tarjeta1){
    int num_balances = NUM_BALANCES;
    balance_t balance[num_balances];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(num_balances * sizeof(balance_t));

    FILE *f_p = fopen(F_BALANCES, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    printf("Estos son los movimientos de su cuenta: \n");
    for(int i; i < NUM_BALANCES ; i++){
        
        int var = fscanf(f_p, "%[^,], %[^,], %f", balance[i].nombre, balance[i].no_tarjeta, &balance[i].transaccion); //& solo para int y float, ya char es un puntero

        if(atoi(balance[i].no_tarjeta) == no_tarjeta1){
            printf("%s -> %.2f", balance[i].nombre, balance[i].transaccion);
        }


        //printf("%s, %.2f", balance[i].no_tarjeta, balance[i].transaccion);
    }
    printf("\n");
    rewind(f_p);
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
    return total;
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


//AÑADIR LÍNEAS PARA TRANSACCIONES
void movimiento(int no_tarjeta){
    float monto = 0;

    printf("Ingrese el monto que desea mover:  ");
    scanf("%f", &monto);

    FILE *fp_movimientos = fopen(F_BALANCES, "a");
    
    if(fp_movimientos == NULL){
        printf("No se puede acceder al archivo. \n");
    }
    
    else{
        fprintf(fp_movimientos, "%d,%f\n", no_tarjeta, monto);
    }
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
}


void main(void){
    int opcion = 0;
    int ingreso_inicial = 0;
    float monto;

    char contrasena[LEN_PASSWD];

    balance_t *tamano = NULL;
    
    printf("Desea ingresar como:\n1. Cliente\n2. Administrador\nOpción -> ");
    scanf("%d", &ingreso_inicial);

    

    if(ingreso_inicial == 2){
        printf("Ingrese la contraseña de administrador: ");
        scanf("%s", contrasena);

        if(!strcmp(CONTRASENA_ADMINISTRADOR, contrasena)){
            printf("Opciones de administrador:\n1. Mostrar todos los usuarios e información.\n2. Mostrar todos los movimientos.");
            int op_admin = 0;
            scanf("%d", &op_admin);
            switch (op_admin){
            case 1:
                //balances_todos(&tamano);
                break;
            case 2:
                balances_todos(&tamano);
                break;
            case 3:
                exit(0);
            }
        }
        else{
            printf("Contraseña incorrecta");
        }
    }

    else if (ingreso_inicial == 1){
    
        int no_tarjeta = ingreso();

        printf("Su número de tarjeta es: %d\n\n", no_tarjeta);


        for (int i = 0; i < oper_max -1 ; i++){

            printf("%d. %s \n", (opciones[i].opciones), opciones[i].texto);

        }

        printf("\nSeleccione qué desea hacer-> ");
        scanf("%d", &opcion);


        switch (opcion){

        case oper_balance_total:
            monto = balance_total(&tamano, no_tarjeta);
            printf("%.3f", monto);
            break;


        case oper_transaccion:
            printf("\nHa seleccionado la opción de realizar una transacción.\n");
            movimiento(no_tarjeta);
            break;

        case oper_deposito:
            printf("\nHa seleccionado la opción de realizar un depósito a alguien más. \n");
            deposito();
            break;

        case oper_movimientos:
            balance(&tamano, no_tarjeta);
            break;

        case oper_salir:
            printf("Gracias por preferirnos. :)\n");
            exit(0);
            break;
        }

    }
}   