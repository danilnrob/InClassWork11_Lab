#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx = nullptr)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head));
        count++;
    }

    void removeNode(int id) {
        if (!head) return;

        // remove head
        if (head->id == id) {
            head = move(head->next);
            count--;
            return;
        }

        SmartListNode* curr = head.get();

        while (curr->next && curr->next->id != id) {
            curr = curr->next.get();
        }

        if (curr->next) {
            curr->next = move(curr->next->next);
            count--;
        }
    }

    void display() const {
        SmartListNode* curr = head.get();
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null" << endl;
    }

    int getCount() const {
        return count;
    }

    // No destructor needed! No copy constructor needed!
    // unique_ptr handles all cleanup automatically.
};

/*
 - Part A requires more lines of code to efficiently manage memory, because part B's use of smart pointers automatically
   manages the memory, like in part A but simpler. We no longer had to define a destructor, copy constructor, or 
   assignment operator. Part A totals to 116 lines (over 50 lines for the memory management), while Part B takes just 66 lines in total.
 - Part A is more risky because manually writing this memory management is error-prone while using a smart pointer
   should not cause the same memory leaks. 
 - Part A we utilized the Rule of Three, while in Part B we did not have to because we used a smart pointer instead. This
   means we do not need to use the Rule of Three at all. 
*/