// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std;

TEST(empty_tree_test) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  ASSERT_TRUE(tree.size() == 0);
  ASSERT_TRUE(tree.height() == 0);
  ASSERT_TRUE(tree.max_element() == tree.end());
  ASSERT_TRUE(tree.min_element() == tree.end());
  ASSERT_TRUE(tree.min_greater_than(0) == tree.end());
  ASSERT_TRUE(tree.min_greater_than(100) == tree.end());
  ostringstream output;
  tree.traverse_inorder(output);
  ASSERT_EQUAL(output.str(), "");
  tree.traverse_preorder(output);
  ASSERT_EQUAL(output.str(), "");
  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(single_node_test) {
  BinarySearchTree<int> tree;
  tree.insert(1);
  ASSERT_FALSE(tree.empty());
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_EQUAL(*tree.max_element(), 1);
  ASSERT_EQUAL(*tree.min_element(), 1);
  ASSERT_EQUAL(tree.min_greater_than(1), tree.end());
  ostringstream output;
  tree.traverse_inorder(output);
  ASSERT_EQUAL(output.str(), "1 ");
  tree.traverse_preorder(output);
  ASSERT_EQUAL(output.str(), "1 1 ");
  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(multiple_node_test) {
  ostringstream outputinorder;  
  ostringstream outputpreorder;  
  BinarySearchTree<int> tree1;

  tree1.insert(2);
  tree1.insert(1);
  
  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree1.size() == 2);
  ASSERT_TRUE(tree1.height() == 2);
  ASSERT_EQUAL(*tree1.max_element(), 2);
  ASSERT_EQUAL(*tree1.min_element(), 1);
  ASSERT_EQUAL(tree1.min_greater_than(2), tree1.end());
  tree1.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 ");
  tree1.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 1 ");
  ASSERT_TRUE(tree1.check_sorting_invariant());
  
  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();

  BinarySearchTree<int> tree2;    

  tree2.insert(2);
  tree2.insert(3);

  ASSERT_FALSE(tree2.empty());
  ASSERT_TRUE(tree2.size() == 2);
  ASSERT_TRUE(tree2.height() == 2);
  ASSERT_EQUAL(*tree2.max_element(), 3);
  ASSERT_EQUAL(*tree2.min_element(), 2);
  ASSERT_EQUAL(*tree2.min_greater_than(1), 2);
  tree2.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "2 3 ");
  tree2.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 3 ");
  ASSERT_TRUE(tree2.check_sorting_invariant());

  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();

  tree1.insert(3);
  tree2.insert(1);

  ASSERT_EQUAL(tree1.size(), 3);
  ASSERT_EQUAL(tree2.size(), 3);
  ASSERT_EQUAL(tree1.height(), 2);
  ASSERT_EQUAL(tree2.height(), 2);
  ASSERT_EQUAL(*tree1.max_element(), 3);
  ASSERT_EQUAL(*tree2.min_element(), 1);
  ASSERT_EQUAL(*tree1.min_greater_than(2), 3);
  ASSERT_EQUAL(*tree2.min_greater_than(1), 2);
  tree1.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 ");
  tree1.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 1 3 ");
  ASSERT_TRUE(tree1.check_sorting_invariant());

  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();

  tree2.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 ");
  tree2.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 1 3 ");
  ASSERT_TRUE(tree1.check_sorting_invariant());
}

TEST(single_branch_test) {
  ostringstream outputinorder;  
  ostringstream outputpreorder;  
  BinarySearchTree<int> tree1;

  tree1.insert(1);
  tree1.insert(2);
  tree1.insert(3);
  
  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree1.size() == 3);
  ASSERT_TRUE(tree1.height() == 3);
  ASSERT_EQUAL(*tree1.max_element(), 3);
  ASSERT_EQUAL(*tree1.min_element(), 1);
  ASSERT_EQUAL(tree1.min_greater_than(3), tree1.end());
  tree1.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 ");
  tree1.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "1 2 3 ");
  ASSERT_TRUE(tree1.check_sorting_invariant());
  
  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();

  BinarySearchTree<int> tree2;    

  tree2.insert(3);
  tree2.insert(2);
  tree2.insert(1);

  ASSERT_FALSE(tree2.empty());
  ASSERT_TRUE(tree2.size() == 3);
  ASSERT_TRUE(tree2.height() == 3);
  ASSERT_EQUAL(*tree2.max_element(), 3);
  ASSERT_EQUAL(*tree2.min_element(), 1);
  ASSERT_EQUAL(*tree2.min_greater_than(1), 2);
  tree2.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 ");
  tree2.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "3 2 1 ");
  ASSERT_TRUE(tree2.check_sorting_invariant());
}

