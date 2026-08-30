class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int min_index = 0;
        int max_index = 0;

        for (int i = 0; i < n; ++i)
        {
            if(nums[i] < nums[min_index])
            {
                min_index = i;
            }

            if(nums[i] > nums[max_index])
            {
                max_index = i;
            }
        }
        int a = min(min_index, max_index);
        int b = max(min_index, max_index);
        
        int op1 = b + 1;

        int op2 = n - a;

        int op3 = (a + 1) + (n - b);

        return min({op1, op2, op3});
    }
};