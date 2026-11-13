#include <iostream>
using namespace std;

struct Node {
    char value;
    Node *left;
    Node *right;
};

int regCount = 0;

// Create a new node
Node* createNode(char value, Node *left, Node *right) {
    Node *node = new Node();

    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

// Generate target code
int generateCode(Node *root) {

    int leftReg, rightReg, currentReg;

    if (root == NULL)
        return -1;

    // If leaf node
    if (root->left == NULL && root->right == NULL) {

        currentReg = regCount++;

        cout << "MOV R" << currentReg << ", "
             << root->value << endl;

        return currentReg;
    }

    // Generate code for left and right subtrees
    leftReg = generateCode(root->left);
    rightReg = generateCode(root->right);

    currentReg = regCount++;

    switch (root->value) {

        case '+':
            cout << "ADD R" << currentReg
                 << ", R" << leftReg
                 << ", R" << rightReg << endl;
            break;

        case '-':
            cout << "SUB R" << currentReg
                 << ", R" << leftReg
                 << ", R" << rightReg << endl;
            break;

        case '*':
            cout << "MUL R" << currentReg
                 << ", R" << leftReg
                 << ", R" << rightReg << endl;
            break;

        case '/':
            cout << "DIV R" << currentReg
                 << ", R" << leftReg
                 << ", R" << rightReg << endl;
            break;
    }

    return currentReg;
}

int main() {

    Node *a = createNode('a', NULL, NULL);
    Node *b = createNode('b', NULL, NULL);
    Node *c = createNode('c', NULL, NULL);

    Node *mul = createNode('*', b, c);

    Node *root = createNode('+', a, mul);

    cout << "Abstract Syntax Tree:\n\n";

    cout << "    +" << endl;
    cout << "   / \\" << endl;
    cout << "  a   *" << endl;
    cout << "     / \\" << endl;
    cout << "    b   c" << endl;

    cout << "\nGenerated Target Code:\n";

    generateCode(root);

    return 0;
}
