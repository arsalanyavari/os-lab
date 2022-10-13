long long int power(int b, int p)
{
    long long int ans = 1;
    for (int i = 0; i < p; i++)
        ans *= b;
    return ans;
}
