#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool check_usage (int); // There should file name in command line arguments
int find_height(int); //Given number of nodes, finds height of pyramid
bool not_prime(int); // We cant use prime nodes
void printPyramid(int * p, int h);
//Used structs as node because we should save the "primeness" info
//before changing those nodes' values
struct Node {
    bool prime;
    int val;
};

class Pyramid {
    private:
        ifstream file;
        unsigned short h; //height
        unsigned int nodesNum; //number of nodes
        // nodes represents all pyramid, it is implemented with 
        // dynamic arrays of dynamic arrays because length depends on 
        // given pyramid
        Node ** nodes; 
    public:
        Pyramid(const char *);
        ~Pyramid(); //Closes file and frees nodes
        void print();
        int maxSum();
};


int main(int argc, char* argv[]){
    /*
     * I used a down-to-top method, the program takes the
     * pyramid as written in a file, converts it to 2dimensional
     * array, with each element is called node. Nodes are structures
     * of bool and int. We keep one bool variable because we check
     * if that node is prime, if it is, we will ignore it.
     *
     * The algorithm mostly lies under maxSum() function.
     * Start with one upper row of ground and leftmost node. Find which
     * node gonna be added to that node between left and right "child".
     * We add the node. So the current node is changed to find the result gradually
     * The procces is applied to each node of that row, then one upper row and so on.
     *
     * The added children are always changed beforehand and are chosen with value, so
     * it is progressive and the outcome will be the maximum summation.
     * 
     */

    // first and only argument should be file name
    if (check_usage(argc) == false) return 1;
    Pyramid pyr(argv[1]);
    cout << "First situation of pyramid is " << endl;
    pyr.print();
    cout << "=======================================" << endl;
    
    cout << "The maximum path sum is "<< pyr.maxSum() << endl;

    cout << "=======================================" << endl;
    cout << "Final situation of pyramid is" << endl;
    pyr.print();
}

bool not_prime(int num){
    switch(num){
        case 1: return true;
        case 2: return false;
        default:
                for (int i = 2; i <= (int)sqrt(num); i++){
                    if (num % i == 0){
                        return true;
                    }
                }
                return false;
    }
}

int find_height(int len){
    /* Uses root of the equation (with delta formula) to find height */
    return (-1 + sqrt(1 + 8 * len)) / 2;
}

bool check_usage(int c){
    /* First argument is the program's name which is automatically passed
     * Second must be file name
     */
    if (c != 2){
        cout << "Usage is \" maxpath FILE_NAME \"" << endl;
        return false;
    }
    return true;
}

Pyramid::Pyramid(const char * fName){
    /* Read the file */
    file = ifstream(fName);
    /*Throw an error if cant open it */
    if (!file.is_open()) 
        throw invalid_argument("Can not open file");
    /* Number of nodes, will use it in iterations */
    nodesNum = 0;
    /* Just a dummy var, used for counting numbers */
    int nums;
    while (file>>nums){
        nodesNum++;
    }
    /* Find the height, will use it for iterations and indexing mostly */
    this->h = find_height(nodesNum);
    /* Whole pyramid is structred in "nodes", it is dynamic array*/
    nodes = new Node *[h];
    /* Each row's length is the same with the given 
     * pyramid for memory purposes */
    for (int i = 0; i < h; i++){
        nodes[i] = new Node [i + 1];
    }
    /* Clears flags of file */
    file.clear();
    /* Puts the cursor at the beginning because we have read
     * the file once */
    file.seekg(0, ios::beg);
    /* Read numbers from file to "nodes", automatically
     * delimited with space character */
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            file >> nodes[i][j].val;
        }
    }
    /* Prime numbers are tagged
     * Will tag unusable numbers as prime in "maxSum" */
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            nodes[i][j].prime = !not_prime(nodes[i][j].val);
        }
    }
}

Pyramid::~Pyramid(){
    /* Dynamically created variables should be deleted by hand 
     * and files must be closed before exiting program */
    delete [] this->nodes;
    this->file.close();
}

int Pyramid::maxSum(){
    /* The main algorith is explained under main */

    /* Start from one level upper of last level, 
     * go one by one each number*/
    for (int i = h-2; i >= 0; i--){
        for (int j = 0; j <= i; j++){
            /* Create references to current node, 
             * left and right children */
            Node &curr = nodes[i][j];
            Node &left = nodes[i+1][j];
            Node &right = nodes[i+1][j+1];
            /*MY MISTAKE WITH PREVIOUS ASSIGNMENT
            *If any node's both children are prime, that node is considered prime too
            *because we cant use that node, we wont be able to walk further from that
            *if we use it. This is an issue this program faced because the down-top method
            */
            if (left.prime && right.prime){
                curr.prime = true;
            }
            /* We are ignoring prime numbers in every case */
            if (curr.prime == false){
                /* Select the maximum nonprime child */
                if (left.prime == false && right.prime == false){
                    if (left.val >= right.val){
                        curr.val += left.val;
                    }
                    else {
                        curr.val += right.val;
                    }
                }
                else {
                    if (left.prime == false){
                        curr.val += left.val;
                    }
                    else if (right.prime == false){
                        curr.val += right.val;
                    }
                }
            }
            
        }
    }
    /*Return top node which is the maximum sum */
    return nodes[0][0].val;
}

void Pyramid::print(){
    /* Print from top to down */
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            cout << this->nodes[i][j].val << " ";
        }
        cout << endl;
    }
}


