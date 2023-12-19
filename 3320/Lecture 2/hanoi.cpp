#include <vector>
#include <stdio.h>

void hanoi(int n, int src, int dst, int tmp)
{
    if (n==0) return;
    hanoi(n-1, src, tmp, dst);
    printf("disk %d: peg %d -> %d\n", n, src, dst);
    hanoi(n-1, tmp, dst, src);
}


int main()
{
    hanoi(3,0,2,1);
}
