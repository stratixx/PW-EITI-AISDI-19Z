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
            if(newNode.key<curr->key)
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

    /*
        Usuwa element o zgodnym kluczu
    */
    void remove( key_type key)
    {
        Node* parrent = nullptr;
        Node* curr = root;

        // szukanie elementu o zgodnym kluczu
        while(curr!=nullptr)
        {
            if(curr->key==key) // klucz znaleziony
                break;
            if(key < curr->key) // klucz może być po lewej
            {
                if(curr->left!=nullptr) // krok w lewo
                {
                    parrent = curr;
                    curr = curr->left;
                }
                else // nie znaleziono klucza
                    curr = nullptr;
            }
            else // klucz moze być po prawej
            {
                if(curr->right!=nullptr) // krok w prawo
                {
                    parrent = curr;
                    curr = curr->right;
                }
                else // nie znaleziono klucza
                    curr = nullptr;        
            }
        }

        if(curr==nullptr) // nie znaleziono klucza
        {
            return;
        }

        // w curr jest Node z pasującym kluczem
        // w parrent jest rodzic curr

        // jeśli usuwany node nie ma dzieci, skasuj
        if(curr->left==nullptr && curr->right==nullptr)
        {
            if(parrent==nullptr) // usuwanie root
            {
                root = nullptr;
            }
            else
            {
                if(parrent->left==curr)
                    parrent->left = nullptr;
                else if( parrent->right==curr)
                    parrent->right = nullptr;
                else
                    throw std::logic_error("Node has parrent, but parrent is not parrent of this child.");
            }
            delete curr;
        }
        else if(curr->left==nullptr) // node ma tylko prawe dziecko
        {
            if(parrent==nullptr) // usuwanie root
            {
                root = curr->right;
            }
            else
            {    
                if(parrent->left==curr)
                    parrent->left = curr->right;
                else if( parrent->right==curr)
                    parrent->right = curr->right;
                else
                    throw std::logic_error("Node has parrent, but parrent is not parrent of this child.");
            }
            curr->right = nullptr;
            delete curr;     
        }
        else if(curr->right==nullptr) // node ma tylko lewe dziecko
        {
            if(parrent==nullptr) // usuwanie root
            {
                root = curr->left;
            }
            else
            {    
                if(parrent->left==curr)
                    parrent->left = curr->left;
                else if( parrent->right==curr)
                    parrent->right = curr->left;
                else
                    throw std::logic_error("Node has parrent, but parrent is not parrent of this child.");
            }
            curr->left = nullptr;
            delete curr;            
        }
        else // node ma obydwoje dzieci
        {
            Node* next = curr->right; // next będzie następnikiem curr
            Node* nextParrent = curr; // nextParrent będzie parrentem next

            while(next->left!=nullptr) // szukanie następnika curr
            {
                nextParrent = next;
                next = next->left;
            }     
            // //jeśli nastęþnik jest bezpośrednim dzieckiem usuwanego elementu
            // if(curr->right==next)
            // {
                
            // }       
            // przepięcie prawego dziecka next do nextParrent
            // if(nextParrent->left==next)
            //     nextParrent->left = next->right;

            // if(parrent==nullptr) // usuwanie root
            // {
            //     root = next;
            //     root->left = curr->left;
                
            // }
            // else
            // {    
            //     if(parrent->left==curr)
            //         parrent->left = curr->left;
            //     else if( parrent->right==curr)
            //         parrent->right = curr->left;
            //     else
            //         throw std::logic_error("Node has parrent, but parrent is not parrent of this child.");
            // }

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
