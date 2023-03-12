/*
Даны неотрицательные целые числа N, K и массив целых чисел из диапазона [0,10^9] размера N.
Требуется найти K-ю порядковую статистику, т.е. напечатать число, 
которое бы стояло на позиции с индексом K ∈[ (0,N−1] в отсортированном массиве.

Реализуйте алгоритм QuickSelect (среднее время работы O(N)). 
*/

#include<iostream>
#include<vector>


int32_t partition(std::vector<int32_t>& array, int32_t left, int32_t right) {
    
    int32_t pivot = array[rand() % (right - left + 1) + left], i = left, j = right;
    
    while (i <= j) {
        
        while (i < array.size() && array[i] <= pivot) ++i;
        while (j > 0 && array[j] > pivot) --j;
        
        if (i >= j) break;

        std::swap(array[i], array[j]);
    }

    return j;
}

int32_t find_kth_statistic (std::vector<int32_t>& array, int32_t k) {
    
    int32_t left = 0, right = array.size() - 1, middle;
    
    while (true) {

        middle = partition(array, left, right);
        
        if (middle == k) return array[middle];

        if (k > middle) left = middle + 1;
        else right = middle;
    }
}


int main () {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int32_t n, k;

    std::cin >> n >> k;
    std::vector<int32_t> array(n);

    for(size_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    
    std::cout << find_kth_statistic(array, k) << '\n';
}
 
