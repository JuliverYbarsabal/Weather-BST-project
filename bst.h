#ifndef BST_H
#define BST_H

#include <stack>
#include <cstdlib>

using namespace std;

/**
* @class BST
* @brief Manages all essential functions about BST template.
*
* Allow to insert and search, inorderTraversal, preorderTraversal andpostorderTraversal.\n
*
* @author Juliver
* @version 01
* @date 12/05/2021
*
* @bug My program has no bugs. Well, maybe it has...
*/
template<class T>
class BST
{
public:
    /**
    * @brief A constructor.
    * Construct an empty BST.
    */
    BST();
    /**
    * @brief copy constructor
    *
    * @return none
    */
    BST(const BST &other);

    /**
    * @brief Assignemnt operator
    *
    * @return BST
    */
    const BST &operator=( const BST &other);

    /**
    * @brief destructor
    *
    * clear the tree.
    *
    * @return none
    */
    ~BST();
    /**
    * @brief Adds item into tree.
    *
    * @param T data
    * @return void
    */
    bool Insert(const T data);
    /**
    * @brief Searches tree for specific item and removes it.
    *
    * @param T data
    * @return bool
    */
    bool Remove(const T data);
    /**
    * @brief Searches tree for specific item and returns whether it was
    found or not.
    *
    * @param T data
    * @return bool
    */
    bool Search(const T data);
    /**
    * @brief Traverse through the contents of tree in order.
    *
    * @return void
    */
    void InOrder(void (*visit) (T&)) const;
    /**
    * @brief Traverse through the contents of tree in pre order.
    *
    * @return void
    */
    void PreOrder(void (*visit) (T&)) const;
    /**
    * @brief Traverse through the contents of tree in post order.
    *
    * @return void
    */
    void PostOrder(void (*visit) (T&)) const;

private:
    struct node
    {
        /** data of T type */
        T data;
        node *left;
        node *right;
    };
    /** Root node of the tree */
    node *root;

    ///used in copy contructor and assignment operator to copy BST tree heap
    void copyTree(node *&thisRoot, node *other);
    /**
    * @brief public function to do clear the node.
    *
    * @param &p- node*
    *
    * @return void
    */
    void clear(node* &p);
    /**
    * @brief Searches for node to be removed.
    *
    * @param T data, node *removeNode, node *parentNode
    * @return bool
    */
    void Remove(node* &removeNode);
};
template<class T>
BST<T>::BST()
{
    root = nullptr;
}

template<class T>
BST<T>::BST(const BST& other)
{
    if(other.root==nullptr)
        root=nullptr;
    else
        copyTree(root,other.root);
}
template<class T>
void BST<T>::copyTree(node* &thisRoot,node *other)
{
    if(other==nullptr)
        thisRoot=nullptr;
    else
    {
        thisRoot = new node;
        thisRoot->data = other->data;
        copyTree(thisRoot->left,other->left);
        copyTree(thisRoot->right,other->right);
    }
}
template<class T>
const BST<T>& BST<T>::operator=(const BST& other)
{
    if(this!=&other)
    {
        copyTree(this->root,other.root);
    }
    return *this;
}

template <class T>
void BST<T>::clear(node* &p)
{
    if(p != nullptr)
    {
        clear(p->left);
        clear(p->right);
        delete(p);
        p = nullptr;
    }
}

template <class T>
BST<T>::~BST()
{
    if(root)
        clear(root);
}

template<class T>
bool BST<T>::Insert(const T data)
{
    node *current;
    node *trailCurrent;
    node *newNode;
    newNode = new node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if(root == nullptr)
    {
        root = newNode;
    }
    else
    {
        current = root;
        while(current != nullptr)
        {
            trailCurrent = current;
            if(current->data == data)
            {
                return false; //duplicate value
            }
            else if(current->data > data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        if(trailCurrent->data > data)
        {
            trailCurrent->left = newNode;
        }
        else
        {
            trailCurrent->right = newNode;
        }
    }
    return true;
}
template<class T>
bool BST<T>::Remove(const T data)
{
    node *current;
    node *trailCurrent;
    bool found = false;
    if(root == nullptr)
    {
//empty tree
    }
    else
    {
        current = root;
        trailCurrent = root;
        while(current != nullptr && !found)
        {
            if(current->data == data)
            {
                found = true;
            }
            else
            {
                trailCurrent = current;
                if(current->data > data)
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }
        }
        if(current == nullptr)
        {
//item not in tree
        }
        else if(found)
        {
            if(current == root)
            {
                Remove(root);
            }
            else if(trailCurrent->data > data)
            {
                Remove(trailCurrent->left);
            }
            else
            {
                Remove(trailCurrent->right);
            }
        }
        else
        {
//item not in tree
        }
    }
    return found;
}
template<class T>
void BST<T>::Remove(node* &p)
{
    node *current;
    node *trailCurrent;
    node *temp;
    if(p == nullptr)
    {
//node to be deleted is nullptr
    }
    else if(p->left == nullptr && p->right == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if(p->left == nullptr)
    {
        temp = p;
        p = temp->right;
        delete temp;
    }
    else if(p->right == nullptr)
    {
        temp = p;
        p = temp->left;
        delete temp;
    }
    else
    {
        current = p->left;
        trailCurrent = nullptr;
        while(current->right != nullptr)
        {
            trailCurrent = current;
            current = current->right;
        }
        p->data = current->data;
        if(trailCurrent == nullptr)
        {
            p->left = current->left;
        }
        else
        {
            trailCurrent->right = current->left;
        }
        delete current;
    }
}
template<class T>
bool BST<T>::Search(const T data)
{
    node *current;
    bool found = false;
    if(root == nullptr)
    {
//empty tree
    }
    else
    {
        current = root;
        while(current != nullptr && !found)
        {
            if(current->data == data)
            {
                found = true;
            }
            else if(current->data > data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
    }
    return found;
}
template<class T>
void BST<T>::InOrder(void (*visit) (T& item)) const
{
    stack<node*> nodeStack;
    node *current;
    current = root;
    while((current != nullptr) || (!nodeStack.empty()))
    {
        if(current != nullptr)
        {
            nodeStack.push(current);
            current = current->left;
        }
        else
        {
            current = nodeStack.top();
            nodeStack.pop();
            (*visit) (current->data);
            current = current->right;
        }
    }
}
template<class T>
void BST<T>::PreOrder(void (*visit) (T& item)) const
{
    stack<node*> nodeStack;
    node *current;
    current = root;
    while((current != nullptr) || (!nodeStack.empty()))
    {
        if(current != nullptr)
        {
            (*visit) (current->data);
            nodeStack.push(current);
            current = current->left;
        }
        else
        {
            current = nodeStack.top();
            nodeStack.pop();
            current = current->right;
        }
    }
}
template<class T>
void BST<T>::PostOrder(void (*visit) (T& item)) const
{
    stack<node*> nodeStack;
    stack<int> intStack;
    node *current;
    current = root;
    int v = 0;
    if(current != nullptr)
    {
        nodeStack.push(current);
        intStack.push(1);
        current = current->left;
        while(!nodeStack.empty())
        {
            if(current != nullptr && v == 0)
            {
                nodeStack.push(current);
                intStack.push(1);
                current = current->left;
            }
            else
            {
                current = nodeStack.top();
                nodeStack.pop();
                v = intStack.top();
                intStack.pop();
                if(v == 1)
                {
                    nodeStack.push(current);
                    intStack.push(2);
                    current = current->right;
                    v = 0;
                }
                else
                {
                    (*visit) (current->data);
                }
            }
        }
    }
}
#endif // BST_H
