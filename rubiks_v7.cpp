#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

class Cube {
public:
    Cube(int n) {
        sz = n;
        arr.resize(n, vector<vector<int> >(n, vector<int>(n)));
        a = ranges::iota_view{0,n};
        for (auto const& [i,j,k] : ranges::cartesian_product_view(a,a,a)) {
            arr[i][j][k] = i*n*n + j*n + k;
        }
    }
    ~Cube() {}

    void output_cube() {
        for (auto const& [i,j,k] : ranges::cartesian_product_view(a,a,a)) {
            cout << arr[i][j][k] << " \n"[k==sz-1];
        }
    }

    void rotate(int layer, int type) {
        vector<vector<int> > temp(sz, vector<int>(sz));
        for (auto const& [i,j] : ranges::cartesian_product_view(a,a)) {
            temp[j][sz-1-i] = get_node(type, i, j, layer);
        }
        for (auto const& [i,j] : ranges::cartesian_product_view(a,a)) {
            get_node(type, i, j, layer) = temp[i][j];
        }
    }

private:
    vector<vector<vector<int> > > arr;
    int sz;
    std::ranges::iota_view<int, int> a;
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