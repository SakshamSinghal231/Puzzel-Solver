#include <bits/stdc++.h>
#include <windows.h>
#include <thread>
#include <conio.h>
#include <string>
#include <vector>


using namespace std;
using std::this_thread::sleep_for;

//for front screen
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 15;

//for magnet puzzle
#define R 10
#define C 10

void mainMenu();

void clearScreen(int characterLength) {
	for (int i = 0; i < characterLength; i++) {
		cout << "\b";
	}
}

void changeColour(int colour) {
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}


//Cryp start
vector<int> use(10);        //set 1, when one character is assigned previously

struct node{
   char letter;
   int value;
};

int isValidCryptarithmeticPuzzle(node* nodeList, const int count, string s1, string s2, string s3) {
   int val1 = 0, val2 = 0, val3 = 0, m = 1, j, i;

   for (i = s1.length() - 1; i >= 0; i--) {    //find number for first string
      char ch = s1[i];
      for (j = 0; j < count; j++)
         if (nodeList[j].letter == ch)       //when ch is present, break the loop
            break;
      val1 += m * nodeList[j].value;
      m *= 10;
   }

   m = 1;
   for (i = s2.length() - 1; i >= 0; i--) {    //find number for second string
      char ch = s2[i];
      for (j = 0; j < count; j++)
         if (nodeList[j].letter == ch)
            break;
      val2 += m * nodeList[j].value;
      m *= 10;
   }

   m = 1;
   for (i = s3.length() - 1; i >= 0; i--) {    //find number for third string
      char ch = s3[i];
      for (j = 0; j < count; j++)
         if (nodeList[j].letter == ch)
            break;
      val3 += m * nodeList[j].value;
      m *= 10;
   }

   if (val3 == (val1 + val2))    //check whether the sum is same as 3rd string or not
      return 1;
   return 0;
}

bool permutationCryptarithmeticPuzzle(int count, node* nodeList, int n, string s1, string s2, string s3) {
    use.clear();
    if (n == count - 1) {     //when values are assigned for all characters
    for (int i = 0; i < 10; i++) {
        if (use[i] == 0) {     // for those numbers, which are not used
            nodeList[n].value = i;    //assign value i
            if (isValidCryptarithmeticPuzzle(nodeList, count, s1, s2, s3) == 1) { //check validation
                printf("\n%c", 201);
                for(int i=0; i<83; i++){printf("%c", 205);}
                printf("%c\n", 187);
               printf("%c                                    SOLUTION                                       %c\n",186, 186);
               for (int j = 0; j < count; j++){    //print code, which are assigned
                  if(j==0){
                    printf("%c                                    %c%c%c%c%c%c%c%c%c                                      %c\n", 186,214,196,196,196,210,196,196,196,183,186);
                  }
                    printf("%c                                    %c %c %c ", 186, 186, nodeList[j].letter, 186);
                    if(nodeList[j].value/10>0)
                        printf("%d%c                                      %c\n", nodeList[j].value, 186, 186);
                    else
                        printf("%d %c                                      %c\n", nodeList[j].value, 186, 186);
                  if(j!=count-1)
                    printf("%c                                    %c%c%c%c%c%c%c%c%c                                      %c\n", 186,199,196,196,196,215,196,196,196,182,186);
                  else
                    printf("%c                                    %c%c%c%c%c%c%c%c%c                                      %c\n", 186,211,196,196,196,208,196,196,196,189,186);

               }
                printf("%c", 186);
                for(int i=0; i<83; i++){printf(" ");}
                printf("%c\n", 186);


                printf("%c", 200);
                for(int i=0; i<83; i++){printf("%c", 205);}
                printf("%c\n", 188);
               return true;
            }
         }
      }
      return false;


   }

   for (int i = 0; i < 10; i++) {
      if (use[i] == 0) {           // for those numbers, which are not used
         nodeList[n].value = i;    //assign value i and mark as not available for future use
         use[i] = 1;
         if (permutationCryptarithmeticPuzzle(count, nodeList, n + 1, s1, s2, s3))    //go for next characters
            return true;
         use[i] = 0; //when backtracks, make available again
      }
   }
   return false;
}

