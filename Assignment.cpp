#include <iostream>
#include <regex>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include "linkedlist-user.h"
#include "linkedlist-university.h"
#include "linkedlist-feedback.h"
#include "linkedlist-reply.h"

using namespace std;

void admin_account(string &id, string &pass);
void register_account(LinkedListUser* UserAccountList);
void registered_user_menu(string userId, LinkedListUniversity* UniList, LinkedListUser* UserAccountList, LinkedListFeedback *FeedbackList, LinkedListReply* ReplyList);
void admin_menu(LinkedListUniversity* UniList, LinkedListUser* UserAccountList, LinkedListFeedback *FeedbackList, LinkedListReply* ReplyList);
void print_university(LinkedListUniversity* UniList);
void viewFavorite(string userId, LinkedListUniversity* UniList, LinkedListUser* UserAccountList);

int main() {
    system("cls");
    LinkedListUser *UserAccountList = new LinkedListUser;
    LinkedListUniversity *UniList = new LinkedListUniversity;
    LinkedListFeedback *FeedbackList = new LinkedListFeedback;
    LinkedListReply *ReplyList = new LinkedListReply;

    string userDetail[5] = {"richard", "supernova", "richard@gmail.com", "+60 1127129122", "20"};
    UserAccountList->insert(userDetail);
    string userDetail1[5] = {"nathan", "holyholy", "nathan@yahoo.com", "+62 12382174", "14"};
    UserAccountList->insert(userDetail1);

    print_university(UniList);

    while (true) {
        //Generate admin account
        string adminId, adminPwd;
        admin_account(adminId, adminPwd);

        cout << "Welcome to NAMA SYSTEM" << endl;
        cout << "=-----= Menu Option =-----=" << endl;
        cout << "1. Display All Universities\n2. Search University\n3. Login\n4. Register\n5. Exit\n\n";
        cout << "What do you want to do (1-5): ";

        string userChoice;
        getline(cin, userChoice);

        if (userChoice == "1") {
            system("cls");
            UniList->show("uniName");
            system("pause");
            system("cls");
        } else if (userChoice == "2") {
            cout << "University name: ";
            getline(cin, userChoice);
            if (UniList->linearSearch(userChoice, "display")) {
                system("pause");
                system("cls");
            } else {
                system("cls");
                cout << "University name not found!\n\n";
            }
        } else if (userChoice == "3") {
            system("cls");

            string userId, userPwd;
            cout << "Username : ";
            getline(cin, userId);
            cout << "Password : ";
            getline(cin, userPwd);

            if (UserAccountList->binarySearch(userId, userPwd, "login")) {
                system("cls");
                registered_user_menu(userId, UniList,UserAccountList, FeedbackList, ReplyList);
            } else if (userId == adminId && userPwd == adminPwd) {
                system("cls");
                admin_menu(UniList,UserAccountList, FeedbackList, ReplyList);
            } else {
                system("cls");
                cout << "Username and Password not found!\n\n";
            }

        } else if (userChoice == "4") {
            system("cls");
            register_account(UserAccountList);
            system("cls");
        } else if (userChoice == "5") {
            system("cls");
            system("pause");
            system("cls");
        } else {
            system("cls");
            cout << "Invalid input!\n\n";
        }
    }
}

void print_university(LinkedListUniversity* UniList) {
    string myLIST[21];

    string fname = "2023 QS World University Rankings.csv";
    ifstream file(fname); // open file
    if (file.is_open())
    {
        string line;
        getline(file, line);
        while (getline(file, line)) // get line by line
        {
            int i = 0;
            stringstream ss(line); // line by line
            string word;
            while (getline(ss, word, ',')) // seperate
            {
                if (word == "") {
                    word = "-";
                }
                myLIST[i++] = word; // append all word to an array
            }
            UniList->insert(myLIST); // insert array to linked list
        }
        file.close();
    }
    else {
        cout << "Could not open the file\n";
    }
}

void admin_account(string &id, string &pass) {
    // id = "adminMoHE";
    // pass = "admin123";
    id = "q";
    pass = "w";
}

