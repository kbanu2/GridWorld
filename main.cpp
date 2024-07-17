#include <iostream>
using namespace std;


class LinkedList{
  public:
    struct Node{
      int id;
      Node* next, *prev;
    };

    LinkedList();
    void pushFront(int id);
    void pushBack(int id);
    bool popFront(int& id);
    bool popBack(int& id);
    void remove(int id);
    int length();
    void print();
  private:
    Node* head, *tail;
    int size;
};

LinkedList::LinkedList(){
  head = nullptr;
  tail = nullptr;
  size = 0;
}

void LinkedList::pushFront(int id){
  Node* node = new Node();
  node->id = id;
  node->prev = nullptr;
  size++;

  if (head == nullptr){
    node->next = nullptr;
    head = node;
    tail = node;
    return;
  }

  head->prev = node;
  node->next = head;
  head = node;
}

void LinkedList::pushBack(int id){
  Node* node = new Node();
  node->id = id;
  node->next = nullptr;
  size++;

  if (head == nullptr){
    node->prev = nullptr;
    head = node;
    tail = node;
  }

  tail->next = node;
  node->prev = tail;
  tail = node;
}

bool LinkedList::popFront(int& id){
  if (head == nullptr)
    return false;

  id = head->id;
  if (head->next == nullptr){ //single node
    delete(head);
    head = nullptr;
    tail = nullptr;
  }
  else{
    Node* temp = head;
    head = head->next;
    head->prev = nullptr;
    delete(temp);
  }
  size--;
  return true;
}

bool LinkedList::popBack(int& id){
  if (head == nullptr)
    return false;

  id = tail->id;
  if (head->next == nullptr){ //single node
    delete(head);
    head = nullptr;
    tail = nullptr;
  }
  else{
    Node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete(temp);
  }
  size--;
  return true;
}

int LinkedList::length(){
  return size;
}

void LinkedList::print(){
    Node* temp = head;

    while (temp != nullptr){
        cout << temp->id << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main(){
    LinkedList l;
    int res;
    l.pushBack(0);
    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);
    l.pushBack(4);
    l.pushBack(5);
    l.print();
    l.popFront(res);
    cout << res << endl;
    l.popBack(res);
    cout << res << endl;
    l.pushBack(1);
    l.print();
}

