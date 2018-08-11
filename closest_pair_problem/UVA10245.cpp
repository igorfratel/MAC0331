#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <climits>
using namespace std;

double dist(const pair<int, int> &a, const pair<int, int> &b) {
    return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

vector<int> divideSort(vector<int> indirectSortByY, const int begin, const int end) {
    int N = end - begin + 1;
    int middle = floor ((begin + end)/2);
    vector<int> newIndirectSort(N);
    int j = middle + 1;
    for(int i = begin; i <= end; i++) {
        if(i <= middle) newIndirectSort[i] = indirectSortByY[i];
        else newIndirectSort[j++] = indirectSortByY[i];
    }
    return newIndirectSort;
}

vector<int> candidates(const vector<pair<int, int> > &points, vector<int> indirectSortByY, int begin, int end, double distance) {
    int middle = floor((begin + end)/2);
    vector<int> candidatesVector;
    for(int i = begin; i <= end; i++) {
        if(abs(points[indirectSortByY[i]].first - points[middle].first) < distance)
            candidatesVector.push_back(indirectSortByY[i]);
    }
    return candidatesVector;
}

double combine(const vector<pair<int, int> > &points, vector<int> indirectSortByY, int begin, int end, double left, double right) {
   double distance = min(left, right);
   vector<int> candidatesVector = candidates(points, indirectSortByY, begin, end, distance);
   for(int i = 0; i < candidatesVector.size() - 1; i++) {
        int j = i+1;
        while(j < candidatesVector.size() && points[candidatesVector[j]].second - points[candidatesVector[i]].second < distance) {
            if(dist(points[candidatesVector[j]], points[candidatesVector[i]]) < distance)
                distance = dist(points[candidatesVector[j]], points[candidatesVector[i]]);
            j++;
        }
   }
   return distance;
}

double closestPairDistance(const vector<pair<int, int> > &points, vector<int> indirectSortByY, int begin, int end) {
    if (end <= begin + 2)
        return dist(points[begin], points[end]);
    else {
        int middle = floor((begin + end)/2);
        vector<int> newIndirectSort = divideSort(indirectSortByY, begin, end);
        double left = closestPairDistance(points, newIndirectSort, begin, middle + 1);
        double right = closestPairDistance(points, newIndirectSort, middle + 1, end);
        return combine(points, indirectSortByY, begin, end, left, right);

    }
}


int main() {
    int N, x, y;
    double result;
    while(scanf("%d", &N) == 1 && N) {
        vector<pair<int, int> > points(N);
        vector<int> indirectSortByY(N);
        for(int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            points[i] = make_pair(x,y);
        }
        sort(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b){return a.first < b.first;});
        for(int i = 0; i < N; i++) indirectSortByY[i] = i;
        sort(indirectSortByY.begin(), indirectSortByY.end(), [&](int a, int b){return points[a].second < points[b].second;});
        result = closestPairDistance(points, indirectSortByY, 0, N-1);
        if(result > 10000.0) printf("INFINITY\n"); 
        else printf("%.4f\n", result);
    }
    return 0;
}
