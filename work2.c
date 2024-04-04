#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  

// 定义一个函数，用于计算给定数组的最大子数组和 
int maxSubArraySum(int* a, int size) {      
    int max_so_far = a[0];  // 初始化最大和为数组的第一个元素  
    int curr_max = a[0];   // 初始化当前最大和为数组的第一个元素  

    for (int i = 1; i < size; i++) {  // 从数组的第二个元素开始遍历  
        // 如果当前最大和为正数，则累加当前元素，否则重新开始计算当前最大和  
        curr_max = (curr_max > 0) ? (curr_max + a[i]) : a[i];
        if (curr_max > max_so_far) {  // 如果当前最大和大于目前为止的最大和  
            max_so_far = curr_max;   // 更新目前为止的最大和 
        }
    }

    // 如果最大和仍然小于等于0，说明所有数都是负数或者数组为空，返回0  
    // 否则返回最大和  
    return (max_so_far > 0) ? max_so_far : 0;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf_s("%d", &n);

    // 使用malloc动态分配内存  
    int* a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &a[i]);  //VS中使用scanf_s函数
    }

    int max_sum = maxSubArraySum(a, n);
    printf("Maximum contiguous sum is %d\n", max_sum);

    // 释放动态分配的内存  
    free(a);

    return 0;
}