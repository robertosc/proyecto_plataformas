#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "archivo.h"

int ingreso(int opcion);
int countlines(char*nombre_archivo);
int balances_todos(balance_t**tamano);
int balance(balance_t**tamano, int no_tarjeta1);
int balance_total(balance_t**tamano, int no_tarjeta1);
int estado_cuenta(int no_tarejeta3, float balance_total, char archivo_estado[30]);
void movimiento(int no_tarjeta);
void deposito(void);
char *tiempo(int opcion); //Opción 1 fecha, 2 hora
void menu(void);

float total;

void main(void){
    int inicializador = 1;
    int opcion_menu = 1;
    int opcion_admin = 0;
    int opcion_usuario = 0;
    float monto_total, monto_estado;
    char contrasena_admin[30];
    char *fecha = tiempo(1);
    char *hora = tiempo(2);
    balance_t *tamano = NULL;

    while(1){
        printf("Desea ingresar como:\n1. Cliente\n2. Administrador\n\nOpción -> ");
        scanf("%d", &opcion_usuario);
        if((opcion_usuario == 1) || (opcion_usuario == 2)){
            break;
        }
        else{
            printf("Ingrese una opción válida\n\n");
        }
    }

    if(opcion_usuario == 1){
        int no_tarjeta = ingreso(1);
        printf("Número de tarjeta: %d\n", no_tarjeta);
        printf("Ingreso el %s a las %s\n\n", fecha, hora);
        while(inicializador){
            menu();
            printf("Opción -> ");
            scanf("%d", &opcion_menu);
            if(opcion_menu == 1){
                monto_total = balance_total(&tamano, no_tarjeta);
                printf("Su balance total es de: %.3f\n\n", monto_total);
                total = 0;
            }

            else if(opcion_menu == 2){
                movimiento(no_tarjeta);
                printf("Su deposito se verá reflejado en el balance total cuando vuelva a entrar.\n");
            }
            
            else if(opcion_menu == 3){
                deposito();
            }

            else if(opcion_menu == 4){
                balance(&tamano, no_tarjeta);
            }
            
            else if(opcion_menu == 5){
                monto_estado = balance_total(&tamano, no_tarjeta);
                total = 0;
                char nombre_archivo[LEN_NOMBRE];
                printf("Ingrese el nombre del archivo en donde desea guardar su estado de cuenta -> ");
                scanf("%s", nombre_archivo);
                estado_cuenta(no_tarjeta, monto_estado, nombre_archivo);
            }

            else if(opcion_menu == 6){
                printf("\n\nGracias por preferir nuestros servicios.\n");
                inicializador = 0;
            }
        }
    }
    else if(opcion_usuario == 2){
        while(strcmp(CONTRASENA_ADMINISTRADOR, contrasena_admin)){
            printf("Ingrese la contraseña de administrador -> ");
            scanf("%s", contrasena_admin);
        }
        printf("Ingreso el %s a las %s\n\n", fecha, hora);
        printf("Opciones de administrador:\n1. Mostrar info de todos los clientes\n2. Mostrar todos los movimientos de dinero\n3. Salir\n\nOpción -> ");
        scanf("%d", &opcion_admin);
        while(inicializador){
            if(opcion_admin == 1){
                ingreso(2);
            }

            else if(opcion_admin == 2){
                balances_todos(&tamano);
            }
            
            else if(opcion_admin == 3){
                inicializador = 0;
            }

            else{
                printf("Error. Ingrese una opción válida.\n");
            }
        }
    }
}
