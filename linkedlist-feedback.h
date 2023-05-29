/* lab5-linkedlist-singly.h */

#include <iostream>
using namespace std;

/**
 * with structure implementation...
 */
struct NodeFeedback
{
    string feedbackDetail[3];
    NodeFeedback *next; // link pointer
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

    int getSize()
    {
        return size;
    }

    int countFeedbacks() {
        int counter = 0;

        NodeFeedback *curr = head;
        while (curr != nullptr) {
            counter++;
            curr = curr->next;
        }
        
        return counter;
    }

    string* show()
    {
        int maxFeedback = countFeedbacks();
        NodeFeedback* curr = head;
        NodeFeedback* lastNode = nullptr;
        string hyphen(222, '-');
        string switchPage;
        int currentPage = 1;
        int currentPosition = 0; // Variable to store the current position
        int choosenData;

        int totalPages = (maxFeedback + 9) / 10; // Calculate the total number of pages
        
        while (true)
        {
            int feedbackCount = 0;

            // Display the current page of feedbacks
            cout << hyphen << endl << " ID |           Sender              |                                    Institution                                    |                                              Feedback                                              |\n" << hyphen << endl;
            while (curr != nullptr && feedbackCount < 10)
            {
                currentPosition++; // Increment the current position
                printf(" %-*s| %-*s| %-*s| %-*s|\n", 3, to_string(currentPosition).c_str(), 30, curr->feedbackDetail[0].c_str(), 82, curr->feedbackDetail[1].c_str(), 99, curr->feedbackDetail[2].c_str());
                lastNode = curr;
                curr = curr->next;
                feedbackCount++;
            }

            cout << hyphen << "\n\n- Type the corresponding ID to reply";
            if (currentPage < totalPages) // Check if there are more pages available
            {
                cout << "\n- Type \"z\" to go to the next page";
            }
            if (currentPage > 1)
            {
                cout << "\n- Type \"x\" to go back to the previous page";
            }
            cout << "\n- Type \"c\" to exit";
            cout << "\n\nWhat do you want to do: ";

            getline(cin, switchPage);
            // system("cls");
            try {
                choosenData = stoi(switchPage);
            }
            catch(const std::exception& e) {
                cout << "";
            }

            if (switchPage.empty())
            {
                system("cls");
                continue;
            }

            transform(switchPage.begin(), switchPage.end(), switchPage.begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
            });

            if (switchPage == "z" && currentPage < totalPages)
            {
                currentPage++;
                int startPosition = (currentPage - 1) * 10;
                curr = head;
                for (int i = 0; i < startPosition; i++)
                {
                    curr = curr->next;
                }
                lastNode = nullptr;
                currentPosition = startPosition; // Update the current position
            }
            else if (switchPage == "x" && currentPage > 1)
            {
                currentPage--;
                int startPosition = (currentPage - 1) * 10;
                curr = head;
                for (int i = 0; i < startPosition; i++)
                {
                    curr = curr->next;
                }
                lastNode = nullptr;
                currentPosition = startPosition; // Update the current position
            }
            else if (switchPage == "c") {
                string* empty = new string[4];
                empty[3] = "EmPtY";
                return empty;
            }
            else if (choosenData > 0 && choosenData <= maxFeedback)
            {
                string* reply = replyFeedback(choosenData);
                return reply;
            }
            else
            {
                cout << "Invalid input. Please try again." << endl;
            }
            system("cls");
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
                printf("Sended by   : %s\nInstitution : %s\nFeedback    : %s\n\n", curr->feedbackDetail[0].c_str(), curr->feedbackDetail[1].c_str(), curr->feedbackDetail[2].c_str());
                cout << "Reply feedback: ";
                getline(cin, feedbackReply);

                string saveData[3] = curr->feedbackDetail;
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
            return std::tolower(c);
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
                return std::tolower(c);
            });
            transform(mid->feedbackDetail[0].begin(), mid->feedbackDetail[0].end(), mid->feedbackDetail[0].begin(), [](unsigned char c) { //convert to lowercase
                return std::tolower(c);
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