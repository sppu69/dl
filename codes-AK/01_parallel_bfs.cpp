#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

void parallelBFS(vector<vector<int>> &adj, int start, int n)
{
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";

    while (!q.empty())
    {
        int size = q.size();
        vector<int> current_level;

#pragma omp parallel for
        for (int i = 0; i < size; i++)
        {
            int u = q.front();
            q.pop();

#pragma omp critical
            current_level.push_back(u);

            for (int v : adj[u])
            {
#pragma omp critical
                {
                    if (!visited[v])
                    {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        for (int node : current_level)
        {
            cout << node << " ";
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

    cout << "Parallel BFS from node 0:" << endl;
    parallelBFS(adj, 0, n);

    return 0;
}
