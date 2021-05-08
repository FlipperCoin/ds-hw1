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
};

TEST_F(Tests, btreeInsertEmpty) {

}
TEST_F(Tests, btreeInsert2To3) {
    SharedPointer<TreeNode<Int>> root(
            new TreeNode<Int>(
                SharedPointer<TreeNode<Int>>(
                            new TreeNode<Int>(4)
                        ),
                SharedPointer<TreeNode<Int>>(
                            new TreeNode<Int>(7)
                        ),
                7
            )
    );
    BTree23<Int>* t1 = new BTree23<Int>(root);

    t1->printTree();
}
TEST_F(Tests, btreeInsert3To4Once) {

}
TEST_F(Tests, btreeInsert3To4Twice) {

}
TEST_F(Tests, btreeInsert3To4Root) {

}
TEST_F(Tests, btreeRemove3To2) {

}
TEST_F(Tests, btreeRemove2To1Borrow) {

}
TEST_F(Tests, btreeRemove2To1Root) {

}
TEST_F(Tests, btreeRemove2To1UnionOnce) {

}
TEST_F(Tests, btreeRemove2To1UnionTwice) {

}
TEST_F(Tests, btreeRemove2To1UnionRoot) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}