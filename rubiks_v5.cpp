#include <iostream>
#include <vector>

using namespace std;

typedef struct Cube {
    vector<vector<vector<int> > > arr;
} Cube;

Cube* new_cube(int n) {
    Cube *cube = new Cube();
    cube->arr.resize(n, vector<vector<int> >(n, vector<int>(n)));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                cube->arr[i][j][k] = i*n*n + j*n + k;
            }
        }
    }
    return cube;
}

void free_cube(Cube* cube) {
    delete cube;
}

void output_cube(Cube* cube) {
    for(int i = 0; i < cube->arr.size(); i++) {
        for(int j = 0; j < cube->arr[i].size(); j++) {
            for(int k = 0; k < cube->arr[i][j].size(); k++) {
                cout << cube->arr[i][j][k] << ' ';
            }
            cout << '\n';
        }
    }
}

int& get_node(Cube* cube, int type, int i, int j, int layer) {
    return type ? cube->arr[i][j][layer] : cube->arr[layer][i][j];
}

void rotate(Cube* cube, int layer, int type) {
    int n = cube->arr.size();
    vector<vector<int> > temp(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            temp[j][n-1-i] = get_node(cube, type, i, j, layer);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            get_node(cube, type, i, j, layer) = temp[i][j];
        }
    }
}
 
int main(void) {
    int n,m;
    cin >> n >> m;

    Cube *cube = new_cube(n);
    
    for(int i = 0; i < m; i++) {
        int type, layer;
        cin >> type >> layer;
        rotate(cube, layer, type);
    }

    output_cube(cube);
    free_cube(cube);
 
    return 0;
}