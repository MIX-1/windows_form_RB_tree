//
// Created by login on 30.10.2021.
//

#ifndef REV_2_ST__RB_TREE_HPP
#define REV_2_ST__RB_TREE_HPP
#include "node.hpp"
#include <set>
using std::cout;
using std::endl;

class RB_Tree{
public:
    RB_Tree(){pRoot = nullptr;}

    void inserting(short insert_data){
        if(!pRoot){
            pRoot = new Node(insert_data);
            insert_case1(pRoot);
        } else {
            inserting(insert_data, pRoot);
        }
    }

    void deleting(short delete_data){
        if(pRoot){
            deleting(delete_data, pRoot);
        }
    }

    void show(){
        short depth = 0;
        Node* ptr;
        if(!pRoot){
            cout << "\n<Is Empty>\n";
            return;
        }
        depth = go_to_biggest_depth(depth, pRoot);
        ptr = go_to_biggest_ptr(pRoot);
        print_all(depth, ptr, ptr->data);
    }

    void in_order(){
        if(pRoot){
            Node* ptr = go_to_smallest_ptr(pRoot);
            in_order_print(ptr, ptr->data);
        }
    }

    void pre_order(){
        if(pRoot){
            std::set<short> printed;
            pre_order_print(pRoot, printed);
        }
    }

    void post_order(){
        if(pRoot){
            std::set<short> printed;
            post_order_print(go_to_smallest_ptr(pRoot), printed);
        }
    }

    void exiting(){
        if(pRoot){
            exiting_remove(go_to_smallest_ptr(pRoot));
        }
    }
private:
    void inserting(short insert_data, Node* ptr){
        if (insert_data > ptr->data){
            if(!ptr->pRight){
                ptr->pRight = new Node(insert_data, ptr);
                insert_case1(ptr->pRight);
            } else {
                inserting(insert_data, ptr->pRight);
            }
        } else if(insert_data < ptr->data){
            if(!ptr->pLeft){
                ptr->pLeft = new Node(insert_data, ptr);
                insert_case1(ptr->pLeft);
            } else {
                inserting(insert_data, ptr->pLeft);
            }
        } else{
            return;
        }
    }

    Node* grandma(Node* ptr){return (ptr && ptr->pMother) ? ptr->pMother->pMother : nullptr;}

    Node* uncle(Node* ptr){
        Node* g = grandma(ptr);

        if(!g)
            return nullptr;
        if (ptr->pMother == g->pLeft)
            return g->pRight;
        else
            return g->pLeft;
    }

    void rotate_left(Node* ptr){
        Node *pivot = ptr->pRight;

        pivot->pMother = ptr->pMother;
        if(!pivot->pMother){
            pRoot = pivot;
        }
        if (ptr->pMother) {
            if (ptr->pMother->pLeft == ptr)
                ptr->pMother->pLeft = pivot;
            else
                ptr->pMother->pRight = pivot;
        }

        ptr->pRight = pivot->pLeft;
        if (pivot->pLeft)
            pivot->pLeft->pMother = ptr;

        ptr->pMother = pivot;
        pivot->pLeft = ptr;
    }

    void rotate_right(Node* ptr){
        Node *pivot = ptr->pLeft;

        pivot->pMother = ptr->pMother;
        if(!pivot->pMother){
            pRoot = pivot;
        }
        if (ptr->pMother) {
            if (ptr->pMother->pLeft == ptr)
                ptr->pMother->pLeft = pivot;
            else
                ptr->pMother->pRight = pivot;
        }

        ptr->pLeft = pivot->pRight;
        if (pivot->pRight)
            pivot->pRight->pMother = ptr;

        ptr->pMother = pivot;
        pivot->pRight = ptr;
    }

    void insert_case1(Node* ptr)
    {
        if (!ptr->pMother)
            ptr->color = BLACK;
        else
            insert_case2(ptr);
    }

    void insert_case2(Node* ptr)
    {
        if (ptr->pMother->color == BLACK)
            return;
        else
            insert_case3(ptr);
    }

    void insert_case3(Node* ptr)
    {
        Node* u = uncle(ptr), *g;

        if (u && (u->color == RED)) {
            ptr->pMother->color = BLACK;
            u->color = BLACK;
            g = grandma(ptr);
            g->color = RED;
            insert_case1(g);
        } else {
            insert_case4(ptr);
        }
    }

    void insert_case4(Node* ptr)
    {
        Node *g = grandma(ptr);

        if ((ptr == ptr->pMother->pRight) && (ptr->pMother == g->pLeft)) {
            rotate_left(ptr->pMother);
            ptr = ptr->pLeft;
        } else if ((ptr == ptr->pMother->pLeft) && (ptr->pMother == g->pRight)) {
            rotate_right(ptr->pMother);
            ptr = ptr->pRight;
        }
        insert_case5(ptr);
    }

