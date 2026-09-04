class Solution {
public:
    int expandFromCenter(string s, int left, int right)
    {
        while(left >=0 && right < s.length() && s[left] == s[right])
        {
            left = left - 1;
            right = right + 1;
        }

        return right - left - 1;
    }

    string longestPalindrome(string s) {
        if(s.length() <= 1)
            return s;

        int start = 0;
        int maxLength = 0;

        for(int i = 0; i < s.length(); i++)
        {
            int len1 = expandFromCenter(s, i, i);
            int len2 = expandFromCenter(s, i, i+1);

            int len = max(len1, len2);

            if(len > maxLength)
            {
                maxLength = len;
                start = i - (maxLength - 1) / 2;
            }
        }

        return s.substr(start, maxLength);




        
        
    }
};