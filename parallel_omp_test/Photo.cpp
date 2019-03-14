//
// Created by abel on 3/1/19.
//

#include "Photo.h"

unsigned int Photo::tags_number() const {
    return tags.size();
}

unsigned int count_intersection(const set<unsigned int> &tags1, const set<unsigned int> &tags2) {

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

unsigned int Photo::score(const Photo &p) const {
    unsigned int intersection = count_intersection(tags, p.tags);
    unsigned int min_not_selected = min(tags.size() - intersection, p.tags.size() - intersection);
    return min(min_not_selected, intersection);
}

int Photo::compareTags(const Photo& p) {
	int equalTags = 0;
	if(p.tags.size()<this->tags.size()){
		for (unsigned int tag : p.tags) {
			if(this->tags.find(tag)!= this->tags.end()){
				equalTags = equalTags + 1;
			}
		}
	}else{
		for (unsigned int tag : this->tags) {
			if(p.tags.find(tag)!= p.tags.end()){
				equalTags = equalTags + 1;
			}
		}
	}
	
	int totalTags = this->tags.size() + p.tags.size();
	return (int)((double)equalTags/totalTags * 100);
}


Photo::Photo(unsigned int id, bool orientation, const set<unsigned int> &tags) : id(id), orientation(orientation),
                                                                            tags(tags) {}

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
