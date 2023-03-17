/*
Реализуйте AVL-дерево. 

insert x  — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо.
delete x  — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо.
exists x  — если ключ x есть в дереве, вывести «true», иначе «false»
next x    — минимальный  элемент в дереве, больший x, или «none», если такого нет.
prev x    — максимальный элемент в дереве, меньший x, или «none», если такого нет.
*/



#include <iostream>
#include <string>

struct Node {
    int32_t val, height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
};


class AVLTree {
public:
    void add(int32_t x);
    void del(int32_t x);
    bool exists(int32_t x);

   
    Node* next(int32_t x) { return _next(head, x); }
    Node* prev(int32_t x) { return _prev(head, x); }

    int32_t getSize() { return size; }


private:
    void _add(Node* vertex, Node* node);
    bool _del(Node* vertex, int32_t x);

    int32_t del_most_right(Node* vertex);
    void balance(Node* vertex);
    void rotate_left(Node* vertex);
    void rotate_right(Node* vertex);
    void big_rotate_left(Node* vertex);
    void big_rotate_right(Node* vertex);

    Node* _next(Node* vertex, int32_t x);
    Node* _prev(Node* vertex, int32_t x);

    Node* head = nullptr;
    int32_t size = 0;

};


void AVLTree::add(int32_t x) {
    
    Node* node = new Node;
    node -> val = x;
    
    ++size;
    
    if (size > 1) _add(head, node);
    else head = node;
}

void AVLTree::del(int32_t x) {
    if (size == 0) return;
    _del(head, x);
}

bool AVLTree::exists(int32_t x) {

    if (!size) return false;
    Node* vertex = head;
    
    while (true) {
        if (vertex == nullptr) return false;
        
        else if (vertex -> val < x) vertex = vertex -> right;
        else if (vertex -> val > x) vertex = vertex -> left;
        else return true;
    }
}

Node* AVLTree::_next(Node* vertex, int32_t x) {
    if (vertex -> val <= x) { 
        if (vertex -> right == nullptr) return nullptr;
        return _next(vertex -> right, x);
    } else {
        if (vertex -> left == nullptr || _next(vertex -> left, x) == nullptr) return vertex;
        return _next(vertex -> left, x);
    }
}

Node* AVLTree::_prev(Node* vertex, int32_t x) {
    if (vertex -> val >= x) {
        if (vertex -> left == nullptr) return nullptr;
        return _prev(vertex -> left, x);
    } else {
            
        if (vertex -> right == nullptr || _prev(vertex -> right, x) == nullptr) return vertex;
        return _prev(vertex -> right, x);
    }
}

void AVLTree::balance(Node* vertex) {
    int32_t left_height, right_height, b_left_height, b_right_height;

    left_height  = (vertex -> left == nullptr)  ? 0 : vertex -> left -> height;
    right_height = (vertex -> right == nullptr) ? 0 : vertex -> right -> height;

    vertex -> height = 1 + std::max(left_height, right_height);
   
    if (right_height - left_height == 2) {
        b_left_height  = (vertex -> right -> left == nullptr) ? 0 :
                                                    vertex -> right -> left -> height;

        b_right_height = (vertex -> right -> right == nullptr) ? 0 :
                                                    vertex -> right -> right -> height;
            
        if (b_left_height - b_right_height < 1) rotate_left(vertex);
        else big_rotate_left(vertex);
    }

    else if (left_height - right_height == 2) {        
        b_left_height  = (vertex -> left -> left == nullptr) ? 0 :
                                                    vertex -> left -> left -> height;

        b_right_height = (vertex -> left -> right == nullptr) ? 0 :
                                                    vertex -> left -> right -> height;
            
        if (b_left_height - b_left_height < 1) rotate_right(vertex);
        else big_rotate_right(vertex);
    }
}

void AVLTree::_add(Node* vertex, Node* node) {
    if (vertex -> val >= node -> val) {
        if (vertex -> left != nullptr) _add(vertex -> left, node);
        else vertex -> left = node;
    
    } else {
        if (vertex -> right != nullptr) _add(vertex -> right, node);
        else vertex -> right = node;
    
    }

    balance(vertex);
}

int32_t AVLTree::del_most_right(Node* vertex) {
    int32_t res;

    if (vertex -> right -> right == nullptr) {
        res = vertex -> right -> val;
        Node* rightLeft = vertex -> right -> left;
        
        delete vertex -> right;
        vertex -> right = rightLeft;
    } else res = del_most_right(vertex -> right);
    
    balance(vertex);
    return res;
}

