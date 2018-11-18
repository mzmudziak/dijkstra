//
// Created by Michal Zmudziak on 17/11/2018.
//

#ifndef DJIKSTRA_UTILS_H
#define DJIKSTRA_UTILS_H

#include <vector>

using std::vector;


vector<int> indexedVector(int n);

void listVector(vector<int> arr);

vector<int> fisherYatesShuffle(vector<int> n);
vector<std::pair<int, int>> fisherYatesShuffle(vector<std::pair<int, int>> n);

int random(int min, int max);


#endif //DJIKSTRA_UTILS_H
