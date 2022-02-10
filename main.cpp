#include <iostream>
#include "RB_tree.hpp"

using std::cout;
using std::endl;

int main() {
    RB_Tree tree{};
    short input_data;
    cout << "<Is Empty>\n";
    do{
        cout << "\nWhat do you want to do?\n" << endl;
        cout << "1.Insert\n" << endl;
        cout << "2.Delete\n" << endl;
        cout << "3.Show\n" << endl;
        cout << "4.Inorder\n" << endl;
        cout << "5.Preorder\n" << endl;
        cout << "6.Postorder\n" << endl;
        cout << "7.Exit\n" << endl;
        cout << "Enter your choice:";
        std::cin >> input_data;
        switch (input_data) {
            case 1:
                cout << "\nEnter The Data for Inserting:";
                std::cin >> input_data;
                cout << "\nInserting!\n\n" << endl;
                tree.inserting(input_data);
                break;
            case 2:
                cout << "\nEnter The Data for Deleting:";
                std::cin >> input_data;
                tree.deleting(input_data);
                break;
            case 3:
                cout << "\n";
                tree.show();
                break;
            case 4:
                cout << "\n";
                tree.in_order();
                cout << "\n";
                break;
            case 5:
                cout << "\n";
                tree.pre_order();
                cout << "\n";
                break;
            case 6:
                cout << "\n";
                tree.post_order();
                cout << "\n";
                break;
            case 7:
                cout << "\nExiting......" << endl;
                tree.exiting();
                exit(1);
            default:
                cout << "Please Enter a valid number!!\n" << endl;
                break;
        }
    } while (true);
}
