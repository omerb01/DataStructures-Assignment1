
#include "..\testMacros.h"
#include<iostream>



/*
    void inOrderPrint(ostream& os, Node<Type>* x ) const {
        if(x!=NULL){
            inOrderPrint(os, x->left_child);
            os<<"Key1 is: " <<x->key1<< " Key2 is: "<< x->key2<< " Height is: "<< x->height<<endl;
            inOrderPrint(os, x->right_child);
        }
    }
   friend ostream& operator<<(ostream& os, const AvlTree& a){
       a.inOrderPrint(os, a.root);
       return os;
   }
*/
class function{
public:
    bool operator()(Node<int> x){
        return true;
    }
};

//You should change to your own insert function, and your own AvlTree
//you must do an operator << for your avltree
//insert and remove everybody have
//there are some function  that you may not have,delete them if not.
bool testInsert(){
    AvlTree<int> tree;
    tree.insert(4,NULL);
    tree.insert(2,NULL);
    tree.insert(3,NULL);
    tree.insert(9,NULL);
    tree.insert(5,NULL);
    tree.insert(1,NULL);
    cout<<endl<<endl<<"---------------------tree 1--------------------"<<endl;
    cout<<tree;
    /*expected output
Key1 is: 1 Key2 is: 0 Height is: 0
Key1 is: 2 Key2 is: 0 Height is: 1
Key1 is: 3 Key2 is: 0 Height is: 2
Key1 is: 4 Key2 is: 0 Height is: 0
Key1 is: 5 Key2 is: 0 Height is: 1
Key1 is: 9 Key2 is: 0 Height is: 0
    **/

    AvlTree<int> tree2;
    cout<<endl<<endl<<"---------------------tree 2--------------------"<<endl;
    cout<<tree2;

    /*expected output
   **/

    AvlTree<int> tree3;
    tree3.insert(1,NULL);
    tree3.insert(2,NULL);
    tree3.insert(3,NULL);
    cout<<endl<<endl<<"---------------------tree 3--------------------"<<endl;
    cout<<tree3;

    /*expected output
  Key1 is: 1 Key2 is: 0 Height is: 0
Key1 is: 2 Key2 is: 0 Height is: 1
Key1 is: 3 Key2 is: 0 Height is: 0
   **/

    AvlTree<int> tree4;
    tree4.insert(3,NULL);
    tree4.insert(2,NULL);
    tree4.insert(1,NULL);
    cout<<endl<<endl<<"---------------------tree 4--------------------"<<endl;
    cout<<tree4;

    /*expected output
Key1 is: 1 Key2 is: 0 Height is: 0
Key1 is: 2 Key2 is: 0 Height is: 1
Key1 is: 3 Key2 is: 0 Height is: 0

*   */

    AvlTree<int> tree5;
    tree5.insert(2,NULL);
    tree5.insert(3,NULL);
    tree5.insert(1,NULL);
    cout<<endl<<endl<<"---------------------tree 5--------------------"<<endl;
    cout<<tree5;

    /*Key1 is: 1 Key2 is: 0 Height is: 0
Key1 is: 2 Key2 is: 0 Height is: 1
Key1 is: 3 Key2 is: 0 Height is: 0
     */

    return true;
}

bool testRemove(){
    AvlTree<int> tree1;

    cout<<endl<<"-------------------testremove1----------------"<<endl<<endl;
    tree1.remove(0);
    tree1.insert(1,NULL);
    //should do nothing
    tree1.remove(2);
    cout<<endl<<"-------------------testremove2----------------"<<endl<<endl;
    cout<<tree1;
    /*Key1 is: 1 Key2 is: 0 Height is: 0*/

    cout<<endl<<"-------------------testremove3----------------"<<endl<<endl;
    tree1.remove(1);
    cout<<tree1<<endl;
    //nothing
    tree1.insert(1,NULL);
    tree1.insert(2,NULL);
    tree1.remove(1);
    cout<<endl<<"-------------------testremove4----------------"<<endl<<endl;
    cout<<tree1<<endl;
    /*Key1 is: 2 Key2 is: 0 Height is: 0*/

    AvlTree<int> tree2;
    tree2.insert(2,NULL);
    tree2.insert(1,NULL);
    tree2.insert(8,NULL);
    tree2.insert(6,NULL);
    tree2.insert(5,NULL);
    tree2.insert(10,NULL);
    tree2.insert(9,NULL);
    tree2.remove(2);
    cout<<endl<<"-------------------testremove5----------------"<<endl<<endl;
    cout<<tree2;
    /*Key1 is: 1 Key2 is: 0 Height is: 0
Key1 is: 5 Key2 is: 0 Height is: 1
Key1 is: 6 Key2 is: 0 Height is: 2
Key1 is: 8 Key2 is: 0 Height is: 0
Key1 is: 9 Key2 is: 0 Height is: 1
Key1 is: 10 Key2 is: 0 Height is: 0*/

    tree2.remove(1);
    cout<<endl<<"-------------------testremove6----------------"<<endl<<endl;
    cout<<tree2;

    /*   Key1 is: 5 Key2 is: 0 Height is: 0
   Key1 is: 6 Key2 is: 0 Height is: 2
   Key1 is: 8 Key2 is: 0 Height is: 0
   Key1 is: 9 Key2 is: 0 Height is: 1
   Key1 is: 10 Key2 is: 0 Height is: 0*/

    tree2.remove(5);
    cout<<endl<<"-------------------testremove7----------------"<<endl<<endl;
    cout<<tree2;

    /*  Key1 is: 6 Key2 is: 0 Height is: 0
Key1 is: 8 Key2 is: 0 Height is: 2
Key1 is: 9 Key2 is: 0 Height is: 1
Key1 is: 10 Key2 is: 0 Height is: 0*/


    tree2.remove(6);
    cout<<endl<<"-------------------testremove8----------------"<<endl<<endl;
    cout<<tree2;

/*Key1 is: 8 Key2 is: 0 Height is: 0
Key1 is: 9 Key2 is: 0 Height is: 1
Key1 is: 10 Key2 is: 0 Height is: 0
 */

    tree2.remove(9);
    cout<<endl<<"-------------------testremove9----------------"<<endl<<endl;
    cout<<tree2;
/*Key1 is: 8 Key2 is: 0 Height is: 0
Key1 is: 10 Key2 is: 0 Height is: 1*/


    tree2.remove(8);
    cout<<endl<<"-------------------testremove10----------------"<<endl<<endl;
    cout<<tree2;
/*Key1 is: 8 Key2 is: 0 Height is: 0*/


    return true;
}

