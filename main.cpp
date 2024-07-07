#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to generate a random roll number
int generateRollNumber() {
    return rand() % 10000 + 1; // Generates a random number between 1 and 10000
}

// Base class for Question
class Question {
public:
    virtual void ask() const = 0;
    virtual bool checkAnswer(const string& answer) const = 0;
    virtual ~Question() {}
};

// Derived class for Car questions
class CarQuestion : public Question {
    string questionText;
    string correctAnswer;
public:
    CarQuestion(const string& q, const string& a) : questionText(q), correctAnswer(a) {}

    void ask() const override {
        cout << "Question: " << questionText << " ";
    }

    bool checkAnswer(const string& answer) const override {
        return answer == correctAnswer;
    }
};

// Derived class for RoadScenario questions
class RoadScenarioQuestion : public Question {
    string questionText;
    string correctAnswer;
public:
    RoadScenarioQuestion(const string& q, const string& a) : questionText(q), correctAnswer(a) {}

    void ask() const override {
        cout << "Scenario: " << questionText << " ";
    }

    bool checkAnswer(const string& answer) const override {
        return answer == correctAnswer;
    }
};

// Derived class for WeatherScenario questions
class WeatherScenarioQuestion : public Question {
    string questionText;
    string correctAnswer;
public:
    WeatherScenarioQuestion(const string& q, const string& a) : questionText(q), correctAnswer(a) {}

    void ask() const override {
        cout << "Weather Scenario: " << questionText << " ";
    }

    bool checkAnswer(const string& answer) const override {
        return answer == correctAnswer;
    }
};

// Function to display the welcome screen
void displayWelcomeScreen() {
    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "*      Welcome to Car Simulation Test    *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl;
}

// Function to check the password
bool checkPassword(const string& inputPassword) {
    const string correctPassword = "password123"; // Set your password here
    return inputPassword == correctPassword;      // Check if the entered password is correct
}

// Function to display the test section menu
void displayTestSectionMenu() {
    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "*       Select a test section:           *" << endl;
    cout << "*                                        *" << endl;
    cout << "*  1. Car Questions                      *" << endl;
    cout << "*  2. Road Scenarios                     *" << endl;
    cout << "*  3. Weather Conditions                 *" << endl;
    cout << "*  4. Exit                               *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl;
    cout << "Enter your choice (1-4): ";
}

// Class to manage the game
class GameManager {
    vector<Question*> questionsPool;
    unordered_set<Question*> askedQuestions;
    int correctAnswers;

    bool askQuestion(Question* q) {
        q->ask();
        string answer;
        cin >> answer;
        if (q->checkAnswer(answer)) {
            cout << "Correct!" << endl;
            return true;
        } else {
            cout << "Incorrect." << endl;
            return false;
        }
    }

public:
    GameManager() : correctAnswers(0) {}

    void addQuestion(Question* q) {
        questionsPool.push_back(q);
    }

    void shuffleQuestions() {
        random_shuffle(questionsPool.begin(), questionsPool.end());
    }

    bool askQuestions(int numQuestions, int requiredCorrect) {
        correctAnswers = 0;
        vector<Question*> currentRound;
        for (auto q : questionsPool) {
            if (askedQuestions.find(q) == askedQuestions.end()) {
                currentRound.push_back(q);
            }
        }
        random_shuffle(currentRound.begin(), currentRound.end());

        for (int i = 0; i < numQuestions && i < currentRound.size(); ++i) {
            Question* q = currentRound[i];
            askedQuestions.insert(q);
            if (askQuestion(q)) {
                ++correctAnswers;
            }
        }
        return correctAnswers >= requiredCorrect;
    }
};

