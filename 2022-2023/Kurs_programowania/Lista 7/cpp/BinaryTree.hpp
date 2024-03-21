//
// Created by Paweł on 25.06.2023.
//

#ifndef A_BINARYTREE_HPP
#define A_BINARYTREE_HPP
#include <iostream>

template <typename T>
class BinaryTree{
private:
    class Node{
    private:
        T value;
        Node* right;
        Node* left;
    public:
        Node(T value){
            this->getValue() = value;
            left = nullptr;
            right = nullptr;
        }
        Node*& getLeftNode(){
            return left;
        }
        Node*& getRightNode(){
            return right;
        }
        T& getValue(){
            return value;
        }
    };
    void destroyTree(Node* root){
        if(root != nullptr){
            destroyTree(root->getLeftNode());
            destroyTree(root->getRightNode());
            delete root;
        }
    }

    Node* insert(Node* node,T value){
        if(node == nullptr){
            return new BinaryTree<T>::Node(value);
        }
        if(value < node->getValue()){
            node->getLeftNode() = insert(node ->getLeftNode(),value);
        }
        else if(value > node->getValue()){
            node->getRightNode() = insert(node->getRightNode(),value);
        }
        return node;
    }
    Node* search(Node* root, T value){
        if(root==nullptr || root->getValue() == value){
            return root;
        }
        if(root->getValue() < value){
            return search(root->getRightNode(),value);
        }
        return search(root->getLeftNode(),value);
    }
    Node* deleteNode(Node* root,T value){
        if(root == nullptr){
            return root;
        }
        if(root->getValue()>value){
            root->getLeftNode() = deleteNode(root->getLeftNode(),value);
        }
        else if(root->getValue()<value){
            root->getRightNode() = deleteNode(root->getRightNode(),value);
        }else {
            if (root->getLeftNode() == nullptr) {
                Node *temp = root->getRightNode();
                delete root;
                return temp;
            } else if (root->getLeftNode() == nullptr) {
                Node *temp = root->getLeftNode();
                delete root;
                return temp;
            }
                Node *succParent = root;
                Node *succ = root->getRightNode();
                while (succ->getLeftNode() != nullptr) {
                    succParent = succ;
                    succ = succ->getLeftNode();
                }
                if (succParent != root) {
                    succParent->getLeftNode() = succ->getRightNode();
                } else {
                    succParent->getRightNode() = succ->getRightNode();
                }
                root->getValue() = succ->getValue();
                delete succ;
                return root;

        }
        return root;
    }
    void inorder(Node* root) {
        if (root != nullptr) {
            std::cout<<"(";
            inorder(root->getLeftNode());
            std::cout << " "<<root->getValue() << " ";
            inorder(root->getRightNode());
            std::cout<<")";
        }
    }
    Node* root;
public:
    BinaryTree(){
        root = nullptr;
    }
    ~BinaryTree(){
        destroyTree(root);
    }
    void insertValue(T value) {
        root = insert(root, value);
    }

    void deleteValue(T value) {
        root = deleteNode(root, value);
    }

    bool searchValue(T value) {
        if (search(root, value) == nullptr) return false;
        return true;
    }

    void printTree() {
        inorder(root);
        std::cout << '\n';
    }
};



#endif //A_BINARYTREE_HPP
