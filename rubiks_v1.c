#include <stdio.h>
 
int main(void)
{
    int n, m, ini = 0;
    int i,j,k;
    scanf("%d%d", &n, &m);
    int cube[100][100][100];
    int temp[100][100] = {0};
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++){
                cube[i][j][k] = ini;
                ini++;
            }
    
    for(i = 0; i < m; i++)
    {
        int type, layer;
        int it, jt;
        scanf("%d%d", &type, &layer);
        if(type==0)
        {
            for(it = 0; it < n; it++)
                for(jt = 0; jt < n; jt++){
                    temp[jt][n-1-it] = cube[layer][it][jt];
                }
            for(it = 0; it < n; it++)
                for(jt = 0; jt < n; jt++){
                    cube[layer][it][jt] = temp[it][jt];
                }
        }else
        {
            for(it = 0; it < n; it++)
                for(jt = 0; jt < n; jt++){
                    temp[jt][n-1-it] = cube[it][jt][layer];
                }
            for(it = 0; it < n; it++)
                for(jt = 0; jt < n; jt++){
                    cube[it][jt][layer] = temp[it][jt];
                }
        }
    }
 
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < n; k++){
                    printf("%d ", cube[i][j][k]);
            }
            printf("\n");
        }
    }
 
    return 0;
}