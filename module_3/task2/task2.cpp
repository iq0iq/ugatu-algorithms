#include <algorithm>
#include <iostream>
#include <queue>

class Tree {
private:
    struct Node {
        int Data;
        Node *Left = nullptr;
        Node *Right = nullptr;
        explicit Node(int Data) : Data(Data) {}
        ~Node() {
            delete Left;
            delete Right;
        }
    };
    Node *root = nullptr;

public:
    ~Tree() {
        delete root;
    }
    explicit Tree() : root(nullptr) {}
    void Insert(int value);
    size_t WidestLayer();
};

void Tree::Insert(int value) {
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
                current->Left = new Node(value);
                break;
            }
        } else {  // Идем в Right
            if (current->Right) {
                current = current->Right;
            } else {
                current->Right = new Node(value);
                break;
            }
        }
    }
}

size_t Tree::WidestLayer() {  // возвращает количество узлов в самом широком слое
    std::queue<Node *> Queue;
    if (root != nullptr) Queue.emplace(root);
    size_t width = Queue.size();
    size_t Max = Queue.size();
    while (!Queue.empty()) {
        Node *node = Queue.front();
        Queue.pop();
        --width;
        if (node->Left)
            Queue.emplace(node->Left);
        if (node->Right)
            Queue.emplace(node->Right);
        if (width == 0) {
            width = Queue.size();
            if (width > Max) Max = width;
        }
    }
    return Max;
}


class Treap {
private:
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
    TreapNode *root = nullptr;
    void Split(TreapNode *current_node, int key, TreapNode *&left, TreapNode *&right);
    void Add(TreapNode *&current, TreapNode *inserted_element);

public:
    ~Treap() {
        delete root;
    }
    explicit Treap() : root(nullptr) {}
    void Insert(int key, int priority);
    size_t WidestLayer();
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

void Treap::Insert(int key, int priority) {
    TreapNode *inserted_element = new TreapNode(key, priority);
    Add(root, inserted_element);
}

size_t Treap::WidestLayer() {
    std::queue<TreapNode *> Queue;
    if (root != nullptr) Queue.emplace(root);
    size_t width = Queue.size();
    size_t Max = Queue.size();
    while (!Queue.empty()) {
        TreapNode *current = Queue.front();
        Queue.pop();
        --width;
        if (current->Left)
            Queue.emplace(current->Left);
        if (current->Right)
            Queue.emplace(current->Right);
        if (width == 0) {
            width = Queue.size();
            if (width > Max) Max = width;
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
        treap.Insert(key, priority);
        tree.Insert(key);
    }
    std::cout << static_cast<long long>(treap.WidestLayer()) - static_cast<long long>(tree.WidestLayer()) << std::endl;
    return 0;
}
