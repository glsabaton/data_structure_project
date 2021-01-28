#ifndef H_structure
#define H_structure
#include <iostream>
using namespace std;
struct Word;

Word* topTen[10];


struct Word // Every word is a node
{
private:
    string wordString;
    int count;
    Word* right = NULL;
    Word* left = NULL;
public:
    Word(string word) {
        this->wordString = word;
        this->count = 1;
    }

    string getWord() {
        return wordString;
    }

    Word* getLeft() {
        return left;
    }

    Word* getRight() {
        return right;
    }

    void setLeft(Word* left) {
        this->left = left;
    }

    void setRight(Word* right) {
        this->right = right;
    }
    void incrementCount() {
        this->count++;
        //cout << "count incremented" << endl;
    }

    int getCount() {
        return count;
    }
};


void addToTopTen(Word* h) {
    if (h == NULL) {
        return;
    }
    int count = h->getCount();
    int index = -1;

    for (int i = 0; i < 10; i++) {
       
        if (count < topTen[i]->getCount()) {
            index = i - 1;
            break;
        }

        if (i != 9)
            topTen[i] = topTen[i + 1];
        else
            index = i;
    }
    
    if (index != -1)
        topTen[index] = h;
}


class myTree
{
public:
    Word* head = NULL;
    void insert(string newWord);// inserts a new word

    bool isExist(string str);// checks whether the same word exists or not

    void print(Word* h) const;

    void traverse(Word* h) const;
};

class myStructure {
public:
    myTree* wordArr[26][26];

    void insert(string w);

    bool isExist(string str);

    void print() const;

    void traverse() const;

    myStructure() {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                wordArr[i][j] = new myTree();
            }
        }
    }
};







void myStructure::insert(string w) {
    wordArr[w[0] - 97][w[1] - 97]->insert(w);
}
bool myStructure::isExist(string str) {
    if (wordArr[str[0] - 97][str[1] - 97]->head != NULL) {
        return wordArr[str[0] - 97][str[1] - 97]->isExist(str);
    }
    else {
        return false;
    }
}

void myStructure::print() const {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            cout << char(i + 97) << char(j + 97) << ": ";
            wordArr[i][j]->print(wordArr[i][j]->head);
        }
    }
}

void  myStructure::traverse() const {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            wordArr[i][j]->traverse(wordArr[i][j]->head);
        }
    }
}




bool myTree::isExist(string str) {
    if (head->getWord() == str) {
        head->incrementCount();
        return true;
    }
    Word* cursor = this->head;
    while (cursor != NULL) {
        //cout << cursor->getWord() << endl;
        if (cursor->getWord()[2] < str[2]) {
            cursor = cursor->getRight();
            if (cursor == NULL) {
                //cout << "cursor is NULL " << endl;
                break;
            }
        }
        else if (cursor->getWord()[2] > str[2]) {
            cursor = cursor->getLeft();
            if (cursor == NULL)
                break;

        }
        else if (cursor->getWord()[2] == str[2]) {
            if (cursor->getWord() == str) {
                cursor->incrementCount();
                return true;
            }
            cursor = cursor->getRight();
            if (cursor == NULL)
                break;
        }
    }
    return false;
}


void myTree::insert(string newWord) {
    if (head == NULL) {
        //cout << "inserting as head  "<< newWord << endl;
        head = new Word(newWord);
        //cout << head->getWord() << endl;
        return;
    }
    Word* parent = this->head;
    Word* cursor = this->head;

    while (cursor != nullptr) {
        //cout << cursor->getWord() << " " << newWord <<endl;
        if (cursor->getWord()[2] < newWord[2]) {
            parent = cursor;
            cursor = cursor->getRight();
            if (cursor == NULL) {
                parent->setRight(new Word(newWord));
                //cout << parent->getWord();
                //cout << "new word added to right" << endl;
                return;
            }
        }
        else if (cursor->getWord()[2] > newWord[2]) {
            parent = cursor;
            cursor = cursor->getLeft();
            if (cursor == NULL) {
                parent->setLeft(new Word(newWord));
                //cout << parent->getWord();
                //cout << "new word added to left" << endl;
                return;
            }
        }
        else if (cursor->getWord()[2] == newWord[2]) {
            if (cursor->getWord() == newWord) {
                //cout << "count incremented" << endl;
                cursor->incrementCount();
                return;
            }
            parent = cursor;
            cursor = cursor->getRight();
            if (cursor == NULL) {
                parent->setRight(new Word(newWord));
                //cout << parent->getWord();
                //cout << "new word added to right" << endl;
                return;
            }
        }
    }
    //cout << "insertin sonu" << endl;
}

void myTree::print(Word* h) const {
    if (h == NULL) {
        return;
    }
    if (h->getLeft() == NULL && h->getRight() == NULL) {
        cout << h->getWord() << " " << h->getCount() << " ";
    }
    else if (h->getLeft() == NULL && h->getRight() != NULL) {
        cout << h->getWord() << " " << h->getCount() << " ";
        print(h->getRight());
    }
    else if (h->getLeft() != NULL && h->getRight() == NULL) {
        print(h->getLeft());
        cout << h->getWord() << " " << h->getCount() << " ";
    }
    else {
        print(h->getLeft());
        cout << h->getWord() << " " << h->getCount() << " ";
        print(h->getRight());
    }
}


void myTree::traverse(Word* h) const {
    if (h == NULL) {
        return;
    }
    if (h->getLeft() == NULL && h->getRight() == NULL) {
        addToTopTen(h);
    }
    else if (h->getLeft() == NULL && h->getRight() != NULL) {
        addToTopTen(h);
        traverse(h->getRight());
    }
    else if (h->getLeft() != NULL && h->getRight() == NULL) {
        traverse(h->getLeft());
        addToTopTen(h);
    }
    else {
        traverse(h->getLeft());
        addToTopTen(h);
        traverse(h->getRight());
    }
}


#endif
