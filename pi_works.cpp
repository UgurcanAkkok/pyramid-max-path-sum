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

#define MAX_HEIGHT 200

using namespace std;

struct Node {
    int value;
    bool isPrime;
    Node leftChild;
    Node rightChild;
};

bool check_usage(int c){
    if (c != 2){
        cout << "Usage is \" maxpath FILE_NAME \"" << endl;
        return false;
    }
    return true;
}

int find_height(int len);

int main(int argc, char* argv[]){
    if (check_usage(argc) == false) return 1;
    int pyr_len = 0;
    Node * pyramid;

    ifstream pyramidFile(argv[1]);
    if (pyramidFile.is_open()){
        int num;
        while(pyramidFile >> num){
            pyr_len++;
        }
    }
    int height = find_height(pyr_len);
    pyramid = new Node [height];
}

int find_height(int len){
    return (-1 + sqrt(1 + 8 * len)) / 2;
}
