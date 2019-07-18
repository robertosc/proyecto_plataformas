#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



//FUNCIÓN PARA IMPRIMIR EL TIEMPO (IMPORTANTE HACER FREE A HORARIOS)

//FUNCION CONTAR LÍNEAS

//MOVIMIENTOS DE UN USUARIO ESPECÍFICO

//FUNCIÓN PARA MOSTRAR BALANCE TOTAL

//FUNCION DE INGRESO

//AÑADIR LÍNEAS PARA TRANSACCIONES

//FUNCIÓN PARA DEPOSITARLE DINERO A ALGUIEN MAS

//FUNCIÓN PARA MOSTRAR ESTADOS DE CUENTA


void main(void){
    int opcion = 0;
    int ingreso_inicial = 0;


    char contrasena[LEN_PASSWD];

    balance_t *tamano = NULL;
    
    printf("Desea ingresar como:\n1. Cliente\n2. Administrador\nOpción -> ");
    scanf("%d", &ingreso_inicial);

    

    if(ingreso_inicial == 2){
        printf("Ingrese la contraseña de administrador: ");
        scanf("%s", contrasena);

        if(!strcmp(CONTRASENA_ADMINISTRADOR, contrasena)){
            char *fecha = tiempo(1);
            char *hora = tiempo(2);
            printf("Ingreso el %s a las %s\n", fecha, hora);
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
        
        int no_tarjeta = ingreso(1);
        char *fecha = tiempo(1);
        char *hora = tiempo(2);
        printf("Ingreso el %s a las %s\n", fecha, hora);
        printf("Su número de tarjeta es: %d\n\n", no_tarjeta);


        for (int i = 0; i < oper_max -1 ; i++){

            printf("%d. %s \n", (opciones[i].opciones), opciones[i].texto);

        }

        printf("\nSeleccione qué desea hacer-> ");
        scanf("%d", &opcion);


        switch (opcion){

        case oper_balance_total:
            balance_total(&tamano, no_tarjeta);
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

        case oper_estado:
            float monto = balance_total(&tamano, no_tarjeta);
            char nombre_archivo[LEN_NOMBRE];

            printf("Ingrese el nombre del archivo que desea crear -> ");
            scanf("%s", nombre_archivo);

            estado_cuenta(no_tarjeta,monto, nombre_archivo);

        case oper_salir:
            printf("Gracias por preferirnos. :)\n");
            exit(0);
            break;
        }
    }

    else{
        printf("Error. Opción no disponible");
        exit(0);
    }
}   
