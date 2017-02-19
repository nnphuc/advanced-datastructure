#include "AVLTree.h"

template <class Key,class Comp>
AVLNode<Key,Comp>::AVLNode()
{
    height=1;
    size=1;
    left=right=parent=NULL;
    key=Key();
}

template <class Key,class Comp>
AVLNode<Key,Comp>::AVLNode(Key k)
{
    height=1;
    size=1;
    left=right=parent=NULL;
    key=k;
}

template<class Key,class Comp>
int AVLNode<Key,Comp>::getHeight(AVLNode *node)
{
    if(node){
        return node->height;
    }
    return 0;
}

template<class Key,class Comp>
int AVLNode<Key,Comp>::getBalance(AVLNode *node)
{
    if(node){
        return AVLNode::getHeight(node->left)-AVLNode::getHeight(node->right);
    }
    return 0;
}
template<class Key,class Comp>
int AVLNode<Key,Comp>::getSize(AVLNode *node)
{
    if(node){
        return node->size;
    }
    return 0;
}

template<class Key,class Comp>
void AVLNode<Key,Comp>::updateSize()
{
    size=AVLNode::getSize(left)+AVLNode::getSize(right)+1;
}

template<class Key,class Comp>
void AVLNode<Key,Comp>::updateHeight()
{
    height=max(AVLNode::getHeight(left),AVLNode::getHeight(right))+1;
}

template<class Key,class Comp>
AVLNode<Key,Comp>* AVLNode<Key,Comp>::rightRotate(AVLNode<Key,Comp> *x)
{
    AVLNode<Key,Comp> *y=x->left,*B=y->right;
    y->parent=B;
    y->right=x;
    x->parent=y;
    x->left=B;
    if(B)B->parent=x;
    x->updateHeight();
    y->updateHeight();
    x->updateSize();
    y->updateSize();
    return y;
}


template<class Key,class Comp>
AVLNode<Key,Comp>* AVLNode<Key,Comp>::leftRotate(AVLNode<Key,Comp> *x)
{
    AVLNode<Key,Comp> *y=x->right,*B=y->left;
    y->parent=B;
    y->left=x;
    x->parent=y;
    x->right=B;
    if(B)B->parent=x;
    x->updateHeight();
    y->updateHeight();
    x->updateSize();
    y->updateSize();
    return y;
}

template<class Key,class Comp>
AVLNode<Key,Comp>::~AVLNode()
{
    if(left) delete left;
    if(right) delete right;
    left=right=NULL;
}

template<class Key,class Comp>
AVLTree<Key,Comp>::AVLTree()
{
    root=NULL;
    m_size=0;
}

template<class Key,class Comp>
AVLTree<Key,Comp>::~AVLTree()
{
    delete root;
    root=NULL;
    m_size=0;
}


template<class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::_insert(AVLNode<Key,Comp> *root,Key key)
{
    if(root==NULL){
        root=new AVLNode<Key,Comp>(key);
        lastInsert=root;
        return root;
    }
    if(Comp()(key,root->key)){
        AVLNode<Key,Comp>* t=_insert(root->left,key);
        t->parent=root;
        root->left=t;
    }else{
        AVLNode<Key,Comp>* t=_insert(root->right,key);
        t->parent=root;
        root->right=t;
    }
    root->updateHeight();
    root->updateSize();
    int balance=AVLNode<Key,Comp>::getBalance(root);
    if(balance>1){
        if(AVLNode<Key,Comp>::getBalance(root->left)<0){
            root->left=AVLNode<Key,Comp>::leftRotate(root->left);
        }
        root=AVLNode<Key,Comp>::rightRotate(root);
    }else if(balance<-1){
        if(AVLNode<Key,Comp>::getBalance(root->right)>0){
            root->right=AVLNode<Key,Comp>::rightRotate(root->right);
        }
        root=AVLNode<Key,Comp>::leftRotate(root);
    }

    return root;
}

template <class Key,class Comp>
AVLNode<Key,Comp> * AVLTree<Key,Comp>::insert(Key data)
{
    root=_insert(root,data);
    return lastInsert;
}

