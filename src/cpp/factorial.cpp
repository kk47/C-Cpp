#include <iostream>

using namespace std;

int factorial(int);
int main()
{
    int n = 10;
    int answer;
    answer = factorial(n);
    cout << n << "*" << n - 1 << "... = " << answer << endl;
    return 0;
}

int factorial(int n) {
    int answer = 1;
    if(n==1)
        return answer;
    answer = factorial(n-1)*n;
    return answer;
}
