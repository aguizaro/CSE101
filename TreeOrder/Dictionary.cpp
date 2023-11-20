//-----------------------------------------------------------------------------
// Dictionary.cpp by Antonio Guizar Orozco
// PA7
// CruzID: aguizaro
//
// Implementation file for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<sstream>
#include"Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

// Creates new Node with key k and value v
Dictionary::Node::Node(keyType k, valType v){
    key= k;
    val= v;
    parent = left = right= nullptr;
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
    //std::cout << "Searching for: "<< k << std::endl;
    Node* N= this->search(root, k);
    return ( N != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (!this->contains(k))
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    Node* N= this->search(root, k);
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
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node *y= nil, *x= root;
    int diff;
    while (x != nil){
        diff= x->key.compare(k);
        y= x;
        if (diff > 0) x= x->left;
        else if (diff < 0) x= x->right;
        else{ x->val= v; return;}
    }
    Node* N= new Node(k, v);
    N->parent= y;
    N->left = N->right= nil;
    if (y == nil) root= N;
    else if (y->key.compare(k) > 0) y->left= N;
    else y->right= N;
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node *y, *N= this->search(root, k);
    if (N == nil) throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");

    if (N == current) current= nil;
    if (N->left ==  nil){ this->transplant(N, N->right); delete N;}
    else if (N->right == nil){ this->transplant(N, N->left); delete N;}
    else{
        y= this->treeMinimum(N->right);
        if (y->parent != N){
            this->transplant(y, y->right);
            y->right= N->right;
            y->right->parent= y;
        }
        this->transplant(N, y);
        y->left= N->left;
        y->left->parent= y;

        delete N;

    }
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
    this->clear();
    this->preOrderCopy(D.root, D.nil);
    return *this;
}

// Helper Functions (Optional) ---------------------------------------------

// transplant()
// swaps node u with node v in the tree
void Dictionary::transplant(Node* u, Node* v){
    if (u->parent == nil) root= v;
    else if (u->parent->left == u) u->parent->left= v;
    else u->parent->right= v;
    if (v != nil) v->parent= u->parent;
}

// treeMinimum()
// returns the leftmost (smallest) key in the subtree T
Dictionary::Node* Dictionary::treeMinimum(Node* N){
    while (N->left != nil)
        N= N->left;
    return N;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R, std::string delimiter) const{
    if (R != nil){
        inOrderString(s, R->left, delimiter);
        delimiter= "\n";
        s+= delimiter;
        s+= R->key;
        s+= " : ";
        s+= std::to_string(R->val);
        inOrderString(s, R->right, delimiter);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R, std::string delimiter) const{
    if (R != nil){
        s+= delimiter;
        s+= R->key;
        delimiter= "\n";
        preOrderString(s, R->left, delimiter);
        preOrderString(s, R->right, delimiter);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Recursion ends at NIL
void Dictionary::preOrderCopy(Node* R, Node* NIL){
    if (R == NIL) return;
    setValue(R->key, R->val);
    preOrderCopy(R->left, NIL);
    preOrderCopy(R->right, NIL); 
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){ 
    if (R == nil) return;
    if (R->left != nil) postOrderDelete(R->left);
    if (R->right != nil)postOrderDelete(R->right);
    remove(R->key);
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    //std::cout << "R: " << R << std::endl;
    if (R == nil || R->key == k){
        //std::cout << "inside R: " << R->key << std::endl;
        return R;
    }else if (R->key.compare(k) > 0){/*std::cout << "go left"<< std::endl;*/ return this->search(R->left, k);}
    else{/* std::cout << "go right"<< std::endl;*/ return this->search(R->right, k);}
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