    void insert_case5(Node* ptr)
    {
        Node *g = grandma(ptr);

        ptr->pMother->color = BLACK;
        g->color = RED;
        if ((ptr == ptr->pMother->pLeft) && (ptr->pMother == g->pLeft)) {
            rotate_right(g);
        } else if((ptr == ptr->pMother->pRight) && (ptr->pMother == g->pRight)){
            rotate_left(g);
        }
    }

    void deleting(short delete_data, Node* ptr){
        if (delete_data > ptr->data){
            if(ptr->pRight){
                deleting(delete_data, ptr->pRight);
            }
        } else if(delete_data < ptr->data){
            if(ptr->pLeft){
                deleting(delete_data, ptr->pLeft);
            }
        } else{
            if(is_leaf(ptr->pLeft) && is_leaf(ptr->pRight))
                delete_none_child(ptr);
            else if(is_leaf(ptr->pLeft) || is_leaf(ptr->pRight))
                delete_one_child(ptr);
            else
                delete_two_child(ptr);
        }
    }

    void delete_none_child(Node* ptr){
        if(ptr->color == RED){
            if(ptr->pMother){
                if(ptr->pMother->data > ptr->data){
                    ptr->pMother->pLeft = nullptr;
                } else{
                    ptr->pMother->pRight = nullptr;
                }
            } else {
                pRoot = nullptr;
            }
        } else
            delete_case2(ptr);
        cout << "deleting......\n";
        delete ptr;
    }

    Node* sibling(Node* ptr){return (ptr == ptr->pMother->pLeft) ? ptr->pMother->pRight : ptr->pMother->pLeft;}

    bool  is_leaf(Node* ptr){return ptr == nullptr;}

    void replace_node(Node* ptr, Node* child) {
        child->pMother = ptr->pMother;
        if(!ptr->pMother)
            pRoot = child;
        else{
            if (ptr == ptr->pMother->pLeft)
                ptr->pMother->pLeft = child;
            else if(ptr == ptr->pMother->pRight)
                ptr->pMother->pRight = child;
        }
    }

    void delete_one_child(Node* ptr){
        Node* child = is_leaf(ptr->pRight) ? ptr->pLeft : ptr->pRight;

        replace_node(ptr, child);
        if (ptr->color == BLACK) {
            if (child->color == RED)
                child->color = BLACK;
            else{
                cout << "too......\n";
                delete_case1(child);
            }
        }
        cout << "deleting......\n";
        delete(ptr);
    }

    void delete_case1(Node* ptr){
        if (ptr->pMother)
            delete_case2(ptr);
    }

    void delete_case2(Node* ptr){
        Node* s = sibling(ptr);

        if (s->color == RED) {
            ptr->pMother->color = RED;
            s->color = BLACK;
            if (ptr == ptr->pMother->pLeft)
                rotate_left(ptr->pMother);
            else
                rotate_right(ptr->pMother);
        }
        delete_case3(ptr);
    }

    void delete_case3(Node* ptr){
        Node* s = sibling(ptr);

        if ((ptr->pMother->color == BLACK) &&
            (s->color == BLACK) &&
            (!s->pLeft || (s->pLeft->color == BLACK)) &&
            (!s->pRight || (s->pRight->color == BLACK))) {
            s->color = RED;
            delete_case1(ptr->pMother);
        } else
            delete_case4(ptr);
    }

    void delete_case4(Node* ptr){
        Node* s = sibling(ptr);

        if ((ptr->pMother->color == RED) &&
            (s->color == BLACK) &&
            (s->pLeft->color == BLACK) &&
            (s->pRight->color == BLACK)) {
            s->color = RED;
            ptr->pMother->color = BLACK;
        } else
            delete_case5(ptr);
    }

    void delete_case5(Node* ptr){
        Node* s = sibling(ptr);

        if  (s->color == BLACK) {
            if ((ptr == ptr->pMother->pLeft) &&
                (s->pRight->color == BLACK) &&
                (s->pLeft->color == RED)) {
                s->color = RED;
                s->pLeft->color = BLACK;
                rotate_right(s);
            } else if ((ptr == ptr->pMother->pRight) &&
                       (s->pLeft->color == BLACK) &&
                       (s->pRight->color == RED)) {
                s->color = RED;
                s->pRight->color = BLACK;
                rotate_left(s);
            }
        }
        delete_case6(ptr);
    }

    void delete_case6(Node* ptr){
        Node* s = sibling(ptr);

        s->color = ptr->pMother->color;
        ptr->pMother->color = BLACK;

        if (ptr == ptr->pMother->pLeft) {
            s->pRight->color = BLACK;
            rotate_left(ptr->pMother);
        } else {
            s->pLeft->color = BLACK;
            rotate_right(ptr->pMother);
        }
    }

