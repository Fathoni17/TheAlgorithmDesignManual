#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAXN        10000
typedef struct node
{
    int y;
    struct node *next;
} node;

typedef struct graph
{
    node *edges[MAXN+1];
    node *last[MAXN+1];
    int degree[MAXN+1];
    int nvertices;
    int nedges;
    bool directed;
} graph;

void initialize_graph(graph *g, bool directed);
void pull_back(graph *g, int x, int y, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);
void print_graph(graph *g);
void dfs(graph *g, int start);

//////////////////////////////////////////////////////////
// Global Variable
int i, count = 1, min_global = 0xFFFFFFF;
bool checked[MAXN];
int result[MAXN];

int main(){
    graph g;
    initialize_graph(&g, FALSE);
    
    int ncity, nroad;
    scanf("%d %d", &ncity, &nroad);
    g.nvertices = ncity;
    while (nroad--){
        int x, y;
        scanf("%d %d", &x, &y);
        pull_back(&g, x, y, FALSE);
    }

    // City with fewest neighbor
    int tmp = 0xFFFFFFF;
    int min;
    for(i=1; i<=ncity; i++){
        if (tmp = tmp>g.degree[i]){
            tmp = g.degree[i];
            min = i;
        }
        checked[i]=FALSE;
    }

    checked[min]=TRUE;
    result[0] = min;
    dfs(&g, min);

    printf("%d", count);
    printf("\n%d", result[0]);
    for(int i=1;i<count;i++){
        printf(" %d", result[i]);
    }
    return 0;
}

void initialize_graph(graph *g, bool directed) {
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
    g -> directed = directed;

	for (i=0; i<MAXN; i++) {
        g->degree[i] = 0;
	    g->edges[i] = NULL;
        g->last[i] = NULL;
    }
}

void pull_back(graph *g, int x, int y, bool directed){
    node *p;			/* temporary pointer */

	p = malloc(sizeof(node));	/* allocate storage for edgenode */

	p->y = y;
	p->next = NULL;

	if (g->last[x] == NULL){
        g->edges[x] = p;
    } else 
        g->last[x]->next = p;
    g->last[x] = p;

	g->degree[x] ++;

	if (directed == FALSE) {
		pull_back(g,y,x,TRUE);
	} else
		g->nedges ++;
}

void insert_edge(graph *g, int x, int y, bool directed) {
	node *p;			/* temporary pointer */

	p = malloc(sizeof(node));	/* allocate storage for edgenode */

	p->y = y;
	p->next = g->edges[x];

	if (g->edges[x] == NULL){
        g->last[x] = p;
    }
	g->edges[x] = p;		/* insert at head of list */

	g->degree[x] ++;

	if (directed == FALSE) {
		insert_edge(g,y,x,TRUE);
	} else
		g->nedges ++;
}

void print_graph(graph *g){
	int i;				/* counter */
	node *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d",p->y);
			p = p->next;
		}
		printf("\n");
	}
}

void dfs(graph *g, int start){
    node *p;
    int y, tmp = 0xFFFFFFF, min=-1;

    p = g->edges[start];
    while (p!=NULL)
    {
        y = p->y;

        if (!checked[y]){
            // checking y;
            if (tmp>g->degree[y]){
                tmp=g->degree[y];
                min = y;
            }
        }

        p=p->next;
    }

    if (min>0){
        checked[min] = TRUE;
        result[count] = min;
        count++;
        dfs(g, min);   
    }
}