#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "archivo.h"


//MENÚ
void menu(void){
    enum opciones_e{
        oper_balance_total = 1,
        oper_transaccion = 2,
        oper_deposito = 3,
        oper_movimientos = 4,
        oper_estado = 5,
        oper_salir = 6,
        oper_max
    };

    typedef struct opciones_s{
        enum opciones_e opciones;
        char *texto;
    }opciones_t;

    opciones_t opciones[oper_max] = {
        {.opciones = oper_balance_total, .texto = "Mostrar mi balance actual."},
        {.opciones = oper_transaccion, .texto = "Depositar o retirar dinero de mi cuenta."},
        {.opciones = oper_deposito, .texto = "Depositar dinero a alguien más."},
        {.opciones = oper_movimientos, .texto = "Mostrar mis movimientos de dinero."},
        {.opciones = oper_estado, .texto = "Generar mi estado de cuenta."},
        {.opciones = oper_salir, .texto = "Salir de mi cuenta."}
    };
    printf("\n\tOpciones disponibles\n");

    for (int i = 0; i < oper_max -1 ; i++){
        printf("%d. %s \n", (opciones[i].opciones), opciones[i].texto);
    }
}
