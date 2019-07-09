#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define F_INFO "info.csv"
#define F_BALANCE "balance.csv"
#define NUM_USERS 1
#define LEN_BUFFER 1024
#define LEN_PASSWD 512
#define NUM_BALANCES 20

file_balance
file_info
num_balances
num_persona
len_buffer
len_passwd

enum opciones_e{
    oper_ingresar = 1,
    oper_sacar = 2,
    oper_deposit = 3,
    oper_movimientos = 4,
    oper_salir = 5,
    oper_max
};

typedef struct opciones_s{
    enum opciones_e opciones;
    char *texto;
}opciones_t;

opciones_t opciones[oper_max] = {
    {.opciones = oper_ingresar, .texto = "Ingresar a mi cuenta"},
    {.opciones = oper_sacar, .texto = "Retirar dinero de mi cuenta."},
    {.opciones = oper_deposit, .texto = "Depositar dinero a mi cuenta"},
    {.opciones = oper_movimientos, .texto = "Mostrar mis movimientos de dinero"},
    {.opciones = oper_salir, .texto = "Salir de mi cuenta."}

}

typedef struct usuarios_s{
    char nombre[100];
    char num_tarjeta[20];
    char contraseña[18];
    float balance;
    int encontrado;
}usuarios_t;


char *ingreso(){
    char *tarjeta = malloc(LEN_USER);
    int validador = 0;
    printf("Ingrese su número de tarjeta: ");
    scanf("%s", tarjeta);
    return tarjeta;
}
char *contraseña(void){
    char *passwd = malloc(LEN_PASSWD);
    //hacer malloc porque el array anterior no tiene tamaño
    printf("Ingrese su número de PIN -> ");
    scanf("%s", passwd);
    return passwd;
}


typedef struct balance_s{
    char nombre[100];
    float transaccion;
}balance_t;

int balance(int *num_lines, balance_t**tamano){
    int num_balances = NUM_BALANCES;
    balance_t balance[NUM_BALANCES];

    //char buffer_b[len_buffer];
    *tamano = (balance_t*) malloc(NUM_BALANCES * sizeof(balance_t));

    FILE *f_p = fopen(file_balance, "r");
    //memset(buffer_b, 0, sizeof(char *len_buffer);
    for(int i; i <  ; i++){
        int var = fscanf(f_p, "%[^,], %f", balance[i].nombre, &balance[i].transaccion); //& solo para int y float, ya char es un puntero
        printf("%s, %f", balance[i].nombre, balance[i].transaccion);
    }
}

int countlines(char*filename){  //in filename mist go the name of the file
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
    printf("There's %d", counter);
    return counter;
}


int main(void){
    char *tarjeta;
    char *passwd;
    usuarios_t usuarios[NUM_USERS];

    char equipo_buscado[60];
    char buffer[LEN_BUFFER];

    FILE *fp = fopen(file_info, "r");
    memset(usuarios, 0, sizeof(usuarios_t) * NUM_USERS);
    memset(buffer, 0, sizeof(char) * LEN_BUFFER);

    int k=1;

    while(k){
        tarjeta = ingreso();
        passwd = contraseña();


        int repetidor, contador;
        int validor;

        while (!usuarios[0].encontrado && fgets(buffer, len_buffer, fp) != NULL){
            char *p_nombre = strtok(buffer, ",");
            char *p_num_tarjeta = strtok(NULL, ",");
            char *p_contraseña = strtok(NULL, ",");

            strcpy(usuarios->nombre, p_nombre);
            strcpy(usuarios->num_tarjeta, p_num_tarjeta);
            strcpy(usuarios->contraseña, p_contraseña);

            //if(!strcmp(p_num_tarjeta, tarjeta) && !strcpy(p_contraseña, passwd));
        }
        
    }

}







