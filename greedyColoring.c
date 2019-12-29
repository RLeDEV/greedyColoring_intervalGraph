/*
* Author: Raz Levy
* **Greedy Coloring Algo **
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Interval {
	int start,end;
	int colorID;
	int degree;
} vertex;

void GreedyColoring();
void printVertexes(vertex*, int);
void setDegree(vertex*, int);
int getMaxDegree(vertex* arr, int k);
int getMinDegree(vertex* arr, int k);
int getSumDegrees(vertex* arr, int k);
void printByColor(vertex* arr, int k);
void sort(vertex* arr, int k);
void greedyALGO(vertex* arr, int k);

void main() {
	GreedyColoring();
	system("pause");
}

void GreedyColoring() {
	int k, i;
	vertex *arr;
	printf("Please input k\n");
	scanf("%d", &k); // getting the interval's family size into K
	// Dynamic memory allocate
	arr = (vertex*)malloc(k*sizeof(vertex));
	// Getting all vertex's (interval) data
	for (i = 0; i < k; i++) {
		printf("Interval %d: ", i+1);
		scanf("%d%d", &arr[i].start, &arr[i].end);
		arr[i].degree = 0;
		arr[i].colorID = -1;
	}
	// Prints all the vertexes
	printVertexes(arr, k);
	sort(arr, k);
	// Setting degree for all vertexes
	setDegree(arr, k);
	printf("G edges = %d\n", getSumDegrees(arr, k) / 2);
	printf("Maximum degree of G = %d\n", getMaxDegree(arr, k));
	printf("Minumim degree of G = %d\n", getMinDegree(arr, k));
	// Num of edges is sum of degrees / 2;
	printf("G's Complement Edges = %d\n", (k*(k - 1)) / 2 - (getSumDegrees(arr, k) / 2));
	printf("Maximum degree of G's Complement = %d\n", k - getMinDegree(arr, k) - 1);
	printf("Minimum degree of G's Complement = %d\n", k - getMaxDegree(arr, k) - 1);
	// Setting colors by greedy coloring algorithm
	greedyALGO(arr, k);
	// Sorting by colorID and prints by color
	printByColor(arr,k);
}

void printVertexes(vertex* arr, int k) {
	int i;
	printf("The Intervals family is:\n");
	// Running trough arr and prints every interval
	for (i = 0; i < k; i++) {
		printf("[%d,%d]", arr[i].start, arr[i].end);
		// In case its not the last vertex, prints also ',' between them.
		if (i < k - 1) {
			printf(",");
		}
	}
	printf("\n");
}

void setDegree(vertex* arr, int k) {
	int i,j;
	// Running through all vertexes and checks if there is a 'cut' between them, increasing both of their degrees
	for (i = 0; i < k; i++) {
		for (j = i + 1; j < k; j++) {
			// checks if there's a 'cut' between arr[i] and arr[j]
			if (!((arr[i].end < arr[j].start) || (arr[i].start > arr[j].end))) {
				arr[i].degree++;
				arr[j].degree++;
			}
		}
	}
}

int getMaxDegree(vertex* arr, int k) {
	int max = 0, i;
	for (i = 0; i < k; i++) {
		if (arr[i].degree > max) {
			max = arr[i].degree;
		}
	}
	return max;
}

int getMinDegree(vertex* arr, int k) {
	int min = arr[0].degree, i;
	for (i = 1; i < k; i++) {
		if (arr[i].degree < min) {
			min = arr[i].degree;
		}
	}
	return min;
}

int getSumDegrees(vertex* arr, int k) {
	int sum = 0, i;
	// adding degree of each vertex to the sum
	for (i = 0; i < k; i++) {
		sum += arr[i].degree;
	}
	return sum;
}

void sort(vertex* arr, int k){
	int j, i;

	for (i = 1; i<k; i++)
	{
		for (j = 0; j<k - i; j++)
		{
			if (arr[j].start > arr[j + 1].start)
			{
				vertex temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void greedyALGO(vertex* arr, int k) {
	int i,ch,c,color =0;
	int *colorsArray;
	bool *isNeighbor;
	arr[0].colorID = 0; // define first vertex's color as 0
	colorsArray = (int*)malloc(k * sizeof(int)); // array of possible colors (in case it's a K graph)
	for (i = 0; i < k; i++) {
		colorsArray[i] = i;
	}
	isNeighbor = (bool*)malloc(k * sizeof(bool)); // bools array to find neighbors for each vertex
	for (i = 1; i < k; i++) { // Initializing all vertexes except the first one color to -1
		arr[i].colorID = -1;
	}
	for (i = 0; i < k; i++) { // Initializing all neighbors to false
		isNeighbor[i] = false;
	}
	for (i = 1; i < k; i++) {
		for (c = 0; c < k; c++) { // finds the neighbors of vertex number C
			if (c == i)
				continue;
			else if (!((arr[c].end < arr[i].start) || (arr[c].start > arr[i].end))) {
				isNeighbor[c] = true;
			}
		}
		for (ch = 0; ch < i; ch++) { // If there's a neighbor, then delete the neighbor's colorID from
			if (isNeighbor[ch] == true) {	// the possible colors list by making it -1
				for (int j = 0; j < i; j++) {
					if (colorsArray[j] == arr[ch].colorID)
						colorsArray[j] = -1;
				}
			}
		}
		for (ch = 0; ch < k; ch++) { // takes the first possible color
			if (colorsArray[ch] != -1) {
				color = colorsArray[ch];
				break;
			}
		}
		arr[i].colorID = color; // Initializing the color into vertex I
		for (c = 0; c < k; c++) { // reseting neighbors for next vertex
			isNeighbor[c] = false;
		}
		for (int n = 0; n < k; n++) { // reseting possible colors for next vertex
			colorsArray[n] = n;
		}
	}
	free(colorsArray); // free dynamic memory allocated for possible colors
	free(isNeighbor); // free dynamic memory allocated for neighbors
}

void printByColor(vertex* arr, int k) {
	int j, i;
	// Sorting the array by the colorID
	for (i = 1; i < k; i++) {
		for (j = 0; j < k - 1; j++) {
			if (arr[j].colorID > arr[j + 1].colorID) {
				vertex temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// find the max degree
	int max = 0;
	for (int i = 0; i < k; i++) {
		if (arr[i].colorID > max)
			max = arr[i].colorID;
	}
	printf("Optional Coloring: ");
	// Prints the color of the vertex
	for (i = 0; i <= max; i++) {
		printf("{");
		for (j = 0; j < k; j++) {
			if (arr[j].colorID == i) {
				printf("[%d,%d]", arr[j].start, arr[j].end);
				if (arr[j].colorID == arr[j + 1].colorID)
					printf(",");
			}
		}
		printf("}");
		printf("= %d", i + 1);
		if (!(i == max)) {
			printf(", ");
		}
	}
	printf("\n");
}
