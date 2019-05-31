#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define min(int a, int b) a<b ? a:b
char* readline();

typedef struct node
{
    unsigned val;
    struct node* next;
    struct node* prev;
} node;

typedef struct list
{
    struct node* start;
} list;

int insertElmt(list* l, unsigned e, node* median){
    struct node *current;
    node *tmp;
    tmp = (node*) malloc (sizeof(node));
    tmp->val = e;

    if (l->start == NULL) {
        tmp->next = NULL;
        tmp->prev = NULL;
        l->start = tmp;
        //median = tmp;
        return 99;
	}
	// kalau nggak kosong
	else {
        if (median->val > e){
            // insert to left
            for (current = median; current->prev != NULL; current = current->prev){
                if (current->prev->val < e)
                    break;
            }
            tmp->prev = current->prev;
            tmp->next = current;
            if (current->prev != NULL)
                current->prev->next = tmp;
            current->prev = tmp;
            // median = median->prev;
            return -1;
        } else if (median->val == e){
            // insert at next
            tmp->prev=current;
            tmp->next=current->next;
            if (current->next != NULL)
                current->next->prev = tmp;
            current->next=tmp;
            // median=median->next;
            return 0;
        } else {
            // insert to right
            for (current = median; current->next != NULL; current = current->next){
                if (current->next->val > e)
                    break;
            }
            tmp->next = current->next;
            tmp->prev = current;
            if (current->next != NULL)
                current->next->prev = tmp; 
            current->next = tmp;
            // median=median->next;
            return 1;
        }
    }
}
/*
 * Complete the runningMedian function below.
 */

/*
 * Please store the size of the double array to be returned in result_count pointer. For example,
 * double a[3] = {1.1, 2.2, 3.3};
 *
 * *result_count = 3;
 *
 * return a;
 *
 */
double* runningMedian(int a_count, int* a, int* result_count) {
    /*
     * Write your code here.
     */
    *result_count = a_count;
    double *hasil = (double*)malloc(a_count*sizeof(double));
    double test[50];
    list l;
    l.start = NULL;
    node* median = NULL;
    for(int i=0; i<a_count; i++){
        int get = insertElmt(&l, a[i], median);
        switch (get){
        case 99:{
            median = l.start;
        }    break;
        case -1:{
            if ((i+1)%2)
                {}
            else
                median = median->prev;
        }    break;
        case 0:{
            if ((i+1)%2)
                median = median->next;
        }    break;
        case 1:{
            if ((i+1)%2)
                median = median->next;
        }    break;
        
        default:
            break;
        }
        hasil[i] = (double) ((i+1)%2) ? (median->val):(median->val+median->next->val)/2.0;
        if (i<50)
            test[i] = (double) ((i+1)%2) ? (median->val):(median->val+median->next->val)/2.0;
    }
    return hasil;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* a_count_endptr;
    char* a_count_str = readline();
    int a_count = strtol(a_count_str, &a_count_endptr, 10);

    if (a_count_endptr == a_count_str || *a_count_endptr != '\0') { exit(EXIT_FAILURE); }

    int a[a_count];

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        char* a_item_endptr;
        char* a_item_str = readline();
        int a_item = strtol(a_item_str, &a_item_endptr, 10);

        if (a_item_endptr == a_item_str || *a_item_endptr != '\0') { exit(EXIT_FAILURE); }

        a[a_itr] = a_item;
    }

    int result_count;
    double* result = runningMedian(a_count, a, &result_count);

    for (int result_itr = 0; result_itr < result_count; result_itr++) {
        fprintf(fptr, "%.1lf", result[result_itr]);
        printf("%.1lf", result[result_itr]);

        if (result_itr != result_count - 1) {
            fprintf(fptr, "\n");
            printf("\n");
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