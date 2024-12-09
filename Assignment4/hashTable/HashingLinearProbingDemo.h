/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include <iostream>
#include <functional>
// #include "SkipList.h"
using namespace std;
class HashingLinearProbingDemo
{
public:
    HashingLinearProbingDemo();
    ~HashingLinearProbingDemo();
    HashingLinearProbingDemo(int size, double lft);
    void Insert(int value);
    void ReHash();
    void Delete(int value);
    bool Search(int value, bool check);
    void Display();

private:
    int *hashTable;
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold;
};
#endif