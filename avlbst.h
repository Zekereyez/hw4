#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    static AVLNode<Key, Value>* blah ();
    static void rightRotate(AVLNode<Key, Value>* node);
    static void leftRotate(AVLNode<Key, Value>* node);


};
// Right rotation function
template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* node) {
  // this rotation function is simple and only handles the rotation of
  // a single node given but the overview concept is that we will call 
  // these functions on the nodes needed to perform the zigzig or zigzag

  // If we right rotate on a parent then this means promote the child of p as 
  // a child of the grandparent and then demote the parent to a child of its 
  // child node 
  auto parent = node->getParent();
  auto rightChild = node->getRight();
  auto leftChild = node->getLeft();
  // need to check if parent has a parent aka g 
  // if so this means that g must point to child 
  if (parent->getParent() != nullptr && parent->getLeft() == node) {
    node->getParent()->setLeft(leftChild);
    // can we just node swap then swap so that the p is right child of n
    nodeSwap(node, parent);
    
  }
}

// Left rotate function 
template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* node) {
   
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO - From bst
    // For insert we need to check the where the inserted KVP needs to be easy stuff
    // Extract information for the creation of new node 
  //   Key key = keyValuePair.first;
  //   Value value = keyValuePair.second;

  //   if (empty()) {
  //     // this means we can just insert into the tree
  //     root_ = new Node<Key, Value> (key, value, nullptr);
  //   }
  //   else {
  //     // we have work to do, need to iterate through and find place for new item
  //     Node<Key, Value>* root = root_;
  //     while (root != nullptr) {
  //         Key rootKey = root->getKey();
  //         if (key < rootKey) {
  //             // this means that we need to traverse to the left subtree
  //             Node<Key, Value>* leftNode = root->getLeft();
  //             if (leftNode != nullptr) {
  //                 root = leftNode;
  //             }
  //             // if there is no left node that means that this is where the inserted 
  //             // noded needs to be placed 
  //             else {
  //                 // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
  //                 root->setLeft(new Node<Key, Value> (key, value, root)); // the root should be the parent in this case here
  //                 return;
  //             }
  //         }
  //         else if (key > rootKey) {
  //             // traverse right
  //             Node<Key, Value>* rightNode = root->getRight();
  //             if (rightNode != nullptr) {
  //                 root = rightNode;
  //             }
  //             else {
  //                 // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
  //                 root->setRight(new Node<Key, Value> (key, value, root));
  //                 return;
  //             }
  //         }
  //         else {
  //             // the key is already in the tree and needs to be overwritten with the current value
  //             root->setValue(value);
  //             return;
  //         }
  //     }
  // }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
