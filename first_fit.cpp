#include <iostream>
#include <vector>
using namespace std;

class FirstFitAllocator {
private:
    vector<int> memoryBlocks; // Available memory blocks
    vector<int> allocatedBlocks; // Allocation results for processes

public:
    // Constructor to initialize memory blocks
    FirstFitAllocator(vector<int> blocks) {
        memoryBlocks = blocks;
        allocatedBlocks.resize(blocks.size(), -1); // Initialize all allocations as -1 (unallocated)
    }

    // Function to allocate memory to processes using First-Fit algorithm
    void allocateMemory(vector<int> processSizes) {
        for (int i = 0; i < processSizes.size(); i++) {
            bool allocated = false;

            // Try to allocate the process to the first fitting memory block
            for (int j = 0; j < memoryBlocks.size(); j++) {
                if (memoryBlocks[j] >= processSizes[i]) {
                    // Allocate the memory block to the process
                    memoryBlocks[j] -= processSizes[i];
                    allocatedBlocks[i] = j; // Record which block was used
                    allocated = true;
                    break;
                }
            }

            // If no suitable memory block is found
            if (!allocated) {
                cout << "Process " << i + 1 << " with size " << processSizes[i] << " could not be allocated memory.\n";
            }
        }
    }

    // Function to display allocation results
    void displayAllocation() {
        cout << "\nAllocation Results:\n";
        for (int i = 0; i < allocatedBlocks.size(); i++) {
            if (allocatedBlocks[i] != -1) {
                cout << "Process " << i + 1 << " allocated to memory block " << allocatedBlocks[i] + 1 << "\n";
            }
        }
    }

    // Function to display the remaining memory blocks after allocation
    void displayRemainingMemory() {
        cout << "\nRemaining Memory in Blocks:\n";
        for (int i = 0; i < memoryBlocks.size(); i++) {
            cout << "Block " << i + 1 << ": " << memoryBlocks[i] << " KB remaining\n";
        }
    }
};

int main() {
    // Memory blocks (in KB)
    vector<int> memoryBlocks = {100, 500, 200, 300, 600};

    // Process sizes (in KB)
    vector<int> processSizes = {212, 417, 112, 426};

    // Initialize the First-Fit memory allocator
    FirstFitAllocator allocator(memoryBlocks);

    // Allocate memory to processes
    allocator.allocateMemory(processSizes);

    // Display the allocation results
    allocator.displayAllocation();

    // Display remaining memory in blocks after allocation
    allocator.displayRemainingMemory();

    return 0;
}