TEST(skewed_branch_test) {
  ostringstream outputinorder;  
  ostringstream outputpreorder;  
  BinarySearchTree<int> tree1;

  tree1.insert(2);
  tree1.insert(1);
  tree1.insert(3);
  tree1.insert(4);
  
  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree1.size() == 4);
  ASSERT_TRUE(tree1.height() == 3);
  ASSERT_EQUAL(*tree1.max_element(), 4);
  ASSERT_EQUAL(*tree1.min_element(), 1);
  ASSERT_EQUAL(*tree1.min_greater_than(*tree1.begin()), 2);
  tree1.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 4 ");
  tree1.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 1 3 4 ");
  ASSERT_TRUE(tree1.check_sorting_invariant());
  
  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();
  
  BinarySearchTree<int> tree2;

  tree2.insert(4);
  tree2.insert(3);
  tree2.insert(5);
  tree2.insert(2);
  tree2.insert(1);
  tree2.insert(6);
  
  ASSERT_FALSE(tree2.empty());
  ASSERT_TRUE(tree2.size() == 6);
  ASSERT_TRUE(tree2.height() == 4);
  ASSERT_EQUAL(*tree2.max_element(), 6);
  ASSERT_EQUAL(*tree2.min_element(), 1);
  ASSERT_EQUAL(*tree2.min_greater_than(*tree2.begin()), 2);
  tree2.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "1 2 3 4 5 6 ");
  tree2.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "4 3 2 1 5 6 ");
  ASSERT_TRUE(tree2.check_sorting_invariant());

}

TEST(complex_tree_test){
  ostringstream outputinorder;  
  ostringstream outputpreorder;
  BinarySearchTree<int> tree;

  tree.insert(10);
  ASSERT_EQUAL(*tree.min_element(), 10);
  ASSERT_EQUAL(*tree.max_element(), 10);
  ASSERT_TRUE(tree.height() == 1);
  tree.insert(5);
  ASSERT_EQUAL(*tree.min_element(), 5);
  ASSERT_TRUE(tree.height() == 2);
  tree.insert(15);
  ASSERT_EQUAL(*tree.max_element(), 15);
  ASSERT_TRUE(tree.height() == 2);
  tree.insert(7);
  ASSERT_TRUE(tree.height() == 3);
  tree.insert(4);
  ASSERT_EQUAL(*tree.min_element(), 4);
  ASSERT_TRUE(tree.height() == 3);
  tree.insert(2);
  ASSERT_EQUAL(*tree.min_element(), 2);
  ASSERT_TRUE(tree.height() == 4);
  tree.insert(3);
  ASSERT_TRUE(tree.height() == 5);
  ASSERT_EQUAL(*tree.max_element(), 15);
  tree.insert(17);
  ASSERT_EQUAL(*tree.max_element(), 17);
  ASSERT_TRUE(tree.height() == 5);
  tree.insert(13);
  ASSERT_TRUE(tree.height() == 5);
  tree.insert(11);
  ASSERT_TRUE(tree.height() == 5);
  tree.insert(12);
  ASSERT_TRUE(tree.height() == 5);
  tree.insert(16);
  ASSERT_TRUE(tree.height() == 5);
  
  ASSERT_FALSE(tree.empty());
  ASSERT_TRUE(tree.size() == 12);
  ASSERT_EQUAL(*tree.max_element(), 17);
  BinarySearchTree<int>::Iterator i = tree.begin();
  for(int x = 0; x < 11; x++){
    i++;
  }
  ASSERT_TRUE(*tree.max_element() == *i);
  ASSERT_EQUAL(*tree.min_element(), 2);
  ASSERT_EQUAL(*tree.min_greater_than(-15), 2);
  ASSERT_EQUAL(*tree.min_greater_than(1), 2);
  ASSERT_EQUAL(*tree.min_greater_than(2), 3);
  ASSERT_EQUAL(*tree.min_greater_than(3), 4);
  ASSERT_EQUAL(*tree.min_greater_than(4), 5);
  ASSERT_EQUAL(*tree.min_greater_than(5), 7);
  ASSERT_EQUAL(*tree.min_greater_than(6), 7);
  ASSERT_EQUAL(*tree.min_greater_than(7), 10);
  ASSERT_EQUAL(*tree.min_greater_than(8), 10);
  ASSERT_EQUAL(*tree.min_greater_than(9), 10);
  ASSERT_EQUAL(*tree.min_greater_than(10), 11);
  ASSERT_EQUAL(*tree.min_greater_than(11), 12);
  ASSERT_EQUAL(*tree.min_greater_than(12), 13);
  ASSERT_EQUAL(*tree.min_greater_than(13), 15);
  ASSERT_EQUAL(*tree.min_greater_than(14), 15);
  ASSERT_EQUAL(*tree.min_greater_than(15), 16);
  ASSERT_EQUAL(*tree.min_greater_than(16), 17);
  ASSERT_EQUAL(tree.min_greater_than(17), tree.end());
  tree.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "2 3 4 5 7 10 11 12 13 15 16 17 ");
  tree.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "10 5 4 2 3 7 15 13 11 12 17 16 ");
  ASSERT_TRUE(tree.check_sorting_invariant());
  vector<int> output = {2,3,4,5,7,10,11,12,13,15,16,17};
  BinarySearchTree<int>::Iterator find = tree.begin();
  int x = 0;
  while(find != tree.end()){
    ASSERT_EQUAL(find, tree.find(output[x]));
    find++;
    x++;
  }
}

