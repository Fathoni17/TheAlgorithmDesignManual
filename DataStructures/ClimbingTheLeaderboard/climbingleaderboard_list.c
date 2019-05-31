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
typedef struct node{
    unsigned val;
    unsigned nscores;
    struct node* next;
} node;
typedef struct list{
    struct node * start;
} list;

void addElmt(list* l, unsigned* scores, int n){
    node *current;
    current = l->start;
    int i = 0;
    while(i<n){
        node *tmp;
        tmp = (node*) malloc (sizeof(node));
        if (i==0){
            tmp->val = scores[i];
            tmp->nscores = 1;
            tmp->next = NULL;
            l->start = tmp;
            current = tmp;
        } else {
            if (scores[i] == scores[i-1]){
                current->nscores++;
            } else {
                tmp->val = scores[i];
                tmp->nscores = 1;
                tmp->next = NULL;
                current->next = tmp;
                current = tmp;
            }
        }
        i++;
    }
}
unsigned insertElmt(list* l, unsigned e){
    struct node *current;
    unsigned i = 1;
    node *tmp;
    tmp = (node*) malloc (sizeof(node));
    tmp->val = e;
    tmp->nscores=1;

    if (l->start == NULL) {
        tmp->next = NULL;
        l->start = tmp;
        return 1;
	}
	// kalau nggak kosong
	else {
        for (current = l->start; current->next != NULL; current = current->next){
            if (current->next->val < e){
                break;
            }
            i++;
        }
        if (current->val == e){
            current->nscores++;
            return i;
        }else if(current->val < e){
            tmp->next = current;
            l->start = tmp;
            return i;
        }else{
            tmp->next = current->next;
            current->next = tmp;
            return i+1;
        }
    }
}
void climbingLeaderboard(FILE *fptr, int scores_count, int* scores, int alice_count, int* alice, int* result_count) {
    list l;
    l.start = NULL;

    addElmt(&l, scores, scores_count);
    for (int i=0; i<alice_count; i++){
        unsigned pos = insertElmt(&l, alice[i]);
        fprintf(fptr, "%d", pos);
        printf("%d", pos);

        if (i != alice_count- 1) {
            fprintf(fptr, "\n");
            printf("\n");
        }
    }
    *result_count = alice_count;    
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
    climbingLeaderboard(fptr, scores_count, scores, alice_count, alice, &result_count);

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