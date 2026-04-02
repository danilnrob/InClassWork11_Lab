#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

public:
    NodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        ListNode* n = new ListNode{id, name, head};
        head = n;
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return;
        if (prev) prev->next = curr->next;
        else head = curr->next;
        delete curr;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    // TODO: Implement destructor, copy constructor, operator=
    // (Part A deliverable)
 
    // Destructor: clean up all nodes and frees memory
    ~NodeList() {
        ListNode* curr = head;
        while (curr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        count = 0;
    }

    // Copy constructor: creates a deep copy of the list
   NodeList(const NodeList& other) : head(nullptr), count(0) {
        if (!other.head) return;

        // Copy first node
        head = new ListNode{other.head->id, other.head->name, nullptr};
        ListNode* currNew = head;
        ListNode* currOld = other.head->next;

        // Copy rest
        while (currOld) {
            currNew->next = new ListNode{currOld->id, currOld->name, nullptr};
            currNew = currNew->next;
            currOld = currOld->next;
        }

        count = other.count;
    }

    // Assignment operator: handles setting one list equal to another, with an '=' sign
    NodeList& operator=(const NodeList& other) {
        if (this == &other) return *this; // self-assignment check

        // First: clean current list
        ListNode* curr = head;
        while (curr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }

        head = nullptr;
        count = 0;

        // Then: deep copy (same logic as copy constructor)
        if (!other.head) return *this;

        head = new ListNode{other.head->id, other.head->name, nullptr};
        ListNode* currNew = head;
        ListNode* currOld = other.head->next;

        while (currOld) {
            currNew->next = new ListNode{currOld->id, currOld->name, nullptr};
            currNew = currNew->next;
            currOld = currOld->next;
        }

        count = other.count;

        return *this;
    }
};

int main() {
    NodeList list;
    list.addNode(1, "Cat");
    list.addNode(2, "Dog");
    list.addNode(3, "Birby");

    cout << "Original list: ";
    list.display();

    list.removeNode(2); // Remove Dog
    cout << "After removing Dog: ";
    list.display();

    return 0;
}