class Solution {
public:
    int hammingWeight(int n) {
        // int count = 0;
        // unsigned int num = n;
        // while(num)
        // {
        //     if(num & 1)
        //         count++;

        //     num = num >> 1;
        // }
        // return count;

        int count = 0;
        while(n)
        {
            n = n & (n - 1);
            count = count + 1;
        }
        return count;
    }
};