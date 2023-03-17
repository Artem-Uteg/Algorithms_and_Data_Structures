/*
Дан массив a из n чисел. Нужно обрабатывать запросы:
0. set(i, x) – a[i] = x;
1. get(i, x) – найти min k : k > i и ak > x
*/


#include <iostream>
#include <vector>

const int32_t N = 262144;

struct Node {
    Node(int32_t a, int32_t b) : max(a), size(b) {}

    int32_t max, size;
};

struct Segment_tree {

public:
    Segment_tree(std::vector<int32_t>& numbers) {
        tree.assign(2 * N, Node(-1, 1));
        build(numbers, 0, 0, N);
    }

    void set(int32_t i, int32_t x) {
        set(0, i, x);
    }

    int32_t64_t get(int32_t i, int32_t x) {
        std::vector<int32_t> indexs = get_indexs(0, i);
        for (int32_t j = 0; j < indexs.size(); ++j) {
            if (tree[indexs[j]].max >= x) return get_left(indexs[j], x) - N + 1;
        }
        return -1;
    }

private:
    std::vector<Node> tree;
    
    void build(std::vector<int32_t>& numbers, int32_t i, int32_t left, int32_t right) {
        if (right - left == 1) {

            int32_t number = (left < numbers.size()) ? numbers[left] : -1;
            tree[i] = Node(number, 1);
        
        } else {

            int32_t middle = (left + right)/2, j = 2 * i + 1;
            build(numbers, j, left, middle);
            build(numbers, j + 1, middle, right);
            tree[i].max = std::max(tree[j].max, tree[j + 1].max);
            tree[i].size = tree[j].size + tree[j + 1].size;
        
        }
    }

    void set(int32_t i, int32_t index, int32_t x) {
        int32_t j = 2 * i + 1;
        if ((j + 1) < tree.size()) {
            if (tree[j].size > index) {
                set(j, index, x);
                tree[i].max = std::max(tree[j].max, tree[j + 1].max);
            } else {
                set(j + 1, index - tree[j].size, x);
                tree[i].max = std::max(tree[j].max, tree[j + 1].max);
            }
        } else {
            tree[i].max = x;
        }
    }

    std::vector<int32_t> get_indexs(int32_t i, int32_t index) {
        int32_t j = 2 * i + 1; 

        std::vector<int32_t> ans;
        if (i >= tree.size()) return ans;
        
        if (!index) {
            ans.push_back(i);
            return ans;
        }

        if (index >= (tree[i].size/2)) 
            return get_indexs(j + 1, index - (tree[i].size/2));
        
        std::vector<int32_t> left = get_indexs(j, index);
        for (const int32_t& j : left) {
            ans.push_back(j);
        }

        std::vector<int32_t> right = get_indexs(j + 1, 0);
        for (const int32_t& j : right) {
            ans.push_back(j);
        }
        
        return ans;
    }

    int32_t get_left(int32_t i, int32_t x) {
        int32_t j = 2 * i + 1;
        if (tree[i].size == 1) return i;
        if (tree[j].max >= x) return get_left(j, x);
        return get_left(j + 1, x);
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    
    int32_t n, m;
    std::cin >> n >> m;
    
    std::vector<int32_t> array(n);
    for (int32_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    Segment_tree tree(array);

    int32_t command, index, x, answer;
    
    for (int32_t i = 0; i < m; ++i) {
        std::cin >> command >> index >> x;
        
        if (command) {
            answer = tree.get(index - 1, x);
            answer = (answer == -1) ? -1 : (answer + 1);
            std::cout << answer << '\n';

        } else {
            tree.set(index - 1, x);
        
        }
    }
}

