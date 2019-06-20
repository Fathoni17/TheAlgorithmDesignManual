#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

///////////////////////////////////////////////////////////////
// Graph code 
#define MAXV        100500    /* Maximum number of vertices */

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

void initialize_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, int weight, bool directed);
void read_graph(graph *g, bool directed);
void print_graph(graph *g);

///////////////////////////////////////////////////////////////
// Djikstra Code 
#define MAXINT 0xfffffff
int parent[MAXV+1];	/* discovery relation */

int dijkstra(graph *g, int start);
void find_path(int start, int end, int parents[]);

int main(){
    int i;
    graph g;
    int start;
    
    read_graph(&g, FALSE);
    // print_graph(&g);

    int tmp = 0xFFFFFFF;
    for(i=1; i<=g.nvertices; i++){
        if (tmp = tmp>g.degree[i]){
            tmp = g.degree[i];
            start = i;
        }
    }

    int end_c = dijkstra(&g, start);

    find_path(start, end_c, parent);

    return 0;
}

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
    int weight = -1;    /* -1 uniform for get the longest distance*/

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d",&x,&y);
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

int dijkstra(graph *g, int start){		/* WAS prim(g,start) */
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
	}

	distance[start] = 0;
	v = start;

	while (intree[v] == FALSE) {
		intree[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
			w = p->y;
			weight = p->weight;
            if (!intree[w]){
/* CHANGED */		if (distance[w] > (distance[v]+weight)) {
/* CHANGED */			distance[w] = distance[v]+weight;
/* CHANGED */			parent[w] = v;
            }
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
    int tmp = 1, min;
	for (i=1; i<=g->nvertices; i++) {
		if (i!=start)
			if (distance[i] == MAXINT){
				// printf("-1 ");
			} else {
				// printf("%d ",distance[i]); //*/
                if (tmp>distance[i]){
                    tmp = distance[i];
                    min = i;
                }
            }
	}	
	// printf("\n");
    printf("%d", -1*tmp + 1);
    return min;
}

void find_path(int start, int end, int parents[]) {
	if ((start == end) || (end == -1))
		printf("\n%d",start);
	else {
		find_path(start,parents[end],parents);
		printf(" %d",end);
	}
}