/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 300000.
Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include<iostream>
#include<vector>

const int32_t BIT_IN_BYTE = 8;
const int32_t VALUE_BYTE = 256;
const int32_t BYTE_INT64 = 8;

int32_t bytes(int64_t number, int32_t n) {
    return number >> (BIT_IN_BYTE * n) & (VALUE_BYTE - 1);
}

void lsd_sort(std::vector<int64_t>& array) {
    std::vector<int32_t> count(VALUE_BYTE);

    for(int32_t number_byte = 0; number_byte < BYTE_INT64; number_byte++) {
        for(int32_t i = 0; i < VALUE_BYTE; i++) {
            count[i] = 0;
        }

        for(int32_t i = 0; i < array.size(); i++) {
            count[bytes(array[i], number_byte)]++;
        }

        for(int32_t i = 1; i < VALUE_BYTE; i++) {
            count[i] += count[i - 1];
        }

        std::vector<int64_t> copy_array(array.size());

        for(int32_t i = array.size() - 1; i > -1; i--) {
            copy_array[--count[bytes(array[i], number_byte)]] = array[i];
        }

        for(int32_t i = 0; i < array.size(); i++) {
            array[i] = copy_array[i];
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int32_t n;
    std::cin >> n;

    std::vector<int64_t> array(n);

    for(int32_t i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    lsd_sort(array);

    for(int32_t i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    return 0;
}

