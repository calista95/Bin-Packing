# Bin-Packing

# Description: 

This program will read from a text file called bin.txt and return the number of bins needed to hold a vector of items with a given container capacity. It will use two algorithms to do this: 

First-Fit: Put each item as you come to it into the first (earliest opened) bin into which it fits.  If there is no available bin then open a new bin. 

First-Fit-Decreasing: First sort the items in decreasing order by size, then use First-Fit on the resulting list. 
