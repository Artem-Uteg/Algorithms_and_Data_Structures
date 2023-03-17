/*
Реализуйте структуру данных из n элементов a1,a2…an, поддерживающую следующие операции:
присвоить элементу ai значение j;
найти знакочередующуюся сумму на отрезке от l до r включительно (al−al+1+al+2−…±ar). 
*/

#include <iostream>
#include <vector>

class Binary_indexed_tree {

public:
    explicit Binary_indexed_tree (const std::vector<int32_t>& array);
    void change (size_t index, int32_t value);
    int32_t get_sum (int32_t left, int32_t right) const;

private:
    std::vector<int32_t> tree;
    int32_t get_sum (size_t index) const;
    static int32_t f (int32_t x) {return (x + 1) & x; }
    static int32_t g (int32_t x) {return (x + 1) | x; }
    
};

Binary_indexed_tree::Binary_indexed_tree (const std::vector<int32_t>& array) {
    tree.assign(array.size(), 0);
    for (size_t i = 0; i < array.size(); ++i) {
        for (size_t j = f(i); j < i + 1; ++j) {
            tree[i] += array[j];
        }
    }
}

void Binary_indexed_tree::change (size_t index, int32_t value) {
    if (index % 2) value *= -1;

    for (size_t i = index; i < tree.size(); i = g(i)) {
        tree[i] += value;
    }
}

int32_t Binary_indexed_tree::get_sum (int32_t left, int32_t right) const {    
    int32_t border_right = get_sum(right),
    border_left = (left > 0) ? get_sum(left - 1) : 0,
    sum = border_right - border_left ;

    if (left % 2) 
        return -sum;

    return sum;
}

int32_t Binary_indexed_tree::get_sum (size_t index) const {
    int32_t answer = 0;

    for(int32_t i = index; i >= 0; i = f(i) - 1) {
        answer += tree[i];
    }
    return answer;
}

int main() {
    int32_t n, x;
    std::cin >> n;
    std::vector<int32_t> array(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> x;
        array[i] = (i % 2) ? -x : x;
    }

    Binary_indexed_tree tree(array);

    int32_t m, command, i, j;
    std::cin >> m;
    
    for (size_t k = 0; k < m; ++k) {
        std::cin >> command >> i >> j;

        if (command == 0) tree.change(i - 1, j - tree.get_sum(i - 1, i - 1));
        else std::cout << tree.get_sum(i - 1, j - 1) << '\n';
        
    }
}
