//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_GRADENODE_H
#define DS_EX1_GRADENODE_H

#include "shared_pointer.h"
#include "model_node.h"

#include <string>
#include <sstream>

using std::string;

struct GradeNode {
    int TypeID;
    int ModelID;
    int Grade;
public:
    bool operator<(const GradeNode& other) const;
    bool operator>=(const GradeNode& other) const;
    bool operator==(const GradeNode& other) const;
    string str() const;
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

bool GradeNode::operator==(const GradeNode &other) const {
    return Grade == other.Grade && TypeID == other.TypeID && ModelID == other.ModelID;
}

string GradeNode::str() const {
    std::ostringstream string_stream;
    string_stream << "(" << Grade << "," << TypeID << "," << ModelID << ")";
    return string_stream.str();
}

#endif //DS_EX1_GRADENODE_H
