/*
Гоблины Мглистых гор очень любях ходить к своим шаманам. 
Так как гоблинов много, к шаманам часто образуются очень длинные очереди. 
А поскольку много гоблинов в одном месте быстро образуют шумную толку, 
которая мешает шаманам проводить сложные медицинские манипуляции, 
последние решили установить некоторые правила касательно порядка в очереди.

Обычные гоблины при посещении шаманов должны вставать в конец очереди. 
Привилегированные же гоблины, знающие особый пароль, встают ровно в ее середину, 
причем при нечетной длине очереди они встают сразу за центром.

Так как гоблины также широко известны своим непочтительным отношением 
ко всяческим правилам и законам, шаманы попросили вас написать программу, 
которая бы отслеживала порядок гоблинов в очереди.

+ i  − гоблин с номером i (1≤i≤N) встаёт в конец очереди.
* i  − привилегированный гоблин с номером i встает в середину очереди.
-    − первый гоблин из очереди уходит к шаманам. Гарантируется,
                    что на момент такого запроса очередь не пуста. 
*/


#include<iostream>
#include<queue>
#include<deque>

struct Goblins_in_queue {
private:
    std::queue<int32_t> first_half;
    std::deque<int32_t> second_half;
    
    void find_balance() {
        if (second_half.size() <= first_half.size()) return;
        int32_t middle = second_half.front();
        second_half.pop_front();
        first_half.push(middle);
    }

public:
    void push_common(int32_t namber) {
        second_half.push_back(namber);
        find_balance();
    }
    
    void push_favored(int32_t namber) {
        second_half.push_front(namber);
        find_balance();
    }
    
    int32_t pop_goblin(){
        int32_t next = first_half.front();
        first_half.pop();
        find_balance();
        
        return next;
    }
};

int main() {
    
    int32_t namber, n;
    char command;
    
    std::cin >> n;

    Goblins_in_queue goblins;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> command;
        
        if(command == '-'){
            std::cout << goblins.pop_goblin() << '\n';
        
        } else {
            std::cin >> namber;
            if(command == '+') goblins.push_common(namber);
            else goblins.push_favored(namber);
        }
    }

    return 0;
}

