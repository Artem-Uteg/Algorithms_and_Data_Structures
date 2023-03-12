/*
Отсортируйте данную последовательность, используя алгоритм быстрой сортировки QuickSort.
*/

#include<iostream>
#include<vector>


std::pair<int32_t, int32_t> partition (std::vector<int32_t>& array, int32_t left, int32_t right) {
    
    int32_t pivot_index = rand() % (right - left) + left;

    std::swap(array[pivot_index], array[left]);
    int32_t pivot = array[left];


    while (left <= right) {

        while (array[left] < pivot) ++left;
        while (array[right]  > pivot) --right;
        
        if (left <= right) {
            std::swap(array[right], array[left]);
            ++left;
            --right;
        }
    }


    return {right, left};
} 

void quick_sort(std::vector<int32_t>& array, int32_t left, int32_t right) {
    
    if (right > left) {
        std::pair<int32_t, int32_t> pivot = partition(array, left, right); 
        
        int32_t border_left = pivot.first;
        int32_t border_right = pivot.second;

        quick_sort(array, left, border_left); 
        quick_sort(array, border_right, right); 
    } 
} 


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int32_t n;
    std::cin >> n;
    std::vector<int32_t> array(n);
    
    for (size_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    
    quick_sort(array, 0, n - 1);

    for (size_t i = 0; i < n; i++) {
        std::cout << array[i] << " "; 
    }
}
 
