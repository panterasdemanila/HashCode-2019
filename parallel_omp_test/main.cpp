#include <iostream>
#include <list>
#include <set>
#include <chrono>
#include "Photo.h"
#include "io_operations.h"

#ifdef _OPENMP
# include <omp.h>
#endif

using namespace std;

int main() {

	#ifdef _OPENMP
		omp_lock_t lock;
		omp_init_lock(&lock);
	#endif

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
		percSup = 85; percInf = 15;

		while(!match){
			percSup = percSup + 5;
			percInf = percInf - 5;

			Photo photoRes = *itRe;


			#pragma omp parallel for
			for(int i=0; i < input.size(); i++){
				#ifdef _OPENMP
  					omp_set_lock(&lock);
				#endif
				auto itCo = next(input.begin(),i);
				Photo photoCom = *itCo;
				int percRes = photoRes.compareTags(photoCom);

				//cout << omp_get_num_threads() << endl;
				if(percInf <= percRes && percRes <= percSup && !match){

					numMatch--;
					result.emplace_back(photoCom);
					cout << input.size() << ", " << photoCom.id << endl;
					auto itComp = next(input.begin(),i);
					input.erase(itComp);
					i--;
					match=true;

				}
				#ifdef _OPENMP
					omp_unset_lock(&lock);
				#endif
			}
		}
		advance(itRe,1);
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
