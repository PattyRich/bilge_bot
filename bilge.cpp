#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>


using namespace std;

const int rows = 12;
const int cols = 6;
const int DEPTH = 7;

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
	int predict;
};

struct retStruct {
	int predict;
	int total;
};


bool comparePredict(const boardObj &a, const boardObj &b) {
	// if (a.previous.size() != b.previous.size()){
	// 	return a.best > b.best;
 	return a.predict > b.predict;
}

bool compareAbs(const boardObj &a, const boardObj &b) {
	return abs(a.best) > abs(b.best);
	// if (a.previous.size() != b.previous.size()){
	// 	return a.best > b.best;
	// }
 //    return a.predict > b.predict;
}

retStruct evalBoard(char * board[rows][cols], int ii, int jj, int iSizeStart, int iSize, int jSizeStart, int jSize, int prevSize, vector<int> previous){
	int total = 0;

	int predict = 0;

	int checkRange = 2;
 
 	// if (prevSize >= 2){
 	// 	ii = previous[0];
 	// 	jj = previous[1];
 	// }


 	int tally1 = 0;
 	int tally2 = 0;
 	int tally3 = 0;
 	int tally4 = 0;
 	int tally5 = 0;
 	int tally6 = 0;
 	int tally7 = 0;

	iSize = ii + checkRange;
	jSize = jj + checkRange;
	iSizeStart = iSize - checkRange*2;
	jSizeStart = jSize - checkRange*2;

	if (iSize > rows){
		iSize = rows;
	}
	if (iSizeStart < 0){
		iSizeStart = 0;
	}
	if (jSize > cols){
		jSize = cols;
	}
	if (jSizeStart < 0){
		jSizeStart = 0;
	}

	for(int i=iSizeStart; i<iSize; i++) {
		for(int j=jSizeStart; j<jSize; j++) {
		 	if (strcmp(board[i][j], "1") == 0){
		 		tally1 ++;
		 	}
		 	if (strcmp(board[i][j], "2") == 0){
		 		tally2 ++;
		 	}
		 	if (strcmp(board[i][j], "3") == 0){
		 		tally3 ++;
		 	}
		 	if (strcmp(board[i][j], "4") == 0){
		 		tally4 ++;
		 	}
		 	if (strcmp(board[i][j], "5") == 0){
		 		tally5 ++;
		 	}
		 	if (strcmp(board[i][j], "6") == 0){
		 		tally6 ++;
		 	}
		 	if (strcmp(board[i][j], "7") == 0){
		 		tally7 ++;
		 	}
	    	// if (strcmp(board[ii][jj], board[i][j]) == 0){
	    	// 	predict +=1;
	    	// }
	    	// if (strcmp(board[ii][jj-1], board[i][j]) == 0){
	    	// 	predict +=1;
	    	// }    
	    }
	}


 	vector<int> v;
 	v.push_back(tally1);
  	v.push_back(tally2);
 	v.push_back(tally3);
 	v.push_back(tally4);
 	v.push_back(tally5);
 	v.push_back(tally6);
 	v.push_back(tally7);

 	sort(v.begin(), v.end());

 	predict += v[v.size()-1];
 	predict += v[v.size()-2];

	for(int j=0; j<cols; j++) {
		char * lastTile = "f";
		int counter = 0;
	    for(int i=0; i<rows; i++) {
	    	// cout << "\n" << "lastTile: " << board[i][j] <<flush;
	    	// cout << "\n" << "I: " << i  << " J: " << j << " tile: " << lastTile << flush;
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
		char * lastTile = "f";
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

	retStruct r = {
		.total = total,
		.predict = predict	
	};

	// if (total == 13){
	// 	cout << "ii: " << ii << " jj: " << jj << " predict: " << predict << "\n";
	// 	printBoard(board);
	// 	for (int i =0; i<v.size(); i++){
	// 		cout << v[i] << " ";
	// 	}
	// 	cout << " \n";
	// 	for(int i=iSizeStart; i<iSize; i++) {
	// 		for(int j=jSizeStart; j<jSize; j++) {
	// 			cout << board[i][j];
	// 		}
	// 	}
	// }

	return r;
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
		},
		.predict = 0
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

	boardObj keep = {
		.best = -DEPTH
	};


	for (int k = 0; k < DEPTH; k++){
		int size = arr.size();

		cout << size << " ";
		for (int x = 0; x < size; x++){
			if (arr[x].broke) {
				continue;
			}
			if (arr[x].previous.size() != k * 2){
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
					if (arr[x].previous.size()){
						if (i == arr[x].previous[arr[x].previous.size()-2] && j-1 == arr[x].previous[arr[x].previous.size()-1]){
							continue;
						}
					}
					if (strcmp(arr[x].board[i][j], arr[x].board[i][j-1]) == 0){
			    		continue;
			    	}

					boardObj obj;
					obj =  arr[x];
					char * boardCopy [rows][cols];
					memcpy(boardCopy, obj.board, sizeof (char *) * rows * cols);
					


					char * tmp = boardCopy[i][j-1];
					boardCopy[i][j-1] = boardCopy[i][j];
					boardCopy[i][j] = tmp;

					retStruct ret = evalBoard(boardCopy, i, j, iSizeStart, iSize, jSizeStart, jSize, obj.previous.size(), obj.previous);
					int points = ret.total;
					obj.predict = ret.predict;
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
		sort(arr.begin(), arr.end(), compareAbs);
		if (size > 40){
			arr.resize(arr.size() * 0.65);
		}
		// for (int i = 0; i < arr.size(); i ++) {
		// 	cout << "best: " << arr[i].best << " predict: " << arr[i].predict << " \n";
		// }
		sort(arr.begin(), arr.end(), comparePredict);
		if (size > 40){
			arr.resize(arr.size() * 0.65);
		}
		for (int i = 0; i < arr.size(); i ++) {
			if (keep.best < arr[i].best) {
				keep = arr[i];
				cout << arr[i].best;
			}
		}

		// for (int i = 0; i < arr.size(); i ++) {
		// 	// if (arr[i].best < arr[0].best &&  arr[i].best > 0){ 
		// 	// 	arr.erase(arr.begin()+i);
		// 	// 	i--;
		// 	// 	continue;
		// 	// }
		// 	// if (arr[i].best < arr[0].best && arr[i].previous.size() < k * 2 + 2 ){
		// 	// 	//cout << arr[i].previous.size() << k * 2 << " e ";
		// 	// 	arr.erase(arr.begin()+i);
		// 	// 	i--;
		// 	// }
		// }


		// cout <<"arr[0].predict: " <<arr[0].predict <<  " arr[0].best: " << arr[0].best << "\n";
		// printBoard(arr[0].board);
	}

	// for (int i = 0; i < arr.size(); i ++) {
	// 	//cout << arr[i].previous.size() << " " << arr[i].best << " \n";
	// }

	// for (int i = arr.size(); i >= 0; i --) {
	// 	cout <<"pred: " << arr[i].predict << " " << arr[i].best << " ";
	// }

	// printBoard(arr[0].board);
	// cout << arr[0].predict;

	// for (int i = 0; i < arr[0].previous.size(); i+=2) {
	// 	cout << "[" << arr[0].previous[i] << "," << arr[0].previous[i+1] << "] \n";
	// }

	// int max = 0;
	// int index = 0;
	// for (int i = 0; i < arr.size(); i ++) {
	// 	if (arr[i].best > max){
	// 		index = i;
	// 		max = arr[i].best;
	// 	}
	// }

	// if (keep.best < arr[index].best) {
	// 	keep = arr[index];
	// }
	// cout << index;
	cout << "\n" << "Best score: " << keep.best << "\n";

	// printBoard(arr[index].board);
	// cout << "predict: " << arr[index].predict << " ";

	// // printBoard(arr[index].board);
	// for (int i = 0; i < arr[index].previous.size(); i+=2) {
	// 	cout << "[" << arr[index].previous[i] << "," << arr[index].previous[i+1] << "] \n";
	// }

	ofstream outFile("moves.txt");
    // the important part
    for (const auto &e : keep.previous) outFile << e << "\n";

	return 0;
}
