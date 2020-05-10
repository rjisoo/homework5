#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void bfs(string **, int, int);

int main(int argc, char * args[]) {
	ifstream inputFile;
	int verticiesSize = 0;
	int edgeSize = 0;

	string ** verticies;
	string user;

	inputFile.open(args[1]);

	// handle verticies
	inputFile >> verticiesSize;
	verticies = new string*[verticiesSize];
	for (int i = 0; i < verticiesSize + 1; i++) {
		verticies[i] = new string[verticiesSize+1];
	}
	for (int i = 0; i < verticiesSize; i++) {
		inputFile >> verticies[0][i];
	}

	// handle edges
	inputFile >> edgeSize;
	string verticie;
	string edge;
	int checkBreakout = 0;
	int countAddedEdge = 0;

	// iterate until check all edges
	while (checkBreakout != edgeSize) {
		inputFile >> verticie;
		inputFile >> edge;

		for (int i = 0; i < verticiesSize; i++) {
			// find columns
			if (verticie == verticies[0][i]) {
				for (int j = 0; j < verticiesSize; j++) {
					if (edge == verticies[0][j]) {
						verticies[j+1][i] = edge;
						verticies[i+1][j] = verticie;

						countAddedEdge = 1;
						checkBreakout++;
						break;
					}
				}

				// if edge is already checked, reset the value, and break the loop
				if (countAddedEdge == 1) {
					countAddedEdge--;
					break;
				}
			}
		}
	}

	bfs(verticies, verticiesSize, edgeSize);
	return 0;
}

// by using bfs, fill out babyfaces and heels array according to the rivarity status.
void bfs(string **verticies, int verticiesSize, int edgeSize) {
	bool viableSplit = true;

	// set babyfaces array
	string * babyface;
	babyface = new string[verticiesSize];

	// set heels array
	string * heels;
	heels = new string[verticiesSize];

	int countBabyfaces = 0;
	int countHeels = 0;

	if (edgeSize != (verticiesSize * 2)) {
		int i = 0;

		// check first two matches
		while (i != 2) {
			for (int j = 0; j < verticiesSize; j++) {
				// if verticies is empty, add according member
				if (verticies[j + 1][i] != "") {
					if (i == 0) {
						heels[j] = verticies[j + 1][i];
						countHeels++;
					} else {
						babyface[j] = verticies[j + 1][i];
						countBabyfaces++;
					}
				}
			}
			i++;
		}


		int z = 0;
		while (z != verticiesSize) {
			if (babyface[z] == heels[z]) {
				viableSplit = false;
			}
			z++;
		}
	} else {
		// otherwise, set viable to false
		viableSplit = false;
	}

	// print out
	if (viableSplit) {
		cout << "Yes" << endl << "Babyface: ";

		for (int i = 0; i < verticiesSize; i++) {
			cout << babyface[i] << " ";
		}

		cout << endl << "Heels:";

		for (int i = verticiesSize - 1; i > -1; i--) {
			cout << heels[i] << " ";
		}

		cout << endl;
	} else {
		cout << "No, if impossible" << endl;
	}
}