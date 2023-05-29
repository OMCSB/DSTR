#include <iostream>
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
using namespace std;

/**
 * with structure implementation...
 */
struct UniNode
{
    string universityColumns[22];
    UniNode *next; // link pointer
};

struct LinkedListUniversity
{
    UniNode *head;
    int size;

    LinkedListUniversity()
    {
        this->size = 0;
        this->head = nullptr;
    }

    void insert(string details[21])
    {
        UniNode *newNode = new UniNode;
        for (int i = 0; i < 21; i++) {
            newNode->universityColumns[i] = details[i];
        }
        newNode->universityColumns[21] = "0";
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            UniNode *last = head;
            while (last->next != nullptr)
                last = last->next;
            last->next = newNode;
        }
        size++;
    }

    int getSize()
    {
        return size;
    }

    void show(string userAction)
    {
        UniNode *curr = head;

        string divider0(125, '-'), divider1(19, '-'), divider2(21, '-'), divider3(14, '-');
        string hyphenCollection[4] = {divider0, divider1, divider2, divider3};
        string subContent[9] = {" ArScore | ArRank |", " ErScore | ErRank |", " FsrScore | FsrRank |", " CpfScore | CpfRank |", " IfrScore | IfrRank |", " IsrScore | IsrRank |", " IrnScore | IrnRank |", " GerScore | GerRank |", " ScoreScaled |"};
        string mainContent = " RANK |                                    Institution                                    | CODE |         LOCATION         |";

        if (userAction == "uniName") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << endl << mainContent << endl << hyphenCollection[0] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str());
                curr = curr->next;
            }
        } else if (userAction == "uniAR") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[1] << endl << mainContent << subContent[0] << endl << hyphenCollection[0] << hyphenCollection[1] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |  %-*s |  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 6, curr->universityColumns[4].c_str(), 5, curr->universityColumns[5].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniER") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[1] << endl << mainContent << subContent[1] << endl << hyphenCollection[0] << hyphenCollection[1] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |  %-*s |  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 6, curr->universityColumns[6].c_str(), 5, curr->universityColumns[7].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniFSR") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[2] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[8].c_str(), 6, curr->universityColumns[9].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniCPF") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[3] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[10].c_str(), 6, curr->universityColumns[11].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniIFR") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[4] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[12].c_str(), 6, curr->universityColumns[13].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniISR") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[5] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[14].c_str(), 6, curr->universityColumns[15].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniIRN") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[6] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[16].c_str(), 6, curr->universityColumns[17].c_str());
                curr = curr->next;
            }   
        } else if (userAction == "uniGER") {
            bubbleSort(userAction);
            cout << hyphenCollection[0] << hyphenCollection[2] << endl << mainContent << subContent[7] << endl << hyphenCollection[0] << hyphenCollection[2] << endl;
            while (curr != nullptr) {
                printf(" %-*s | %-*s |  %-*s | %-*s |   %-*s|  %-*s |\n", 4, curr->universityColumns[0].c_str(), 81, curr->universityColumns[1].c_str(), 3, curr->universityColumns[2].c_str(),24, curr->universityColumns[3].c_str(), 7, curr->universityColumns[18].c_str(), 6, curr->universityColumns[19].c_str());
                curr = curr->next;
            }   
        }
        cout << endl;   
    }

    void bubbleSort(string userAction) {
        if (head == nullptr || head->next == nullptr)
            return;

        bool swapped;
        UniNode* ptr1;
        UniNode* lptr = nullptr;

        int indexToCheck, firstCheck, secondCheck;
        if (userAction == "uniName" || userAction == "favorite") {
            if (userAction == "uniName") {
                indexToCheck = 1;
            } else if (userAction == "favorite") {
                indexToCheck = 21;
            }
            do
            {            
                swapped = false;
                ptr1 = head;

                while (ptr1->next != lptr)
                {
                    if (ptr1->universityColumns[indexToCheck] > ptr1->next->universityColumns[indexToCheck]) {
                        customSwap(ptr1, ptr1->next);
                        swapped = true;
                    }
                    ptr1 = ptr1->next;
                }
                lptr = ptr1;

            } while (swapped);
        } else if (userAction == "uniAR") {
            indexToCheck = 5;
        } else if (userAction == "uniER") {
            indexToCheck = 7;
        } else if (userAction == "uniFSR") {
            indexToCheck = 9;
        } else if (userAction == "uniCPF") {
            indexToCheck = 11;
        } else if (userAction == "uniIFR") {
            indexToCheck = 13;
        } else if (userAction == "uniISR") {
            indexToCheck = 15;
        } else if (userAction == "uniIRN") {
            indexToCheck = 17;
        } else if (userAction == "uniGER") {
            indexToCheck = 19;
        }

        if (userAction != "uniName") {
            do
            {            
                swapped = false;
                ptr1 = head;

                while (ptr1->next != lptr)
                {
                    if (ptr1->universityColumns[indexToCheck] == "-") {
                        firstCheck = 1000;
                    } else {
                        firstCheck = stoi(ptr1->universityColumns[indexToCheck]);
                    }
                    
                    if (ptr1->next->universityColumns[indexToCheck] == "-") {
                        secondCheck = 1000;
                    } else {
                        secondCheck = stoi(ptr1->next->universityColumns[indexToCheck]);
                    }
                    
                    if (firstCheck > secondCheck) {
                        customSwap(ptr1, ptr1->next);
                        swapped = true;
                    }
                    ptr1 = ptr1->next;
                }
                lptr = ptr1;
            } while (swapped);
        }
    }

    void customSwap(UniNode* a, UniNode* b)
    {
        for (int i = 0; i < 21; i++)
        {
            swap(a->universityColumns[i], b->universityColumns[i]);
        }
    }

    bool linearSearch(string stringToMatch, string userAction) {
        transform(stringToMatch.begin(), stringToMatch.end(), stringToMatch.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
        });

        UniNode *curr = head;
        while (curr != nullptr) { //visit each note
            string currName = curr->universityColumns[1];
            currName.erase(0, currName.find_first_not_of(" "));
            currName.erase(currName.find_last_not_of(" ") + 1); //remove extra spaces

            transform(currName.begin(), currName.end(), currName.begin(), [](unsigned char c) {
                return std::tolower(c);
            }); 

            if (currName == stringToMatch) { //check UniNode's name equals to target
                if (userAction == "display") {
                    displayDetail(curr->universityColumns);
                } else if (userAction == "update") {
                    int totalFavorite = stoi(curr->universityColumns[21]);
                    totalFavorite++;
                    curr->universityColumns[21] = to_string(totalFavorite);
                } else if (userAction == "decrement") {
                    int totalFavorite = stoi(curr->universityColumns[21]);
                    totalFavorite--;
                    curr->universityColumns[21] = to_string(totalFavorite);
                }
                return true; //found
            }
            curr = curr->next;
        }
        return false; //not found after all visits
    }

    void sortFavorite() {
        UniNode* curr = head;
        UniNode* minNode;

        while (curr != nullptr) {
            minNode = curr;
            UniNode* temp = curr->next;

            while (temp != nullptr) {
                if (temp->universityColumns[21] < minNode->universityColumns[21]) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            // Swap the data of current node and minimum node
            if (minNode != curr) {
                swap(curr->universityColumns, minNode->universityColumns);
            }

            curr = curr->next;
        }
    }

    void displayDetail(string uniDetail[21]) {
        system("cls");

        string hyphen(47, '-');
        string listCategories[9] = {"Academic Reputation", "Employer Reputation", "Faculty / Student Ratio", "Citations per Faculty", "International Faculty Ratio", "International Student Ratio", "International Research Network", "Employment Outcome", "Score Scaled"};

        printf("%-*s: #%s\n", 12, "Rank", uniDetail[0].c_str());
        printf("%-*s: %s\n", 12, "Institution", uniDetail[1].c_str());
        printf("%-*s: %s\n", 12, "Code", uniDetail[2].c_str());
        printf("%-*s: %s\n\n", 12, "Location", uniDetail[3].c_str());

        cout << "|" << hyphen << "|\n" << "|" <<  " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=| Score | Rank |\n";
        for (int i = 0, j = 4 ; i < 8 ; i++, j+=2) {
            printf("| %-*s: %-*s| %-*s|\n", 31, listCategories[i].c_str(), 6, uniDetail[j].c_str(), 5, uniDetail[j+1].c_str());
        }
        printf("| %-*s: %-*s|      |\n", 31, listCategories[8].c_str(), 6, uniDetail[20].c_str());
        cout << "|" << hyphen << "|\n\n";
    }

    void topFavorite() {
        UniNode *curr = head;
        int total = 0;
        string hyphen(108, '-');

        cout << hyphen << endl << " RANK |                                    Institution                                    | Total Favorite |\n" << hyphen << endl;

        while (curr != nullptr && total < 10)
        {
            if (stoi(curr->universityColumns[21]) > 0) {
                printf(" %-*s| %-*s|      %-*s|\n", 5, curr->universityColumns[0].c_str(), 82, curr->universityColumns[1].c_str(), 10, curr->universityColumns[21].c_str());
                total++;
            }
            curr = curr->next;
        }
        cout << hyphen << endl << endl;
    }
};