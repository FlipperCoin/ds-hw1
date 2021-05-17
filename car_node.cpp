//
// Created by Itai on 08/05/2021.
//

#include "vector.h"
#include "shared_pointer.h"
#include "model_data.h"
#include "car_node.h"

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

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

int CarNode::getBestSellingModel() const{
    return BestSellingModel;
}