// https://leetcode.cn/problems/number-of-orders-in-the-backlog/

#include "leetcode.h"

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        multimap<int, int, less<int>> buy;
        multimap<int, int, greater<int>> sell;
        using ir = int&;
        for (int i = 0; i < orders.size(); i++) {
            auto& order = orders[i];
            ir price = order[0], amount = order[1], type = order[2];
            if (type == 0) {
                for (auto it = sell.lower_bound(price); it != sell.end();) {
                    ir delay_amount = orders[it->second][1];
                    if (delay_amount > amount) {
                        delay_amount -= amount;
                        amount = 0;
                        break;
                    }
                    amount -= delay_amount;
                    delay_amount = 0;
                    it = sell.erase(it);
                    if (amount == 0) break;
                }
                if (amount > 0) {
                    buy.insert(make_pair(price, i));
                }
            } else {
                for (auto it = buy.lower_bound(price); it != buy.end();) {
                    ir delay_amount = orders[it->second][1];
                    if (delay_amount > amount) {
                        delay_amount -= amount;
                        amount = 0;
                        break;
                    }
                    amount -= delay_amount;
                    delay_amount = 0;
                    it = buy.erase(it);
                    if (amount == 0) break;
                }
                if (amount > 0) {
                    sell.insert(make_pair(price, i));
                }
            }
        }
        long long ret = 0;
        for (int i = 0; i < orders.size(); i++) {
            ret += orders[i][1];
        }
        return ret % 1000000007;
    }
};

int main() {
    vector<vector<int>> orders = {{10, 5, 0}, {15, 2, 1}, {25, 1, 1}, {30, 4, 0}};
    cout << Solution().getNumberOfBacklogOrders(orders) << endl;  // 6

    orders = {{30, 27, 1}, {18, 9, 1}, {11, 4, 0}, {21, 11, 0}, {1, 1, 1}, {24, 20, 1}, {15, 13, 1}, {13, 3, 0},
            {30, 11, 1}};
    cout << Solution().getNumberOfBacklogOrders(orders) << endl;  // 77

    orders = {{27, 30, 0}, {10, 10, 1}, {28, 17, 1}, {19, 28, 0}, {16, 8, 1}, {14, 22, 0}, {12, 18, 1}, {3, 15, 0},
            {25, 6, 1}};
    cout << Solution().getNumberOfBacklogOrders(orders) << endl;  // 82
}
