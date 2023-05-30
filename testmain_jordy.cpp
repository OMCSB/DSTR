#include <iostream>
#include <regex>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include "test-dynamic-user.h"
#include "test-mergesort.h"
#include "linkedlist-feedback.h"
#include "linkedlist-reply.h"

using namespace std;

void admin_account(string &id, string &pwd);
void register_account(LinkedListUser* usrAccList, int size);
void load_university(LinkedListUniversity* unvList);
void view_favourite(string userId, LinkedListUniversity* unvList, LinkedListUser* usrAccList);
void admin_menu(LinkedListUniversity* unvList, LinkedListUser* usrAccList, LinkedListFeedback *fbkList, LinkedListReply* rlyList);
void registered_user_menu(string userId, LinkedListUniversity* unvList, LinkedListUser* usrAccList, LinkedListFeedback *fbkList, LinkedListReply* rlyList);

int main() {
    system("cls");
    LinkedListUniversity *unvList = new LinkedListUniversity;
    LinkedListUser *usrAccList = new LinkedListUser;
    LinkedListFeedback *fbkList = new LinkedListFeedback;
    LinkedListReply *rlyList = new LinkedListReply;
    int size;

    string userDetail[5] = {"user1", "aaaabbbb", "user1@gmail.com", "+60 1127129122", "Inactive"};
    usrAccList->insert(userDetail);
    // size++;
    string userDetail1[5] = {"user2", "bbbbaaaa", "user2@yahoo.com", "+62 12382174", "Inactive"};
    usrAccList->insert(userDetail1);
    // size++;

    load_university(unvList);

    while (true) {
        //Generate admin account
        string adminId, adminPwd;
        admin_account(adminId, adminPwd);
    
        cout << "---- TUR SYSTEM ----" << endl;
        cout << "******* Menu *******" << endl;
        cout << "\n1. Login\n2. Register\n3. View All Universities\n4. Search University\n5. Exit\n\n";
        cout << "Please select an activity (1-5): ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            system("cls");

            string userId, userPwd;
            cout << "Username : ";
            getline(cin, userId);
            cout << "\nPassword : ";
            getline(cin, userPwd);

            
            string checker;
            checker = usrAccList->binarySearch(userId, userPwd, "login");
            if (checker != "NULL") {
                system("cls");
                usrAccList->editActivity(checker);
                registered_user_menu(userId, unvList,usrAccList, fbkList, rlyList);
            } else if (userId == adminId && userPwd == adminPwd) {
                system("cls");
                admin_menu(unvList,usrAccList, fbkList, rlyList);
            } else {
                system("cls");
                cout << "Username and Password not found!\n\n";
            }
            
        } else if (choice == "2") {
            system("cls");
            register_account(usrAccList, size);
            system("cls");
        } else if (choice == "3") {
            system("cls");
            unvList->show("uniName");
            system("pause");
            system("cls");

        } else if (choice == "4") {
            cout << "University name: ";
            getline(cin, choice);
            if (unvList->linearSearch(choice, "display")) {
                system("pause");
                system("cls");
            } else {
                system("cls");
                cout << "This university does not exist in the database!\n\n";
            }
        } else if (choice == "5") {
            system("cls");
            break;
            system("cls");
        } else {
            system("cls");
            cout << "Invalid input!\n\n";
        }
    }
}

void admin_account(string &id, string &pwd) {
    // id = "q";
    // pass = "w";
    id = "q";
    pwd = "w";
}


void register_account(LinkedListUser* usrAccList, int size) {
    string userName, userPass, userEmail, userPhone, userAge, userActivity;
    userActivity = "Inactive";
    
    while (true) {
        cout << "***** Register Account *****" << endl;
        cout << "\nName               : ";
        getline(cin, userName);
        string checkUsername = usrAccList->binarySearchUsername(userName);
        if (checkUsername != "NULL"){
            cout << "\nThe username have been taken. Please try another username!" << endl;
            system("pause");
            break;
        }
        
        cout << "Password           : ";
        getline(cin, userPass);  //1
        if (userPass.length() < 8 ) {
            cout << "\nThe minimum password length is 8!";
            system("pause");
            break;
        }
        
        cout << "Email              : ";
        getline(cin, userEmail); //2
        const regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        // Match the email against the pattern
        if (!regex_match(userEmail, emailPattern)) {
            cout << "\nYou have inputted an invalid email!";
            system("pause");
            break;
        }
        cout << "Phone (+xxxxxxxxx): ";
        getline(cin, userPhone); //3
        const regex phonePattern(R"(^\+\d{9,13}$)");
        if (!regex_match(userPhone, phonePattern)) {
            system("pause");
            cout << "\nPlease follow the phone number format!";
            break;
        }
        
        string userDetail[5] = {userName, userPass, userEmail, userPhone, userActivity};
        

        
        // Email pattern
        
        
        usrAccList->insert(userDetail);
        break;
    }
}

void load_university(LinkedListUniversity* unvList) {
    string unvArray[21];

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
                unvArray[i++] = word; // append all word to an array
            }
            unvList->insert(unvArray); // insert array to linked list
        }
        file.close();
    }
    else {
        cout << "Could not open the file\n";
    }
}

