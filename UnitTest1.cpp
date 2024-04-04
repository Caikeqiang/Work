#include "pch.h"  
#include "CppUnitTest.h"  
#include "../work2/work2.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(MaxSubArraySumTests)
    {
    public:

        // 测试情况A: 当前子段和curr_max > 0 且 curr_max > max_so_far  
        TEST_METHOD(TestCaseA_PositiveSubArrayIncreasingMaxSoFar)
        {
            int arr[] = { 1, 2, 3, 4, 5 };
            int size = sizeof(arr) / sizeof(arr[0]);
            int expected = 15;
            int actual = maxSubArraySum(arr, size);
            Assert::AreEqual(expected, actual, L"Positive subarray should increase max_so_far.");
        }

        // 测试情况B: 当前子段和curr_max > 0 但 curr_max <= max_so_far  
        TEST_METHOD(TestCaseB_PositiveSubArrayDoesNotIncreaseMaxSoFar)
        {
            int arr[] = { 5, 1, 3, 4, 2 };
            int size = sizeof(arr) / sizeof(arr[0]);
            int expected = 15; // 5 + 4 + 3  
            int actual = maxSubArraySum(arr, size);
            Assert::AreEqual(expected, actual, L"Positive subarray should not decrease max_so_far if it does not increase it.");
        }

        // 测试情况C: 当前子段和curr_max <= 0 但之前存在更大的max_so_far  
        TEST_METHOD(TestCaseC_NegativeSubArrayWithPreviousMaxSoFar)
        {
            int arr[] = { 5, -1, -3, 4, -2, 2 };
            int size = sizeof(arr) / sizeof(arr[0]);
            int expected = 5; // 4 + 2  
            int actual = maxSubArraySum(arr, size);
            Assert::AreEqual(expected, actual, L"Negative subarray should not affect max_so_far if there was a previous maximum.");
        }

        // 测试情况D: 当前子段和curr_max <= 0 且没有之前的max_so_far（所有元素都是负数或数组为空）  
        TEST_METHOD(TestCaseD_AllNegativeSubArrayOrEmpty)
        {
            int arr[] = { -1, -2, -3, -4, -5 };
            int size = sizeof(arr) / sizeof(arr[0]);
            int expected = 0;
            int actual = maxSubArraySum(arr, size);
            Assert::AreEqual(expected, actual, L"All negative subarray or empty array should return 0.");
        }

        // 假设这是您之前定义的maxSubArraySum函数  
        //extern "C" int maxSubArraySum(int* a, int size);
    };
}