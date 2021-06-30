#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const long long INF = 92233720368547758;

struct TEdge {
    int From;
    int To;
    long long Weight;
};

struct TList {
    int To;
    long long Weight;
};

struct TPriority{
    long long  Distance;
    int Vertex;
};

bool operator<(const TPriority &l, const TPriority &r) {
    return l.Distance > r.Distance;
}

bool FordBellman(vector<TEdge>& edges, vector<long long> &distances, int n) {
    int i;
    bool changed = false;
    for (i = 0; i < n; ++i) {
        changed = false;
        for (long unsigned int j = 0; j < edges.size(); ++j) {
            if ((distances[edges[j].From] != INF) && (distances[edges[j].To] > distances[edges[j].From] + edges[j].Weight)) {
                changed = true;
                distances[edges[j].To] = distances[edges[j].From] + edges[j].Weight;
            }
        }
        if (!changed) {
            break;
        }
    }
    if (i == n) {
        changed = false;
        for (long unsigned int j = 0; j < edges.size(); ++j) {
            if ((distances[edges[j].From] != INF) && (distances[edges[j].To] > distances[edges[j].From] + edges[j].Weight)) {
                changed = true;
                distances[edges[j].To] = distances[edges[j].From] + edges[j].Weight;
            }
        }
    }
    return !changed;
}

void H(vector<vector<TList>>& edges, vector<long long> &distances) {
    for (int i = 0; i < edges.size(); ++i) {
        for(int j = 0; j < edges[i].size(); ++j) {
            edges[i][j].Weight = edges[i][j].Weight + distances[i] - distances[edges[i][j].To];
        }
    }
}

vector<long long> Dijkstra(vector<vector<TList>>& edges, vector<long long> &distances, int s) {
    priority_queue<TPriority> pq;
    vector<bool> relaxed(distances.size());
    pq.push(TPriority{0, s});
    while (!pq.empty()) {
        TPriority p = pq.top();
        pq.pop();
        if (relaxed[p.Vertex - 1]) {
            continue;
        }
        relaxed[p.Vertex - 1] = 1;
        for (int i = 0; i < edges[p.Vertex].size(); ++i) {
            if((distances[p.Vertex - 1] != INF) && (distances[edges[p.Vertex][i].To - 1] > distances[p.Vertex - 1] + edges[p.Vertex][i].Weight)) {
                distances[edges[p.Vertex][i].To - 1] = distances[p.Vertex - 1] + edges[p.Vertex][i].Weight;
                pq.push(TPriority{distances[edges[p.Vertex][i].To - 1], edges[p.Vertex][i].To});
            }
        }
    }
    return distances;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<TEdge> edgesS;
    vector<vector<TList>> edges(n + 1);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edgesS.push_back({from, to, weight});
        edges[from].push_back({to, weight});
    }

    for (int i = 1; i <= n; ++i) {
        edgesS.push_back({0, i, 0});
    }

    vector<long long> distances(n + 1, INF);
    distances[0] = 0;
    bool flag = FordBellman(edgesS, distances, n + 1);

    if (!flag) {
        cout << "Negative cycle\n";
        return 0;
    }

    H(edges, distances);

    vector<vector<long long>> result(n);
    vector<long long> distances2(distances.size() - 1);

    for (int i = 0; i < n; ++i) {
        distances2.assign(distances2.size(), INF);
        distances2[i] = 0;
        result[i] = Dijkstra(edges, distances2, i + 1);
    }

    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            if (result[i][j] == INF) {
                cout << "inf ";
            } else {
                cout << result[i][j] + distances[j + 1] - distances[i + 1]<< " ";
            }
        }
        cout << endl;
    }
} 
