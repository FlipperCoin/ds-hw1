//
// Created by Itai on 12/05/2021.
//

#include "zero_grade_type_node.h"
#include <sstream>

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
