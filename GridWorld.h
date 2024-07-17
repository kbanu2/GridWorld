#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>
using namespace std;
using std::vector;

struct Node{
  int row, column;
  int id;
  Node *next, *prev;
};

class LinkedList{
  public:
    LinkedList();
    Node* front() const;
    Node* back() const;
    Node* pushFront(int id, int row, int column);
    Node* pushBack(int id, int row, int column);
    bool popFront(int& id);
    bool popBack(int& id);
    void removeNodeFromMiddle(Node* node);
    int length() const;
  private:
    Node* head, *tail;
    int size;
};

LinkedList::LinkedList(){
  head = nullptr;
  tail = nullptr;
  size = 0;
}

Node* LinkedList::front() const{
  return head;
}

Node* LinkedList::back() const{
  return tail;
}

Node* LinkedList::pushFront(int id, int row, int column){
  Node* node = new Node();

  node->id = id;
  node->row = row;
  node->column = column;
  node->prev = nullptr;
  
  if (head == nullptr){
    node->next = nullptr;
    head = node;
    tail = node;
  }
  else{
    head->prev = node;
    node->next = head;
    head = node;
  }

  size++;
  return node;
}

Node* LinkedList::pushBack(int id, int row, int column){
  Node* node = new Node();

  node->id = id;
  node->row = row;
  node->column = column;
  node->next = nullptr;
  
  if (head == nullptr){
    node->prev = nullptr;
    head = node;
    tail = node;
  }
  else{
    tail->next = node;
    node->prev = tail;
    tail = node;
  }

  size++;
  return node;
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

void LinkedList::removeNodeFromMiddle(Node* node){
  node->prev->next = node->next;
  node->next->prev = node->prev;
  size--;
  delete(node);
}

int LinkedList::length() const{
  return size;
}

class GridWorld {

  private:
    vector<Node*> people;
    vector<vector<LinkedList> > world;
    LinkedList grave;
    int size;
    int rows, columns;
    int nextID;

    void removeNode(Node* node){
      int temp;

      if (world.at(node->row).at(node->column).front() == node){
        world.at(node->row).at(node->column).popFront(temp);
      }
      else if (world.at(node->row).at(node->column).back() == node){
        world.at(node->row).at(node->column).popBack(temp);
      }
      else{
        world.at(node->row).at(node->column).removeNodeFromMiddle(node);
      }
    }
  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows, unsigned ncols)   {
      rows = nrows;
      columns = ncols;
      size = 0;
      nextID = 0;
      people.resize(10, nullptr);

      world.resize(rows);
      for (int i = 0; i < rows; i++){
        world.at(i).resize(columns);
      }
    }

    ~GridWorld(){
      // your destructor code here.
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    bool birth(int row, int col, int &id){
      if (row > rows || row < 0 || col > columns || col < 0)
        return false;
      
      int newId;
      if (grave.popBack(newId)){ //Get next ID from grave
        id = newId;
        people.at(id) = world.at(row).at(col).pushFront(id, row, col);
      }
      else{
        while (nextID >= people.size())
          people.resize(people.size() * 2, nullptr);

        id = nextID++;
        people.at(id) = world.at(row).at(col).pushFront(id, row, col);
      }

      size++;
      return true;
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){
      if (personID >= people.size() || people.at(personID) == nullptr)
        return false;

      removeNode(people.at(personID));
      people.at(personID) = nullptr;
      grave.pushFront(personID, 0, 0);
      size--;

      return true;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
      if (id >= people.size() || people.at(id) == nullptr)
        return false;

      row = people.at(id)->row;
      col = people.at(id)->column;
      return true;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
      if (id >= people.size() || people.at(id) == nullptr)
        return false;
      
      removeNode(people.at(id));
      world.at(targetRow).at(targetCol).pushFront(id, targetRow, targetCol);
      return true;
    }

    /** func: members(r,c)
     *  returns a snapshot of the members of specified
     *    district as a vector (ordered by seniority).
     *  If invalid district, an empty vector is
     *    returned
     */
    std::vector<int> * members(int row, int col) const {
      vector<int>* result = new vector<int>;

      if (row > rows || row < 0 || col > columns || col < 0)
        return result;

      Node* tail = world.at(row).at(col).back();
      while (tail != nullptr){
        result->push_back(tail->id);
        tail = tail->prev;
      }

      return result;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return size;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return world.at(row).at(col).length();
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return rows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return columns;
    }
};

#endif
