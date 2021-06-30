#include<iostream>
#include<vector>
#include<algorithm>
#include<unistd.h>

using namespace std;

struct TEdge{
    int L;
    int R;

    bool operator<(const TEdge &t) {
        return L < t.L;
    }
};


int main() {
    int n, m;
    cin >> n;
    vector<TEdge> v;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, r});
    }
    vector<TEdge> begin = v;
    sort(v.begin(), v.end());
    cin >> m;
    vector<int> res;

    int empty = 0;
    bool zero = false;
    int j = -1;

    while (empty < m && !zero) {
        int index = j + 1;
        int right = empty;
        for (long unsigned int i = index; i < v.size(); ++i) {
            if(v[i].L > empty) {
                break;
            }
            if (v[i].R > right) {
                j = i;
                right = v[j].R;
            }
        }
        if (j == index - 1) {
            zero = true;
            break;
        }
        empty = v[j].R;
        for (long unsigned int k = 0; k < begin.size(); ++k) {
            if (v[j].L == begin[k].L && v[j].R == begin[k].R) {
                res.push_back(k);
                break;
            }
        }
    }
    sort(res.begin(), res.end());
    if (zero) {
        cout << "0" << endl;
    } else {
        cout << res.size() << endl;
        for (long unsigned int i = 0; i < res.size(); ++i) {
            cout << begin[res[i]].L << " " << begin[res[i]].R << endl;
        }
    }
} 
