#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

///////////////////////////////////////////////////////////////
// Graph code 
#define MAXV        100000    /* Maximum number of vertices */
#define TREE		0		/* tree edge */
#define BACK		1		/* back edge */
#define CROSS		2		/* cross edge */
#define FORWARD		3		/* forward edge */

typedef struct edgenode{
    int y;                      /* Adjacency info */
    int weight;                 /* edge weight, if any */
    struct edgenode *next;      /* next edge in list */
} edgenode;

typedef struct graph{
    edgenode *edges[MAXV+1];    /* Adjacency info */
    int degree[MAXV+1];         /* outdegree of each vertex */
    int nvertices;              /* number of vertices in graph */
    int nedges;                 /* number of edges in graph */
    int directed;              /* is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed) {
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

	for (i=1; i<=MAXV; i++) {
        g->degree[i] = 0;
	    g->edges[i] = NULL;
    }
}

void insert_edge(graph *g, int x, int y, int weight, bool directed) {
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = weight;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;		/* insert at head of list */

	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,weight,TRUE);
	else
		g->nedges ++;
}

void read_graph(graph *g, bool directed) {
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y;			/* vertices in edge (x,y) */
    int weight;

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d",&x,&y,&weight);
		insert_edge(g,x,y,weight,directed);
	}
}

void print_graph(graph *g) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d(%d)",p->y, p->weight);
			p = p->next;
		}
		printf("\n");
	}
}

///////////////////////////////////////////////////////////////
// Djikstra Code 
#define MAXINT 0xfffffff
bool processed[MAXV+1];	/* which vertices have been processed */
bool discovered[MAXV+1];  /* which vertices have been found */
int parent[MAXV+1];	/* discovery relation */

bool finished = FALSE;	/* if true, cut off search immediately */

void initialize_search(graph *g) {
    int i;                          /* counter */

    for (i=0; i<=g->nvertices; i++) {
        processed[i] = FALSE; discovered[i] = FALSE;
        parent[i] = -1;
    }
}

void dijkstra(graph *g, int start){		/* WAS prim(g,start) */
	int i;				/* counter */
	edgenode *p;                    /* temporary pointer */
	bool *intree = malloc(sizeof(int)*(g->nvertices+1));		/* is the vertex in the tree yet? */
	int distance[MAXV+1];		/* distance vertex is from start */
	int v;				/* current vertex to process */
	int w;				/* candidate next vertex */
	int weight;			/* edge weight */
	int dist;			/* best current distance from start */

	for (i=1; i<=g->nvertices; i++) {
		intree[i] = FALSE;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	while (intree[v] == FALSE) {
		intree[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
			w = p->y;
			weight = p->weight;
/* CHANGED */		if (distance[w] > (distance[v]+weight)) {
/* CHANGED */			distance[w] = distance[v]+weight;
/* CHANGED */			parent[w] = v;
			}
			p = p->next;
		}

		v = 1;
		dist = MAXINT;
		for (i=1; i<=g->nvertices; i++) 
			if ((intree[i] == FALSE) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	}
	for (i=1; i<=g->nvertices; i++) {
		if (i!=start)
			if (distance[i] == MAXINT)
				printf("-1 ");
			else
				printf("%d ",distance[i]); //*/
	}	
	printf("\n");
}

int main(){
    int i;
    int ntest;
    scanf("%d", &ntest);
    graph g;
    int start;
    int **result = malloc(ntest*sizeof(int*));
    int *nres = (int*)malloc(sizeof(int)*ntest);

    i = 0;
    while (i<ntest)
    {
        read_graph(&g, FALSE);
        // print_graph(&g);
        scanf("%d", &start);
        *(result+i) = malloc((g.nvertices+1)*sizeof(int));
        result[i][0] = start;
        nres[i] = g.nvertices;
        initialize_search(&g);
        dijkstra(&g, start);
        i++;
    }

    // for (int i=0; i<ntest; i++){
    //     for (int j=1; j<=nres[i]; j++){
    //         if (j != result[i][0])
    //             printf("%d ", result[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}