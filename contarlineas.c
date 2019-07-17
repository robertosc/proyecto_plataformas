#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define F_BALANCES "balance.csv"

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
    return counter+1; //Se debe añadir +1 porque al final no hay \n, sin no un EOF que complicaría el codigo
}

int main(){
    int a = countlines();
    printf("%d", a);
}
