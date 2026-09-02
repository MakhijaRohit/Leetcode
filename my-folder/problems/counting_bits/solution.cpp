class Solution {
public:
    vector<int> countBits(int n) {
        vector <int> vect;
        for(int i = 0; i <= n; i++)
        {
            int bitCount = 0;
            unsigned int num = i;
            while(num)
            {
                bitCount = bitCount + (num & 1);
                num = num >> 1;
            }
            vect.push_back(bitCount);
        }
        return vect;
    }
};