bool solveCryptarithmeticPuzzle(string s1, string s2,string s3) {
   int uniqueChar = 0; //Number of unique characters
   int len1 = s1.length();
   int len2 = s2.length();
   int len3 = s3.length();

   vector<int> freq(26); //There are 26 different characters

   for (int i = 0; i < len1; i++)
      ++freq[s1[i] - 'A'];
   for (int i = 0; i < len2; i++)
      ++freq[s2[i] - 'A'];
   for (int i = 0; i < len3; i++)
      ++freq[s3[i] - 'A'];

   for (int i = 0; i < 26; i++)
      if (freq[i] > 0)     //whose frequency is > 0, they are present
         uniqueChar++;

   if (uniqueChar > 10) { //as there are 10 digits in decimal system
      cout << "\n\nInvalid strings";
      return 0;
   }

   node nodeList[uniqueChar];
   for (int i = 0, j = 0; i < 26; i++) {     //assign all characters found in three strings
      if (freq[i] > 0) {
         nodeList[j].letter = char(i + 'A');
         j++;
      }
   }
   return permutationCryptarithmeticPuzzle(uniqueChar, nodeList, 0, s1, s2, s3);
}

string captalize(string s, int size){
    for(int i=0; i<size; i++){
        if(s[i]>='a' && s[i]<='z'){
            s[i]-=32;
        }
    }

    return s;
}

void cryptarithmeticPuzzle() {

    system("CLS");

    string s1, s2, s3;

    //info
    for(int i=0; i<85; i++){printf("%c",176);}
    printf("\n%c                                                                                   %c",176,176);
    printf("\n%c                             CRYPTARITHMETIC PUZZLE                                %c",176,176);
    printf("\n%c 1. We are given three strings s1, s2 and s3.                                      %c",176,176);
    printf("\n%c 2. First two are supposed to add and form third. s1 + s2 = s3                     %c",176,176);
    printf("\n%c 3. You have to map each individual character to a digit, so that the              %c",176,176);
    printf("\n%c    above equation holds true.                                                     %c",176,176);
    printf("\n%c                                                                                   %c\n",176,176);
    for(int i=0; i<85; i++){printf("%c",176);}
    cout<<endl;
    //

    for(int i=0; i<85; i++){printf("-");}
    cout<<"\nEnter String 1: ";
    cin>>s1;

    cout<<endl;
    for(int i=0; i<85; i++){printf("-");}
    cout<<"\nEnter String 2: ";
    cin>>s2;

    cout<<endl;
    for(int i=0; i<85; i++){printf("-");}
    cout<<"\nEnter String 3: ";
    cin>>s3;
    for(int i=0; i<85; i++){printf("-");}
    fflush(stdin);

    //s1 = "base"; s2="ball"; s3="games";
    if (solveCryptarithmeticPuzzle(captalize(s1, s1.length()), captalize(s2, s2.length()), captalize(s3, s3.length())) == false)
        cout << "No solution!";

    changeColour(GREEN); cout <<endl<<endl<< "                             PRESS ANY KEY TO CONTINUE";
	changeColour(WHITE);

    cout << "\n\n\n";
    use.clear();
    fflush(stdin);
	getchar();
	mainMenu();

}
//cryp end

//tugofwar start
void TugofWarRecur(int* array, int n, bool* currentElements, int selectedElementsCount,bool* solution, int* minDiff, int sum, int currentSum, int currentPosition)
{

    if (currentPosition == n)
    {
        return;
    }
    if ((n/2 - selectedElementsCount) > (n - currentPosition))
    {
        return;
    }

    TugofWarRecur(array, n, currentElements, selectedElementsCount,solution, minDiff, sum, currentSum, currentPosition+1);

    selectedElementsCount++;
    currentSum = currentSum + array[currentPosition];
    currentElements[currentPosition] = true;
    if (selectedElementsCount == n/2)
    {
        if (abs(sum/2 - currentSum) < *minDiff)
        {
            *minDiff = abs(sum/2 - currentSum);
            for (int i = 0; i<n; i++)
            {
                solution[i] = currentElements[i];
            }
        }
    }
    else
    {
        TugofWarRecur(array, n, currentElements, selectedElementsCount, solution, minDiff, sum, currentSum, currentPosition+1);
    }
    currentElements[currentPosition] = false;
}

