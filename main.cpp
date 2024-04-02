// CPP code to implement booth's algorithm
#include <bits/stdc++.h>
 
using namespace std;
 
// function to perform adding in the accumulatorcumulator
void add(int accumulator[], int x[], int multiplierLength)
{
    int i, c = 0;
     
    for (i = 0; i < multiplierLength; i++) {
         
        // updating accumulatorcumulator with A = A + multiplicand
        accumulator[i] = accumulator[i] + x[i] + c;
         
        if (accumulator[i] > 1) {
            accumulator[i] = accumulator[i] % 2;
            c = 1;
        }
        else
            c = 0;
    }
}
 
// function to find the number's complement
void complement(int a[], int n)
{
    int increment;
    int x[8] = {0};
    x[0] = 1;
     
    for (increment = 0; increment < n; increment++) {
        a[increment] = (a[increment] + 1) % 2;
        cout << a[increment] << endl;
    }
    add(a, x, n);
}
 
// function to perform right shift
void arithmeticRightShft(int accumulator[], int multiplier[], int& E, int multiplierLength)
{
    int temp, i;
    temp = accumulator[0];
    E = multiplier[0];
     
    cout << "\t\tarithmeticRightShft\t";
     
    for (i = 0; i < multiplierLength - 1; i++) {
        accumulator[i] = accumulator[i + 1];
        multiplier[i] = multiplier[i + 1];
    }
    multiplier[multiplierLength - 1] = temp;
}
 
// function to display operations
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
 
// Function to implement booth's algo
void boothAlgorithm(int multiplicand[], int multiplier[], int multiplicandComp[], int multiplierLength, int multiplicandLength, int sequenceCounter)
{
 
    int E = 0; 
    int accumulator[multiplicandLength] = { 0 };
    int temp = 0;
    cout << "E\tq[n+1]\t\tmultiplicand\t\tAC\tmultiplier\t\tsequenceCounter\n";
    cout << "\t\t\tinitial\t\t";
     
    display(accumulator, multiplier, multiplierLength);
    cout << "\t\t" << sequenceCounter << "\n";
     
    // Everytime we ASHR decrease the Sequence Counter
    while (sequenceCounter != 0) {
        cout << multiplier[0] << "\t" << E;
         
        // If 01 OR 10
        if ((E + multiplier[0]) == 1)
        {
            if (temp == 0) {
                 
                add(accumulator, multiplicandComp, multiplierLength);
                cout << "\t\tA = A - multiplicand\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];
                temp = 1;
            }
             
            // THIRD CONDITION
            else if (temp == 1)
            {
                // add multiplicand to accumulatorcumulator
                add(accumulator, multiplicand, multiplierLength);
                cout << "\t\tA = A + multiplicand\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];
                temp = 0;
            }
            cout << "\n\t";
            arithmeticRightShft(accumulator, multiplier, E, multiplierLength);
        }
         
        // 00 No Action, Shift Right AND 11 No Action, Shift Right
        else if (E - multiplier[0] == 0)
            arithmeticRightShft(accumulator, multiplier, E, multiplierLength);
        
        display(accumulator, multiplier, multiplierLength);
        
        cout << "\t";
         
        // decrement counter
        sequenceCounter--;
        cout << "\t" << sequenceCounter << "\n";
    }
}

void populateBinaryArray(int binaryNumberArray[], int size, string binaryNumber){
    for (int x = 0; x < size; x++) {
        char binaryChar = binaryNumber[x];
        int binaryNumb = binaryChar - '0';
        binaryNumberArray[x] = binaryNumb;
    }
}

void deleteArray();
void printResult();
 
int main()
{
    // Need to change this to CIN input
    string stringMultiplicand = "1101101";
    string stringMultiplier = "0000111";
    int multiplierLength = stringMultiplier.length();
    int multiplicandLength = stringMultiplicand.length();

    int* multiplicand = new int[multiplicandLength];
    populateBinaryArray(multiplicand, multiplicandLength, stringMultiplicand);

    int* multiplier = new int[multiplierLength];
    populateBinaryArray(multiplier, multiplierLength, stringMultiplier);

    int multiplicandComp[multiplicandLength]; 
    int sequenceCounter;
     

    // Store Two's Complement of Multiplicand
    for (int i = multiplicandLength - 1; i >= 0; i--) {
        multiplicandComp[i] = multiplicand[i]; 
    }

    complement(multiplicandComp, multiplicandLength);
     
    reverse(multiplicand, multiplicand + multiplicandLength);
    sequenceCounter = multiplierLength;
    reverse(multiplier, multiplier + multiplierLength);
    boothAlgorithm(multiplicand, multiplier, multiplicandComp, multiplierLength, multiplicandLength, sequenceCounter);
}
