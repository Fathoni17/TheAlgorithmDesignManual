#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset()

#define min(A,B) A>B ? B:A
#define MAXV 100005
const long long INF = 1LL << 55;
#define TRUE 1
#define FALSE 0
typedef int bool;

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
    int directed;              /* is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, int weight, bool directed);
void print_graph(graph *g);
void initialize_search(graph *g);
int edge_classification(int x, int y);
void dfs(graph *g, int v, int fa);

int N,K;
bool robot[MAXV];
long long dp[MAXV][2];

int main(){
    graph g;
    initialize_graph(&g, FALSE);

    scanf("%d %d", &N, &K);
    // read graph
    g.nvertices = N;

    for (int i=1; i<N; i++){
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        insert_edge(&g, x,y,w, FALSE);
    }
    // print_graph(&g);
    memset(robot, FALSE, sizeof(robot));
    for (int i = 0; i < K; i++) {
        int x;
        scanf("%d", &x);
        robot[x] = TRUE;
    }    

    dfs(&g,0,-1);

    long long result = min(dp[0][0], dp[0][1]);

    printf("%lld\n", result);

    return 0;
}

void initialize_graph(graph *g, bool directed) {
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

	for (i=0; i<MAXV; i++) { // edited -> 0 base
        g->degree[i] = 0;
	    g->edges[i] = NULL;
    }
}

void insert_edge(graph *g, int x, int y, int weight, bool directed) {
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = weight;
	p->y = y;
	p->next = g->edges[x]; /*
    p->next = NULL; //*/

	g->edges[x] = p;		/* insert at head of list 
    if (g->edges[x] == NULL){
        g->edges[x] = p;
    } else {
        edgenode *q = g->edges[x];
        for (;q->next!=NULL;q = q->next){}
        q->next = p;
    } //*/

	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,weight,TRUE);
	else
		g->nedges ++;
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

void dfs(graph *g, int u, int fa)
{
	edgenode *p;			/* temporary pointer */
	int v;				/* successor vertex */
    int w;
    long long cek;

    dp[u][1] = 0;
    if (robot[u] == TRUE)
        cek = INF;
    else 
        cek = 0;
    dp[u][0] = cek;

    p = g->edges[u];
	for (int i=0; i<g->degree[u]; i++){
    	v = p->y;
        w = p->weight;

        if (v != fa) {
            dfs(g,v,u);
            dp[u][1] += min(dp[v][0], dp[v][1] + w);
            dp[u][1] = min(dp[u][1], dp[u][0] + dp[v][1]);

            if (!robot[u])
                dp[u][0] += min(dp[v][0], dp[v][1] + w);

            // printf("%d: %lld %lld\n", u, dp[u][1], dp[u][0]);
            
        }
        p = p->next;
	}
}