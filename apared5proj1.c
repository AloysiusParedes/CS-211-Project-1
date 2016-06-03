#include <stdio.h>
#include <stdlib.h> //to be used for malloc

/***FUNCTION PROTOTYPES***/
void arrayCopy(int fromArray[], int toArray[], int size);
void sort(int arr[], int size);
int linSearch(int arr[], int size, int target, int* numComparisons);
int binSearch(int arr[], int size, int target, int* numComparisons);
void displayArray(int arr[], int size);

int const TERMVAL = -999;   //terminating value for comparisons

int main(void){
    /***VARIABLES***/
    int userInput;          //for user input
    //CHANGE TO CONSTANT
    int size = 100;         //size to grow dynamically
    int count = 0;          //counter

    int *dArr1 = (int *) malloc(sizeof(int) * size);    //dynamic array 1

    //prompt for user input
    printf("Enter values into array. Enter \"-999\" when finished.\n");

    //loop to accept user input and place values into dArr1
    while(userInput != TERMVAL){ //stops when user input is -999
        scanf("%d", &userInput); //accept user input
        if(count >= size){ //check to see if number of inputs exceeds original size of array
            int i; //used in for-loop
            int *temp = (int *) malloc(sizeof(int) * size * 2);  //allocate the larger array space

            for(i = 0; i < size; i++) //loop to copy values to larger array space
                temp[i] = dArr1[i];

            free(dArr1); //return smaller array space to OS

            dArr1 = temp; //set "permanent" array identifier to point to larger space
            size = size * 2; //update size to reflect larger array space
        }
        dArr1[count] = userInput; //add value to array
        count++; //increment counter
    }

    int *dArr2 = (int *) malloc(sizeof(int) * size);    //dynamic array 2

    //copy values from dArr1 to dArr2
    arrayCopy(dArr1, dArr2, count - 1);

    //sort dArr1
    sort(dArr1, count - 1);

    printf("\nSORTED ARRAY\n");
    displayArray(dArr1, count - 1);

    printf("UNSORTED ARRAY\n");
    displayArray(dArr2, count - 1);

    userInput = 0; //reset value for use with next loop

    //prompt for user input for values to search for
    printf("\nEnter values to search for in array. Enter \"-999\" when finished.");
    //loop to search for values
    while(userInput != TERMVAL){
        int positionLin = 0, comparisonsLin = 0;    //variables for linear search
        int positionBin = 0, comparisonsBin = 0;    //variables for binary search

        scanf("%d", &userInput);   //accept user input
        if(userInput == TERMVAL){  //check to see if user input is -999
            printf("PROGRAM FINISHED...\n\n");
            break;
        }

        positionLin = linSearch(dArr2, count - 1, userInput, &comparisonsLin); //search for value using linear search
        positionBin = binSearch(dArr1, count - 1, userInput, &comparisonsBin); //search for value using binary search

        if(positionLin == -1 && positionBin == -1){
            printf("\n%d not found in array. Done in %d comparisons using LINEAR SEARCH\n", userInput, comparisonsLin);
            printf("%d not found in array. Done in %d comparisons using BINARY SEARCH\n\n", userInput, comparisonsBin);

            //reset values for next search
            comparisonsLin = 0;
            positionLin = 0;
            comparisonsBin = 0;
            positionBin = 0;
        }
        else{
            printf("\nLINEAR SEARCH: %d found at index %d. Done in %d comparisons.\n", userInput, positionLin, comparisonsLin);
            printf("BINARY SEARCH: %d found at index %d. Done in %d comparisons.\n\n", userInput, positionBin, comparisonsBin);

            //reset values for next search
            comparisonsLin = 0;
            positionLin = 0;
            comparisonsBin = 0;
            positionBin = 0;
        }
    }

    return 0;
}//end main()

/***FUNCTION DEFINITIONS***/
//function to copy values from one array to another
void arrayCopy(int fromArray[], int toArray[], int size){
    int i;
    for(i = 0; i < size; i++)
        toArray[i] = fromArray[i];
}//end arrayCopy(...)

//function to sort array in ascending order (SELECTION SORT)
void sort(int arr[], int size){
    int i, j, position, swap;

    for(i = 0; i < (size - 1); i++){
        position = i;

        for(j = i + 1; j < size; j++){
           if(arr[position] > arr[j])
               position = j;
        }
        if(position != i){
            swap = arr[i];
            arr[i] = arr[position];
            arr[position] = swap;
        }
    }
}//end sort(...)

//function to search for target value in linear fashion
int linSearch(int arr[], int size, int target, int* numComparisons){
    int i;
    for(i = 0; i < size; i++){
        *numComparisons += 1;
        //printf("Comparing %d with %d\n", target, arr[i]); //FOR DEBUGGING
        if(target == arr[i])
            break;
    }

    if(i == size)
        return -1;
    else
        return i;
}//end linSearch(...)

//function to search for target value in binary fashion
int binSearch(int arr[], int size, int target, int* numComparisons){
    int lower = 0;  //to represent smallest number in array
    int upper = size - 1;   //to represent largest number in array
    int middle = (lower + upper) / 2;   //to represent middle value in array

    while(lower <= upper){
        *numComparisons += 1;
        if(arr[middle] < target)
            lower = middle + 1;
        else if(arr[middle] == target){
            return middle;
            break;
        }
        else
            upper = middle - 1;

        middle = (lower + upper) / 2;
    }

    if(lower > upper)
        return -1;
}//end binSearch(...)

//FOR DEBUGGING; function to display array
void displayArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%d. %d\n", i, arr[i]);
    printf("\n");
}//end displayArray(...)
