/*
* Full Name: Raz Levy
* ID : 311335699
* Lecturer : Ahuva Meualem
* **Greedy Coloring Task **
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
void sort(vertex* arr, int k);

void main() {
	GreedyColoring();
	system("pause");
}

void GreedyColoring() {
	int k,i;
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
		arr[i].colorID = 0;
	}
	// Prints all the vertexes
	printVertexes(arr, k);
	sort(arr, k);
	printVertexes(arr, k);
	// Setting degree for all vertexes
	setDegree(arr, k);
	printf("G edges = %d\n", getSumDegrees(arr, k) / 2);
	printf("Maximum degree of G = %d\n", getMaxDegree(arr, k));
	printf("Minumim degree of G = %d\n", getMinDegree(arr, k));
	// Num of edges is sum of degrees / 2;
	printf("G's Complement Edges = %d\n", (k*(k - 1)) / 2 - (getSumDegrees(arr, k) / 2));
	printf("Maximum degree of G's Complement = %d\n", k - getMinDegree(arr, k) - 1);
	printf("Minimum degree of G's Complement = %d\n", k - getMaxDegree(arr, k) - 1);
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

void sort(vertex* arr, int k) {
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