// https://www.youtube.com/watch?v=jkgZw2WEaqA 

class Solution {
public:
    set<vector<int>> s;
    void getAllCombinations(vector<int>& arr, int index, int target, vector<vector<int>>& ans, vector<int> & combinations)
    {
        if(index == arr.size() || target < 0)
            return;

        if(target == 0)
        {
            if(s.find(combinations) == s.end())
            {
                ans.push_back(combinations);
                s.insert(combinations);
            }
            return;
        }

        combinations.push_back(arr[index]);

        //single inclusion of element
        getAllCombinations(arr, index + 1, target - arr[index], ans, combinations);

        //multiple inclusion of same element
        getAllCombinations(arr, index, target - arr[index], ans, combinations);
        combinations.pop_back();

        // exclusion
        getAllCombinations(arr, index + 1, target, ans, combinations);
    }
    vector<vector<int>> combinationSum(vector<int>& arr, int target) {
        vector<vector<int>> ans;

        vector<int>combinations;

        getAllCombinations(arr, 0, target, ans, combinations);

        return ans;

    }
};