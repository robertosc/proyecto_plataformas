#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define F_BALANCES "balance.csv"

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

int main(){
    int a = countlines(F_BALANCES);
    printf("%d", a);
}
