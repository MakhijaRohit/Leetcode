class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        for(int i = 0; i < nums.size(); i++)
        {
            int maximum = 0;
            int minimum = nums[i];
            for(int j = 0; j <= i; j++)
            {
                if(maximum < nums[j])
                {
                    maximum = nums[j];
                }
            }

            for(int k = i; k < nums.size(); k++)
            {
                if(minimum > nums[k])
                {
                    minimum = nums[k];
                }
            }

            if((maximum - minimum) <= k)
                return i;
        }
        return -1;
    }
};