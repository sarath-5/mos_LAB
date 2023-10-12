#include <stdio.h>
#include <stdlib.h>
#define MAX_PAGES 100
// Page frame structure
typedef struct {
int page;
int count; // For LFU algorithm
} PageFrame;
// Function prototypes
int fifo(int pages[], int n, int capacity);
int lru(int pages[], int n, int capacity);
int lfu(int pages[], int n, int capacity);
int main() {
int n; // Number of pages
int pages[MAX_PAGES]; // Array to hold page references
int capacity; // Page frame capacity
printf("Enter the number of pages: ");
scanf("%d", &n);
printf("Enter the page references: ");
for (int i = 0; i < n; i++) {
scanf("%d", &pages[i]);
}
printf("Enter the page frame capacity: ");
scanf("%d", &capacity);
int algorithm;
printf("Select the page replacement algorithm:\n");
printf("1. FIFO\n");
printf("2. LRU\n");
printf("3. LFU\n");
printf("Enter your choice: ");
scanf("%d", &algorithm);
int pageFaults;
switch (algorithm) {
case 1:
pageFaults = fifo(pages, n, capacity);
printf("Page faults using FIFO: %d\n", pageFaults);
break;
case 2:
pageFaults = lru(pages, n, capacity);
printf("Page faults using LRU: %d\n", pageFaults);
break;
43
case 3:
pageFaults = lfu(pages, n, capacity);
printf("Page faults using LFU: %d\n", pageFaults);
break;
default:
printf("Invalid choice.\n");
return 1;
}
return 0;
}
int fifo(int pages[], int n, int capacity) {
PageFrame* frame = (PageFrame*) malloc(capacity * sizeof(PageFrame));
int pageFaults = 0;
int currentIndex = 0;
// Initialize page frames
for (int i = 0; i < capacity; i++) {
frame[i].page = -1;
}
for (int i = 0; i < n; i++) {
int currentPage = pages[i];
int found = 0;
// Check if the page is already in a frame
for (int j = 0; j < capacity; j++) {
if (frame[j].page == currentPage) {
found = 1;
break;
}
}
if (!found) {
frame[currentIndex].page = currentPage;
currentIndex = (currentIndex + 1) % capacity;
pageFaults++;
}
}
free(frame);
return pageFaults;
}
int lru(int pages[], int n, int capacity) {
PageFrame* frame = (PageFrame*) malloc(capacity * sizeof(PageFrame));
int pageFaults = 0;
// Initialize page frames
for (int i = 0; i < capacity; i++) {
frame[i].page = -1;
frame[i].count = 0;
}
for (int i = 0; i < n; i++) {
int currentPage = pages[i];
44
int found = 0;
// Check if the page is already in a frame
for (int j = 0; j < capacity; j++) {
if (frame[j].page == currentPage) {
found = 1;
frame[j].count = i + 1; // Update the count
break;
}
}
if (!found) {
int leastCount = frame[0].count;
int replaceIndex = 0;
// Find the page with the least count
for (int j = 1; j < capacity; j++) {
if (frame[j].count < leastCount) {
leastCount = frame[j].count;
replaceIndex = j;
}
}
frame[replaceIndex].page = currentPage;
frame[replaceIndex].count = i + 1;
pageFaults++;
}
}
free(frame);
return pageFaults;
}
int lfu(int pages[], int n, int capacity) {
PageFrame* frame = (PageFrame*) malloc(capacity * sizeof(PageFrame));
int pageFaults = 0;
// Initialize page frames
for (int i = 0; i < capacity; i++) {
frame[i].page = -1;
frame[i].count = 0;
}
for (int i = 0; i < n; i++) {
int currentPage = pages[i];
int found = 0;
int minCount = frame[0].count;
int replaceIndex = 0;
// Check if the page is already in a frame
for (int j = 0; j < capacity; j++) {
if (frame[j].page == currentPage) {
found = 1;
frame[j].count++;
break;
}
45
if (frame[j].count < minCount) {
minCount = frame[j].count;
replaceIndex = j;
}
}
if (!found) {
frame[replaceIndex].page = currentPage;
frame[replaceIndex].count = 1;
pageFaults++;
}
}
free(frame);
return pageFaults;
}