int totalDigits(int x){
    int temp;
    if(x<0){
        temp=2;
        x*=-1;
    }else{
        temp=1;
    }

    while(x/10!=0){
        x/=10;
        temp++;
    }

    return temp;
}


void TugOfWar()
{
    system("CLS");

    //info
    for(int i=0; i<85; i++){printf("%c",176);}
    printf("\n%c                                                                                   %c",176,176);
    printf("\n%c                                  TUG OF WAR                                       %c",176,176);
    printf("\n%c 1. We are given an array of n integers.                                           %c",176,176);
    printf("\n%c 2. We have to divide these n integers into 2 subsets such that the difference     %c",176,176);
    printf("\n%c    of sum of two subsets  is as minimum as possible.                              %c",176,176);
    printf("\n%c 3. If n is even, both set will contain exactly n/2 elements. If  is odd, one      %c",176,176);
    printf("\n%c    set will contain (n-1)/2 and other set will contain (n+1)/2 elements.          %c",176,176);
    printf("\n%c                                                                                   %c\n",176,176);
    for(int i=0; i<85; i++){printf("%c",176);}
    cout<<endl;
    //

    for(int i=0;i<85;i++){cout<<"-";}
    cout<<endl;

    int n;
    cout<<"Enter Total Numbers in Array: ";
    cin>>n;
    int array[n];
    cout<<"Enter Elements in Array: ";
    for(int i=0;i<n;i++)
    {
        cin>>array[i];
    }

    cout<<endl;
    for(int i=0;i<85;i++){cout<<"-";}
    cout<<endl;

    bool *currentElements = new bool[n];
    bool *solution = new bool[n];
    int minDiff = INT_MAX;
    int sum = 0;
    for (int i=0; i<n; i++)
    {
        sum =sum + array[i];
        currentElements[i] =  solution[i] = false;
    }
    TugofWarRecur(array, n, currentElements, 0, solution, &minDiff, sum, 0, 0);

    printf("\n%c", 201);
    for(int i=0; i<83; i++){printf("%c", 205);}
    printf("%c\n", 187);
    printf("%c                                    SOLUTION                                       %c\n",186, 186);

    int temp=0;
    printf("%c ", 186);
    for (int i=0; i<n; i++)
    {
        if(solution[i] == true)
        {
            cout <<"| "<< array[i] << " ";
            temp=temp+totalDigits(array[i])+3;
        }
    }
    cout<<'|';
    for(int i=0; i<81-temp; i++){cout<<" ";}
    printf("%c\n", 186);

    temp=0;
    printf("%c ", 186);
    for (int i=0; i<n; i++)
    {
        if(solution[i] == false)
        {
            cout <<"| "<< array[i] << " ";
            temp=temp+totalDigits(array[i])+3;
        }
    }

    cout<<'|';
    for(int i=0; i<81-temp; i++){cout<<" ";}
    printf("%c\n", 186);

    printf("%c", 186);
    for(int i=0; i<83; i++){printf(" ");}
    printf("%c\n", 186);

    printf("%c", 200);
    for(int i=0; i<83; i++){printf("%c", 205);}
    printf("%c\n", 188);

    changeColour(GREEN); cout <<endl<<endl<< "                             PRESS ANY KEY TO CONTINUE";
	changeColour(WHITE);

    cout << "\n\n\n";
    fflush(stdin);
	getchar();
	system("CLS");
	mainMenu();
}
//tugofwar end

