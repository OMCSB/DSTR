/* lab5-linkedlist-singly.h */

#include <iostream>
#include <ctime>
using namespace std;

/**
 * with structure implementation...
 */
struct NodeUser //NodeUser1, 2, 3
{
    string userDetails[5];
    string userFavorite[5] = {"a","a","a","a","a"};
    time_t userLogOff;
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

    void getTime(string username) {
        transform(username.begin(), username.end(), username.begin(), [](unsigned char c) {
                return std::tolower(c);
        });

        string nameToMatch;
        NodeUser *curr = head;
        while (curr != nullptr) {
            nameToMatch = curr->userDetails[0];
            transform(nameToMatch.begin(), nameToMatch.end(), nameToMatch.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            if (username == nameToMatch) {
                curr->userLogOff = time(0);
            }
            curr = curr->next;
        }
    }
    
    string getFavorite(string userId, int index, string userAction) {
        transform(userId.begin(), userId.end(), userId.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
        });

        string matchId;
        NodeUser *curr = head;
        while (curr != nullptr)
        {
            matchId = curr->userDetails[0];
            transform(matchId.begin(), matchId.end(), matchId.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
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

    void insert(string details[5])
    {
        NodeUser *newNode = new NodeUser;
        for (int i = 0; i < 5; i++) {
            newNode->userDetails[i] = details[i];
        }
        time_t currentTime = time(0);
        newNode->userLogOff = currentTime;

        newNode->next = head; //point to current firstNode
        head = newNode;       //update the head pointer to point to the newNode
        size++;
    }

    string insertUni(string username, string uniName) {
        transform(username.begin(), username.end(), username.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
        });

        NodeUser *curr = head;
        string textToGenerate = "", userToMatch;
        bool checker = false;

        while (curr != nullptr) {
            userToMatch = curr->userDetails[0];
            transform(userToMatch.begin(), userToMatch.end(), userToMatch.begin(), [](unsigned char c) { //convert to lowercase
                    return std::tolower(c);
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

    void deleteNode(string nameToDelete)
    {
        transform(nameToDelete.begin(), nameToDelete.end(), nameToDelete.begin(), [](unsigned char c) { //convert to lowercase
            return std::tolower(c);
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
        string hyphen(69,'-'), timeDif;
        time_t currentTime = time(0);
        double diffSeconds, diffMinutes, diffHours;
        cout << hyphen << endl << "             Name              |           Inactivity Time          |\n" << hyphen << endl;
        while (curr != nullptr) {
            diffSeconds = difftime(currentTime, curr->userLogOff);
            diffMinutes = diffSeconds / 60;
            if (diffMinutes <= 1) {
                timeDif = "Less than a minute of inactivity";
            } else if (diffMinutes < 60) {
                timeDif = to_string(diffMinutes) + " minutes of inactivity";
            } else {
                diffHours = diffMinutes / 60;
                timeDif = to_string(diffHours) + " hours of inactivity";
            }
            printf(" %-*s| %-*s|\n", 30, curr->userDetails[0].c_str(), 35, timeDif.c_str());
            curr = curr->next;
        }
        cout << hyphen << endl << endl;
    }

    // void sortInactivityTime() {
    //     NodeUser* curr = head;
    //     NodeUser* minNode;

    //     while (curr != nullptr) {
    //         minNode = curr;
    //         NodeUser* temp = curr->next;

    //         while (temp != nullptr) {
    //             if (temp->userLogOff < minNode->userLogOff) {
    //                 minNode = temp;
    //             }
    //             temp = temp->next;
    //         }

    //         // Swap the data of current node and minimum node
    //         if (minNode != curr) {
    //             swap(curr->userDetails, minNode->userDetails);
    //         }

    //         curr = curr->next;
    //     }
    // }

    // void sortInactivityTime() {
    //     NodeUser* curr = head;
    //     NodeUser* minNode;

    //     while (curr != nullptr) {
    //         minNode = curr;
    //         NodeUser* temp = curr->next;

    //         while (temp != nullptr) {
    //             if (temp->userLogOff < minNode->userLogOff) {
    //                 minNode = temp;
    //             }
    //             temp = temp->next;
    //         }

    //         // Swap the nodes
    //         if (minNode != curr) {
    //             // Swap the user details array
    //             swap(curr->userDetails, minNode->userDetails);

    //             // Swap the user favorite array
    //             swap(curr->userFavorite, minNode->userFavorite);

    //             // Swap the user logoff time
    //             time_t tempLogOff = curr->userLogOff;
    //             curr->user  LogOff = minNode->userLogOff;
    //             minNode->userLogOff = tempLogOff;
    //         }

    //         curr = curr->next;
    //     }
    // }

    void sortInactivityTime() {
        NodeUser* curr = head;
        NodeUser* minNode;

        while (curr != nullptr) {
            minNode = curr;
            NodeUser* temp = curr->next;

            while (temp != nullptr) {
                if (temp->userLogOff < minNode->userLogOff) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            if (minNode != curr) {
                // Swap the user details
                swap(curr->userDetails[0], minNode->userDetails[0]);
                swap(curr->userDetails[1], minNode->userDetails[1]);
                swap(curr->userDetails[2], minNode->userDetails[2]);
                swap(curr->userDetails[3], minNode->userDetails[3]);
                swap(curr->userDetails[4], minNode->userDetails[4]);

                // Swap the user favorites
                swap(curr->userFavorite[0], minNode->userFavorite[0]);
                swap(curr->userFavorite[1], minNode->userFavorite[1]);
                swap(curr->userFavorite[2], minNode->userFavorite[2]);
                swap(curr->userFavorite[3], minNode->userFavorite[3]);
                swap(curr->userFavorite[4], minNode->userFavorite[4]);

                // Swap the user logoff time
                time_t tempLogOff = curr->userLogOff;
                curr->userLogOff = minNode->userLogOff;
                minNode->userLogOff = tempLogOff;
            }

            curr = curr->next;
        }
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

    void show()
    {
        NodeUser *curr = head;

        string hyphen(102, '-'), hyphen0(5, '-'), hyphen1(32, '-'), hyphen2(42, '-'), hyphen3(17, '-');
        string mainTitle = " No |             Name              | Age |             Email Address               |  Phone Number  |";
        cout << hyphen << endl << mainTitle << endl << hyphen << endl;

        int i = 1;
        while (curr != nullptr)
        {
            printf(" %-*s| %-*s| %-*s| %-*s| %-*s|\n", 3, to_string(i).c_str(), 30, curr->userDetails[0].c_str(), 4, curr->userDetails[4].c_str(), 40, curr->userDetails[2].c_str(), 15, curr->userDetails[3].c_str());
            curr = curr->next;
            i++;
        }
        cout << hyphen << "\n\n";
    }
    
    void editDetail(string nameToFind) {
        transform(nameToFind.begin(), nameToFind.end(), nameToFind.begin(), [](unsigned char c) { //convert to lowercase
            return std::tolower(c);
        });

        string nameToMatch, option, detail;
        NodeUser *curr = head;
        while (curr != nullptr){
            nameToMatch = curr->userDetails[0];
            transform(nameToFind.begin(), nameToFind.end(), nameToFind.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
            });

            if (nameToFind == nameToMatch) {
                break;
            }

            curr = curr->next;
        }

        if (nameToFind == nameToMatch) {
            while (true) {
                cout << "Detail of \"" << curr->userDetails[0] << "\"\n\n";
                printf("1. Age  : %s\n2. Email: %s\n3. Phone: %s\n\n", curr->userDetails[4].c_str(), curr->userDetails[2].c_str(), curr->userDetails[3].c_str());

                cout << "Which one do you want to edit (1-3): ";
                getline(cin, option);
                if (option == "1" || option == "2" || option == "3") {
                    if (option == "1") {
                        cout << "Enter the new age for this account: ";
                    } else if (option == "2") {
                        cout << "Enter the new email for this account: ";
                    } else {
                        cout << "Enter the new phone for this account: ";
                    }
                    getline(cin, detail);
                    if (option == "1") {
                        curr->userDetails[4] = detail;
                        cout << "AGE";
                    } else if (option == "2") {
                        curr->userDetails[2] = detail;
                        cout << "Email";
                    } else if (option == "3") {
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

    bool binarySearch(string username, string password, string userAction) {
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
                return std::tolower(c);
            });
            transform(mid->userDetails[0].begin(), mid->userDetails[0].end(), mid->userDetails[0].begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
            });
            
            // Check if the middle element matches the target
            if (mid->userDetails[0] == username && mid->userDetails[1] == password) {
                return true;  // Found
            }
            
            // Adjust the start and end pointers based on the comparison
            if (mid->userDetails[0] < username) {
                start = mid->next;
            } else {
                end = mid;
            }
        }
        return false;  // Not found after all iterations
    }
};