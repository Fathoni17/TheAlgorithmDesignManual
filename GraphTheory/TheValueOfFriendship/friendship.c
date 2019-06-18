#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // for memset();

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

///////////////////////////////////////////////////////////////
// Graph code 
#define MAXV        1000    /* Maximum number of vertices */

typedef struct edgenode{
    unsigned y;                      /* Adjacency info */
    unsigned weight;                 /* edge weight, if any */
    struct edgenode *next;      /* next edge in list */
} edgenode;

typedef struct graph{
    edgenode *edges[MAXV+1];    /* Adjacency info */
    unsigned degree[MAXV+1];         /* outdegree of each vertex */
    unsigned nvertices;              /* number of vertices in graph */
    unsigned nedges;                 /* number of edges in graph */
    unsigned directed;              /* is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed);
void insert_edge(graph *g, unsigned x, unsigned y, bool directed);
void read_graph(graph *g, bool directed);
void print_graph(graph *g);

///////////////////////////////////////////////////////////////
// Queue code 
#define QUEUESIZE 1000
typedef unsigned item_type;

typedef struct {
        unsigned q[MAXV+1];	        /* body of queue */
        unsigned first;              /* position of first element */
        unsigned last;               /* position of last element */
        unsigned count;              /* number of queue elements */
} queue;

void init_queue(queue *q);
void enqueue(queue *q, item_type x);
item_type dequeue(queue *q);
item_type headq(queue *q);
unsigned empty_queue(queue *q);

///////////////////////////////////////////////////////////////
// BFS & DFS Code 
bool processed[MAXV+1];	/* which vertices have been processed */
bool discovered[MAXV+1];  /* which vertices have been found */
unsigned parent[MAXV+1];	/* discovery relation */

unsigned entry_time[MAXV+1];         /* time of vertex entry */
unsigned exit_time[MAXV+1];          /* time of vertex exit */
unsigned time;                       /* current event time */

bool finished = FALSE;	/* if true, cut off search immediately */

void initialize_search(graph *g);
void process_vertex_early();
void process_edge();
void process_vertex_late();
unsigned bfs(graph *g, unsigned start, unsigned list[], unsigned ntree);

///////////////////////////////////////////////////////////////
// Main Code
int main(){
    unsigned ngraph;
    scanf("%d", &ngraph);
    // int **res = (int**)malloc(sizeof(int*)*ngraph);
    // int *nres = (int*)malloc(sizeof(int)*ngraph);
    for (int i=0; i<ngraph; i++){
        graph g;
        read_graph(&g, FALSE);
            
    }
    // for (int i=0; i<ngraph; i++){
    //     for (int j=1; j<=nres[i]; j++){
    //         // if (j != res[i][0])
    //             printf("%d ", res[i][j]>0 ? res[i][j]+1:res[i][j]);
    //     }
    //     printf("\n");
    // }
    return 0;
}

///////////////////////////////////////////////////////////////
// Graph Code
void initialize_graph(graph *g, bool directed) {
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

    // memset(g->edges, 0, sizeof(g->edges));
    // memset(g->degree, 0, sizeof(g->degree));
	for (i=1; i<=MAXV; i++) {
        g->degree[i] = 0;
	    g->edges[i] = NULL;
    }
}

void insert_edge(graph *g, unsigned x, unsigned y, bool directed) {
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = 0;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;		/* insert at head of list */

	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE);
	else
		g->nedges ++;
}

void read_graph(graph *g, bool directed) {
	unsigned i;				/* counter */
	unsigned m;				/* number of edges */
	unsigned x, y;			/* vertices in edge (x,y) */
    int *list;
    unsigned nedge=0, total=0;
	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);
    list =  malloc((g->nvertices+1)*sizeof(unsigned));
        for (unsigned i=0; i<=g->nvertices; i++) list[i] = -1;
        // memset(list, -1, (g->nvertices+1)*sizeof(int));
	for (i=1; i<=m; i++) {
		scanf("%d %d",&x,&y);
        if (! (list[x] == list[y] && (list[x]>0 && list[y]>0)) ) {
    		insert_edge(g,x,y,directed);
            nedge++;
        }
    
        initialize_search(g);
        memset(list, -1, (g->nvertices+1)*sizeof(int));
        // for (unsigned i=0; i<=g->nvertices; i++) list[i] = -1;

        unsigned ntree = 1;
        for (unsigned k=1; k<=g->nvertices; k++)
            if (list[k]==-1){
                unsigned c = bfs(g, k, list, ntree);
                if (c>1)
                    total+=nedge*c;
                    printf("%lu\n", total);
                ntree++;
            }
	}
    // for(int i=1; i<=g->nvertices; i++){
    //     printf("%d ", list[i]);
    // }
    // printf("\n");
    // printf("%lu\n", total);
    // print_graph(g);
}

void print_graph(graph *g) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

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

///////////////////////////////////////////////////////////////
// Queue Code
void init_queue(queue *q) {
        q->first = 0;
        q->last = QUEUESIZE-1;
        q->count = 0;
}

void enqueue(queue *q, item_type x) {
    if (q->count >= QUEUESIZE)
    printf("Warning: queue overflow enqueue x=%d\n",x);
    else {
        q->last = (q->last+1) % QUEUESIZE;
        q->q[ q->last ] = x;    
        q->count = q->count + 1;
    }
}

item_type dequeue(queue *q) {
    item_type x;

    if (q->count <= 0) printf("Warning: empty queue dequeue.\n");
    else {
        x = q->q[ q->first ];
        q->first = (q->first+1) % QUEUESIZE;
        q->count = q->count - 1;
    }

    return(x);
}

item_type headq(queue *q) {
	return( q->q[ q->first ] );
}

unsigned empty_queue(queue *q) {
    if (q->count <= 0) return (TRUE);
    else return (FALSE);
}

///////////////////////////////////////////////////////////////
// BFS Code
void initialize_search(graph *g)
{
    int i;                          /* counter */

	time = 0;
    for (i=0; i<=g->nvertices; i++) {
        processed[i] = discovered[i] = FALSE;
        parent[i] = -1;
    }
}

unsigned bfs(graph *g, unsigned start, unsigned list[], unsigned ntree)
{
	queue q;			/* queue of vertices to visit */
	unsigned v;				/* current vertex */
	unsigned y;				/* successor vertex */
	edgenode *p;			/* temporary pointer */
    unsigned nvertex = 1;

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;

	while (empty_queue(&q) == FALSE) {
		v = dequeue(&q);
		// process_vertex_early(v);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
		    y = p->y;
		    if ((processed[y] == FALSE) || g->directed){
			    // process_edge(v,y);
                nvertex++;
                list[v] = ntree;
                list[y] = ntree;
            }    
		    if (discovered[y] == FALSE) {
                enqueue(&q,y);
                discovered[y] = TRUE;
                parent[y] = v;
            }
		    p = p->next;
		}
		// process_vertex_late(v);
	}

    return nvertex;
}