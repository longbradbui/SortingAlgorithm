#include <vector>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;
#define ANSI_COLOR_GREEN "\x1b[32m"

template <class T>
void InsertionSort(vector<T>& v) 
{
    int n = v.size();                        //  Assign n as the size of the vector 
    for (int i = 1; i < n; i++) {            //  Outer Loop: Starts from index 1 to the second last index
        int j = i - 1;                       //  The start of inner loop
        T key = v[i];                        //  The KEY component, used as a reference point for the comparison
        while (j >= 0 && v[j] > key) {       //  This gets triggered when: j is still valid AND the lhs value is less than the rhs value
            v[j + 1] = v[j];                 //  -> Swap them [assign lhs value to rhs value]
            --j;                             //  Decrement the position of j, and keeps iterating until one of the condition fails
        }
        v[j + 1] = key;                      //  If not, assign KEY to the next value in the vector
    }
}

template <class T>
void BubbleSort(vector<T>& v)
{
    int n = v.size();                        //  Assign n as the size of the vector 
    for (int i = 0; i < n; i++)              //  Outer Loop: Runs through the vector
    {
        for (int j = 0; j < n - 1; j++) {    //  Inner Loop: Starts from index zero and always stops at the second last index
            if (v[j] > v[j + 1])             //  This get triggered when the value of index on the rhs is less than the lhs
            {
                T temp = v[j];               //  -> Swap them 
                v[j] = v[j + 1];             //  Cons: High number of comparisons. Doesn't take advantage of existing order in the dataset.                                            
                v[j + 1] = temp;             //  Even if the array is partially sorted, it still requires the same number of passes to sort the entire array
            }
        }
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 2000);
    vector<int> randomVector(30000);

    // Fill the vector with random values
    for (int i = 0; i < 30000; ++i) {
        randomVector[i] = distribution(gen);
    }

    // Create a copy of the original vector for BubbleSort
    vector<int> bubbleSortVector = randomVector;
    vector<int> insertionSortVector = randomVector;

    // Measure insertionSort sorting time
    cout << ANSI_COLOR_GREEN << "Starting Insertion Sort . . . ." << endl;
    auto insertionSortStart = chrono::high_resolution_clock::now();
    InsertionSort(insertionSortVector);
    auto insertionSortEnd = chrono::high_resolution_clock::now();
    auto insertionSortDuration = chrono::duration_cast<chrono::milliseconds>(insertionSortEnd - insertionSortStart);
    cout << "Insertion Sort time: " << insertionSortDuration.count() << " milliseconds\n" << endl;

    // Measure BubbleSort sorting time
    cout << ANSI_COLOR_GREEN << "Starting Bubble Sort . . . ." << endl;
    auto bubbleSortStart = chrono::high_resolution_clock::now();
    BubbleSort(bubbleSortVector);
    auto bubbleSortEnd = chrono::high_resolution_clock::now();
    auto bubbleSortDuration = chrono::duration_cast<chrono::milliseconds>(bubbleSortEnd - bubbleSortStart);
    cout << "Bubble Sort time: " << bubbleSortDuration.count() << " milliseconds\n" << endl;

    return 0;
}
