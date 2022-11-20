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
    static void findBalance(AVLNode<Key, Value>* node);
    static void removeFix(AVLNode<Key, Value>* node, int diff);

};
template<class Key, class Value>
void AVLTree<Key, Value>::findBalance(AVLNode<Key, Value>* node) {
    if (node = nullptr) {
        return;
    }
    int8_t balance = (int8_t)BinarySearchTree<Key, Value>::calculateTreeHeight(node->getRight) 
    - BinarySearchTree<Key, Value>::calculateTreeHeight(node->getLeft);
    if ()
}

// Right rotation function
template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* node) {
  // this rotation function is simple and only handles the rotation of
  // a single node given but the overview concept is that we will call 
  // these functions on the nodes needed to perform the zigzig or zigzag

  // If we right rotate on a parent then this means promote the child of p as 
  // a child of the grandparent and then demote the parent to a child of its 
  // child node 

  // OKOK Fuck all this noise for right rotate we are concered for the child 
  // right subtree here so we can make the correct adjustments
  auto parent = node->getParent();
  auto rightChild = node->getRight();
  auto leftChild = node->getLeft();
  // need to account for root case
  if (BinarySearchTree<Key, Value>::root_ == static_cast<Node<Key, Value>*>(node)) {
    BinarySearchTree<Key, Value>::root_ = leftChild;
  }
  // need to check if parent has a parent aka g 
  // if so this means that g must point to child 
  if (grandparent != nullptr && parent->getLeft() == node) {
    node->getParent()->setLeft(leftChild);
    // can we just node swap then swap so that the p is right child of n
    nodeSwap(node, parent);
  }
  
}

