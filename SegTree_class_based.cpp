// Segment Tree Template using class based 
// the problem solved in this example is finding the minimum of the index in the range


#include <bits/stdc++.h>
using namespace std;
#define int long long 
typedef long long ll;

class SegmentTree {
private:
    vector<ll> tree;
    vector<ll> arr;
    int n;

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2*idx+1, l, mid);
        build(2*idx+2, mid+1, r);
        tree[idx] = min(tree[2*idx+1],tree[2*idx+2]);
    }

    ll query(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return LLONG_MAX;
        if (ql <= l && r <= qr) return tree[idx];

        int mid = (l + r) / 2;
        ll leftRes = query(2*idx+1, l, mid, ql, qr);
        ll rightRes = query(2*idx+2, mid+1, r, ql, qr);

        return min(leftRes,rightRes);
    }

    void update(int idx, int l, int r, int pos, ll val) {
        if (l == r) {
            arr[l] = val;
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(2*idx+1, l, mid, pos, val);
        else update(2*idx+2, mid+1, r, pos, val);
        tree[idx] = min(tree[2*idx+1],tree[2*idx+2]);
    }

public:
    SegmentTree(const vector<ll>& input) {
        arr = input;
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n-1);
    }

    ll getMin(int l, int r) {
        return query(0, 0, n-1, l, r);
    }

    void setValue(int pos, ll val) {
        update(0, 0, n-1, pos, val);
    }
};

signed main(){
    int n,m; cin >> n >> m;
    vector<int>arr(n);

    for(int &e : arr) cin >> e;

    SegmentTree st(arr);
    
    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        if(a==1){
            st.setValue(b,c);
        }else{
            cout << st.getMin(b,c-1) << endl;
        }
    }
}
