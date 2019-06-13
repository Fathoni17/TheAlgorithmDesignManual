#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

///////////////////////////////////////////////////////////////
// Graph code 
#define MAXV        1000    /* Maximum number of vertices */
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
    int weight;         /* weight of edge (x,y) */

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d",&x,&y,&weight);
		insert_edge(g,x,y,weight,directed);
	}
}

void delete_edge(graph *g, int x, int y, bool directed) {
	int i;				/* counter */
	edgenode *p, *p_back;		/* temporary pointers */

	p = g->edges[x];
	p_back = NULL;

	while (p != NULL) 
		if (p->y == y) {
			g->degree[x] --;
			if (p_back != NULL) 
				p_back->next = p->next;
			else
				g->edges[x] = p->next;

			free(p);

			if (directed == FALSE)
				delete_edge(g,y,x,TRUE);
			else
				g->nedges --;

			return;
		}
		else
			p = p->next;

	printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

void print_graph(graph *g) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d(%d)",p->y,p->weight);
			p = p->next;
		}
		printf("\n");
	}
}

void find_path(int start, int end, int parents[]) {
	if ((start == end) || (end == -1))
		printf("\n%d",start);
	else {
		find_path(start,parents[end],parents);
		printf(" %d",end);
	}
}

///////////////////////////////////////////////////////////////
// Prim Algorithm Code
#define MAXINT	2147483647
void prim(graph *g, int start, int parent[], int distance[]) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */
	bool *intree = malloc(sizeof(int)*(g->nvertices+1));		/* is the vertex in the tree yet? */
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
			if ((distance[w] > weight) && (intree[w] == FALSE)) {
				distance[w] = weight;
				parent[w] = v;
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
}

int main() {
	graph g;
	int i;
    int start;

	read_graph(&g,FALSE);
    // print_graph(&g);
    int *parent = malloc(sizeof(int)*(g.nvertices+1));
	int *distance = malloc(sizeof(int)*(g.nvertices+1));		/* cost of adding to tree */

    scanf("%d", &start);
	prim(&g,start,parent,distance);

    // printf("Out of Prim\n");
    int count = 0;
    for (i=1; i<=g.nvertices; i++) {
    /*printf(" %d parent=%d\n",i,parent[i]);*/
        if (i!=start)
            count+=distance[i];
        // find_path(1,i,parent);
	}
    printf("%d\n", count);

}