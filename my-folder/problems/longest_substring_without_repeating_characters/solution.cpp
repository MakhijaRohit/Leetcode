class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0)
            return 0;
        
        if(s.length() == 1)
            return 1;

        int left = 0;
        int right = 1;
        int maxLength = 0;
        unordered_set<char> u_set;
        u_set.insert(s[left]);

        while(right < s.length() && left <= right)
        {
            while(right < s.length() && u_set.find(s[right]) == u_set.end())
            {
                u_set.insert(s[right]);
                right++;
            }

            if(maxLength < (right - left))
                maxLength = right - left;

            u_set.erase(s[left]);
            left++;
        }   
        return maxLength;
    }
};