//
// Created by login on 30.10.2021.
//

#ifndef REV_2_ST__NODE_HPP
#define REV_2_ST__NODE_HPP
enum  Node_color {BLACK, RED};

struct Node{
    explicit Node(short data_, Node* mother = nullptr){
        data = data_;
        pMother = mother;
    }
    Node* pRight = nullptr;
    Node* pLeft = nullptr;
    Node* pMother = nullptr;
    Node_color color = RED;
    short data;
};
#endif //REV_2_ST__NODE_HPP
