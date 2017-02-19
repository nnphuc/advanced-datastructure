#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define debug(x) cout<<"#"<<#x<<" = "<<x<<endl;

typedef long long llong;
typedef vector<int> vi;

template <class T>
struct Node{
    Node *parent,*child,*left,*right;
    bool mark;
    int degree;
    T data;
    Node(T data){
        this->data=data;
        parent=left=right=child=NULL;
        mark=false;
        degree=0;
    }
};

template <class T>
vector<Node<T> *> childs(Node<T> *n){
    vector<Node<T> *> c;
    Node<T>* node,*stop;
    node=stop=n;
    bool flag=false;
    while(1){
        //cout<<c.size()<<endl;
        if(n==stop and flag==true){
            break;
        }else if(n==stop){
            flag=true;
        }
        c.push_back(n);
        n=n->right;
    }
    return c;
}

template <class T>
struct Heap{
    Node<T>* min_node=NULL,*root_list=NULL;
    H(){
        min_node=root_list=NULL;
        size=0;
    }
    int size=0;
    Node<T> *min(){
        return min_node;
    }
    void merge(const Heap<T> & h2){
        Heap<T> H;
        H.root_list=root_list;
        H.min_node=min_node;
        Node<T> *last=h2.root_list->left;
        h2.root_list->left = H.root_list->left;
        H.root_list->left->right = h2.root_list;
        H.root_list->left = last;
        H.root_list->left->right = H.root_list;
        if(h2.min_node->data<H.min_node->data){
            H.min_node=h2.min_node;
        }
        H.size+=h2.size;
        return H;
    }

    void merge_node(Node<T>*& cur,Node<T>* node){
        if(cur==NULL){
            cur=node;
        }else{
            node->right=cur->right;
            node->left=cur;
            cur->right->left=node;
            cur->right=node;
        }
    }

    void merge_with_root_list(Node<T> * node){
        assert(node);
        merge_node(root_list,node);
    }

    void merge_with_child_list(Node<T> * parent,Node<T>* node){
        assert(parent);
        assert(node);
        merge_node(parent->child,node);
    }

    void remove_from_root_list(Node<T>* node){
        assert(node);
        if(node==root_list){
            root_list=node->right;
        }
        node->left->right = node->right;
        node->right->left = node->left;

        //delete node;
    }
    void remove_from_child_list(Node<T>* parent,Node<T>* node){
        assert(parent);
        assert(node);
        if(parent->child==parent->child->right){
            //delete parent->child;
            parent->child=NULL;
        }else if(parent->child==node){
            parent->child = node->right;
            node->right->parent = parent;
        }
        node->left->right = node->right;
        node->right->left = node->left;
        //delete node;
    }
    void link(Node<T> *y,Node<T>* x){
        assert(x);
        assert(y);
        remove_from_root_list(y);
        y->left=y->right=y;
        merge_with_child_list(x,y);
        x->degree++;
        y->parent=x;
        y->mark=false;
    }
    Node<T>* insert(T d){
        Node<T>* n=new Node<T>(d);
        n->left=n->right=n;
        merge_with_root_list(n);
        if(min_node==NULL or d<min_node->data){
            min_node=n;
        }
        size++;
        return n;
    }
    void cut(Node<T>* x,Node<T>* y){
        assert(x);
        assert(y);
        remove_from_child_list(y,x);
        y->degree--;
        merge_with_root_list(x);
        x->parent=NULL;
        x->mark=false;
    }
    void cascading_cut(Node<T>* y){
        assert(y);
        Node<T>* z=y->parent;
        if(z!=NULL){
            if(y->mark==false){
                y->mark=true;
            }else{
                cut(y,z);
                cascading_cut(z);
            }
        }
    }
    bool decrease_key(Node<T>* x,T k){
        if(k>x->data){
            return false;
        }
        x->data=k;
        Node<T>* y=x->parent;
        if(y!=NULL && x->data<y->data){
            cut(x,y);
            cascading_cut(y);
        }
        if(x->data<min_node->data){
            min_node=x;
        }
        return true;
    }
    void consolidate(){
        unordered_map<int,Node<T>*> A;
        vector<Node<T>* > nodes=childs(root_list);
        for(int w=0;w<nodes.size();w++){
             auto x=nodes[w];
             int d=x->degree;
             while(A.find(d)!=A.end()){

                Node<T>* y=A[d];
                if(x->data>y->data){
                    Node<T>* temp=x;
                    x=y;
                    y=temp;
                }
                link(y,x);
                A.erase(d);
                d++;
             }
             A[d]=x;
        }
        for(auto x:A){
            if(x.second->data<min_node->data){
                min_node=x.second;
            }
        }
    }
    Node<T>* extract_min(){
        Node<T>* z=min_node;
        if(z!=NULL){
            if(z->child!=NULL){
                auto children=childs(z->child);
                for(auto x:children){
                    merge_with_root_list(x);
                    x->parent=NULL;
                }
            }
            remove_from_root_list(z);

            if(z==z->right){
                min_node=root_list=NULL;
            }else{
                min_node=z->right;
                consolidate();
            }
            size--;
        }
        return z;
    }
};

int main(){

    Heap<int> H;
    Node<int> *a=H.insert(4);
    Node<int> *b=H.insert(1);
    Node<int> *c=H.insert(3);
    Node<int> *d=H.insert(6);
    Node<int> *e=H.insert(2);
    H.decrease_key(d,1);
    while(H.size){
        cout<<H.min()->data<<endl;
        auto z=H.extract_min();
    }
	return 0;
}
