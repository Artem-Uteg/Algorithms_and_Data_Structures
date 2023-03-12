/*
Представьте себе клетчатую окружность, состояющую из L клеток. 
Клетки нумеруются целыми числами от 1 до L. Некоторые N клеток закрашены. 
Окружность можно разрезать между любыми двумя клетками. Всего существует L различных разрезов.
Получившаяся полоска делится на K равных частей (L кратно K).
Для каждого i определим fi как количество закрашенных клеток в i-й части.
Вам нужно найти такой разрез, что

F = max fi(i=1..K) − min fi(i=1..K)

минимально возможно. Кроме того, вам нужно найти количество разрезов, на которых достигается минимум.
*/

#include<iostream>
#include<vector>
#include<algorithm>

int32_t main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int64_t l, k, n;
    
    std::cin >> l >> n >> k;
    std::vector<std::vector<int64_t>> circle(n, std::vector<int64_t>(3));
    std::vector<int64_t> parts(k, 0);
    
    int64_t x, quantity = l / k;
    
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> x;
        circle[i][0] = x - 1;
        circle[i][1] = (x - 1) / quantity;
        circle[i][2] = (x - 1) % quantity;
        ++parts[circle[i][1]];
    }

    sort(circle.begin(), circle.end(), []
    (std::vector<int64_t> &a, std::vector<int64_t> &b)
    { return a[2] < b[2]; });

    int64_t min = *std::min_element(parts.begin(), parts.end()),
              max = *std::max_element(parts.begin(), parts.end()),
              range = max - min, count = 1, cut = l, step = 0;

    for (int64_t i = 0; i < n;) {
        
        if(max - min == range) count += circle[i][2] - step - 1;

        step = circle[i][2];
        
        for (; i < n && circle[i][2] == step; ++i) {
            --parts[circle[i][1]];
            ++parts[(circle[i][1] + k - 1) % k];
        }

        min = *std::min_element(parts.begin(), parts.end());
        max = *std::max_element(parts.begin(), parts.end());
    
        if (max - min < range) {
            range = max - min;
            count = 1;
            cut = step + 1;
        } else if (max - min == range) {
            count++;
        }
    }
    
    if(max - min == range) count += quantity - step - 1;
    
    std::cout << range << " " << count * k << '\n';
    std::cout << cut << '\n';
}

