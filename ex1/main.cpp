#include <iostream>
#include <vector>
using namespace std;

void printVec(vector<int> vec){
    for(int i : vec){
        cout << i << " ";
    }
    cout << endl;
}


int main(){
    vector<int> vec(5, 1);
    
    printVec(vec);

    vec.insert(vec.begin()+2, 5);

    printVec(vec);

    vec.at(5) = 6;

    printVec(vec);

    vec.erase(vec.begin()+1);

    printVec(vec);

}