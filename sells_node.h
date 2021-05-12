//
// Created by Itai on 12/05/2021.
//

#ifndef DS_EX1_SELLS_NODE_H
#define DS_EX1_SELLS_NODE_H

#include <string>

using std::string;

struct SellsNode {
    int TypeID;
    int ModelID;
    int Sells;

    bool operator<(const SellsNode& other) const;
    bool operator>=(const SellsNode& other) const;
    bool operator==(const SellsNode& other) const;
    string str() const;
};


#endif //DS_EX1_SELLS_NODE_H
