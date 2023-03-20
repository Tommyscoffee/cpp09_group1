#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <cstdlib>
#include <vector>
// # define debug std::cout << "DEBUG [" << __FILE__ << ":" << __LINE__ << "] "
# define THRESHOLD 1000
# define ERROR 1
# define SUCCESS 0

template <typename T> void  mergeSort(T & arr, int left, int mid, int right)//再帰で一番小さいセクションの２つを比較する
{
    std::deque<int> deq;
    int i = left, j = mid + 1;
    
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            deq.push_back(arr[i]);
            i++;
        } else {
            deq.push_back(arr[j]);
            j++;
        }
    }
    
    while (i <= mid) {
        deq.push_back(arr[i]);
        i++;
    }
    
    while (j <= right) {
        deq.push_back(arr[j]);
        j++;
    }
    for (int k = left; k <= right; k++) {
        arr[k] = deq.front();
        deq.pop_front();
    }
}

template <typename T> void insertionSortDeq(T &deque, int left, int right)
{
    for (int i = left + 1; i <= right; ++i) {
        int key = deque[i];
        int j = i - 1;
        
        while (j >= left && deque[j] > key) {
            deque[j+1] = deque[j];
            j--;
        }
        
        deque[j+1] = key;
    }
}

// マージソートの再帰的処理
template <typename T> void mergeInsertionSort(T& arr, int left, int right)
{
	if (left < right)
	{
		if (right - left + 1 <= THRESHOLD)
			insertionSortDeq(arr, left, right);
		else
		{
			int mid = (left + right) / 2;
			mergeInsertionSort(arr, left, mid);
			mergeInsertionSort(arr, mid + 1, right);
			mergeSort(arr, left, mid, right);
		}
	}
}

template <typename T> bool isSorted(T& arr)
{
	size_t	i = 1;

	for(;i < arr.size() - 1; i++)
	{
		if (arr[i - 1] >= arr[i])
		{
			std::cout << "Error: Not Sorted Error " << " arr[i - 1] = " << arr[i - 1] << " arr[i] = " << arr[i] << std::endl;   
			return (ERROR);
		}
	}
	std::cout << "OK!! Sorted" << std::endl;
	return (SUCCESS);
}

bool isInvalidNum(char *str);
bool isDuplicate(std::deque<int> &deq, int num);
void putArr(std::string str, std::deque<int> vec);

#endif