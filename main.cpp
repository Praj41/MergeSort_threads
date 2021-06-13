#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#define int64_t long long int

#include "RNG.h"
#include "Timer.h"

void merge(int64_t arr[], int64_t l, int64_t m, int64_t r)
{
    int64_t i, j, k;
    int64_t n1 = m - l + 1;
    int64_t n2 = r - m;

    /* create temp arrays */
    auto *L = new int64_t[n1], *R = new int64_t[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;

}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int64_t arr[], int64_t l, int64_t r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int64_t m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int64_t partition (int64_t arr[], int64_t low, int64_t high)
{
    int64_t pivot = arr[high]; // pivot
    int64_t i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int64_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int64_t arr[], int64_t low, int64_t high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int64_t pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<void (*sorter) (int64_t*, int64_t, int64_t)>
void scheduler(int64_t *arr, int64_t size) {

    size_t x[8], y[8];
    std::vector<std::thread> work;

    for (size_t i = 0, j = 0; i < size && j < 8; j++) {
        x[j] = i;
        y[j] = (((i += (size / 8)) > size) ? size : i) - 1;
    }

    y[7] = size - 1;

    for (int i = 0; i < 8; ++i) {
        work.emplace_back(sorter, arr, x[i], y[i]);
    }

    for (auto &workThread : work)
        workThread.join();

    work.clear();

    for (int i = 0; i < 8; i += 2) {
        work.emplace_back(merge, arr, x[i], y[i], y[i + 1]);
    }

    for (auto &workThread : work)
        workThread.join();

    work.clear();

    for (int i = 0; i < 8; i += 4) {
        work.emplace_back(merge, arr, x[i], y[i + 1], y[i + 3]);
    }

    for (auto &workThread : work)
        workThread.join();

    work.clear();

    merge(arr, x[0], y[3], y[7]);

}

void printArr(long long int *arr, long long int size) {
    for (long long int i = 0; i < size; ++i) {
        printf("%lld\n", arr[i]);
    }
}

void checkSorted(const long long int *arr, long long int size) {
    for (long long int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]){
            printf("Not sorted\n");
            return;
        }
    }
    printf("Sorted!!!!!\n");
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    using namespace std::chrono_literals;

    int64_t size = 40960000;

    //std::cin >> size;

    auto *arr = RNG(size, INT32_MIN, INT32_MAX);

    auto *arr1 = (int64_t*) malloc(sizeof(int64_t) * size);
    std::memcpy(arr1, arr, sizeof(int64_t) * size);
    Timer t;

    //printArr(arr, size);

    //checkSorted(arr, size);
    printf("Cool Down time : ");
    std::this_thread::sleep_for(5s);
    t.lap_reset();
    scheduler<quickSort> (arr1, size);
    printf("Quick Sort time : ");
    t.lap_reset();
    printf("Cool Down time : ");
    std::this_thread::sleep_for(5s);
    t.lap_reset();
    scheduler<mergeSort> (arr, size);
    //mergeSort(arr, 0, size - 1);

    //std::sort(arr, arr + size);

    printf("Merge Sort time : ");
    t.lap_reset();

    checkSorted(arr, size);
    checkSorted(arr1, size);
    //std::cout << "\n\n\nSorted array here!!!" << std::endl;

    //printArr(arr, size);

    delete[] arr;

    //system("pause");

    return 0;
}