//magnet puzzle start
void printSolutionMagnetPuzzle(int N, int M, char board[R][C], int top[], int left[], int bottom[], int right[]){

    printf("\n%c", 201);
    for(int i=0; i<84; i++){printf("%c", 205);}
    printf("%c\n", 187);

    printf("%c                                    SOLUTION                                        %c\n",186, 186);

    //print top
    printf("%c + ",186);
    for(int i=0; i<N; i++){
        printf(" ");
        if(top[i]<0){printf("\b");}
        printf("%d  ",top[i]);
    }
    for(int j=0; j<81-4*N; j++){cout<<" ";}
    printf("%c", 186);
    //

    printf("\n%c  %c",186, 218);
    for(int i=0; i<N; i++){
        printf("%c%c%c%c",196,196,196,194);
    }
    printf("\b%c",191);
    for(int j=0; j<81-4*N; j++){cout<<" ";}
    printf("%c", 186);

    int temp=0;

    for (int i = 0; i < M; i++)
    {
        printf("\n%c ",186);
        if(left[i]<0){printf("\b");}
        printf("%d%c ", left[i], 179);
        for (int j = 0; j < N; j++){
            printf("%c %c ",board[i][j],179);
        }
        if(right[i]<0){printf("\b");}
        printf("%d",right[i]);

        for(int j=0; j<79-4*N; j++){cout<<" ";}
        printf("%c\n", 186);



        printf("%c  %c",186, 195);
        for (int j = 0; j < N; j++) {
            printf("%c%c%c%c",196,196,196,197);
        }
        printf("\b%c",180);


        for(int j=0; j<81-4*N; j++){cout<<" ";}
        printf("%c", 186);

    }


    for(int i=0; i<87; i++){cout<<"\b";}
    printf("%c  %c",186, 192);
    for (int j = 0; j < N; j++) {
        printf("%c%c%c%c",196,196,196,193);
    }
    printf("\b%c",217);

    for(int j=0; j<81-4*N; j++){cout<<" ";}
    printf("%c\n", 186);

    //print bottom
    printf("%c   ",186);
    for(int i=0; i<N; i++){
        printf(" ");
        if(bottom[i]<0){printf("\b");}
        printf("%d  ",bottom[i]);
    }
    printf(" -");
    for(int j=0; j<79-4*N; j++){cout<<" ";}
    printf("%c", 186);

    printf("\n%c", 200);
    for(int i=0; i<84; i++){printf("%c", 205);}
    printf("%c\n", 188);

    changeColour(GREEN); cout <<endl<<endl<< "                             PRESS ANY KEY TO CONTINUE";
	changeColour(WHITE);

    cout << "\n\n\n";
    fflush(stdin);
	getchar();
	system("CLS");
	mainMenu();

}

// Utility function to count the total number of characters `ch` in current column `j`
int countInColumnsMagnetPuzzle(int N, int M, char board[C][C], char ch, int j){
    int count = 0;
    for (int i = 0; i < M; i++)
    {
        if (board[i][j] == ch) {
            count++;
        }
    }

    return count;
}

// Utility function to count the total number of characters `ch` in current row `i`
int countInRowMagnetPuzzle(int N, int M, char board[C][C], char ch, int i){
    int count = 0;
    for (int j = 0; j < N; j++)
    {
        if (board[i][j] == ch) {
            count++;
        }
    }

    return count;
}

// Function to check if it is safe to put `ch` at `board[row][col]`
bool isSafeMagnetPuzzle(int N, int M, char board[C][C], int row, int col, char ch, int top[], int left[], int bottom[], int right[]){
    // check for adjacent cells
    if ((row - 1 >= 0 && board[row - 1][col] == ch) ||
            (col + 1 < N && board[row][col + 1] == ch) ||
            (row + 1 < M && board[row + 1][col] == ch) ||
            (col - 1 >= 0 && board[row][col - 1] == ch)) {
        return false;
    }

    // count character `ch` in the current row
    int rowCount = countInRowMagnetPuzzle(N, M, board, ch, row);

    // count character `ch` in the current column
    int colCount = countInColumnsMagnetPuzzle(N, M, board, ch, col);

    // if the given character is `+`, check `top[]` and `left[]`
    if (ch == '+')
    {
        // check top
        if (top[col] != -1 && colCount >= top[col]) {
            return false;
        }

        // check left
        if (left[row] != -1 && rowCount >= left[row]) {
            return false;
        }
    }

    // if the given character is `-`, check `bottom[]` and `right[]`
    if (ch == '-')
    {
        // check bottom
        if (bottom[col] != -1 && colCount >= bottom[col]) {
            return false;
        }

        // check left
        if (right[row] != -1 && rowCount >= right[row]) {
            return false;
        }
    }

    return true;
}

