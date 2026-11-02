
class Solution {
public:
    int minMoves2(vector<int>& nums) {

        int n = nums.size();

        // Find median using nth_element
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());

        int median = nums[n / 2];

        long long ans = 0;

        // Calculate total distance from median
        for (int i = 0; i < n; i++) {
            ans += abs(nums[i] - median);
        }

        return ans;
    }
};
