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
    list<Photo> input = read_input("/Users/adrian/Downloads/E-S/b_lovely_landscapes.txt");
    /* Algorithm */
    cout << "Executing algorithm" << endl;
    list<Photo> result;

    input.sort([](const Photo &photo1, const Photo &photo2) {
        return photo1.tags_number() < photo2.tags_number();
    });

		int iter=0;
	    bool match;

	    int numMatch = input.size();
	    int percSup, percInf;
	    result.emplace_back(input.front());
	    input.pop_front();


		auto itRe = result.begin();

	    while(iter < result.size() && numMatch>0){
	        match = false;
	        percSup = 98; percInf = 2;

	        while(!match){
	            percSup = percSup + 1;
	            percInf = percInf - 1;

	            Photo photoRes = *itRe;
	            auto itIn = input.begin();

	            for(int index = 0; index < input.size() && !match; index++){
	                Photo photoCom = *itIn;
	                int percRes = photoRes.compareTags(photoCom);
	                if(percInf <= percRes && percRes <= percSup){
	                    numMatch--;
	                    result.emplace_back(photoCom);
	                    input.erase(itIn);
	                    match=true;
	                    cout << input.size() << endl;
	                }else{
						advance(itIn, 1);
					}
	            }
	        }
			advance(itRe, 1);
			iter++;
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
