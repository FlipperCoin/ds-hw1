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
    /**
     * Type ID of the node
     */
    int TypeID{};
    /**
     * Model ID of the best selling model for the corresponding car type
     */
    int BestSellingModel{};
    /**
     * Array of metadata for all models, containing sells count and grade
     * Item i corresponds to model ID i
     */
    Vector<ModelData> Models;

    CarNode() = default;
    explicit CarNode(int typeID, int numOfModels=0) : TypeID(typeID), BestSellingModel(0),
        Models(Vector<ModelData>(numOfModels)) {}
    /**
     * @param other node to compare to
     * @return Is this node's type id higher than other's type id
     */
    bool operator<(const CarNode& other) const;
    /**
     * @param other node to compare to
     * @return Is this node's type id lower/equals to other's type id
     */
    bool operator>=(const CarNode& other) const;
    /**
     * @param other node to compare to
     * @return Is this node's type id equal to other's type id
     */
    bool operator==(const CarNode& other) const;
    string str() const;
};

#endif //DS_EX1_CARNODE_H
