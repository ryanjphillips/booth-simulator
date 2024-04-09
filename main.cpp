// Includes:

#include <iostream>   
#include <algorithm>  // For std::reverse
#include <string>     

using namespace std;
 
// Function to add the contents of the multiplicand to the accumulator.
//
void add(int accumulator[], int x[], int multiplierLength)
{
    int i; 
    int c = 0;
     
    for (i = 0; i < multiplierLength; i++) {
         
        accumulator[i] = accumulator[i] + x[i] + c;
         
        if (accumulator[i] > 1) {
            accumulator[i] = accumulator[i] % 2;
            c = 1;
        }
        else
            c = 0;
    }
}

// Function that gives the compplement of an array. This is used before the start of the algo loop.
// Second have is the same as the add function, but reversed because the multiplicand is reversed at the begging.
 
void complement(int a[], int n)
{
    int increment;
    int x[n] = {0};
    x[n - 1] = 1;
     
    for (increment = 0; increment < n; increment++) {
        a[increment] = (a[increment] + 1) % 2;
    }

    int i, c = 0;
     
    for (i = n - 1; i >= 0 ; i--) {
         
        a[i] = a[i] + x[i] + c;
         
        if (a[i] > 1) {
            a[i] = a[i] % 2;
            c = 1;
        }
        else
            c = 0;
    }

}

// Function that multiplies the multiplicand by 2 or logical shift left.
// Note: Multiplicand is in reverse, so multiplicand[length] is least MSB.

void logicalShiftLeft(int multiplicand[], int multiplicandLength) {

    int temp;
    int i;

    // Loops through reversed adding 0 to the LSB.
    for (i = multiplicandLength; i > 0; i--) {
        multiplicand[i] = multiplicand[i - 1];
    }

    multiplicand[0] = 0;
}


// Function that does a right shift.
// Note: This is an arithmetic right shift the value of the MSB is going to be inputted at the end of the word.

void arithmeticRightShft(int accumulator[], int multiplier[], int& E, int multiplierLength)
{
    int temp, i;
    temp = accumulator[0];
    E = multiplier[0];
     
    for (i = 0; i < multiplierLength - 1; i++) {
        accumulator[i] = accumulator[i + 1];
        multiplier[i] = multiplier[i + 1];
    }
    multiplier[multiplierLength - 1] = temp;
}
 
// Funciton that cout's the accumulator and the multiplier.

void display(int accumulator[], int multiplier[], int multiplierLength)
{
    int i;
     
    // accumulatorcumulator content
    for (i = multiplierLength - 1; i >= 0; i--)
        cout << accumulator[i];
    cout << "\t";
     
    // multiplier content
    for (i = multiplierLength - 1; i >= 0; i--)
        cout << multiplier[i];
}
 
// Function to implement Booth's Algorithm, not the modified version.

void boothAlgorithm(int multiplicand[], int multiplier[], int multiplicandComp[], int multiplierLength, int multiplicandLength, int sequenceCounter, int addCount, int subCount)
{
 
    int E = 0; 
    int accumulator[multiplicandLength] = { 0 };
    int temp = 0;
    cout << "q[n+1]\tE\tmultiplicand\tAC\tmultiplier\tsequenceCounter\n";
    cout << "\t\tinitial\t\t";
     
    display(accumulator, multiplier, multiplierLength);
    cout << "\t\t" << sequenceCounter << "\n";
     
    // Everytime we ASHR decrease the Sequence Counter
    while (sequenceCounter != 0) {
        cout << multiplier[0] << "\t" << E;
         
        // If 01 OR 10
        if ((E + multiplier[0]) == 1)
        {
            // 10
            if (temp == 0) {
                 
                add(accumulator, multiplicandComp, multiplierLength);
                subCount += 1;
                cout << "\tSub Counter: \t" << subCount << "\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];
                temp = 1;
            }
             
            // 01
            else if (temp == 1)
            {
                // add multiplicand to accumulatorcumulator
                add(accumulator, multiplicand, multiplierLength);
                addCount += 1;
                cout << "\tAdd Counter:" << addCount << "\t" ;
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];
                temp = 0;
            }
            cout << "\n\t";
            cout << "\tRight Shift\t";
            arithmeticRightShft(accumulator, multiplier, E, multiplierLength);
        }
         
        // 00 No Action, Shift Right AND 11 No Action, Shift Right
        else if (E - multiplier[0] == 0)
            cout << "\tRight Shift\t";
            arithmeticRightShft(accumulator, multiplier, E, multiplierLength);
        
        display(accumulator, multiplier, multiplierLength);
        
        cout << "\t";
         
        // decrement counter
        sequenceCounter--;
        cout << "\t" << sequenceCounter << "\n";
    }
}

// Function to take a string and make an array from it. 

void populateBinaryArray(int binaryNumberArray[], int size, string binaryNumber){

    for (int x = 0; x < size; x++) {
        char binaryChar = binaryNumber[x];
        int binaryNumb = binaryChar - '0';
        binaryNumberArray[x] = binaryNumb;
    }
}
 
int main()
{
    // Pre-initialize Booth's Algorithm. 
    // Set the lengths of the multiplier and multiplicand.
    // Calculate the Two's complement of the multiplicnad.
    
    string stringMultiplicand = "11101";
    string stringMultiplier = "110111";
    int multiplierLength = stringMultiplier.length();
    int multiplicandLength = stringMultiplicand.length();
    int addCount = 0;
    int subCount = 0;

    // Move strings into bit array.
    
    int* multiplicand = new int[multiplicandLength];
    populateBinaryArray(multiplicand, multiplicandLength, stringMultiplicand);

    int* multiplier = new int[multiplierLength];
    populateBinaryArray(multiplier, multiplierLength, stringMultiplier);

    int multiplicandComp[multiplicandLength]; 
    int sequenceCounter;
    
    // Create additional array of multiplicand.
    
    for (int i = multiplicandLength - 1; i >= 0; i--) {
        multiplicandComp[i] = multiplicand[i]; 
    }

    // Reverse arrays and get Two's Complement of multiplicand.
    reverse(multiplicand, multiplicand + multiplicandLength);
    complement(multiplicandComp, multiplicandLength);
    sequenceCounter = multiplierLength;
    reverse(multiplier, multiplier + multiplierLength);
    reverse(multiplicandComp, multiplicandComp + multiplicandLength);

    // Call the main loop, Booth's Algorith.
    boothAlgorithm(multiplicand, multiplier, multiplicandComp, multiplierLength, multiplicandLength, sequenceCounter, addCount, subCount);
}
