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

    /**
     * @param other node to compare to
     * @return Is Sells HIGHER than other's Sells, if equal is TypeID LOWER and if equal is ModelID lower.
     */
    bool operator<(const SellsNode& other) const;
    /**
     * @param other node to compare to
     * @return Is Sells LOWER than other's Sells, if equal is TypeID HIGHER and if equal is ModelID higher.
     */
    bool operator>=(const SellsNode& other) const;
    bool operator==(const SellsNode& other) const;
    string str() const;
};


#endif //DS_EX1_SELLS_NODE_H
