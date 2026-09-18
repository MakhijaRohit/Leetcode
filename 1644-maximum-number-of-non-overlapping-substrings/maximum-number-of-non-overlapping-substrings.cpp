#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> leftmost(26, n);
        vector<int> rightmost(26, -1);
        
        // Step 1: Record the first and last occurrences of each character
        for (int i = 0; i < n; ++i) {
            int idx = s[i] - 'a';
            leftmost[idx] = min(leftmost[idx], i);
            rightmost[idx] = i;
        }
        
        vector<string> ans;
        int last_right = -1; // Tracks the right boundary of the last added valid substring
        
        // Step 2: Iterate through the string to find and schedule valid intervals
        for (int i = 0; i < n; ++i) {
            // We only need to check intervals starting at the leftmost occurrence of a character
            if (i != leftmost[s[i] - 'a']) {
                continue;
            }
            
            // Expand the right boundary dynamically
            int new_right = checkInterval(s, i, leftmost, rightmost);
            
            if (new_right != -1) {
                // If the new interval starts after the previous one, add it
                if (i > last_right) {
                    ans.push_back(""); 
                }
                // If it overlaps but ends earlier, it is shorter and strictly better
                // So we replace the last added substring with this nested one
                ans.back() = s.substr(i, new_right - i + 1);
                last_right = new_right;
            }
        }
        
        return ans;
    }

private:
    int checkInterval(const string& s, int i, const vector<int>& leftmost, const vector<int>& rightmost) {
        int right = rightmost[s[i] - 'a'];
        for (int j = i; j <= right; ++j) {
            // If a character inside has an occurrence before our start point, this interval is invalid
            if (leftmost[s[j] - 'a'] < i) {
                return -1;
            }
            // Dynamically stretch the right boundary if needed
            right = max(right, rightmost[s[j] - 'a']);
        }
        return right;
    }
};