    void delete_two_child(Node* ptr){
        Node* biggest_left_ptr = go_to_biggest_ptr(ptr->pLeft);
        std::swap(ptr->data, biggest_left_ptr->data);
        if(biggest_left_ptr->pMother->pRight == biggest_left_ptr){
            biggest_left_ptr->pMother->pRight = nullptr;
        } else{
            biggest_left_ptr->pMother->pLeft = nullptr;
        }
        delete biggest_left_ptr;
    }
    short go_to_biggest_depth(short depth, Node* ptr){
        if(ptr->pRight){
            ++depth;
            go_to_biggest_depth(depth, ptr->pRight);
        } else{
            return depth;
        }
    }

    Node* go_to_biggest_ptr(Node* ptr){
        if(ptr->pRight){
            go_to_biggest_ptr(ptr->pRight);
        } else{
            return ptr;
        }
    }

    Node* go_to_smallest_ptr(Node* ptr){
        if(ptr->pLeft){
            go_to_smallest_ptr(ptr->pLeft);
        } else{
            return ptr;
        }
    }

    void print(short depth, Node* ptr){
        for(short i = 0; i < depth; ++i){
            cout << "\t";
        }
        if(ptr->color == BLACK)
            cout << ptr->data << endl;
        else{
            cout << "\b<" << ptr->data << ">" << endl;
        }
    }

    void print_all(short depth, Node* ptr, short prev){
        if(ptr->data <= prev && (!ptr->pRight || (ptr->pRight->data > prev))){
            print(depth, ptr);
            if(ptr->pLeft){
                ++depth;
                if(ptr->pLeft->data < prev){
                    --prev;
                    print_all(depth, ptr->pLeft, prev);
                } else
                    print_all(depth, ptr->pLeft, ptr->pLeft->data);
            } else if(go_to_smallest_ptr(pRoot)->data == ptr->data){
                return;
            } else {
                --depth;
                if(ptr->pMother->data < prev)
                    print_all(depth, ptr->pMother, ptr->pMother->data);
                else{
                    print_all(depth, ptr->pMother, ptr->data);
                }
            }
        } else if(!ptr->pRight || ptr->pRight->data > prev){
            --depth;
            print_all(depth, ptr->pMother, prev);
        } else{
            ++depth;
            print_all(depth, ptr->pRight, prev);
        }
    }

    void in_order_print(Node* ptr, short  prev){
        if(ptr->data >= prev && (!ptr->pLeft || (ptr->pLeft->data < prev))){
            cout << ptr->data << " -> ";
            if(ptr->pRight){
                if(ptr->pRight->data > prev){
                    ++prev;
                    in_order_print(ptr->pRight, prev);
                } else
                    in_order_print(ptr->pRight, ptr->pRight->data);
            } else if(go_to_biggest_ptr(pRoot)->data == ptr->data){
                return;
            } else {
                if(ptr->pMother->data > prev)
                    in_order_print(ptr->pMother, ptr->pMother->data);
                else{
//                    ++prev;
                    in_order_print(ptr->pMother, prev);
                }
            }
        } else if(!ptr->pLeft || ptr->pLeft->data < prev){
            if(ptr->pMother->data > prev){
                in_order_print(ptr->pMother, ptr->pMother->data);
            } else{
                in_order_print(ptr->pMother, prev);
            }

        } else{
            in_order_print(ptr->pLeft, prev);
        }
    }

    void pre_order_print(Node* ptr, std::set<short> printed){
        if(ptr == nullptr){
            return;
        }
        if(printed.find(ptr->data) == printed.end()){
            cout << ptr->data << " -> ";
            printed.insert(ptr->data);
            if(ptr->pLeft){
                pre_order_print(ptr->pLeft, printed);
            } else if(ptr->pRight){
                pre_order_print(ptr->pRight, printed);
            } else {
                pre_order_print(ptr->pMother, printed);
            }
        } else if(!ptr->pRight || (printed.find(ptr->pRight->data) != printed.end())){
            if (!ptr->pLeft || (printed.find(ptr->pLeft->data) != printed.end())){
                pre_order_print(ptr->pMother, printed);
            } else {
                pre_order_print(ptr->pLeft, printed);
            }
        } else{
            pre_order_print(ptr->pRight, printed);
        }
    }

    void post_order_print(Node* ptr, std::set<short> printed){
        if(ptr->pLeft && (printed.find(ptr->pLeft->data) == printed.end())){
            post_order_print(ptr->pLeft, printed);
        } else if (ptr->pRight && (printed.find(ptr->pRight->data) == printed.end())){
            post_order_print(ptr->pRight, printed);
        } else {
            cout << ptr->data << " -> ";
            printed.insert(ptr->data);
            if(ptr == pRoot){
                return;
            }
            post_order_print(ptr->pMother, printed);
        }
    }

    void exiting_remove(Node* ptr){
        if(ptr->pLeft){
            exiting_remove(ptr->pLeft);
        } else if (ptr->pRight){
            exiting_remove(ptr->pRight);
        } else {
            Node* mother = ptr->pMother;
            delete_none_child(ptr);
            if(mother){
                exiting_remove(mother);
            }
        }
    }

    Node* pRoot;
};
#endif //REV_2_ST__RB_TREE_HPP
