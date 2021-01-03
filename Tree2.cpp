#include <iostream>

using namespace std;

template <typename T>
struct node {

    T data;
    node<T>* right;
    node<T>* left;
    bool rightThread;

    node(T el) : data(el), right(nullptr), left(nullptr), rightThread(false) {}

};

template <typename T>
class Tree {

    node<T>* root;

    void caseA(node<T>* prev, node<T>* ptr, T el) {

        if(prev->left == ptr)  prev->left = nullptr;
        else {

            if(ptr->rightThread) {
                
                prev->right = ptr->right;
                prev->rightThread = 1;
            }
            else prev->right = nullptr;
        }

        delete ptr;
    }

    void caseC(node<T>* prev, node<T>* ptr, T el) {

        if(ptr->left!=nullptr) {

            node<T>* pre, *succ ;
            pre = inPre(root,pre,el);
            succ = inSucc(el);

            if(pre->right == ptr) pre->right = succ;

            node<T>* child = ptr->left;
            if(prev->left == ptr) prev->left = child;
            else prev->right = child;

        }

        else {

            node<T>* child = ptr -> right;
            if(prev->left == ptr) prev->right = child;
            else prev->right = child;
        }

        delete ptr;
    }

    void caseB(node<T>* prev, node<T>* ptr, T el) {


        node<T>* succ = ptr->right;
        node<T>* par = ptr;

        while(succ->left!=nullptr) {

            par = succ;
            succ = succ->left;
        }

        ptr->data = succ->data;

        if(succ->left==nullptr and (succ->right==nullptr or succ->rightThread)) caseA(par,succ,el);
        else caseC(par,succ,el);
    }



    node<T>* inPre(node<T>* rt, node<T>* pre, T el) {

        if(rt == nullptr) {
            
            pre = nullptr;
            return pre;
        }

        else if(rt->data == el) {

            if(rt->left!=nullptr) pre = rightMost(rt->left);
            return pre;
        }

        else if(el<rt->data) return inPre(rt->left,pre,el);

        else {

            if(rt->rightThread) {

                pre = nullptr;
                return pre;
            }

            pre = rt;
            return inPre(rt->right,pre,el);
        } 


    }

    public:

    Tree() : root(nullptr) {}

    void insert(T el) {

        node<T>* nn = new node<T>(el);

        if(root == nullptr) root = nn;

        else {

            node<T>* ptr = root, *prev = nullptr;
            
            while(ptr!=nullptr) {

                prev = ptr;
                if(el<ptr->data) ptr = ptr->left;
                else if(!ptr->rightThread) ptr = ptr->right;
                else break;
            }

            if(prev->data>el) {

                prev->left = nn;
                nn->right = prev;
                nn->rightThread = 1;

            }

            else if(prev->rightThread) {

                nn->right = prev->right;
                prev->right = nn;
                nn->rightThread = 1;
                prev->rightThread = 0;
            }

            else prev->right = nn;
         }
    }

    node<T>* leftMost(node<T>* ptr) {

        if(ptr == nullptr) return ptr;
        while(ptr->left!=nullptr) ptr = ptr->left;
        return ptr;

    }

    node<T>* rightMost(node<T>* ptr) {

        if(ptr == nullptr) return ptr;
        while(ptr->right!=nullptr and !ptr->rightThread) ptr = ptr->right;
        return ptr;
    }

    void inorder() {

        node<T>* nd = root;
        nd = leftMost(nd);
        cout<<"[ ";
        while(nd!=nullptr) {
            
            cout<<nd->data<<" ";
            if(nd->rightThread) nd = nd->right;
            else nd = leftMost(nd->right);
        } 

        cout<<"]"<<endl;

    }

    bool isempty() {

        return root==nullptr;
    }

    node<T>* search(T el) {

        node<T>* ptr = root;
        while(ptr!=nullptr) {

            if(el==ptr->data) return ptr;
            else if(el<ptr->data) ptr = ptr->left;
            else if(el>ptr->data && !ptr->rightThread) ptr = ptr-> right;
            else break; 
        }

        return nullptr;
    }

    void findAndDel(T el) {

        node<T>* ptr = root, *prev = nullptr;

        while(ptr!=nullptr) {

            if(el==ptr->data) break;
            prev = ptr;
            if(el<ptr->data) ptr = ptr->left;
            else if(el>ptr->data and !ptr->rightThread) ptr = ptr-> right;
            else ptr = nullptr; 
        }

        if(ptr == nullptr) return;

        else {

            if(ptr->left == nullptr and (ptr->rightThread or ptr->right == nullptr)) caseA(prev,ptr,el); //No children
            else if(ptr->left!=nullptr and (!ptr->rightThread and ptr->right!=nullptr)) caseB(prev,ptr,el); //Two children
            else caseC(prev,ptr,el); //One child

        }
    }

    node<T>* inSucc(T el) {

        node <T>* ptr = search(el), * temp;
        temp = ptr;

        if(ptr == nullptr) return ptr;

        if(ptr->rightThread) return ptr->right;

        else {

            temp = temp ->right;
            while(temp!=nullptr and temp->left !=nullptr) temp = temp ->left;
            return temp;
        }
    }

    node<T>* inPre(T el) {
        
        node<T>* pre = nullptr;
        pre = inPre(root,pre,el);
        return pre; 

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
    tr.inorder();
    tr.findAndDel(6);
    tr.inorder();
}
