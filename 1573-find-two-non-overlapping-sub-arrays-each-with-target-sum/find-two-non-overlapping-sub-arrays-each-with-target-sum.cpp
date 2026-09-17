#include <vector>
#include <algorithm>

class Solution {
public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        
        // min_len[i] will store the minimum length of a valid subarray in arr[0...i]
        // Initialize with a large number (1e9) to prevent integer overflow during addition
        std::vector<int> min_len(n, 1e9); 
        
        int ans = 1e9;
        int window_sum = 0;
        int l = 0;
        
        for (int r = 0; r < n; ++r) {
            window_sum += arr[r];
            
            // Shrink the window from the left if the sum exceeds target
            while (window_sum > target) {
                window_sum -= arr[l];
                l++;
            }
            
            // If we found a valid subarray matching the target sum
            if (window_sum == target) {
                int current_len = r - l + 1;
                
                // Check if there is a valid non-overlapping subarray before index 'l'
                if (l > 0 && min_len[l - 1] != 1e9) {
                    ans = std::min(ans, min_len[l - 1] + current_len);
                }
                
                // Update the min length for the current end position 'r'
                min_len[r] = std::min(min_len[r], current_len);
            }
            
            // Propagate the minimum length found so far to the next index
            if (r > 0) {
                min_len[r] = std::min(min_len[r], min_len[r - 1]);
            }
        }
        
        // If ans wasn't updated, it means two non-overlapping subarrays were not found
        return (ans >= 1e9) ? -1 : ans;
    }
};
