#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset()

///////////////////////////////////////////////////////////////
// Bool Simple Typedef
#define FALSE 0
#define TRUE 1
typedef int bool;

///////////////////////////////////////////////////////////////
// Graph Code
#define MAXV        1000    /* Maximum number of vertices */
#define MAXINT      0xFFFFFFF

typedef struct edgenode{
    int y;                      /* Adjacency info */
    int weight;                 /* edge weight, if any */
    struct edgenode *next;      /* next edge in list */
} edgenode;

typedef struct graph{
    edgenode *edges[MAXV];    /* Adjacency info */
    int degree[MAXV];         /* outdegree of each vertex */
    int nvertices;              /* number of vertices in graph */
    int nedges;                 /* number of edges in graph */
    int directed;               /* is the graph directed? */
} graph;

bool visited[MAXV];
int vi[MAXV], match[MAXV]; 

void initialize_graph(graph *g, bool directed);
void pull_back(graph *g, int x, int y, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);
bool find(graph *g, int x);

int main(){
    int ncase;
    scanf("%d", &ncase);

    while (ncase--){
        int n, k;
        scanf("%d %d",&n,&k);

        int i=0;
        char ch;
        while (scanf("%d%c", &vi[i], &ch) >= 1) {
            // printf("%d ", vi[i]);
            match[i] = -1;

            if (ch != ' '){
                break;
            }
            i++;    
        }

        graph g;
        initialize_graph(&g, TRUE);
        g.nvertices = n;

        for (int i=0; i<n; i++){
            for (int j=i+1;j<n;j++){
                if (abs(vi[i]-vi[j]) >= k)
                    pull_back(&g, i, j, TRUE);
            }
        }

        int res = 0;
        for (int i=0; i<n; i++){
            memset(visited, FALSE, sizeof(bool)*MAXV);
            res += find(&g, i);
        }
        printf("%d\n", n-res);
    }

    return 0;
}


void initialize_graph(graph *g, bool directed) {
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

	for (i=0; i<MAXV; i++) {
        g->degree[i] = 0;
	    g->edges[i] = NULL;
    }
}

void pull_back(graph *g, int x, int y, bool directed){
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = 0;
	p->y = y;
	p->next = NULL;

	// g->edges[x] = p;		/* insert at head of list */
    edgenode *q = g->edges[x];
    if (g->edges[x] == NULL){
        g->edges[x] = p;
    }else{
        for (;q->next != NULL; q=q->next){}
        q->next = p;
    }

	g->degree[x] ++;

	if (directed == FALSE) {
		pull_back(g,y,x,TRUE);
	} else
		g->nedges ++;
}

void insert_edge(graph *g, int x, int y, bool directed) {
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = 0;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;		/* insert at head of list */

	g->degree[x] ++;

	if (directed == FALSE) {
		insert_edge(g,y,x,TRUE);
	} else
		g->nedges ++;
}

bool find(graph *g, int x){
    edgenode *p = g->edges[x];
    int y;
    for (int i=0; i<g->degree[x]; i++){
        y  = p->y;
        if (!visited[y]){
            visited[y] = TRUE;
            if(match[y] == -1 || find(g, match[y])){
                match[y]=x;
                return TRUE;
            }
        }
        p = p->next;
    }
    return FALSE;
}