
#include <iostream>

using namespace std;

template<class NodeType>
struct Node {
    Node(NodeType value) : value(value) {}

    NodeType value;
    int balance = 0;
    Node *right = nullptr;
    Node *left = nullptr;
};

template<class NodeType> void rotateLeft(Node<NodeType> **node);
template<class NodeType> void rotateRight(Node<NodeType> **node);
template<class NodeType> void printNodes(Node<NodeType>* node);
template<class NodeType> bool nodeExist(Node<NodeType>* node);

int main(int argc, char * argv[])
{
    // cout<<"hello World!"<<endl;

    // Node<int> nodes[5] = { 0, 1, 2, 3, 4};
    Node<char> nodes[5] = { 'A', 'B', 'C', 'D', 'E'};

    //Node<int>* root = &nodes[0];
    Node<char>* root = &nodes[0];
    root->left = &nodes[1];
    root->right = &nodes[2];
    root->left->left = &nodes[3];
    root->left->right = &nodes[4];

    cout << "----------------  Initial  -----------"<<endl;
    printNodes(root);
    cout << endl;
    
    cout << "----------------  Root rotate right  -----------"<<endl;
    rotateRight(&root);
    printNodes(root);
    cout << endl;
    
    cout << "----------------  Root rotate left   -----------"<<endl;
    rotateLeft(&root);
    printNodes(root);
    cout << endl;
    
    cout<< "First and last print should be the same."<<endl;
    
    return 0;
}

template<class NodeType>
void rotateLeft(Node<NodeType> **node)
{ 
    Node<NodeType> *p, *q;

    p = *node;
    q = p->right;
    p->right = q->left;
    q->left = p;

    *node = q;
}

template<class NodeType>
void rotateRight(Node<NodeType> **node)
{
    Node<NodeType> *p, *q;

    q = *node;
    p = q->left;
    q->left = p->right;
    p->right = q;
    q = p;

    *node = q;
}

template<class NodeType>
void printNodes(Node<NodeType>* node)
{
    if(!nodeExist(node))
        return;

    cout<<"Value: "<<node->value<<"\t";

    if(nodeExist(node->left))
        cout<<"L Value: "<<node->left->value<<"\t";
    else
        cout<<"L NullPtr\t";

    if(nodeExist(node->right))
        cout<<"R Value: "<<node->right->value;
    else
        cout<<"R NullPtr";
    
    cout<<endl;

    if(nodeExist(node->left))
        printNodes(node->left);
    if(nodeExist(node->right))
        printNodes(node->right);    
}

template<class NodeType>
bool nodeExist( Node<NodeType>* node )
{
    return node!=nullptr;
}