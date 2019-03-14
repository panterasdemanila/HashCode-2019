#include <list>
#include <string>
#include <algorithm>
#include <set>



//
// Created by abel on 3/1/19.
//

#ifndef HASHCODE2019_PHOTO_H
#define HASHCODE2019_PHOTO_H

using namespace std;

class Photo {
public:
    unsigned int id;
    bool orientation; // TRUE -> H, FALSE -> V
    set<unsigned int> tags;



    Photo(unsigned int id, bool orientation, const set<unsigned int> &tags);

    unsigned int tags_number() const;

    unsigned int score(const Photo &p) const;

	int compareTags(const Photo& p);

    bool operator<(const Photo &rhs) const;

    bool operator>(const Photo &rhs) const;

    bool operator<=(const Photo &rhs) const;

    bool operator>=(const Photo &rhs) const;

};

#endif //HASHCODE2019_PHOTO_H
