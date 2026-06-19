#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string name;
    Node* parent;
    vector<Node*> children;
};

Node* createNode(string folderName, Node* parent = NULL) {
    Node* node = new Node();
    node->name = folderName;
    node->parent = parent;
    return node;
}

void addFolder(Node* parent, string folderName) {
    Node* newFolder = createNode(folderName, parent);
    parent->children.push_back(newFolder);
    cout << "Folder '" << folderName
         << "' berhasil ditambahkan ke '"
         << parent->name << "'\n";
}

void printTree(Node* node, int level = 0) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++)
        cout << "| ";

    if (level > 0)
        cout << "+-- ";

    cout << node->name << endl;

    for (Node* child : node->children)
        printTree(child, level + 1);
}

void preorder(Node* node) {
    if (node == NULL) return;
    cout << node->name << endl;
    for (Node* child : node->children)
        preorder(child);
}

void postorder(Node* node) {
    if (node == NULL) return;
    for (Node* child : node->children)
        postorder(child);
    cout << node->name << endl;
}

Node* search(Node* node, string target) {
    if (node == NULL) return NULL;
    if (node->name == target) return node;

    for (Node* child : node->children) {
        Node* result = search(child, target);
        if (result != NULL) return result;
    }
    return NULL;
}

int countFolder(Node* node) {
    if (node == NULL) return 0;
    int total = 1;
    for (Node* child : node->children)
        total += countFolder(child);
    return total;
}

void showPath(Node* node) {
    if (node == NULL) return;

    vector<string> path;
    Node* current = node;
    while (current != NULL) {
        path.push_back(current->name);
        current = current->parent;
    }

    cout << "Path : ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << "/";
    }
    cout << endl;
}

void deleteSubtree(Node* node) {
    if (node == NULL) return;
    for (Node* child : node->children)
        deleteSubtree(child);
    delete node;
}

void deleteFolder(Node* root, string folderName) {
    Node* target = search(root, folderName);

    if (target == NULL) {
        cout << "Folder tidak ditemukan!\n";
        return;
    }
    if (target == root) {
        cout << "Root tidak dapat dihapus!\n";
        return;
    }

    Node* parent = target->parent;
    for (auto it = parent->children.begin();
         it != parent->children.end(); it++) {
        if (*it == target) {
            parent->children.erase(it);
            break;
        }
    }

    deleteSubtree(target);
    cout << "Folder berhasil dihapus!\n";
}

int main() {
    // Buat root
    Node* root = createNode("Root");

    addFolder(root, "Documents");
    addFolder(root, "Pictures");
    addFolder(root, "Music");

    Node* documents = search(root, "Documents");
    addFolder(documents, "Kuliah");
    addFolder(documents, "Tugas");

    cout << "\n===== STRUKTUR FOLDER =====\n";
    printTree(root);

    cout << "\n===== PREORDER TRAVERSAL =====\n";
    preorder(root);

    cout << "\n===== POSTORDER TRAVERSAL =====\n";
    postorder(root);

    cout << "\n===== SEARCH FOLDER =====\n";
    Node* result = search(root, "Tugas");
    if (result != NULL) {
        cout << "Folder ditemukan : " << result->name << endl;
        showPath(result);
    } else {
        cout << "Folder tidak ditemukan\n";
    }


    cout << "\n===== JUMLAH FOLDER =====\n";
    cout << "Total Folder : " << countFolder(root) << endl;

    cout << "\n===== HAPUS FOLDER =====\n";
    deleteFolder(root, "Pictures");

    cout << "\n===== STRUKTUR SETELAH DELETE =====\n";
    printTree(root);

    deleteSubtree(root);

    return 0;
}
