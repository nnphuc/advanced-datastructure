#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "header.h"

template <class Key,class Comp=less<Key>>
struct  AVLNode
{
    Key key;
    int height;
    int size;
    AVLNode *left,*right,*parent;
    AVLNode ();
    AVLNode(Key);
    ~AVLNode();
    static int getHeight(AVLNode *);
    static int getBalance(AVLNode *);
    static int getSize(AVLNode *);
    void updateHeight();
    void updateSize();
    static AVLNode* rightRotate(AVLNode *node);
    static AVLNode* leftRotate(AVLNode *node);

};

template <class Key,class Comp=less<Key>>
struct AVLTree
{

    AVLNode<Key,Comp> *root;
    AVLTree();
    ~AVLTree();
    AVLNode<Key,Comp> * insert(Key);
    int size();
    void erase(Key);
    AVLNode<Key,Comp> *min();
    AVLNode<Key,Comp> *max();
    AVLNode<Key,Comp> *find(Key);
    AVLNode<Key,Comp>* succ(AVLNode<Key,Comp> *node);
    AVLNode<Key,Comp>* pred(AVLNode<Key,Comp> *node);
    AVLNode<Key,Comp>* nth(int index);

private:
    int m_size;
    AVLNode<Key,Comp> * lastInsert=NULL;
    AVLNode<Key,Comp> * _insert(AVLNode<Key,Comp> *root,Key key);
    AVLNode<Key,Comp>* _delete(AVLNode<Key,Comp> *root,Key key);
    AVLNode<Key,Comp> *_min(AVLNode<Key,Comp> *root);
    AVLNode<Key,Comp> *_max(AVLNode<Key,Comp> *root);
    AVLNode<Key,Comp>* _find(AVLNode<Key,Comp> *root,Key key);
    AVLNode<Key,Comp>* _find_nth(AVLNode<Key,Comp> *root,int index);
};

#endif // AVLTREE_H_INCLUDED
