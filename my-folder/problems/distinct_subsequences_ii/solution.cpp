class Solution {
public:
    int distinctSubseqII(string s) {
        int MOD = 1e9 + 7;
        int n = s.length();

        vector<long> dp(n + 1, 0);

        dp[0] = 1;

        vector<int> last(26, -1);

        for(int i = 1; i <= n; i++)
        {
            char ch = s[i - 1];
            int alphaIdx = ch - 'a';

            dp[i] = (dp[i - 1] * 2) % MOD;

            if(last[alphaIdx] != -1)
            {
                int prevIdx = last[alphaIdx];
                dp[i] = (dp[i] - dp[prevIdx] + MOD) % MOD;
            }

            last[alphaIdx] = i - 1;
        }

        return (dp[n] - 1 + MOD) % MOD;
    }
};