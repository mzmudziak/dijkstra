//
// Created by Michal Zmudziak on 17/11/2018.
//

#include <iostream>
#include <random>
#include "Utils.h"

using namespace std;

void listVector(vector<int> arr) {
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
}

vector<int> indexedVector(int n) {
    vector<int> vec;
    vec.reserve(static_cast<unsigned long>(n));
    for (int i = 0; i < n; i++) {
        vec.push_back(i);
    }

    return vec;
}

vector<int> fisherYatesShuffle(vector<int> arr) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, INT32_MAX);

    int n = static_cast<int>(arr.size());
    for (int i = n - 1; i > 0; --i) {
        int r = uni(rng) % (i + 1);
        swap(arr[i], arr[r]);
    }
    return arr;
}

int random(int min, int max) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(min, max);
    return uni(rng);
}

vector<std::pair<int, int>> fisherYatesShuffle(vector<std::pair<int, int>> arr) {
    random(0, INT_MAX);

    int n = static_cast<int>(arr.size());
    for (int i = n - 1; i > 0; --i) {
        int r = random(0, INT_MAX) % (i + 1);
        swap(arr[i], arr[r]);
    }


    return arr;
}


