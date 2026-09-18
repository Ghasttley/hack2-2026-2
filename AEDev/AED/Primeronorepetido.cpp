//
// Created by LENOVO on 31/08/2026.
//

#include <iostream>
#include <unordered_map>
#include <vector>

void number(std::vector<int> a) {
    std::unordered_map<int, int> l;
    for (int i = 0; i < l.size(); i++) {
        if (l.contains(a[i])) {
            l.at(a[i])++;
        } else {
            l.insert(std::pair<int, int>(a[i], 0));
        }
    }
    int val=-1;
    for (auto & it : l) {
        if (it.second == 0) {
            val = it.first;
            break;
        }
    }
    std::cout << val << std::endl;
}

/*int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> a;
    int cant;
    std::cin >> cant;


    while (cant!=0) {
        int n;
        std::cin >> n;
        a.push_back(n);
        cant--;
    }
    number(a);


}*/
