#include <iostream>
#include <list>
#include <set>
#include <chrono>
#include "Photo.h"
#include "io_operations.h"
#include <limits>

using namespace std;

int main() {

    auto start_time = chrono::steady_clock::now();

    cout << "Read input" << endl;
    list<Photo> input = read_input("./input/d_pet_pictures.txt");
    /* Algorithm */
    cout << "Executing algorithm" << endl;
    list<Photo> result;

    list<Photo> verticals_top;
    list<Photo> horizontals_top;

    list<Photo> verticals_result;

    for (auto &photo_act: input) {
        if (photo_act.orientation) {
            horizontals_top.emplace_back(photo_act);
        } else {
            verticals_top.emplace_back(photo_act);
        }
    }

    /**
    * Vertical algorithm
    */

    unsigned int divisions = 1;

    unsigned int partition_size = verticals_top.size() / divisions;

    auto verticals_iter = verticals_top.begin();

    for (int i = 0; i < divisions; ++i) {
        auto actual_iterator = verticals_iter;
        advance(verticals_iter, partition_size);

        set<Photo> verticals(actual_iterator, verticals_iter);
        while (!verticals.empty()) {
            auto actual_selection = *verticals.begin();
            verticals.erase(actual_selection);

            auto best_pair = actual_selection;
            int best_pair_score = -1;

            for (const auto &actual_pair : verticals) {
                auto tags_in_common = actual_selection.tags_in_common(actual_pair);
                int score = 1000000 - tags_in_common;
                if (best_pair_score < score) {
                    best_pair_score = score;
                    best_pair = actual_pair;
                }
            }

            if (best_pair_score != -1) {
                verticals_result.emplace_back(Photo(actual_selection, best_pair));
                verticals.erase(best_pair);
            }

            if (verticals.size() % 2048 == 0) {
                cout << i << " " << verticals.size() << endl;
            }
        }
    }


    // Merge results after vertical algorithm
    horizontals_top.splice(horizontals_top.begin(), verticals_result);

    /**
     * Horizontal algorithm
     */
    horizontals_top.sort([](const Photo &photo1, const Photo &photo2) {
        return photo1.tags_number() < photo2.tags_number();
    });

    divisions = 1;

    partition_size = horizontals_top.size() / divisions;

    auto input_iter = horizontals_top.begin();

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
    save_output("./output/d_pet_pictures.txt", result);

    auto end_time = chrono::steady_clock::now();

    cout << "Elapsed time in seconds : "
         << chrono::duration_cast<chrono::seconds>(end_time - start_time).count()
         << " sec";

    return 0;
}