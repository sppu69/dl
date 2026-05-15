#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int> arr)
{
    int n = arr.size();
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Sequential Bubble Sort Time: " << duration.count() << " ms" << endl;
}

// Parallel Odd-Even Sort (variant of bubble sort)
void parallelBubbleSort(vector<int> arr)
{
    int n = arr.size();
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
#pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        else
        {
#pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Parallel Bubble Sort Time: " << duration.count() << " ms" << endl;
}

int main()
{
    int n = 10000;
    vector<int> arr1(n), arr2(n);

    // Generate random array
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr2[i] = rand() % 1000;
    }

    cout << "Array size: " << n << endl;
    cout << "\n--- Bubble Sort Performance ---" << endl;
    sequentialBubbleSort(arr1);
    parallelBubbleSort(arr2);

    return 0;
}
