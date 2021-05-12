//
// Created by Itai on 12/05/2021.
//

#include "sells_node.h"
#include <sstream>

bool SellsNode::operator<(const SellsNode &other) const {
    // this is intentional!
    // if Sells is *larger*, then treat it as *smaller* than other
    if (Sells > other.Sells) return true;
    if (Sells < other.Sells) return false;
    // The other checks are fine intuitively
    if (TypeID < other.TypeID) return true;
    if (TypeID > other.TypeID) return false;
    if (ModelID < other.ModelID) return true;

    return false;
}

bool SellsNode::operator>=(const SellsNode &other) const {
    return !(*this < other);
}

bool SellsNode::operator==(const SellsNode &other) const {
    return TypeID==other.TypeID &&
            ModelID==other.ModelID &&
            Sells==other.Sells;
}

string SellsNode::str() const {
    std::ostringstream string_stream;
    string_stream << "(" << Sells << "," << TypeID << "," << ModelID << ")";
    return string_stream.str();
}