// Function to validate the configuration of an output board
bool validateConfigurationMagnetPuzzle(int N, int M, char board[C][C], int top[], int left[], int bottom[], int right[]){
    // check top
    for (int i = 0; i < N; i++)
    {
        if (top[i] != -1 && countInColumnsMagnetPuzzle(N, M, board, '+', i) != top[i]) {
            return false;
        }
    }

    // check left
    for (int j = 0; j < M; j++)
    {
        if (left[j] != -1 && countInRowMagnetPuzzle(N, M, board, '+', j) != left[j]) {
            return false;
        }
    }

    // check bottom
    for (int i = 0; i < N; i++)
    {
        if (bottom[i] != -1 && countInColumnsMagnetPuzzle(N, M, board, '-', i) != bottom[i]) {
            return false;
        }
    }

    // check right
    for (int j = 0; j < M; j++)
    {
        if (right[j] != -1 && countInRowMagnetPuzzle(N, M, board, '-', j) != right[j]) {
            return false;
        }
    }

    return true;
}

// The main function to solve the Bipolar Magnets puzzle
bool solveMagnetPuzzle(int N, int M, char board[C][C], int row, int col, int top[], int left[], int bottom[], int right[], char rules[R][C]){
    // if the last cell is reached
    if (row >= M - 1 && col >= N - 1)
    {
        if (validateConfigurationMagnetPuzzle(N, M, board, top, left, bottom, right)) {
            return true;
        }

        return false;
    }

    // if the last column of the current row is already processed,
    // go to the next row, the first column
    if (col >= N)
    {
        col = 0;
        row = row + 1;
    }

    // if the current cell contains `R` or `B` (end of horizontal
    // or vertical slot), recur for the next cell
    if (rules[row][col] == 'R' || rules[row][col] == 'B')
    {
        if (solveMagnetPuzzle(N, M, board, row, col + 1, top,
                                left, bottom, right, rules)) {
            return true;
        }
    }

    // if horizontal slot contains `L` and `R`
    if (rules[row][col] == 'L' && rules[row][col + 1] == 'R')
    {
        // put (`+`, `-`) pair and recur
        if (isSafeMagnetPuzzle(N, M, board, row, col, '+', top, left, bottom, right) &&
            isSafeMagnetPuzzle(N, M, board, row, col + 1, '-', top, left, bottom, right))
        {
            board[row][col] = '+';
            board[row][col + 1] = '-';

            if (solveMagnetPuzzle(N, M, board, row, col + 2,
                            top, left, bottom, right, rules)) {
                return true;
            }

            // if it doesn't lead to a solution, backtrack
            board[row][col] = 'X';
            board[row][col + 1] = 'X';
        }

        // put (`-`, `+`) pair and recur
        if (isSafeMagnetPuzzle(N, M, board, row, col, '-', top, left, bottom, right) &&
            isSafeMagnetPuzzle(N, M, board, row, col + 1, '+', top, left, bottom, right))
        {
            board[row][col] = '-';
            board[row][col + 1] = '+';

            if (solveMagnetPuzzle(N, M, board, row, col + 2,
                            top, left, bottom, right, rules)) {
                return true;
            }

            // if it doesn't lead to a solution, backtrack
            board[row][col] = 'X';
            board[row][col + 1] = 'X';
        }
    }

    // if vertical slot contains `T` and `B`
    if (rules[row][col] == 'T' && rules[row + 1][col] == 'B')
    {
        // put (`+`, `-`) pair and recur
        if (isSafeMagnetPuzzle(N, M, board, row, col, '+', top, left, bottom, right) &&
            isSafeMagnetPuzzle(N, M, board, row + 1, col, '-', top, left, bottom, right))
        {
            board[row][col] = '+';
            board[row + 1][col] = '-';

            if (solveMagnetPuzzle(N, M, board, row, col + 1,
                            top, left, bottom, right, rules)) {
                return true;
            }

            // if it doesn't lead to a solution, backtrack
            board[row][col] = 'X';
            board[row + 1][col] = 'X';
        }

        // put (`-`, `+`) pair and recur
        if (isSafeMagnetPuzzle(N, M, board, row, col, '-', top, left, bottom, right) &&
            isSafeMagnetPuzzle(N, M, board, row + 1, col, '+', top, left, bottom, right))
        {
            board[row][col] = '-';
            board[row + 1][col] = '+';

            if (solveMagnetPuzzle(N, M, board, row, col + 1,
                            top, left, bottom, right, rules)) {
                return true;
            }

            // if it doesn't lead to a solution, backtrack
            board[row][col] = 'X';
            board[row + 1][col] = 'X';
        }
    }

    // ignore the current cell and recur
    if (solveMagnetPuzzle(N, M, board, row, col + 1,
                        top, left, bottom, right, rules)) {
        return true;
    }

    // if no solution is possible, return false
    return false;
}

