#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    int n, m, opponent_taken;
    // 读取总物品数n和至多拿的件数m
    scanf("%d%d", &n, &m);
    // 巴什博弈算法，计算第一步应该拿的数量
    int my_taken = (n % (m + 1) != 0) ? (n % (m + 1)) : 1;
    n -= my_taken;
    // 输出第一步拿的物品的数量
    printf("%d\n", my_taken);
    fflush(stdout);
    // 不断交替进行拿取，直到所有物品拿完为止
    while (1)
    {
        scanf("%d", &opponent_taken); // 读取对手拿的物品数量
        n -= opponent_taken;          // 计算剩余物品数量
        if (n <= 0)
        {
            break; // 若无剩余物品，则结束循环
        }
        // 根据剩余物品数量计算下一步应该拿的数量
        my_taken = (n % (m + 1) != 0) ? (n % (m + 1)) : 1;
        // 输出下一步拿的物品数量
        printf("%d\n", my_taken);
        n -= my_taken;
        if (n <= 0)
        {
            break; // 若无剩余物品，则结束循环
        }
        fflush(stdout);
    }

    return 0;
}