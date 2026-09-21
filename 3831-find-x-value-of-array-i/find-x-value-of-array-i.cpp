#include <vector>
#include <utility>

class Solution {
public:
    std::vector<long long> resultArray(std::vector<int>& nums, int k) {
        std::vector<long long> ans(k, 0);
        // Both dp arrays MUST share the exact same type: std::vector<long long>
        std::vector<long long> dp(k, 0);

        for (const int num : nums) {
            std::vector<long long> newDp(k, 0);
            int numMod = num % k;

            // Start a new subarray with just the current element
            newDp[numMod] = 1;

            // Transition from previous subarrays
            for (int i = 0; i < k; ++i) {
                if (dp[i] > 0) {
                    int newMod = (static_cast<long long>(i) * numMod) % k;
                    newDp[newMod] += dp[i];
                }
            }

            // Accumulate counts into the final answer array
            for (int i = 0; i < k; ++i) {
                ans[i] += newDp[i];
            }

            // This now moves perfectly since the types match identically
            dp = std::move(newDp);
        }

        return ans;
    }
};
