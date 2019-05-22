#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getpos(char* str, char x, int pos){
    for (int i=0; i<=pos; i++){
        if (str[i]>x)
            return i;
    }
    return pos;
}

void swap(char* str, int i){
    char tmp = str[i];
    str[i] = str[i+1];
    str[i+1] = tmp;
    if (str[i]<str[i-1]){
        swap(str, i-1);
    }
}

void insertionsort(char* str){
    int len = strlen(str);

    for (int i=0; i<len-1; i++){
        if (str[i+1]<str[i]){
            swap(str, i);
        }
    }
}

int main(){
    char str[256];
    printf("Input String: ");
    scanf("%s", str);

    printf("Before: %s\n", str);
    insertionsort(str);
    printf("After: %s", str);

    return 0;
}