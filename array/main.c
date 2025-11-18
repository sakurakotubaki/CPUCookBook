#include <stdio.h>

int main(void)
{
    int array[10] = { 42, 79, 13 };

    printf("array[0] = %d\n", array[0]);
    printf("array[1] = %d\n", array[1]);
    printf("array[2] = %d\n", array[2]);

    // 他の配列のコピーする
    int copy_array[10];
    for (int i = 0; i < 10; i++) {
        copy_array[i] = array[i];
    }
    printf("copy_array[0] = %d\n", copy_array[0]);
    printf("copy_array[0] = %d\n", copy_array[1]);
    printf("copy_array[0] = %d\n", copy_array[2]);

    return 0;
}
