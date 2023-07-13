/*
Binary Search Tree is implemented.
Chap. 4.3, p. 132
*/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define SPACE 4


template <typename Comparable>
class BinarySearchTree
{
    public:
        BinarySearchTree(); // zero-parameter constructor 
        BinarySearchTree( const BinarySearchTree & rhs); // copy constructor
        BinarySearchTree( BinarySearchTree && rhs); // move constructor
        ~BinarySearchTree(); //destructor

        const Comparable & findMin() const;
        const Comparable & findMax() const;
        bool contains ( const Comparable & x) const;
        bool isEmpty() const;
        void printTree( std::ostream & out = std::cout );
        
        void makeEmpty();
        void insert(const Comparable & x);
        void insert(Comparable && x);
        void remove(const Comparable & x);
        const int height() const;

        BinarySearchTree & operator= ( const BinarySearchTree & rhs) // copy assignment operator
        {
            BinarySearchTree copy = rhs;
            std::swap(*this, copy);
            return *this;
        }
        BinarySearchTree & operator= (BinarySearchTree && rhs) // move assignment operator
        {
            std::swap(root,rhs.root);
            return *this;
        }


    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const Comparable & theElement, BinaryNode * lt, BinaryNode * rt)
            : element{ theElement }, left{ lt }, right{ rt } {}

            BinaryNode(Comparable && theElement, BinaryNode * lt, BinaryNode * rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } {}
        };

        BinaryNode * root;

        //                  BinaryNode * & t 
        // Passing the reference to pointer (to the BinaryNode)
        // That means we want to change the pointer of the BinaryNode.
        // That imples that the recursive method will be used.
        // First the "root" points to the root of the tree,
        // and it becomes to point another node(root of subtree).
        // and this is repeated until target node is reached.
        // That is, the actual change of tree(insert,remove) is supposed to be happen.
        // Otherwise, passing only the pointer of node is enough(even for the recursive procesure).

        void insert( const Comparable & x, BinaryNode * & t);
        void insert( Comparable && x, BinaryNode * & t);
        void remove (const Comparable & x, BinaryNode * & t); 
        const int height( BinaryNode * t) const;
        BinaryNode * findMin( BinaryNode * t) const; // not call-by-ref. --> not going to change the value of parameter(starting BinaryNode for FindMax) 
        BinaryNode * findMax( BinaryNode * t) const; // "const" also implies that we are not goint to change any value. 
        bool contains(const Comparable & x, BinaryNode * t) const;
        void makeEmpty(BinaryNode * & t);
        void printTree( BinaryNode * t, std::ostream & out, int space);
        BinaryNode * clone ( BinaryNode *t) const;
};

#endif