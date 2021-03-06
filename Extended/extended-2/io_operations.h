//
// Created by abel on 3/1/19.
//

#include "Photo.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#ifndef HASHCODE2019_IO_OPERATIONS_H
#define HASHCODE2019_IO_OPERATIONS_H

using namespace std;

set<Photo> read_input(const char path[]);

void save_output(const char path[], const list<Photo>& result );

#endif //HASHCODE2019_IO_OPERATIONS_H
