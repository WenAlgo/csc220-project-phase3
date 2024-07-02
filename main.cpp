#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides NULL, srand, rand
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        // Parameterized Constructor
        Node(int value) {
            data = value;
            left = right = NULL;
        }
};

class BinaryTree {
    public:
        Node* root;
    
        BinaryTree() { root = NULL; }            //constructor

//function declarations
        void insert(Node*& root, int value);
        void printPreOrder(Node* root);
        void printInOrder(Node* root);
        void printPostOrder(Node* root);
        int countNodes(Node* root);
        int countLeaves(Node* root);
        Node* generateNewTree(Node* root);
};

// Function to generate a new tree with doubled values of each node
Node* BinaryTree::generateNewTree(Node* root) {
    // Base case
    if (root == NULL) 
        return NULL;
    
    // Create a new node with doubled value
    Node* newRoot = new Node((root->data) * 2);
    
    // Recursively generate new trees for the left and right subtrees
    newRoot->left = generateNewTree(root->left);
    newRoot->right = generateNewTree(root->right);
    
    return newRoot;
}

//insert function
void BinaryTree::insert(Node*& root, int value){            
    if (root==NULL){                  //creates a root if the tree is empty
        root=new Node(value);
        return;
    }
    if (root->data==value){            //makes sure there are no duplicates
        return;
    }
    if (value<root->data){            //inserts new node to the left if it's < it's parent
        insert(root->left, value);
    }
    else {                             //inserts new node to the right if it's > then it's parent
        insert(root->right, value);
    }
}

// Pre, In, and Post print functions
void BinaryTree::printPreOrder(Node *root){
    if (!root){                        //Base case
        return;
    }
    cout<<root->data<<"  ";            //prints the root first
    printPreOrder(root->left);         //traverses left, only goes to the next step after the return is called
    printPreOrder(root->right);        //then traverses right. After this, that node is done and returns back to the last called node on the stack
}
//The same goes for the next 2 print functions but in different orders

void BinaryTree::printInOrder(Node *root){
    if (!root){
        return;
    }
    printInOrder(root->left);
    cout<<root->data<<"  ";
    printInOrder(root->right);    
}

void BinaryTree::printPostOrder(Node *root){
    if (!root){
        return;
    }    
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout<<root->data<<"  "; 
}

int BinaryTree::countNodes(Node * root) {
    //base case
    if (root == NULL) {
        return 0;
    }

    //recursion to count all nodes
    return (countNodes(root->left) + countNodes(root->right) + 1);
}

int BinaryTree::countLeaves(Node* root) {
    //base cases
    if (root == NULL) {
        return 0;
    }
    else if ((root->left == NULL) && (root->right == NULL)) {           //check if its a leaf
        return 1;
    }
    else {
        return (countLeaves(root->left) + countLeaves(root->right));    //recursion to count all leaf
    }
}

//MAIN
int main() {
    // Seed the random number generator to get a different sequence each time
    srand(time(0));

    // Set N to a random number from 1 to 20
    int N = rand() % 20 + 1;
    
    // Generate a tree with N random nodes 
    BinaryTree tree;
    Node* root = NULL;
    for (int i = 0; i < N; ++i) {
        // Set the value of the nodes to random numbers from 1 to 40
        int value = rand() % 40 + 1;
        tree.insert(root, value);
    }

    int choice;
    do {
        // Display menu
        cout << "Menu:" << endl;
        cout << "1. Insert new number" << endl;
        cout << "2. Print the tree" << endl;
        cout << "3. Count the nodes" << endl;
        cout << "4. Count the leaves" << endl;
        cout << "5. Generate new tree" << endl;
        cout << "6. Exit" << endl;
        
        cout << "Enter your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1: {
                // Insert new number
                int value;
                cout << "Enter a new number to insert: ";
                cin >> value;
                tree.insert(root, value);
                break;
            }
            case 2: {
                // Print the tree in preorder, inorder, and postorder
                cout<<endl<<"Pre-Order: ";
                tree.printPreOrder(root);
                cout<<endl<<"In-Orer: ";
                tree.printInOrder(root);
                cout<<endl<<"Post-Order: ";
                tree.printPostOrder(root);
                cout<<endl<<endl;
                break;
            }       
            case 3:
                // Count the nodes
                cout << "Total nodes: " << tree.countNodes(root) << endl;
                break;
            case 4:
                // Count the leaves
                cout << "Total leaves: " << tree.countLeaves(root) << endl;
                break;
            case 5: {
                // Generate new tree with doubled values
               Node* newTree = tree.generateNewTree(root);
                cout<<endl<<"Pre-Order: ";
                tree.printPreOrder(newTree);
                cout<<endl<<"In-Orer: ";
                tree.printInOrder(newTree);
                cout<<endl<<"Post-Order: ";
                tree.printPostOrder(newTree);
                cout<<endl<<endl;
                break;
            }                
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