void solveMagnetPuzzle(int N, int M, int top[], int left[], int bottom[], int right[], char rules[R][C]){
    // to store the result
    char board[R][C];

    // initialize all cells by `X`
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) {
            board[i][j] = 'X';
        }
    }

    // start from `(0, 0)` cell
    if (!solveMagnetPuzzle(N, M, board, 0, 0, top, left, bottom, right, rules))
    {
        cout << "\nSolution does not exist";

        changeColour(GREEN); cout <<endl<<endl<< "                             PRESS ANY KEY TO CONTINUE";
        changeColour(WHITE);

        cout << "\n\n\n";
        fflush(stdin);
        getchar();
        system("CLS");
        mainMenu();
        return;
    }

    // print result if the given configuration is solvable
    printSolutionMagnetPuzzle(N, M, board, top, left, bottom, right);
}

string suffix(int n){
    if(n==1){
        return "st";
    }else if(n==2){
        return "nd";
    }else if(n==3)
        return "rd";
    else{
        return "th";
    }
}

void magnetPuzzle()
{

    system("CLS");
    // indicates the count of `+` or `-` along the top (+), bottom (-),
    // left (+), and right (-) edges, respectively.
    // Value of -1 indicate any number of `+` or `-` signs
    int M, N;

    //info
    for(int i=0; i<85; i++){printf("%c",176);}
    printf("\n%c                                                                                   %c",176,176);
    printf("\n%c                                 MAGNET PUZZLE                                     %c",176,176);
    printf("\n%c 1. We are given n number of domino shaped bipolar magnets.                        %c",176,176);
    printf("\n%c 2. We have to place these magnets in M*N following the conditions.                %c",176,176);
    printf("\n%c 3. We have to place these magnets in M*N following the conditions.                %c",176,176);
    printf("\n%c    a. Each box of 1*2 or 2*1 can contain a magnet or can be empty.                %c",176,176);
    printf("\n%c    b. Empty box can be represented by X's and magnets are represented by          %c",176,176);
    printf("\n%c       + and - sign.                                                               %c",176,176);
    printf("\n%c    c. Digits along left and top side of the board represents the number           %c",176,176);
    printf("\n%c       of + in corresponding rows and columns.                                     %c",176,176);
    printf("\n%c    d. Digits along right and bottom side of the board represents the number       %c",176,176);
    printf("\n%c       of + in corresponding rows and columns.                                     %c",176,176);
    printf("\n%c    e. -1 denotes that the corresponding row and column can have any number        %c",176,176);
    printf("\n%c       of +  and - signs.                                                          %c",176,176);
    printf("\n%c    f. f. No two adjacent cell can have the same sign.                             %c",176,176);
    printf("\n%c                                                                                   %c\n",176,176);
    for(int i=0; i<85; i++){printf("%c",176);}
    cout<<endl;
    //

    for(int i=0; i<85; i++){cout<<"-";}
    cout<<"\nNo. of Rows:\t";
    cin>>M;

    cout<<"No. of Columns:\t";
    cin>>N;

    for(int i=0; i<85; i++){cout<<"-";}

    int top[N], bottom[N], left[M], right[M];

    cout<<endl;
    for(int i=0; i<85; i++){cout<<"-";}

    cout<<"\nInput Rules for Top:\t";
    for(int i=0; i<N; i++){cin>>top[i];}

    cout<<"Input Rules for Bottom:\t";
    for(int i=0; i<N; i++){cin>>bottom[i];}

    cout<<"Input Rules for Left:\t";
    for(int i=0; i<M; i++){cin>>left[i];}

    cout<<"Input Rules for Right:\t";
    for(int i=0; i<M; i++){cin>>right[i];}
    cout<<endl;
    for(int i=0; i<85; i++){cout<<"-";}

    /*int top[N] = { 1, -1, -1, 2, 1, -1 };
    int bottom[N] = { 2, -1, -1, 2, -1, 3 };
    int left[M] = { 2, 3, -1, -1, -1 };
    int right[M] = { -1, -1, -1, 1, -1 };

    // rules matrix
    char rules[M][N] =
    {
        { 'L', 'R', 'L', 'R', 'T', 'T' },
        { 'L', 'R', 'L', 'R', 'B', 'B' },
        { 'T', 'T', 'T', 'T', 'L', 'R' },
        { 'B', 'B', 'B', 'B', 'T', 'T' },
        { 'L', 'R', 'L', 'R', 'B', 'B' }
    };*/

    char rules[R][C];
    int k=1;

    cout<<endl;
    for(int i=0; i<85; i++){cout<<"-";}

    cout<<endl;
    for(int i=0; i<M; i++, k++){
            cout<<"Input "<<N<<" Elements for "<<k<<suffix(k)<<" row: ";
        for(int j=0; j<N; j++){
            cin>>rules[i][j];
        }
    }

    for(int i=0; i<85; i++){cout<<"-";}

    solveMagnetPuzzle(N, M, top, left, bottom, right, rules);
}
//magnet puzzle end

