#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <omp.h>

using namespace std;

int main()
{
    int n = 1000000;
    vector<int> arr(n);

    // Generate random array
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    cout << "Array size: " << n << endl;
    cout << "\n--- Parallel Reduction Operations ---" << endl;

    // Min operation
    int min_val = INT_MAX;
#pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < n; i++)
    {
        min_val = min(min_val, arr[i]);
    }
    cout << "Min: " << min_val << endl;

    // Max operation
    int max_val = INT_MIN;
#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < n; i++)
    {
        max_val = max(max_val, arr[i]);
    }
    cout << "Max: " << max_val << endl;

    // Sum operation
    long long sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;

    // Average operation
    double average = (double)sum / n;
    cout << "Average: " << average << endl;

    // Count above average
    int count = 0;
#pragma omp parallel for reduction(+ : count)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > average)
        {
            count++;
        }
    }
    cout << "Elements above average: " << count << endl;

    return 0;
}
