/*
 * You will have an orthogonal triangle input from a file and you need to find the maximum sum of the numbers according to given rules below;

1. You will start from the top and move downwards to an adjacent number as in below.
2. You are only allowed to walk downwards and diagonally.
3. You can only walk over NON PRIME NUMBERS.
4. You have to reach at the end of the pyramid as much as possible.
5. You have to treat your input as pyramid.

According to above rules the maximum sum of the numbers from top to bottom in below example is 24.

      *1
     *8 4
    2 *6 9
   8 5 *9 3

As you can see this has several paths that fits the rule of NOT PRIME NUMBERS; 1>8>6>9, 1>4>6>9, 1>4>9>9
1 + 8 + 6 + 9 = 24.  As you see 1, 8, 6, 9 are all NOT PRIME NUMBERS and walking over these yields the maximum sum.

Paste the link to your code.
1 3 6 10 15 21 
1 2 3 4  5  6
n.(n+1)/2 = y

n.n+1 = 2y
n2 + n - 2y = 0
-b + kökdelta 
 
215
193 124
117 237 442
218 935 347 235
320 804 522 417 345
229 601 723 835 133 124
248 202 277 433 207 263 257
359 464 504 528 516 716 871 182
461 441 426 656 863 560 380 171 923
381 348 573 533 447 632 387 176 975 449
223 711 445 645 245 543 931 532 937 541 444
330 131 333 928 377 733 017 778 839 168 197 197
131 171 522 137 217 224 291 413 528 520 227 229 928
223 626 034 683 839 053 627 310 713 999 629 817 410 121
924 622 911 233 325 139 721 218 253 223 107 233 230 124 233
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool check_usage (int); // There should be 1 additional argument (PROGRAM FILE)
int find_height(int); //Given number of nodes, finds height of pyramid
bool is_prime(int); // We cant use prime nodes
int * max(int *,int *);
void printPyramid(int * p, int h);


int main(int argc, char* argv[]){
    int pyr_len = 0;
    ifstream pyramidFile(argv[1]);
    int h;
    int garbage; //while counting num of nodes, i use dummy var

    if (check_usage(argc) == false) return 1;
    // Check we can open the file
    if (!pyramidFile.is_open()){
        cout << "Could not open file" << endl;
        return 1;
    }
    while (pyramidFile >> garbage){
        pyr_len++;
    }
    h = find_height(pyr_len);

    // Construct given pyramid as 2dim matrix
    int ** pyramid = new int * [h];
    for (int i = 0; i < h; i++){
        pyramid[i] = new int [i]; 
    }
    // Put the cursor at the beginning
    pyramidFile.clear();
    pyramidFile.seekg(0, ios::beg);
    int curr_h = 1;
    // Set length of each row as increasing at each step, beginning with 1
    while (curr_h <= h){
        for (int i = 0; i < curr_h; i++){
            pyramidFile >> pyramid[curr_h - 1][i];
        }
        curr_h++;
    }
    // Starting with upper row of last row, sum each node with left and 
    // right childs, find the max between them, set that node as that sum,
    // Do not use prime nodes
    for (int i=h-2; i>=0; i--){
        for (int j = 0; j <= i; j++){
            int * curr = &pyramid[i][j];
            int * left = &pyramid[i + 1][j];
            int * right = &pyramid[i + 1][j + 1];
            if (!is_prime(*curr)){
                int * max_node = max(left,right);
                if (!is_prime(*max_node)){
                    *curr += *max_node;
                }
                else {
                    if (!is_prime(*left)){
                        *curr += *left;
                    }
                    else if (!is_prime(*right)){
                        *curr += *right;
                    }
                }
            }
        }
    }
    // Print the pyramid
    // Print the top node
    cout << *pyramid[0] << endl;
    // Clean up
    delete [] pyramid;
    pyramidFile.close();
}

bool is_prime(int num){
    for (int i = 1; i < sqrt(num); i++){
        if (num % i == 0) return false;
    }
    return true;
}

int find_height(int len){
    return (-1 + sqrt(1 + 8 * len)) / 2;
}

bool check_usage(int c){
    if (c != 2){
        cout << "Usage is \" maxpath FILE_NAME \"" << endl;
        return false;
    }
    return true;
}
int * max(int * a,int * b){
    return (*a >= *b)? a : b;
}