void showLoadingScreen(){
    int i;
    int colour[] = {RED, GREEN, BLUE, WHITE};

    int k=15;
    int m=k/2, n=k-k/2;

    while(m){
        system("CLS");
        changeColour(m);
        for(int i=0; i<k; i++){
            if(i==m || i==n){
                cout<<"***********************************************************************************";

            }
            cout<<endl;
        }
        m--;
        n++;
        sleep_for(250ms);

    }

    sleep_for(250ms);

    system("CLS");
}

void mainMenu();

void showPuzzleSolver() {

    system("CLS");

    cout<<endl<<endl<<endl;
    changeColour(RED); cout << "    ____  __  _____________   __    ______"; changeColour(BLUE); cout << "   _____ ____  __ _    ____________ \n";
    changeColour(RED); cout << "   / __ \\/ / / /__  //__  /  / /   / ____/"; changeColour(BLUE); cout << "  / ___// __ \\/ /| |  / / ____/ __ \\\n";
    changeColour(RED); cout << "  / /_/ / / / /  / /   / /  / /   / __/   "; changeColour(BLUE); cout << "  \\__ \\/ / / / / | | / / __/ / /_/ /\n";
    changeColour(RED); cout << " / ____/ /_/ /  / /__// /__/ /___/ /___   "; changeColour(BLUE); cout << " ___/ / /_/ / /__| |/ / /___/ _, _/ \n";
    changeColour(RED); cout << "/_/    \\____/  /____//____/_____/_____/   "; changeColour(BLUE); cout << "/____/\\____/_____|___/_____/_/ |_|  \n";

	changeColour(GREEN); cout <<endl<<endl<< "                        PRESS ENTER OR D TO CONTINUE";
	changeColour(WHITE);

    cout << "\n\n\n";
	char ch;
    string pass="";
    do{
        ch = _getch();
        pass.push_back(ch);
        if(ch == 13 || ch=='d' || ch=='D'){
            break;
        }
    }while(1);

	system("CLS");
	mainMenu();
}

