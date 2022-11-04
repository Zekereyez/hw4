#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* internalFindHelper(Node<Key, Value>* root, const Key& k) const;
    void removeHelper(const Key& key, Node<Key, Value>* parentNode = nullptr);
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    static Node<Key, Value>* getLeftMostChild(Node<Key, Value>* node);
    static Node<Key, Value>* getRightMostChild(Node<Key, Value>* node);
    static Node<Key, Value>* getRightMostParent(Node<Key, Value>* node);
    static Node<Key, Value>* getLeftMostParent(Node<Key, Value>* node);
    static int calculateTreeHeight(Node<Key, Value>* root);
    static bool isBalancedHelper(Node<Key, Value>* root);
    static void clearHelper(Node<Key, Value>* root);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr)
{
    // I'm smarter...
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL)
{
    // I am better...

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (this->current_ == rhs.current_) {
        return true;
    }
    else {
        return false;
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (this->current_ != rhs.current_) {
        return true;
    }
    else {
        return false;
    }
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // need to increment the current iterator and then return the object by reference
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(NULL)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO - Probably call clear or sum
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // For insert we need to check the where the inserted KVP needs to be easy stuff
    // Extract information for the creation of new node 
    Key key = keyValuePair.first;
    Value value = keyValuePair.second;

    if (empty()) {
        // this means we can just insert into the tree
        root_ = new Node<Key, Value> (key, value, nullptr);
    }
    else {
        // we have work to do, need to iterate through and find place for new item
        Node<Key, Value>* root = root_;
        while (root != nullptr) {
            Key rootKey = root->getKey();
            if (key < rootKey) {
                // this means that we need to traverse to the left subtree
                Node<Key, Value>* leftNode = root->getLeft();
                if (leftNode != nullptr) {
                    root = leftNode;
                }
                // if there is no left node that means that this is where the inserted 
                // noded needs to be placed 
                else {
                    // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
                    root->setLeft(new Node<Key, Value> (key, value, root)); // the root should be the parent in this case here
                    return;
                }
            }
            else if (key > rootKey) {
                // traverse right
                Node<Key, Value>* rightNode = root->getRight();
                if (rightNode != nullptr) {
                    root = rightNode;
                }
                else {
                    // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
                    root->setRight(new Node<Key, Value> (key, value, root));
                    return;
                }
            }
            else {
                // the key is already in the tree and needs to be overwritten with the current key
                root->setValue(value);
                return;
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // Difficult method for this damn bst
    // Node<Key, Value>* foundNode = internalFind(key);
    // if (foundNode == nullptr) {
    //     return;
    // }
    // // this means that the node is valid and we can perform the 
    // // swap and deletion of the node 
    // nodeSwap(foundNode, predecessor(foundNode)); // a predecessor is a leaf node ie no children
    // delete foundNode;


    Node<Key, Value>* currNode = root_;
    Node<Key, Value>* parentNode = nullptr;
    while (currNode != nullptr) {
        if (key < currNode->getKey()) {
            parentNode = currNode;
            currNode = currNode->getLeft();
        }
        else if (key > currNode->getKey()) {
            parentNode = currNode;
            currNode = currNode->getRight();
        }
        else {
            // found node but many cases now
            // case for two children 
            if (currNode->getRight() != nullptr && currNode->getLeft() != nullptr) {
                // we swap with predecessor 
                nodeSwap(currNode, predecessor(currNode));
                delete currNode;
            }
            else if (parentNode == nullptr) {
                // if no parent ie root node removal case
                if (currNode->getLeft() != nullptr) {
                    currNode->setValue(currNode->getLeft()->getKey());
                    currNode->setRight(currNode->getLeft()->getRight());
                    currNode->setLeft(currNode->getLeft()->getLeft());
                }
                else if (currNode->getRight() != nullptr) {
                    currNode->setValue(currNode->getRight()->getKey());
                    currNode->setLeft(currNode->getRight()->getLeft());
                    currNode->setRight(currNode->getRight()->getRight());
                }
                else {
                    // do I need to delete the root? this would delete the bst?
                    // currNode->setValue(nullptr);
                    root_ = nullptr;
                    return; // no work to do with a single node tree
                }
            }
            else if (parentNode->getLeft() == currNode) {
                if (currNode->getLeft() != nullptr) {
                    parentNode->setLeft(currNode->getLeft());
                }
                else {
                    parentNode->setRight(currNode->getRight());
                }
            }
            else if (parentNode->getRight() == currNode) {
                if (currNode->getLeft() != nullptr) {
                    parentNode->setLeft(currNode->getLeft());
                }
                else {
                    parentNode->setRight(currNode->getRight());
                }
            }
        }
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(const Key& key, Node<Key, Value>* parentNode = nullptr) {

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current->getLeft() != nullptr) {
        return getRightMostChild(current->getLeft());
    }
    return getLeftMostParent(current);
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // Get the successor of the given node ie leftmost node of the 
    // right subtree
    // Node<Key, Value>* currNode = current;
    if (current->getRight() != nullptr) {
        return getLeftMostChild(current->getRight());
    }
    // otherwise we just return the right most parent
    return getRightMostParent(current);
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // Idea: we can recurse all the way to the leaf nodes of the tree
    // and then set those nodes to null and then attack each level of the 
    // tree from the most depth to the centralized root that way there is no 
    // memory leaks or nodes left out when clearing the tree - most effective
    clearHelper(root_);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* root) {
    if (root == nullptr) {
        return;
    }
    else {
        clearHelper(root->getLeft());
        clearHelper(root->getRight());
        delete root;
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // This is the left most node of the tree
    // check if the tree is empty first
    if (empty()) {
        return nullptr;
    }
    // Just use the leftMostChild function here
    Node<Key, Value>* smallestNode = root_;
    return getLeftMostChild(smallestNode);
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getLeftMostChild(Node<Key, Value>* node) {
    // Looping here is more ideal since it will always run 
    // in n time but we are doing this in constant space 
    // rather than n space with recursive calls
    Node<Key, Value>* currNode = node;
    while (currNode->getLeft() != nullptr) {
        currNode = currNode->getLeft();
    }
    return currNode;
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getRightMostChild(Node<Key, Value>* node) {
    Node<Key, Value>* currNode = node;
    while (currNode->getRight() != nullptr) {
        currNode = currNode->getRight();
    }
    return currNode;
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getLeftMostParent(Node<Key, Value>* node) {
    Node<Key, Value>* currNode = node;
    while (currNode->getParent() != nullptr && currNode->getParent()->getLeft() == currNode) {
        currNode = currNode->getParent();
    }
    return currNode->getParent();
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getRightMostParent(Node<Key, Value>* node) {
    Node<Key, Value>* currNode = node;
    while (currNode->getParent() != nullptr && currNode->getParent()->getRight() == currNode) {
        currNode = currNode->getParent();
    }
    return currNode->getParent();
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* currNode = root_;
    return internalFindHelper(currNode, key);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFindHelper(Node<Key, Value>* root, const Key& key) const {
    if (root->getKey() == key) {
        return root;
    }
    if (key < root->getKey() && root->getLeft() != nullptr) {
        return internalFindHelper(root->getLeft(), key);
    }
    else if (key > root->getKey() && root->getRight() != nullptr) {
        return internalFindHelper(root->getRight(), key);
    }
    else {
        return nullptr; // the key does not exist
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{   

    // call isBalancedHelper
    return isBalancedHelper(root_);
    
}

template<typename Key, typename Value>
bool isBalancedHelper(Node<Key, Value>* root) {
    // implement the same thing as in the lab
    if (root == NULL) {
		return true;
	}

	// Get the heights of the left and right subtrees 
	int leftTree = calculateHeightIfBalanced(root->getLeft());
	int rightTree = calculateHeightIfBalanced(root->getRight());
	// Determine if this node is balanced! If not return false!
	int bal = rightTree - leftTree;
	if (bal > 1 || bal < -1 ) {
		return false;
	}
	// Check if there are subtrees under us
	// Are they balanced?
	bool l = isBalancedHelper(root->getLeft());
	bool r = isBalancedHelper(root->getRight());

	// If all nodes are balanced return true!
	if (l && r) {
		return true;
	}
	else {
		return false;
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateTreeHeight(Node<Key, Value>* root) {
    // Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) {
        return 0;
    }
	// counts height
	else {
		return 1 + std::max(calculateHeightIfBalanced(root->getLeft()), 
        calculateHeightIfBalanced(root->getRight()));
	}
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
