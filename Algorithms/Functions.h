#pragma once

template <typename T> void insertionSort(std::vector<T>& vector) {
	for (int i = 1; i < vector.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (vector[i] < vector[j]) {
				std::swap(vector[i], vector[j]);
			}
		}
	}
}

template <typename T> void bubbleSort(std::vector<T>& vector) {
	bool swapped = false;
	do {
		swapped = false;
		for (int i = 0; i < vector.size() - 1; ++i) {
			if (vector[i] > vector[i + 1]) {
				std::swap(vector[i], vector[i + 1]);
				if (!swapped) {
					swapped = true;
				}
			}
		}
	} while (swapped == true);
}

// This function uses recursiveness
template <typename T> void quickSort(T arr[], int begin, int end) {
	if (begin < end) {
		int pivotIndex = begin;
		for (int i = begin + 1; i <= end; ++i) {
			if (arr[i] < arr[pivotIndex]) {
				for (int j = i; j > pivotIndex; --j) {
					std::swap(arr[j], arr[j - 1]);
				}
				++pivotIndex;
			}
		}
		quickSort(arr, begin, pivotIndex - 1);
		quickSort(arr, pivotIndex + 1, end);
	}
}

template<typename T, size_t N>
constexpr size_t arraySize(T(&)[N]) noexcept {
	return N;
}

template <typename T> void selectionSort(T arr[], int end) {
	int subArrayLastIndex = end;

	for (int i = 0; i <= end; ++i) {
		int currentLargestIndex = 0;
		for (int j = 0; j <= subArrayLastIndex; ++j) {
			if (arr[j] > arr[currentLargestIndex]) {
				currentLargestIndex = j;
			}
		}
		if (subArrayLastIndex > 0) {
			std::swap(arr[subArrayLastIndex], arr[currentLargestIndex]);
			--subArrayLastIndex;
		}
	}

}