int main() {
    srand(time(0)); // Seed the random number generator

    string password;
    bool accessGranted = false;

    displayWelcomeScreen();

    // Loop until the correct password is entered
    while (!accessGranted) {
        cout << "\nPlease enter the password to enter the test section: ";
        cin >> password;

        if (checkPassword(password)) {
            accessGranted = true;
            cout << "\nAccess Granted! Welcome to the Car Simulation Test.\n";
        } else {
            cout << "\nIncorrect password. Please try again.\n";
        }
    }

    GameManager gameManager;
    // Adding Car Questions
    gameManager.addQuestion(new CarQuestion("What is the typical number of doors on a Sedan?", "4"));
    gameManager.addQuestion(new CarQuestion("What does S stand for in SUV?", "Sport"));
    gameManager.addQuestion(new CarQuestion("Which wheel is used to change the direction of a Truck?", "steering"));
    gameManager.addQuestion(new CarQuestion("What is the main purpose of a spoiler on a car?", "aerodynamics"));
    gameManager.addQuestion(new CarQuestion("What type of fuel is commonly used in a Diesel engine?", "Diesel"));

    // Adding Road Scenario Questions
    gameManager.addQuestion(new RoadScenarioQuestion("You are driving in a residential area. A child suddenly runs into the road. What should you do? (A: Honk, B: Stop immediately, C: Speed up)", "B"));
    gameManager.addQuestion(new RoadScenarioQuestion("You are approaching a yellow traffic light. What should you do? (A: Speed up, B: Stop if safe, C: Ignore)", "B"));
    gameManager.addQuestion(new RoadScenarioQuestion("You are driving on a highway and see a car merging from an on-ramp. What should you do? (A: Speed up, B: Move to the left lane if safe, C: Honk and maintain speed)", "B"));
    gameManager.addQuestion(new RoadScenarioQuestion("You encounter a pedestrian at a crosswalk. What should you do? (A: Stop, B: Speed up, C: Honk)", "A"));
    gameManager.addQuestion(new RoadScenarioQuestion("A traffic sign shows a school zone ahead. What should you do? (A: Maintain speed, B: Slow down, C: Speed up)", "B"));

    // Adding Weather Scenario Questions
    gameManager.addQuestion(new WeatherScenarioQuestion("It is raining heavily and the roads are slippery. What should you do? (A: Speed up, B: Drive slowly, C: Turn on high beams)", "B"));
    gameManager.addQuestion(new WeatherScenarioQuestion("You are driving in dense fog. What should you do? (A: Turn on fog lights, B: Speed up, C: Turn off headlights)", "A"));
    gameManager.addQuestion(new WeatherScenarioQuestion("There is a snowstorm and visibility is low. What should you do? (A: Speed up, B: Drive slowly, C: Turn on high beams)", "B"));
    gameManager.addQuestion(new WeatherScenarioQuestion("The road is icy. What should you do? (A: Speed up, B: Drive slowly, C: Turn on high beams)", "B"));
    gameManager.addQuestion(new WeatherScenarioQuestion("You encounter a strong wind while driving. What should you do? (A: Maintain speed, B: Slow down, C: Speed up)", "B"));

    gameManager.shuffleQuestions();

    int choice = 0;
    while (choice != 4) {
        displayTestSectionMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Beginner Level: Answer 6 out of 10 questions correctly to advance.\n";
                if (gameManager.askQuestions(10, 6)) {
                    cout << "Congratulations! You've advanced to the Intermediate Level.\n";
                    cout << "Intermediate Level: Answer 3 out of 3 questions correctly to advance.\n";
                    if (gameManager.askQuestions(3, 3)) {
                        cout << "Congratulations! You've advanced to the Advanced Level.\n";
                        cout << "Advanced Level: Answer all 5 questions correctly to complete the test.\n";
                        if (gameManager.askQuestions(5, 5)) {
                            cout << "Congratulations! You've completed the Car Simulation Test.\n";
                        } else {
                            cout << "You did not answer all questions correctly. Try again later.\n";
                        }
                    } else {
                        cout << "You did not answer enough questions correctly. Try again later.\n";
                    }
                } else {
                    cout << "You did not answer enough questions correctly. Try again later.\n";
                }
                break;
            }
            case 2: {
                cout << "Beginner Level: Answer 6 out of 10 questions correctly to advance.\n";
                if (gameManager.askQuestions(10, 6)) {
                    cout << "Congratulations! You've advanced to the Intermediate Level.\n";
                    cout << "Intermediate Level: Answer 3 out of 3 questions correctly to advance.\n";
                    if (gameManager.askQuestions(3, 3)) {
                        cout << "Congratulations! You've advanced to the Advanced Level.\n";
                        cout << "Advanced Level: Answer all 5 questions correctly to complete the test.\n";
                        if (gameManager.askQuestions(5, 5)) {
                            cout << "Congratulations! You've completed the Road Scenario Test.\n";
                        } else {
                            cout << "You did not answer all questions correctly. Try again later.\n";
                        }
                    } else {
                        cout << "You did not answer enough questions correctly. Try again later.\n";
                    }
                } else {
                    cout << "You did not answer enough questions correctly. Try again later.\n";
                }
                break;
            }
            case 3: {
                cout << "Beginner Level: Answer 6 out of 10 questions correctly to advance.\n";
                if (gameManager.askQuestions(10, 6)) {
                    cout << "Congratulations! You've advanced to the Intermediate Level.\n";
                    cout << "Intermediate Level: Answer 3 out of 3 questions correctly to advance.\n";
                    if (gameManager.askQuestions(3, 3)) {
                        cout << "Congratulations! You've advanced to the Advanced Level.\n";
                        cout << "Advanced Level: Answer all 5 questions correctly to complete the test.\n";
                        if (gameManager.askQuestions(5, 5)) {
                            cout << "Congratulations! You've completed the Weather Conditions Test.\n";
                        } else {
                            cout << "You did not answer all questions correctly. Try again later.\n";
                        }
                    } else {
                        cout << "You did not answer enough questions correctly. Try again later.\n";
                    }
                } else {
                    cout << "You did not answer enough questions correctly. Try again later.\n";
                }
                break;
            }
            case 4:
                cout << "Exiting the Car Simulation Test. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
        }
    }

    return 0;
}
