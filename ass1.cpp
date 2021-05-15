/*
Assignment 1
Name: Peter Qian
Student ID: lhq036
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


int insert(int node, int start, int end);
int visit(int node);
int compare(int node, int poolStart, int poolEnd);
bool compareWord(char arr[], int node);
int rotate_right(int k2);
int rotate_left(int k2);
int double_right(int k3);
int double_left(int k3);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void printArray(int A[], int size);
void printLastTen(int A[], int size);

struct text{
	int start;
	int end;
	int count;
	int left;
	int right;
	int height;
	
};

char pool[500000];
char tempWord[100] = {0};												// temp word start null		

const int dataSize = 50000;			
text word[dataSize];
int sorted[dataSize];

int comparePointer; 													//Pointer to increment node 
int indexPointer;
int sortPointer;
bool wordDupCheck;


int main(){
	
	string fileName;
	cerr << "Enter FileName: " << endl;
    cin >> fileName;
	//fileName = "sample.txt";
	
	ifstream inFile;
    inFile.open(fileName);
	
	if(!inFile.good()){
		cerr << "Error with fileName \n";
        exit(1);
    }
	
	char c;
	bool inWord, startWord, endWord;
	int wordPointer, startPointer, endPointer, poolPointer;
	int length = 0;
	int counting;
	int wordsCount;
	int root = -1;
	
	while(!inFile.eof()){
		
		inFile.get(c);
		
		if(isspace(c) || inFile.eof())
		{ // Is a space

			if(endPointer != wordPointer) // Compare the previous value to current value
			{	
				//First print the temp word - Check to see if correct
				// Check if word already exists in pool 
				wordDupCheck = compareWord(tempWord, root);
				if(!wordDupCheck){
					// If word doesn't already exist, put word into BST and pool
					endPointer = wordPointer-1;
					//cout <<"Insert with start pointer: " << startPointer << " end pointer: " << endPointer << endl; //Debug
					strcat(pool, tempWord);					// Next input the word into the pool array
					root = insert(root, startPointer, endPointer);
					
				} else {
					// If word already exists, increase counter
					//cout << "word already exists???" << endl;
					//cout << "compare Pointer in the reading main " << comparePointer << endl;
					word[comparePointer].count++;
					//de-increment wordPointer by length of tempWord
					wordPointer = wordPointer - strlen(tempWord);
					
				}
				
				for (int i = 0; i < 15; i++){tempWord[i] = 0; }
				length = 0;
			}
		} 
		else 
		{ // if it isn't a space then we start putting the word into the array
		
			//if (!ispunct(c)) //isn't punctuation
			if(isalpha(c))
			{
				
				if(length == 0)	// we're now counting the word
				{
					startPointer = wordPointer;
				}	
				wordPointer++;								//increment the wordPointer
				
				tempWord[length++] = (char) tolower(c); 	//temporary word to store
				
			}
		}
	}
	
	// Debugging statements
	
	//cout << "POOL" << endl;
	/*
	for (int i = 0; i < wordPointer+1; i++)
	{
		//cout << i << " = " << pool[i] << ", ";				//Debugging Statement
		cout << pool[i];
	}
	*/
	//cout << endl;
	
	// Debugging for loop
	/*
	cout << "arrays" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << "index: " << i;
		cout << " start: " << word[i].start << " pool start " << pool[word[i].start] << " pool end " << pool[word[i].end];
		cout << " end: " << word[i].end;
		cout << " left: " <<  word[i].left; 
		cout << " right: " <<  word[i].right;
		cout << " count: " << word[i].count;
		//cout << " height: " << word[i].height << endl;				
		cout << endl;
	}
	cout << endl;
	*/
	//cout << "visit in-order traversal" << endl;
	visit(0);
	//cout << "sort pointer" << sortPointer << endl;
	//cout << "Sorted Array Alphabetically" << endl;
	//printArray(sorted, 10);
	
	mergeSort(sorted, 0, sortPointer-1);
	
	cout << "The first 10 words are" << endl;
	printArray(sorted, 10);
	
	cout << "The Last 10 Words in the List are:" << endl;
	
	printLastTen(sorted, sortPointer);
	
	inFile.close();
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////



int compare(int node, int poolStart, int poolEnd){
	
	int poolPointer = poolStart;
	int wordAPointer = word[node].start;
	
	char poolA[20]= {0}; 
	char wordB[20] = {0};
	
	for (int i = 0; i <= (poolEnd-poolStart);i++){
		poolA[i] = pool[poolPointer++];
	}
	
	for (int i = 0; i <= (word[node].end-word[node].start);i++){
		wordB[i] = pool[wordAPointer++];
	}
	
	if(strcmp(poolA, wordB) == 0){return 0;	}
	
}

