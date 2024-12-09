#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SkipList.h"

using namespace std;

int main()
{
    srand(time(0));

    SkipList lst(3); // skiplist with maximum allowed level index

    lst.InsertElement(3);
    lst.InsertElement(4);
    lst.InsertElement(5);

    lst.InsertElement(13);
    lst.InsertElement(14);
    lst.InsertElement(1);
    lst.Search(13);
    lst.InsertElement(7);
    lst.InsertElement(11);
    lst.InsertElement(1);
    lst.InsertElement(5);
    lst.InsertElement(19);

    lst.InsertElement(313);
    lst.InsertElement(37);
    lst.InsertElement(311);
    lst.InsertElement(31);
    lst.InsertElement(35);
    lst.InsertElement(319);

    lst.Show();
    cout << "------------------" << endl;
    lst.Delete(1);
    lst.Show();
    cout << "------------------" << endl;
    lst.Delete(319);
    lst.Show();
    cout << "------------------" << endl;
    lst.Delete(14);
    lst.Show();
    cout << "------------------" << endl;
    lst.Rescale(5);
    cout << "Rescale" << endl;
    lst.Show();
    // SkipList list2(3);
    // list2.InsertElement(2);
    // list2.InsertElement(4);
    // list2.InsertElement(8);

    // cout << "List 2 before merge:" << endl;
    // list2.Show();

    // // Merging list2 into list1
    // lst.Merge(&list2);

    // cout << "List 1 after merging with List 2:" << endl;
    // lst.Show();
    return 0;
}