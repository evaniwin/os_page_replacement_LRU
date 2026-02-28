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