//
// Created by Itai on 12/05/2021.
//

#ifndef DS_EX1_ZERO_GRADE_NODE_H
#define DS_EX1_ZERO_GRADE_NODE_H

#include "btree_23.h"

struct ZeroGradeTypeNode {
    int TypeID;
    BTree23<int> ModelsTree;

    ZeroGradeTypeNode(int typeID, int n) : TypeID(typeID), ModelsTree(n) {}
    ZeroGradeTypeNode(int typeID) : TypeID(typeID) {}
    bool operator<(const ZeroGradeTypeNode& other) const;
    bool operator>=(const ZeroGradeTypeNode& other) const;
    bool operator==(const ZeroGradeTypeNode& other) const;
    string str() const;
};


#endif //DS_EX1_ZERO_GRADE_NODE_H