class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = min(n, 2);
        int left = 0;

        for (int right = 0; right < n; right++) {
            int lastConflict = -1;

            for (int i = left; i < right; i++) {
                if (gcd(nums[i], nums[right]) > 1) {
                    lastConflict = i;
                }
            }

            left = max(left, lastConflict + 1);

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};