#include "filetree.h"

#include <fstream>
#include <string>
#include <vector> 
using std::istream;
using std::string;
using namespace std;
class NODE{
    public:
        string name;
        bool is_file;
        int size; // Add size member for the node
        std::vector<NODE *> children;

        NODE(string name, bool is_file) : name(name), is_file(is_file){}
};


void printNode(NODE *node, int lvl = 0) {
    for (int i = 0; i < lvl; i++) {
        cout << "|  ";
    }

    if (lvl > 0) {
        cout << "+-";
    }

    cout << "(" << node->name << ")" << endl;

    for (NODE *child : node->children) {
        printNode(child, lvl + 1);
    }
}

/* For each function, make sure you call your readInput function to
    load the data */

void printTree(istream &is) {

}

int computeSize(istream & is, string path)
{
    /* TO BE COMPLETED */
    return -1;
}

string smallestDir(istream & is, int targetSize, string ext)
{
    /* TO BE COMPLETED */
    return "";
}

void listDeleted(istream & is, int targetSize, string ext)
{
    /* TO BE COMPLETED */
}