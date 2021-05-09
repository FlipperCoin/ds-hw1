//
// Created by Itai on 08/05/2021.
//

#include "gtest/gtest.h"
#include "btree_23.h"

class Tests : public ::testing::Test {

protected:

    void SetUp() override {

    }

    void TearDown() override {
    }
};

#include "string"
#include "sstream"
using std::string;
using std::ostringstream;
struct Int {
    int n;
    Int(){}
    Int(int n) : n(n){}
    string str() const {
        ostringstream stream;
        stream << n;
        return stream.str();
    }
    bool operator<(const Int& other) const{
        return n < other.n;
    };
    bool operator>=(const Int& other) const{
        return n >= other.n;
    }
    bool operator!=(const Int& other) const{
        return n != other.n;
    }
    bool operator==(const Int& other) const {
        return n == other.n;
    }
};

void link(SharedPointer<TreeNode<Int>> node) {
    for (int i = 0; i < node->Sons; i++) {
        node->Children[i]->Parent = node;
        link(node->Children[i]);
    }
}

TEST_F(Tests, btreeInsertEmpty) {
    auto* t1 = new BTree23<Int>();
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1));

    t1->insert(1);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert1to2) {
    auto* t1 = new BTree23<Int>();
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5));

    t1->insert(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}

TEST_F(Tests, btreeInsert2To3Small) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5));
    link(root);
    auto* t1 = new BTree23<Int>(root);
    auto* t_exp = new BTree23<Int>(expected);

    t1->insert(2);

    ASSERT_TRUE(*t1 == *t_exp);
}

TEST_F(Tests, btreeInsert2To3Mid) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),4,5));
    link(root);
    auto* t1 = new BTree23<Int>(root);
    auto* t_exp = new BTree23<Int>(expected);

    t1->insert(4);

    ASSERT_TRUE(*t1 == *t_exp);
}

TEST_F(Tests, btreeInsert2To3Big) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),5,6));
    link(root);
    auto* t1 = new BTree23<Int>(root);
    auto* t_exp = new BTree23<Int>(expected);

    t1->insert(6);

    ASSERT_TRUE(*t1 == *t_exp);
}

TEST_F(Tests, btreeInsert3To4RootSmall) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),4));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(1);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4RootMid1) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),4));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(3);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4RootMid2) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),5));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4RootBig) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),7)),6));;
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(7);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4FirstSmall) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),8));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),4,8));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(1);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4FirstMid1) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),8));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),4,8));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(3);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4FirstMid2) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),8));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),5,8));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4FirstBig) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),8));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),6,8));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(7);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4SecondSmall) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),2));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),1,4));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(1);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4SecondMid1) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),2));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),2,4));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(3);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4SecondMid2) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),2));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),2,5));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4SecondBig) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6)),2));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(-1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(0)),0)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),7)),2,6));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(7);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4TwiceRootFirstCh) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),9,11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),15,17)),7,13));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),9,11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),15,17)),13)),7));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(6);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4TwiceRootSecondCh) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),9,11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),15,17)),7,13));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),8)),7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),15,17)),13)),9));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(8);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeInsert3To4TwiceRootThirdCh) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),9,11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),15,17)),7,13));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),3,5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),9,11)),7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(16)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),17)),16)),13));
    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->insert(16);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
//TODO: if there's time, add "insert3to4twice" tests (not root)

TEST_F(Tests, btreeRemove3To2Small) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(2);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove3To2Mid) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(4);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove3To2Big) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),4,6));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(4)),4));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(6);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1BorrowSmall) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),8)),7));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),8)),6));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(7);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1BorrowMid) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),7,8)),3,6));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(1)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(2)),2)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),8)),5,7));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(3);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1BorrowBig) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),7,8)),6));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(6)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(8)),8)),7));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1UnionSmall) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),7));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),5,7));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(9);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1UnionMid) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),13)),7,11));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),11,13)),9));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(7);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1UnionBig) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),7));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),7,9));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1Root) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5));
    SharedPointer<TreeNode<Int>> expected =SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(5);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}
TEST_F(Tests, btreeRemove2To1UnionTwice) {
    SharedPointer<TreeNode<Int>> root = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(9)),9)),7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),17)),15)),11));
    SharedPointer<TreeNode<Int>> expected = SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(3)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(5)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(7)),5,7)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(11)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(13)),13)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(SharedPointer<TreeNode<Int>>(new TreeNode<Int>(15)),SharedPointer<TreeNode<Int>>(new TreeNode<Int>(17)),17)),11,15));

    link(root);
    auto* t1 = new BTree23<Int>(root);

    t1->remove(9);

    auto* t_exp = new BTree23<Int>(expected);
    ASSERT_TRUE(*t1 == *t_exp);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}