void view_favourite(string userId, LinkedListUniversity* unvList, LinkedListUser* usrAccList) {
    string uniName, listUni[5], choice, textDisplay ="";
    int index;
    bool anyFavorite = false;
    for (int i = 0; i < 5; i++) {
        uniName = usrAccList->get_favourite(userId, i, "get");

        if (!(uniName == "a")) {
            cout << i+1 << ". " << uniName << endl;
            listUni[i] = uniName;
            anyFavorite = true;
        }
    }

    if (anyFavorite == true) {
        cout << "\nSelect a university you want to remove (1-5)!\nType anything besides 1 to 5 to go back to main menu!\n\nPlease select a university or go back to menu: ";
        getline(cin, choice);
        if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") {
            index = (stoi(choice)) - 1;
            textDisplay = usrAccList->get_favourite(userId, index, "remove");
            unvList->linearSearch(listUni[stoi(choice) - 1], "decrement");
        }
        system("cls");
        cout << textDisplay;
    }
    else {
        cout << "You have no favorite university! Add them to your favorites by searching them! \n\n";
        system("pause");
        system("cls");
    }
}

void admin_menu(LinkedListUniversity* unvList, LinkedListUser* usrAccList, LinkedListFeedback *fbkList, LinkedListReply* rlyList) { 
    while (true) {
        cout << "******** Menu Option ********" << endl;
        cout << "\n1. Display Users\n2. Edit User Details\n3. Delete Account\n4. View or Reply Feedbacks\n5. Generate report of the Top 10 Universities\n6. Logout\n\n";
        cout << "Please select an activity (1-6): ";

        string rAdminChoice ,nameToFind;
        getline (cin, rAdminChoice);
        
        if (rAdminChoice == "1") {
            system("cls");
            usrAccList->show();
            system("pause");
            system("cls");
        } else if (rAdminChoice == "2"){
            cout << "Name to find: ";
            getline(cin, nameToFind);
            system("cls");
            usrAccList->editDetail(nameToFind);
        } else if (rAdminChoice == "3"){
            system("cls");
            usrAccList->showBasedInactivity();
            cout << "Username to be deleted: ";
            getline(cin, nameToFind);
            system("cls");
            usrAccList->deleteNode(nameToFind);
        } else if (rAdminChoice == "4"){
            system("cls");
            string* feedbackData = fbkList->show();
            if (feedbackData[3] != "NULL") {
                rlyList->insert(feedbackData);
            }
            system("cls");
        } else if (rAdminChoice == "5"){
            system("cls");
            unvList->sortFavorite();
            unvList->topFavorite();
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

void registered_user_menu(string userId, LinkedListUniversity* unvList, LinkedListUser* usrAccList, LinkedListFeedback *fbkList, LinkedListReply* rlyList) {
    string rchoice, rchoice2, rUniSort, uniName, uniFeedback;
    while (true) {
        cout << "******* Menu Option ********" << endl;
        cout << "\n1. Display All Universities\n2. Search University\n3. Send Feedback\n4. Read Feedback\n5. View Favorite\n6. Logout\n\n";
        cout << "Choose the option (1-6): ";
        
        getline (cin, rchoice);
        if (rchoice == "1") {
            while (true) {            
                system("cls");
                cout << "******** Sort Option ********\n";
                cout << "1. Sort by Academic Reputation\n2. Sort by Employer Reputation\n3. Sort by Faculty/Student Ratio\n";
                cout << "\n4. Back\n\n";
                getline(cin, rUniSort);
                system("cls");

                if (rUniSort == "1"){
                    unvList->show("uniAR");
                    system("pause");
                }else if (rUniSort == "2"){
                    unvList->show("uniER");
                    system("pause");
                }else if (rUniSort == "3"){
                    unvList->show("uniFSR");
                    system("pause");
                }else if (rUniSort == "4"){
                    break;
                }else{
                    cout << "Invalid input!\n\n";
                    continue;
                }
                system("cls");
                break;
            }
        } else if (rchoice == "2"){
            cout << "University name: ";
            getline (cin, rchoice);
            if (unvList->linearSearch(rchoice, "display")) {
                cout << "Enter \"y\" to add to Favorites or anything else to go back: ";
                
                getline (cin, rchoice2);
                if (rchoice2 == "y") {
                    rchoice2 = usrAccList->insertUni(userId, rchoice);
                }
                system("cls");
                if (rchoice2 == "There can only be 5 Favorite University. Please remove a university from Favorites") {
                    cout << rchoice2 << endl << endl;
                } else {
                    unvList->linearSearch(rchoice, "update");
                }
            } else {
                system("cls");
                cout << "University name not found!\n\n";
            }
        } else if (rchoice == "3"){
            cout << endl;
            cout << "University Name: ";
            getline(cin, uniName);
            if (unvList->linearSearch(uniName, "findonly")) {
                cout << "Write your feedback: ";
                getline(cin, uniFeedback);
                string toInsert[3] = {userId, uniName, uniFeedback};
                fbkList->insertFeedback(toInsert);
                system("cls");
                cout << "Feedback sent!\n\n";
            } else {
                system("cls");
                cout << "This university does not exist in the database!\n\n";
            }
        } else if (rchoice == "4"){
            system("cls");
            rlyList->feedbackReplyShow(userId);
            system("pause");
            system("cls");
        } else if (rchoice == "5"){
            system("cls");
            view_favourite(userId, unvList, usrAccList);
        } else if (rchoice == "6"){
            system("cls");
            break;
        }else {
            system("cls");
            cout << "Invalid input!\n\n";
        }
    }
}