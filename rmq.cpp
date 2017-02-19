#include <bits/stdc++.h>


using namespace std;

#define ri(res) do{ \
    (res)=0; \
    char c; \
    int flag=1; \
    for(;;){ \
        c=getchar_unlocked(); \
        if(isdigit(c)||c==EOF) break; \
        else if(c=='-') flag=-1; \
    } \
    while(isdigit(c)){ \
        (res)=(res)*10+c-'0'; \
        c=getchar_unlocked(); \
    } \
    (res)*=flag; \
}while(0)

typedef vector<int> vi;
typedef vector<vi> vvi;

const int tab64[64] = {
    63,  0, 58,  1, 59, 47, 53,  2,
    60, 39, 48, 27, 54, 33, 42,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5};

typedef unsigned long long uint64_t;
int Ln2 (uint64_t value){
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value |= value >> 32;
    return tab64[((uint64_t)((value - (value >> 1))*0x07EDD5E59A4E28C2)) >> 58];
}


template <class T, class comp=less<T> >
struct RMQ_Util{ // nlogn
	T *a;
	vvi t;
	int t_size;
	int n;
	RMQ_Util(){
	}
	~RMQ_Util(){

	}
	RMQ_Util(T *_a,int _n){
		a=_a;
		n=_n;
		register int i,j;
		int lg2=Ln2(n)+1;
		t=vvi(lg2);
		t[0]=vi(n);
		for(i=0;i<n;++i){
			t[0][i]=i;
		}
		t_size=1;
		for(j=1;(1<<j) <=n;++j){
			t_size++;
			t[j]=vi(n-(1<<(j-1)));
			for(i=0;i+(1<<(j-1))<n ;++i){
				if(comp()(a[t[j-1][i]],a[t[j-1][i+(1<<(j-1))] ])){
					t[j][i]=t[j-1][i];
				}else{
					t[j][i]=t[j-1][i+(1<<(j-1))];
				}
			}
		}
	}
	int query(int u,int v){
		int k=Ln2(v-u+1);
		if(comp()(a[ t[k][u] ],a[ t[k][v-(1<<k)+1] ])){
			return t[k][u];
		}else{
			return t[k][v-(1<<k)+1];
		}
	}

};

template <class T,class comp=less<T> >
struct RMQ{ // nloglogn
	T *a;
	int n;
	int block_size;
	int count_block;
	RMQ_Util<T,comp> **rmq;
	vi ind;
	T *block;
	int nb;
	RMQ_Util<T,comp> min_block;
	RMQ(){
		n=0;
		rmq=NULL;
	}
	RMQ(T * _a, int _n){
		a=_a;
		n=_n;

		block_size=Ln2(n)/2+1;

		count_block=n/block_size+1;
		ind= vi(count_block);
		rmq = new RMQ_Util<T,comp>* [count_block];
		block=new T[count_block];
		nb=0;
		for(int i=0;i<count_block;++i){
			int st=i*block_size;
			int nd=min((i+1)*block_size,n);
			if(nd>st){
				rmq[i]=new RMQ_Util<T,comp>(a+st,nd-st);
				ind[i]=st+rmq[i]->query(0,rmq[i]->n-1);
				block[nb]=a[ind[i]];
				nb++;
			}else{
				rmq[i]=NULL;
			}
		}

		min_block=RMQ_Util<T,comp>(block,nb);

	}

	~RMQ(){
		if(!n or !rmq) return;

		//puts("call delete");
		for(int i=0;i<count_block-1;++i){
			if(rmq[i]){
				//delete rmq[i];
				//printf("%p\n",rmq[i]);
				rmq[i]=NULL;
			}
		}
		n=0;
		delete [] rmq;
		delete [] block;

	}
	int query(int u,int v){

		int b_start=u/block_size;
		int b_end=v/block_size;

		if(b_start==b_end){
			return block_size*b_start+rmq[b_start]->query(u%block_size,v%block_size);
		}
		int x=b_start*block_size +rmq[b_start]->query(u%block_size,rmq[b_start]->n-1);
		int y=b_end*block_size+rmq[b_end]->query(0,v%block_size);

		if(comp()(a[y],a[x])){
			x=y;
		}
		if(b_start+1==b_end){
			return x;
		}
		int z=ind[min_block.query(b_start+1,b_end-1)];
		if(comp()(a[x],a[z])){
			return x;
		}else{
			return z;
		}

	}

};



#define maxn 50002

long a[maxn];
int n,q;
int main(){
	ri(n);
	ri(q);
	int i;
	for(i=1;i<=n;++i){
		ri(a[i]);

	}
	RMQ<long,less<long> > r1,r3(a,n+1);
	RMQ<long, greater<long> > r2(a,n+1);
	r1=r3;
	for(i=0;i<q;++i){
		int u,v;
		ri(u);
		ri(v);
		long res=a[r2.query(u,v)]-a[r1.query(u,v)];
		printf("%ld\n",res);
	}
	return 0;
}
