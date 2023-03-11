/*
Гистограмма является многоугольником, сформированным из последовательности прямоугольников, выровненных на общей базовой линии. 
Прямоугольники имеют равную ширину, но могут иметь различные высоты.
Обычно гистограммы используются для представления дискретных распределений, например,
частоты символов в текстах. Отметьте, что порядок прямоугольников очень важен.
Вычислите область самого большого прямоугольника в гистограмме, который также находится на общей базовой линии.
*/

#include<stack>
#include<iostream>
#include<vector>


int main() {
    using namespace std;

    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
 
    int32_t n;

    cin >> n;
    
    stack<int32_t> stack_first;
    vector<int64_t> left(n + 1), right(n + 1), hight(n + 1);

    for (int32_t i = 0; i < n; ++i) cin >> hight[i];
    
    for (int32_t i = 0; i < n; ++i) {
        while (!stack_first.empty() && hight[stack_first.top()] >= hight[i]) {
            stack_first.pop();
        }

        if (stack_first.empty()) left[i] = -1;
        else left[i] = stack_first.top();

        stack_first.push(i);
    }

    stack<int32_t> stack_second;
    
    for(int32_t i = n - 1; i > -1; --i) {
        while (!stack_second.empty() && hight[stack_second.top()] >= hight[i]) {
            stack_second.pop();
        }

        if (stack_second.empty()) right[i] = n;
        else right[i] = stack_second.top();

        stack_second.push(i);
    }

    int64_t res = hight[0];
    
    for(int32_t i = 0; i < n; ++i) {
        res = max(res, hight[i] * (right[i] - left[i] - 1));
    }

    cout << res;
}
