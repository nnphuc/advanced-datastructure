#include "header.h"

struct BST_Node{
    int val;
    BST_Node *left, *right,*p;
    BST_Node(int _val){
        left=right=NULL;
        val=_val;
    }
};

void BST_inorder(BST_Node *x){
    if(x==NULL) return;
    BST_inorder(x->left);
    cout<<x->val<<" ";
    BST_inorder(x->right);
}

BST_Node *BST_search(BST_Node* cur,int val){
    if(cur==NULL or cur->val==val) return cur;
    if(cur->val > val){
        return BST_search(cur->left,val);
    }else{
        return BST_search(cur->right,val);
    }
}

BST_Node* BST_maximum(BST_Node *x){
    while(x->right!=NULL)x=x->right;
    return x;
}
BST_Node* BST_minimum(BST_Node *x){
    while(x->left!=NULL) x=x->left;
    return x;
}
BST_Node* BST_successor(BST_Node *x){
    if(x->right!=NULL){
        return BST_minimum(x->right);
    }
    auto y=x->p;
    while(y!=NULL and x==y->right){
        x=y;
        y=y->p;
    }
    return y;
}
BST_Node*  BST_insert(BST_Node *&root, BST_Node *z){
    BST_Node *y=NULL;
    BST_Node *x=root;
    while(x!=NULL){
        y=x;
        if(z->val<x->val){
            x=x->left;
        }else x=x->right;
    }
    z->p=y;
    if(y==NULL){
        root=z;
    }else if(z->val<y->val){
        y->left=z;
    }else{
        y->right=z;
    }
    return z;
}

void BST_transplant(BST_Node *&root,BST_Node *u,BST_Node *v){
    if(u->p==NULL) root=v;
    else if(u==u->p->left){
        u->p->left=v;
    }else u->p->right=v;
    if(v!=NULL) v->p=u->p;
}

void BST_delete(BST_Node *&root, BST_Node *z){
    if(z->left==NULL) BST_transplant(root,z,z->right);
    else if(z->right==NULL) BST_transplant(root,z,z->left);
    else{
        auto y=BST_minimum(z->right);
        if(y->p!=z){
            BST_transplant(root,y,y->right);
            y->right=z->right;
            y->right->p=y;
        }
        BST_transplant(root,z,y);
        y->left=z->left;
        y->left->p=y;
    }
}
int main(){

    BST_Node *root=NULL;
    auto a=BST_insert(root, new BST_Node(6));
    auto b=BST_insert(root, new BST_Node(2));
    auto c=BST_insert(root, new BST_Node(10));
    auto d=BST_insert(root, new BST_Node(4));
    auto e=BST_insert(root, new BST_Node(14));
    auto f=BST_insert(root, new BST_Node(8));
    auto g=BST_insert(root, new BST_Node(12));

    BST_inorder(root);
    cout<<endl;

    //cout<<(BST_successor(f)->val);
    return 0;
}
