#include "CircularList.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <cmath>

class RoundRobin{
    public:
        RoundRobin(){
            turnaround_times = nullptr;
        }
        void LoadFromFile(string file_name){
            outFile.open("output.txt"); 
            outFile<<"";
            outFile.close();
            input.open(file_name);
            int task_num = 0;
            while(!input.eof()){
                task_num+=1;
                string a;
                id_update = 0;
                getline(input, a);
                time_slice = stoi(a, nullptr);
                getline(input, a);
                a+=",";
                int len = a.length();
                string::size_type sz;
                int node_value;
                while(a.length()>0){
                    node_value = stoi(a, &sz);
                    if(sz != len-1){
                        a = a.substr(sz+1);
                    }
                    else
                        a = "";
                    
                    processTimes.insert(node_value, id_update++); 
                }
                Process(task_num);
            }
            
        }
        void Process(int task_num){
            turnaround_times = processTimes.cycle(time_slice, id_update);
            ShowResults(task_num);
        }
        void ShowResults(int task_num){
            outFile.open("output.txt", ios::app);
            outFile<<"Task "<<task_num<<": "<<endl;
            if(turnaround_times != nullptr){
                double turnaround_time = 0.0;
                for(int i = 0; i<id_update; i++){
                    turnaround_time += 1.0*turnaround_times[i];
                    outFile<<"p"<<i+1<<": "<<turnaround_times[i]<<endl;
                }
                turnaround_time = turnaround_time/id_update;
                turnaround_time =  std::round(turnaround_time * 100) / 100;
                outFile<<"Average turnaround time: "<<turnaround_time<<endl;
            }
            outFile.close();
        }

    private:
        CircularLinkedList processTimes;
        ifstream input;
        int time_slice;
        int id_update;
        int* turnaround_times;
        ofstream outFile;

};