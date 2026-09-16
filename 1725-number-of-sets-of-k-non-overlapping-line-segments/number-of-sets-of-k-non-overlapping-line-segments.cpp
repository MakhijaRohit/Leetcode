class Solution {
public:
    int numberOfSets(int n, int k) {
        long long MOD = 1e9 + 7;
        
        // The problem is equivalent to choosing 2k points out of (n + k - 1) points
        int total_points = n + k - 1;
        int target_choose = 2 * k;
        
        if (total_points < target_choose) return 0;
        
        // Compute nCr (total_points Choose target_choose) % MOD
        return nCr(total_points, target_choose, MOD);
    }
    
private:
    // Helper function to calculate combinations using modular inverse
    long long nCr(int n, int r, long long MOD) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r; // Optimize symmetry
        
        long long num = 1, den = 1;
        for (int i = 0; i < r; i++) {
            num = (num * (n - i)) % MOD;
            den = (den * (i + 1)) % MOD;
        }
        
        return (num * modInverse(den, MOD)) % MOD;
    }
    
    // Fermat's Little Theorem for Modular Inverse
    long long modInverse(long long n, long long MOD) {
        return power(n, MOD - 2, MOD);
    }
    
    long long power(long long base, long long exp, long long MOD) {
        long long res = 1;
        base = base % MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }
};
