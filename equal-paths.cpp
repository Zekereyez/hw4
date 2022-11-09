#include "equal-paths.h"
#include <algorithm>
using namespace std;


// You may add any prototypes of helper functions here
int getHeight(Node* root);
bool equalPathsHelper(Node * root);


bool equalPaths(Node * root)
{
    // Add your code below
    // base case
    if (root == nullptr) {
        return true;
    }
    // check if only one node exists
    else if ((root->left == nullptr) || (root->right == nullptr)) {
        // checks if the subtrees of the trees are equal ie the null node 
        // counted as true and checks if the valid node has null child nodes
        // if it doesnt then it will go on and count the nodes of the valid 
        // child node and will check if those subtrees are equal or not
        if (equalPathsHelper(root->left) && equalPathsHelper(root->right)) {
            return true;
        }
    }
    int leftTree = getHeight(root->left);
    int rightTree = getHeight(root->right);
    int pathDifference = leftTree - rightTree;
    if (pathDifference == 0) {
        return true;
    }
    else {
        return false;
    }

}

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return 1 + max(getHeight(root->left), 
        getHeight(root->right));
    }
}

bool equalPathsHelper(Node * root) {
    if (root == nullptr) {
        return true;
    }
    else if ((root->left == nullptr) && (root->right == nullptr)) {
        return true;
    }
    else {
        return false;
    }
}

