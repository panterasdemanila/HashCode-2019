#include "io_operations.h"

using namespace std;

list<Photo> read_input(const char path[]) {
    list<Photo> output;
    ifstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        unsigned int size_of_data;

        myfile >> size_of_data;

        map<string, unsigned int> tasks_map;

        for (unsigned int i = 0; i < size_of_data; i++) {
            list<unsigned int> tags;
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
                    tags.emplace_back(task_map_size);
                } else {
                    tags.emplace_back(search_key->second);
                }
            }

            tags.sort();
            output.emplace_back(Photo(i, orientation == "H", tags));
        }

        cout << "Different tags: " << tasks_map.size() << endl;
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

            if (result_iterator->orientation)
                myfile << result_iterator->id << endl;
            else {
                auto to_save = result_iterator->get_id_pair();
                myfile << to_save.first << " " << to_save.second << endl;
            }
            ++result_iterator;
        }
    }

    cout << "My score: " << score << endl;

    myfile.close();

}