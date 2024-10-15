#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // For INT_MAX
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int remainingTime;  // This will be used to keep track of remaining burst time
    int completionTime;
    int waitingTime;
    int turnAroundTime;

    // Constructor
    Process(int pID, int arrivalTime, int burstTime) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->remainingTime = burstTime;  // At the start, remaining time = burst time
        this->completionTime = 0;
        this->waitingTime = 0;
        this->turnAroundTime = 0;
    }

    // Display process details
    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Completion Time: " << completionTime
             << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

int main() {
    int n;
    cout << "Enter the Number of Processes for SJF (Pre-emptive): ";
    cin >> n;

    vector<Process> processes;

    // Input processes
    for (int i = 0; i < n; i++) {
        int pID, arrivalTime, burstTime;
        cout << "Enter pID: ";
        cin >> pID;
        cout << "Enter Arrival Time: ";
        cin >> arrivalTime;
        cout << "Enter Burst Time: ";
        cin >> burstTime;

        processes.push_back(Process(pID, arrivalTime, burstTime));
    }

    int completed = 0, currentTime = 0;
    int shortestProcessIndex = -1;
    int minRemainingTime = INT_MAX;
    bool processRunning = false;
    int lastFinishTime = 0;

    while (completed != n) {
        // Find the process with the minimum remaining burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].remainingTime < minRemainingTime) {
                shortestProcessIndex = i;
                minRemainingTime = processes[i].remainingTime;
                processRunning = true;
            }
        }

        if (!processRunning) {
            currentTime++;  // If no process is ready to execute, increment time
            continue;
        }

        // Decrease the remaining time of the chosen process
        processes[shortestProcessIndex].remainingTime--;
        minRemainingTime = processes[shortestProcessIndex].remainingTime;

        // If a process is completed
        if (processes[shortestProcessIndex].remainingTime == 0) {
            completed++;
            processRunning = false;
            minRemainingTime = INT_MAX;  // Reset minRemainingTime for the next selection

            // Calculate completion, turnaround, and waiting times
            processes[shortestProcessIndex].completionTime = currentTime + 1;
            processes[shortestProcessIndex].turnAroundTime = processes[shortestProcessIndex].completionTime - processes[shortestProcessIndex].arrivalTime;
            processes[shortestProcessIndex].waitingTime = processes[shortestProcessIndex].turnAroundTime - processes[shortestProcessIndex].burstTime;
        }

        currentTime++;  // Increment current time for each time unit
    }

    // Display process information
    cout << "\nProcess Scheduling Results (SJF Pre-emptive):\n";
    for (const auto &p : processes) {
        p.display();
    }

    // Calculate and display average waiting time and turnaround time
    double avgWaitingTime = 0;
    double avgTurnAroundTime = 0;

    for (const auto &p : processes) {
        avgWaitingTime += p.waitingTime;
        avgTurnAroundTime += p.turnAroundTime;
    }

    avgWaitingTime /= n;
    avgTurnAroundTime /= n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
