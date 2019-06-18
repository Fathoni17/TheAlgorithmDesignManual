#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

#define MAXV        100    /* Maximum number of vertices */

typedef struct edgenode{
    unsigned vid;                      /* Adjacency info /edited */
    // unsigned weight;                 /* edge weight, if any */
    struct edgenode *next;      /* next edge in list */
} edgenode;

void insert_edge(edgenode **head, int vertex_idx);
int comp(const void *a, const void *b) {return (*(int*)b-*(int*)a);}

int main(){
    int q, i;
    scanf("%d", &q);
    while(q--){
        long *grup_cnt;
        int *grup_idx;
        edgenode **friend_list;
        int next_grup = 1;
        long total;

        int n, m;
        scanf("%d %d", &n, &m);
        // allocation
        grup_cnt= calloc(((n/2)+1),sizeof(long));
        grup_idx= calloc(n+1, sizeof(int));
        friend_list = calloc((n/2)+1,sizeof(edgenode *));

        for (i=1;i++<=m;){
            int x, y;
            scanf("%d %d", &x, &y);

            if (grup_idx[x] == 0 && grup_idx[y] == 0){
                // New Group
                grup_idx[y] = grup_idx[x] = next_grup;
                grup_cnt[next_grup] = 2;
                insert_edge(friend_list+next_grup, x);
                insert_edge(friend_list+next_grup, y);
                next_grup++;
            } else if (grup_idx[x] == 0 || grup_idx[y] == 0){
                if (grup_idx[x] == 0) {
                    /* add x to y's group */
                    grup_idx[x] = grup_idx[y];
                    insert_edge(friend_list + grup_idx[y], x);
                } else {
                    /* add y to x's group */
                    grup_idx[y] = grup_idx[x];
                    insert_edge(friend_list + grup_idx[x], y);
                }

                grup_cnt[grup_idx[y]]++;
            } else if (grup_idx[x] != grup_idx[y]){
                edgenode *prev, *curr;
                int idxy = grup_idx[y];

                prev = NULL; curr = friend_list[grup_idx[y]];
                while (curr!=NULL)
                {
                    grup_idx[curr->vid] = grup_idx[x];
                    grup_cnt[grup_idx[x]]++;
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = friend_list[grup_idx[x]];
                friend_list[grup_idx[x]] = friend_list[idxy];
                friend_list[idxy] = NULL;
                grup_cnt[idxy] = 0;
            }
        }

        qsort(grup_cnt, (n/2)+1, sizeof(long), &comp);

        for (i=0, total=0; i<=n/2; i++){
            long c = grup_cnt[i];
            if (c == 0){
                break;
            }

            m-= (c-1);
            total += (((c - 1) * c * ((3 * m) + c + 1)) / 3);
        }
        printf("%ld\n", total);
        free(grup_idx);
        for(i=1;i<=n/2;i++){
            edgenode *curr, *del;
            curr = friend_list[i];
            while (curr!=NULL)
            {
                del = curr;
                curr = curr->next;
                free(del);
            }
        }
        free(grup_cnt);
        free(friend_list);
    }

    return 0;
}

void insert_edge(edgenode **head, int vertex_idx){
    edgenode *new = malloc(sizeof(edgenode));
    new->vid = vertex_idx;
    new->next = *head;
    *head = new;
}
