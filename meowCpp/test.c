#include <stdio.h>
#include <stdlib.h>

// 计算阶乘
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 判断是否为素数
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// 斐波那契数列
int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    printf("数字运算演示程序\n");
    printf("================\n");
    
    // 测试阶乘函数
    printf("5的阶乘: %d\n", factorial(5));
    
    // 查找并输出1-100之间的素数
    printf("1-100之间的素数: ");
    for (int i = 1; i <= 100; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    // 输出斐波那契数列前10项
    printf("斐波那契数列前10项: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    
    // 数组操作示例
    int arr[5] = {3, 1, 4, 1, 5};
    int sum = 0;
    printf("数组元素: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
        sum += arr[i];
    }
    printf("\n数组元素总和: %d\n", sum);
    
    // 简单的排序
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    printf("排序后的数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}