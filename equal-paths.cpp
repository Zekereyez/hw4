#include "equal-paths.h"
#include <algorithm>
using namespace std;


// You may add any prototypes of helper functions here
int getHeight(Node* root);


bool equalPaths(Node * root)
{
    // Add your code below
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