// Left rotate function 
template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* node) {
    // for leftR we need to worry about the left child subtree so we 
   // can make the correct pointer adjustments 
   auto parent = node->getParent();
   auto child = node->getRight();
   auto xnode = child->getLeft();

   child->setLeft(node);
   node->setRight(xnode);
   // child is the most volatile node in this situation so 
   // this means we can promote child and make the adjustments
   if (parent == nullptr) {
      // this means we are at the root and need to change
      BinarySearchTree<Key, Value>::root_ = node;
   }
   else {
      if (parent->getLeft() == node) {
          parent->setLeft(xnode);
      }
      else {
          parent->setRight(xnode);
      }
   }
   
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
    Key key = keyValuePair.first;
    Value value = keyValuePair.second;

    if (empty()) {
      // this means we can just insert into the tree
      this->root_ = new AVLNode<Key, Value> (key, value, nullptr);
    }
    else {
      // we have work to do, need to iterate through and find place for new item
      AVLNode<Key, Value>* root = this->root_;
      while (root != nullptr) {
          Key rootKey = root->getKey();
          if (key < rootKey) {
              // this means that we need to traverse to the left subtree
              AVLNode<Key, Value>* leftNode = root->getLeft();
              if (leftNode != nullptr) {
                  root = leftNode;
              }
              // if there is no left node that means that this is where the inserted 
              // noded needs to be placed 
              else {
                  // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
                  root->setLeft(new AVLNode<Key, Value> (key, value, root)); // the root should be the parent in this case here
                  return;
              }
          }
          else if (key > rootKey) {
              // traverse right
              AVLNode<Key, Value>* rightNode = root->getRight();
              if (rightNode != nullptr) {
                  root = rightNode;
              }
              else {
                  // Node<Key, Value>* freshNode = new Node<Key, Value>* (key, value, root);
                  root->setRight(new AVLNode<Key, Value> (key, value, root));
                  return;
              }
          }
          else {
              // the key is already in the tree and needs to be overwritten with the current value
              root->setValue(value);
              return;
          }
      }
  }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // Find the node by walking the tree
    AVLNode<Key, Value>* currNode = this->root_;
    Node<Key, Value>* parentNode = nullptr;
    int diff;
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
            // if the node has two children swap with the predecessor and then 
            // remove that node aka same as bst
            if (currNode->getRight() != nullptr && currNode->getLeft() != nullptr) {
                // we swap with predecessor 
                Node<Key, Value>* bestNode = predecessor(currNode);
                // the appropriate parents have been set for the nodes here 
                // so there is no need to make any changes to them 
                // Note: parentNode currently points to the parent of current
                // location and we need to update accordingly when swapped
                nodeSwap(currNode, bestNode);
                parentNode = currNode->getParent();
                Node<Key, Value>* childNode;
                // no children on swap case
                if (currNode->getLeft() == nullptr && currNode->getRight() == nullptr) {
                    childNode = nullptr;
                }
                // otherwise then the node must have at least one node by definition
                else if (currNode->getLeft() != nullptr) {
                    childNode = currNode->getLeft();
                }
                else if (currNode->getRight() != nullptr) {
                    childNode = currNode->getRight();
                }
                if (parentNode == nullptr) {
                    this->root_ = childNode;
                }
                else {
                    if (parentNode->getLeft() == currNode) {
                        // do something here
                        // delete currNode;
                        parentNode->setLeft(childNode);
                        diff = 1;
                    }
                    else {
                        // do the opposite
                        // delete currNode;
                        parentNode->setRight(childNode);
                        diff = -1;
                    }
                    // delete currNode;
                }
                if (childNode != nullptr) {
                    childNode->setParent(parentNode);
                }
                delete currNode;
                currNode = nullptr;
            }
            else if (parentNode == nullptr) {
                // if no parent ie root node removal case
                if (currNode->getLeft() != nullptr) {
                    // Can I set the root to the next node then
                    // delete the currNode so that it removes?
                    this->root_ = currNode->getLeft();
                    // reset the parent of the node
                    // all other nodes are fine with the reassignment
                    root_->setParent(nullptr);
                    delete currNode;
                    currNode = nullptr;
                }
                else if (currNode->getRight() != nullptr) {
                    this->root_ = currNode->getRight();
                    root_->setParent(nullptr);
                    delete currNode;
                }
                else {
                    // set root to null then return 
                    this->root_ = nullptr;
                    return; // easy with a single node tree
                }
            }
            else if (parentNode->getLeft() == currNode) {
                diff = 1;
                if (currNode->getLeft() != nullptr) {
                    parentNode->setLeft(currNode->getLeft());
                }
                else {
                    parentNode->setRight(currNode->getRight());

                }
                delete currNode;
                currNode = nullptr;
            }
            else if (parentNode->getRight() == currNode) {
                diff = -1;
                if (currNode->getLeft() != nullptr) {
                    parentNode->setLeft(currNode->getLeft());
                }
                else {
                    parentNode->setRight(currNode->getRight());
                }
                delete currNode;
                currNode = nullptr;
            }
        }
        removeFix(parentNode, diff);
        return; // work is all done here 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff) {
    if (node == nullptr) {
        return;
    }
    auto parent = node->getParent();
    int ndiff;
    if (parent != nullptr) {
        if (parent->getLeft() == node) {
            ndiff = 1;
        }
        else if (parent->getRight() == node) {
            ndiff = -1;
        }
    }
    // Case 1
    if (node->getBalance() + diff == -2) {
        auto child = node->getLeft();
        // case 1a
        if (child->getBalance() == -1) {
            // zig zag case here 
            rightRotate(node);
            node->setBalance(0);
            child->setBalance(0);
            removeFix(parent, ndiff);
        }
        // case 1b
        else if (child->getBalance() == 0) {
            // zig zig case
            rightRotate(node);
            node->setBalance(-1);
            child->setBalance(1);
            return;
        }
        // case 1c 
        else if (child->getBalance() == 1) {
            auto g = child->getRight();
            leftRotate(child);
            rightRotate(node);
            if (g->getBalance() == 1) {
                node->setBalance(0);
                child->setBalance(-1);
                g->setBalance(0);
            }
            else if (g->getBalance() == 0) {
                node->setBalance(0);
                child->setBalance(0);
                g->setBalance(0);
            }
            else if (g->getBalance() == -1) {
                node->setBalance(1);
                child->setBalance(0);
                g->setBalance(0);
            }
            removeFix(parent, ndiff);
        }
    }
    // Case 2
    else if (node->getBalance() + diff == -1) {
        node->setBalance(-1);
        return;
    }
    // Case 3
    else if (node->getBalance() + diff == 0) {
        node->setBalance(0);
        removeFix(parent, ndiff);
    }
    // Case 4
    else if (node->getBalance() + diff == 2) {
        auto child = node->getRight();
        // case 4a
        if (child->getBalance() == 1) {
            // zig zag case here 
            leftRotate(node);
            node->setBalance(0);
            child->setBalance(0);
            removeFix(parent, ndiff);
        }
        // case 4b
        else if (child->getBalance() == 0) {
            // zig zig case
            leftRotate(node);
            node->setBalance(1);
            child->setBalance(-1);
            return;
        }
        // case 4c 
        else if (child->getBalance() == 1) {
            auto g = child->getLeft();
            rightRotate(child);
            leftRotate(node);
            if (g->getBalance() == -1) {
                node->setBalance(0);
                child->setBalance(1);
                g->setBalance(0);
            }
            else if (g->getBalance() == 0) {
                node->setBalance(0);
                child->setBalance(0);
                g->setBalance(0);
            }
            else if (g->getBalance() == 1) {
                node->setBalance(-1);
                child->setBalance(0);
                g->setBalance(0);
            }
            removeFix(parent, ndiff);
        }
    }
    // Case 5
    else if (node->getBalance() + diff == 1) {
        node->setBalance(-1);
        return;
    }
    // Case 6
    else if (node->getBalance() + diff == 0) {
        node->setBalance(0);
        removeFix(parent, ndiff);
    }

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
