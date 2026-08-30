class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Map to store: Key = number, value = its index
        std::unordered_map<int, int> num_map;

        for (int i = 0; i < nums.size(); ++i)
        {
            int complement = target - nums[i];

            // Check if the complement already exists in the map
            if (num_map.find(complement) != num_map.end())
            {
                // if found, return the index of the complement and the current index
                return {num_map[complement], i};
            }

            // if not found, store the current number and its index in the map
            num_map[nums[i]] = i;
        }

        return {};
    }
};