/*
Cole Schreiner
caschrei
pa7
Dictionary.cpp
*/


#include "Dictionary.h"
#include <stdexcept>
#include <iostream>
#include <string>

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// Creates new Dictionary in the empty state.
Dictionary::Dictionary()
{
    nil = new Node("NIL", 0);
    root = nullptr;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("NIL", 0);
    root = nullptr;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, nullptr);
}

// Destructor
Dictionary::~Dictionary()
{
    clear();
    delete nil;
    nil = nullptr;
    current = nullptr;
    root = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const
{
    if (R == nullptr)
    {
        return;
    }
    if (R != nil)
    {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const
{
    if (R == nullptr)
    {
        return;
    }
    if (R != nil)
    {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R == N || R == nil || R == nullptr)
    {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node *R)
{
    if (R == nullptr || R == nil)
    {
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    num_pairs--;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    if (R == nullptr)
    {
        return nil;
    }
    if (k == R->key)
    {
        return R;
    }
    if (k < R->key)
    {
        return search(R->left, k);
    }
    else
    {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R)
{
    if (R == nullptr)
    {
        return nil;
    }
    Node *N = R;
    while (N->left != nullptr)
    {
        N = N->left;
    }
    return N;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R)
{
    if (R == nullptr)
    {
        return nil;
    }
    Node *N = R;
    while (N->right != nullptr)
    {
        N = N->right;
    }
    return N;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *N)
{
    if (N->right != nullptr)
    {
        return findMin(N->right);
    }
    Node *P = N->parent;
    while (P != nullptr && N == P->right)
    {
        N = P;
        P = P->parent;
    }
    return P;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N)
{
    if (N->left != nullptr)
    {
        return findMax(N->left);
    }
    Node *P = N->parent;
    while (P != nullptr && N == P->left)
    {
        N = P;
        P = P->parent;
    }
    return P;
}

// Helper function to find the minimum value node in the tree rooted at root
Dictionary::Node *Dictionary::minValueNode(Node *node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != nullptr)
        current = current->left;

    return current;
}

// Helper function to delete the node with the given key and return the new root
Dictionary::Node *Dictionary::deleteNode(Node *root, keyType key)
{
    // base case
    if (root == nullptr)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        Node *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const
{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const
{
    Node *N = search(root, k);
    return N != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const
{
    Node *N = search(root, k);
    if (N == nil)
    {
        throw std::invalid_argument("getValue() called with non-existent key");
    }
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const
{
    if (current == nullptr)
    {
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const
{
    if (current == nil)
    {
        throw std::invalid_argument("currentKey() called with undefined current");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const
{
    if (current == nil)
    {
        throw std::invalid_argument("currentVal() called with undefined current");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear()
{
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v)
{
    Node *N = search(root, k);
    if (N != nil)
    {
        N->val = v;
        return;
    }
    else
    {
        N = new Node(k, v);
        num_pairs++;
    }
    Node *A = nullptr;
    Node *B = root;
    while (B != nullptr)
    {
        A = B;
        if (N->key < B->key)
        {
            B = B->left;
        }
        else
        {
            B = B->right;
        }
    }
    N->parent = A;
    if (A == nullptr)
    {
        root = N;
    }
    else if (N->key < A->key)
    {
        A->left = N;
    }
    else
    {
        A->right = N;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k)
{
    if (!contains(k))
    {
        throw std::invalid_argument("remove() called with non-existent key");
    }
    Node *S = search(root, k);
    if (S == nil || S == nullptr)
    {
        throw std::logic_error("remove() called with non-existent key");
    }
    if (S->key != "NIL" && S->val != -1)
    {
        if (current->key == k)
        {
            current = nullptr;
        }
        root = deleteNode(root, k);
        num_pairs--;
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin()
{
    if (root == nullptr)
    {
        return;
    }
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end()
{
    if (root == nullptr)
    {
        return;
    }
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("next() called with undefined current");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("prev() called with undefined current");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const
{
    Dictionary D(*this);
    std::string s = "";
    inOrderString(s, D.root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const
{
    Dictionary D(*this);
    std::string s = "";
    preOrderString(s, D.root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const
{
    if (this->size() != D.size())
    {
        return false;
    }
    std::string s1 = this->to_string();
    std::string s2 = D.to_string();
    return s1 == s2;
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    stream << D.to_string();
    return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B)
{
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D)
{
    if (this != &D)
    {
        Dictionary temp(D);
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
