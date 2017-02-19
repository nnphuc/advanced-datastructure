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
    AVLNode<Key,Comp> *p=x->parent,*y=x->left,*B=y->right;
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
    AVLNode<Key,Comp> *p=x->parent,*y=x->right,*B=y->left;
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




