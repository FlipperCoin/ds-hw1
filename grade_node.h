//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_GRADENODE_H
#define DS_EX1_GRADENODE_H

#include "shared_pointer.h"

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

#endif //DS_EX1_GRADENODE_H
