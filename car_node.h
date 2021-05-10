//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_CARNODE_H
#define DS_EX1_CARNODE_H

#include "vector.h"
#include "shared_pointer.h"
#include "model_data.h"

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

struct CarNode {
    int TypeID;
    int BestSellingModel;
    int SellsForBestSelling;
    Vector<SharedPointer<ModelData>> Models;
public:
    bool operator<(const CarNode& other) const;
    bool operator>=(const CarNode& other) const;
    bool operator==(const CarNode& other) const;
    string str() const;
};

bool CarNode::operator<(const CarNode &other) const {
    return TypeID < other.TypeID;
}

bool CarNode::operator>=(const CarNode &other) const {
    return TypeID >= other.TypeID;
}

bool CarNode::operator==(const CarNode &other) const {
    return TypeID == other.TypeID;
}

string CarNode::str() const {
    std::ostringstream string_stream;
    string_stream << "(" << TypeID << "," << BestSellingModel << "," << Models.getCount() << ")";
    return string_stream.str();
}


#endif //DS_EX1_CARNODE_H
