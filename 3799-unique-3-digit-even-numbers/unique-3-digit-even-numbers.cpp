class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> count(10, 0);
        for(int d : digits)
            count[d]++;

        int ans = 0;

        for(int i = 100; i < 1000; i = i + 2)
        {
            int num = i;

            int c = num % 10;
            int b = (num / 10) % 10;
            int a = num / 100;

            vector<int> current_req(10, 0);
            current_req[a]++;
            current_req[b]++;
            current_req[c]++;

            bool possible = true;
            for(int d = 0; d < 10; d++)
            {
                if(current_req[d] > count[d])
                {
                    possible = false;
                    break;
                }
            }

            if(possible)
                ans++;
        }
        return ans;
    }
};