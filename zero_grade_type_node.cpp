//
// Created by Itai on 12/05/2021.
//

#include "zero_grade_type_node.h"
#include <sstream>

template<>
BTree23<int>::BTree23(int n) {
    if (n == 0) {
        root = SharedPointer<TreeNode<int>>();
        return;
    }

    // create references for all nodes in final tree,
    // less than 2*n for n leaves
    Vector<SharedPointer<TreeNode<int>>> nodes(2*n);

    // create row of leaves
    for (int i = 0; i < n; i++) {
        nodes.add(SharedPointer<TreeNode<int>>(new TreeNode<int>(i)));
    }

    child = nodes[0];

    // loop row by row, from the bottom up
    // each time creating the row's parents and linking them
    int k = n;
    int r = 0;
    while (r+k - r > 1) {
        createRow(nodes, k, r);
        r += k;
        k /= 2; // rounding down is a wanted behaviour, in case of 3 sons in the end
    }

    root = nodes[r];
}

ZeroGradeTypeNode::ZeroGradeTypeNode(int typeID, int n) : TypeID(typeID), ModelsTree(n) {}

bool ZeroGradeTypeNode::operator<(const ZeroGradeTypeNode &other) const {
    return this->TypeID < other.TypeID;
}

bool ZeroGradeTypeNode::operator>=(const ZeroGradeTypeNode &other) const {
    return !(*this < other);
}

bool ZeroGradeTypeNode::operator==(const ZeroGradeTypeNode &other) const {
    return this->TypeID == other.TypeID;
}

string ZeroGradeTypeNode::str() const {
    std::ostringstream string_stream;
    string_stream << "(" << TypeID << ")";
    return string_stream.str();
}