class Solution {
public:
    long long countCommas(long long n) {
        long long totalNumCommas = 0;

        for(long long i = 1000; i <= n; i = i * 1000)
        {
            totalNumCommas = totalNumCommas + (n - i + 1); 
        }
        return totalNumCommas;
    }
};