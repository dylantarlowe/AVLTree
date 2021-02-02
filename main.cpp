#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Node
{
    public:
        string NAME;
        int ID = 0;
        int balFactor;
        Node* left = NULL;
        Node* right = NULL;
};

// taken from my stepik work
// https://stepik.org/submissions/1590562/299391665?unit=400654
int height(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + std::max(leftHeight, rightHeight);
}

// taken from my stepik work
// used lecture powerpoint rotateLeft (Trees-3 slide 16)
// https://stepik.org/submissions/1480367/299099765?unit=379728
Node* rotateLeft(Node *node)
{
    Node* grandChild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandChild;
    return newParent;
}

// taken from my stepik work
// used reverse of lecture powerpoint rotateLeft (trees-3 slide 16)
// https://stepik.org/submissions/1480367/299099765?unit=379728
Node* rotateRight(Node *node)
{
    Node* grandChild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandChild;
    return newParent;
}

// taken from my stepik work
// https://stepik.org/submissions/1480367/299099765?unit=379728
Node* rotateLeftRight(Node *node)
{
    Node* greatGrandChild = node->left->right->left;
    Node* newChild = node->left->right;
    Node* grandChild = node->left;
    node->left = newChild;
    newChild->left = grandChild;
    grandChild->right = greatGrandChild;
    Node* newParent = rotateRight(node);
    return newParent;
}

// taken from my stepik work
// https://stepik.org/submissions/1480369/299535542?unit=379728
Node* rotateRightLeft(Node *node)
{
    Node* greatGrandChild = node->right->left->right;
    Node* newChild = node->right->left;
    Node* grandChild = node->right;
    node->right = newChild;
    newChild->right = grandChild;
    grandChild->left = greatGrandChild;
    Node* newParent = rotateLeft(node);
    return newParent;
}

int getBalanceFactor(Node* root) {
    if (root == NULL)
        return 0;
    else
        return height(root->left) - height(root->right);

}

bool searchID(Node* root, int ID) {
    //Search for the student with the specified ID from the tree.
    //If the ID was found, print out their NAME.
    //If the ID does not exist within the tree, print “unsuccessful”.
    // traverse using any method
    if (root == NULL) {
        cout << "unsuccessful" << endl;
        return false;
    }
    else if (root->ID == ID) {
        cout << root->NAME << endl;
        return true;
    }
    else if (ID < root->ID) {
        searchID(root->left, ID);
    }
    else if (ID > root->ID) {
        searchID(root->right, ID);
    }

    return false;
}

bool searchName(Node* root, string name) {
    //Search for the student with the specified name, NAME in the tree.
    //If the student name was found, print the associated ID.
    //If the tree has more than one object with the same NAME, print each ID on a new line with no other spaces and in the same relative order as a pre-order traversal.
    //If the name does not exist within the tree, print “unsuccessful”.
    //NAME identifier will be separated by double inverted commas for parsing, e.g. "Josh Smith".
    if (root == NULL) {
        cout << "unsuccessful" << endl;
        return false;
    }
    if (root->NAME == name) {
        cout << root->ID << endl;
        return true;
    }
    searchName(root->left, name);
    searchName(root->right, name);

    return false;
}

// took insert from my stepik, which useed Trees-1 Slide 31
// https://stepik.org/submissions/1480362/296614853?unit=379727
// used geeks for geeks to find out what condition to call for the child node
// for example, if (ID < root->left->ID)
// link: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
Node* insertNameID(Node* root, string NAME, int ID) {
    if (root == NULL) {
        cout << "successful" << endl;
        Node* node = new Node();
        node->NAME = NAME;
        node->ID = ID;
        return node;
    }
    //left subtree
    if (root->ID > ID)
        root->left = insertNameID(root->left, NAME, ID);
    // right subtee
    else if (root->ID < ID)
        root->right = insertNameID(root->right, NAME, ID);
    // key already exists, unsuccessful
    else {
        cout << "unsuccessful" << endl;
        return root;
    }

    // get balance factor of root to know if it is unbalanced
    root->balFactor = getBalanceFactor(root);

    // left left
    if (root->balFactor > 1 && ID < root->left->ID)
        return rotateRight(root);
    // left right
    else if (root->balFactor > 1 && ID > root->left->ID)
        return rotateLeftRight(root);
    // right right
    else if (root->balFactor < -1 && ID > root->right->ID)
        return rotateLeft(root);
    // right left
    else if (root->balFactor < -1 && ID < root->right->ID)
        return rotateRightLeft(root);


    return root;
}

