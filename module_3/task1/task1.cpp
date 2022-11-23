#include <iostream>
#include <stack>

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

class Tree {
private:
    Node *root = nullptr;

public:
    ~Tree() {
        delete root;
    }
    explicit Tree() : root(nullptr) {}
    void Add(int value);
    void Print() const;
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

void Tree::Print() const {
    if (!root) return;
    std::stack<std::pair<Node *, bool>> Stack;
    Stack.emplace(root, false);
    while (!Stack.empty()) {
        if (Stack.top().second) {
            std::cout << Stack.top().first->Data << ' ';
            Stack.pop();
            continue;
        }
        Node *current = Stack.top().first;
        Stack.pop();
        if (current->Right) Stack.emplace(current->Right, false);
        Stack.push({current, true});
        if (current->Left) Stack.emplace(current->Left, false);
    }
    std::cout << std::endl;
}

int main() {
    int n = 0;
    std::cin >> n;
    Tree tree;
    int value = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        tree.Add(value);
    }
    tree.Print();
    return 0;
}
