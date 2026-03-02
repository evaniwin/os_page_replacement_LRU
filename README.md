# OS Page Replacement LRU

This project is built with the following criteria
```
Simulate the LRU, and optimal page-replacement algorithms as follows: First, generate a
random page-reference string where page numbers range from 0 to 9. Apply the random
page-reference string to each algorithm, and record the number of page faults incurred by
each algorithm. Assume that demand paging is used. The length of the reference string and
the number of page frames (varying from 1 to 7) are to be received as command line
arguments
```
### This project is build using make

> [!WARNING]
> The make Build Utility must be manually installed in windows.

Build the project with
``` 
make all
```

Run the project with
```
make run
```

Clean old build files with 
```
make clean
```

```text
Enter the length of the refrence String
> 20

Enter the size of the frame
> 5
Generated Reference String:
2 6 6 2 8 5 0 9 5 1 4 8 4 5 0 6 9 2 7 2 

LRU Page Replacement
2 2 ^ ^ 2 2 2 2 ^ 1 1 1 ^ ^ 1 6 6 6 6 ^ 
- 6 | | 6 6 6 9 | 9 9 9 | | 0 0 0 0 0 | 
- - | | 8 8 8 8 | 8 4 4 | | 4 4 4 2 2 | 
- - | | - 5 5 5 | 5 5 5 | | 5 5 5 5 7 | 
- - o o - - 0 0 o 0 0 8 o o 8 8 9 9 9 o 
Total Page faults: 14

Optimal Page Replacement
2 2 ^ ^ 2 2 2 9 ^ 1 4 ^ ^ ^ ^ ^ 9 2 2 ^ 
- 6 | | 6 6 6 6 | 6 6 | | | | | 6 6 7 | 
- - | | 8 8 8 8 | 8 8 | | | | | 8 8 8 | 
- - | | - 5 5 5 | 5 5 | | | | | 5 5 5 | 
- - o o - - 0 0 o 0 0 o o o o o 0 0 0 o 
Total Page faults: 11
```