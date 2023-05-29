/* lab5-linkedlist-singly.h */

#include <iostream>
using namespace std;
/**
 * with structure implementation...
 */
struct NodeReply
{
    string reply[4];   // input value
    NodeReply *next; // link pointer
};

struct LinkedListReply
{
    NodeReply *head;
    int size;

    LinkedListReply()
    {
        this->size = 0;
        this->head = nullptr;
    }

    /* Lab 5 - insert NodeReply */
    void insert(string data[4])
    {
        NodeReply *newNode = new NodeReply;
        newNode->reply[0] = data[0];
        newNode->reply[1] = data[1];
        newNode->reply[2] = data[2];
        newNode->reply[3] = data[3];
        newNode->next = head; //point to current firstNode
        head = newNode;       //update the head pointer to point to the newNode
        size++;
    }

    void feedbackReplyShow(string username) {
        NodeReply *curr = head;
        string hyphen(186,'-');
        
        cout << hyphen << endl << "                                     Institution                                    |                                              Feedback                                              |\n" << hyphen << endl;
        while (curr != nullptr) {
            if (curr->reply[0] == username) {
                printf(" %-*s| %-*s|\n", 83, curr->reply[1].c_str(), 99, curr->reply[3].c_str());
            }
            curr = curr->next;
        }
        
        cout << hyphen << endl << endl;
    }
};