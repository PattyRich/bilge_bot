#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const int rows = 12;
const int cols = 6;
const int DEPTH = 5;

void printBoard(char * board[rows][cols]){
	cout << "\n";
	for(int i=0; i<rows; i++) {
	        for(int j=0; j<cols; j++) {
	                cout<<" "<<board[i][j]<<" ";
	        }
	        cout<<"\n";
	}
}

struct boardObj {
	bool broke;
	int best;
	char * board [rows][cols];
	vector<int> previous;
};

int evalBoard(char * board[rows][cols]){
	int total = 0;

	for(int j=0; j<cols; j++) {
		char * lastTile;
		int counter = 0;
	    for(int i=0; i<rows; i++) {
			if (strcmp(lastTile, board[i][j]) == 0 && i == rows-1){
				counter += 1;
				if (counter >= 3){
					if (total >= 4){
						total += 7;
					}
					else if (total >= 2){
						total +=4;
					}
					else {
						total +=2;	
					}
				}
			} else if (strcmp(lastTile, board[i][j]) == 0) {
				counter += 1;
			} else {
				if (counter >= 3){
					if (total >= 4){
						total += 7;
					}
					else if (total >= 2){
						total +=4;
					}
					else {
						total +=2;	
					}
				}
				counter = 1;
			}
	    	lastTile = board[i][j];
	    }
	}
	for(int i=0; i<rows; i++) {
		char * lastTile;
		int counter = 0;
	    for(int j=0; j<cols; j++) {
			if (strcmp(lastTile, board[i][j]) == 0 && j == cols-1){
				counter += 1;
				if (counter >= 3){
					if (total >= 4){
						total += 7;
					}
					else if (total >= 2){
						total +=4;
					}
					else {
						total +=2;	
					}
				}
			} else if (strcmp(lastTile, board[i][j]) == 0) {
				counter += 1;
			} else {
				if (counter >= 3){
					if (total >= 4){
						total += 7;
					}
					else if (total >= 2){
						total +=4;
					}
					else {
						total +=2;	
					}
				}
				counter = 1;
			}
	    	lastTile = board[i][j];
	    }
	}
	return total;
}

int main() {

	vector<boardObj> arr;

	boardObj obj = {
		.broke = false, 
		.best = 0,
		.board = {
			{ "1", "3", "2", "3" ,"1", "2"},
			{ "2", "1", "1", "6" ,"4", "2"},
			{ "6", "2", "1", "3" ,"2", "7"},
			{ "5", "1", "3", "7" ,"4", "4"},
			{ "7", "2", "4", "3" ,"3", "2"},
			{ "3", "4", "2", "1" ,"1", "5"},
			{ "7", "2", "6", "2" ,"7", "1"},
			{ "1", "4", "5", "5" ,"2", "6"},
			{ "4", "2", "2", "1" ,"1", "2"},
			{ "7", "5", "3", "6" ,"5", "1"},
			{ "7", "1", "5", "2" ,"1", "3"},
			{ "2", "7", "4", "7" ,"6", "3"},
		}
	};

    std::fstream myfile("data.txt", std::ios_base::in);

    vector<string> b;
    string a;

    while (myfile >> a)
    {
    	//cout << a;
    	b.push_back(a);
    }


    int count = 0;
	for(int i=0; i<rows; i++) {
	    for(int j=0; j<cols; j++) {
			char * writable = new char[b[count].size() + 1];
			std::copy(b[count].begin(), b[count].end(), writable);
			writable[b[count].size()] = '\0'; // don't forget the terminating 0
			obj.board[i][j] = writable;
			count++;
			// don't forget to free the string after finished using it
			//delete[] writable;
	    }
	}

	//printBoard(obj.board);

	arr.push_back(obj);

	int cnt = 0;
	for (int k = 0; k < DEPTH; k++){
		int size = arr.size();
		//this line is for some reason needed for -O1 to work properly???
		cout << size << " ";
		for (int x = cnt; x < size; x++){
			if (arr[x].broke) {
				continue;
			}
			
			int iSize = rows;
			int jSize = cols;
			int iSizeStart = 0;
			int jSizeStart = 1;
			int checkRange = 3;
			if (arr[x].previous.size()){
				if (arr[x].previous.size() > 4){
					checkRange = 2;
				}
				iSize = arr[x].previous[arr[x].previous.size()-2]+ checkRange;
				jSize = arr[x].previous[arr[x].previous.size()-1]+ checkRange;
				iSizeStart = iSize - checkRange*2;
				jSizeStart = jSize - checkRange*2;
			}
			if (iSize > rows){
				iSize = rows;
			}
			if (iSizeStart < 0){
				iSizeStart = 0;
			}
			if (jSize > cols){
				jSize = cols;
			}
			if (jSizeStart < 1){
				jSizeStart = 1;
			}

			for (int i = iSizeStart; i < iSize; i++){
				for (int j = jSizeStart; j< jSize; j++){
					boardObj obj;
					obj =  arr[x];
					char * boardCopy [rows][cols];
					memcpy(boardCopy, obj.board, sizeof (char *) * rows * cols);
					char * tmp = boardCopy[i][j-1];
					boardCopy[i][j-1] = boardCopy[i][j];
					boardCopy[i][j] = tmp;

					int points = evalBoard(boardCopy);
					if (points > 0) {
						obj.broke = true;
					} 

					obj.best += points;
					if (obj.previous.size()){
						obj.best -=1;
					}

					//1printBoard(boardCopy);

					//cout << i << " " << j << "\n";
					obj.previous.push_back(i);
					obj.previous.push_back(j-1);

					memcpy(&obj.board, boardCopy, sizeof(obj.board));
					//printBoard(obj.board);
					//cout << "\n previous: " << obj.previous [0] << obj.previous[1] << "\n";
					arr.push_back(obj);
				}
			}
		}
		cnt = size;
	}

	int max = 0;
	int index = 0;
	for (int i = 0; i < arr.size(); i ++) {
		if (arr[i].best > max){
			index = i;
			max = arr[i].best;
		}
	}

	cout << "\n" << "Best score: " << arr[index].best << "\n";
	// printBoard(arr[index].board);
	// for (int i = 0; i < arr[index].previous.size(); i+=2) {
	// 	cout << "[" << arr[index].previous[i] << "," << arr[index].previous[i+1] << "] \n";
	// }

	ofstream outFile("moves.txt");
    // the important part
    for (const auto &e : arr[index].previous) outFile << e << "\n";

	return 0;
}
