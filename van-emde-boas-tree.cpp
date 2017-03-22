#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define debug(x) cout<<"#"<<#x<<" = "<<x<<endl;


inline long _sqrt(long n){

    long x=n,y=(n+1)/2;
    while(y<x){
        x=y;
        y=(y+n/y)/2;
    }
    if(x*x<n){
        return x+1;
    }
    return x;

}
class VEB{

public:
    VEB(){
        m_u=2;
        m_summary=NULL;
    }
    VEB(long u){


        m_summary=NULL;
        m_u=u;
        m_sqrt_u=_sqrt(m_u);
        if(m_u>2){
            m_summary=NULL;
        }
        m_min=m_max=NIL;
    }
    ~VEB(){
        if(m_u>2){
            for(auto p:m_cluster){
                if(p.second!=NULL){
                    delete p.second;
                }
            }
            if(m_summary!=NULL){
                delete m_summary;
            }
        }
    }
    long min() const {
        return m_min;
    }
    long max() const {
        return m_max;
    }

    bool find(long x){
        if(x==m_min || x==m_max){
            return true;
        }else if(m_u==2){
            return false;
        }
        if(m_cluster.find(high(x))==m_cluster.end()){
            return false;
        }
        return m_cluster[high(x)]->find(low(x));
    }
    void insert(long x){
        if(m_min==NIL){
            empty_insert(x);
        }else{
            if(x<m_min){
                long temp=m_min;
                m_min=x;
                x=temp;
            }
            if(m_u>2){
                long h=high(x);
                if(m_cluster.find(h)==m_cluster.end()){
                    m_cluster[h]=new VEB(m_sqrt_u);
                }
                if(m_summary==NULL){
                    m_summary=new VEB(m_sqrt_u);
                }
                if(m_cluster[h]->min()==NIL){
                    m_summary->insert(h);
                    m_cluster[h]->empty_insert(low(x));
                }else{
                    m_cluster[h]->insert(low(x));
                }
            }
            if(x>m_max){
                m_max=x;
            }
        }
    }
    void erase(long x){

        if(m_min==m_max){
            m_min=m_max=NIL;
        }else if(m_u==2){
            if(x==0){
                m_min=1;
            }else{
                m_min=0;
            }
            m_max=m_min;
        }else{
            if(x==m_min){
                long first=m_summary->min();
                x=index(first,m_cluster[first]->min());
                m_min=x;
            }

            m_cluster[high(x)]->erase(low(x));
            if(m_cluster[high(x)]->min()==NIL){
                m_summary->erase(high(x));
                if(x==m_max){
                    long summary_max=m_summary->max();
                    if(summary_max==NIL){
                        m_max=m_min;
                    }else{
                        m_max=index(summary_max,m_cluster[summary_max]->max());
                    }
                }
            }else if(x==m_max){
                m_max=index(high(x),m_cluster[high(x)]->max());
            }
        }
    }
    long successor(long x){
        if(m_u<=2){
            if(x==0 && m_max==1){
                return 1;
            }else{
                return NIL;
            }
        }else if(m_min!=NIL && x<m_min){
            return m_min;
        }else{
            long H=high(x),L=low(x);
            long maxLow=NIL;
            VEB * c=NULL;
            if(m_cluster.find(H)!=m_cluster.end()){
                c=m_cluster[H];
                maxLow=c->max();
            }
            if(maxLow !=NIL && L<maxLow){
                long offset=c->successor(L);
                return index(H,offset);
            }else{
                long succ_cluster=NIL;
                if(m_summary!=NULL){
                    succ_cluster=m_summary->successor(H);
                }
                if(succ_cluster==NIL){
                    return NIL;
                }else{
                    VEB *cluster2=NULL;
                    long offset=0;
                    if(m_cluster.find(succ_cluster)!=m_cluster.end()){
                        cluster2=m_cluster[succ_cluster];
                        offset=cluster2->min();
                    }
                    return index(succ_cluster,offset);
                }
            }
        }
    }
    long predecessor(long x){
        if(m_u<=2){
            if(x==1 && m_min==0){
                return 0;
            }else{
                return NIL;
            }
        }else if(m_max!=NIL && x>m_max){
            return m_max;
        }else{
            long H=high(x),L=low(x);
            long minLow=NIL;
            VEB * c=NULL;
            if(m_cluster.find(H)!=m_cluster.end()){
                c=m_cluster[H];
                minLow=c->min();
            }
            if(minLow !=NIL && L>minLow){
                long offset=c->predecessor(L);
                offset=offset==NIL?0:offset;
                return index(H,offset);
            }else{
                long pred_cluster=NIL;
                if(m_summary!=NULL){
                    pred_cluster=m_summary->predecessor(H);
                }
                if(pred_cluster==NIL){
                    if(m_min!=NIL && x>m_min){
                        return m_min;
                    }else{
                        return NIL;
                    }
                }else{
                    VEB *cluster2=NULL;
                    long offset=0;
                    if(m_cluster.find(pred_cluster)!=m_cluster.end()){
                        cluster2=m_cluster[pred_cluster];
                        offset=cluster2->max();
                    }
                    return index(pred_cluster,offset);
                }
            }
        }
    }

private:
    const static long NIL=-1;
    long high(long x){
        return x/m_sqrt_u;
    }
    long low(long x){
        return x%m_sqrt_u;
    }
    long index(long x,long y){
        return x*m_sqrt_u+y;
    }
    void empty_insert(long x){
        m_min=m_max=x;
    }
    long m_sqrt_u;
    long m_u;
    long m_min;
    long m_max;
    VEB *m_summary;
    unordered_map<long,VEB *> m_cluster;
};


int main(){

    VEB t=VEB(100000000000);
    for(int i=1;i<=1000000;i++){
        t.insert(i);
    }
    for(int i=4;i<=1000000;i++){
        t.erase(i);
    }
    for(int i=1;i<=10;i++){
        if(t.find(i)){
            cout<<i<<" ";
        }
    }
    cout<<t.successor(10);
	return 0;
}
