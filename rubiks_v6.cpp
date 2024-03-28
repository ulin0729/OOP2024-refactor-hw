#include <iostream>
#include <vector>

using namespace std;

class Cube {
public:
    Cube(int n) {
        arr.resize(n, vector<vector<int> >(n, vector<int>(n)));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    arr[i][j][k] = i*n*n + j*n + k;
                }
            }
        }
    }
    ~Cube() {}

    void output_cube() {
        for(int i = 0; i < arr.size(); i++) {
            for(int j = 0; j < arr[i].size(); j++) {
                for(int k = 0; k < arr[i][j].size(); k++) {
                    cout << arr[i][j][k] << ' ';
                }
                cout << '\n';
            }
        }
    }

    void rotate(int layer, int type) {
        int n = this->arr.size();
        vector<vector<int> > temp(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                temp[j][n-1-i] = get_node(type, i, j, layer);
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                get_node(type, i, j, layer) = temp[i][j];
            }
        }
    }

private:
    vector<vector<vector<int> > > arr;
    int &get_node(int type, int i, int j, int layer) {
        return type ? this->arr[i][j][layer] : this->arr[layer][i][j];
    }
};


 
int main(void) {
    int n, m;
    cin >> n >> m;

    Cube cube(n);
    
    for(int i = 0; i < m; i++) {
        int type, layer;
        cin >> type >> layer;
        cube.rotate(layer, type);
    }

    cube.output_cube();
 
    return 0;
}