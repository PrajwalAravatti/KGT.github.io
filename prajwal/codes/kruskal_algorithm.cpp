#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;
};

void unionSets(vector<int> &arr, int n, int u, int v) {
    int temp = arr[u];
    for (int i = 0; i < n; i++) {
        if (arr[i] == temp) {
            arr[i] = arr[v];
        }
    }
}

int findSet(vector<int> &arr, int u, int v) {
    return arr[u] == arr[v];
}

void mergeVectors(vector<Edge> &B, vector<Edge> &C, vector<Edge> &A) {
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;

    while (i < p && j < q) {
        if (B[i].weight <= C[j].weight) {
            A[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            j++;
        }
        k++;
    }
    while (i < p) {
        A[k] = B[i];
        i++;
        k++;
    }
    while (j < q) {
        A[k] = C[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Edge> &A) {
    int n = A.size();
    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    vector<Edge> B(A.begin(), A.begin() + mid);
    vector<Edge> C(A.begin() + mid, A.end());

    mergeSort(B);
    mergeSort(C);

    mergeVectors(B, C, A);
}

vector<Edge> kruskalMST(vector<Edge> &edges, vector<int> &arr, int n) {
    vector<Edge> mst;
    int n1 = edges.size();
    for (int i = 0; i < n1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (!findSet(arr, u, v)) {
            mst.push_back(edges[i]);
            unionSets(arr, n, u, v);
        }
    }
    return mst;
}

int main() {
    vector<string> locations = {"Water Source 0", "Reservoir 1", "Reservoir 2", "Reservoir 3", "Reservoir 4", "Reservoir 5", "Reservoir 6", "Reservoir 7"};
    vector<vector<int>> graph = {
        {0, 105, 65, 80, 0, 0, 0, 0},
        {105, 0, 45, 0, 0, 40, 0, 100},
        {65, 45, 0, 50, 60, 30, 0, 0},
        {80, 0, 50, 0, 40, 28, 0, 0},
        {0, 0, 60, 40, 0, 0, 70, 0},
        {0, 35, 30, 0, 0, 0, 55, 40},
        {0, 0, 0, 0, 70, 55, 0, 90},
        {0, 100, 0, 0, 0, 40, 90, 0},
    };

    vector<Edge> edges;
    int n = graph.size();

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0) {
                edges.push_back(Edge{i, j, graph[i][j]});
            }
        }
    }

    mergeSort(edges);

    vector<Edge> mst = kruskalMST(edges, arr, n);

    cout << "\nEdges and their weights:\n";
    int n2 = edges.size();
    for (int i = 0; i < n2; i++) {
        cout << "(" << locations[edges[i].u] << ", " << locations[edges[i].v] << ") --> " << edges[i].weight << "\n";
    }

    cout << "\nEdges in the MST:\n";
    int m = mst.size();
    int totalCost = 0;
    for (int i = 0; i < m; i++) {
        cout << "(" << locations[mst[i].u] << ", " << locations[mst[i].v] << ") --> " << mst[i].weight << "\n";
        totalCost += mst[i].weight;
    }

    cout << "\nMinimum Cost of the MST: " << totalCost << "\n";

    return 0;
}
