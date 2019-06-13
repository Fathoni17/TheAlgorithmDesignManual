#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// Bool Type
#define FALSE       0
#define TRUE        1
typedef int bool;

#define	MAXV		400		/* maximum number of vertices */
#define MAXDEGREE	400		/* maximum outdegree of a vertex */

#define MAXINT 0xfffffff

typedef struct {
        int weight[MAXV+1][MAXV+1];    	/* adjacency/weight info */
        int nvertices;                  /* number of vertices in the graph */
} adjacency_matrix;


void initialize_adjacency_matrix(adjacency_matrix *g)
{
	int i,j;			/* counters */

	g -> nvertices = 0;

	for (i=1; i<=MAXV; i++)
		for (j=1; j<=MAXV; j++)
			g->weight[i][j] = MAXINT;
}

void read_adjacency_matrix(adjacency_matrix *g, bool directed)
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x,y,w;			/* placeholder for edge and weight */

	initialize_adjacency_matrix(g);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d",&x,&y,&w);
		g->weight[x][y] = w;
		if (directed==FALSE) g->weight[y][x] = w;
	}
}

void print_adjacency_matrix(adjacency_matrix *g)
{
    int i,j;                        /* counters */

    for (i=1; i<=g->nvertices; i++) {
        printf("%3d: ",i);
        for (j=1; j<=g->nvertices; j++)
            printf("\t%10d",g->weight[i][j]);
        printf("\n");
    }
}

void floyd(adjacency_matrix *g)
{
	int i,j;			/* dimension counters */
	int k;				/* intermediate vertex counter */

	for (k=1; k<=g->nvertices; k++)
		for (i=1; i<=g->nvertices; i++)
			for (j=1; j<=g->nvertices; j++) {
				if (g->weight[i][j] > g->weight[i][k]+g->weight[k][j])
					g->weight[i][j] = g->weight[i][k]+g->weight[k][j];
			}
}

int main(){
    adjacency_matrix g;
	read_adjacency_matrix(&g,TRUE);

    // Before
	// print_adjacency_matrix(&g); printf("\n\n");

	floyd(&g);

    // After
	// print_adjacency_matrix(&g);

    int i;
    int queue;
    scanf("%d", &queue);
    for(i=0; i<queue; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        if (x == y)
            printf("0\n");
        else if (g.weight[x][y] == MAXINT)
            printf("-1\n");
        else
            printf("%d\n", g.weight[x][y]);
    }

    return 0;
}