/*
C++ program to print all paths from a source to destination. 
In this iteration, we use it to calculate all paths going from the start, here is 0, with a maximun of 33 steps, the limit of our graph.
It is needed the following inputs:

    arq2 = fopen("listAdj.txt","r");
    The adjacency list of your graph (or edge list) with the nodes separated via white space, as in:
    0	1
    0	2
    0	3
    0	4
    0	5
    0	6
    0	7
    0	8


    arq3 = fopen("spl.txt","r");
    A shortest path matrix from every node to every node, needed to know where to start our calculation since the paths can't be smaller then the shortest.


    to compile we recomend "g++ allPaths.c++ -O2 -o allPaths.out;
    and to run "time ./a.out > outfile_0.dat";
    since the results will be printed in screen.

    the outfile is given as:
    starting_node ending_node length_of_path

    Example:

    0 1 1
    0 1 2
    0 1 3
    0 1 4
    0 1 4
    0 1 7
    0 1 8

    So, in here we have a lot of paths going from 0 to 1 with different lengths.

*/

#include <stdlib.h> 
#include <stdio.h>
#include <iostream> 
#include <list>
using namespace std;
#define N 34
#define L 78

/*With both files ready, you need to change the values below
N: count of nodes;
L: count of edges;
start: the starting node to calculate all other paths;
steps: cutoff of how many steps you want to take.
*/

int l, i, j, spl[N+1][N+1], start = 0, max_steps = 33; //  34 78 



// A directed graph using adjacency list representation 
class Graph 
{ 
    int V; // No. of vertices in graph 
    list<int> *adj; // Pointer to an array containing adjacency lists 

    FILE *arq1;
	
    // A recursive function used by printAllPaths() 
    void printAllPathsUtil(int, int , int , bool [], int [], int &); 
  
public: 
    Graph(int V); // Constructor 
    void addEdge(int u, int v); 
    void printAllPaths(int s, int d); 
    void vulnerability(int v); 

}; 

Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
 
void Graph::addEdge(int u, int v) 
{ 
    adj[u].push_back(v); // Add v to u’s list. 
} 

// Prints all paths from 's' to 'd' 
void Graph::printAllPaths(int s, int d) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
  
    // Create an array to store paths 
    int *path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 

    // Call the recursive helper function to print all paths 
    printAllPathsUtil(s, s, d, visited, path, path_index); 

} 
  
// A recursive function to print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void Graph::printAllPathsUtil(int s, int u, int d, bool visited[], 
                            int path[], int &path_index)
{ 

    // Mark the current node and store it in path[]  
    visited[u] = true; 
    path[path_index] = u; 
    path_index++;
  
    // If current vertex is same as destination, then print 
    // current path[] 
    if (u == d)
    { 
        //for (int i = 0; i<path_index; i++) cout << path[i] << " ";
        //cout << endl;
        // fprintf(arq1, "%d %d %d\n", path[0], path[path_index-1], path_index-1);
        
		//printf("%d %d %d %d\n", path[0], path[path_index-1], path_index-1);
        printf("%d %d %d\n", path[0], path[path_index-1], path_index-1);
    } 
    else // If current vertex is not destination 
    { 
        // Recur for all the vertices adjacent to current vertex 
        list<int>::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
            //if (!visited[*i]) 
				//0 1 1 1 1 1 1 1 1 2 1 1 1 1 3 3 2 1 3 1 3 1 3 3 2 2 3 2 2 3 2 1 2 2
            if ( !visited[*i] and path_index <= (spl[s][d]+max_steps) ) {   //    CUTTING!!!    //    spl=1, spl+1=2, spl+2=3, spl+3=4 
                //printf("%d %d %d \n", *i, d, spl[*i][d]);
                //system("pause");
                printAllPathsUtil(s, *i, d, visited, path, path_index);
			}
				//printf(" --- %d %d %d --- ", u, d, spl[u][d]);
    } 


/*
    for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			printf("%d %d %d ", i, j, spl[i][j]);
		}
		printf("\n");
	}		
*/
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--;
    visited[u] = false;
} 

void Graph::vulnerability(int v)
{ 
 double efi, new_efi, vul;
 efi=2;
 new_efi=v;
 vul=(efi-new_efi)/efi;
 cout << v << " " << efi << " " << new_efi << " " << vul << endl; 
}
  
// Driver program 
int main() 
{ 

    FILE *arq2;
    arq2 = fopen("listAdj.txt","r");

    FILE *arq3;
    arq3 = fopen("spl.txt","r");
   	
    int s, S, d, D; //source and destination
	
    // Create a graph given in the above diagram 
    Graph g(N);
    
    for(l=0;l<L;l++) {
	    fscanf(arq2, "%d %d", &s, &d);
		//printf("%d\n", l);
        g.addEdge(s, d); 
        g.addEdge(d, s);  
    }

    for(i=0;i<N;i++) for(j=0;j<N;j++) fscanf(arq3, "%d", &spl[i][j]);
	

    //cout << "All different paths from " << s 
    //    << " to " << d << endl; 

    S=N;
    D=N;

    //for(s=0;s<S;s++) for(d=0;d<D;d++) if(d!=s) g.printAllPaths(s, d); 
	
	// system("pause");
	s=start;	
	for(d=0;d<D;d++) if(d!=s) g.printAllPaths(s, d); 
	
    //g.vulnerability(1);
    //vou salvar tbm uma lista com o comprimento de todos os caminhos entre O e D, com base nisso dá para calcular a Ei e então a Vi

    fclose(arq2);
    // system("pause");
    return 0; 
} 




/*
    Graph g(5); 
    g.addEdge(0, 1); 
        g.addEdge(1, 0); 
    g.addEdge(0, 2);
        g.addEdge(2, 0);
    g.addEdge(1, 2); 
        g.addEdge(2, 1); 
    g.addEdge(1, 4); 
        g.addEdge(4, 1); 
    g.addEdge(2, 3); 
        g.addEdge(3, 2);     
    g.addEdge(3, 4); 
        g.addEdge(4, 3); 



    g.addEdge(0, 1); 
        g.addEdge(1, 0); 
    g.addEdge(0, 2);
        g.addEdge(2, 0);
    g.addEdge(1, 2); 
        g.addEdge(2, 1); 
    g.addEdge(2, 3); 
        g.addEdge(3, 2);     

*/

