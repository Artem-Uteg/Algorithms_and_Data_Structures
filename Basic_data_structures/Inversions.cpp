/*
Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ 
находит количество пар (i,j) таких, что i < j и a[i] > a[j].
*/

#include <iostream>
#include <vector>

int64_t merge(std::vector<int32_t> &array, int32_t left, int32_t middle, int32_t right) {
    
    std::vector<int32_t> copy_array(right - left + 1);
    
    int32_t i = left, j = middle + 1, k = 0;
    int64_t count = 0;
 
    while (i <= middle && j <= right) {
        if (array[i] < array[j]) {
            copy_array[k++] = array[i++];
        
        } else {
            copy_array[k++] = array[j++];
            count += middle - i + 1;
        }
    }

    while (i <= middle) { 
        copy_array[k++] = array[i++];
    }
    while (j <= right) {
        copy_array[k++] = array[j++];
    }
    
    for (size_t i = left; i < right + 1; ++i) {
        array[i] = copy_array[i - left];
    }

    return count;
}


int64_t inverses(std::vector<int32_t> &array, int32_t left, int32_t right) {

    if (left >= right)  return 0;
 
    int32_t middle = (left + right) / 2;
    int64_t count = 0;
    
    count += inverses(array, left, middle);
    count += inverses(array, middle + 1, right);
 
    count += merge(array, left, middle, right);
    return count;
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

    std::cout << inverses(array, 0, n - 1);
    return 0;
}


