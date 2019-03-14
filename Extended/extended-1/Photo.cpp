#include "Photo.h"

unsigned int Photo::tags_number() const {
    return tags.size();
}

unsigned int count_intersection(const vector<unsigned int> &tags1, const vector<unsigned int> &tags2) {

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

unsigned int Photo::tags_in_common(const Photo &p) const {
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
                                                                                  tags(tags.begin(), tags.end()) {
    this->tags.shrink_to_fit();
}

Photo::Photo(Photo &ph1, Photo &ph2) : id(ph1.id * 100000 + ph2.id), orientation(ph1.orientation) {
    auto x = list<unsigned int>(ph1.tags.begin(), ph1.tags.end());
    auto y = list<unsigned int>(ph2.tags.begin(), ph2.tags.end());
    x.splice(x.begin(), y);
    x.sort();

    tags.resize(x.size());

    int i = 0;
    for (const auto &actual : x) {
        tags[i] = actual;
        i++;
    }

    tags.shrink_to_fit();
}

unsigned long Photo::heuristic_next(const Photo &p) const {

    unsigned int intersection = count_intersection(tags, p.tags);
    unsigned int min_not_selected = min(tags.size(), p.tags.size()) - intersection;
    unsigned long mm = min(min_not_selected, intersection);
    mm = (mm + 1) * 512 - (p.tags_number());
    return mm;
}

/*unsigned long Photo::heuristic_next(const Photo &p) const {
    unsigned int intersection = count_intersection(tags, p.tags);
    unsigned int min_not_selected = min(tags.size() - intersection, p.tags.size() - intersection);
    unsigned long mm = min(min_not_selected, intersection);
    mm = (mm + 1) * 1024 - 64 * intersection - (p.tags_number());
    return mm;
}*/

unsigned long Photo::heuristic_pair(const Photo &p, int media_tags) const {
    auto tags_in_common_number = tags_in_common(p);

    unsigned long score = (tags_in_common_number + 1) * 16384 + p.tags_number() +
                          1024 * abs((int) (media_tags - (p.tags_number() + tags_number())));
    score = 268435456 - score;
    return score;
}


pair<unsigned long, unsigned long> Photo::get_id_pair() const {
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

bool Photo::operator==(const Photo &rhs) const {
    return id == rhs.id;
}

