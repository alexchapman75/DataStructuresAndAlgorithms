#include <iostream>
using namespace std;

// Step 1: Define the BST Node Structure
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Step 3: Helper Function for In-order Successor
Node* findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Step 2: Implement the Remove Function
Node* removeNode(Node* root, int key) {
    if(root == nullptr) return nullptr;

    if(key < root->data) {
        root->left = removeNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = removeNode(root->right, key);
    }
    else {
        //Node is found, handle 3 cases
        // No children
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // One Child
        else if(root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == nullptr) {
            Node*temp = root->left;
            delete root;
            return temp;
        }

        // Two children
        else {
            Node* successor = findMin(root->right);
            root->data = successor->data; //copy vals
            root->right = removeNode(root->right, successor->data);
        }
    }
    return root;
}

// Step 4: Implement BST Traversal to Verify Correctness
void inorder(Node* root) {
    if(root == nullptr) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Helper: Insert a node (for building the test tree)
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}

// Helper: Free the entire tree
void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    // Step 5: Test All Removal Scenarios
    /*
        Construct the following BST:
                50
              /    \
            30      70
           /  \    /  \
         20   40  60  80
    */
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "Original BST (in-order):\n";
    inorder(root);
    cout << "\n\n";

    // Remove a leaf node (20)
    root = removeNode(root, 20);
    cout << "After removing 20:\n";
    inorder(root);
    cout << "\n\n";

    // Remove a node with one child (30)
    root = removeNode(root, 30);
    cout << "After removing 30:\n";
    inorder(root);
    cout << "\n\n";

    // Remove a node with two children (50)
    root = removeNode(root, 50);
    cout << "After removing 50:\n";
    inorder(root);
    cout << "\n";

    freeTree(root);
    return 0;
}
