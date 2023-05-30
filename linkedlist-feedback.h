
#include <iostream>
#include <algorithm>
using namespace std;

struct NodeFeedback
{
    string feedbackDetail[3];
    NodeFeedback *next; // link pointer
    NodeFeedback *prev;
};

struct LinkedListFeedback
{
    NodeFeedback *head;
    int size;

    LinkedListFeedback()
    {
        this->size = 0;
        this->head = nullptr;
    }

    void insertFeedback(string details[3])
    {
        NodeFeedback *newNode = new NodeFeedback;
        for (int i = 0; i < 3; i++) {
            newNode->feedbackDetail[i] = details[i];
        }
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            NodeFeedback *last = head;
            while (last->next != nullptr)
                last = last->next;
            last->next = newNode;
        }
        size++; 
    }


    int feedback_counter() {
        int cnt = 0;

        NodeFeedback *curr = head;
        while (curr != nullptr) {
            cnt++;
            curr = curr->next;
        }
        
        return cnt;
    }

    string* show()
    {
        int feedbackMaxAmount = feedback_counter();
        NodeFeedback* curr = head;
        NodeFeedback* lastNode = nullptr;
        string optChange;
        int currPage = 1;
        int currPosition = 0; // Variable to store the current position
        int dataChosen;

        int pageTotal = (feedbackMaxAmount + 9) / 10; // Calculate the total number of pages
        
        while (true)
        {
            int feedbackCnt = 0;
            // Display the current page of feedbacks
            cout << " ID | Sender              | Institution                                       | Feedback                                                         |\n" << endl;
            while (curr != nullptr && feedbackCnt < 10)
            {
                currPosition++; // Increment the current position
                printf(" %-*s| %-*s| %-*s| %-*s|\n", 3, to_string(currPosition).c_str(), 20, curr->feedbackDetail[0].c_str(), 50, curr->feedbackDetail[1].c_str(), 65, curr->feedbackDetail[2].c_str());
                lastNode = curr;
                curr = curr->next;
                feedbackCnt++;
            }

            cout << "\nPlease select a number to reply";
            if (currPage < pageTotal) // Check if there are more pages available
            {
                cout << "\nType \"n\" to go to the next page";
            }
            if (currPage > 1)
            {
                cout << "\nType \"p\" to go back to the previous page";
            }
            cout << "\n- Type \"x\" to exit";
            cout << "\nPlease enter an option: ";

            getline(cin, optChange);
            system("cls");
            try {
                dataChosen = stoi(optChange);
            }
            catch(const exception& e) {
                cout << "";
            }

            if (optChange.empty())
            {
                system("cls");
            }

            transform(optChange.begin(), optChange.end(), optChange.begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });

            if (optChange == "n" && currPage < pageTotal)
            {
                currPage++;
                int firstPosition = (currPage - 1) * 10;
                curr = head;
                for (int i = 0; i < firstPosition; i++)
                {
                    curr = curr->next;
                }
                lastNode = nullptr;
                currPosition = firstPosition; // Update the current position
            }
            else if (optChange == "p" && currPage > 1)
            {
                currPage--;
                int firstPosition = (currPage - 1) * 10;
                curr = head;
                for (int i = 0; i < firstPosition; i++)
                {
                    curr = curr->next;
                }
                lastNode = nullptr;
                currPosition = firstPosition; // Update the current position
                
            }
            else if (optChange == "x") {
                string* null_null = new string[4];
                null_null[3] = "NULL";
                return null_null;
                break;
            }
            else if (dataChosen > 0 && dataChosen <= feedbackMaxAmount)
            {
                string* reply = replyFeedback(dataChosen);
                return reply;
                break;
            }
            else
            {
                system("cls");
                cout << "Invalid input. Please try again." << endl << endl;
            }
        }
    }

    string* replyFeedback(int dataNumber) {
        NodeFeedback *curr = head;
        dataNumber--;
        int numberNow = 0;
        string feedbackReply;

        while (curr != nullptr)
        {
            if (numberNow == dataNumber) {
                printf("Sended by    : %s\nInstitution : %s\nFeedback    : %s\n\n", curr->feedbackDetail[0].c_str(), curr->feedbackDetail[1].c_str(), curr->feedbackDetail[2].c_str());
                cout << "Enter feedback : ";
                getline(cin, feedbackReply);
                system("cls");

                string saveData[3];
                copy(curr->feedbackDetail, curr->feedbackDetail + 3, saveData);
                deleteNode(curr->feedbackDetail[0]);
                // deleteLast();
                return insertReplyFeedback(saveData, feedbackReply);
                break;           
            }
            numberNow++;
            curr = curr->next;
        }
    }

    string* insertReplyFeedback(string detail[3], string reply){
        string* arrayData = new string[4];
        arrayData[0] = detail[0];
        arrayData[1] = detail[1];
        arrayData[2] = detail[2];
        arrayData[3] = reply;
        return arrayData;
    }

    void deleteNode(string nameToDelete)
    {
        transform(nameToDelete.begin(), nameToDelete.end(), nameToDelete.begin(), [](unsigned char c) { //convert to lowercase
            return tolower(c);
        });

        NodeFeedback *curr = head;
        NodeFeedback *prev = nullptr;

        // Find the node to delete
        while (curr != nullptr && curr->feedbackDetail[0] != nameToDelete)
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
        }
    }

    void deleteLast()
    {
        /* YOUR CODE GOES HERE */
        if (size > 0)
        {
            if (size == 1) // list has only one item
            {
                delete head;
                head = NULL;
            }
            else
            {
                NodeFeedback *beforeLast = head;
                while (beforeLast->next->next != NULL) // traverse
                    beforeLast = beforeLast->next;
                delete beforeLast->next;
                beforeLast->next = NULL;
            }
            size--;
        }
    }

    void selectionSort() {
        NodeFeedback* curr = head;
        NodeFeedback* minNode;

        while (curr != nullptr) {
            minNode = curr;
            NodeFeedback* temp = curr->next;

            while (temp != nullptr) {
                if (temp->feedbackDetail[0] < minNode->feedbackDetail[0]) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            // Swap the data of current node and minimum node
            if (minNode != curr) {
                swap(curr->feedbackDetail, minNode->feedbackDetail);
            }

            curr = curr->next;
        }
    }

    bool binarySearch(string username, string password, string userAction) {
        NodeFeedback *start = head;
        NodeFeedback *end = nullptr;

        selectionSort();
        
        while (start != end) {
            NodeFeedback *mid = start;
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
            transform(mid->feedbackDetail[0].begin(), mid->feedbackDetail[0].end(), mid->feedbackDetail[0].begin(), [](unsigned char c) { //convert to lowercase
                return tolower(c);
            });
            
            // Check if the middle element matches the target
            if (mid->feedbackDetail[0] == username && mid->feedbackDetail[1] == password) {
                return true;  // Found
            }
            
            // Adjust the start and end pointers based on the comparison
            if (mid->feedbackDetail[0] < username) {
                start = mid->next;
            } else {
                end = mid;
            }
        }
        return false;  // Not found after all iterations
    }
};