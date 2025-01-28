// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Gia Berekashvili

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    theArray.resize(numObjects, -1);
}

//recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    if (theArray[objectIndex]<0)
    {
        return objectIndex;
    }
    else
    {
        return theArray[objectIndex] = find(theArray[objectIndex]);
    }
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{
    int root1 = find(objIndex1);
    int root2 = find(objIndex2);

    if (root1 == root2)
    {
        return false;
    }
    else
    {
        if (theArray[root1] > theArray[root2])
        {
            theArray[root2] += theArray[root1];
            theArray[root1] = root2;
        }
        else
        {
            theArray[root1] += theArray[root2];
            theArray[root2] = root1;
        }   
    }
    
    return (theArray[root1] == -numValues || theArray[root2] == -numValues); 
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
