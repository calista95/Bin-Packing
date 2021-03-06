# Bin-Packing

# Description for bin.cpp: 

This program will read from a text file called bin.txt and return the number of bins needed to hold a vector of items with a given container capacity. It will use two algorithms to do this: 

First-Fit: Put each item as you come to it into the first (earliest opened) bin into which it fits.  If there is no available bin then open a new bin. 

First-Fit-Decreasing: First sort the items in decreasing order by size, then use First-Fit on the resulting list. 

# Format of file: 

The first line is the number of test cases, followed by the capacity of bins for that test case, the number of items and then the weight of each item. 

Ex:
```
2 
10
6 
5 10 2 5 4 4 
10
20
4 4 4 4 4 4 4 4 4 4 6 6 6 6 6 6 6 6 6 6 
 
```
# Output
For the example above:   
Test Case 1   
First Fit : 4  
First Fit Decreasing : 3   
Test Case 2   
First Fit : 15    
First Fit Decreasing : 10  

# How to run
```
g++ bin.cpp 
a.out
```
# Description for binIP.cpp: 
This program will read from a file called binEC.txt. It will read the information in the file in the same way and format as for bin.cpp, but it will parse the information into a .txt file readable by a linear program. See one of the test cases attached as an example.

# How to run
```
g++ binIP.cpp 
a.out
```