void register_account(LinkedListUser* UserAccountList) {
    string userName, userPass, userEmail, userPhone, userAge;
    
    while (true) {
        cout << "=---= Register Account =---=" << endl;
        cout << "Name     : ";
        getline(cin, userName);
        cout << "Password : ";
        getline(cin, userPass);  //1
        cout << "Age      : ";
        getline(cin, userAge);   //4
        cout << "Email    : ";
        getline(cin, userEmail); //2
        cout << "*Phone format -> +xx xxxxxxxx\nPhone    : ";
        getline(cin, userPhone); //3
        
        string userDetail[5] = {userName, userPass, userEmail, userPhone, userAge};

        if (userDetail[1].length() < 8 ) {
            system("cls");
            cout << "Password is too short, 8+ is our recommendation\n\n";
            continue;
        }

        // Email pattern
        const regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        // Match the email against the pattern
        if (!regex_match(userDetail[2], emailPattern)) {
            system("cls");
            cout << "Email Invalid!\n\n";
            continue;
        }

        const regex phonePattern(R"(^\+\d{2}\s\d{7,10}$)");
        if (!regex_match(userDetail[3], phonePattern)) {
            system("cls");
            cout << "Phone Number Invalid!\n\n";
            continue;
        }

        const regex agePattern(R"(^\d{2}$)");
        if (!regex_match(userDetail[4], agePattern)) {
            system("cls");
            cout << "Age Invalid!\n\n";
            continue;
        }
        UserAccountList->insert(userDetail);
        break;
    }
}

void registered_user_menu(string userId, LinkedListUniversity* UniList, LinkedListUser* UserAccountList, LinkedListFeedback *FeedbackList, LinkedListReply* ReplyList) {
    string rUserChoice, rUserChoice2, rUniSort, uniName, uniFeedback;
    while (true) {
        cout << "=-----= Menu Option =-----=" << endl;
        cout << "1. Display All Universities\n2. Search University\n3. Send Feedback\n4. Read Feedback\n5. View Favorite\n6. Logout\n\n";
        cout << "Choose the option (1-6): ";
        
        getline (cin, rUserChoice);
        if (rUserChoice == "1") {
            while (true) {            
                system("cls");
                cout << "=-----= Sort Option =-----=\n";
                cout << "1. Sort by Academic Reputation\n2. Sort by Employer Reputation\n3. Sort by Faculty/Student Ratio\n";
                cout << "4. Sort by Citations Per Faculty\n5. Sort by International Faculty Ratio\n6. Sort by International Student Ratio\n";
                cout << "7. Sort by Research Network\n8. Sort by Employment Outcome\n9. Back\n\n";
                getline(cin, rUniSort);
                system("cls");

                if (rUniSort == "1"){
                    UniList->show("uniAR");
                    system("pause");
                }else if (rUniSort == "2"){
                    UniList->show("uniER");
                    system("pause");
                }else if (rUniSort == "3"){
                    UniList->show("uniFSR");
                    system("pause");
                }else if (rUniSort == "4"){
                    UniList->show("uniCPF");
                    system("pause");
                }else if (rUniSort == "5"){
                    UniList->show("uniIFR");
                    system("pause");
                }else if (rUniSort == "6"){
                    UniList->show("uniISR");
                    system("pause");
                }else if (rUniSort == "7"){
                    UniList->show("uniIRN");
                    system("pause");
                }else if (rUniSort == "8"){
                    UniList->show("uniGER");
                    system("pause");
                }else if (rUniSort == "9"){
                    break;
                }else{
                    cout << "Invalid input!\n\n";
                    continue;
                }
                system("cls");
                break;
            }
        } else if (rUserChoice == "2"){
            cout << "University name: ";
            getline (cin, rUserChoice);
            if (UniList->linearSearch(rUserChoice, "display")) {
                cout << "1. Make it as favorite\nanything to exit\n\nWhat do you want to do: ";
                
                getline (cin, rUserChoice2);
                if (rUserChoice2 == "1") {
                    rUserChoice2 = UserAccountList->insertUni(userId, rUserChoice);
                }
                system("cls");
                if (rUserChoice2 == "Slot maximum is 5, please remove any university from favorite") {
                    cout << rUserChoice2 << endl << endl;
                } else {
                    UniList->linearSearch(rUserChoice, "update");
                }
            } else {
                system("cls");
                cout << "University name not found!\n\n";
            }
        } else if (rUserChoice == "3"){
            cout << endl;
            cout << "University Name: ";
            getline(cin, uniName);
            if (UniList->linearSearch(uniName, "findonly")) {
                cout << "Write your feedback: ";
                getline(cin, uniFeedback);
                string toInsert[3] = {userId, uniName, uniFeedback};
                FeedbackList->insertFeedback(toInsert);
                system("cls");
                cout << "Feedback sent!\n\n";
            } else {
                system("cls");
                cout << "University not found!\n\n";
            }
        } else if (rUserChoice == "4"){
            system("cls");
            ReplyList->feedbackReplyShow(userId);
            system("pause");
            system("cls");
        } else if (rUserChoice == "5"){
            system("cls");
            viewFavorite(userId, UniList, UserAccountList);
        } else if (rUserChoice == "6"){
            system("cls");
            UserAccountList->getTime(userId);
            break;
        }else {
            system("cls");
            cout << "Invalid input!\n\n";
        }
    }
}

