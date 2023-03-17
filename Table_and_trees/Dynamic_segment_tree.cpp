/*
Нужно отвечать на запросы вида

•+ x – добавить в мультимножество число x.
•? x – посчитать сумму чисел не больших x.

*/

#include <iostream>

const int64_t SIZE = 1073741823;

struct Node {
    int64_t b_l = 0, b_r = SIZE; 
    int64_t sum = 0;
    
    Node* left = nullptr;
    Node* right = nullptr;
};

struct Dynamic_segment_tree {
public:
    Dynamic_segment_tree() { top = new Node; }

    ~Dynamic_segment_tree() { del(top); }

    void add (int64_t x, int64_t left, int64_t right) { add(top, x, left, right); }

    int64_t get_sum (int64_t index) const { return get_sum(top, index); }

private:
    Node* top = nullptr;

    void del(Node* tree);
    
    void add (Node* tree, int64_t x, int64_t left, int64_t right);
    
    int64_t get_sum (Node* tree, int64_t index) const;

    bool is_empty_right (Node* tree) const { return tree -> right == nullptr; }
    bool is_empty_left (Node* tree) const { return tree -> left == nullptr; }
    int64_t middle (Node* tree) const { return (tree -> b_l + tree -> b_r) / 2; }

};

void Dynamic_segment_tree::del(Node* tree) {
    if (!is_empty_left(tree)) del(tree -> left);
    if (!is_empty_right(tree)) del(tree -> right);
    delete tree;
}

void Dynamic_segment_tree::add (Node* tree, int64_t x, int64_t left, int64_t right) {
    if ((tree -> b_l == left) && (tree -> b_r == right)) {
        tree -> sum += x;
        
    } else if (middle(tree) < left) {
        
        if (is_empty_right(tree)) {
            tree -> right = new Node;
            tree -> right -> b_l = middle(tree) + 1;
            tree -> right -> b_r = tree -> b_r;
        }

        add(tree -> right, x, left, right);
    
    } else if (middle(tree) >= right) {
            
        if (is_empty_left(tree)) {
            tree -> left = new Node;
            tree -> left -> b_l = tree -> b_l;
            tree -> left -> b_r = middle(tree);
        }
        add(tree -> left, x, left, right);
        
    } else {
        
        if (is_empty_right(tree)) {
            tree -> right = new Node;
            tree -> right -> b_l = middle(tree) + 1;
            tree -> right -> b_r = tree -> b_r;
        }

        add(tree -> right, x, tree -> right -> b_l, right);
        
        if (is_empty_left(tree)) {
            tree -> left = new Node;
            tree -> left -> b_l = tree -> b_l;
            tree -> left -> b_r = middle(tree);
        }

        add(tree -> left, x, left, tree -> left -> b_r);
    }
}  

int64_t Dynamic_segment_tree::get_sum (Node* tree, int64_t index) const {

    if ((!is_empty_left(tree)) && (index <= middle(tree))) 
        return tree -> sum + get_sum(tree -> left, index);
        
    if ((!is_empty_right(tree)) && (index > middle(tree)))
        return tree -> sum + get_sum(tree -> right, index);
        
    return tree -> sum;
}

int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);    
    
    Dynamic_segment_tree tree;

    int64_t q, x;
    std::cin >> q;

    char command; 
    
    for (size_t i = 0; i < q; ++i) {
        std::cin >> command >> x;
        
        if (command == '+') tree.add(x, x, SIZE);
        else std::cout << tree.get_sum(x) << std::endl;
    }
}

