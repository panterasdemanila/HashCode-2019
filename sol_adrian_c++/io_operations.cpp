//
// Created by abel on 3/1/19.
//

#include "io_operations.h"

using namespace std;

set<Photo> read_input(const char path[]) {

	set<Photo> output;
    ifstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        unsigned int size_of_data;

        myfile >> size_of_data;

        map<string, unsigned int> tasks_map;

        unsigned long max_score = 0;

        for (unsigned int i = 0; i < size_of_data; i++) {
            set<unsigned int> tags;
            string orientation;
            int num_of_tags;
            myfile >> orientation >> num_of_tags;

            for (unsigned int j = 0; j < num_of_tags; j++) {
                string tag;
                myfile >> tag;
                auto search_key = tasks_map.find(tag);
                if (search_key == tasks_map.end()) {
                    auto task_map_size = tasks_map.size();
                    tasks_map.insert(pair<string, unsigned int>(tag, task_map_size));
                    tags.emplace(task_map_size);
                } else {
                    tags.emplace(search_key->second);
                }
            }

            max_score=+ tags.size() / 2;

            //tags.sort();
            output.emplace(Photo(i, orientation == "H", tags));
        }

        cout << "Different tags: " << tasks_map.size() << endl;
        cout << "Max score: " << max_score << endl;
    }
    myfile.close();

    return output;
}

void save_output(const char path[], const list<Photo> &result) {

    auto result_iterator = result.begin();

    unsigned int score = 0;

    ofstream myfile;
    myfile.open(path);

    if (myfile.is_open()) {

        Photo last_iterator = *result_iterator;

        myfile << result.size() << endl;

        while (result_iterator != result.end()) {
            const Photo actual = *result_iterator;
            score += last_iterator.score(actual);
            last_iterator = actual;

            myfile << result_iterator->id << endl;

            ++result_iterator;
        }
    }

    cout << "My score: " << score << endl;

    myfile.close();

}
