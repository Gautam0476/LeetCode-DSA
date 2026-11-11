
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long ans = LLONG_MAX;

        // Option 1: Buy only individual items
        ans = min(ans, 1LL * need1 * cost1 +
                       1LL * need2 * cost2);

        // Option 2: Buy common items for the minimum requirement
        int mn = min(need1, need2);
        int mx = max(need1, need2);

        ans = min(ans, 1LL * mn * costBoth +
                       1LL * (need1 - mn) * cost1 +
                       1LL * (need2 - mn) * cost2);

        // Option 3: Buy common items for the maximum requirement
        ans = min(ans, 1LL * mx * costBoth);

        return ans;
    }
};
