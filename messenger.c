
/*
Nabin Giri
nvngiri2@gmail.com

Imperial Messengers Problem in C
*/


#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

max_cities = 100; // given in the question as the empire can have maximum of 100 cities. 
max_int = INT_MAX;
typedef int matrix[100 + 1][100 + 1]; // total number of rows and cols for the graph matrix.
#define V 6 // number of vertices

int short_path(int dist[], bool boolset[]) // checkes the minimum cost of path, which are false in boolset.
{
	int min = max_int, min_index;
	for (int v = 0; v < V; v++)
		if (boolset[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}


void shortest_path(matrix graph_matrix, int start) // a graph representation of adjacency matrix
{
	int dist[V]; // this stores the shortes path to the destination
	bool boolset[V]; // this stores bool values; if the short path is identified then make it true
	for (int i = 0; i < V; i++) // initilize all the values as maximum values first and bool values as false
		dist[i] = max_int, boolset[i] = false;
	dist[start] = 0; // the start city does not have any cost
	for (int count = 0; count < V - 1; count++)
	{
		int u = short_path(dist, boolset); // getting the index of short path
		boolset[u] = true; // set true once the short path is identified
		for (int v = 0; v < V; v++) // updating values
			if (!boolset[v] && graph_matrix[u][v] && dist[u] != max_int + 1
				&& dist[u] + graph_matrix[u][v] < dist[v])
				dist[v] = graph_matrix[u][v];

	}
	// just calculating the sum of the shortest path identified.
	int result = 0;
	for (int i = 0; i < V - 1; i++)
	{
		result = result + dist[i];
	}
	result = result - dist[3];
	printf("%d ", result);

}


int stream_inputs()
{
	// reads the streaming input form the stdin
	char input[30];
	for (int i = 0; i < sizeof(input) - 1; i++)
	{
		char nums = (char)getc(stdin);
		if (nums == 'X' || nums == 'x') // as x and X indicates the message cannot go through this path.
			return max_int;
		if (nums < '0' || nums > '9')
		{
			if (i == 0) continue;
			input[i] = 0;
			return atoi(input); // converts string to int
		}
		input[i] = nums;
	}
	input[29] = 0;
	return atoi(input);
}


void init()
{
	int cities_num = stream_inputs(); //reads the first input, the number of cities
	matrix graph_matrix; // initializing matrix

	for (int i = 0; i < V; i++) // keeping all the values of matrix  as zero 
	{
		for (int j = 0; j < V + 1; j++)
		{
			graph_matrix[i][j] = 0;
		}
	}


	for (int src = 2; src <= cities_num; ++src) // filling the values into the matrix 
	{
		for (int des = 1; des < src; ++des)
		{
			int cost = stream_inputs();
			graph_matrix[src][des] = cost; // question says A(i,j) == A(j,i)
			graph_matrix[des][src] = cost;

		}

	}
	shortest_path(graph_matrix, 0);
}



int main(void)
{
	
	init();
	return 0;

}
