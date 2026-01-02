#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>


TEST(test_stub) {
    using BST = BinarySearchTree<int>;

    BST b;
    ASSERT_TRUE(b.empty());
    ASSERT_EQUAL(b.size(), 0u);
    ASSERT_EQUAL(b.height(), 0u);
    ASSERT_TRUE(b.begin() == b.end());
    ASSERT_TRUE(b.min_element() == b.end());
    ASSERT_TRUE(b.max_element() == b.end());

    b.insert(42);
    ASSERT_FALSE(b.empty());
    ASSERT_EQUAL(b.size(), 1u);
    ASSERT_EQUAL(b.height(), 1u);
    ASSERT_TRUE(b.begin() != b.end());
    ASSERT_EQUAL(*b.begin(), 42);
    ASSERT_EQUAL(*b.min_element(), 42);
    ASSERT_EQUAL(*b.max_element(), 42);
    ASSERT_TRUE(b.min_greater_than(42) == b.end());
    ASSERT_TRUE(b.min_greater_than(0) != b.end());
    ASSERT_EQUAL(*b.min_greater_than(0), 42);

    b.insert(20);
    b.insert(60);
    b.insert(10);
    b.insert(30);
    b.insert(50);
    b.insert(70);

    ASSERT_EQUAL(b.size(), 7u);
    ASSERT_EQUAL(b.height(), 3u);

    std::ostringstream os;
    b.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), std::string("10 20 30 42 50 60 70 "));

    std::ostringstream os2;
    b.traverse_preorder(os2);
    ASSERT_EQUAL(os2.str(), std::string("42 20 10 30 60 50 70 "));

    auto it = b.begin();
    ASSERT_EQUAL(*it, 10);
    ++it; ASSERT_EQUAL(*it, 20);
    ++it; ASSERT_EQUAL(*it, 30);
    ++it; ASSERT_EQUAL(*it, 42);
    ++it; ASSERT_EQUAL(*it, 50);
    ++it; ASSERT_EQUAL(*it, 60);
    ++it; ASSERT_EQUAL(*it, 70);
    ++it; ASSERT_TRUE(it == b.end());

    auto mgt = b.min_greater_than(30);
    ASSERT_TRUE(mgt != b.end());
    ASSERT_EQUAL(*mgt, 42);
    ASSERT_TRUE(b.min_greater_than(100) == b.end());

    ASSERT_TRUE(b.find(50) != b.end());
    ASSERT_TRUE(b.find(999) == b.end());

    BST copy_b(b);
    ASSERT_EQUAL(copy_b.size(), b.size());
    std::ostringstream osb, osc;
    b.traverse_inorder(osb);
    copy_b.traverse_inorder(osc);
    ASSERT_EQUAL(osb.str(), osc.str());

    BST assign_b;
    assign_b = b;
    std::ostringstream osa;
    assign_b.traverse_inorder(osa);
    ASSERT_EQUAL(osa.str(), osb.str());

    struct PairFirstComp {
        bool operator()(const std::pair<int,int> &a, const std::pair<int,int> &b) const {
            return a.first < b.first;
        }
    };
    BinarySearchTree<std::pair<int,int>, PairFirstComp> ptre;
    ptre.insert({1,100}); ptre.insert({2,200}); ptre.insert({3,300});
    auto pcopy = ptre;
    auto pit2 = ptre.find({2, 0});
    ASSERT_TRUE(pit2 != ptre.end());
    pit2->second = 9999;
    ASSERT_EQUAL(pit2->second, 9999);
    auto pcopy_it = pcopy.find({2, 0});
    ASSERT_TRUE(pcopy_it != pcopy.end());
    ASSERT_EQUAL(pcopy_it->second, 200);

    struct Rev { bool operator()(int a, int b) const { return a > b; } };
    BinarySearchTree<int, Rev> br;
    br.insert(1); br.insert(2); br.insert(3);
    std::ostringstream osr;
    br.traverse_inorder(osr);
    ASSERT_EQUAL(osr.str(), std::string("3 2 1 "));

    BinarySearchTree<std::pair<int,int>> bp;
    bp.insert({1,10}); bp.insert({2,20}); bp.insert({3,30});
    auto pit = bp.begin();
    ASSERT_TRUE(pit != bp.end());
    ASSERT_EQUAL(pit->first, 1);
    ASSERT_EQUAL(pit->second, 10);
    ++pit;
    ASSERT_EQUAL(pit->first, 2);
    ASSERT_EQUAL(pit->second, 20);

    BST inv;
    inv.insert(0); inv.insert(1); inv.insert(2);
    ASSERT_TRUE(inv.check_sorting_invariant());
    *inv.begin() = 10; 
    ASSERT_FALSE(inv.check_sorting_invariant());

    BST mm;
    ASSERT_TRUE(mm.min_element() == mm.end());
    ASSERT_TRUE(mm.max_element() == mm.end());
    mm.insert(5);
    ASSERT_EQUAL(*mm.min_element(), 5);
    ASSERT_EQUAL(*mm.max_element(), 5);
    mm.insert(3); mm.insert(7);
    ASSERT_EQUAL(*mm.min_element(), 3);
    ASSERT_EQUAL(*mm.max_element(), 7);

    ASSERT_TRUE(b.size() >= 1u);
    ASSERT_TRUE(b.height() >= 1u);

    BinarySearchTree<int> t_more;
    t_more.insert(10); t_more.insert(20); t_more.insert(30); t_more.insert(40);
    auto a = t_more.min_greater_than(0);
    ASSERT_TRUE(a != t_more.end()); ASSERT_EQUAL(*a, 10);
    auto b2 = t_more.min_greater_than(10);
    ASSERT_TRUE(b2 != t_more.end()); ASSERT_EQUAL(*b2, 20);
    auto c2 = t_more.min_greater_than(25);
    ASSERT_TRUE(c2 != t_more.end()); ASSERT_EQUAL(*c2, 30);
    ASSERT_TRUE(t_more.min_greater_than(100) == t_more.end());

    BinarySearchTree<int> t1;
    t1.insert(5);
    ASSERT_EQUAL(t1.height(), 1u);
    t1.insert(3);
    ASSERT_EQUAL(t1.height(), 2u);

    BinarySearchTree<int> left_tree;
    left_tree.insert(5); left_tree.insert(4); left_tree.insert(3);
    std::ostringstream os_left;
    left_tree.traverse_preorder(os_left);
    ASSERT_EQUAL(os_left.str(), std::string("5 4 3 "));

    BinarySearchTree<int> t_rand;
    std::vector<int> vals(200);
    for (int i = 0; i < 200; ++i) vals[i] = i;
    std::mt19937 rng(12345);
    std::shuffle(vals.begin(), vals.end(), rng);
    for (int v : vals) t_rand.insert(v);
    ASSERT_EQUAL(t_rand.size(), 200u);
    std::ostringstream os_rand;
    t_rand.traverse_inorder(os_rand);
    std::string expected;
    for (int i = 0; i < 200; ++i) { expected += std::to_string(i) + " "; }
    ASSERT_EQUAL(os_rand.str(), expected);
    ASSERT_TRUE(t_rand.check_sorting_invariant());

    BinarySearchTree<int> t_right;
    const int N = 200;
    for (int i = 1; i <= N; ++i) t_right.insert(i);
    ASSERT_EQUAL(t_right.size(), static_cast<size_t>(N));
    ASSERT_EQUAL(t_right.height(), static_cast<size_t>(N));

    BinarySearchTree<int> empty_bst;
    ASSERT_TRUE(empty_bst.begin() == empty_bst.end());

    BinarySearchTree<int> small_b;
    small_b.insert(2); small_b.insert(1); small_b.insert(3);
    auto it2 = small_b.begin();
    ASSERT_EQUAL(*it2, 1);
    auto old2 = it2++;
    ASSERT_EQUAL(*old2, 1);
    ASSERT_EQUAL(*it2, 2);
    it2++; ASSERT_EQUAL(*it2, 3);
    it2++; ASSERT_TRUE(it2 == small_b.end());
}

TEST_MAIN()
