/* 
Напишите программу, реализующую структуру данных, позволяющую добавлять и удалять элементы, 
а также находить k-й максимум.
Поддерживаемые команды:
+1(или просто 1) : Добавить элемент с ключом ki.
0                : Найти и вывести k-й максимум.
−1               : Удалить элемент с ключом ki.
*/

#include <iostream>

struct Node {
    
    Node (int64_t x = 0, int64_t y = rand(), int64_t size = 1, Node* left = nullptr, Node* right= nullptr): x(x), y(y), size(size), left(left), right(right) {};

    int64_t size = 1, x = 0, y = rand();
    
    Node* left = nullptr;
    Node* right = nullptr;
};

class Treap {

public:
    Treap () {}
    ~Treap() { while (head != nullptr) del(head->x); }
    
    void add(int32_t x);
    void del(int32_t x);

    int32_t find(int32_t index) const { 
        return (head == nullptr || head -> size <= index) ? -1 : _find(head, index);
    }
    
    int32_t size() const { return (head != nullptr) ? head->size : 0;}

private:
    Node* head = nullptr;
    Treap(const Treap& other);
    Treap &operator=(const Treap &other);
    
    void _del(Node *&index);
    int32_t _find(const Node* vertex, int32_t index) const;
    bool contains(int32_t x) const;

    std::pair<Node*, Node*> split(Node* node, int64_t x);
    Node* merge(Node* left, Node* right);
   
};
 
Treap::Treap(const Treap& other) {
    Treap copy = other;
    std::swap(head, copy.head);
}

Treap &Treap::operator=(const Treap &other) {
    Treap copy = other;
    std::swap(head, copy.head);
 
    return *this;
}
    


void Treap::_del(Node *&index) {
    if (index != nullptr) {
        _del(index->left);
        _del(index->right);
        delete index;
        index = nullptr;
    }
}

void Treap::add(int32_t x) {
    Node* node = new Node;
    node -> x = x;
    
    if (head != nullptr) {    
        std::pair<Node*, Node*> pair_treap;
        pair_treap = split(head, x);
        head = merge(merge(pair_treap.first, node), pair_treap.second);
    
    } else head = node;
}

void Treap::del(int32_t x) {
    
    if (!contains(x)) return;
    
    std::pair<Node*, Node*> pair_treap;
    pair_treap = split(head, x);

    if (pair_treap.first -> right != nullptr) {
        Node* vertex = pair_treap.first;
        --vertex -> size;
        
        while (vertex -> right -> right != nullptr) {
            vertex = vertex -> right;
            --vertex -> size;
        }
        Node* to_del = vertex -> right;
        vertex -> right = vertex -> right -> left;
        delete to_del;
    } else { 
        Node* to_del = pair_treap.first;
        pair_treap.first = pair_treap.first->left;
        delete to_del;
    }
    head = merge(pair_treap.first, pair_treap.second);
}


int32_t Treap::_find(const Node* vertex, int32_t index) const {
    if (vertex -> left == nullptr) {
        if (index == 0) return vertex -> x;
        else if (index > 0) return _find(vertex -> right, index-1);
    } else {
        if (index < vertex -> left -> size) return _find(vertex -> left, index);
        else if (index == vertex -> left -> size) return vertex -> x;
    }
    return _find(vertex -> right, index - vertex -> left -> size - 1);
}

bool Treap::contains(int32_t x) const {
    Node* vertex = head;
    
    while (vertex != nullptr) {
        if (vertex -> x < x) vertex = vertex -> right;
        else if (vertex -> x > x) vertex = vertex -> left;
        else return true;
    }
    return false;
}

std::pair<Node*, Node*> Treap::split(Node* node, int64_t x) {
    if (node == nullptr) return {nullptr, nullptr};
    
    if (node -> x <= x) {
        node -> size -= (node -> right != nullptr) ? node -> right -> size : 0;
        std::pair<Node*, Node*> pair_treap;
        pair_treap = split(node -> right, x);
        
        node -> right = pair_treap.first;
        node -> size += (node -> right != nullptr) ? node -> right -> size : 0;
        
        return {node, pair_treap.second};
    
    } else {
        node -> size -= (node -> left != nullptr) ? node -> left -> size : 0;
        std::pair<Node*, Node*> pair_treap;
        pair_treap = split(node -> left, x);
        
        node -> left = pair_treap.second;
        node -> size += (node -> left != nullptr) ? node -> left -> size : 0;
        
        return {pair_treap.first, node};
    }
}

Node* Treap::merge(Node* left, Node* right) {
    
    if (right == nullptr) return left;
    if (left == nullptr) return right;

    if (left -> y >= right -> y) {
        right -> size += left -> size;
        right -> left = merge(left, right -> left);
        
        return right;

    } else {
        left -> size += right -> size;
        left -> right = merge(left -> right, right);
        
        return left;
    }
}

int main() {
    Treap tree;

    int32_t n, c, k;
    std::cin >> n;
    
    for (int32_t i = 0; i < n; ++i) {
        std::cin >> c >> k;
        
        if (c == 1) tree.add(k);
        else if (c == -1) tree.del(k);
        else std::cout << tree.find(tree.size() - k) << '\n';
    
    }
}
