// C++ program to implement Quick convexSet algorithm
// to find convexSet in 2-d space.
#include <bits/stdc++.h>
using namespace std;

// xy_pair is integer pairs
#define xy_pair pair<int, int>

// Stores the result (points of convex hull)
set<xy_pair> convexSet;

// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(xy_pair p1, xy_pair p2, xy_pair p)
{
    int distance = (p.second - p1.second) * (p2.first - p1.first) -
                   (p2.second - p1.second) * (p.first - p1.first);

    if (distance > 0)
        return 1;
    if (distance < 0)
        return -1;
    return 0;
}

// returns points_array value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDistance(xy_pair p1, xy_pair p2, xy_pair p)
{
    return abs((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2. side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(xy_pair points_array[], int pairCount, xy_pair p1, xy_pair p2, int side)
{
    int index = -1;
    int max_distance = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i = 0; i < pairCount; i++)
    {
        int temp = lineDistance(p1, p2, points_array[i]);
        if (findSide(p1, p2, points_array[i]) == side && temp > max_distance)
        {
            index = i;
            max_distance = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex convexSet.
    if (index == -1)
    {
        convexSet.insert(p1);
        convexSet.insert(p2);
        return;
    }

    // Recur for the two parts divided by points_array[index] just like in Quick Sort
    quickHull(points_array, pairCount, points_array[index], p1, -findSide(points_array[index], p1, p2));
    quickHull(points_array, pairCount, points_array[index], p2, -findSide(points_array[index], p2, p1));
}

void ConvexPolygonVertices(xy_pair points_array[], int pairCount)
{
    // points_array[i].second -> y-coordinate of the ith point
    if (pairCount < 3)
    {
        cout << "No possible Convex polygon ";
        return;
    }

    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i = 1; i < pairCount; i++)
    {
        if (points_array[i].first < points_array[min_x].first)
            min_x = i;
        if (points_array[i].first > points_array[max_x].first)
            max_x = i;
    }

    // Recursively find convex convexSet points on
    // one side of line joining points_array[min_x] and
    // points_array[max_x]
    quickHull(points_array, pairCount, points_array[min_x], points_array[max_x], 1);

    //  find convex convexSet points on
    // other side of line joining points_array[min_x] and
    // points_array[max_x] using recursion
    quickHull(points_array, pairCount, points_array[min_x], points_array[max_x], -1);

    cout << "Vertices of Convex Polygon: ";
    while (!convexSet.empty())
    {
        cout << "(" << (*convexSet.begin()).first << ", "
             << (*convexSet.begin()).second << ") ";
        convexSet.erase(convexSet.begin());
    }
}

// Driver code
int main()
{

    int pairCount; //number of input pairs
    cin >> pairCount;
    xy_pair points_array[pairCount]; //initiliazing an array of pairs
    for (int i = 0; i < pairCount; i++)
    {
        cin >> points_array[i].first;  //input x co-ordinate of ith pair
        cin >> points_array[i].second; //input y co-ordinate of ith pair
    }

    ConvexPolygonVertices(points_array, pairCount);
    return 0;
}