void viewFavorite(string userId, LinkedListUniversity* UniList, LinkedListUser* UserAccountList) {
    string uniName, listUni[5], userChoice, textDisplay ="";
    int index;
    bool anyFavorite = false;
    for (int i = 0; i < 5; i++) {
        uniName = UserAccountList->getFavorite(userId, i, "get");

        if (!(uniName == "a")) {
            cout << i+1 << ". " << uniName << endl;
            listUni[i] = uniName;
            anyFavorite = true;
        }
    }

    if (anyFavorite == true) {
        cout << "\nIf you wish to remove, type the number next to it (1-5)\nType anything beside (1-5) to back to main menu\n\nWhat do you want to do: ";
        getline(cin, userChoice);
        if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5") {
            index = (stoi(userChoice)) - 1;
            textDisplay = UserAccountList->getFavorite(userId, index, "remove");
            UniList->linearSearch(listUni[stoi(userChoice) - 1], "decrement");
        }
        system("cls");
        cout << textDisplay;
    }
    else {
        cout << "You have not make any university as your favorite!\n\n";
        system("pause");
        system("cls");
    }
}
    
void admin_menu(LinkedListUniversity* UniList, LinkedListUser* UserAccountList, LinkedListFeedback *FeedbackList, LinkedListReply* ReplyList) { 
    while (true) {
        cout << "=-----= Menu Option =-----=" << endl;
        cout << "1. Display All Registered Users\n2. Modify User Detail\n3. Delete User Account\n4. View or Reply Feedbacks\n5. Generate report of the Top 10 Universities\n6. Logout\n\n";
        cout << "Choose the option (1-7): ";

        string rAdminChoice ,nameToFind;
        getline (cin, rAdminChoice);
        
        if (rAdminChoice == "1") {
            system("cls");
            UserAccountList->show();
            system("pause");
            system("cls");
        } else if (rAdminChoice == "2"){
            cout << "Name to find: ";
            getline(cin, nameToFind);
            system("cls");
            UserAccountList->editDetail(nameToFind);
        } else if (rAdminChoice == "3"){
            system("cls");
            UserAccountList->showBasedInactivity();
            cout << "Username to be deleted: ";
            getline(cin, nameToFind);
            system("cls");
            UserAccountList->deleteNode(nameToFind);
        } else if (rAdminChoice == "4"){
            system("cls");
            string* feedbackData = FeedbackList->show();
            if (feedbackData[3] != "EmPtY") {
                ReplyList->insert(feedbackData);
            }
            system("cls");
        } else if (rAdminChoice == "5"){
            system("cls");
            UniList->sortFavorite();
            UniList->topFavorite();
            system("pause");
            system("cls");
        } else if (rAdminChoice == "6"){
            system("cls");
            break;
        } else {
            system("cls");
            cout << "invalid Input!\n\n";
        }
    }
}