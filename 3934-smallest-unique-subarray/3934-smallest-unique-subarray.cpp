
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        if (n == 0) return 0;

        vector<int> sa(n), rank(n), temp(n);

        iota(sa.begin(), sa.end(), 0);

        // Coordinate compression
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        for (int i = 0; i < n; i++) {
            rank[i] = lower_bound(vals.begin(), vals.end(),
                                  nums[i]) - vals.begin();
        }

        // Build suffix array
        for (int k = 1; ; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int x = (a + k < n) ? rank[a + k] : -1;
                int y = (b + k < n) ? rank[b + k] : -1;

                return x < y;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                bool diff = rank[a] != rank[b] ||
                    (a + k < n ? rank[a + k] : -1) !=
                    (b + k < n ? rank[b + k] : -1);

                temp[b] = temp[a] + diff;
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;

            if (k >= n) break;
        }

        // Kasai's algorithm: Build LCP array
        vector<int> pos(n), lcp(n, 0);

        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) continue;

            int j = sa[r - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0) h--;
        }

        // Find shortest unique subarray
        int ans = n;

        for (int i = 0; i < n; i++) {
            int mx = lcp[i];

            if (i + 1 < n)
                mx = max(mx, lcp[i + 1]);

            int len = mx + 1;

            if (len <= n - sa[i])
                ans = min(ans, len);
        }

        return ans;
    }
};
