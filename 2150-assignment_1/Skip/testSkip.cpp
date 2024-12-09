#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SkipList.h"
using namespace std;

int main(){
    srand(time(0));
 
    SkipList lst(5); 
 

    lst.InsertElement(19);
    lst.InsertElement(30);
    lst.Show();
    cout<<"----------------------"<<endl;
    lst.Delete(19);
    lst.Show();
    return 0;
}