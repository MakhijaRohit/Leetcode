class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int total = 0;
        int summation = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            total = total + nums[i];
        }
        summation = (nums.size() * ( nums.size() + 1 )) / 2;
        return summation - total;
    }
};