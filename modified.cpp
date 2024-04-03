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
    int x[n] = {0};
    x[n - 1] = 1;
     
    for (increment = 0; increment < n; increment++) {
        a[increment] = (a[increment] + 1) % 2;
    }

    int i, c = 0;
     
    for (i = n - 1; i >= 0 ; i--) {
         
        // updating accumulatorcumulator with A = A + multiplicand
        a[i] = a[i] + x[i] + c;
         
        if (a[i] > 1) {
            a[i] = a[i] % 2;
            c = 1;
        }
        else
            c = 0;
    }

}

void logicalShiftLeft(int multiplicand[], int multiplicandLength) {

    int temp;
    int i;
     
    for (i = multiplicandLength - 1; i >= 0; i--) {
        multiplicand[i] = multiplicand[i - 1];
    }
    multiplicand[0] = 0;
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
    cout << "E\tq[n+1]\t\tmultiplicand\t\tAC\tmultiplier\t\tsequenceCounter\n";
    cout << "\t\t\t\tinitial\t\t";
     
    display(accumulator, multiplier, multiplierLength);
    cout << "\t\t" << sequenceCounter << "\n";
     
    // Everytime we ASHR decrease the Sequence Counter
    while (sequenceCounter > 0) {
        cout << multiplier[0] << "\t" << E;

        int first = multiplier[1];
        int second = multiplier[0];
        int third = E;
         
        if ((first == 1 && second == 0 && third == 1) || (first == 1 && second == 1 && third == 0)) {
                 
            cout << "\t\tA = A - multiplicand\t";
            add(accumulator, multiplicandComp, multiplierLength);
             
            for (int i = multiplierLength - 1; i >= 0; i--)
                cout << accumulator[i];

        } else if ((first == 0 && second == 0 && third == 1) || (first == 0 && second == 1 && third == 0)) {
                // add multiplicand to accumulatorcumulator
                add(accumulator, multiplicand, multiplierLength);
                cout << "\t\tA = A + multiplicand\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];

        } else if ((first == 0 && second == 1 && third == 1)) {
                logicalShiftLeft(multiplicand, multiplicandLength);
                add(accumulator, multiplicand, multiplierLength);
                cout << "\t\tA = A + multiplicand\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];

        } else if ((first == 1 && second == 0 && third == 0)) {
                logicalShiftLeft(multiplicandComp, multiplicandLength);
                add(accumulator, multiplicandComp, multiplierLength);
                cout << "\t\tA = A + multiplicand\t";
                 
                for (int i = multiplierLength - 1; i >= 0; i--)
                    cout << accumulator[i];
        }

        cout << "\n\t";
        arithmeticRightShft(accumulator, multiplier, E, multiplierLength);
        arithmeticRightShft(accumulator, multiplier, E, multiplierLength);

        
        display(accumulator, multiplier, multiplierLength);
        
        cout << "\t";
         
        // decrement counter
        sequenceCounter = sequenceCounter - 2;
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
void printResults();
 
int main()
{
    // Need to change this to CIN input
    string stringMultiplicand = "11101";
    string stringMultiplier = "10111";
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

    reverse(multiplicand, multiplicand + multiplicandLength);
    complement(multiplicandComp, multiplicandLength);
    sequenceCounter = multiplierLength;
    reverse(multiplier, multiplier + multiplierLength);
    reverse(multiplicandComp, multiplicandComp + multiplicandLength);
    boothAlgorithm(multiplicand, multiplier, multiplicandComp, multiplierLength, multiplicandLength, sequenceCounter);
}
