This program generates a boggle board and then solves it. It solves the boarding by processing a dictionary file into a Trie data structure. 

The program then executes a depth first search on the boggle board and compares each branch to the Trie. It prunes branches as necessary to speed it up.

I recommend compiling it with aggressive optimizations (-O3). I was able to get an order of magnitude speed increase with no changes in correctness. 
