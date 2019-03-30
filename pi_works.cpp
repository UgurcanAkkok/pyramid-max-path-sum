#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool check_usage (int); // There should be 1 additional argument (PROGRAM FILE)
int find_height(int); //Given number of nodes, finds height of pyramid
bool not_prime(int); // We cant use prime nodes
void printPyramid(int * p, int h);
struct Node {
    bool prime;
    int val;
};
class Pyramid {
    private:
        ifstream file;
        unsigned short h;
        unsigned int nodesNum;
        Node ** nodes;
    public:
        Pyramid(const char *);
        ~Pyramid();
        void print();
        int maxSum();
};


int main(int argc, char* argv[]){
    if (check_usage(argc) == false) return 1;
    Pyramid pyr(argv[1]);
    
    cout << "The maximum path sum is "<< pyr.maxSum() << endl;
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
    return (-1 + sqrt(1 + 8 * len)) / 2;
}

bool check_usage(int c){
    if (c != 2){
        cout << "Usage is \" maxpath FILE_NAME \"" << endl;
        return false;
    }
    return true;
}

Pyramid::Pyramid(const char * fName){
    file = ifstream(fName);
    if (!file.is_open()) 
        throw invalid_argument("Can not open file");
    nodesNum = 0;
    int node;
    while (file>>node){
        nodesNum++;
    }
    this->h = find_height(nodesNum);
    nodes = new Node *[h];
    for (int i = 0; i < h; i++){
        nodes[i] = new Node [i + 1];
    }
    file.clear();
    file.seekg(0, ios::beg);
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            file >> nodes[i][j].val;
        }
    }
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            nodes[i][j].prime = !not_prime(nodes[i][j].val);
        }
    }
}

Pyramid::~Pyramid(){
    delete [] this->nodes;
    this->file.close();
}

int Pyramid::maxSum(){
    for (int i = h-2; i >= 0; i--){
        for (int j = 0; j <= i; j++){
            Node &curr = nodes[i][j];
            Node &left = nodes[i+1][j];
            Node &right = nodes[i+1][j+1];
            
            if (curr.prime == false){
                if (left.prime == false && left.val >= right.val){
                    curr.val += left.val;
                }
                else if (right.prime == false && right.val >= left.val){
                    curr.val += right.val;
                }
            }
        }
    }
    return nodes[0][0].val;
}

void Pyramid::print(){
    for (int i = 0; i < h; i++){
        for (int j = 0; j <= i; j++){
            cout << this->nodes[i][j].val << " ";
        }
        cout << endl;
    }
}


