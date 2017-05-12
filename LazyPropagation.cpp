#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct node{
	long long sum, prop;
	node(){
		sum = 0;
		prop = 0;
	}
};

node tree[3*100005];

void update(ll n, ll b, ll e, ll i, ll j, ll v){
	if(b > j || e < i){
		return;
	}
	if(b >= i && e <= j){
		tree[n].sum += (e - b + 1) * v;
		tree[n].prop += v;
		return;
	}
	ll left = 2 * n;
	ll right = 2 * n + 1;
    ll mid = (b + e) / 2;
    update(left, b, mid, i, j, v);
    update(right, mid + 1, e, i, j, v);
    tree[n].sum = tree[left].sum + tree[right].sum + (e - b + 1) * tree[n].prop;
}
ll query(ll n, ll b, ll e, ll i, ll j, ll carry = 0){
	if(b > j || e < i){
		return 0;
	}
	if(b >= i && e <= j){
		return tree[n].sum + (e - b + 1) * carry;
	}
	ll left = 2 * n;
	ll right = 2 * n + 1;
    ll mid = (b + e) / 2;
    ll p1 = query(left, b, mid, i, j, carry + tree[n].prop);
    ll p2 = query(right, mid + 1, e, i, j, carry + tree[n].prop);
    return p1 + p2;
}

void init(){
	for(int i=0; i<3*100005; i++){
		tree[i].sum = 0;
		tree[i].prop = 0;
	}
}

int main()
{
	ll t, cases=0, n, m;
	scanf("%lld", &t);
	while(t--){
		scanf("%lld%lld", &n, &m);
		init();
		ll q, i, j, x;
		printf("Case %lld:\n", ++cases);
		while(m--){
			scanf("%lld%lld%lld", &q, &i, &j);
			if(q == 1){
				printf("%lld\n", query(1, 1, n, i+1, j+1));
			}else {
				scanf("%lld", &x);
				update(1, 1, n, i+1, j+1, x);
			}
		}
	}

	return 0;
}
