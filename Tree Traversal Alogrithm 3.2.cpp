#include <iostream>
#include <iomanip>
using namespace std;

// Define the structure for a node in the BST
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Error: Memory allocation failed.\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a node in the BST
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    return root;
}

// Find the minimum value node in the BST
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node from the BST
Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Preorder traversal
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Display the tree with arrows
void display(Node* node, int level) {
    if (node == NULL) return;

    // Print right subtree first (for visual representation)
    display(node->right, level + 1);

    // Print current node value
    cout << string(level * 4, ' ') << node->data;

    // Print arrows for children
    if (node->left) {
        cout << "\n" << string(level * 4 + 2, ' ') << "<-- " << node->left->data; // Arrow pointing left
    }
    if (node->right) {
        cout << "\n" << string(level * 4 + 2, ' ') << "--> " << node->right->data; // Arrow pointing right
    }

    cout << "\n";

    // Print left subtree
    display(node->left, level + 1);
}

// Display the tree structure graphically
void graphicalDisplay(Node* root, int space = 0, int height = 10) {
    if (root == NULL) return;

    space += height;

    // Process right child first
    graphicalDisplay(root->right, space);

    // Print current node after space
    cout << endl;
    for (int i = height; i < space; i++) cout << " ";
    cout << root->data << "\n";

    // Process left child
    graphicalDisplay(root->left, space);
}

int main() {
    Node* root = NULL;
    int initialNodes, value;

    // Welcome message and program introduction
    cout << "==============================================\n";
    cout << "         Welcome to the Binary Search Tree Program         \n";
    cout << "==============================================\n\n";
    
    cout << "This program allows you to create and interact with a Binary Search Tree (BST).\n";
    cout << "You can insert, delete, and display nodes in various traversal orders.\n\n";

    // Step 1: Initial BST setup
    cout << "---------- Step 1: Initial Tree Setup ----------\n";
    cout << "Enter the number of initial nodes to insert: ";
    cin >> initialNodes;

    // Insert each initial node value
    for (int i = 0; i < initialNodes; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> value;
        root = insertNode(root, value);
    }

    // Main menu for BST operations
    int choice;
    while (true) {
        cout << "\n\n==================== BST Operations Menu ====================\n";
        cout << "1. Insert a new node\n";
        cout << "2. Delete an existing node\n";
        cout << "3. Display Inorder Traversal\n";
        cout << "4. Display Preorder Traversal\n";
        cout << "5. Display Postorder Traversal\n";
        cout << "6. Display Tree Structure\n";  // Display tree structure with arrows
        cout << "7. Display Graphical Tree Structure\n"; // New option for graphical display
        cout << "8. Exit the program\n";
        cout << "-------------------------------------------------------------\n";
        cout << "Please select an option (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- Insert Node ---\n";
                cout << "Enter the value to insert: ";
                cin >> value;
                root = insertNode(root, value);
                cout << "Node with value " << value << " has been successfully inserted.\n";
                break;

            case 2:
                cout << "\n--- Delete Node ---\n";
                cout << "Enter the value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Node with value " << value << " has been deleted if it existed.\n";
                break;

            case 3:
                cout << "\n--- Inorder Traversal ---\n";
                cout << "Tree (Inorder): ";
                inorder(root);
                cout << "\n";
                break;

            case 4:
                cout << "\n--- Preorder Traversal ---\n";
                cout << "Tree (Preorder): ";
                preorder(root);
                cout << "\n";
                break;

            case 5:
                cout << "\n--- Postorder Traversal ---\n";
                cout << "Tree (Postorder): ";
                postorder(root);
                cout << "\n";
                break;

            case 6:
                cout << "\n--- Tree Structure ---\n";
                display(root, 0); // Display the tree with arrows
                break;

            case 7:
                cout << "\n--- Graphical Tree Structure ---\n";
                graphicalDisplay(root); // Display graphical representation of the tree
                break;

            case 8:
                cout << "\nThank you for using the Binary Search Tree Program. Goodbye!\n";
                return 0;

            default:
                cout << "\nInvalid option. Please enter a number between 1 and 8.\n";
        }
    }
}
