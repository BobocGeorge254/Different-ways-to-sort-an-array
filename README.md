# Different-ways-to-sort-an-array
Let's find out together which is the fastest sorting method by running some basic tests.
First let's see how each algorithm it's supposed to work.

Merge Sort - sorting algorithm based on divide and conquer method. You divide each array into two halves recursively until you reach sub-arrays of one element, which are obviously sorted. Then you merge the two little sub-arrays obtaining a bigger sorted sub-array and so on, until you build up the entire solution. Average complexity - O(nlogn).


Quick Sort - sorting algorithm based on divide and conquer method. At each step you choose an element called "pivot", then partitions the given array around the pivot, meaning that the pivot it's in its correct position and all smaller elements are on its left side and all bigger elements are on its right side. Similar to Merge Sort, you recursively do the same thing for each sub-array (on the left and on the right side of the pivot), until you build the sorted array. Avarage complexity - O(nlogn), Worst case - O(n^2).


Radix Sort - sorting algorithm that sorts numbers based on the position of their digits, with no comperisions. It avoids comparison by creating and distributing elements into buckets according to their radix. For elements with more than one significant digit, this bucketing process is repeated for each digit, while preserving the ordering of the prior step, until all digits have been considered. Radix sort uses a stable sorting algorithm as a subrutine in order to sort the digits in every position. For this test I used counting sort. Average complexity ~ O(n)


Insertion Sort - insertion sort iterates, consuming one input element each repetition, and grows a sorted output list. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain. Average complexity - O(n^2)


Shell Sort - it can be seen as either a generalization of sorting by exchange or sorting by insertion. The method starts by sorting pairs of elements far apart from each other, then progressively reducing the gap between elements to be compared. Average complexity - O(n log^2 n)

Here are the results.

Test 1 -  50 elements<br>
MergeSort: 0.000000 seconds <br>
QuickSort - non-randomised pivot: 0.000000 seconds <br>
QuickSort - randomised pivot: 0.000000 seconds <br>
RadixSort - base 10: 0.000000 seconds <br>
RadixSort - base 2^16: 0.000000 seconds <br>
ShellSort: 0.000000 seconds <br>
InsertionSort: 0.000000 seconds <br>
STLSort: 0.000000 seconds <br>


Test 2 -  100 elements<br>
MergeSort: 0.000000 seconds <br>
QuickSort - non-randomised pivot: 0.000000 seconds <br>
QuickSort - randomised pivot: 0.000000 seconds<br>
RadixSort - base 10: 0.000000 seconds<br>
RadixSort - base 2^16: 0.000000 seconds<br>
ShellSort: 0.000000 seconds<br>
InsertionSort: 0.000000 seconds<br>
STLSort: 0.000000 seconds<br>

Test 3 -  1000 elements<br>
MergeSort: 0.000000 seconds<br>
QuickSort - non-randomised pivot: 0.000000 seconds<br>
QuickSort - randomised pivot: 0.000000 seconds<br>
RadixSort - base 10: 0.000000 seconds<br>
RadixSort - base 2^16: 0.000000 seconds<br>
ShellSort: 0.000000 seconds<br>
InsertionSort: 0.015000 seconds<br>
STLSort: 0.000000 seconds<br>

Test 4 -  10000 elements<br>
MergeSort: 0.022000 seconds<br>
QuickSort - non-randomised pivot: 0.000000 seconds<br>
QuickSort - randomised pivot: 0.015000 seconds<br>
RadixSort - base 10: 0.000000 seconds<br>
RadixSort - base 2^16: 0.016000 seconds<br>
ShellSort: 0.000000 seconds<br>
InsertionSort: 0.202000 seconds<br>
STLSort: 0.000000 seconds<br>

Test 5 -  100000 elements<br>
MergeSort: 0.116000 seconds<br>
QuickSort - non-randomised pivot: 0.020000 seconds<br>
QuickSort - randomised pivot: 0.061000 seconds<br>
RadixSort - base 10: 0.050000 seconds<br>
RadixSort - base 2^16: 0.010000 seconds<br>
ShellSort: 0.047000 seconds<br>
InsertionSort: 19.934000 seconds<br>
STLSort: 0.038000 seconds<br>

Test 6 -  1000000 elements<br>
MergeSort: 1.115000 seconds<br>
QuickSort - non-randomised pivot: 0.273000 seconds<br>
QuickSort - randomised pivot: 0.702000 seconds<br>
RadixSort - base 10: 0.527000 seconds<br>
RadixSort - base 2^16: 0.110000 seconds<br>
ShellSort: 0.692000 seconds<br>
InsertionSort: 2035.631411 seconds<br>
STLSort: 0.385000 seconds<br>

Test 7 -  10000000 elements<br>
MergeSort: 11.734000 seconds<br>
QuickSort - non-randomised pivot: 4.055000 seconds<br>
QuickSort - randomised pivot: 9.023000 seconds<br>
RadixSort - base 10: 5.262000 seconds<br>
RadixSort - base 2^16: 1.060000 seconds<br>
ShellSort: 12.389000 seconds<br>
InsertionSort: failed<br>
STLSort: 4.208000 seconds<br>

Test 8 -  15000000 elements<br>
MergeSort: 17.870000 seconds<br>
QuickSort - non-randomised pivot: 7.107000 seconds<br>
QuickSort - randomised pivot: 14.231000 seconds<br>
RadixSort - base 10: 7.145000 seconds<br>
RadixSort - base 2^16: 1.410000 seconds<br>
ShellSort: 15.284000 seconds<br>
InsertionSort: failed<br>
STLSort: 5.921000 seconds<br>


Let's start by getting the Insertion Sort out of the way. Being the only algorithm with a complexity of O(n^2), Insertion Sort can't stand a chance in front of the other faster sorting algorithms, at least when we talk about large input of numbers. When sorting an array of 10^5 elements the difference is already noticeable, taking about 20 seconds to do the exact same thing that every other algorithm does in less then a second. The number of operations that this algorithm does is proportional to the square of the sorted numbers, thus sorting an array with 10 times as many numbers will take approximately 100 as much time, as we can see between test 5 and 6, making it useless for sorting large arrays of numbers. On the other hand, the constant in front of the n^2, which as we know, does not have any effect on theoretical complexity, but can very well impact the time efficiency, is relatively smaller to other sorting algorithms, making it a "not so bad" option for sorting smaller amounts of data.

Now let's talk about the O(nlogn) class of complexity, comparing Merge Sort with Quick Sort and Shell Sort. <br>
I decided to implement a Quick Sort algorithm with the pivot being a fixed number every time ( the rightmost element ), and another one with pivot being a random number in the array. As expected, for random data in the array, there is no difference in between the two, even though the second one might be better in some specific cases, like when the array is sorted in descending order. Note that Quick Sort is very unstable, and poor choices of the pivot might result in huge time gaps, but for the avarage case it's still the fastest of all three for medium and larger arrays. Shell Sort and Merge Sort have very similar results timewise, but it's worth saying that the second uses another auxiliary array for the Merge operation, making it problematic when we already work with huge arrays. Since Shell Sort is a particularisation of the Insertion Sort, it is as well used to sort smaller amounts of data, with close or even better results then any other O(nlogn) algorithm.


Now, as expected, being the algorithm with the best average complexity, Radix Sort it's the fastest of all sorting algorithms. Even though the base 10 algorithm has similar results to Quick Sort, it has the advantage to be more stable for the worst case, but the disadvantage to use auxiliary arrays . Similarly, the base 2^16 algorithm has the same advantages and disadvantages, but the trade-off between time and memory might recommend it as the best sorting algorithm in general.
