#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <conio.h>
using namespace std;

string fileName;
int allIDs = 0;
int currentUser;
string correctChoice;

class Quiz {
private:
	int _correctAmount;
	int _wrongAmount;
	int _score;
public:
	void setScore(int score) {
		_score = score;
	}
	void setCorrect(int correctAmount) {
		_correctAmount = correctAmount;
	}
	void setWrong(int wrongAmount) {
		_wrongAmount = wrongAmount;
	}
	int getScore() {
		return _score;
	}

	int getCorrectAmount() {
		return _correctAmount;
	}
	int getWrongAmount() {
		return _wrongAmount;
	}
	vector <string> correctAnswers;
	vector <string> rightSelections;
	vector <string> inputsByUser;
	vector <int> sequences;
};

class Question {
protected:
	string _question;
	string _correctAnswer;
	string temp;
	int numOfLines = 0;
	int _ID;
	int count = 1;
public:
	string getQuestion() {
		return _question;
	}
	int getID() {
		return _ID;
	}
	string getAnswer() {
		return _correctAnswer;
	}

	bool operator == (Question& question) {
		string quest1 = this->_question;
		string quest2 = question.getQuestion();
		if (quest1 == quest2) {
			return true;
		}
		else {
			return false;
		}
	}
};

class MultipleChoiceQuestions : public Question {
private:
	string _secondChoice;
	string _thirdChoice;
	string _fourthChoice;
public:
	MultipleChoiceQuestions(int ID) {
		_ID = ID;
	}
	string getRandomChoices(int cases) {
		switch (cases) {
		case 1:
			return _correctAnswer;
			break;
		case 2:
			return _secondChoice;
			break;
		case 3:
			return _thirdChoice;
			break;
		case 4:
			return _fourthChoice;
			break;
		}
	}
	void setQuestion(string question) {
		_question = question;
	}
	void setAnswer(string answer) {
		_correctAnswer = answer;
	}
	void setSecondChoice(string secondChoice) {
		_secondChoice = secondChoice;
	}
	void setThirdChoice(string thirdChoice) {
		_thirdChoice = thirdChoice;
	}
	void setFourthChoice(string fourthChoice) {
		_fourthChoice = fourthChoice;
	}

	bool readQuestions(string fileName, int line) {
		ifstream questionFile;
		questionFile.open(fileName.c_str());
		while (getline(questionFile, temp)) {
			if (count >= line) {
				switch (numOfLines) {
				case 1:
					_question = temp;
					break;
				case 2:
					_correctAnswer = temp;
					break;
				case 3:
					_secondChoice = temp;
					break;
				case 4:
					_thirdChoice = temp;
					break;
				case 5:
					_fourthChoice = temp;
					break;
				}
				numOfLines++;
			}
			if (numOfLines == 6) {
				break;
			}
			count++;
		}
		return true;
	}

};

class User {
protected:
	string _userName;
	string _password;
	string _firstName;
	string _lastName;
	string _position;
public:
	string getUsername() {
		return _userName;
	}
	string getPassword() {
		return _password;
	}
	string getFirstname() {
		return _firstName;
	}
	string getLastname() {
		return _lastName;
	}
	void setFirstname(string firstName) {
		_firstName = firstName;
	}
	void setLastname(string lastName) {
		_lastName = lastName;
	}
	void setPassword(string password) {
		_password = password;
	}

