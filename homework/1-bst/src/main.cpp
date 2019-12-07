/*
Autor: Konrad Winnicki
Utworzono: 27.11.2019


Zadanie:
    *   Zaimplementuj operację usuwania węzła z binarnego drzewa poszukiwań.
*/

#include <iostream>
#include <vector>
#include <cassert>




using namespace std;

////////////////////////////////////////////////////////////


/*
 * BST
 *
 */
template<typename KeyType, typename DataType>
class BST {
public:
    using key_type = KeyType;
    using data_type = DataType;

    BST() = default;    // konstruktor trywialny
    ~BST() {
        if(root!=nullptr)
            delete root;
        root = nullptr;
    }


    class Node {
    public:
        Node(key_type key, data_type data) : key(key), data(data) {}
        ~Node()
        {
            if(left!=nullptr)
                delete left;
            if(right!=nullptr)
                delete right;
            left = nullptr;
            right = nullptr;
        }

        void copyContent(Node* node)
        {
            key = node->key;
            data =  node->data;
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

            stream<<this->key<<"("<<this->data<<")"<<std::endl;


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
        data_type data;
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
            if(newNode.key<=curr->key)
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
        Wykonuje operację usunięcia elementu o zgodnym kluczu, 
        zwraca nowy root
    */
    Node* doRemove(Node* node, key_type key )
    {
        if(node==nullptr)
            return nullptr;
        
        if(key < node->key)
        {
            //cout<<"usuwany element może być po lewej"<<endl;
            node->left = doRemove(node->left, key);
        }
        else if(key > node->key) 
        {
            //cout<<"usuwany element może być po prawej"<<endl;
            node->right = doRemove(node->right, key);
        }
        else
        {
            //cout<<"klucz znaleziony"<<endl;
            Node* tmp;

            if(node->left==nullptr) 
            {
                //cout<<"node nie ma lewego dziecka"<<endl;
                tmp = node->right;
                node->right = nullptr;
                delete(node);
                return tmp;
            }        
            if(node->right==nullptr) 
            {
                //cout<<"node nie ma prawego dziecka"<<endl;    
                tmp = node->left;
                node->left = nullptr;
                delete(node);
                return tmp;
            }
            
            //cout<<"node ma dwójkę dzieci"<<endl;
            //cout<<"szukanie następnika node"<<endl;
            tmp = node->right;
            while(tmp->left!=nullptr)
                tmp = tmp->left;
            
            //cout<<"skopiowanie zawartości następnika do usuwanego elementu"<<endl;
            node->copyContent(tmp);
            
            //cout<<"skasowanie następnika"<<endl;
            node->right = doRemove(node->right, node->key);            
        }

        return node;
    }

    /*
        Inicjuje operację usunięcia elementu o zgodnym kluczu
    */
    void remove( key_type key)
    {
        root = doRemove(root, key);         
    }

    /*
        wypisanie całego drzewa
    */
	template<typename StreamType>
	void print(StreamType& stream) const
	{
		if(isEmpty())
		    return;

        root->print(stream);			
	}

    /* 
        wykonanie operacji sprawdzenia czy drzewo zachowuje własności BST
    */
    bool doIsBST(Node* node)
    {
        if(node==nullptr)
            return true;

        if(node->left!=nullptr)
        {
            if(node->left->key > node->key)
                return false;
            if(node->left->left!=nullptr && node->left->left->key > node->key)
                return false;
            if(node->left->right!=nullptr && node->left->right->key > node->key)
                return false;
            if(!doIsBST(node->left))
                return false;
        }

        if(node->right!=nullptr)
        {
            if(node->right->key <= node->key)
                return false;
            if(node->right->left!=nullptr && node->right->left->key <= node->key)
                return false;
            if(node->right->right!=nullptr && node->right->right->key <= node->key)
                return false;
            if(!doIsBST(node->right))
                return false;
        }

        return true;
    }

    /* 
        inicjacja operacji sprawdzenia czy drzewo zachowuje własności BST
    */
    bool isBST()
    {
        return doIsBST(root);
    }

    Node *root = nullptr;

};

int main(int argc, char *argv[]) {

    std::vector<BST<int, int>::Node> nodes = { {40, 40}, {65, 65}, {20, 20}, {55, 55}, 
                                                {30, 30}, {75, 75}, {15, 15}, {50, 50}, 
                                                {10, 10}, {45, 45}, {80, 80}, {60, 60}, 
                                                {70, 70}, {35, 35}, {25, 25} };
    BST<int, int> tree;

    cout<<"Wstawienie elementów do drzewa"<<endl;
    for(auto node : nodes)
    {
        tree.insert(node);
    }

    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);


    cout<<"Usunięcie elementu bez dzieci(key=45)"<<endl;
    tree.remove(45);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    cout<<"Usunięcie elementu z jednym lewym dzieckiem(key=15)"<<endl;
    tree.remove(15);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    cout<<"Usunięcie elementu z dwójką dzieci(key=65)"<<endl;
    tree.remove(65);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    cout<<"Usunięcie elementu z jednym prawym dzieckiem(key=75)"<<endl;
    tree.remove(75);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    cout<<"Usunięcie korzenia(key=40)"<<endl;
    tree.remove(40);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    cout<<"Usunięcie nieistniejacego klucza(key=31)"<<endl;
    tree.remove(31);
    cout<<"Zawartość drzewa:"<<endl;
    tree.print(cout);
    cout<<"Czy drzewo zachowuje własności BST? ";
    assert(tree.isBST());
    cout<<"Tak"<<endl;

    return 0;
}
