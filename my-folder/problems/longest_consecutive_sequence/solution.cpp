class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
            
        sort(nums.begin(), nums.end());
        int count = 1;
        int maxLength = 1;

        for(int i = 0; i < nums.size() - 1; i++)
        {
            if(nums[i] + 1 == nums[i+1])
                count = count + 1;
            else if(nums[i] == nums[i+1] )
                continue;
            else
                count = 1;

            if(maxLength < count)
                maxLength = count;
        }
        return maxLength;
    }
};