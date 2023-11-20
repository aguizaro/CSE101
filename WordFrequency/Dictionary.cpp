//-----------------------------------------------------------------------------
// Dictionary.cpp by Antonio Guizar Orozco
// PA8
// CruzID: aguizaro
//
// Implementation file for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<sstream>
#include"Dictionary.h"

//Macros used for Red/Black coloring of Node Obj
#define RED 0
#define BLACK 1
#define UNDEF -1

// Class Constructors & Destructors ----------------------------------------

// Creates new Node with key k and value v
Dictionary::Node::Node(keyType k, valType v){
    key= k;
    val= v;
    parent = left = right= nullptr;
    color= UNDEF;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    Node* N= new Node("0", 0);
    nil= current= root= N;
    root->parent= root->left= root->right= nil;
    num_pairs= 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    Node* N= new Node("0", 0);
    N->color= BLACK;
    nil= current= root= N;
    root->parent= root->left= root->right= nil;
    num_pairs= 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    Node* N= search(root, k);
    return ( N != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (!contains(k))
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    Node* N= search(root, k);
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (current == nil) throw std::logic_error("Dictionary: currentKey(): current undefined");
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (current == nil) throw std::logic_error("Dictionary: currentVal(): current undefined");
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    num_pairs= 0;
    root= current= nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* y= nil;
    Node* x= root;
    int comp;
    while(x != nil){
        y= x;
        comp= x->key.compare(k);
        if (comp > 0) x= x->left;
        else if (comp < 0) x= x->right;
        else{ x->val= v; return;} //overwrite current val and return
    }
    Node* N= new Node(k, v);
    N->parent= y;
    N->left= nil;
    N->right= nil;
    N->color= RED;
    if (y == nil) root= N;
    else if (y->key.compare(k) > 0) y->left= N;
    else y->right= N;
    RB_InsertFixUp(N);
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node* N= search(root, k);
    if (N == nil) throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    if (N == current) current= nil;
    RB_Delete(N);
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if (num_pairs> 0)
        current= findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if (num_pairs > 0)
        current= findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (current == nil) throw std::logic_error("Dictionary: next(): current undefined");
    current= findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (current == nil) throw std::logic_error("Dictionary: prev(): current undefined");
    current= findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    if (num_pairs == 0) return "";
    std::string s;
    inOrderString(s, root);
    return s.substr(1) + "\n";
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s + "\n";
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return (this->to_string() == D.to_string());
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    clear();
    preOrderCopy(D.root, D.nil);
    return *this;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R, std::string delim) const{
    if (R != nil){
        inOrderString(s, R->left, delim);
        delim= "\n";
        s+= delim;
        s+= R->key;
        s+= " : ";
        s+= std::to_string(R->val);
        inOrderString(s, R->right, delim);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary::preOrderString(std::string& s, Node* R, std::string delim) const{
    if (R != nil){
        s+= delim;
        s+= R->key;
        if (R->color == RED) s+= " (RED)";
        delim= "\n";
        preOrderString(s, R->left, delim);
        preOrderString(s, R->right, delim);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){
    Node *y= nil, *x= root;
    int diff;
    while (x != nil){
        diff= x->key.compare(M->key);
        y= x;
        if (diff > 0) x= x->left;
        else if (diff < 0) x= x->right;
        else{ x->val= M->val; return;}
    }
    Node* N= new Node(M->key, M->val);
    N->parent= y;
    N->left = N->right= nil;
    N->color= M->color;
    if (y == nil) root= N;
    else if (y->key.compare(M->key) > 0) y->left= N;
    else y->right= N;
    num_pairs++;
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R == N) return;
    BST_insert(R);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R == nil) return;
    if (R->left != nil) postOrderDelete(R->left);
    if (R->right != nil)postOrderDelete(R->right);
    delete R;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (R == nil || R->key == k){
        return R;
    }else if (R->key.compare(k) > 0){return search(R->left, k);}
    else{return search(R->right, k);}
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if (R == nil) return nil;
    while(R->left != nil)
        R= R->left;
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if (R == nil) return nil;
    while(R->right != nil){
        R= R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == nil || N == this->findMax(root)) return nil;
    if (N->right != nil) return findMin(N->right);
    Node* y= N->parent;
    while(y != nil && N == y->right){
        N= y;
        y= y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == nil || N == this->findMin(root)) return nil;
    if (N->left != nil) return findMax(N->left);
    Node* y= N->parent;
    while(y != nil && N == y->left){
        N= y;
        y= y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* y= N->right; //set y
    //turn y's left subtree into N's right subtree
    N->right= y->left;
    if (y->left != nil) y->left->parent= N;
    //link y's parent to N
    y->parent= N->parent;
    if (N->parent == nil) root= y;
    else if (N == N->parent->left) N->parent->left= y;
    else N->parent->right= y;
    //put N on y's left
    y->left= N;
    N->parent= y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node* y= N->left; //set y
    //turn y's right subtree into N's left subtree
    N->left= y->right;
    if (y->right != nil) y->right->parent= N;
    //link y's parent to N
    y->parent= N->parent;
    if (N->parent == nil) root= y;
    else if (N == N->parent->right) N->parent->right= y;
    else N->parent->left= y;
    //put N on y's right 
    y->right= N;
    N->parent= y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    Node* y;
    while (N->parent->color == RED){
        if (N->parent == N->parent->parent->left){
            y= N->parent->parent->right;
            if (y->color == RED){
                N->parent->color= BLACK;                // case 1
                y->color= BLACK;                        // case 1
                N->parent->parent->color= RED;          // case 1
                N= N->parent->parent;                   // case 1
            }else{
                if(N == N->parent->right){
                    N= N->parent;                       // case 2
                    LeftRotate(N);                      // case 2
                }
                N->parent->color = BLACK;               // case 3
                N->parent->parent->color= RED;          // case 3
                RightRotate(N->parent->parent);         // case 3
            }
        }else{
            y= N->parent->parent->left;
            if (y->color == RED){
                N->parent->color= BLACK;                // case 4
                y->color= BLACK;                        // case 4
                N->parent->parent->color= RED;          // case 4
                N= N->parent->parent;                   // case 4
            }else{
                if (N == N->parent->left){
                    N = N->parent;                      // case 5
                    RightRotate(N);                     // case 5
                }
                N->parent->color= BLACK;                // case 6
                N->parent->parent->color= RED;          // case 6
                LeftRotate(N->parent->parent);          // case 6
            }
        }
    }
    root->color= BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if (u->parent == nil) root= v;
    else if (u == u->parent->left) u->parent->left= v;
    else u->parent->right= v;
    v->parent= u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* w;
    while (N != root && N->color == BLACK){
        if (N == N->parent->left){
            w= N->parent->right;
            if (w->color == RED){
                w->color= BLACK;                                        // case 1
                N->parent->color= RED;                                  // case 1
                LeftRotate(N->parent);                                  // case 1
                w= N->parent->right;                                    // case 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
                w->color= RED;                                          // case 2
                N= N->parent;                                           // case 2
            }else{
                if (w->right->color == BLACK){
                    w->left->color= BLACK;                              // case 3
                    w->color= RED;                                      // case 3
                    RightRotate(w);                                     // case 3
                    w= N->parent->right;                                // case 3
                }
                w->color= N->parent->color;                             // case 4
                N->parent->color= BLACK;                                // case 4
                w->right->color= BLACK;                                 // case 4
                LeftRotate(N->parent);                                  // case 4
                N= root;                                                // case 4
            }
        }else{
            w= N->parent->left;
            if (w->color == RED){
                w->color= BLACK;                                        // case 5
                N->parent->color= RED;                                  // case 5
                RightRotate(N->parent);                                 // case 5
                w= N->parent->left;                                     // case 5
            }
            if (w->right->color == BLACK && w->left->color == BLACK){
                w->color= RED;                                          // case 6
                N= N->parent;                                           // case 6
            }else{
                if (w->left->color == BLACK){
                    w->right->color= BLACK;                             // case 7
                    w->color= RED;                                      // case 7
                    LeftRotate(w);                                      // case 7
                    w= N->parent->left;                                 // case 7
                }
                w->color= N->parent->color;                             // case 8
                N->parent->color= BLACK;                                // case 8
                w->left->color= BLACK;                                  // case 8
                RightRotate(N->parent);                                 // case 8
                N= root;                                                // case 8
            }
        }
    }
    N->color= BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node *x, *y= N;
    int y_orig_color= y->color;
    if (N->left == nil){
        x= N->right;
        RB_Transplant(N, N->right);
    }else if (N->right == nil){
        x= N->left;
        RB_Transplant(N, N->left);
    }else{
        y= findMin(N->right);
        y_orig_color= y->color;
        x= y->right;
        if (y->parent == N) x->parent= y;
        else{ 
            RB_Transplant(y, y->right);
            y->right= N->right;
            y->right->parent= y;
        }
        RB_Transplant(N, y);
        y->left= N->left;
        y->left->parent= y;
        y->color= N->color;
    }
    delete N;
    if (y_orig_color == BLACK) RB_DeleteFixUp(x);
}