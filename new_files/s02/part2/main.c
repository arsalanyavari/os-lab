#include <stdio.h>

long long int power(int b, int p);

int main(void)
{
    int b, p;
    scanf("%d", &b);
    scanf("%d", &p);

    printf("%lld", power(b, p));
    return 0;
}
