#include <stdio.h>

void init_cube(int cube[100][100][100], int n) {
    int ini = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++){
                cube[i][j][k] = ini;
                ini++;
            }
        }
    }
}

void output_cube(int cube[100][100][100], int n) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                    printf("%d ", cube[i][j][k]);
            }
            printf("\n");
        }
    }
}

void green_rotation(int cube[100][100][100], int n, int layer) {
    int it,jt;
    int temp[100][100];
    for(it = 0; it < n; it++) {
        for(jt = 0; jt < n; jt++){
            temp[jt][n-1-it] = cube[layer][it][jt];
        }
    }
    for(it = 0; it < n; it++) {
        for(jt = 0; jt < n; jt++){
            cube[layer][it][jt] = temp[it][jt];
        }
    }
}

void blue_rotation(int cube[100][100][100], int n, int layer) {
    int it,jt;
    int temp[100][100];
    for(it = 0; it < n; it++) {
        for(jt = 0; jt < n; jt++){
            temp[jt][n-1-it] = cube[it][jt][layer];
        }
    }
    for(it = 0; it < n; it++) {
        for(jt = 0; jt < n; jt++){
            cube[it][jt][layer] = temp[it][jt];
        }
    }
}
 
int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    int cube[100][100][100];
    int temp[100][100] = {0};

    init_cube(cube, n);
    
    for(int i = 0; i < m; i++) {
        int type, layer;
        scanf("%d%d", &type, &layer);
        if(type==0) {
            green_rotation(cube, n, layer);
        } else {
            blue_rotation(cube, n, layer);
        }
    }

    output_cube(cube, n);
 
    return 0;
}