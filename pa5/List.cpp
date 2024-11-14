/*
Cole Schreiner
caschrei
pa5
List.cpp
*/


// #include <iostream>
// #include <string>
// #include <stdexcept>

// using namespace std;

#include "List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x)
{
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List()
{
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List &L)
{
    // make this an empty List
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into this List
    Node *N = L.frontDummy->next;
    while (N != L.backDummy)
    {
        insertBefore(N->data);
        N = N->next;
    }
    // std::cout << "***called copy constructor: " << this->to_string() << std::endl;
}

// Destructor
List::~List()
{
    clear();
    delete frontDummy;
    delete backDummy;
    // frontDummy = new Node(0);
    // backDummy = new Node(0);
    // frontDummy->next = backDummy;
    // backDummy->prev = frontDummy;
    // beforeCursor = frontDummy;
    // afterCursor = backDummy;
    // pos_cursor = 0;
    // num_elements = 0;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const
{
    return (num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const
{
    if (length() <= 0)
    {
        throw std::length_error("List: front(): empty List");
    }
    return (frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const
{
    if (length() <= 0)
    {
        throw std::length_error("List: back(): empty List");
    }
    return (backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const
{
    return (pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const
{
    if (position() >= length())
    {
        throw std::range_error("List: peekNext(): position() >= length()");
    }
    return (afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const
{
    if (position() <= 0)
    {
        throw std::range_error("List: peekPrev(): position() <= 0");
    }
    return (beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{
    moveFront();
    while (length() > 0)
    {
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront()
{
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack()
{
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext()
{
    if (position() >= length())
    {
        throw std::range_error("List: moveNext(): position() >= length()");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return (beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev()
{
    if (position() <= 0)
    {
        throw std::range_error("List: movePrev(): position() <= 0");
        // std::cerr << "moveNext() pre-condition: position()>0" << std::endl;
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return (afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x)
{
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    afterCursor = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x)
{
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x)
{
    if (position() >= length())
    {
        throw std::range_error("List: setAfter(): position() >= length()");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x)
{
    if (position() <= 0)
    {
        throw std::range_error("List: setBefore(): position() <= 0");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter()
{
    if (position() >= length())
    {
        throw std::range_error("List: eraseAfter(): position() >= length()");
    }
    Node *N = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete N;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore()
{
    if (position() <= 0)
    {
        throw std::range_error("List: eraseBefore(): position() <= 0");
    }
    Node *N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete N;
    pos_cursor--;
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x)
{
    while (afterCursor != backDummy)
    {
        moveNext();
        if (beforeCursor->data == x)
        {
            return position();
        }
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x)
{
    while (beforeCursor != frontDummy)
    {
        movePrev();
        if (afterCursor->data == x)
        {
            return position();
        }
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    Node* current = frontDummy->next;
    int outside = 0;

    while (current != backDummy) {
        int data_i = current->data;
        Node* next_node = current->next;
        int inside = outside + 1;

        while (next_node != backDummy) {
            int data_j = next_node->data;
            Node* before = next_node->prev;
            Node* after = next_node->next;
            Node* to_erase = next_node;
            next_node = after;

            if (data_j == data_i) {
                before->next = after;
                after->prev = before;
                delete to_erase;
                num_elements--;

                if (inside <= pos_cursor) {
                    pos_cursor--;
                }
            }
            inside++;
        }
        outside++;
        current = current->next;
    }
    int pos = pos_cursor;
    
    for (moveFront(); position() != pos; moveNext()) {
        continue;
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const
{
    List Concat = List(L);
    Node *N = backDummy->prev;
    for (Concat.moveFront(); N != frontDummy; N = N->prev)
    {
        Concat.insertAfter(N->data);
    }
    return Concat;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const
{
    std::string s = "(";
    Node *N = frontDummy->next;
    while (N != backDummy)
    {
        s += std::to_string(N->data);
        if (N->next != backDummy)
        {
            s += ", ";
        }
        N = N->next;
    }
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const
{
    if (length() != R.length())
    {
        return false;
    }
    Node *I = frontDummy->next;
    Node *J = R.frontDummy->next;
    while (I != backDummy)
    {
        if (I->data != J->data)
        {
            return false;
        }
        I = I->next;
        J = J->next;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream &operator<<(std::ostream &stream, const List &L)
{
    stream << L.to_string();
    return stream;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List &A, const List &B)
{
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L)
{
    if (this != &L)
    {
        clear();
        Node *N = L.frontDummy->next;
        while (N != L.backDummy)
        {
            insertBefore(N->data);
            N = N->next;
        }
    }
    return *this;
}
