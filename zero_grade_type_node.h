//
// Created by Itai on 12/05/2021.
//

#ifndef DS_EX1_ZERO_GRADE_NODE_H
#define DS_EX1_ZERO_GRADE_NODE_H

#include "btree_23.h"

struct ZeroGradeTypeNode {
    int TypeID{};
    /**
     * Tree of all model IDs that have a grade of zero, fast initialized
     */
    BTree23<int> ModelsTree;

    ZeroGradeTypeNode(int typeID, int n);
    explicit ZeroGradeTypeNode(int typeID) : TypeID(typeID) {}
    ZeroGradeTypeNode() = default;
    bool operator<(const ZeroGradeTypeNode& other) const;
    bool operator>=(const ZeroGradeTypeNode& other) const;
    bool operator==(const ZeroGradeTypeNode& other) const;
    string str() const;
};


#endif //DS_EX1_ZERO_GRADE_NODE_H
