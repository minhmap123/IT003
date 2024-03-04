#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

const int limit = 1e6;

void GUI() {
    cout << "Choose which Algorithm you want to calculate execute time !\n";
    cout << "1: Sort C++\n";
    cout << "2: Merge Sort\n";
    cout << "3: HeapSort\n";
    cout << "4: QuickSort\n";
    cout << "Press other keys to exit program\n\n";
    cout << "Your choice: ";
}

void swap(float &a, float &b) {
    float tmp = a;
    a = b;
    b = tmp;
}

int find_pivot_index(float arr[], int low, int high) {
    float pivot = arr[(low + high) / 2];
    int left = low,
        right = high;
    
    while (true) {
        while (left <= right && arr[left] < pivot) 
            ++left;
        while (right >= left && arr[right] > pivot)
            --right;
        
        if (left >= right) break;

        swap(arr[left], arr[right]);
        ++left; --right; 
    }

    // find correct position for pivot
    swap(arr[left], arr[high]);

    return left;    // return pivot's index
}

void QuickSort(float arr[], int low, int high) {
    if (low < high) {
        int key = find_pivot_index(arr, low, high);

        // Sort 2 side of key
        QuickSort(arr, low, key-1);
        QuickSort(arr, key+1, high);
    }
}

float *leftArray = new float[limit/2 + 1];
float *rightArray = new float[limit/2 + 1];

void merge(float arr[], int low, int middle, int high) {
    int len_leftArr = middle - low + 1;
    int len_rightArr = high - middle; 

    for(int i = 0; i < len_leftArr; ++i) 
        leftArray[i] = arr[i + low];
    for(int i = 0; i < len_rightArr; ++i) 
        rightArray[i] = arr[i + middle + 1];

    int leftIndex = 0,
        rightIndex = 0,
        arrIndex = low;

    while (leftIndex < len_leftArr && rightIndex < len_rightArr) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            arr[arrIndex] = leftArray[leftIndex];
            ++leftIndex;
        }
        else {
            arr[arrIndex] = rightArray[rightIndex];
            ++rightIndex;
        }
        ++arrIndex;
    }


    while (leftIndex < len_leftArr) {
        arr[arrIndex] = leftArray[leftIndex];
        ++leftIndex;
        ++arrIndex;
    }   

    while (rightIndex < len_rightArr) {
        arr[arrIndex] = rightArray[rightIndex];
        ++rightIndex;
        ++arrIndex;
    }
}

void MergeSort(float arr[], int low, int high) {
    if (low >= high) 
        return;
    
    int middle = low + (high - low) / 2;
    MergeSort(arr, low, middle);
    MergeSort(arr, middle+1, high);
    merge(arr, low, middle, high);
}

void heapify(float arr[], int N, int index) {
    int parent = index;

    int left  = 2*index + 1,
        right = 2*index + 2;

    if (left < N && arr[left] > arr[parent]) 
        parent = left;

    if (right < N && arr[right] > arr[parent]) 
        parent = right;

    if (parent != index) {
        // find the correct value for parent
        swap(arr[parent], arr[index]);

        // change the child node
        heapify(arr, N, parent);
    }

}

void HeapSort(float arr[], int N) {

    // build max heap
    for (int i = N / 2 - 1; i >= 0; --i)
        heapify(arr, N, i);

    for(int i = N - 1; i > 0; --i) {
        // move root to the back
        swap(arr[0], arr[i]);

        // build max heap again
        heapify(arr, i, 0);
    }
}

int main()
{
    float *arr = new float[limit];
    char sort_case; 

    while (true) {
        GUI();
        cin >> sort_case;
        cout << sort_case << endl;
        if (sort_case < '1' || sort_case > '4') break;

        ifstream inputFile("test_case.txt");
        for (short test_case = 1; test_case <= 10; ++test_case) {
            for(int i = 0; i < limit; ++i) 
                inputFile >> arr[i];

            auto start = high_resolution_clock::now();

            switch (sort_case) {
                case '1': 
                    sort(arr, arr + limit);
                    break;
                
                case '2': 
                    MergeSort(arr,0, limit-1);
                    break;
                
                case '3':
                    HeapSort(arr, limit);
                    break;

                case '4': 
                    QuickSort(arr, 0, limit-1);
                    break;
            }

            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "Sort time [" << test_case << "]:\t" << duration.count() << "\tms" << endl;
        }

        cout << "Finish!";
        cout << "\n\n-----------------------------------------------------------------------------\n\n";
        inputFile.close();
    }

    delete[] arr;   
	return 0;
}
