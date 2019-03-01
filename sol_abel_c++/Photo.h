#include <list>
#include <string>
#include <algorithm>

//
// Created by abel on 3/1/19.
//

#ifndef HASHCODE2019_PHOTO_H
#define HASHCODE2019_PHOTO_H

using namespace std;

class Photo {
public:
    unsigned long id;
    bool orientation; // TRUE -> H, FALSE -> V : If is vertical can contain 1 or 2 photos
    list<unsigned int> tags;

    Photo(unsigned int id, bool orientation, const list<unsigned int> &tags);

    // Generate one vertical photo from 2 vertical
    Photo(Photo& ph1,  Photo& ph2);

    pair<unsigned int, unsigned int> get_id_pair() const;

    unsigned int tags_number() const;

    unsigned int score(const Photo &p) const;

    unsigned int tags_in_common(const Photo &p) const;

    bool operator<(const Photo &rhs) const;

    bool operator>(const Photo &rhs) const;

    bool operator<=(const Photo &rhs) const;

    bool operator>=(const Photo &rhs) const;

};


#endif //HASHCODE2019_PHOTO_H