// used pseudocode from Trees-1 slide 32
Node* removeID(Node* root, int ID){

    //Find and remove the account with the specified ID from the tree.
    //[Optional: Balance the tree automatically if necessary. We will test your code only on cases
    // where the tree will be balanced before and after the deletion.
    // So you can implement a BST deletion and still get full credit]
    //If deletion is successful, print “successful”.
    //If the ID does not exist within the tree, print “unsuccessful”.
    //You must prioritize replacing a removed node with its inorder successor for the case where the deleted node has two children.

    Node* child = root;
    Node* parent = root;
    Node* newRootParent;
    string side;
    if (root == NULL) {
        cout << "unsuccessful" << endl;
        return root;
    }

    while (true) {
        if (ID == child->ID) {
            // no children
            if (child->left == NULL && child->right == NULL) {
                if (side == "left")
                    parent->left = NULL;
                else if (child == root)
                    root = NULL;
                else
                    parent->right = NULL;
            }
            // set parent left or right to childs left
            else if (child->left != NULL && child->right == NULL) {
                if (side == "left")
                    parent->left = child->left;
                else if (child == root)
                    child->right = root->right;
                else
                    parent->right = child->left;
            }
            // set parent left or right to local roots right child
            else if (child->left == NULL && child->right != NULL) {
                if (side == "left")
                    parent->left = child->right;
                else if (child == root)
                    root = child->right;
                else
                    parent->right = child->right;
            }
            //two child
            else {
                // if child->left does not have a right child
                if (child->left->right == NULL) {
                    if (child == root) {
                        child->left->right = parent->right;
                        root = child->left;
                    }
                    else
                        parent->left = child->left;
                }
                //find right most node of left subtree and set it as new root
                else {
                    Node* newRoot = child->left;
                    while (true) {
                        if (newRoot->right == NULL) {
                            if (newRoot->ID < parent->ID)
                                parent->left = newRoot;
                            else
                                parent->right = newRoot;

                            newRootParent->right = NULL;
                            newRoot->left = child->left;
                            newRoot->right = child->right;
                            break;
                        }
                        else
                            newRootParent = newRoot;
                            newRoot = newRoot->right;
                    }
                }
            }
            cout << "successful" << endl;
            return root;
        }
        else if (ID < child->ID && child->left != NULL) {
            parent = child;
            side = "left";
            child = child->left;
        }
        else if (ID > child->ID && child->right != NULL) {
            parent = child;
            side = "right";
            child = child->right;
        }
        else if (ID != child-> ID) {
            cout << "unsuccessful" << endl;
            return root;
        }
    }
}

// used code from Trees-1 slide 36
void inOrderHelper(Node* root, vector<Node*> &tree) {
    if (root == nullptr) {
        return;
    }
    inOrderHelper(root->left, tree);
    tree.push_back(root);
    inOrderHelper(root->right, tree);
}

// used from my stepik
// but just switched cout with pushback and put cout above inorder(head->right)
// https://stepik.org/submissions/1480358/296190355?unit=379725
void preOrderHelper(Node* root, vector<Node*> &tree) {
    if (root == nullptr) {
        return;
    }
    tree.push_back(root);
    preOrderHelper(root->left, tree);
    preOrderHelper(root->right, tree);
}

// used code from inorder Trees-1 slide 36
// but just switched cout with pushback and put cout below inorder(head->right)
void postOrderHelper(Node* root, vector<Node*> &tree) {
    if (root == nullptr) {
        return;
    }
    postOrderHelper(root->left, tree);
    postOrderHelper(root->right, tree);
    tree.push_back(root);
}


