class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        // 3 index pointers 
        // pehla num1 k valid element ka last point
        // dusra num2 ka point
        // teesra total length ka last point

        int index_num1 = m - 1;
        int index_num2 = n - 1;
        int index_max  = m + n - 1;

        // Dono me se koi be agar 0 se neeche chale jaaye to break
        while(index_num1 >= 0 && index_num2 >= 0)
        {
            // Agar num1 num2 se bada hai to last pointer me num1 jaayega
            // dono index pointers ko ek se kamm karna padega
            if(nums1[index_num1] > nums2[index_num2])
            {
                nums1[index_max] = nums1[index_num1];
                index_num1 = index_num1 - 1;
                index_max = index_max - 1;
            }
            // Agar num1 num2 se chhoata hai to last pointer me num2 jaayega
            // dono index pointers ko ek se kamm karna padega
            else
            {
                nums1[index_max] = nums2[index_num2];
                index_num2 = index_num2 - 1;
                index_max = index_max - 1;
            }
        }

        // Agar num2 me koi elements bach gye ho to, unko as it is array me daal do
        while(index_num2 >= 0)
        {
            nums1[index_max] = nums2[index_num2];
            index_num2 = index_num2 - 1;
            index_max = index_max - 1;
        }        
    }
};