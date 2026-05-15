#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;

void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int i = left, k = 0; i <= right; i++, k++)
    {
        arr[i] = temp[k];
    }
}

void sequentialMergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(vector<int> &arr, int left, int right, int depth)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        if (depth < 4)
        { // Limit parallelism depth
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);

#pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        }
        else
        {
            parallelMergeSort(arr, left, mid, depth + 1);
            parallelMergeSort(arr, mid + 1, right, depth + 1);
        }

        merge(arr, left, mid, right);
    }
}

int main()
{
    int n = 100000;
    vector<int> arr1(n), arr2(n);

    // Generate random array
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr2[i] = rand() % 10000;
    }

    cout << "Array size: " << n << endl;
    cout << "\n--- Merge Sort Performance ---" << endl;

    auto start = chrono::high_resolution_clock::now();
    sequentialMergeSort(arr1, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    auto dur1 = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Sequential Merge Sort Time: " << dur1.count() << " ms" << endl;

    start = chrono::high_resolution_clock::now();
    parallelMergeSort(arr2, 0, n - 1, 0);
    end = chrono::high_resolution_clock::now();
    auto dur2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Parallel Merge Sort Time: " << dur2.count() << " ms" << endl;

    cout << "Speedup: " << (float)dur1.count() / dur2.count() << "x" << endl;

    return 0;
}
