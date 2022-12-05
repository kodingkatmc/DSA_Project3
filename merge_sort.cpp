// FIXME: Implement Stuff


// Borrowing structure from merge sort pseudocode on Sorting PPT page 88
void merge(int numbers[], int left, int middle, int right) {
    // TODO: Create merge function
}

void mergeSort(int numbers[], int start, int end) {

    if ( start < end ) { // Base case for array size 1
        int middle = start + (end - start) / 2; // Use this formula for average to prevent integer overflow
        mergeSort(numbers, start, middle);
        mergeSort(numbers, middle + 1, end);
        merge(numbers, start, middle, end);
    }
}