template <class Key,class Comp>
int AVLTree<Key,Comp>::size()
{
    return AVLNode<Key,Comp>::getSize(root);
}

template <class Key,class Comp>
AVLNode<Key,Comp> *AVLTree<Key,Comp>::_min(AVLNode<Key,Comp> *root)
{
    if(root==NULL)
        return NULL;
    if(root->left){
        return   _min(root->left);
    }
    return root;
}

template <class Key,class Comp>
AVLNode<Key,Comp> *AVLTree<Key,Comp>::_max(AVLNode<Key,Comp> *root)
{
    if(root==NULL)
        return NULL;
    if(root->right){
        return   _max(root->right);
    }
    return root;
}

template <class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::_delete(AVLNode<Key,Comp> *root, Key key)
{
    if(root==NULL){
        return NULL;
    }
    if(Comp()(key,root->key)){
        root->left=_delete(root->left,key);
    }else if(Comp()(root->key,key)){
        root->right=_delete(root->right,key);
    }else {
        if(!root->left ||!root->right){
            AVLNode<Key,Comp>* temp=root->left?root->left:root->right;
            if(temp==NULL){
                temp=root;
                root=NULL;
            }else{
                *root=*temp;
            }
            delete temp;
        }else{
            AVLNode<Key,Comp>* temp=_min(root->right);
            root->key=temp->key;
            root->right=_delete(root->right,key);
        }
    }
    if(!root) {
        return root;
    }
    root->updateHeight();
    root->updateSize();
    int balance = AVLNode<Key,Comp>::getBalance(root);
     if(balance>1){
        if(AVLNode<Key,Comp>::getBalance(root->left)<0){
            root->left=AVLNode<Key,Comp>::leftRotate(root->left);
        }
        return AVLNode<Key,Comp>::rightRotate(root);
    }else if(balance<-1){
        if(AVLNode<Key,Comp>::getBalance(root->right)>0){
            root->right=AVLNode<Key,Comp>::rightRotate(root->right);
        }
        return AVLNode<Key,Comp>::leftRotate(root);
    }
    return root;
}

template<class Key,class Comp>
void AVLTree<Key,Comp>::erase(Key key)
{
    root=_delete(root,key);
}

template<class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::min()
{
    return _min(root);
}

template<class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::max()
{
    return _max(root);
}

template<class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::_find(AVLNode<Key,Comp> *root,Key key)
{
    if(root==NULL)
        return NULL;
    if(key==root->key)
        return root;
    if(Comp()(key,root->key)){
        return _find(root->left,key);
    }else{
        return _find(root->right,key);
    }
}

template<class Key,class Comp>
AVLNode<Key,Comp>* AVLTree<Key,Comp>::find(Key key)
{
   return _find(root,key);
}

template <class Key,class Comp>
AVLNode<Key,Comp> *AVLTree<Key,Comp>::succ(AVLNode<Key,Comp> *node)
{
    if(node==NULL)
        return node;
    if(node->right)
        return _min(node->right);
    AVLNode<Key,Comp> *p=node->parent;
    while(p!=NULL &&node==p->right){
        node=p;
        p=p->parent;
    }
    return p;
}

template <class Key,class Comp>
AVLNode<Key,Comp> *AVLTree<Key,Comp>::pred(AVLNode<Key,Comp> *node)
{
    if(node==NULL)
        return node;
    if(node->left)
        return _max(node->left);
    AVLNode<Key,Comp> *p=node->parent;
    while(p!=NULL &&node==p->left){
        node=p;
        p=p->parent;
    }
    return p;
}

template <class Key,class Comp>
AVLNode<Key,Comp> * AVLTree<Key,Comp>::_find_nth(AVLNode<Key,Comp> *root,int index)
{
    if(root==NULL || index> root->size || index<1)
        return NULL;
    int r=AVLNode<Key,Comp>::getSize(root->left)+1;
    if(r==index)
        return root;
    if(index<r){
        return _find_nth(root->left,index);
    }else{
        return _find_nth(root->right,index-r);
    }
}

template <class Key,class Comp>
AVLNode<Key,Comp> * AVLTree<Key,Comp>::nth(int index)
{
    return _find_nth(root,index);
}
