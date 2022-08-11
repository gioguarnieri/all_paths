# allPaths.cpp

In this repository we hold a code that calculates the length of all possible paths leaving a node to every other node in the network. This process is done via a BFS, and then printed on screen. There is a small tutorial commented inside the code on how to run it.

This code uses 2 file inputs, being them:

# listAdj.txt

A file containing the adjacency list of your desired graph. Here we have the Zachary's Karate Club graph as an example on how the adjacency list should be.

# spl.txt

A file containing a matrix with all the shortest path length from node i to j, needed to know where the BFS should start, since we can't have paths smaller than the shortest one.
