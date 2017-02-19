#include <bits/stdc++.h>
using namespace std;


template <class K,class V>
struct item{
	K key;
	V val;
	int pos;
	item(K k=K(),V v=V()):key(k),val(v){

	}
};


template <class K,class V>
struct heap{
	typedef item<K,V> Item;
	typedef vector<Item*> Data;
	static inline int cmp1(K &a,K &b) {
		if(a==b){
			return 0;
		}else if(a>b){
			return 1;
		}
		return -1;
	}
	static inline int cmp2(K &a,K &b) {
		if(a==b){
			return 0;
		}else if(a<b){
			return 1;
		}
		return -1;
	}
	Data data;
	int ary;
	int (*cmp) (K&,K &);
	heap(int d=4,bool less=true){
		ary=d;
		if(less){
			cmp=cmp1;
		}else{
			cmp=cmp2;
		}
	}
	~heap(){
		int i;
		for(i=0;i<data.size();++i){
			delete data[i];
		}

	}
	int parent(int x){
		if(x==0) return -1;
		return (x-1)/ary;
	}
	int first_child(int x){
		return x*ary+1;
	}
	int last_child(int x){
		return (x+1)*ary;
	}
	void siftup(Item *i,int x){
		int p=parent(x);
		while(p>=0 and cmp(i->key,data[p]->key)<0){
			data[x]=data[p];
			data[x]->pos=x;
			x=p;
			p=parent(x);
		}
		data[x]=i;
		data[x]->pos=x;
	}
	Item *insert(K k,V v){
		Item *i=new Item(k,v);
		data.push_back(i);
		siftup(i,data.size()-1);
		return i;
	}
	Item * top(){
		return data.front();
	}
	int min_child(int x){
		int minc=first_child(x);
		if(minc>=data.size()) return -1;
		int last=min((int)data.size()-1,last_child(x));
		for(int i=minc+1;i<=last;++i){
			if(cmp(data[i]->key,data[minc]->key)<0) minc=i;
		}
		return minc;
	}
	void siftdown(Item *i,int x){
		int c=min_child(x);
		while(c>=0 and cmp(i->key, data[c]->key)>0){
			data[x]=data[c];
			data[x]->pos=x;
			x=c;
			c=min_child(x);
		}
		data[x]=i;
		data[x]->pos=x;
	}
	void erase(Item *i){
		Item *j=data.back();
		if(i->pos!=j->pos){
			if(cmp(j->key,i->key)<=0)siftup(j,i->pos);
			else siftdown(j,i->pos);
		}
		delete i;
		data.pop_back();
	}
	void pop(){
		erase(top());
	}
	void changekey(Item *i,K k){
		K ki=i->key;
		if(cmp(ki,k)!=0){
		i->key=k;
		if(cmp(k<ki)<0) siftup(i,i->pos);
			else siftdown(i,i->pos);
		}
	}
	int size(){return data.size();}
};

int main() {
	heap<int,int> h=heap<int,int>(2,true);
	item<int,int> *a =h.insert(3,1);
	item<int,int> *b =h.insert(1,2);
	item<int,int> *c =h.insert(6,3);
	item<int,int> *d =h.insert(2,4);
	item<int,int> *e =h.insert(1,5);
	while(h.size()){
		cout<<h.top()->key<<" "<<h.top()->val<<endl;
		h.pop();
	}

	return 0;
}
