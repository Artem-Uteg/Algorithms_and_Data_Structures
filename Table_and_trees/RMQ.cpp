/*
Дано число N и последовательность из N целых чисел.
Найти вторую порядковую статистику на заданных диапазонах.
Для решения задачи используйте структуру данных Sparse Table.
Требуемое время обработки каждого диапазона O(1). 
Время подготовки структуры данных O(nlogn).
*/


#include <iostream>
#include <vector>
#include <set>
#include<limits>

const std::pair<int32_t, int32_t> nullpair = {0, 0};
const int32_t INF = std::numeric_limits<int32_t>::max();

class Sparse_table {
public:
    explicit Sparse_table (const std::vector<int32_t>& array);
    int32_t get_min (int32_t left, int32_t right) const;

private:
    std::vector<int32_t> number;
    std::vector<int32_t> power_of_two;
    std::vector<std::vector<std::pair<std::pair<int32_t, int32_t>, 
                                      std::pair<int32_t, int32_t>>>> sparse;

    void build (int32_t size);
    void write_power_of_two(int32_t size);
};

Sparse_table::Sparse_table (const std::vector<int32_t>& array) {

    int32_t n = array.size();
    std::vector<std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>> temp;
    sparse.push_back(temp);
        
    for (size_t i = 0; i < n; ++i) 
        sparse[0].push_back({{array[i], i}, {INF, -1}});

    build(n);
    write_power_of_two(n);
}    

void Sparse_table::build(int32_t size) {
    int32_t two_in_range = 2;
    size_t j;

    for (size_t range = 0; two_in_range < size; ++range) {
            
        std::vector<std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>> temp;
        sparse.push_back(temp);
            
        for (size_t i = 0; i < (size - two_in_range + 1); ++i) {
            sparse[range + 1].push_back({nullpair, nullpair});                

            std::set<std::pair<int32_t, int32_t>> set_for_min_now;

            j = std::min(sparse[range].size() - 1, i + (two_in_range / 2));
            
            set_for_min_now.insert(sparse[range][i].first);
            set_for_min_now.insert(sparse[range][i].second);
            set_for_min_now.insert(sparse[range][j].first);
            set_for_min_now.insert(sparse[range][j].second);
                
            sparse[range + 1][i] = {*(set_for_min_now.begin()), *next(set_for_min_now.begin())};
        }
        two_in_range *= 2;
    }
}

void Sparse_table::write_power_of_two(int32_t size) {

    number.reserve(size);
    power_of_two.reserve(size);

    number[0] = 0;
    power_of_two[0] = 0;

    int32_t now_number = 0, now_digit_two = 1;

    for (size_t i = 1; i < size; ++i) {
            
        if (((i&(i-1)) == 0) && (i != 1)) {
            ++now_number;
            now_digit_two *= 2;
        }

        number[i] = now_number;
        power_of_two[i] = now_digit_two;
    }
}

int32_t Sparse_table::get_min (int32_t left, int32_t right) const {
    int32_t range = right - left;

    std::set<std::pair<int32_t, int32_t>> set_for_min;
        
    set_for_min.insert(sparse[number[range]][left].first);
    set_for_min.insert(sparse[number[range]][left].second);
    set_for_min.insert(sparse[number[range]][right - power_of_two[range] + 1].first);
    set_for_min.insert(sparse[number[range]][right - power_of_two[range] + 1].second);
        
    return (*(next(set_for_min.begin()))).first;
}

int main() {
    int32_t n, m;
    std::cin >> n >> m;

    std::vector<int32_t> array(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    Sparse_table table(array);

    int32_t left, right;
    
    for (size_t i = 0; i < m; ++i) {
        std::cin >> left >> right;
        std::cout << table.get_min(left - 1, right - 1) << '\n';
    }
}
 
