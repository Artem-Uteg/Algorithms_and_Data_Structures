#include <iostream>
#include <vector>

int INF = 1e6;

struct Node {
    Node(int64_t a, int64_t b, int64_t c) : max(a), min(b), size(c) {}

    int64_t max = 0;
    int64_t min = 0;
    int64_t size = 1;
};


class Segment_tree {
public:
    Segment_tree(std::vector<int64_t>& numbers) {
        for (uint64_t i = 0; i < 2 * numbers.size(); ++i) {
            t.push_back(Node(-INF, INF, 1));
        }
        build(numbers, 0, 0, numbers.size());
    }

    int64_t get(uint64_t left, int64_t right) const {
        return getMax(0, left, right) - getMin(0, left, right);
    }

    void change(uint64_t index, int64_t value) {  
        change(0, index, value);
    }

private:
    std::vector<Node> t;
    
    void build(std::vector<int64_t>& numbers, uint64_t i, int64_t left, int64_t right) {
        if (right - left == 1) {
            t[i] = Node(numbers[left], numbers[left], 1);
        } else {
            int64_t middle = (right + left) / 2;
            build(numbers, 2 * i + 1, left, middle);
            build(numbers, 2 * i + 2, middle, right);
            t[i].max = std::max(t[2 * i + 1].max, t[2 * i + 2].max);
            t[i].min = std::min(t[2 * i + 1].min, t[2 * i + 2].min);
            t[i].size = t[2 * i + 1].size + t[2 * i + 2].size;
        }
    }

    void change(uint64_t i, int64_t index, int64_t value) {
        if ((2 * i + 2) < t.size()) {
            if (t[2 * i + 1].size > index) {
                change(2 * i + 1, index, value);
                t[i].max = std::max(t[2 * i + 1].max, t[2 * i + 2].max);
                t[i].min = std::min(t[2 * i + 1].min, t[2 * i + 2].min);
            } else {
                change(2 * i + 2, index - t[2 * i + 1].size, value);
                t[i].max = std::max(t[2 * i + 1].max, t[2 * i + 2].max);
                t[i].min = std::min(t[2 * i + 1].min, t[2 * i + 2].min);
            }
        } else {
            t[i].max = value;
            t[i].min = value;
        }
    }

    int64_t getMax(uint64_t i, int64_t left, int64_t right) const {
        if (i >= t.size()) 
            return -INF;

        if ((left == 0) && (right == (t[i].size - 1))) 
            return t[i].max;
        
        if (right < ((t[i].size / 2) - 1)) 
            return getMax(2 * i + 1, left, right);
        
        if (left > ((t[i].size / 2) - 1)) 
            return getMax(2 * i + 2, left - (t[i].size / 2), right - (t[i].size / 2));

        return std::max(getMax(2 * i + 1, left, (t[i].size / 2) - 1), 
                        getMax(2 * i + 2, 0, right - (t[i].size / 2)));
    }

    int64_t getMin(uint64_t i, int64_t left, int64_t right) const {
        if (i >= t.size())
            return INF;

        if ((left == 0) && (right == (t[i].size - 1))) 
            return t[i].min;

        if (right < ((t[i].size / 2) - 1))
            return getMin(2 * i + 1, left, right);

        if (left > ((t[i].size / 2) - 1))
            return getMin(2 * i + 2, left - (t[i].size / 2), right - (t[i].size / 2));

        return std::min(getMin(2 * i + 1, left, (t[i].size / 2) - 1),
                        getMin(2 * i + 2, 0, right - (t[i].size / 2)));
    }
};



int main() {
    int64_t size = 1 << 20;
    std::vector<int64_t> array (size);
    for (int64_t i = 1; i <= size; ++i) 
        array[i - 1] = (i * i) % 12345 + (i * i * i) % 23456;

    Segment_tree tree(array);
    
    int64_t k, x, y; 
    std::cin >> k;
    
    for (int64_t i = 0; i < k; ++i) {
        std::cin >> x >> y;
        if (x > 0) std::cout << tree.get(x - 1, y - 1) << '\n';
        else tree.change(- x - 1, y);
    }
}
 
