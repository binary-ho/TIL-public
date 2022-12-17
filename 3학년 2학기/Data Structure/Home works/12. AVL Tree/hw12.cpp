#include "AVL.h"
int main() {
nodeptr root;
    int a, choice, findele, delele;
    bstree bst;
    bool flag = true;
    root = NULL;
    bst.insert(19, root);
    bst.insert(10, root);
    bst.insert(46, root);
    bst.insert(4, root);
    bst.insert(14, root);
    bst.insert(37, root);
    bst.insert(55, root);
    bst.insert(7, root);
    bst.insert(12, root);
    bst.insert(18, root);
    bst.insert(28, root);
    bst.insert(40, root);
    bst.insert(51, root);
    bst.insert(61, root);
    bst.insert(21, root);
    bst.insert(32, root);
    bst.insert(49, root);
    bst.insert(58, root);

    while (flag) {
        cout << "Enter the choice: (1 : search, 2 : add, 3 : delete, 4 : show, 0 : exit)";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter node to search:";
                cin >> findele;
                if (root != NULL) bst.search(findele, root);
                break;
            case 2:
                cout << "Enter a new value:";
                cin >> a;
                bst.insert(a, root);
                bst.show(root);
                break;
            case 3:
                cout << "Enter node to delete:";
                cin >> delele;
                bst.del(delele, root);
                bst.show(root);
                break;
            case 4:
                if (root != NULL) bst.show(root);
                break;
            case 0:
                cout << "\n\tThank your for using AVL maxTree program\n" << endl;
                flag = false;
                break;
            default: cout << "Sorry! wrong input\n" << endl; break;
        }
    }
    return 0;
}
