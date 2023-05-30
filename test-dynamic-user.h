#include <iostream>
#include <ctime>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

struct NodeUser //NodeUser1, 2, 3
{
    string userDetails[5];
    string userFavorite[5] = {"a","a","a","a","a"};
    NodeUser *next; // link pointer
};

struct LinkedListUser
{
    NodeUser *head;
    int size;

    LinkedListUser()
    {
        this->size = 0;
        this->head = nullptr;
    }
    
    string get_favourite(string userId, int index, string userAction) {
        transform(userId.begin(), userId.end(), userId.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
        });

        string matchId;
        NodeUser *curr = head;
        while (curr != nullptr)
        {
            matchId = curr->userDetails[0];
            transform(matchId.begin(), matchId.end(), matchId.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });

            if (matchId == userId && userAction == "get") {
                return curr->userFavorite[index];
            } else if (matchId == userId && userAction == "remove") {
                curr->userFavorite[index] = "a";
                return "Favorite removed!\n\n";
            }
            curr = curr->next;
        }
    }

    void insert(string details[5]) {

        NodeUser *newNode = new NodeUser;
        for (int i = 0; i < 5; i++) {
            newNode->userDetails[i] = details[i];
        }
        newNode->next = head; //point to current firstNode
        head = newNode;       //update the head pointer to point to the newNode
        size++;
    }

    string insertUni(string username, string uniName) {
        transform(username.begin(), username.end(), username.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
        });

        NodeUser *curr = head;
        string textToGenerate = "", userToMatch;
        bool checker = false;

        while (curr != nullptr) {
            userToMatch = curr->userDetails[0];
            transform(userToMatch.begin(), userToMatch.end(), userToMatch.begin(), [](unsigned char c) { //convert to lowercase
                    return tolower(c);
            });

            if (userToMatch == username) {
                for (int i = 0; i < 5; i++) {
                    if ((curr->userFavorite[i] == "a")) {
                        curr->userFavorite[i] = uniName;
                        checker = true;
                        return textToGenerate;
                    }
                }
            }
            curr = curr->next;
        }
        
        if (checker == false) {
            textToGenerate = "Slot maximum is 5, please remove any university from favorite";
        }

        return textToGenerate;
    }

    void deleteNode(string nameToDelete) {
        transform(nameToDelete.begin(), nameToDelete.end(), nameToDelete.begin(), [](unsigned char c) { //convert to lowercase
            return tolower(c);
        });

        NodeUser *curr = head;
        NodeUser *prev = nullptr;

        // Find the node to delete
        while (curr != nullptr && curr->userDetails[0] != nameToDelete)
        {
            prev = curr;
            curr = curr->next;
        }

        // If the node was found
        if (curr != nullptr)
        {
            // If the node to delete is the head
            if (prev == nullptr)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }

            delete curr;
            size--;

            cout << "Node with name \"" << nameToDelete << "\" has been deleted.\n\n";
        }
        else
        {
            cout << "Node with name \"" << nameToDelete << "\" not found.\n\n";
        }
    }
    
    void showBasedInactivity() {
        // sortInactivityTime();

        NodeUser *curr = head;
        string hyphen(69,'-');
        cout << hyphen << endl << "             Name              |           Inactivity Status          |\n" << hyphen << endl;
        while (curr != nullptr) {
            if(curr->userDetails[4] == "Inactive"){
            printf(" %-*s| %-*s|\n", 30, curr->userDetails[0].c_str(), 37, curr->userDetails[4].c_str());
            }
            curr = curr->next;
        }
        cout << hyphen << endl << endl;
    }

    void selectionSort() {
        NodeUser* curr = head;
        NodeUser* minNode;

        while (curr != nullptr) {
            minNode = curr;
            NodeUser* temp = curr->next;

            while (temp != nullptr) {
                if (temp->userDetails[0] < minNode->userDetails[0]) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            // Swap the data of current node and minimum node
            if (minNode != curr) {
                swap(curr->userDetails, minNode->userDetails);
            }

            curr = curr->next;
        }
    }

    void show() {
        NodeUser *curr = head;

        string mainTitle = " No | Name                | Activity Status                   | Email Address                 | Phone Number   |";
        cout << endl << mainTitle << endl << endl;

        int i = 1;
        while (curr != nullptr)
        {
            printf(" %-*s| %-*s| %-*s| %-*s| %-*s|\n", 3, to_string(i).c_str(), 20, curr->userDetails[0].c_str(), 34, curr->userDetails[4].c_str(), 30, curr->userDetails[2].c_str(), 15, curr->userDetails[3].c_str());
            curr = curr->next;
            i++;
        }
        cout << "\n\n";
    }
    
    void editDetail(string nameToFind) {
        transform(nameToFind.begin(), nameToFind.end(), nameToFind.begin(), [](unsigned char c) { //convert to lowercase
            return tolower(c);
        });

        string nameToMatch, option, detail;
        NodeUser *curr = head;
        while (curr != nullptr){
            nameToMatch = curr->userDetails[0];
            transform(nameToFind.begin(), nameToFind.end(), nameToFind.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });

            if (nameToFind == nameToMatch) {
                break;
            }

            curr = curr->next;
        }

        if (nameToFind == nameToMatch) {
            while (true) {
                cout << "Detail of \"" << curr->userDetails[0] << "\"\n\n";
                printf("1. Email: %s\n2. Phone: %s\n\n", curr->userDetails[2].c_str(), curr->userDetails[3].c_str());

                cout << "Which one do you want to edit (1-3): ";
                getline(cin, option);
                if (option == "1" || option == "2" || option == "3") {
                    if (option == "1") {
                        cout << "Enter the new email for this account: ";
                    } else if (option == "2") {
                        cout << "Enter the new phone for this account: ";
                    }
                    
                    else if (option == "1") {
                        curr->userDetails[2] = detail;
                        cout << "Email";
                    } else if (option == "2") {
                        curr->userDetails[3] = detail;
                        cout << "Phone";
                    }
                    // system("cls");
                    cout << "Account detail has been changed!\n\n";
                    return;
                } else {
                    system("cls");
                    cout << "Invalid Input!\n\n";
                }
            }
        }
        system("cls");
        cout<< "Account not found!\n\n";
        return;
    }

    string binarySearch(string username, string password, string userAction) {
        NodeUser *start = head;
        NodeUser *end = nullptr;

        selectionSort();
        
        while (start != end) {
            NodeUser *mid = start;
            int count = 0;
            
            // Count the number of elements between start and mid
            while (mid != end) {
                mid = mid->next;
                count++;
            }
            
            // Find the middle element
            mid = start;
            for (int j = 0; j < count / 2; j++) {
                mid = mid->next;
            }

            transform(username.begin(), username.end(), username.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });
            transform(mid->userDetails[0].begin(), mid->userDetails[0].end(), mid->userDetails[0].begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });
            
            // Check if the middle element matches the target
            if (mid->userDetails[0] == username && mid->userDetails[1] == password) {
                string user_information = mid->userDetails[0];
                return user_information;  // Found
            }
            
            // Adjust the start and end pointers based on the comparison
            if (mid->userDetails[0] < username) {
                start = mid->next;
            } else {
                end = mid;
            }
        }
        return "NULL";  // Not found after all iterations
    }

    string binarySearchUsername(string username) {
        NodeUser *start = head;
        NodeUser *end = nullptr;

        selectionSort();
        
        while (start != end) {
            NodeUser *mid = start;
            int count = 0;
            
            // Count the number of elements between start and mid
            while (mid != end) {
                mid = mid->next;
                count++;
            }
            
            // Find the middle element
            mid = start;
            for (int j = 0; j < count / 2; j++) {
                mid = mid->next;
            }

            transform(username.begin(), username.end(), username.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });

            
            // Check if the middle element matches the target
            if (mid->userDetails[0] == username) {
                string user_information = mid->userDetails[0];
                return user_information;  // Found
            }
            
            // Adjust the start and end pointers based on the comparison
            if (mid->userDetails[0] < username) {
                start = mid->next;
            } else {
                end = mid;
            }
        }
        return "NULL";  // Not found after all iterations
    }

    void editActivity(string user_info){
        transform(user_info.begin(), user_info.end(), user_info.begin(), [](unsigned char c){
            return tolower(c);
        });

        
        string nameMatch;
        NodeUser *curr = head;
        string lastActiveDate;

        time_t now = time(NULL);
        tm* ltm = localtime(&now);

        stringstream buffer;
        buffer << 1900 + ltm->tm_year << '/' << setw(2) << setfill('0') << ltm->tm_mon + 1 << '/' <<
            setw(2) << setfill('0') << ltm->tm_mday << ' ' << setw(2) << setfill('0') << ltm->tm_hour << ':' <<
            setw(2) << setfill('0') << ltm->tm_min << ':' << setw(2) << setfill('0') << ltm->tm_sec;
        lastActiveDate = buffer.str();
        while (curr != nullptr){
            nameMatch = curr->userDetails[0];
            transform(nameMatch.begin(), nameMatch.end(), nameMatch.begin(), [](unsigned char c){
                return tolower(c);
            });
            if(user_info == nameMatch){
                break;
            }
            curr = curr->next;
        }
        if (user_info == nameMatch){
            curr->userDetails[4] = "Last login on " + lastActiveDate;
        }
    }
};