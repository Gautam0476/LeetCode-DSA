
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        // Two multisets to maintain sliding window median
        multiset<int> low, high;

        long long sumLow = 0, sumHigh = 0;

        // Balance both halves
        auto balance = [&]() {
            int need = (low.size() + high.size() + 1) / 2;

            while (low.size() > need) {
                int val = *low.rbegin();

                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while (low.size() < need) {
                int val = *high.begin();

                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        // Insert element
        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } 
            else {
                high.insert(val);
                sumHigh += val;
            }

            balance();
        };

        // Remove element
        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } 
            else {
                auto it2 = high.find(val);
                high.erase(it2);
                sumHigh -= val;
            }

            balance();
        };

        // Calculate cost of every window
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x)
                remove(nums[i - x]);

            if (i >= x - 1) {

                long long median = *low.rbegin();

                long long leftCost =
                    median * low.size() - sumLow;

                long long rightCost =
                    sumHigh - median * high.size();

                cost[i - x + 1] = leftCost + rightCost;
            }
        }

        // DP for selecting k non-overlapping windows
        const long long INF = 4e18;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {

            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current element
                curr[i] = curr[i - 1];

                // Select window ending at i-1
                if (i >= x) {

                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
