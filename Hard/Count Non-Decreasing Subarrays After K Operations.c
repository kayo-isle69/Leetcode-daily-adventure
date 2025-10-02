long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    if (numsSize <= 0) return 0;

    long long ans = 0;
    long long cost = 0;

    int cap = numsSize * 2 + 5;
    int* dq_val = (int*)malloc(sizeof(int) * cap);
    int* dq_cnt = (int*)malloc(sizeof(int) * cap);
    int front = numsSize;
    int back = numsSize;
    
    int j = numsSize - 1;

    for (int i = numsSize - 1; i >= 0; --i) {
        int num = nums[i];
        int count = 1;

        while (back > front && dq_val[back - 1] < num) {
            int nextNum = dq_val[back - 1];
            int nextCount = dq_cnt[back - 1];
            back--;
            count += nextCount;
            cost += (long long)(num - nextNum) * (long long)nextCount;
        }

        dq_val[back] = num;
        dq_cnt[back] = count;
        back++;

        while (cost > k) {
            int rightmostNum = dq_val[front];
            int rightmostCount = dq_cnt[front];
            front++;
            cost -= (long long)(rightmostNum - nums[j]);
            j--;
            if (rightmostCount > 1) {
                front--;
                dq_val[front] = rightmostNum;
                dq_cnt[front] = rightmostCount - 1;
            }
        }

        ans += (long long)(j - i + 1);
    }

    free(dq_val);
    free(dq_cnt);
    return ans;
}