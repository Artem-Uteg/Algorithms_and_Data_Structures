/*
Даны n нестрого возрастающих массивов Ai и m нестрого убывающих массивов Bj. 
Все массивы имеют одну и ту же длину l. Далее даны q запросов вида (i,j), 
ответ на запрос – такое k, что max(Aik,Bjk) минимален.
Если таких k несколько, можно вернуть любое.
*/

#include <iostream>
#include <vector>

using namespace std;

int32_t binsearch(vector<int32_t> &first, vector<int32_t> &second) {

    int32_t mid, left = 0, right = first.size() - 1;
    
    while(right - left > 1) {
        mid = (left + right) / 2;

        if (!(first[mid] >= second[mid])) left = mid + 1;
        else right = mid;
    
    }
    
    if (right > left and first[left] >= second[left]) return left;
    
    return right;
}


int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    int32_t n, m, l;
    cin >> n >> m >> l;

    vector<vector<int32_t>> first (n, vector<int32_t>(l));
    vector<vector<int32_t>> second(m, vector<int32_t>(l));

    int32_t t;

    for(int32_t i = 0; i < n; ++i) 
        for(int32_t j = 0; j < l; ++j) 
            cin >> first[i][j];

    for(int32_t i = 0; i < m; ++i) 
        for(int32_t j = 0; j < l; ++j) 
            cin >> second[i][j];

    int32_t q;
    cin >> q;

    for (int32_t _ = 0; _ < q; ++_) {
        
        int32_t i, j;
        cin >> i >> j;

        int32_t k = binsearch(first[i - 1], second[j - 1]);

        bool is_side = max(first[i - 1][k],     second[j - 1][k]) >
                       max(first[i - 1][k - 1], second[j - 1][k - 1]);
        
        if (k == 0)        cout << 1     << '\n';
        else if (is_side)  cout << k     << '\n';
        else               cout << k + 1 << '\n';
    }

    return 0;
}