bool array2tree(){
    AvlTree<int> tree;
    tree.insert(4,NULL);
    tree.insert(2,NULL);
    tree.insert(3,NULL);
    tree.insert(9,NULL);
    tree.insert(5,NULL);
    tree.insert(1,NULL);
    Node<int>* arr = new Node<int>[tree.getSize()];
    tree.tree2array(arr);
    AvlTree<int> new_tree;
    array2tree(new_tree,arr,tree.getSize());
    cout<< new_tree;
    delete(arr);
    return true;
}

bool mergeArrays(){
    AvlTree<int> tree;
    tree.insert(4,NULL);
    tree.insert(2,NULL);
    tree.insert(3,NULL);
    tree.insert(9,NULL);
    tree.insert(5,NULL);
    tree.insert(1,NULL);
    Node<int>* arr = new Node<int>[tree.getSize()];
    tree.tree2array(arr);

    AvlTree<int> tree1;
    tree1.insert(-10,NULL);
    tree1.insert(100,NULL);
    tree1.insert(102,NULL);

    Node<int>* arr1 = new Node<int>[tree1.getSize()];
    tree1.tree2array(arr1);

    Node<int>* arr2 = new Node<int>[tree.getSize() + tree1.getSize()];


    mergeArrays(arr,arr1,6,3,arr2);

    for(int i=0; i<6; i++){
        cout<<arr[i].key1;
        cout<<" ";
    }
    cout<<endl;

    for(int i=0; i<3; i++){
        cout<<arr1[i].key1;
        cout<<" ";
    }
    cout<<endl;
    for(int i=0; i<9; i++){
        cout<<arr2[i].key1;
        cout<<" ";
    }

    cout<<endl;
    delete[](arr);
    delete[](arr1);
    delete[](arr2);
    return true;
}

bool testMergeTree(){

    AvlTree<int> tree;
    tree.insert(4,NULL);
    tree.insert(2,NULL);
    tree.insert(3,NULL);
    tree.insert(9,NULL);
    tree.insert(5,NULL);
    tree.insert(1,NULL);

    AvlTree<int> tree2;
    tree2.insert(100,NULL);
    tree2.insert(101,NULL);
    tree2.insert(102,NULL);
    tree2.insert(103,NULL);
    tree2.insert(104,NULL);
    tree2.insert(105,NULL);

    AvlTree<int> tree3;

    mergeTrees(tree,tree2,tree3,function());
    cout<<tree3;


    return true;
}


bool tree2array(){
    AvlTree<int> tree;
    tree.insert(4,NULL);
    tree.insert(2,NULL);
    tree.insert(3,NULL);
    tree.insert(9,NULL);
    tree.insert(5,NULL);
    tree.insert(1,NULL);
    Node<int>* arr = new Node<int>[tree.getSize()];
    tree.tree2array(arr);
    for(int i=0;i<6;i++){
        cout<<(arr+i)->key1;
    }
    cout<<endl;
    delete(arr);
    return true;
}

int main() {
    RUN_TEST(testInsert);
    RUN_TEST(testRemove);
    RUN_TEST(tree2array);
    RUN_TEST(array2tree);
    RUN_TEST(mergeArrays);
    RUN_TEST(testMergeTree);
}