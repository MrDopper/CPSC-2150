#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include "CircularList.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

class RoundRobinProcessScheduler
{
private:
    int timeSlice;
    CircularLinkedList processTimes;
    Node *currentProcess;

public:
    // Constructor
    RoundRobinProcessScheduler() : timeSlice(0), currentProcess(nullptr) {}

    // Method to load data from the file
    void LoadFromFile(const string &fileName)
    {
        ifstream inFile(fileName);
        if (!inFile)
        {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }

        // Read the time slice (quantum)
        string line;
        if (!getline(inFile, line) || line.empty())
        {
            cerr << "Error reading time slice from file." << endl;
            return;
        }

        // Remove any whitespace around the time slice
        try
        {
            timeSlice = stoi(line);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid time slice in file: " << line << endl;
            return;
        }

        // Read process execution times
        if (!getline(inFile, line) || line.empty())
        {
            cerr << "Error reading process times from file." << endl;
            return;
        }

        // Parse and insert process times into the circular list
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos)
        {
            string token = line.substr(0, pos);
            try
            {
                int processTime = stoi(token);
                // Insert into circular list
                processTimes.insert(processTime);
            }
            catch (const invalid_argument &e)
            {
                cerr << "Invalid process time: " << token << endl;
                return;
            }
            line.erase(0, pos + 1);
        }

        // Insert the last remaining process time
        try
        {
            processTimes.insert(stoi(line));
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid process time: " << line << endl;
            return;
        }

        // Start from the first node after loading
        currentProcess = processTimes.getLast()->next;
    }

    Node *findNextProcess(Node *currentProcess)
    {
        Node *start = currentProcess;
        do
        {
            if (currentProcess->data > 0)
            {
                return currentProcess;
            }
            currentProcess = currentProcess->next;
        } while (currentProcess != start);

        return nullptr;
    }
    void Process()
    {
        if (!currentProcess)
        {
            cout << "There is no input" << endl;
            return;
        }

        int completedProcesses = 0;
        int totalProcesses = 0;
        int time = 0;

        // Count total processes by traversing the circular list
        Node *temp = currentProcess;
        do
        {
            totalProcesses++;
            temp = temp->next;
        } while (temp != currentProcess);

        // Array to store the turnaround times for each process
        vector<int> turnaroundTimes(totalProcesses, 0);

        while (completedProcesses < totalProcesses)
        {
            currentProcess = findNextProcess(currentProcess);
            if (!currentProcess)
            {
                break;
            }

            if (currentProcess->data > 0)
            {
                if (currentProcess->data > timeSlice)
                {
                    time += timeSlice;
                    currentProcess->data -= timeSlice;
                }
                else
                {
                    // Process completes within this time slice
                    time += currentProcess->data;
                    // Mark as completed
                    currentProcess->data = 0;
                    turnaroundTimes[completedProcesses] = time;
                    completedProcesses++;
                }
            }
            // Move to the next process in the circular list
            currentProcess = currentProcess->next;
        }

        // Write results to the output file
        ShowResults(turnaroundTimes, totalProcesses);
    }

    // Display and write the results to output.txt
    void ShowResults(const vector<int> &turnaroundTimes, int totalProcesses)
    {
        ofstream outFile("output.txt");
        if (!outFile)
        {
            cerr << "Error opening output.txt" << endl;
            return;
        }

        int totalTurnaroundTime = 0;
        for (int i = 0; i < totalProcesses; i++)
        {
            outFile << "P" << i + 1 << ": " << turnaroundTimes[i] << endl;
            totalTurnaroundTime += turnaroundTimes[i];
        }

        double averageTurnaroundTime = (double)totalTurnaroundTime / totalProcesses;
        outFile << "Average: " << averageTurnaroundTime << endl;

        outFile.close();
        cout << "Results have been written to output.txt." << endl;
    }
};

#endif