TEST(out_of_order_tree){
  ostringstream outputinorder;  
  ostringstream outputpreorder;  
  BinarySearchTree<int> tree1;
  tree1.insert(2);
  tree1.insert(1);
  tree1.insert(3);

  *tree1.begin() = 5;

  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree1.size() == 3);
  ASSERT_TRUE(tree1.height() == 2);
  tree1.traverse_inorder(outputinorder);
  ASSERT_EQUAL(outputinorder.str(), "5 2 3 ");
  tree1.traverse_preorder(outputpreorder);
  ASSERT_EQUAL(outputpreorder.str(), "2 5 3 ");
  ASSERT_FALSE(tree1.check_sorting_invariant());

  outputinorder.str("");
  outputinorder.clear();
  outputpreorder.str("");
  outputpreorder.clear();

  BinarySearchTree<int> tree;

  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(7);
  tree.insert(4);
  tree.insert(2);
  tree.insert(3);
  tree.insert(17);
  tree.insert(13);
  tree.insert(11);
  tree.insert(12);
  tree.insert(16);
  
  ASSERT_TRUE(tree.check_sorting_invariant());
  *tree.find(3) = 1;
  ASSERT_FALSE(tree.check_sorting_invariant());
  *tree.find(5) = 10;
  ASSERT_FALSE(tree.check_sorting_invariant());
  *tree.find(11) = 12;
  ASSERT_FALSE(tree.check_sorting_invariant());
  *tree.find(12) = 11;
  ASSERT_FALSE(tree.check_sorting_invariant());
  *tree.find(10) = 0;
  ASSERT_FALSE(tree.check_sorting_invariant());
  *tree.find(13) = 21;
  ASSERT_FALSE(tree.check_sorting_invariant());


}

TEST(copy_and_assignment_constructor){
  ostringstream outputpreorder1;  
  ostringstream outputpreorder2;  
  ostringstream outputpreorder3;  
  BinarySearchTree<int> tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);
  tree.insert(4);
  tree.insert(6);
  tree.insert(5);

  BinarySearchTree<int> copy(tree);
  BinarySearchTree<int> assign = tree;
  tree.traverse_preorder(outputpreorder1);
  copy.traverse_preorder(outputpreorder2);
  assign.traverse_preorder(outputpreorder3);
  ASSERT_EQUAL(outputpreorder1.str(), outputpreorder2.str());
  ASSERT_EQUAL(outputpreorder1.str(), outputpreorder3.str());
  BinarySearchTree<int>::Iterator i1 = tree.begin();
  BinarySearchTree<int>::Iterator i2 = copy.begin();
  BinarySearchTree<int>::Iterator i3 = assign.begin();
  while(i1 != tree.end() || i2 != copy.end() || i3 != assign.end()){
     ASSERT_TRUE(*i1 == *i2);
     ASSERT_TRUE(*i1 == *i3);
     i1++;
     i2++;
     i3++;
  }
}


TEST_MAIN()