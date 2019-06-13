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

void insert_edge(graph *g, int x, int y, bool directed) {
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
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y;			/* vertices in edge (x,y) */

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,directed);
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
			printf(" %d",p->y);
			p = p->next;
		}
		printf("\n");
	}
}

///////////////////////////////////////////////////////////////
// Queue code 
#define QUEUESIZE 1000
typedef int item_type;

typedef struct {
        int q[MAXV+1];	        /* body of queue */
        int first;              /* position of first element */
        int last;               /* position of last element */
        int count;              /* number of queue elements */
} queue;

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

int empty_queue(queue *q) {
        if (q->count <= 0) return (TRUE);
        else return (FALSE);
}

void print_queue(queue *q) {
        int i,j;

        i=q->first; 
        
        while (i != q->last) {
                printf("%d ",q->q[i]);
                i = (i+1) % QUEUESIZE;
        }

        printf("%2d ",q->q[i]);
        printf("\n");
}

///////////////////////////////////////////////////////////////
// BFS & DFS Code 
bool processed[MAXV+1];	/* which vertices have been processed */
bool discovered[MAXV+1];  /* which vertices have been found */
int parent[MAXV+1];	/* discovery relation */

int entry_time[MAXV+1];         /* time of vertex entry */
int exit_time[MAXV+1];          /* time of vertex exit */
int time;                       /* current event time */

bool finished = FALSE;	/* if true, cut off search immediately */

void initialize_search(graph *g) {
        int i;                          /* counter */

	time = 0;

        for (i=0; i<=g->nvertices; i++) {
                processed[i] = discovered[i] = FALSE;
                parent[i] = -1;
        }
}
void process_vertex_early(int v){
}
void process_edge(int v, int y){
}
void process_vertex_late(int v){
}

void bfs(graph *g, int start, int x, int **res) {
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int y;				/* successor vertex */
	edgenode *p;			/* temporary pointer */

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;
    int *done = malloc(sizeof(int)*(g->nvertices+1));
    for (int i=1; i<=g->nvertices; i++) {res[x][i] = -1; done[i] = 0;}
    int count = 0;
	while (empty_queue(&q) == FALSE) {
		v = dequeue(&q);
		//process_vertex_early(v);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
		    y = p->y;
		    if ((processed[y] == FALSE) || g->directed)
			    //process_edge(v,y);
                if (!done[y])
                    if (y != start) {
                        if (v != start)
                            res[x][y] += (6+res[x][v]+1);
                        else
                            res[x][y] += 6;
                        done[y] = TRUE;
                    }
		    if (discovered[y] == FALSE) {
			    enqueue(&q,y);
			    discovered[y] = TRUE;
			    parent[y] = v;
		    }
		    p = p->next;
		}
		//process_vertex_late(v);
	}
}

int edge_classification(int x, int y) {
        if (parent[y] == x) return(TREE);
        if (discovered[y] && !processed[y]) return(BACK);
        if (processed[y] && (entry_time[y]>entry_time[x])) return(FORWARD);
        if (processed[y] && (entry_time[y]<entry_time[x])) return(CROSS);

        printf("Warning: self loop (%d,%d)\n",x,y);
}

void dfs(graph *g, int v) {
	edgenode *p;			/* temporary pointer */
	int y;				/* successor vertex */
    int count;
	if (finished) return;		/* allow for search termination */

	discovered[v] = TRUE;
        time = time + 1;
        entry_time[v] = time;
        /*printf("entered vertex %d at time %d\n",v, entry_time[v]);*/

	process_vertex_early(v);

	p = g->edges[v];
	while (p != NULL) {
		y = p->y;
		if (discovered[y] == FALSE) {
			parent[y] = v;
			process_edge(v,y);
			dfs(g,y);
		} 
		else if ((!processed[y]) || (g->directed))
			process_edge(v,y);

		if (finished) return;

		p = p->next;
	}

	process_vertex_late(v);

        time = time + 1;
        exit_time[v] = time;
        /*printf("exit vertex %d at time %d\n",v, exit_time[v]);*/

	processed[v] = TRUE;
}

int main(){
    int ngraph;
    scanf("%d", &ngraph);
    int **res = (int**)malloc(sizeof(int*)*ngraph);
    int *nres = (int*)malloc(sizeof(int)*ngraph);
    for (int i=0; i<ngraph; i++){
        graph g;
        read_graph(&g, FALSE);

        int start;
        scanf("%d", &start);
        nres[i] = g.nvertices;
        *(res+i) = malloc(sizeof(int)*(g.nvertices+1));
        res[i][0] = start;
        initialize_search(&g);
        // print_graph(&g);
        bfs(&g, start, i, res);
    }
    for (int i=0; i<ngraph; i++){
        for (int j=1; j<=nres[i]; j++){
            if (j != res[i][0])
                printf("%d ", res[i][j]>0 ? res[i][j]+1:res[i][j]);
        }
        printf("\n");
    }
    return 0;
}