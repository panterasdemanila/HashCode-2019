#include <iostream>
#include <list>
#include <set>
#include <chrono>
#include "Photo.h"
#include "io_operations.h"

using namespace std;

int main() {

    auto start_time = chrono::steady_clock::now();

    cout << "Read input" << endl;
    list<Photo> input = read_input("./input/b_lovely_landscapes.txt");
    /* Algorithm */
    cout << "Executing algorithm" << endl;
    list<Photo> result;

    input.sort([](const Photo &photo1, const Photo &photo2) {
        return photo1.tags_number() < photo2.tags_number();
    });

    unsigned int divisions = 4;

    unsigned int partition_size = input.size() / divisions;

    auto input_iter = input.begin();

    auto last_photo = *input_iter;

    for (int i = 0; i < divisions; ++i) {
        auto actual_iterator = input_iter;
        advance(input_iter, partition_size);
        set<Photo> horizontals(actual_iterator, input_iter);
        horizontals.erase(last_photo);

        while (!horizontals.empty()) {
            Photo best = last_photo;
            int best_score = -1;
            for (auto const &internal : horizontals) {
                int mm = last_photo.score(internal);
                if (best_score < mm) {
                    best = internal;
                    best_score = mm;
                }
            }
            last_photo = best;
            horizontals.erase(last_photo);
            result.emplace_back(last_photo);

            if (horizontals.size() % 2048 == 0) {
                cout << i << " " << horizontals.size() << endl;
            }
        }


    }

    /* Output */
    cout << "Writing output" << endl;
    save_output("./output/b_lovely_landscapes.txt", result);

    auto end_time = chrono::steady_clock::now();

    cout << "Elapsed time in seconds : "
         << chrono::duration_cast<chrono::seconds>(end_time - start_time).count()
         << " sec";

    return 0;
}