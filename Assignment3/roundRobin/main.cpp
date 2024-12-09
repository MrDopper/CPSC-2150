#include "RoundRobinProcessScheduler.h"
#include "iostream"
using namespace std;

int main()
{
    RoundRobinProcessScheduler scheduler;
    scheduler.LoadFromFile("process.txt");
    scheduler.Process();
    return 0;
}