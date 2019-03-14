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
	set<Photo> input = read_input("/Users/adrian/Downloads/E-SC++/b_lovely_landscapes.txt");
	/* Algorithm */
	cout << "Executing algorithm" << endl;
	list<Photo> result;

	// sort(input.begin(), input.end(), less_than_key());

	int iter=0;
	bool match;

	int numMatch = input.size()-1;
	int percSup, percInf;

	result.emplace_back(*input.begin());
	input.erase(input.begin());

	auto itRe = result.begin();

	// iter < result.size()
	while(itRe!=result.end() && numMatch>0){
		match = false;
		percSup = 94; percInf = 6;

		while(!match){
			percSup = percSup + 5;
			percInf = percInf - 5;

			Photo photoRes = *itRe;

			for (auto &itCo : input){
				Photo photoCom = itCo;
				int percRes = photoRes.compareTags(photoCom);

				if(percInf <= percRes && percRes <= percSup){
					numMatch--;
					result.emplace_back(photoCom);
					cout << input.size() << ", " << photoCom.id << endl;
					input.erase(itCo);
					match=true;
					break;
				}
			}
		}
		itRe++;
	}

	/* Output */
	cout << "Writing output" << endl;
	save_output("/Users/adrian/Downloads/E-SC++/b_lovely_landscapes.out", result);

	auto end_time = chrono::steady_clock::now();

	cout << "Elapsed time in seconds : "
		 << chrono::duration_cast<chrono::seconds>(end_time - start_time).count()
		 << " sec";

	return 0;
}
