#include <iostream>
#include <queue>

using namespace std;

template <typename T>
struct node {

    T data;
    node* left;
    node* right;

    node(T el) : data(el),left(nullptr),right(nullptr) {}

};

template <typename T>
class Queue : public queue<T> {

    public :

    T dequeue() {

        T tmp = queue<T>::front();
        queue<T>::pop();
        return tmp;

    }

    void enqueue(const T& el) {

        queue<T>::push(el);
    }
};


template <typename T>
class Tree{

    node<T>* root;

    void inorder(node<T>* ptr) {

        if(ptr!=nullptr) {

            inorder(ptr->left);
            cout<<ptr->data<<" ";
            inorder(ptr->right);

        }

    }

    void clear(node <T>* ptr) {


        if (ptr==nullptr) return;

        else if(ptr->left!=nullptr and ptr->right==nullptr) {

            clear(ptr->left);
            ptr->left = nullptr;
        }

        else if(ptr->left==nullptr and ptr->right!=nullptr) {
            
            clear(ptr->right);
            ptr->right = nullptr;
        }

        else if(ptr->left!=nullptr and ptr->right!=nullptr) {

            clear(ptr->right);
            clear(ptr->left);
            ptr->left = ptr->right = nullptr;
        }

        delete ptr;

    }

    void postorder(node <T>* ptr) {

        if(ptr!=nullptr) {

            postorder(ptr->left);
            postorder(ptr->right);
            cout<<ptr->data<<" ";
        }
    }

    void preorder(node <T>* ptr) {

        if(ptr!=nullptr) {

            cout<<ptr->data<<" ";
            postorder(ptr->left);
            postorder(ptr->right);
        }
    }

    void delMerging(node<T>*& nd) {

        node<T>* temp = nd;

        if(nd!=nullptr) {

            if(nd->right==nullptr) nd = nd->left;

            else if(nd->left==nullptr) nd = nd->right;
            
            else {

                temp = nd->left;
                while(temp->right!=nullptr) temp = temp->right;
                temp->right = nd->right;
                temp = nd;
                nd = nd->left;
            }
            delete temp;

        }


    }


    public:    

    Tree() : root(nullptr) {}

    void inorder() {

        cout<<"[ ";
        inorder(root);
        cout<<"]"<<endl;
    }

    node<T>* search(T el) {

        node<T>* ptr = root;
        while(ptr!=nullptr) {

            if(el==ptr->data) return ptr;
            else if(el<ptr->data) ptr = ptr->left;
            else ptr = ptr->right;

        }
        return nullptr;
    }

    bool isempty() {

        return root==nullptr;
    }

    void clear() {

        clear(root);
        root = nullptr;
    }

    void insert(T el) {

        node<T> * nn = new  node<T>(el);

        if(root == nullptr) root = nn;

        else {

            node<T> *ptr = root ,*prev = nullptr;
            while(ptr!=nullptr) {

                prev = ptr;
                el < ptr -> data ? ptr = ptr -> left : ptr = ptr -> right;
            }
            
            el< prev-> data ? prev->left = nn : prev->right = nn;
        }

    }

    void postorder() {

        cout<<"[ ";
        postorder(root);
        cout<<"]"<<endl;
    }

    void preorder() {

        cout<<"[ ";
        preorder(root);
        cout<<"]"<<endl;
    }

    void findAndDelMerging(T el) {

        node<T> *nd = root, *prev = nullptr;
        while(nd !=nullptr) {

            if(nd->data == el) break;
            prev = nd;
            el< nd->data ? nd = nd->left : nd = nd->right;
        }
        if(nd!=nullptr and nd->data == el) {

            if(nd==root) delMerging(root);
            else if(prev->left == nd) delMerging(prev->left);
            else delMerging(prev->right);

        }


    }

    node<T>* RightMost() {

        if(root == nullptr) return root;

        node<T>* ptr = root;

        while(ptr->right != nullptr) ptr = ptr->right;

        return ptr;
    }

    node<T>* LeftMost() {

        if(root == nullptr) return root;

        node<T>* ptr = root;

        while(ptr->left != nullptr) ptr = ptr->left;

        return ptr;
    }

    void breadthFirst() {
        
        Queue<node<T>*> nodes;
        node<T>* ptr = root;

        cout<<"[ ";

        if(ptr!=nullptr) {

            nodes.enqueue(ptr);
            while(!nodes.empty()) {

                ptr = nodes.dequeue();
                cout<<ptr->data<<" ";
                if(ptr->left!=nullptr) nodes.enqueue(ptr->left);
                if(ptr->right!=nullptr) nodes.enqueue(ptr->right);

            }

        }

        cout<<"]"<<endl;    

    }

    void morrisInorder() {

        node<T>* ptr = root;
        node<T>* temp;

        cout<<"[ ";

        while(ptr!=nullptr) {

            if(ptr->left == nullptr) {

                cout<<ptr->data<<" ";
                ptr = ptr->right;
            }

            else {

                temp = ptr->left;
                while(temp->right!=nullptr and temp->right != ptr) temp = temp->right;

                if(temp->right == nullptr) {
                    
                    temp->right = ptr;
                    ptr = ptr->left;
                }

                else {

                    temp->right = nullptr;
                    cout<<ptr->data<<" ";
                    ptr = ptr->right;
                }
            }
        }

        cout<<"]"<<endl;
    }
};

int main() {

    Tree<int>tr;
    tr.insert(6);
    tr.insert(10);
    tr.insert(1);
    tr.insert(0);
    tr.insert(4);
    tr.insert(5);
    tr.insert(2);
    tr.insert(11);
    tr.insert(8);
    tr.morrisInorder();
    
    
}