void printInorder(Node* root) {
    //Print out a comma separated inorder traversal of the names in the tree.
    // Left, Root, Right
    vector<Node*> tree;
    inOrderHelper(root, tree);
    for (int i = 0; i < tree.size(); i++) {
        if (i == tree.size() - 1)
            cout << tree[i]->NAME;
        else
            cout << tree[i]->NAME << ", ";
    }

}

// used from my stepik
// https://stepik.org/submissions/1480358/296190355?unit=379725
void printPreorder(Node* root) {
    //Print out a comma separated preorder traversal of the names in the tree.
    // Root, Left, Right
    vector<Node*> tree;
    preOrderHelper(root, tree);
    for (int i = 0; i < tree.size(); i++) {
        if (i == tree.size() - 1)
            cout << tree[i]->NAME;
        else
            cout << tree[i]->NAME << ", ";
    }
}

void printPostorder(Node* root) {
    //Print out a comma separated postorder traversal of the names in the tree.
    // Left, Right, Root
    vector<Node*> tree;
    postOrderHelper(root, tree);
    for (int i = 0; i < tree.size(); i++) {
        if (i == tree.size() - 1)
            cout << tree[i]->NAME;
        else
            cout << tree[i]->NAME << ", ";
    }
}

void printLevelCount(Node* root) {

    //Prints the number of levels that exist in the tree.
    //Prints 0 if the head of the tree is null. For example, the tree in Fig. 1 has 4 levels.
    // get height
    int levelCount = height(root);
    cout << levelCount << endl;

}

void removeInorder(Node* root, int n) {
    //Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
    //If removal is successful, print “successful”.
    //[Optional: Balance the tree automatically if necessary. We will test your code only on cases where the tree will be balanced before and after the deletion. So you can implement a BST deletion and still get full credit]
    //If the Nth GatorID does not exist within the tree, print “unsuccessful”.

    vector<Node*> tree;
    inOrderHelper(root, tree);

    removeID(root, tree[n]->ID);

}

bool checkID(int ID) {
    return double(ID / 10000000) < 10 && double(ID / 10000000) > 0;
}

// checked if string contained a digit using find first of with 0123456789 inside
// https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
bool checkNAME (string NAME) {
    return NAME.find_first_of("0123456789") == std::string::npos;
}

int main() {
    int input;
    cin >> input;
    string line;
    int ID;
    string name;
    Node* root = nullptr;

    // used concept of getline(), line.find_first_of() and substr()
    // from a previous Programming 2 assignment to read input
    for (int i = 0; i < input + 1; i++) {
        getline(cin, line);
        int index = line.find_first_of(' ');
        string function = line.substr(0, index);
        line = line.substr(index + 1);


        if (function == "insert") {
            line = line.substr(1);
            index = line.find_first_of('\"');
            name = line.substr(0, index);
            ID = stoi(line.substr(index + 1));
            if (checkID(ID) && checkNAME(name)) {
                auto newRoot = insertNameID(root, name, ID);
                root = newRoot;
            }
            else
                cout << "unsuccessful";
        }
        else if (function == "remove") {
            ID = stoi(line);
            root = removeID(root, ID);
        }
        else if (function == "search") {
            // search name
            if (line[0] == '"') {
                name = line.substr(1, line.length() - 2);
                searchName(root, name);
            }
                // search ID
            else {
                ID = stoi(line);
                searchID(root, ID);
            }
        }
        else if (function == "printInorder") {
            printInorder(root);
            cout << endl;
        }
        else if (function == "printPreorder") {
            printPreorder(root);
            cout << endl;

        }
        else if (function == "printPostorder") {
            printPostorder(root);
            cout << endl;
        }
        else if (function == "printLevelCount")
            printLevelCount(root);
        else if (function == "removeInorder") {
            int n = stoi(line);
            removeInorder(root, n);
        }
    }
    return 0;
}
