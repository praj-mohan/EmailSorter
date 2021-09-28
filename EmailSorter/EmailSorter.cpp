#include "svm.h"
#include "svm.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define Malloc(type,n) (type *)malloc((n)*sizeof(type)) //defines Malloc
using namespace std;

struct svm_parameter param; //Consists of data to be transferred for training and testing
struct svm_problem training;
struct svm_model* model;
struct svm_node* x_space;


int main() {
	// creates the stream objects for opening and writing files
	ifstream in;
	ofstream printout;

	string st; // string is used for reading file
	string choice; // used to ask user whether if they want to read and create the dictionary files
	string choice2;// used to ask user whether if they want to train and test the data
	string cursor; // used to parse through all the files in the dataset
	vector<string> data; //used to store the dictionary
	vector<int> counter; //used to store the location of frequency counters for the dictionary words
	int filecursor; //used to store current location of file
	int filestopper; //used to store last file location

	//asks the user whether if they want to read and create the dictionary files
	cout << "Type yes for reading, otherwise type any character and press enter." << endl;
	cin >> choice;
	if (choice == "yes") {
		//sets first and last file locations for the stopper and cursor
		filestopper = 481;
		filecursor = 1;

		//runs until the cursor reaches the end of the list
		while (filecursor != filestopper) {
			//cursor stores the directory of the current file
			cursor = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\nonspam (";
			cursor += to_string(filecursor);
			cursor += ").txt";

			//opens the file
			in.open(cursor);

			//skips the subject line and reaches the content of the email
			getline(in, st);
			getline(in, st);
			getline(in, st);

			int stopper = 0; //creates stopper
			while (stopper == 0) {
				int size = st.length(); //stores length of string
				int countingline = 0; //creates a counter for parsing through string
				string word; //this will be where the word is stored
				int wordsize = 0;
				while (countingline != size) { //while loop runs until end of string
					if (st.at(countingline) < 48 || (st.at(countingline) > 57 && st.at(countingline) < 65) || (st.at(countingline) > 90 && st.at(countingline) < 97) || st.at(countingline) > 122) { //checks if the cursor has reach the end of the word
						if (wordsize != 0) { //checks if the word is not an empty space
							int duplicatecheck = 0;
							for (int i = 0; i < data.size(); i++) { //parses the dictionary to see if the word is already there
								if (word == data.at(i)) { //checks if the current location in the dictionary is equal to the word
									duplicatecheck = 1; //sets the duplicate check to true
								}
							}
							if (duplicatecheck == 0) { // checks if duplicate check is false
								data.push_back(word); //pushes the word into dictionary
								counter.push_back(0); //adds a corresponding frequency counter
							}
							word = ""; //resets the word string
							wordsize = 0; //resets word size
						}
					}
					else {
						word += st.at(countingline); //adds the next letter into the word
						wordsize++; //increases the wordsize

					}
					countingline++; //parses to the next character
				}
				stopper = 1; //stops the loop

			}
			in.close(); //closes the file
			filecursor++; //goes to the next file
		}

		//resets the stopper/cursor
		filestopper = 481;
		filecursor = 1;

		//runs until the cursor reaches the end of the list
		while (filecursor != filestopper) {
			//cursor stores the directory of the current file
			cursor = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\spam (";
			cursor += to_string(filecursor);
			cursor += ").txt";

			//opens the file
			in.open(cursor);

			//skips the subject line and reaches the content of the email
			getline(in, st);
			getline(in, st);
			getline(in, st);

			int stopper = 0; //creates stopper
			while (stopper == 0) {
				int size = st.length(); //stores length of string
				int countingline = 0; //creates a counter for parsing through string
				string word; //this will be where the word is stored
				int wordsize = 0;
				while (countingline != size) { //while loop runs until end of string
					if (st.at(countingline) < 48 || (st.at(countingline) > 57 && st.at(countingline) < 65) || (st.at(countingline) > 90 && st.at(countingline) < 97) || st.at(countingline) > 122) { //checks if the cursor has reach the end of the word
						if (wordsize != 0) { //checks if the word is not an empty space
							int duplicatecheck = 0;
							for (int i = 0; i < data.size(); i++) { //parses the dictionary to see if the word is already there
								if (word == data.at(i)) { //checks if the current location in the dictionary is equal to the word
									duplicatecheck = 1; //sets the duplicate check to true
								}
							}
							if (duplicatecheck == 0) { // checks if duplicate check is false
								data.push_back(word); //pushes the word into dictionary
								counter.push_back(0); //adds a corresponding frequency counter
							}
							word = ""; //resets the word string
							wordsize = 0; //resets word size
						}
					}
					else {
						word += st.at(countingline); //adds the next letter into the word
						wordsize++; //increases the wordsize

					}
					countingline++; //parses to the next character
				}
				stopper = 1; //stops the loop

			}
			in.close(); //closes the file
			filecursor++; //goes to the next file
		}

		cursor = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\dictionary.txt"; //sets cursor to dictionary.txt file.
		printout.open(cursor); //opens the dictionary.txt file
		for (int i = 0; i < data.size(); i++) { //writes all of the words from the data set into the file
			printout << data.at(i) << endl;
		}
		printout.close(); //closes the file

			//resets the cursor and stopper
		filestopper = 481;
		filecursor = 1;

		//runs until the cursor reaches the end of the list
		while (filecursor != filestopper) {
			vector<int> frequency = counter; //used to count the frequency for each word in the current file

			//cursor stores the directory of the current file
			cursor = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\nonspam (";
			cursor += to_string(filecursor);
			cursor += ").txt";

			in.open(cursor); 		//opens the file

			//skips the subject line and reaches the content of the email
			getline(in, st);
			getline(in, st);
			getline(in, st);

			int stopper = 0; //creates stopper
			while (stopper == 0) {
				int size = st.length(); //stores length of string
				int countingline = 0; //creates a counter for parsing through string
				string word; //this will be where the word is stored
				int wordsize = 0;
				while (countingline != size) { //while loop runs until end of string
					if (st.at(countingline) < 48 || (st.at(countingline) > 57 && st.at(countingline) < 65) || (st.at(countingline) > 90 && st.at(countingline) < 97) || st.at(countingline) > 122) { //checks if the cursor has reach the end of the word
						if (wordsize != 0) {  //checks if the word is not an empty space
							for (int i = 0; i < data.size(); i++) { //parses the dictionary to see if the word is already there
								if (word == data.at(i)) { //checks if the current location in the dictionary is equal to the word

									//increments the counter
									int increment = frequency.at(i) + 1;
									frequency.at(i) = increment;
								}
							}
							word = ""; //resets the word string
							wordsize = 0; //resets word size
						}
					}
					else {
						word += st.at(countingline); //adds the next letter into the word
						wordsize++; //increases the wordsize

					}
					countingline++; //parses to the next character
				}
				stopper = 1; //stops the loop

			}
			in.close();  //closes the file

			//points to the corresponding frequency file
			string freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\nonspamfrequency (";
			freqfile += to_string(filecursor);
			freqfile += ").txt";

			//opens the file
			printout.open(freqfile);

			//stores the counters into the frequency file
			for (int i = 0; i < frequency.size(); i++) {
				printout << frequency.at(i) << endl;
			}
			printout.close(); //closes the file
			filecursor++; // increments the cursor
		}

		//resets the cursor and stopper
		filestopper = 481;
		filecursor = 1;

		//runs until the cursor reaches the end of the list
		while (filecursor != filestopper) {
			vector<int> frequency = counter; //used to count the frequency for each word in the current file

			//cursor stores the directory of the current file
			cursor = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\spam (";
			cursor += to_string(filecursor);
			cursor += ").txt";

			in.open(cursor); 		//opens the file

			//skips the subject line and reaches the content of the email
			getline(in, st);
			getline(in, st);
			getline(in, st);

			int stopper = 0; //creates stopper
			while (stopper == 0) {
				int size = st.length(); //stores length of string
				int countingline = 0; //creates a counter for parsing through string
				string word; //this will be where the word is stored
				int wordsize = 0;
				while (countingline != size) { //while loop runs until end of string
					if (st.at(countingline) < 48 || (st.at(countingline) > 57 && st.at(countingline) < 65) || (st.at(countingline) > 90 && st.at(countingline) < 97) || st.at(countingline) > 122) { //checks if the cursor has reach the end of the word
						if (wordsize != 0) {  //checks if the word is not an empty space
							for (int i = 0; i < data.size(); i++) { //parses the dictionary to see if the word is already there
								if (word == data.at(i)) { //checks if the current location in the dictionary is equal to the word

									//increments the counter
									int increment = frequency.at(i) + 1;
									frequency.at(i) = increment;
								}
							}
							word = ""; //resets the word string
							wordsize = 0; //resets word size
						}
					}
					else {
						word += st.at(countingline); //adds the next letter into the word
						wordsize++; //increases the wordsize

					}
					countingline++; //parses to the next character
				}
				stopper = 1; //stops the loop

			}
			in.close();  //closes the file

			//points to the corresponding frequency file
			string freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\spamfrequency (";
			freqfile += to_string(filecursor);
			freqfile += ").txt";

			//opens the file
			printout.open(freqfile);

			//stores the counters into the frequency file
			for (int i = 0; i < frequency.size(); i++) {
				printout << frequency.at(i) << endl;
			}
			printout.close(); //closes the file
			filecursor++; // increments the cursor
		}

	}

	//asks if the user is ready to start training and testing the data
	cout << "Ready to start? Type yes" << endl;
	cin >> choice2;

	//checks if the user said yes
	if (choice2 == "yes") {

		//used to store input, model, and error messsages
		char input_file_name[1024];
		char model_file_name[1024];
		const char* error_msg;

		//parameters for the SVM (based off of LIBSVM's README)
		param.svm_type = C_SVC;
		param.kernel_type = 0;
		param.degree = 1;
		param.gamma = 0.2;
		param.coef0 = 0;
		param.nu = 0.5;
		param.cache_size = 300;
		param.C = 1;
		param.eps = 1e-3;
		param.p = 0.1;
		param.shrinking = 1;
		param.probability = 0;
		param.nr_weight = 0;
		param.weight_label = NULL;
		param.weight = NULL;

		//stores the training data size into the training struct
		training.l = 768;

		// creates a 2d array using the training data size and number of words in dictionary
		auto matrix = new double[768][23961];

		for (int i = 0; i < 768; i++) {
			string freqfile; // stores location of the frequency file
			if (i < 384) {
				//gets the location of a nonspam frequency file if at the first part of the loop
				freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\nonspamfrequency (";
				freqfile += to_string(i + 1);
				freqfile += ").txt";
			}
			else {
				//gets the location of a spam frequency file if at the second part of the loop
				freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\spamfrequency (";
				freqfile += to_string(i - 383);
				freqfile += ").txt";
			}
			in.open(freqfile); // opens the file
			for (int j = 0; j < 23961; j++) {
				getline(in, st); //gets the counter
				double storage = stoi(st); //converts count into int and stores it
				matrix[i][j] = storage; // stores it into the array
			}
			in.close(); // closes the file
		}
		svm_node** x = Malloc(svm_node*, training.l); //Mallocs the svm_node with training data set size

		for (int i = 0; i < 768; i++) {
			svm_node* x_space = Malloc(svm_node, 23962); //mallocs the node with the number of words in the dictionary
			for (int j = 0; j < 23961; j++) {
				x_space[j].index = j; //stores the index of the counter
				x_space[j].value = matrix[i][j]; //stores counter into value 
			}
			x_space[23961].index = -1; //ends the index with -1
			x[i] = x_space; //stores it into the svm_node
		}
		delete[] matrix; //deletes the array


		training.x = x; //stores the node into training


		training.y = Malloc(double, training.l); //Mallocs the label with training data set size
		for (int i = 0; i < 384; i++) {
			training.y[i] = 1; //gives the label of 1 to nonspam folders
		}
		for (int i = 384; i < 768; i++) {
			training.y[i] = 2;//gives the label of 1 to spam folders
		}

		int accuracy = 0; //creates an accuracy counter
		int testsize = 192; //stores the size of test data

		svm_model* model = svm_train(&training, &param); //trains the SVM

		for (int i = 385; i < 481; i++) {
			svm_node* testnode = new svm_node[23961]; //creates a node with the number of words in the dictionary

			//gets the location of a nonspam frequency file
			string freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\nonspamfrequency (";
			freqfile += to_string(i);
			freqfile += ").txt";

			//opens the file
			in.open(freqfile);

			//passes the indexes and counters into the test node
			for (int j = 0; j < 23961; j++) {
				getline(in, st);
				testnode[j].index = j;
				testnode[j].value = stoi(st);
			}
			//ends the node with -1
			testnode[23961].index = -1;
			in.close(); //closes the file
			//asks the SVM to predict the file
			double retval = svm_predict(model, testnode);
			if (retval == 1) { //checks if the prediction is correct and updates the counter accordingly
				accuracy++;
			}
		}

		for (int i = 385; i < 481; i++) {
			svm_node* testnode = new svm_node[23961]; //creates a node with the number of words in the dictionary

			//gets the location of a nonspam frequency file
			string freqfile = "C:\\Users\\mohan_home\\source\\repos\\EmailSorter\\spamfrequency (";
			freqfile += to_string(i);
			freqfile += ").txt";

			//opens the file
			in.open(freqfile);

			//passes the indexes and counters into the test node
			for (int j = 0; j < 23961; j++) {
				getline(in, st);
				testnode[j].index = j;
				testnode[j].value = stoi(st);
			}
			//ends the node with -1
			testnode[23961].index = -1;
			in.close(); //closes the file
			//asks the SVM to predict the file
			double retval = svm_predict(model, testnode);
			if (retval == 2) { //checks if the prediction is correct and updates the counter accordingly
				accuracy++;
			}
		}


		//prints the accuracy of the result
		cout << "result: " << accuracy << "/" << testsize << endl;

		//destroys the parameter and frees the data space
		svm_destroy_param(&param);
		free(training.y);
		free(training.x);
		free(x_space);

		return 0;


	}
	else { //prints an exit statement
		cout << "Exiting Program" << endl;
	}
}

