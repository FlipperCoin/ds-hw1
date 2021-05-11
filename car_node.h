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
    int TypeID{};
    int BestSellingModel{};
    int SellsForBestSelling{};
    Vector<SharedPointer<ModelData>> Models;

    CarNode() = default;
    explicit CarNode(int typeID, int numOfModels=0) : TypeID(typeID), BestSellingModel(0),
    SellsForBestSelling(0), Models(Vector<SharedPointer<ModelData>>(numOfModels)){}
    bool operator<(const CarNode& other) const;
    bool operator>=(const CarNode& other) const;
    bool operator==(const CarNode& other) const;
    string str() const;
};

#endif //DS_EX1_CARNODE_H
