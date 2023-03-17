/*
Во Флатландии протекает богатая рыбой река Большой Флат. 
Много лет назад река была поделена между n рыболовными предприятиями, 
каждое из которых получило непрерывный отрезок реки. 
При этом i-е предприятие, если рассматривать их по порядку, начиная от истока, 
изначально получило отрезок реки длиной ai.

С тех пор с рыболовными предприятиями во Флатландии k раз происходили различные события. 
Каждое из событий было одного из двух типов: 

банкротство некоторого предприятия или разделение некоторого предприятия на два. 
При некоторых событиях отрезок реки, принадлежащий предприятию, 
с которым это событие происходит, делится на две части. 
Каждый такой отрезок имеет длину большую или равную 2. Деление происходит по следующему правилу.
Если отрезок имеет четную длину, то он делится на две равные части.
Иначе он делится на две части, длины которых различаются ровно на единицу, при этом часть, 
которая ближе к истоку реки, имеет меньшую длину.

При банкротстве предприятия происходит следующее. 
Отрезок реки, принадлежавший обанкротившемуся предприятию, переходит к его соседям. 
Если у обанкротившегося предприятия один сосед, 
то этому соседу целиком передается отрезок реки обанкротившегося предприятия.
Если же соседей двое, то отрезок реки делится на две части описанным выше способом,
после чего каждый из соседей присоединяет к своему отрезку ближайшую к нему часть.
При разделении предприятия отрезок реки, принадлежавший разделяемому предприятию, 
всегда делится на две части описанным выше способом. Разделившееся предприятие ликвидируется,
и образуются два новых предприятия.
Таким образом, после каждого события каждое предприятие владеет некоторым отрезком реки.

Министерство финансов Флатландии предлагает ввести налог на рыболовные предприятия, 
пропорциональный квадрату длины отрезка реки, принадлежащего соответствующему предприятию. 
Чтобы проанализировать, как будет работать этот налог, министр хочет по имеющимся данным узнать,
как изменялась величина, равная сумме квадратов длин отрезков реки, 
принадлежащих предприятиям, после каждого произошедшего события.

Требуется написать программу, 
которая по заданному начальному разделению реки между предприятиями и списку событий, 
происходивших с предприятиями, определит, чему равна сумма квадратов длин отрезков реки,
принадлежащих предприятиям, в начальный момент времени и после каждого события.
*/



#include <iostream>
#include <fstream>

struct Node {
    int64_t size = 1, y = rand(), val = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

class Treap {
public:
    void insert(int64_t x, int64_t val) {
        Node* node = new Node;
        node -> val = val;
        
        if (head != nullptr) {    
            std::pair<Node*, Node*> p;
            p = split(head, x - 1);
            head = merge(merge(p.first, node), p.second);
        
        } else head = node;
    }

    int64_t del(int64_t x) {
        int64_t ans = 0;
        
        if (head == nullptr || head -> size <= x) return ans;
        
        std::pair<Node*, Node*> p = split(head, x);
        
        if (p.first->right == nullptr) {
            Node* to_del = p.first;
            ans = p.first -> val;
            p.first = p.first -> left;
            
            delete to_del;
        
        } else {
            Node* vertex = p.first;
            
            --vertex -> size;
            while (vertex -> right -> right != nullptr) {
                vertex = vertex -> right;
                --vertex -> size;
            }
            Node* to_del = vertex -> right;
            ans = vertex -> right -> val;
            vertex -> right = vertex -> right -> left;
            delete to_del;
        }

        head = merge(p.first, p.second);
        return ans;
    }
    
    int64_t size() { return (head != nullptr) ? head -> size : 0; }
    int64_t add(int64_t x, int64_t val) { return _add(head, x, val); }

private:
    Node* head = nullptr;
    
    int64_t _add(Node* vertex, int64_t x, int64_t val) {
        if (vertex -> left == nullptr) {
            if (x == 0) {
                vertex -> val += val;
                return vertex -> val;
        
            } else if (x > 0)
                return _add(vertex -> right, x - 1, val);
        
        } else if (vertex -> left != nullptr ) {
               if (x < vertex -> left -> size)
                    return _add(vertex -> left, x, val);
        
                else if (x == vertex -> left -> size) {
                    return vertex -> val += val;
                }
        }

        return _add(vertex -> right, x -1 - vertex -> left -> size, val);
    }

    std::pair<Node*, Node*> split(Node* node, int64_t x) {
        if (node == nullptr) return {nullptr, nullptr};
        
        if (((node -> left != nullptr) ? node -> left -> size : 0) <= x) {
            node -> size -= (node -> right != nullptr) ? node -> right -> size : 0;
            std::pair<Node*, Node*> p = split(node -> right, x - 1 - (node->left != nullptr ? 
                                                                    node -> left -> size : 0));
            node -> right = p.first;
            node -> size += (node -> right != nullptr) ? node -> right -> size : 0;
            
            return {node, p.second};
        
        } else {
            node -> size -= (node -> left != nullptr) ? node -> left -> size : 0;
            std::pair<Node*, Node*> p = split(node -> left, x);
            
            node -> left = p.second;
            int64_t out_size = (node -> left != nullptr) ? node -> left -> size : 0;
            node -> size += out_size;
            
            return {p.first, node};
        }
    }
    
    Node* merge(Node* left, Node* right) {
        
        if (right == nullptr) return left;
        if (left == nullptr) return right;

        if (left -> y >= right -> y) {
            right -> size += left -> size;
            right -> left = merge(left, right -> left);
            return right;

        } else {
            left -> size += right -> size;
            left -> right = merge(left -> right, right);
            return left;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);

    Treap tree;
    
    int64_t res = 0, n, p, a;
    std::cin >> n >> p;
    
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> a;
        tree.insert(i, a);
        res += a*a;
    }
    
    std::cout << res << '\n';
      
    int64_t k, e, v;
    std::cin >> k;
    
    int64_t place, new_place, left_place, right_place;
    int64_t new_left_place, new_right_place;
    
    for (int64_t i = 0; i < k; ++i) {
        std::cin >> e >> v;
    
        if (e == 1) { 
            if (v == 1) {
                place = tree.del(v - 1);
                res -= place * place;
                new_place = tree.add(v - 1, place);
                res -= (new_place - place) * (new_place - place) - new_place * new_place;
            
            } else if (v == tree.size()) {
                place = tree.del(v - 1);
                res -= place * place;
                new_place = tree.add(v - 2, place);
                res -= (new_place - place) * (new_place - place) - new_place * new_place;
            
            } else {
                place = tree.del(v - 1);
                res -= place*place;
                
                left_place = place / 2;
                right_place = place - place / 2;
                
                new_left_place = tree.add(v - 2, left_place);
                new_right_place = tree.add(v - 1, right_place);
                
                res -= (new_left_place - left_place) * (new_left_place - left_place) +
                       (new_right_place - right_place) * (new_right_place - right_place);
                
                res += new_left_place * new_left_place + new_right_place * new_right_place;
            }
        } else {
            place = tree.del(v - 1);
            res -= place * place;
            
            left_place = place / 2;
            right_place = place - place / 2;
            
            tree.insert(v - 1, left_place);
            tree.insert(v, right_place);
            
            res += left_place * left_place + right_place*right_place;
        }
        std::cout << res << '\n';
    }
}

