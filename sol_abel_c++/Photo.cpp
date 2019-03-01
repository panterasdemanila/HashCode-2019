//
// Created by abel on 3/1/19.
//

#include "Photo.h"

unsigned int Photo::tags_number() const {
    return tags.size();
}

unsigned int count_intersection(const list<unsigned int> &tags1, const list<unsigned int> &tags2) {

    auto it1 = tags1.begin();
    auto it2 = tags2.begin();

    unsigned int count = 0;

    while (it1 != tags1.end() && it2 != tags2.end()) {
        if (*it1 < *it2)
            it1++;
        else if (*it2 < *it1)
            it2++;
        else /* equal */
        {
            ++count;
            it1++;
            it2++;
        }
    }

    return count;
}

unsigned int Photo::tags_in_common(const Photo &p) const{
    auto it1 = tags.begin();
    auto it2 = p.tags.begin();

    unsigned int common = 0;

    while (it1 != tags.end() && it2 != p.tags.end()) {
        if (*it1 < *it2) {
            it1++;
        } else if (*it2 < *it1) {
            it2++;
        } else /* equal */
        {
            ++common;
            it1++;
            it2++;
        }
    }

    return common;
}

unsigned int Photo::score(const Photo &p) const {
    unsigned int intersection = count_intersection(tags, p.tags);
    unsigned int min_not_selected = min(tags.size() - intersection, p.tags.size() - intersection);
    return min(min_not_selected, intersection);
}


Photo::Photo(unsigned int id, bool orientation, const list<unsigned int> &tags) : id(id), orientation(orientation),
                                                                                  tags(tags) {}

/*
 * Photo::Photo(Photo &ph1, Photo &ph2) : id(ph1.id * 100000 + ph2.id), orientation(ph1.orientation) {
    auto it1 = ph1.tags.begin();
    auto it2 = ph2.tags.begin();

    while (it1 != ph1.tags.end() && it2 != ph2.tags.end()) {
        if (*it1 < *it2) {
            tags.emplace_back(*it1);
            it1++;
        } else if (*it2 < *it1) {
            tags.emplace_back(*it1);
            it2++;
        } else
        {
            it1++;
            it2++;
        }
    }

    tags.sort();
 }
*/

Photo::Photo(Photo &ph1, Photo &ph2) : id(ph1.id * 100000 + ph2.id), orientation(ph1.orientation) {
    auto it1 = ph1.tags.begin();
    auto it2 = ph2.tags.begin();

    auto x = ph1.tags;
    auto y = ph2.tags;

    x.splice(x.begin(), y);

    tags = x;

    tags.sort();
}


pair<unsigned int, unsigned int> Photo::get_id_pair() const {
    return {id / 100000, id % 100000};
}

bool Photo::operator<(const Photo &rhs) const {
    return id < rhs.id;
}

bool Photo::operator>(const Photo &rhs) const {
    return rhs < *this;
}

bool Photo::operator<=(const Photo &rhs) const {
    return !(rhs < *this);
}

bool Photo::operator>=(const Photo &rhs) const {
    return !(*this < rhs);
}
