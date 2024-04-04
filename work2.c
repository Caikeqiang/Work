#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  

// ����һ�����������ڼ��������������������� 
int maxSubArraySum(int* a, int size) {      
    int max_so_far = a[0];  // ��ʼ������Ϊ����ĵ�һ��Ԫ��  
    int curr_max = a[0];   // ��ʼ����ǰ����Ϊ����ĵ�һ��Ԫ��  

    for (int i = 1; i < size; i++) {  // ������ĵڶ���Ԫ�ؿ�ʼ����  
        // �����ǰ����Ϊ���������ۼӵ�ǰԪ�أ��������¿�ʼ���㵱ǰ����  
        curr_max = (curr_max > 0) ? (curr_max + a[i]) : a[i];
        if (curr_max > max_so_far) {  // �����ǰ���ʹ���ĿǰΪֹ������  
            max_so_far = curr_max;   // ����ĿǰΪֹ������ 
        }
    }

    // ���������ȻС�ڵ���0��˵�����������Ǹ�����������Ϊ�գ�����0  
    // ���򷵻�����  
    return (max_so_far > 0) ? max_so_far : 0;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf_s("%d", &n);

    // ʹ��malloc��̬�����ڴ�  
    int* a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &a[i]);  //VS��ʹ��scanf_s����
    }

    int max_sum = maxSubArraySum(a, n);
    printf("Maximum contiguous sum is %d\n", max_sum);

    // �ͷŶ�̬������ڴ�  
    free(a);

    return 0;
}