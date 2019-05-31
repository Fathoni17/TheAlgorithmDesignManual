#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

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
int maxheap[100000], minheap[100000], hmax=0, hmin=0;
void minheap_down(){
	int cur=0;
	while(cur<hmin && (2*cur+1 < hmin && (minheap[cur] > minheap[2*cur +1]))||(2*cur+2 < hmin && (minheap[cur]> minheap[2*cur+2])) ){
		if(minheap[2*cur+1] < minheap[2*cur+2] || (2*cur + 2)>=hmin)
		{
			int temp = minheap[2*cur+1];
			minheap[2*cur+1] = minheap[cur];
			minheap[cur]=temp;
	
			cur = 2*cur + 1;
		}else{
			int temp = minheap[2*cur+2];
			minheap[2*cur+2] = minheap[cur];
			minheap[cur]=temp;
			cur = 2*cur + 2;
		}		
	}
}
void maxheap_down(){
	int cur=0;
	//printf("gaga%d ",maxheap[0]);
	while(cur < hmax && (2*cur+1 < hmax && (maxheap[cur] < maxheap[2*cur +1]))||(2*cur+2 < hmax && (maxheap[cur]< maxheap[2*cur+2])) )
	{
		if(maxheap[2*cur+1] > maxheap[2*cur+2] || (2*cur + 2)>=hmax)
		{
			int temp = maxheap[2*cur+1];
			maxheap[2*cur+1] = maxheap[cur];
			maxheap[cur]=temp;
	
			cur = 2*cur + 1;
		}
		else
		{
			int temp = maxheap[2*cur+2];
			maxheap[2*cur+2] = maxheap[cur];
			maxheap[cur]=temp;
			cur = 2*cur + 2;
		}		
	}
}
void minheap_up(){
    int cur = hmin-1;
	
	while(minheap[cur]< minheap[(cur-1)/2])
	{
		int temp = minheap[cur];
		minheap[cur]= minheap[(cur-1)/2];
		minheap[(cur-1)/2] = temp;
	
		cur = (cur-1)/2;
	}

}
void maxheap_up(){
    int cur = hmax-1;
	
	while(maxheap[cur]> maxheap[(cur-1)/2])
	{
		int temp = maxheap[cur];
		maxheap[cur]=maxheap[(cur-1)/2];
		maxheap[(cur-1)/2] = temp;
	
		cur = (cur-1)/2;
	}
}
void insert(int num){
    if(hmax==0 && hmin==0){ // fisrt elmt
        maxheap[hmax++]= num;
    }else if(hmin==0 && hmax!=0){
        if(num < maxheap[0]){
            int temp = maxheap[0];
            maxheap[0]= num;
            minheap[hmin++]= temp;
        }else
            minheap[hmin++]=num;
    } else if(hmax!=0 && hmin!=0){
        int i;
        if(hmax > hmin){
            if(num < maxheap[0]){ 
                minheap[hmin++]=maxheap[0];
                minheap_up();
                maxheap[0]=num;
                maxheap_down();
            }else{            
                minheap[hmin++]=num;
                minheap_up();        
            }
        }else if(hmin >= hmax){
            if(num > minheap[0]){
                maxheap[hmax++]=minheap[0];
                maxheap_up();
                minheap[0]=num;
                //hmin = hmin-1;
                minheap_down();
            }else{
                maxheap[hmax++]=num;
                maxheap_up();
            }
        } else  {
            if(num > minheap[0]) {
                minheap[hmin++]=num;
                minheap_up();
            } else {
                maxheap[hmax++]=num;
                maxheap_up();
            }
        }
    }
}

double findMedian(){
    if ( (hmin+hmax) % 2 == 0 ){
        return (double) (maxheap[0]+minheap[0])/2.0;
    }else{
        return (double) maxheap[0];
    }
}

void runningMedian(int a_count, int* a, int* result_count, FILE* fptr) {
    /*
     * Write your code here.
     */
    *result_count = a_count;
    double* hasil = (double*)malloc(a_count*sizeof(double));
    for (int i=0; i<a_count; i++){
        insert(a[i]);
        hasil[i] = findMedian();
        fprintf(fptr, "%.1lf\n", hasil[i]);
        printf("%.1lf\n", hasil[i]);
    }
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
    runningMedian(a_count, a, &result_count, fptr);
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