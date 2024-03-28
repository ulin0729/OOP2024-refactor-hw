#include <stdio.h>
#include <stdlib.h>

typedef struct Cube {
    int ***arr;
    int size;
} Cube;

Cube* new_cube(int n) {
    Cube *cube = (Cube*)malloc(sizeof(Cube));
    cube->size = n;
    cube->arr = (int***)malloc(n * sizeof(int**));
    for(int i = 0; i < n; i++) {
        cube->arr[i] = (int**)malloc(n * sizeof(int*));
        for(int j = 0; j < n; j++) {
            cube->arr[i][j] = (int*)malloc(n * sizeof(int));
            for(int k = 0; k < n; k++) {
                cube->arr[i][j][k] = i * n * n + j * n + k;
            }
        }
    }
    return cube;
}

void free_cube(Cube* cube) {
    for(int i = 0; i < cube->size; i++) {
        for(int j = 0; j < cube->size; j++) {
            free(cube->arr[i][j]);
        }
        free(cube->arr[i]);
    }
    free(cube->arr);
    free(cube);
}

void output_cube(Cube* cube) {
    for(int i = 0; i < cube->size; i++) {
        for(int j = 0; j < cube->size; j++) {
            for(int k = 0; k < cube->size; k++) {
                printf("%d ", cube->arr[i][j][k]);
            }
            printf("\n");
        }
    }
}

void green_rotation(Cube* cube, int layer) {
    int n = cube->size;
    int **temp = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        temp[i] = (int*)malloc(n * sizeof(int));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            temp[j][n-1-i] = cube->arr[layer][i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cube->arr[layer][i][j] = temp[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);
}

void blue_rotation(Cube* cube, int layer) {
    int n = cube->size;
    int **temp = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        temp[i] = (int*)malloc(n * sizeof(int));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            temp[j][n-1-i] = cube->arr[i][j][layer];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cube->arr[i][j][layer] = temp[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);
}
 
int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);

    Cube *cube = new_cube(n);
    
    for(int i = 0; i < m; i++) {
        int type, layer;
        scanf("%d%d", &type, &layer);
        if(type==0) {
            green_rotation(cube, layer);
        } else {
            blue_rotation(cube, layer);
        }
    }

    output_cube(cube);
    free_cube(cube);
 
    return 0;
}