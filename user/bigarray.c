#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


#define ARR_SIZE (1 << 16) // 2^16 elements = 65536
#define NUM_CHILD 4

int main()
{
    int *bigarray = malloc(ARR_SIZE * sizeof(int));
    //int bigarray[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++)
    {
        bigarray[i] = i;
    }

    int child_pids[NUM_CHILD];
    int ret = forkn(NUM_CHILD, child_pids);
    if (ret < 0)
    {
        printf("forkn failed\n");
        exit(1, "forkn failed\n");
    }
    else if (ret == 0)
    {
        // Parent process
        
        int n;
        int child_statuses[NUM_CHILD];
        if (waitall(&n, child_statuses) < 0)
        {
            printf("waitall failed\n");
            exit(1, "waitall failed\n");
        }

        int total_sum = 0;
        for (int i = 0; i < n; i++)
        {
            total_sum += child_statuses[i];
        }
        printf("Parent: Total sum = %d\n", total_sum);

        free(bigarray);
        exit(0, "Parent finished\n");
    }
    else
    {
        // Child processes
        
        int start = (ret - 1) * (ARR_SIZE / NUM_CHILD);
        int end = ret * (ARR_SIZE / NUM_CHILD);
        
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += bigarray[i];
        }
        printf("Child number %d: %d\n", ret, sum);
        exit(sum, "Child finished\n");
    }
}
