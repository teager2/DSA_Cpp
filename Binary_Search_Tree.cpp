#include "Binary_Search_Tree.h"


// public

// constructor
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr} {};

// copy constructor
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree & rhs) : root{nullptr} 
{
    root = clone( rhs. root ); // eventually, proper pointer to the root is everything.
};

// move constructor
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( BinarySearchTree && rhs) : root{nullptr} 
{
    root = clone( rhs.root ); 
    makeEmpty(rhs); // rhs is not needed.
};

//destructor
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() 
{
    makeEmpty();
};

template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
    BinaryNode * minNode = findMin(root);
    return minNode->element;
}


template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
    BinaryNode * maxNode = findMax(root);
    return maxNode->element;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains( const Comparable & x) const 
{
    return contains(x,root);
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const 
{
    return root == nullptr; // empty tree
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree( std::ostream & out ) 
{
    printTree(root,out,0);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty() 
{
    makeEmpty(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x ) 
{
    insert(x,root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable && x ) 
{
    insert(x,root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x ) 
{
    remove(x,root);
}

template<typename Comparable>
const int BinarySearchTree<Comparable>::height( ) const 
{
    return height(root);
}

// private


template<typename Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode * & t ) 
{
    //recursive
    if(t == nullptr) // empty (sub)tree
        t = new BinaryNode{x,nullptr,nullptr};
    else if(x < t->element)
        insert (x, t->left);
    else if(x > t->element)
        insert (x, t->right);
    else 
        ; // duplicate; do nothing
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable && x, BinaryNode * & t ) 
{
    //recursive
    if(t == nullptr) // empty (sub)tree
        t = new BinaryNode{std::move(x),nullptr,nullptr};
    else if(x < t->element)
        insert (x, t->left);
    else if(x > t->element)
        insert (x, t->right);
    else 
        ; // duplicate; do nothing
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode * & t)
{
    
    if ( t == nullptr ) // item not found; do nothing
        return; // very important to implement this base case.

    if ( x < t -> element) // item is on the left side
        remove(x,t->left);
    else if( x > t->element) // item is on the right side
        remove(x,t->right);
    // 4 cases. (the cases of node to be removed)
    // case 1. leaf node
        //  left child is nullptr
        //  make t nullptr and reclaim t (simple!)
    // case 2. has one left child node
        //  left child is not nullptr
        //  connect t->left with t's parent by substitute t with t->left
        //  and reclaim t
    // case 3. has one right child node
        //  left child is nullptr
        //  connect t->right with t's parent by substitute t with t->right
        //  and reclaim t
    // case 4. has two children nodes
        //  substitue t's element with the max element in right subtree.
        //  and "remove" that node with max element.

    else if (t->left != nullptr && t->right != nullptr) // case 4.
    {
        t->element = findMax(t->right)->element;
        remove(t->element,t->right);
    }
    else // case 1,2,3
    {
        BinaryNode * oldNode = t;
        t = (t->left == nullptr) ? t->right : t->left;
        delete oldNode;
    }
}

template<typename Comparable>
const int BinarySearchTree<Comparable>::height( BinaryNode * t) const
{
    if(t == nullptr)
        return 0;
    return 1 + std::max(height(t->left),height(t->right));
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin( BinaryNode * t) const
{
    // Going left as much as you can. that's the min node

    // recursive
    // if(t == nullptr) // empty node
    //     return nullptr;
    // if( t->left == nullptr )
    //     return t;
    // return findMin(t->left); //tail recursion

    // while
    if (t != nullptr) // not empty node
        while (t->left != nullptr)
            t = t->left;
    return t;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax( BinaryNode * t) const
{
    // Going left as much as you can. that's the min node

    // recursive
    // if(t == nullptr) // empty node
    //     return nullptr;
    // if( t->right == nullptr )
    //     return t;
    // return findMin(t->right); //tail recursion

    // while loop
    if (t != nullptr) // not empty node
        while (t->right != nullptr)
            t = t->right;
    return t;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains( const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr) //empty node
        return false;
    else if (x < t->element) // it's in left subtree
        return contains(x,t->left);
    else if (x > t->element)
        return contains(x, t->right);
    else
        return true; //match
}


template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode * & t)
{
    if (t != nullptr) // no need to consider both left or right cases.
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree( BinaryNode * t, std::ostream & out, int space)
{
    //print by inorder traversal 

    if (t == nullptr)
        return;
    space += SPACE;
    printTree(t->left,out,space);

    // out<<"\n";
    for(int i = SPACE; i<space;++i)
        out<<" ";
    out << t->element << "\n";

    printTree(t->right,out,space);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone( BinaryNode * t) const
{

    if(t==nullptr)
        return nullptr;
    else 
        return new BinaryNode{t->element,clone(t->left),clone(t->right)};
}