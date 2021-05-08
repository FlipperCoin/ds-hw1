//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_GRADENODE_H
#define DS_EX1_GRADENODE_H

#include "shared_pointer.h"
#include "model_node.h"

struct GradeNode {
    int Grade;
    int TypeID;
    int ModelID;
public:
    bool operator<(const GradeNode& other) const;
    bool operator>=(const GradeNode& other) const;
};

bool GradeNode::operator<(const GradeNode &other) const {
    if (Grade < other.Grade) return true;
    if (Grade > other.Grade) return false;
    if (TypeID < other.TypeID) return true;
    if (TypeID > other.TypeID) return false;
    if (ModelID < other.ModelID) return true;

    return false;
}

bool GradeNode::operator>=(const GradeNode &other) const {
    return !(*this < other);
}

#endif //DS_EX1_GRADENODE_H
