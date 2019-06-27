#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int bool;

bool cekPola(bool valid[2][10]);

int t, n;
int main(){
    char ch;
    scanf("%d", &t);
    while (t--) {
        int notValid = 0, nleft = 0, i=0;
        bool valid[2][10] = {0};
        scanf("%d", &n);
        scanf("%c", &ch);
        for (scanf("%c", &ch); i<n; i++,scanf("%c", &ch)){
            if (ch == '1'){
                notValid = !notValid;
                valid[0][i] = FALSE;
            }
            if (ch == '0') {
                valid[0][i] = TRUE;
            }
        }
        scanf("%c", &ch);
        for (i=0; i<n; i++,scanf("%c", &ch)){
            if (ch == '1'){
                notValid = !notValid;
                valid[1][i] = FALSE;
            }
            if (ch == '0') {
                valid[1][i] = TRUE;
            }
        }

        // for(int i=0;i<2;i++){
        //     for (int j=0; j<n; j++)
        //         printf("%2d ", valid[i][j]);
        //     printf("\n");
        // }

        if (notValid){
            printf("NO\n");
        } else {
            bool tmp = cekPola(valid);
            if (tmp){
                printf("NO\n");
            } else
                printf("YES\n", tmp);
        }
    }
        
    return 0;
}

bool cekPola(int valid[2][10]){
    int i;
    bool cnt = FALSE;
    for(i=0;i<n;i++)
    {   
        if(valid[0][i] && valid[1][i])
            continue;
        else if(!valid[0][i] && valid[1][i])
        {   
            cnt = !cnt;
            continue;
        }   
        else if(valid[0][i] && !valid[1][i])
        {   
            cnt = !cnt;
            if(i < n - 1 && !valid[0][i+1])
            {   
                if(cnt)
                    return TRUE;
            }   
            continue;
        }   
        else if(!valid[0][i] && !valid[1][i])
        {   
            if(cnt)
                return TRUE;
            continue;
        }   
    }   
    return cnt;
}
