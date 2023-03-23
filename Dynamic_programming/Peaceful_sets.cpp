/* 
Группа математиков проводит бои между натуральными числами.
Результаты боя между двумя натуральными числами, вообще говоря, случайны,
однако подчиняются следующему правилу:
если одно из чисел не менее чем в два раза превосходит другое, то большее число всегда побеждает;
в противном случае победить может как одно, так и другое число.

Бой называется неинтересным, если его результат предопределён.
Множество натуральных чисел называется мирным,
если бой любой пары различных чисел из этого множества неинтересен.
Силой множества называется сумма чисел в нём.
Сколько существует мирных множеств натуральных чисел силы n?
*/

#include <iostream>
#include <vector>

long long get_count_common_sequence(long long n) {
    std::vector<std::vector<long long>> dp (n, std::vector<long long> (n, 0));

    //dp[i][j] contains the number of peaceful sets with max element i and power j

    for (size_t i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = i - 1; j >= 0 && j < n; --j) {
            dp[i][j] += 1;            
            for (size_t k = j + 1; 3 * k < i + 2; ++k) {
                dp[i][j] += dp[i - k][2 * k - 1];
            }
        }
    }
    return dp[n - 1][0];
}

int main() {
    long long n;
    std::cin >> n;
    std::cout << get_count_common_sequence(n);
}


