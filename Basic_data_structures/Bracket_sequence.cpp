/*
По заданной строке из круглых/квадратных/фигурных открывающих и закрывающих скобок определить, 
является ли она правильной скобочной последовательностью.

Множество правильных скобочных последовательностей (ПСП) определяется 
как наименьшее множество с условиями:

пустая строка является ПСП;
если S — ПСП, то (S), [S], {S} — тоже ПСП;
если S1 и S2 — ПСП, то S1S2 — тоже ПСП. 
*/


#include<stack>
#include<iostream>
#include<string>
#include<vector>

int main() {

    std::string psp;
    std::stack<char> s;
    std::cin >> psp;

    for(size_t i = 0; i < psp.size(); ++i) {
        char x = psp[i];
        
        if (x == '(' || x == '[' || x == '{') {
            s.push(psp[i]);
        
        } else if (!s.empty() && ((s.top() == '(' && ')' == x) 
                               || (s.top() == '[' && ']' == x)
                               || (s.top() == '{' && '}' == x))) {
            s.pop();
        
        } else {
            s.push(x);
            break;
        }
    }

    if(s.empty()) std::cout << "yes";
    else std::cout << "no";
}

