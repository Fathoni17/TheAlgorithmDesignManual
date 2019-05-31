#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the climbingLeaderboard function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//
int* climbingLeaderboard(int scores_count, int* scores, int alice_count, int* alice, int* result_count) {
    int *result = (int*)malloc(alice_count*sizeof(int));
    *result_count = alice_count;

    int *rank = (int*)malloc(scores_count*2*sizeof(int));

    //do while(j<scores_count)
    int nact=0;     // n used block of memory
    int i=0;        // point to i-th scores
    *(rank+nact*2+0)=scores[i];
    *(rank+nact*2+1)=1;
    nact++;
    i++;
    while (i < scores_count)
    {
        if(*(rank+(nact-1)*2+0) == scores[i]){
            *(rank+(nact-1)*2+1)+=1;
        }else{
            *(rank+nact*2+0) = scores[i];
            *(rank+nact*2+1) = 1;
            nact++;
        }
        i++;
    }

    // preparing
    int length;
    if (scores_count-nact<alice_count){
        rank = (int*)realloc(rank, (nact+alice_count)*2*sizeof(int));
        length = nact+alice_count;
    } else {
        length = nact;
    }

    // sort rank
    int j = 0;
    for(int i=0; i<alice_count; i++){
        int first = 0, last = nact-1;
        int middle = (first+last)/2;
        while (first <= last)
        {
            if (*(rank+middle*2+0) > alice[i]){
                first = middle+1;
            } else if (*(rank+middle*2+0) == alice[i]){
                // found at middle (+1 karna index mulai dari 0);
                result[j] = middle;
                *(rank+middle*2+1)+=1;
                printf("%d->%d\n", result[j]+1, alice[i]);
                j++;
                break;
            } else {
                last = middle-1;
            }
            middle = (first+last)/2;
            // printf("..%d.", middle);
        }
        if (first > last){
            // not found
            int idx = first;
            result[j] = first;
            nact++;
            // if (idx>nact-2){
            //     printf("%d--%d  Paling Belakang --- ", alice[i], result[j]);
            //     *(rank+idx*2+0) = alice[i];
            //     *(rank+idx*2+1) = 1;
            // }else{
            printf("%d--%d", result[j]+1, alice[i]);
            //     printf("%d--%d  mulai pemindahan dari %d->%d --- ", alice[i], result[j], idx, nact-1);
            //     int tmp1[2]={0,0}, tmp2[2]={*(rank+(idx)*2+0),*(rank+(idx)*2+1)};
            //     *(rank+idx*2+0) = alice[i];
            //     *(rank+idx*2+1) = 1;
            //     for (int k=idx+1; k<nact; k++){
            //         tmp1[0] = tmp2[0];
            //         tmp1[1] = tmp2[1];
            //         tmp2[0] = *(rank+k*2+0);
            //         tmp2[1] = *(rank+k*2+1);
            //         *(rank+k*2+0) = tmp1[0];
            //         *(rank+k*2+1) = tmp1[1];
            //     }
            // }

            // printing
            // for(int i=0;i<nact;i++){
            //     if (*(rank+i*2+1) == 1)
            //         printf("%d ", *(rank+i*2+0));
            //     else{
            //         for (int j=0; j<*(rank+i*2+1); j++){
            //             printf("%d ", *(rank+i*2+0));
            //         }
            //     }
            // }
            printf("\n");
            j++;
        }
    }

    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* scores_count_endptr;
    char* scores_count_str = readline();
    int scores_count = strtol(scores_count_str, &scores_count_endptr, 10);

    if (scores_count_endptr == scores_count_str || *scores_count_endptr != '\0') { exit(EXIT_FAILURE); }

    char** scores_temp = split_string(readline());

    int* scores = malloc(scores_count * sizeof(int));

    for (int i = 0; i < scores_count; i++) {
        char* scores_item_endptr;
        char* scores_item_str = *(scores_temp + i);
        int scores_item = strtol(scores_item_str, &scores_item_endptr, 10);

        if (scores_item_endptr == scores_item_str || *scores_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(scores + i) = scores_item;
    }

    char* alice_count_endptr;
    char* alice_count_str = readline();
    int alice_count = strtol(alice_count_str, &alice_count_endptr, 10);

    if (alice_count_endptr == alice_count_str || *alice_count_endptr != '\0') { exit(EXIT_FAILURE); }

    char** alice_temp = split_string(readline());

    int* alice = malloc(alice_count * sizeof(int));

    for (int i = 0; i < alice_count; i++) {
        char* alice_item_endptr;
        char* alice_item_str = *(alice_temp + i);
        int alice_item = strtol(alice_item_str, &alice_item_endptr, 10);

        if (alice_item_endptr == alice_item_str || *alice_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(alice + i) = alice_item;
    }

    int result_count;
    int* result = climbingLeaderboard(scores_count, scores, alice_count, alice, &result_count);

    for (int i = 0; i < result_count; i++) {
        int x = *(result + i);
        x++;
        fprintf(fptr, "%d", x);

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}