bool AVLTree::_del(Node* vertex, int32_t x) {
    bool is_left  = false, is_right = false;

    if (vertex -> val > x) {
        if (vertex -> left == nullptr) return false;
        else is_left  = _del(vertex -> left, x);
    
    } else if (vertex -> val < x) { 
        if (vertex -> right == nullptr) return false;
        else is_right = _del(vertex -> right, x);
    } else {
        
        if (vertex -> left == nullptr && vertex -> right == nullptr)
            return true;
        
        else if (vertex -> left == nullptr) {
            Node* right = vertex -> right;
            
            vertex -> height = right -> height;
            vertex -> right = right -> right;
            vertex -> left = right -> left;
            vertex -> val = right -> val;
            
            delete right;
        
        } else if (vertex->right == nullptr) {
            Node* left = vertex->left;
            
            vertex -> height = left -> height;
            vertex -> right = left -> right;
            vertex -> left = left -> left;
            vertex -> val = left -> val;
            
            delete left;
        
        } else if (vertex -> left -> right == nullptr) {
            Node* left = vertex -> left;
            
            vertex -> left = left -> left;
            vertex -> val = left -> val;
            
            delete left;
        
        } else vertex -> val = del_most_right(vertex -> left);
        
        --size;
    }

    if (is_right) {
        delete vertex -> right;
        vertex -> right = nullptr;
    }

    if (is_left) {
        delete vertex -> left;
        vertex -> left = nullptr;
    }

    balance(vertex);
    return false;
}

void AVLTree::rotate_left(Node* vertex) {
    Node* new_left_right = vertex -> right -> left;
    Node* new_left_left = vertex -> left;
    Node* new_right = vertex -> right -> right;
    
    std::swap(vertex -> val, vertex -> right -> val);
    vertex -> left = vertex -> right;
    vertex -> left -> right = new_left_right;
    vertex -> left -> left = new_left_left;
    vertex -> right = new_right;
    
    if (vertex -> left -> right != nullptr && vertex -> left -> left != nullptr)
        vertex -> left -> height = 1 + std::max(vertex -> left -> right -> height, 
                                                vertex -> left -> left -> height);
    
    else if (vertex -> left -> right != nullptr)
        vertex -> left -> height = 1 + vertex -> left -> right -> height;
    
    else if (vertex -> left -> left != nullptr)
        vertex -> left -> height = 1 + vertex -> left -> left -> height;
    
    else vertex -> left -> height = 1;
   
    if (vertex -> right != nullptr)
        vertex -> height = 1 + std::max(vertex -> right -> height,
                                        vertex -> left -> height);
    
    else vertex -> height = 1 + vertex -> left -> height;
}

void AVLTree::rotate_right(Node* vertex) {
    Node* new_right_right = vertex -> right;
    Node* new_right_left = vertex -> left -> right;
    Node* new_left = vertex -> left -> left;

    std::swap(vertex -> val, vertex -> left->val);
    vertex -> right = vertex -> left;
    vertex -> right -> right = new_right_right;
    vertex -> right -> left = new_right_left;
    vertex -> left = new_left;
    
    if (vertex -> right -> right != nullptr && vertex -> right -> left != nullptr)
        vertex -> right -> height = 1 + std::max(vertex -> right -> right -> height, 
                                                 vertex -> right -> left -> height);

    else if (vertex -> right -> right != nullptr)
        vertex -> right -> height = 1 + vertex -> right -> right -> height;
    
    else if (vertex -> right -> left != nullptr)
        vertex -> right -> height = 1 + vertex -> right -> left -> height;
    
    else vertex -> right -> height = 1;
    
    if (vertex -> left != nullptr)
        vertex -> height = 1 + std::max(vertex -> right -> height,
                                        vertex -> left -> height);
    
    else
        vertex -> height = 1 + vertex -> right -> height;
}

void AVLTree::big_rotate_left(Node* vertex) {
    rotate_right(vertex->right);
    rotate_left(vertex);
}

void AVLTree::big_rotate_right(Node* vertex) {
    rotate_left(vertex->left);
    rotate_right(vertex);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::string command;
    int32_t number;

    AVLTree tree;
    while (std::cin >> command) {
        std::cin >> number;

        if (command == "insert") {
            if (!tree.exists(number)) tree.add(number);
        } else if (command == "delete") {
            tree.del(number);
        } else if (command == "exists") {
            if (tree.exists(number))
                std::cout << "true" << '\n';
            else std::cout << "false" << '\n';
        } else if (command == "next") {
            if (tree.getSize() == 0 || tree.next(number) == nullptr)
                std::cout << "none" << '\n';
            else std::cout << tree.next(number) -> val << '\n';
        } else {
            if (tree.getSize() == 0 || tree.prev(number) == nullptr)
                std::cout << "none" << '\n';

            else std::cout << tree.prev(number) -> val << '\n';
        }
    }
}