bool compareWord(char arr[], int node){
	if ( node == -1) return false;		// At root
	
	//Grab the word from the current node
	int wordPointer = word[node].start;
	char wordB[20] = {0};
	
	//cout << "compareWord Function" << endl;
	
	//cout << "arry read from pool: ";						//Debug
	/*
	for (int i = 0; i <= 20 ;i++){
		cout << arr[i];
	}
	*/
	//cout << endl;
	//cout << " \t word that exist in BST: ";				//Debug
	for (int i = 0; i <= (word[node].end-word[node].start);i++){
		wordB[i] = pool[wordPointer++];
		//cout << wordB[i];
	}
	
	//cout << "word[node].left: " << word[node].left << "\t" << " word[node].right: " <<  word[node].right << endl;
	if(word[node].left == -1 && word[node].right == -1){
		//cout << "when at the bottom node w/o l and r: " << strcmp(arr, wordB) << endl;
		
		if( strcmp(arr, wordB) != 0) { 
			//cout << "Not zero and at bottom node return false" << endl; 
			return false; 
		}
		
		if( strcmp(arr, wordB) == 0) { 
			//cout << "Zero and at bottom node return true" << endl; 
			//cout << "node for compare pointer: " << comparePointer << endl;
			comparePointer = node;
			
			return true; 
		}
	} else {
	
		if(strcmp(arr, wordB) == 0){
			//cout << "strcmp is equal at first if: " << strcmp(arr, wordB) << endl;
			//cout << "node for compare pointer: " << comparePointer << endl;
			comparePointer = node;
			return true;	
		}
	}
	
	if (strcmp(arr, wordB) < 0) {
		//cout << "l:  " << strcmp(arr, wordB) << endl;
		compareWord(arr, word[node].left);
	} else if (strcmp(arr, wordB) > 0) {
		//cout << "r:  " << strcmp(arr, wordB) << endl;
		compareWord(arr, word[node].right);
	}
	
}

int insert(int node, int start, int end){
	
	
	if(node == -1){
		word[indexPointer].start = start;
		word[indexPointer].end =  end;
		word[indexPointer].left = -1;
		word[indexPointer].right = -1;
		word[indexPointer].count++;
		word[indexPointer].height = 0;
		
		return indexPointer++;
	} 
	
	//cout << "node: " << node << " start: " << start << " end: " << end << endl;		//Debug
	//cout << pool[start] << "\t" << pool[end] << endl;									//Debug
	//cout << pool[word[node].start] << "\t" << pool[word[node].end] << endl;			//Debug
	
	// Need to compare words before all of this...
	// First check if the word exists already
	if(start >= end) {return node;}
	
	int temp = 0;
	//compare(node,start, end);
	temp = compare(node,start, end);
	//cout << "TEMP HAS BEEN INITIALIZED TO : " << temp << endl;

	if(temp < 0)
	{
		//cout << "less than" << endl;															//Debug
		//cout << "node: " << node << " start: " << start << " end: " << end << endl;			//Debug
		//cout << pool[start] << "\t" << pool[word[node].start] <<  endl;						//Debug
		//cout << pool[end] << "\t" << pool[word[node].end] <<  endl;							//Debug
		word[node].left = insert(word[node].left, start, end);
		
		// AVL Function
		int ld = word[word[node].left].height;
		int rd; 
		
		// Check if left pointer is not null
		if(word[node].right != -1){
			rd = word[word[node].right].height;
		} else {
			rd = -1;
		}
		
		//cout << "CHECK IF LEFT HEAVY \nNODE: " << node <<  "\t LEFT NODE HEIGHT: " << ld << "\t RIGHT NODE HEIGHT: " << rd << endl;
		
		//If the balance if left heavy
		// Couldn't be implmeneted properly
		/*
		if (ld - rd == 2){

			if (value < word[word[node].left].contents){ 
				return rotate_right(node);											//Case 1
			}  else {	
				return double_right(node);											//Case 2
			}
		} else {
			cout << "NOT INBALANCED\n" << endl;
		}
		*/
	} 
	//else if ( pool[start] > pool[word[node].start])	// if the value is greater than node pointing to value
	else if(temp > 0)
	{
		//cout << "greater than" << endl;														//Debug
		//cout << "node: " << node << " start: " << start << " end: " << end << endl;			//Debug
		//cout << pool[start] << "\t" << pool[word[node].start] <<  endl;						//Debug
		//cout << pool[end] << "\t" << pool[word[node].end] <<  endl;							//Debug
		word[node].right = insert(word[node].right, start, end);
		
		int ld;
		int rd = word[word[node].right].height; 
		
		// Check if left pointer is not null
		if(word[node].left != -1){
			ld = word[word[node].left].height;
		} else {
			ld = -1;
		}
		/*
		cout << "CHECK IF RIGHT HEAVY\nNODE: " << node << "\t RIGHT NODE HEIGHT: " << rd << "\t LEFT NODE HEIGHT: " << ld <<endl;
		
		//If the balance if right heavy
		// Couldn't be implmeneted properly
		if (rd - ld == 2){
			
			if (value < word[word[node].right].contents){ 	
				return double_left(node);											//Case 3
			} else {
				return rotate_left(node);											//Case 4
			}		
		}	else {
			cout << "NOT INBALANCED\n" << endl;
		}
		*/
	}
	
	//cout << "Process node: " << node << endl;
	
	//AVL Height adjustment code line below
	//word[node].height = max( word[word[node].left].height, word[word[node].right].height ) + 1;
	
	return node;

}

