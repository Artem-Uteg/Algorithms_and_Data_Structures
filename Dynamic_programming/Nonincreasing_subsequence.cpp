/*
Вам требуется написать программу,
которая по заданной последовательности находит максимальную невозрастающую подпоследовательность 
(т.е такую последовательность чисел ai1,ai2,…,aik (i1<i2<…<ik),
что ai1≥ai2≥…≥aik и не существует последовательности с теми же свойствами длиной k+1).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int64_t INF = std::numeric_limits<int64_t>::lowest();

std::vector<int64_t> find_max_subseq(std::vector<int64_t>& array) {
    int64_t n = array.size();
    std::vector<int64_t> dp(n, INF), index(n, INF), parent(n, INF);
    
    // dp[i] - длинна максимальной подпоследовательности для i элемента слова.
    // index[i] - индекс при i максимальной длинной 
    // parent[i] - предыдущий элемент для  array[i] 

    size_t next;

    for (size_t i = 0; i < n; ++i) {
        next = static_cast<size_t>(std::lower_bound(dp.begin(), dp.end(), array[i], 
                                    std::greater_equal<int64_t>()) - dp.begin()) ;
        
        if (dp[next - 1] >= array[i] >= dp[next]) {
            dp[next] = array[i];
            index[next] = i;
            parent[i] = (next > 0) ? index[next - 1] : INF;
        }
    }
    
    int64_t size_answer = n - 1;

    while ((size_answer > -1) && (index[size_answer] == INF)) --size_answer;
    
    int64_t x = index[size_answer];
    std::vector<int64_t> res;
    
    while (x > -1) {
        res.push_back(x);
        x = parent[x];
    }
    
    return res;
}

int main() {
    int64_t n; 
    std::cin >> n;
    
    std::vector<int64_t> array(n);
    
    for (int64_t i = 0; i < n; ++i) 
        std::cin >> array[i];

    auto answer = find_max_subseq(array);
    int64_t size = answer.size();
    
    std::cout << size << '\n';

    for (size_t i = size - 1; (i >= 0) && (i < size); --i) {
        std::cout << answer[i] + 1 << " ";
    }
}
 
