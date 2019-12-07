/*
Autor: Konrad Winnicki
Utworzono: 27.11.2019


Zadanie:
    *   Zaimplementuj operację usuwania węzła z binarnego drzewa poszukiwań.
*/

#include <iostream>
#include <vector>


using namespace std;

////////////////////////////////////////////////////////////


/*
 * BST
 *
 */
template<typename KeyType>
class BST {
public:
    using key_type = KeyType;

    BST() = default;    // konstruktor trywialny
    ~BST() {
        if(root!=nullptr)
            delete root;
        root = nullptr;
    }


    class Node {
    public:
        Node(key_type key) : key(key) {}
        ~Node()
        {
            if(left!=nullptr)
                delete left;
            if(right!=nullptr)
                delete right;
            left = nullptr;
            right = nullptr;
        }


	    template<typename StreamType>
	    void print(StreamType& stream, unsigned long indent=0) const
        {
            if(this->right!=nullptr)
            	this->right->print(stream, indent+1);		
            else
            {
                for(int n=0; n<indent+1; ++n)
                    stream<<'\t';
                stream<<"X"<<std::endl;
            }

            for(int n=0; n<indent; ++n)
                stream<<'\t';

            stream<<this->key<<std::endl;


            if(this->left!=nullptr)
            	this->left->print(stream, indent+1);		
            else
            {
                for(int n=0; n<indent+1; ++n)
                    stream<<'\t';
                stream<<"X"<<std::endl;
            }
        }


        key_type key;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    /*!
     * true jezeli BST jest pusty
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /*!
     * dodaje wpis do BST
     */
    void insert(const Node &newNode) {
        if (root==nullptr)
        {
            root = new Node(newNode);
            return;
        }
        Node* curr = root;

        while(curr!=nullptr)
        {
            if(curr->key<newNode.key)
            {
                if(curr->left!=nullptr)
                    curr = curr->left;
                else
                {
                    curr->left = new Node(newNode);
                    break;
                }
            }
            else
            {
                if(curr->right!=nullptr)
                    curr = curr->right;
                else
                {
                    curr->right = new Node(newNode);
                    break;
                }                
            }
            
        }

    }


	template<typename StreamType>
	void print(StreamType& stream) const
	{
		if(isEmpty())
		    return;

        root->print(stream);			
	}


    Node *root = nullptr;

};

//#include "tests.h"

int main(int argc, char *argv[]) {
    //unit_test();

    std::vector<BST<int>::Node> nodes = { 40, 65, 20, 55, 30, 75, 15, 50, 10, 45, 80, 60, 70, 35, 25 };
    BST<int> tree;

    for(auto node : nodes)
    {
        tree.insert(node);
    }

    tree.print(cout);


    return 0;
}
