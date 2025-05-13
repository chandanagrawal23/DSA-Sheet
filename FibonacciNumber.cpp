class Solution 
{
public:
    // Recursive function to find the nth Fibonacci number
    int fib(int n) 
    {
        // Base cases
        if (n == 0)
        {
            return 0;
        }

        if (n == 1)
        {
            return 1;
        }

        // Recursive call: F(n) = F(n-1) + F(n-2)
        return fib(n - 1) + fib(n - 2);
    }
};
