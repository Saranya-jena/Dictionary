#include<bits/stdc++.h>
using namespace std;

//Dictionary class
class Dictionary {
public:
	unordered_map<string, string>mp; //Member variable to store the dictionary

	//Member function to read the data from the backup file
	void ReadData() {
		fstream f("Backup.txt"); //Read data
		if (!f.is_open()) {
			cout << "Backup file does not exist, please add a word" << '\n';

		}
		string str;
		int ind = 0;
		vector<string>w(3);
		while (getline(f, str)) {
			char *token = strtok(const_cast<char*>(str.c_str()), ":");
			while (token != NULL) {

				w[ind++] = token;
				token = strtok(nullptr, ":");
			}
			transform(w[0].begin(), w[0].end(), w[0].begin(), ::tolower);
			mp[w[0]] = w[1]; //The data from dictionary is stored in the map
			ind = 0;
		}
	}

    //Member function to insert a new word and its meaning into the dictionary and backup file
	void insertWord(string word, string meaning) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		//Condition to check whether the input word already exists in the dictionary or not
		if (mp.count(word) == 1) {
			cout << endl << "Word is already in the dictionary" << endl;
			return;
		}

		//If not, the word and its meaning is inserted into the dictionary and backup file
		mp[word] = meaning;
		string str = "\n" + word + ":" + meaning;
		ofstream f;
		f.open("Backup.txt", std::ios_base::app); //To write the word into file
		f << str;
		f.close();
		cout << endl << "Word is added to the dictionary" << endl;
	}

	//Member function to search the meaning of a given word
	void SearchWord(string word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		//Condition to check whether the word exists in the dictionary or not
		if (mp.count(word) == 0) {
			cout << endl << "Word is not in the dictionary" << endl;
		}
		else {
			cout << endl << "Meaning of " << word << " : " << mp[word] << endl;
		}

	}

	//Member function to update the meaning of a given word
	void updateWord(string word, string meaning) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (mp.count(word) == 0) {
			insertWord(word, meaning);
			return;
		}
		mp[word] = meaning;
		Write();
	}

	//Member function to delete a given word
	void deleteWord(string word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (mp.count(word) == 0) {
			cout << endl << "Word is not in the dictionary" << endl;
			return;
		}
		mp.erase(word);
		Write();
	}

	//Member function to update words in the backup file
	void Write() {
		ofstream f;
		string str = "";
		f.open("Backup.txt");
		for (auto i : mp) {
			str += i.first + ":" + i.second + "\n";
		}
		f << str;
		f.close();
	}

	//Member function to print the complete dictionary
	void displayAll() {
		for (auto i : mp) {
			cout << i.first << " : " << i.second << endl;
		}
	}
};

    //Function to print the menu
    void printMenu() {
        cout << endl << "----------------------------" << endl << endl;
        cout << "\tMenu\t" << endl;
        cout << "1. Insert a word in the Dictionary" << endl;
        cout << "2. Search a word from the Dictionary" << endl;
        cout << "3. Update the meaning of the word" << endl;
        cout << "4. Delete the word and its meaning from the Dictionary" << endl;
        cout << "5. Display Dictionary" << endl;
        cout << "6. Exit" << endl;
        cout << endl << "----------------------------" << endl ;
    }

int main() {
	Dictionary dict; //Dictionary object
	dict.ReadData();
	string ch; int choice;
	string word, meaning;
	while (1) {
		printMenu(); //Displays the menu
		cout << "Enter your choice : " ;
		cin >> choice;

		//Condition to check whether the entered choice is a valid integer or not
		while(cin.fail()) {
        cout << "Error! please enter a valid integer" << std::endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
        }

        //Different cases to handle user's query
		switch (choice) {
		case 1:
			cout << "Enter the word and its meaning	: " ;
			cin >> word;
			getline(cin, meaning);
			dict.insertWord(word, meaning);
			break;
		case 2:
			cout << "Enter the word for which meaning is to be searched : ";
			cin >> word;
			dict.SearchWord(word);
			break;
		case 3:
			cout << "Enter the word and its meaning	: " ;
			cin >> word;
			getline(cin, meaning);
			dict.updateWord(word, meaning);
			break;
		case 4:
			cout << "Enter the word to be deleted : ";
			cin >> word;
			dict.deleteWord(word);
			break;
		case 5:
			dict.displayAll();
			break;
		case 6:
			cout << "-----------Exiting----------" << endl;
			exit(0);
			break;
		default:
			cout << "Wrong choice! please enter a valid one" << endl;
			break;
		}
	}
	return 0;
}
