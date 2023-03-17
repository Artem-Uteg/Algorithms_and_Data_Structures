/*
В этой задаче используйте дерево Фенвика.
Вася любит наблюдать за звездами. Но следить за всем небом сразу ему тяжело. Поэтому он
наблюдает только за частью пространства, ограниченной кубом размером n×n×n. Этот куб поделен
на маленькие кубики размером 1 × 1 × 1. Во время его наблюдений могут происходить следующие
события:
1. В каком-то кубике появляются или исчезают несколько звезд.
2. К нему может заглянуть его друг Петя и поинтересоваться, сколько видно звезд в части про-
странства, состоящей из нескольких кубиков.
*/


#include <iostream>
#include <vector>


class Binary_indexed_tree {
public:
    Binary_indexed_tree (int32_t n) {

        std::vector<std::vector<int32_t>> sub_tree(n, std::vector<int32_t> (n, 0));
        tree.assign(n, sub_tree);
    }

    void change (int32_t x, int32_t y, int32_t z, int32_t value) {
        int32_t n = tree.size();

        for (int32_t i = x; i < n; i = g(i))
            for (int32_t j = y; j < n; j = g(j))
                for (int32_t k = z; k < n; k = g(k))
                    tree[i][j][k] += value;
    }

    int32_t get_sum (int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) {
        return get_sum(x2, y2, z2) - get_sum(x2, y2, z1)
             - get_sum(x2, y1, z2) - get_sum(x1, y2, z2)
             + get_sum(x2, y1, z1) + get_sum(x1, y2, z1)
             + get_sum(x1, y1, z2) - get_sum(x1, y1, z1);
    }

private:

    std::vector<std::vector<std::vector<int32_t>>> tree;

    int32_t get_sum (int32_t x, int32_t y, int32_t z) {
        int32_t answer = 0;

        for(int32_t i = x; i >= 0; i = f(i) - 1)
            for(int32_t j = y; j >= 0; j = f(j) - 1)
                for(int32_t k = z; k >= 0; k = f(k) - 1)
                    answer += tree[i][j][k];

        return answer;
    }

    int32_t f (int32_t x) { return (x + 1) & x; }

    int32_t g (int32_t x) { return (x + 1) | x; }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int32_t n;
    std::cin >> n;

    Binary_indexed_tree tree(n);

    int32_t m, x, y, z, k, x1, y1, z1, x2, y2, z2, answer;

    while (true) {
        std::cin >> m;

        if (m == 1) {
            std::cin >> x >> y >> z >> k;
            tree.change(x, y, z, k);
            continue;
        }
        if (m == 2) {
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            answer = tree.get_sum(x1 - 1, y1 - 1, z1 - 1, x2, y2, z2);
            std::cout << answer << '\n';
            continue;
        }
        break;
    }
}

