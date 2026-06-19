#include <iostream>
using namespace std;

struct Node {
    int score;
    Node* left;
    Node* right;
};

Node* createNode(int score) {
    Node* newNode = new Node();
    newNode->score = score;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int score) {
    if (root == NULL)
        return createNode(score);
    if (score < root->score)
        root->left = insert(root->left, score);
    else if (score > root->score)
        root->right = insert(root->right, score);
    return root;
}

void descending(Node* root) {
    if (root != NULL) {
        descending(root->right);
        cout << root->score << endl;
        descending(root->left);
    }
}

bool search(Node* root, int score) {
    if (root == NULL)
        return false;
    if (root->score == score)
        return true;
    if (score < root->score)
        return search(root->left, score);
    else
        return search(root->right, score);
}

int main() {
    Node* root = NULL;

    root = insert(root, 500);
    root = insert(root, 300);
    root = insert(root, 700);
    root = insert(root, 200);
    root = insert(root, 400);
    root = insert(root, 600);
    root = insert(root, 800);

    cout << "Ranking Player:" << endl;
    descending(root);

    int findScore = 600;
    if (search(root, findScore))
        cout << "Score ditemukan" << endl;
    else
        cout << "Score tidak ditemukan" << endl;

    return 0;
}
