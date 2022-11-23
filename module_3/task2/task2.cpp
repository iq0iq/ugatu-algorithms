#include <algorithm>
#include <iostream>
#include <queue>

struct Node {
    int Data;
    Node *Left = nullptr;
    Node *Right = nullptr;
    Node *Parent = nullptr;
    explicit Node(int Data, Node *Parent = nullptr) : Data(Data), Parent(Parent) {}
    ~Node() {
        delete Left;
        delete Right;
    }
};

class Tree {
private:
    Node *root = nullptr;

public:
    ~Tree() {
        delete root;
    }
    void Add(int value);
    int BFS();
};

void Tree::Add(int value) {
    if (!root) {
        root = new Node(value);
        return;
    }
    Node *current = root;
    while (true) {
        if (current->Data > value) {  // Идем в Left
            if (current->Left) {
                current = current->Left;
            } else {
                current->Left = new Node(value, current);
                break;
            }
        } else {  // Идем в Right
            if (current->Right) {
                current = current->Right;
            } else {
                current->Right = new Node(value, current);
                break;
            }
        }
    }
}

int Tree::BFS() {  // возвращает количество узлов в самом широком слое
    std::queue<Node *> Queue;
    if (root != nullptr) Queue.push(root);
    int width = (int) Queue.size();
    int Max = (int) Queue.size();
    while (!Queue.empty()) {
        Node *node = Queue.front();
        Queue.pop();
        --width;
        if (node->Left)
            Queue.push(node->Left);
        if (node->Right)
            Queue.push(node->Right);
        if (width == 0) {
            width = (int) Queue.size();
            Max = std::max(Max, width);
        }
    }
    return Max;
}


struct TreapNode {
    int Key;
    int Priority;
    TreapNode *Left = nullptr;
    TreapNode *Right = nullptr;
    ~TreapNode() {
        delete Left;
        delete Right;
    }
    explicit TreapNode(int Key, int Priority) : Key(Key), Priority(Priority) {}
};

class Treap {
public:
    ~Treap() {
        delete root;
    }
    void Insert(TreapNode *inserted_element);
    int BFS();

private:
    TreapNode *root = nullptr;
    void Split(TreapNode *current_node, int key, TreapNode *&left, TreapNode *&right);
    void Add(TreapNode *&current, TreapNode *inserted_element);
};

void Treap::Split(TreapNode *current_node, int key, TreapNode *&left, TreapNode *&right) {
    if (!current_node) {
        left = nullptr;
        right = nullptr;
    } else if (current_node->Key < key) {
        Split(current_node->Right, key, current_node->Right, right);
        left = current_node;
    } else {
        Split(current_node->Left, key, left, current_node->Left);
        right = current_node;
    }
}

void Treap::Add(TreapNode *&current, TreapNode *inserted_element) {
    if (!current) {
        current = inserted_element;
        return;
    }
    if (inserted_element->Priority > current->Priority) {
        Split(current, inserted_element->Key, inserted_element->Left, inserted_element->Right);
        current = inserted_element;
    } else {
        Add(inserted_element->Key < current->Key ? current->Left : current->Right, inserted_element);
    }
}

void Treap::Insert(TreapNode *inserted_element) {
    Add(root, inserted_element);
}

int Treap::BFS() {
    std::queue<TreapNode *> Queue;
    if (root != nullptr) Queue.push(root);
    int width = (int) Queue.size();
    int Max = (int) Queue.size();
    while (!Queue.empty()) {
        TreapNode *current = Queue.front();
        Queue.pop();
        --width;
        if (current->Left)
            Queue.push(current->Left);
        if (current->Right)
            Queue.push(current->Right);
        if (width == 0) {
            width = (int) Queue.size();
            Max = std::max(Max, width);
        }
    }
    return Max;
}


int main() {
    int n = 0;
    std::cin >> n;
    int key = 0;
    int priority = 0;
    Treap treap;
    Tree tree;
    for (int i = 0; i < n; ++i) {
        std::cin >> key >> priority;
        TreapNode *inserted_element = new TreapNode(key, priority);
        treap.Insert(inserted_element);
        tree.Add(key);
    }
    std::cout << treap.BFS() - tree.BFS() << std::endl;
    return 0;
}