void mainMenu()
{
    int point=0;
    char temp=' ';
    string pass="";

    while(1){

        system("CLS");

        printf("%c", 201);
        for(int i=0; i<83; i++){printf("%c", 205);}
        printf("%c\n", 187);

        printf("%c", 186);
        for(int i=0; i<83; i++){printf(" ");}
        printf("%c\n", 186);

        if(temp=='s' || temp=='S'){point++;}
        if(temp=='w' || temp=='W'){point-1<0?point=3:point--;}
        printf("%c                          _____     _        _____                                 %c\n", 186, 186);
        printf("%c                         |     |___|_|___   |     |___ ___ _ _                     %c\n", 186, 186);
        printf("%c                         | | | | .'| |   |  | | | | -_|   | | |                    %c\n", 186, 186);
        printf("%c                         |_|_|_|__,|_|_|_|  |_|_|_|___|_|_|___|                    %c\n", 186, 186);
        printf("%c                                                                                   %c\n", 186, 186);
        printf("%c                                                                                   %c\n", 186, 186);

        printf("%c                         ", 186);changeColour(WHITE);
        if(point%4==0){changeColour(BLUE);printf("\b%c", 175);}
        printf(" 1. Cryptarithmetic Puzzle                                ");
        changeColour(WHITE);
        printf("%c\n", 186);

        printf("%c                         ", 186);changeColour(WHITE);
        if(point%4==1){changeColour(BLUE);printf("\b%c", 175);}
        printf(" 2. Tug of War                                            ");
        changeColour(WHITE);
        printf("%c\n", 186);

        printf("%c                         ", 186);changeColour(WHITE);
        if(point%4==2){changeColour(BLUE);printf("\b%c", 175);}
        printf(" 3. Magnet Puzzle                                         ");
        changeColour(WHITE);
        printf("%c\n", 186);

        printf("%c                         ", 186);changeColour(WHITE);
        if(point%4==3){changeColour(BLUE);printf("\b%c", 175);}
        printf(" 4. Exit                                                  ");
        changeColour(WHITE);
        printf("%c\n", 186);

        printf("%c                                                                       %c%c%c%c%c       %c\n",186,218,196,196,196,191,186);
        printf("%c                                                                       %c W %c       %c\n",186,179,179,186);
        printf("%c                                                                   %c%c%c%c%c%c%c%c%c%c%c%c%c   %c\n",186,218,196,196,196,197,196,196,196,197,196,196,196,191,186);
        printf("%c                                                                   %c A %c S %c D %c   %c\n",186,179,179,179,179,186);
        printf("%c                                                                   %c%c%c%c%c%c%c%c%c%c%c%c%c   %c\n",186,192,196,196,196,193,196,196,196,193,196,196,196,217,186);

/*
        printf("%c", 186);
        for(int i=0; i<83; i++){printf(" ");}
        printf("%c\n", 186);

        printf("%c", 186);
        for(int i=0; i<83; i++){printf(" ");}
        printf("%c\n", 186);

        printf("%c", 186);
        for(int i=0; i<83; i++){printf(" ");}
        printf("%c\n", 186);
*/

        printf("%c", 200);
        for(int i=0; i<83; i++){printf("%c", 205);}
        printf("%c\n", 188);

        char ch;
        pass="";

        do{
            ch = _getch();
            pass.push_back(ch);
            if(ch == 'd' || ch=='D' || ch=='w' || ch=='W' || ch=='s' || ch=='S' || ch=='a' || ch=='A' || ch==13 || ch=='1' || ch=='2' || ch=='3' || ch=='4'){
                break;
            }
        }while(1);

        if(point>3){point-=4;};

        temp=ch;
        if(temp=='d' || temp=='D' || temp=='a' || temp=='A' || temp==13 || temp=='1' || temp=='2' || temp=='3' || temp=='4'){break;}
        changeColour(WHITE);
    }

    if(temp=='a' || temp=='A'){showPuzzleSolver();}
    if(temp=='1'){cryptarithmeticPuzzle();}
    else if(temp=='2'){TugOfWar();}
    else if(temp=='3'){magnetPuzzle();}
    else if(temp=='4'){system("CLS"); return;}
    else if(point==0){cryptarithmeticPuzzle();}
    else if(point==1){TugOfWar();}
    else if (point==2){magnetPuzzle();}
    else if (point==3){system("CLS"); return;}
}

int main() {

    //showLoadingScreen();
	showPuzzleSolver();

	return 0;
}


/*
BASE
BALL
GAMES
*/

/*
10
3 4 5 -3 100 1 89 54 23 20
*/

/*
5
6
1 -1 -1 2 1 -1
2 -1 -1 2 -1 3
2 3 -1 -1 -1
-1 -1 -1 1 -1
L R L R T T
L R L R B B
T T T T L R
B B B B T T
L R L R B B


4
3
2 -1 -1
-1 -1 2
-1 -1 2 -1
0 -1 -1 -1
T T T
B B B
T L R
B L R
*/

