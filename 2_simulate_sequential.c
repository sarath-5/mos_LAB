#include <iostream>
#include <vector>
using namespace std;
struct File {
string name;
int size;
};
class SequentialFileAllocation {
private:
vector<bool> blocks; // Represents the blocks of memory (true means allocated, false means free)
vector<File> files; // Keeps track of the files stored in memory
public:
SequentialFileAllocation(int totalBlocks) {
blocks.resize(totalBlocks, false); // Initialize all blocks as free
}
bool allocateFile(const string& name, int size) {
int startBlock = findFreeBlocks(size); // Find the starting block for the file
if (startBlock == -1) {
cout << "Not enough contiguous blocks available for file allocation." << endl;
return false;
}
// Mark the blocks as allocated
for (int i = startBlock; i < startBlock + size; i++) {
blocks[i] = true;
}
// Create the file and add it to the list
File file;
file.name = name;
file.size = size;
files.push_back(file);
cout << "File '" << name << "' allocated starting from block " << startBlock << "." << endl;
14
return true;
}
bool deallocateFile(const string& name) {
for (auto it = files.begin(); it != files.end(); ++it) {
if (it->name == name) {
int startBlock = findStartBlock(name);
int size = it->size;
// Mark the blocks as free
for (int i = startBlock; i < startBlock + size; i++) {
blocks[i] = false;
}
// Remove the file from the list
files.erase(it);
cout << "File '" << name << "' deallocated." << endl;
return true;
}
}
cout << "File '" << name << "' not found." << endl;
return false;
}
void printMemoryStatus() {
cout << "Memory Status:" << endl;
for (int i = 0; i < blocks.size(); i++) {
cout << "Block " << i << ": " << (blocks[i] ? "Allocated" : "Free") << endl;
}
}
private:
int findFreeBlocks(int size) {
int consecutiveFreeBlocks = 0;
for (int i = 0; i < blocks.size(); i++) {
if (!blocks[i]) {
consecutiveFreeBlocks++;
if (consecutiveFreeBlocks == size) {
return i - size + 1; // Starting block found
}
} else {
consecutiveFreeBlocks = 0; // Reset counter
}
}
return -1; // Not enough contiguous blocks available
}
int findStartBlock(const string& name) {
for (const auto& file : files) {
if (file.name == name) {
15
return findFreeBlocks(file.size);
}
}
return 
-1; // File not found
}
};
int main() {
int totalBlocks;
cout << "Enter the total number of blocks in memory: ";
cin >> totalBlocks;
SequentialFileAllocation sfa(totalBlocks);
int choice;
do {
cout << "
\nMenu:
\n";
cout << "1. Allocate file
\n";
cout << "2. Deallocate file
\n";
cout << "3. Print memory status
\n";
cout << "4. Exit
\n";
cout << "Enter your choice: ";
cin >> choice;
switch (choice) {
case 1: {
string name;
int size;
cout << "Enter the file name: ";
cin >> name;
cout << "Enter the file size (in blocks): ";
cin >> size;
sfa.allocateFile(name, size);
break;
}
case 2: {
string name;
cout << "Enter the file name: ";
cin >> name;
sfa.deallocateFile(name);
break;
}
case 3:
sfa.printMemoryStatus();
break;
case 4:
cout << "Exiting..." << endl;
break;
default:
cout << "Invalid choice. Please try again." << endl;
break;
}
} while (choice != 4);
return 0;
}