	bool operator == (User& otherUser) {
		string user1 = this->_userName;
		string user2 = otherUser.getUsername();
		if (user1 == user2) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Admin : public User {
public:
	Admin(string userName, string password, string firstName, string lastName) {
		setUserName(userName);
		setPassword(password);
		setFirstName(firstName);
		setLastName(lastName);
		setPosition();
	}
	void setUserName(string userName) {
		_userName = userName;
	}
	void setPassword(string password) {
		_password = password;
	}
	void setFirstName(string firstName) {
		_firstName = firstName;
	}
	void setLastName(string lastName) {
		_lastName = lastName;
	}
	void setPosition() {
		_position = "admin";
	}
};

class Player : public User {
public:
	vector <Quiz> quizzes;

	Player(string userName, string password, string firstName, string lastName) {
		setUserName(userName);
		setPassword(password);
		setFirstName(firstName);
		setLastName(lastName);
		setPosition();

	}
	void setUserName(string userName) {
		_userName = userName;
	}
	void setPassword(string password) {
		_password = password;
	}
	void setFirstName(string firstName) {
		_firstName = firstName;
	}
	void setLastName(string lastName) {
		_lastName = lastName;
	}
	void setPosition() {
		_position = "player";
	}
	void addQuiz(Quiz quiz) {
		quizzes.push_back(quiz);
	}
	int getAmoutOfQuiz() {
		return quizzes.size();
	}
};

vector <MultipleChoiceQuestions> allQuestions;
vector <Admin> allAdmins;
vector <Player> allPlayers;

void existingQuestions() {
	string name, label;
	int line = 1;
	char choice;
	bool isOkay;
	int lineForWrite = 1;
	ifstream questionFile;
	questionFile.open(fileName.c_str());

	if (questionFile.fail()) {
		do {
			system("CLS");

			cout << endl << "Enter the name of the file: ";
			cin >> name;
			fileName = name + ".txt";
			questionFile.open(fileName.c_str());
			if (questionFile.fail()) {
				isOkay = true;
			}
			break;

		} while (isOkay == true);
	}

	while (getline(questionFile, label)) {
		if (line == lineForWrite) {
			if (label == "Question") {
				lineForWrite += 6;
				allIDs++;
				MultipleChoiceQuestions newQuestions(allIDs);
				if (newQuestions.readQuestions(fileName, line)) {
					allQuestions.push_back(newQuestions);
				}
			}
		}
		line++;
	}
	questionFile.close();
}

char displayQuestions(int index, bool game) {
	bool done, choices[4];
	int num, character = 97;
	char answer;

	cout << allQuestions[index].getQuestion() << endl;
	done = false;
	for (int x = 0; x < 4; x++) {
		choices[x] = false;
	}
	while (done == false) {
		num = rand() % 4 + 1;
		if (choices[num - 1] == false) {
			if (num == 1) {
				if (game == false) { cout << "*"; }
				answer = (char)character;
				correctChoice = allQuestions[index].getRandomChoices(num);
			}
			cout << "[" << (char)character << "] ";
			cout << allQuestions[index].getRandomChoices(num);
			cout << "   ";
			choices[num - 1] = true;
			character++;
		}
		for (int j = 0; j < 4; j++) {
			done = true;
			if (choices[j] == false) {
				done = false;
				break;
			}
		}
	}
	cout << endl << endl;

	return answer;
}


void addQuestion() {
	string question, answer, secondChoice, thirdChoice, fourthChoice;
	cout << endl << "Enter the question: ";
	cin.ignore();
	getline(cin, question);

	cout << "Enter the correct variant: ";
	getline(cin, answer);
	cout << "Second variant: ";
	getline(cin, secondChoice);
	cout << "Third variant: ";
	getline(cin, thirdChoice);
	cout << "Fourth variant: ";
	getline(cin, fourthChoice);
	allIDs++;
	MultipleChoiceQuestions newQuestions(allIDs);
	newQuestions.setQuestion(question);
	newQuestions.setAnswer(answer);
	newQuestions.setSecondChoice(secondChoice);
	newQuestions.setThirdChoice(thirdChoice);
	newQuestions.setFourthChoice(fourthChoice);
	allQuestions.push_back(newQuestions);


	system("pause");
	system("CLS");
}


void newQuiz() {
	if (allQuestions.size() >= 5) {
		Quiz newQuiz;
		char ans, correctAnswer;
		string answer;
		int num = 1, randIndex, correctAmount = 0, wrongAmount = 0, score = 0;
		int arr[5] = { -1, -1, -1,-1,-1 };

		for (int i = 0; i < 5; i++) {
			randIndex = rand() % allQuestions.size() + 0;
			for (int j = 0; j < 5; j++) {
				if (arr[j] == randIndex) {
					randIndex = rand() % allQuestions.size() + 0;
					j = -1;
				}
			}
			arr[i] = randIndex;
			newQuiz.sequences.push_back(randIndex);
			cout << "Question " << num << " :" << endl;
			correctAnswer = displayQuestions(randIndex, true);
			newQuiz.rightSelections.push_back(correctChoice);
			cout << endl << "Your answer: ";
			cin >> ans;

			string userAns(1, ans), correctAns(1, correctAnswer);
			newQuiz.inputsByUser.push_back(userAns);
			newQuiz.correctAnswers.push_back(correctAns);

			if (ans == correctAnswer) {
				cout << endl << "GREATTT!!!Your answer is correct!" << endl << endl;
				correctAmount++;
				score += 1;
			}
			else {
				cout << endl << "OH NO...INCORRECT! The correct answer was " << correctAnswer << endl << endl;
				wrongAmount++;
			}
			num++;
		}

		cout << " --------------------------------------- " << endl;
		cout << "Out of 5 question your score is  : " << score << endl;
		if (score == 4 and score == 5) {
			cout << "Great!!!, Well-done!";
		}
		else {
			cout << "You have to work hard!!!" << endl;
		}
		cout << "Correct Amount: " << correctAmount << endl;
		cout << "Wrong Amount: " << wrongAmount << endl << endl;
		newQuiz.setScore(score);
		newQuiz.setCorrect(correctAmount);
		newQuiz.setWrong(wrongAmount);
		allPlayers[currentUser].addQuiz(newQuiz);
	}
	else {
		cout << "Invalid! Firstly admin must enter 5 questions ";
	}
	system("pause");
	system("CLS");
}

void showLeaderBoard() {
	int amount = allPlayers[currentUser].getAmoutOfQuiz();
	if (amount > 0) {
		cout << "Amount of quizzes: " << amount << endl;
		cout << " -------------------------------- \n";
		for (int i = 0; i < amount; i++) {
			cout << "Quiz " << i + 1 << " : \n";
			cout << "\t- Score: " << allPlayers[currentUser].quizzes[i].getScore() << "/5" << endl;
			cout << "\t- Number of correct answers: " << allPlayers[currentUser].quizzes[i].getCorrectAmount() << endl;
			cout << "\t- Number of false answers: " << allPlayers[currentUser].quizzes[i].getWrongAmount() << endl;
			cout << "----------------------------\n";
		}
	}
	else {
		cout << "You havent taken any quiz yet.\n\n";
	}
	system("pause");
}

void playerScreen() {
	char choice;
	bool backToLogin = false;
	while (backToLogin == false) {
		system("CLS");
		cout << allPlayers[currentUser].getFirstname() << " " <<
			allPlayers[currentUser].getLastname() << " Student, enter your choice pls:" << endl

			<< "\t 1 for Start a quiz" << endl
			<< "\t 2 for Start a new quiz (from an existing file)" << endl
			<< "\t 3 for Display all your scores" << endl
			<< "\t 4 for Back" << endl
			<< "\t 5 for Exit the program" << endl
			<< "Your choice: ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case '1':
			newQuiz();
			break;
		case '2':
			existingQuestions();
			break;
		case '3':
			showLeaderBoard();
			break;
		case '4':
			backToLogin = true;
			break;
		case '5':
			exit(1);
			break;
		default:
			cout << "\nInvalid Input.\n\n";
			break;
		}
	}
}


void adminPanel() {
	bool isBack = false;
	while (isBack == false) {
		system("CLS");
		cout << allAdmins[currentUser].getFirstname() << " " << allAdmins[currentUser].getLastname()
			<< " Teacher, enter your choice, pls: " << endl
			<< " 1 for Create quiz" << endl
			<< " 2 for Back" << endl
			<< " 3 for Exit" << endl;
		string newFile;
		char choice;
		cin >> choice;
		system("CLS");
		switch (choice) {
		case '1':
			addQuestion();
			break;
		case '2':
			isBack = true;
			break;
		case '3':
			exit(1);
			break;
		default:
			cout << "\nInvalid Input.\n\n";
			break;
		}
	}
}

void mainScreen() {
	string userName, password;
	while (true) {
		bool admin = false;
		bool player = false;
		cout << "\n\t   +-------+                          _______       _______                             ";
		cout << "\n\t   |       |      |         |            |                /                              ";
		cout << "\n\t   |       |      |         |            |               /                               ";
		cout << "\n\t   |       |      |         |            |              /                                ";
		cout << "\n\t   |    // |      |         |            |             /                                 ";
		cout << "\n\t   |   //  |      |         |            |            /                                  ";
		cout << "\n\t   +--//---+      |_________|         ___|___        /_______                          ";
		cout << "\n\n\n\t\t\t\t   RULES OF THE GAME   :     \n";
		cout << "\t\t\t\t   1) 1 POINT WILL BE AWARDED FOR CORRECT     \n";
		cout << "\t\t\t\t   2) NO MARKS WILL AWARDED FOR INCORRECT     \n";
		cout << "\t\t\t\t   3) SCORE CARD WILL BE GIVEN AT END         \n";
		cout << "Admin username: admin, password:admin123" << endl;
		cout << "Player username: player, password:player123" << endl;
		cout << "Press enter to continue..." << endl;
		cin.ignore();
		cout << "Enter your Username: ";
		getline(cin, userName);
		cout << "Enter your password: ";
		getline(cin, password);
		for (int i = 0; i < allAdmins.size(); i++) {
			if (userName == allAdmins[i].getUsername()) {
				if (password == allAdmins[i].getPassword()) {
					admin = true;
					currentUser = i;
				}
			}
		}
		for (int i = 0; i < allPlayers.size(); i++) {
			if (userName == allPlayers[i].getUsername()) {
				if (password == allPlayers[i].getPassword()) {
					player = true;
					currentUser = i;
				}
			}
		}
		system("CLS");
		if (admin == true) {
			adminPanel();
		}
		else if (player == true) {
			playerScreen();
		}
		else {
			cout << "\nWrong username or password.\n\n";
		}
	}
}

int main()
{
	srand(time(NULL));

	Admin admin1("admin", "admin123", "Tural", "Novruzov");

	allAdmins.push_back(admin1);

	Player player1("player", "player123", "Sabina", "Shukurova");
	allPlayers.push_back(player1);


	fileName = "quest";
	mainScreen();
	existingQuestions();



	return 0;
}