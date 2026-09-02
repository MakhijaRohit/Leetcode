class Solution {
public:
    bool isPalindrome(string s) {
        string s1 = "";
        for (char c : s) {
            if (isalnum(c)) {
                s1 += tolower(c);
            }
        }
        
        int l = 0;
        int r = s1.size() - 1;
        while (l < r) {
            if (s1[l] != s1[r]) return false;
            l++;
            r--;
        }
        return true;
    }
};