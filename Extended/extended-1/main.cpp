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
    list<Photo> input = read_input("./input/e_shiny_selfies.txt");

    /* Algorithm */
    cout << "Executing algorithm" << endl;
    list<Photo> result;

    list<Photo> verticals_top;
    list<Photo> horizontals_top;

    list<Photo> verticals_result;

    /**
     * Select only part of the input
     * TODO: Remove this part on produce
     */
    auto data_to_use = 20000;
    auto last_input = input.begin();
    advance(last_input, data_to_use);
    input = list<Photo>(input.begin(), last_input);

    /**
    * End of select input size
    */

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

    long media_tags = 0;

    for (auto &actual_tag : verticals_top) {
        media_tags += actual_tag.tags_number();
    }

    if (!verticals_top.empty())
        media_tags = (media_tags / verticals_top.size()) * 2;

    set<Photo> verticals(verticals_top.begin(), verticals_top.end());

    while (!verticals.empty()) {
        auto actual_selection = *verticals.begin();
        verticals.erase(actual_selection);

        auto best_pair = actual_selection;
        long best_pair_score = -1;

        for (const auto &actual_pair : verticals) {
            long score = actual_selection.heuristic_pair(actual_pair, media_tags);

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
            cout << verticals.size() << endl;
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

    set<Photo> horizontals(horizontals_top.begin(), horizontals_top.end());

    auto last_photo = *horizontals.begin();
    result.emplace_back(last_photo);
    horizontals.erase(horizontals.begin());

    while (!horizontals.empty()) {
        auto best = horizontals.begin();
        long best_score = -1;

        for (auto internal = horizontals.begin(); internal != horizontals.end(); internal++) {
            long mm = last_photo.heuristic_next(*internal);
            if (best_score < mm) {
                best = internal;
                best_score = mm;
            }
        }

        last_photo = *best;
        horizontals.erase(best);
        result.emplace_back(last_photo);

        if (horizontals.size() % 2048 == 0) {
            cout << horizontals.size() << endl;
        }
    }

    /* Output */
    cout << "Writing output" << endl;
    save_output("./output/e_shiny_selfies.txt", result);

    auto end_time = chrono::steady_clock::now();

    cout << "Elapsed time in seconds : "
         << chrono::duration_cast<chrono::seconds>(end_time - start_time).count()
         << " sec";

    return 0;
}