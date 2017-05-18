#include <bits/stdc++.h>

using namespace std;

long long chain_Ind[200005], chain_pos[200005], chain_head[200005], chain_len[200005];
long long chain_no=1, base_arr[200005], pos_base[200005];
vector<long long>tree[200005];
long long sub_tree[200005], p=0, nod_val[200005], par[200005];

void special_child(long long s){
    sub_tree[s] = 1;
    for(int i=0; i<tree[s].size(); i++){
        if(tree[s][i] != par[s]){
            par[tree[s][i]] = s;
            special_child(tree[s][i]);
            sub_tree[s] += sub_tree[tree[s][i]];
        }
    }
}

void HLD(long long cur){
    if(chain_head[chain_no] ==  -1){
        chain_head[chain_no] = cur;
    }
    chain_Ind[cur] = chain_no;
    chain_pos[cur] = chain_len[chain_no];
    chain_len[chain_no]++;
    base_arr[p] = nod_val[cur-1];
    pos_base[cur-1] = p;
    p++;
    long long sc = -1, mx = -1;
    for(int i=0; i<tree[cur].size(); i++){
        if(tree[cur][i] != par[cur]){
            if(mx < sub_tree[tree[cur][i]]){
                sc = tree[cur][i];
                mx = sub_tree[tree[cur][i]];
            }
        }
    }
    if(sc != -1) HLD(sc);
    for(int i=0; i<tree[cur].size(); i++){
        if(tree[cur][i] != sc && tree[cur][i] != cur[par]){
            chain_no++;
            HLD(tree[cur][i]);
        }
    }
}
void init(){
    fill(chain_head, chain_head+200005, -1);
    fill(chain_len, chain_len + 200005, 0);
}

int main()
{
    long long n, u, v;
    cin >> n;
    for(int i=0; i<n; i++) cin >> nod_val[i];
    for(int i=0; i<n-1; i++){
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    init();
    par[1] = 1;
    special_child(1);
    HLD(1);
    cout << chain_no << " " << p << endl;
    for(int i=0; i<n; i++){
        cout << base_arr[i] << " ";
    }
    for(int i=0; i<n; i++){
        cout << pos_base[i] << " ";
    }
    return 0;
}
