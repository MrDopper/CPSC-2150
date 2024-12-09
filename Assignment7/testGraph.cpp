#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
using namespace std;

vector<vector<bool>> GenerateFriendshipMatrix(int n){
    vector<vector<bool>> mat(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){ 
                continue;
            }
            mat[i][j] = mat[j][i] = rand()%2;
        }
    }
    return mat;
}

int main(){
    srand(time(0));

    vector<vector<bool>> mat = GenerateFriendshipMatrix(5);

    Graph g(mat);

    // test all features of the Graph class
 

    return 0;
}
