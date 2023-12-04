#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <random>

// parallel merge sort
void merge(std::vector<int>& nums, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = nums[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = nums[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k] = L[i];
            ++i;
        } else {
            nums[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        nums[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        nums[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(nums, left, mid);
            }
            #pragma omp section
            {
                mergeSort(nums, mid + 1, right);
            }
        }
        merge(nums, left, mid, right);
    }
}

// parallel quick sort
int partition(std::vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1; // index of smaller element

    for (int j = low; j <= high - 1; ++j) {
        if (nums[j] < pivot) { // ascending order
            ++i;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quickSort(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quickSort(nums, low, pi - 1);
            }
            #pragma omp section
            {
                quickSort(nums, pi + 1, high);
            }
        }
    }
}

void quickSort_serial(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);
        quickSort_serial(nums, low, pi - 1);
        quickSort_serial(nums, pi + 1, high);
    }
}

int main() {
    omp_set_num_threads(8);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::vector<int> nums(100000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = dis(gen);
    }
    std::vector<int> nums2(nums);
    std::vector<int> nums3(nums);
    
    // std::cout << "Original array: ";
    // for (int num : nums) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    

    // start = std::chrono::system_clock::now();
    // quickSort_serial(nums3, 0, nums3.size() - 1); // serial quick sort
    // end = std::chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // std::cout << "Time taken by serial quick sort: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::system_clock::now();
    mergeSort(nums, 0, nums.size() - 1); // multi-threaded merge sort
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Time taken by merge sort: " << elapsed_seconds.count() << "s\n";
    
    // std::cout << "Sorted array using merge sort: ";
    // for (int num : nums) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    
    start = std::chrono::system_clock::now();
    quickSort(nums2, 0, nums2.size() - 1); // multi-threaded quick sort
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Time taken by quick sort: " << elapsed_seconds.count() << "s\n";
    
    // std::cout << "Sorted array using quick sort: ";
    // for (int num : nums2) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    return 0;
}