// K1 and K2 switch positions however this function couldn't be fully implemented
int rotate_right(int k2){
	
	// K2 is root node
	// K1 is left child
	cout << "\nROTATE_RIGHT" << endl;

	int k1 = word[k2].left;
	word[k2].left = word[k1].right;
		
	//cout << "kl is node: " << k1 << "\tk2 is node: " << k2 << endl;	
	
	word[k1].right = k2;
																			//Rotation
	//k1 becomes top of tree and k2 goes down
	//Height Update
	//word[k2].height = max( word[word[k2].left].height, word[word[k2].right].height)+1;				//height update
	word[k2].height = max( word[word[k2].left].height, word[word[k2].right].height) +1;
	word[k1].height = max( word[word[k1].left].height, word[k2].height) +1;							//height update
	
	//cout <<"\nheight check after updating height word[k2].height: " << word[k2].height << " word[k1].height: " << word[k1].height << "\n" << endl;
	
	return k1;
	
}

// K1 and K2 switch positions however this function couldn't be fully implemented
int rotate_left(int k2){
	
	//cout << "\nROTATE_LEFT" << endl;

	int k1 = word[k2].right;
	word[k2].right = word[k1].left;

	//cout << "kl is node: " << k1 << "\tk2 is node: " << k2 << endl;														// Debug
	
	word[k1].left = k2;																					//Rotation
	
	//Height Update
	word[k2].height = max( word[word[k2].left].height, word[word[k2].right].height);
	word[k1].height = max( word[k2].height, word[word[k1].right].height)+1;

	//cout <<"\nheight check after updating height word[k2].height: " << word[k2].height << " word[k1].height: " << word[k1].height << "\n" << endl;
	
	return k1;
	
}

int double_right(int k3){

	//cout << "\nDOUBLE_RIGHT" << endl;
	word[k3].left = rotate_left(word[k3].left);
	k3 = rotate_right(k3);
	return k3;
	
}

int double_left(int k3){

	//cout << "\nDOUBLE_LEFT" << endl;
	word[k3].right =rotate_right(word[k3].right);
	k3 = rotate_left(k3);
	return k3;
	
}

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
	
	//cout << "n1: " << n1 << " n2: " << n2 << endl;																	//Debug
    /* create temp arrays */
    int L[n1], R[n2]; 
	
    /* Copy data to temp arrays L[] and R[] */
	//cout << "copying data\n L: " << endl;
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i]; 
		//cout << "L["<< i << "]: " << L[i] << " ";																		//Debug
	}
	
	//cout << "copying data\n R: " << endl;
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j]; 
		//cout << "R["<< j << "]: " << R[j] << " ";																		//Debug
	}
	//cout << endl;
	
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; j = 0; k = l; 
    while (i < n1 && j < n2) { 

		if ( word[L[i]].count >= word[R[j]].count){
            arr[k] = L[i]; 
            i++;
			
        } else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
	//cout <<"i: " <<  i << ", " << n1 << endl;						//Debug
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
	//cout <<"j: " <<  j << ", " << n2 << endl;						//Debug
    while (j < n2) { 
		//cout << R[j] << "\t";										//Debug
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(int arr[], int l, int r){ 
	
    if (l < r) { 
        int m = l + (r - l) / 2; 
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
        merge(arr, l, m, r); 
    } 
	
}

void printArray(int A[], int size) { 

	for(int i = 0; i < size; i++){
		
		
		//cout << "i: " << i << endl;
		for(int j = word[sorted[i]].start; j <= word[sorted[i]].end; j++){
			cout << pool[j];
		}
		
		
		cout << " count: " << word[sorted[i]].count;
		cout << endl;
		
		
	}
}

void printLastTen(int A[], int size) { 

	for(int i =(size-10) ; i < size; i++){
		for(int j = word[sorted[i]].start; j <= word[sorted[i]].end; j++){
			
			cout << pool[j];
		}
		
		cout << " count: " << word[sorted[i]].count;
		cout << endl;
	}
}

int visit(int node){
	//cout << "(";																	//Debug
	
	if (word[node].left != -1)
		visit(word[node].left);
	
	//cout << "node " << node;														//Debug
	//cout << " start: " << word[node].start << " end: " << word[node].end;			//Debug
	//cout << pool[word[node].start] <<  ", " << pool[word[node].end];				//Debug
	sorted[sortPointer++] = node;
	
	if (word[node].right != -1)
		visit(word[node].right);
	//cout << ")";																	//Debug
	
	return node;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////



