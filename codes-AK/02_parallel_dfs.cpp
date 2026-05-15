#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

void parallelDFS(vector<vector<int>> &adj, int start, int n)
{
    vector<bool> visited(n, false);
    stack<int> s;

    s.push(start);
    visited[start] = true;

    cout << "DFS Traversal: ";

    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        cout << u << " ";

#pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
#pragma omp critical
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    s.push(v);
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    int n = 6;
    vector<vector<int>> adj(n);

    // Create graph
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0, 5};
    adj[3] = {1};
    adj[4] = {1};
    adj[5] = {2};

    cout << "Parallel DFS from node 0:" << endl;
    parallelDFS(adj, 0, n);

    return 0;
}
