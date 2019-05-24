#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char* str, int i, int j){
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
}

void selectionsort(char* str){
    int len = strlen(str);
    int idx;
    for (int i=0; i<len; i++){
        idx = i;
        for (int j=i+1; j<len; j++){
            if (str[idx]>str[j]){
                idx = j;
            }
        }
        swap(str, i, idx);
    }
}

int main(){
    char str[256];
    printf("Input String: ");
    scanf("%s", str);

    printf("Before: %s\n", str);
    selectionsort(str);
    printf("After: %s", str);

    return 0;
}