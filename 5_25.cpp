#include <iostream>
#include <queue>
#include <stack>
#include <list>

#define inf INT_MAX

using namespace std;

void DFS(int startVertex, vector<vector<int>>& mat, vector<int>& used, vector<int>& dist)
{
    stack<int> s;
    s.push(startVertex);
    dist[startVertex] = 0;
    int step = 1;

    while (!s.empty())
    {
        int cur_vertex = s.top();
        s.pop();

        if (used[cur_vertex] == 0)
        {
            cout << cur_vertex << " ";
            used[cur_vertex] = 1;
            dist[cur_vertex] = step++;
        }

        for (int i = 0; i < mat.size(); i++)
        {
            if (mat[cur_vertex][i] != 0 && used[i] == 0)
            {
                s.push(i);
            }
        }
        used[cur_vertex] = 2;
    }
}


using vertex_number = int;
using dist = int;
using pair_vector = vector<pair<int, int>>;

vector<int> Dijkstra(const vector<vector<int>>& graph, int v)
{
    int size = graph.size();

    vector<int> distances(size, 10000);
    priority_queue<pair<dist, vertex_number>, pair_vector, greater<pair<int, int>>> pq;

    distances[v] = 0;
    pq.push({ 0, v });

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < size; v++)
        {
            if (graph[u][v] != 0 && distances[v] > distances[u] + graph[u][v])
            {
                distances[v] = distances[u] + graph[u][v];
                pq.push({ distances[v], v });
            }
        }
    }

    return distances;
}

vector<int> Degree(vector<vector<int>>& graph)
{
    int size_mat = graph.size();
    vector<int> deg(size_mat, 0);
    queue<int> Queue;
    vector <int> used(size_mat, 0);
    Queue.push(0);
    int iter = 0;
    while (!Queue.empty())
    {
        int node = Queue.front();
        Queue.pop();


        if (used[node] == 2)
            continue;
        used[node] = 2;
        iter++;


        for (int j = 0; j < size_mat; j++)
        {
            if (graph[node][j] > 0 && used[j] != 2)
            {
                Queue.push(j);
                used[j] = 1;
                deg[node] += 1;
                deg[j] += 1;
            }
        }
    }
    return deg;
}

double AverageDegree(vector<vector<int>> mat)
{
    vector<int> deg = Degree(mat);
    int n = deg.size();
    double sum = 0;
    for (int d : deg)
    {
        sum += d;
    }
    return sum / n;
}

vector<vector<int>> PrimsAlgorithm(vector<vector<int>>& graph)
{
    int n = graph.size();

    vector<int> parent(n, -1);
    vector<int> key(n, inf);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({ 0, 0 });
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;
        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] > 0 && !visited[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.push({ key[v], v });
            }
        }
    }
    vector<vector<int>> span(n, vector<int>(n, 0));
    for (int i = 1; i < n; i++) {
        span[i][parent[i]] = span[parent[i]][i] = graph[i][parent[i]];
    }
    return span;
}


void printMatrix(vector<vector<int>>& m)
{
    int rows = m.size();
    int cols = m[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printVector(vector<int> v)
{
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    vector<vector<int>> mat = {
    { 0, 1, 4, 4, 8, 5, 6, 7, 5, 2, 4, 2 },
    { 1, 0, 6, 9, 1, 2, 3, 1, 2, 8, 9, 5 },
    { 4, 6, 0, 7, 4, 8, 9, 6, 2, 6, 7, 6 },
    { 4, 9, 7, 0, 2, 0, 0, 8, 8, 8, 7, 8 },
    { 8, 1, 4, 2, 0, 3, 9, 2, 7, 7, 3, 1 },
    { 5, 2, 8, 0, 3, 0, 0, 6, 4, 4, 5, 3 },
    { 6, 3, 9, 0, 9, 0, 0, 2, 2, 9, 2, 3 },
    { 7, 1, 6, 8, 2, 6, 2, 0, 7, 4, 2, 6 },
    { 5, 2, 2, 8, 7, 4, 2, 7, 0, 3, 4, 6 },
    { 2, 8, 6, 8, 7, 4, 9, 4, 3, 0, 3, 4 },
    { 4, 9, 7, 7, 3, 5, 2, 2, 4, 3, 0, 7 },
    { 2, 5, 6, 8, 1, 3, 3, 6, 6, 4, 7, 0 }
    };

    vector<int> used(12, 0);
    vector<int> dist(12, -1);

    for (int i = 0; i < 12; i++)
    {
        if (used[i] == 0) {
            DFS(i, mat, used, dist);
        }
    }

    cout << "\nDFS:\n ";
    for (int i = 0; i < 12; i++) cout << dist[i] << " ";
    cout << "\nDFS visited: ";
    for (int i = 0; i < 12; i++) cout << used[i] << " ";
    cout << "\n";

    cout << "\nDijkstra:\n";
    vector<int> distances = Dijkstra(mat, 0);

    for (int i = 0; i < mat.size(); i++)
        cout << "Shortest route from 0 to " << i << ": " << distances[i] << "\n";

    cout << "Degrees based on BFS: ";
    printVector(Degree(mat));
    cout << "\nAverage degrees: " << AverageDegree(mat);

    vector<vector<int>> span = PrimsAlgorithm(mat);
    cout << "\nMin span matrix:\n";
    printMatrix(span);

    DFS(0, span, used, dist);

    cout << "\nDijkstra for min span:\n";
    distances = Dijkstra(span, 0);

    for (int i = 0; i < span.size(); i++)
        cout << "Shortest route from 0 to " << i << ": " << distances[i] << endl;
    cout << endl;

    cout << "Span matrix degrees: ";
    printVector(Degree(span));
    cout << "\nAverage degrees: " << AverageDegree(span);
}