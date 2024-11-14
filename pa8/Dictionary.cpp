/*
Cole Schreiner
caschrei
pa8
Dictionary.cpp
*/

#include "Dictionary.h"
#include <stdexcept>
#include <iostream>
#include <string>

#define RED -1
#define BLACK -2

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

// Creates new Dictionary in the empty state.
Dictionary::Dictionary()
{
    nil = new Node("NULL", -100);
    root = nil;
    current = nil;
    num_pairs = 0;

    nil->color = BLACK;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("NULL", -100);
    root = nil;
    current = nil;
    num_pairs = 0;

    nil->color = BLACK;
    preOrderCopy(D.root, D.nil);
}

// Destructor

Dictionary::~Dictionary()
{
    // clear();
    postOrderDelete(root);
    delete nil;
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
        if (R->key != "NULL")
        {
            s += R->key + " : " + std::to_string(R->val) + "\n";
        }
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.
void Dictionary::preOrderString(std::string &s, Node *R) const
{
    if (R == nullptr)
    {
        return;
    }
    if (R != nil)
    {
        if (R->color == RED)
        {
            s += R->key + " (RED)\n";
        }
        else
        {
            s += R->key + "\n";
        }
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node *M)
{
    if (M == nullptr || M == nil)
    {
        return;
    }
    setValue(M->key, M->val);
    BST_insert(M->left);
    BST_insert(M->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R == N)
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
    if (R != nil && R != nullptr)
    {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        R = nullptr;
        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    if (R == nil)
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
    if (R == nil)
    {
        return nil;
    }
    while (R->left != nil)
    {
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R)
{
    if (R == nullptr || R == nil)
    {
        return nil;
    }
    Node *N = R;
    while (N->right != nil)
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
    if (N->right != nil)
    {
        return findMin(N->right);
    }
    Node *P = N->parent;
    while (P != nil && N == P->right)
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
    if (N->left != nil)
    {
        return findMax(N->left);
    }
    Node *P = N->parent;
    while (P != nil && N == P->left)
    {
        N = P;
        P = P->parent;
    }
    return P;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node *N)
{
    /* Psuedo code:
    // set y
   y = x.right

   // turn y's left subtree into x's right subtree
   x.right = y.left
   if y.left != T.nil     // not necessary if using sentinal nil node
      y.left.parent = x

   // link y's parent to x
   y.parent = x.parent
   if x.parent == T.nil
      T.root = y
   else if x == x.parent.left
      x.parent.left = y
   else
      x.parent.right = y

   // put x on y's left
   y.left = x
   x.parent = y */

    Node *y = N->right;
    N->right = y->left;
    if (y->left != nil)
    {
        y->left->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil)
    {
        root = y;
    }
    else if (N == N->parent->left)
    {
        N->parent->left = y;
    }
    else
    {
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node *N)
{
    /*
    Pseudo code:
    // set y
       y = x.left

       // turn y's right subtree into x's left subtree
       x.left = y.right
       if y.right != T.nil  // not necessary if using sentinal nil node
          y.right.parent = x

       // link y's parent to x
       y.parent = x.parent
       if x.parent == T.nil
          T.root = y
       else if x == x.parent.right
          x.parent.right = y
       else
          x.parent.left = y

       // put x on y's right
       y.right = x
       x.parent = y
     */
    Node *y = N->left;
    N->left = y->right;
    if (y->right != nil)
    {
        y->right->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil)
    {
        root = y;
    }
    else if (N == N->parent->right)
    {
        N->parent->right = y;
    }
    else
    {
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node *N)
{
    /*
    Psuedo code:
    while z.parent.color == RED
          if z.parent == z.parent.parent.left
             y = z.parent.parent.right
             if y.color == RED
                z.parent.color = BLACK              // case 1
                y.color = BLACK                     // case 1
                z.parent.parent.color = RED         // case 1
                z = z.parent.parent                 // case 1
             else
                if z == z.parent.right
                   z = z.parent                     // case 2
                   LeftRotate(T, z)                 // case 2
                z.parent.color = BLACK              // case 3
                z.parent.parent.color = RED         // case 3
                RightRotate(T, z.parent.parent)     // case 3
          else
             y = z.parent.parent.left
             if y.color == RED
                z.parent.color = BLACK              // case 4
                y.color = BLACK                     // case 4
                z.parent.parent.color = RED         // case 4
                z = z.parent.parent                 // case 4
             else
                if z == z.parent.left
                   z = z.parent                     // case 5
                   RightRotate(T, z)                // case 5
                z.parent.color = BLACK              // case 6
                z.parent.parent.color = RED         // case 6
                LeftRotate(T, z.parent.parent)      // case 6
       T.root.color = BLACK
     */
    while (N->parent->color == RED)
    {
        if (N->parent == N->parent->parent->left)
        {
            Node *y = N->parent->parent->right;
            if (y->color == RED)
            {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else
            {
                if (N == N->parent->right)
                {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else
        {
            Node *y = N->parent->parent->left;
            if (y->color == RED)
            {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else
            {
                if (N == N->parent->left)
                {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node *u, Node *v)
{
    /*
    Psuedo code:
    if u.parent == T.nil
          T.root = v
       else if u == u.parent.left
          u.parent.left = v
       else
          u.parent.right = v
       v.parent = u.parent
     */
    if (u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node *N)
{
    /*
    Psuedo code:
    while x != T.root and x.color == BLACK
          if x == x.parent.left
             w = x.parent.right
             if w.color == RED
                w.color = BLACK                        // case 1
                x.parent.color = RED                   // case 1
                LeftRotate(T, x.parent)                // case 1
                w = x.parent.right                     // case 1
             if w.left.color == BLACK and w.right.color == BLACK
                w.color = RED                          // case 2
                x = x.parent                           // case 2
             else
                if w.right.color == BLACK
                   w.left.color = BLACK                // case 3
                   w.color = RED                       // case 3
                   RightRotate(T, w)                   // case 3
                   w = x.parent.right                  // case 3
                w.color = x.parent.color               // case 4
                x.parent.color = BLACK                 // case 4
                w.right.color = BLACK                  // case 4
                LeftRotate(T, x.parent)                // case 4
                x = T.root                             // case 4
          else
             w = x.parent.left
             if w.color == RED
                w.color = BLACK                        // case 5
                x.parent.color = RED                   // case 5
                RightRotate(T, x.parent)               // case 5
                w = x.parent.left                      // case 5
             if w.right.color == BLACK and w.left.color == BLACK
                w.color = RED                          // case 6
                x = x.parent                           // case 6
             else
                if w.left.color == BLACK
                   w.right.color = BLACK               // case 7
                   w.color = RED                       // case 7
                   LeftRotate(T, w)                    // case 7
                   w = x.parent.left                   // case 7
                w.color = x.parent.color               // case 8
                x.parent.color = BLACK                 // case 8
                w.left.color = BLACK                   // case 8
                RightRotate(T, x.parent)               // case 8
                x = T.root                             // case 8
       x.color = BLACK
     */
    while (N != root && N->color == BLACK)
    {
        if (N == N->parent->left)
        {
            Node *w = N->parent->right;
            // case 1
            if (w->color == RED)
            {
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            // case 2
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                N = N->parent;
            }
            else
            {
                // case 3
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                // case 4
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else
        {
            Node *w = N->parent->left;
            // case 5
            if (w->color == RED)
            {
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            // case 6
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                N = N->parent;
            }
            else
            {
                // case 7
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                // case 8
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
// Helper function for remove(). Deletes the Node N from the tree.
void Dictionary::RB_Delete(Node *N)
{
    /*
    Psuedo code:
    y = z
       y_original_color = y.color
       if z.left == T.nil
          x = z.right
          RB_Transplant(T, z, z.right)
       else if z.right == T.nil
          x = z.left
          RB_Transplant(T, z, z.left)
       else
          y = TreeMinimum(z.right)
          y_original_color = y.color
          x = y.right
          if y.parent == z
             x.parent = y
          else
             RB_Transplant(T, y, y.right)
             y.right = z.right
             y.right.parent = y
          RB_Transplant(T, z, y)
          y.left = z.left
          y.left.parent = y
          y.color = z.color
       if y_original_color == BLACK
          RB_DeleteFixUp(T, x)
     */
    Node *y = N;
    int y_original_color = y->color;
    Node *x;
    if (N->left == nil)
    {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil)
    {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else
    {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N)
        {
            x->parent = y;
        }
        else
        {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == BLACK)
    {
        RB_DeleteFixUp(x);
    }
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
    if (N == nil)
    {
        return false;
    }
    return true;
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
    if (current == nullptr || current == nil)
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
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v)
{
    Node *N = search(root, k);
    if (N == nil)
    {
        Node *Z = new Node(k, v);
        Node *Y = nil;
        Node *X = root;
        while (X != nil)
        {
            Y = X;
            if (Z->key < X->key)
            {
                X = X->left;
            }
            else
            {
                X = X->right;
            }
        }
        Z->parent = Y;
        if (Y == nil)
        {
            root = Z;
        }
        else if (Z->key < Y->key)
        {
            Y->left = Z;
        }
        else
        {
            Y->right = Z;
        }
        Z->left = nil;
        Z->right = nil;
        Z->color = RED;
        RB_InsertFixUp(Z);
        num_pairs++;
    }
    else
    {
        N->val = v;
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
    if (S == current)
    {
        current = nil;
    }
    RB_Delete(S);
    num_pairs--;
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
// Returns a string consisting of all keys in this Dictionary. The key order is
// given by a pre-order tree walk. The keys stored in black Nodes will appear in
// the returned string as "key\n", and the keys stored in red Nodes will appear
// as "key (RED)\n".  The output of this function is demonstrated in
// /Examples/pa8/DictionaryClient-out.
std::string Dictionary::pre_string() const
{
    Dictionary D(*this);
    std::string s = "";
    preOrderString(s, root);
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
