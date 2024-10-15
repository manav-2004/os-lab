// First Come First Serve Implementation


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

    // Constructor
    Process(int pID, int arrivalTime, int burstTime) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->completionTime=0;
        this->turnAroundTime = 0;
        this->waitingTime = 0;
    }

    // Display process details
    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Completion Time: " << completionTime << ", Waiting Time: " << waitingTime
             << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

// Function to sort the processes by arrival time
bool compareArrivalTime(const Process &p1, const Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the Number of Processes for FCFS: ";
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

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // FCFS scheduling calculations
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Calculate waiting time for the current process
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;  // If the CPU is idle, move the current time to the process arrival time
        }

        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;

        currentTime += processes[i].burstTime;
        // Calculate turnaround time for the current process
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

      
        
    }

    // Display process information
    cout << "\nProcess Scheduling Results (FCFS):\n";
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
