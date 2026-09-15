#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxPalindromes(std::string s, int k) {
        int n = s.length();
        int count = 0;
        int last_end = -1; // Tracks the end index of the last selected palindrome

        // Iterate through each possible center of a palindrome
        for (int i = 0; i < 2 * n - 1; ++i) {
            // For even i, center is a single character s[i/2]
            // For odd i, center is between s[i/2] and s[i/2 + 1]
            int left = i / 2;
            int right = left + (i % 2);

            // Expand outwards from the center
            while (left >= 0 && right < n && s[left] == s[right]) {
                // If the current valid palindrome starts after the last selected palindrome
                if (left > last_end) {
                    int len = right - left + 1;
                    
                    // Check if it satisfies the minimum length requirement
                    if (len >= k) {
                        count++;
                        last_end = right; // Update the boundary
                        break; // Greedily stop expanding for this center
                    }
                } else {
                    // Optimization: If left <= last_end, any further expansion 
                    // will also start before or at last_end, so we can stop.
                    break;
                }
                left--;
                right++;
            }
        }

        return count;
    }
};
