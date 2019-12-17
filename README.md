# Greedy Coloring algorithm for Interval Graph

## General
- This project was made as a part of my B.Sc at Computer Science at graph's teory course.
- The project was written in C, and is investigating a few properities of Interval graphs by diving it all to functions.

## Functions and possabilites
- Main struct of the program represents each vertex in the graph, vertex's properties are: (i.e. vertex = [3,5]
    1. Start (int)
    2. End (int)
    3. colorID (int)
    4. Degree (int)

- printVertexes - This function is getting an array of vertexes and it's size and prints the vertexes in the order the user inputed them.
- setDegree - This function is getting an array of vertexes and it's size, and setting the degree for each vertex based on a check if 2 vertexes are neighbors.
- sort - This function is sorting the array of vertexes by its start index, from the lower to the higher.
### Getters:
- getMaxDegree - This function is getting an array of vertexes and its size, and will return an integer of the maximum degree in the array.
- getMinDegree - This function is getting an array of vertexes and its size, and will return an integer of the minimum degree in the array.
- getSumDegree - This function is getting an array of vertexes and its size, and will sum up all the degrees.

## Setting up a graph:
To set up a graph you'll have to input a number of how many intervals you'll want to insert, after that you'll have to insert each interval.
i.e: If you want to insert 4 intervals, then iput 4, and if you want to set up interval [3.5] insert it as '3 5'.

## License
Feel free to use, change and do whatever you want with this code.
