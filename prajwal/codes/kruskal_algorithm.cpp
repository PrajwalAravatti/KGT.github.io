#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int u, v, weight;
};
void Union1(vector<int> &arr, int n, int u, int v) {
    int temp = arr[u];
    for (int i = 0; i < n; i++) {
        if (arr[i] == temp) {
            arr[i] = arr[v];
        }
    }
}
int find1(vector<int> &arr, int u, int v) {
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
        if (!find1(arr, u, v)) {
            mst.push_back(edges[i]);
            Union1(arr, n, u, v);
        }
    }
    return mst;
}

int main() {
    vector<vector<int>> graph = {
        {0, 8, 0, 0, 0, 0, 0, 16, 0},
        {8, 0, 16, 0, 0, 0, 0, 22, 0},
        {0, 16, 0, 14, 0, 8, 0, 0, 4},
        {0, 0, 14, 0, 18, 28, 0, 0, 0},
        {0, 0, 0, 18, 0, 20, 0, 0, 0},
        {0, 0, 8, 0, 20, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 12, 0, 2, 12},
        {16, 22, 0, 0, 0, 0, 2, 0, 14},
        {0, 0, 4, 0, 0, 0, 12, 14, 0}
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
        cout << "(" << edges[i].u << ", " << edges[i].v << ") --> " << edges[i].weight << "\n";
    }

    cout << "\nEdges in the MST:\n";
    int m = mst.size();
    int totalCost = 0;
    for (int i = 0; i < m; i++) {
        cout << "(" << mst[i].u << ", " << mst[i].v << ") --> " << mst[i].weight << "\n";
        totalCost += mst[i].weight;
    }

    cout << "\nMinimum Cost of the MST: " << totalCost << "\n";

    return 0;
}
