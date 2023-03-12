/*
Реализуйте двоичную кучу.

Обработайте запросы следующих видов:

insert x — вставить целое число x в кучу;

getMin — вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);

extractMin — удалить минимальный элемент из кучи, выводить его не нужно (гарантируется, что к этому моменту куча не пуста);

decreaseKey i Δ — уменьшить число, вставленное на i-м запросе, на целое число Δ≥0 
(гарантируется, что i-й запрос был осуществлён ранее, являлся запросом добавления,
а добавленное на этом шаге число всё ещё лежит в куче). Обратите внимание, число i

равно номеру запроса среди всех запросов, а не только среди запросов добавления!
*/

#include<iostream>
#include<vector>
#include<string>
#include<limits>

const int64_t INF = std::numeric_limits<int64_t>::max();;

class Heap {
public:

    void insert(int64_t data, size_t time);
    int64_t get_min();
    void extract_min();
    void decrease_key(size_t number, int64_t delta);

private:

    std::vector<std::pair<int64_t, size_t>> values;
    std::vector<size_t> time_in;
    void sift_down(size_t i);
    void sift_up(size_t i);

};

void Heap::insert(int64_t data, size_t time) {
    values.push_back({data, time});
    time_in.push_back(values.size() - 1);
    sift_up(values.size() - 1);
}

int64_t Heap::get_min() {
    time_in.push_back(INF);
    return values[0].first;
}

void Heap::extract_min() {
    time_in.push_back(INF);
    std::swap(time_in[values[0].second], time_in[values[values.size() - 1].second]);

    values[0] = values[values.size() - 1];
    values.pop_back();
    sift_down(0);
}

void Heap::decrease_key(size_t number, int64_t delta) {
    time_in.push_back(INF);
            
    values[time_in[number - 1]].first -= delta;
    sift_up(time_in[number - 1]);

}
        
void Heap::sift_down(size_t i) {
    size_t j;
    while(2 * i < values.size()) {
        j = -1;
        size_t left_child = 2 * i + 1, right_child = 2 * i + 2;
        if (values[left_child].first < values[i].first) j = left_child;

        if (right_child <= values.size() && values[right_child].first < values[i].first 
            && (j == -1 || values[left_child].first > values[right_child].first)) 
            j = right_child;

        if (j == -1) break;
                
        std::swap(time_in[values[i].second], time_in[values[j].second]);
        std::swap(values[i], values[j]);
        i = j;

    }
}

void Heap::sift_up(size_t i) {
    size_t parent = (i - 1) / 2;
    while(i > 0 && values[i].first < values[parent].first){
    
        std::swap(time_in[values[i].second], time_in[values[parent].second]);
        std::swap(values[i], values[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int64_t q, number, delta;
    
    std::cin >> q;
    std::string command;
    
    Heap heap;
    
    for(size_t i = 0; i < q; ++i) {
        std::cin >> command;
        
        if(command == "insert") {
            std::cin >> number;
            heap.insert(number, i);

        } else if(command == "getMin") {
            number = heap.get_min();
            std::cout << number << '\n';

        } else if(command == "extractMin") {
            heap.extract_min();

        } else {
            std::cin >> number >> delta;
            heap.decrease_key(number, delta);
        }
    }
}
 
