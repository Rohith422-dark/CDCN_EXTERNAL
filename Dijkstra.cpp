
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    int n, m, u, v, w, src;

    cout << "Enter vertices and edges: ";
    cin >> n >> m;

    vector< pair<int,int> > adj[100];

    cout << "Enter edges (u v weight):\n";

    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    cout << "Enter source: ";
    cin >> src;

    vector<int> dist(n + 1, 1000000000);

    priority_queue<
        pair<int,int>,
        vector< pair<int,int> >,
        greater< pair<int,int> >
    > pq;

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while(!pq.empty())
    {
        int d = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        if(d > dist[node])
            continue;

        for(int i = 0; i < (int)adj[node].size(); i++)
        {
            int next = adj[node][i].first;
            int wt = adj[node][i].second;

            if(dist[node] + wt < dist[next])
            {
                dist[next] = dist[node] + wt;

                pq.push(make_pair(dist[next], next));
            }
        }
    }

    cout << "Shortest distances:\n";

    for(int i = 1; i <= n; i++)
    {
        if(dist[i] == 1000000000)
            cout << src << " to " << i << " = INF" << endl;
        else
            cout << src << " to " << i << " = " << dist[i] << endl;
    }

    return 0;
}

