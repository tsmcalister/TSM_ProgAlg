#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <mpi.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////
// Prototypes
void shellsort();
void puzzleTest(int maxSynchStates);

//////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	srand((unsigned int)time(nullptr));

	if (argc >= 2) {
		try {
			const char command = argv[1][0];

			MPI_Init(&argc, &argv);

			switch (command) {
			case 'P':
			{
				const int maxSynchStates = stoi(argv[2]);
				if (maxSynchStates <= 0) throw out_of_range("maxSynchStates has to be a positive integer value");
				puzzleTest(maxSynchStates);
				break;
			}
			case 'S':
				shellsort();
				break;
			}

			MPI_Finalize();
		} catch (logic_error& ex) {
			cerr << ex.what() << endl;
		}
	} else {
		cerr << "Usage: Exercise6_MPI P maxSynchStates" << endl;
		cerr << "Usage: Exercise6_MPI S" << endl;
	}

	return 0;
}