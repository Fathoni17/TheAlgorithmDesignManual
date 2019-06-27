#include <stdio.h>

#define M 1900

int best[M][M];
int nPeople[M][M];
int mb[M];

int main()
{
	int N, H, I;
    int nfloor, flr, bld;
    int i; 
	scanf("%d %d %d", &N, &H, &I);
	for (bld = 0; bld < N; ++bld) {
		for (i = 0,scanf("%d", &nfloor); i < nfloor; ++i) {
			scanf("%d", &flr);
			++nPeople[bld][flr-1];
		}
	}                                        

	for (flr = H - 1; flr >= 0; --flr) {
		int tmp = 0;
		for (bld = 0; bld < N; ++bld) {
			int r = nPeople[bld][flr];
			if (flr+1 < H) {
				int s = best[bld][flr+1];
				if (flr+I < H && s < mb[flr+I]) s = mb[flr+I];
				r += s;
			}
			best[bld][flr] = r;
			if (tmp < r) tmp = r;
		}
		mb[flr] = tmp;
	}

	printf("%d\n", mb[0]);
	return 0;
}