#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;
//1993108504
//677609439     
//6359060
//3995010
///////////////////////////////////////////////////////////////
// Graph code 
#define MAXV        10000    /* Maximum number of vertices */
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

///////////////////////////////////////////////////////////////
// set_union Data Type Code
typedef struct {
        int p[MAXV+1]; 		/* parent element */
        int size[MAXV+1];           /* number of elements in subtree i */
	int n;				/* number of elements in set */
} set_union;

void set_union_init(set_union *s, int n) {
	int i;				/* counter */

	for (i=1; i<=n; i++) {
		s->p[i] = i;
		s->size[i] = 1;
	}
	
        s->n = n;
}

int find(set_union *s, int x) {
	if (s->p[x] == x)
		return(x);
	else
		return( find(s,s->p[x]) );
}

void union_sets(set_union *s, int s1, int s2) {
	int r1, r2;			/* roots of sets */

	r1 = find(s,s1);
	r2 = find(s,s2);

    // printf("s1=%d r1=%d s2=%d r2=%d\n",s1,r1,s2,r2);

	if (r1 == r2) return;		/* already in same set */

	if (s->size[r1] >= s->size[r2]) {
		s->size[r1] = s->size[r1] + s->size[r2];
		s->p[ r2 ] = r1;
	}
	else {
		s->size[r2] = s->size[r1] + s->size[r2];
                s->p[ r1 ] = r2;
	}
}

bool same_component(set_union *s, int s1, int s2) {
	return ( find(s,s1) == find(s,s2) );
}

void print_set_union(set_union *s) {
        int i;                          /* counter */

        for (i=1; i<=s->n; i++)
                printf("%i  set=%d size=%d \n",i,s->p[i],s->size[i]);

        printf("\n");
}

///////////////////////////////////////////////////////////////
// Kruskal Algorithm Code
#define MAXINT	2147483647
typedef struct edge_pair{
        int x, y;                       /* adjacency info */
        int weight;                     /* edge weight, if any */
} edge_pair;

void to_edge_array(graph *g, edge_pair e[]) {
	int i,m;			/* counters */
	edgenode *p;			/* temporary pointer */

	m = 0;
    for (i=1; i<=g->nvertices; i++) {
        p = g->edges[i];
        while (p != NULL) {
            if (p->y > i) {
                e[m].x = i;
                e[m].y = p->y;
                e[m].weight = p->weight;
                m = m+1;
            }
            p = p->next;
        }
    }
}

bool weight_compare(edge_pair *x, edge_pair *y) {
	if (x->weight < y->weight) return(-1);
	if (x->weight > y->weight) return(1);
	return(0);
}

void kruskal(graph *g, int distance[], int *count) {
	int i;				/* counter */
	set_union s;			/* set union data structure */
	bool weight_compare();
    edge_pair /*e[MAXV+1];*/ *e = malloc(sizeof(edge_pair)*(g->nedges+1));
	set_union_init(&s, g->nvertices);

    // printf("initialized set union\n");
	to_edge_array(g, e);
	qsort(e,g->nedges,sizeof(edge_pair),weight_compare);

	for (i=0; i<(g->nedges); i++) {
		// print_set_union(&s);
		if (!same_component(&s,e[i].x,e[i].y)) {
			// printf("edge (%d,%d) of weight %d in MST\n",e[i].x,e[i].y,e[i].weight);
			union_sets(&s,e[i].x,e[i].y);
            distance[i] = e[i].weight;
            *count += distance[i];
            // printf("%d %d %d\n", i, *count, distance[i]);
		}
	}
}

int main() {
	graph g;
	int i;
    int count = 0;
	read_graph(&g,FALSE);
    // print_graph(&g);
	int *distance = (int*)calloc((g.nedges+1), sizeof(int));		/* cost of adding to tree */
    for (int j=0; j<=g.nedges; j++) distance[j] = 0;
    kruskal(&g,distance,&count);

    // // printf("Out of Prim\n");
    // i = 0;
    // int n = 0;
    // while (n<countn)
    // {
    //     if (distance[i] != 0){
    //         count+=distance[i];
    //         // printf("%d %d/%d-> %d %d\n", i, n, countn, count, distance[i]);
    //         n++;
    //     }
    //     i++;
    // }
    
    printf("%d", count);

}