//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_CARNODE_H
#define DS_EX1_CARNODE_H

#include "vector.h"
#include "shared_pointer.h"
#include "model_data.h"

struct CarNode {
    int TypeID;
    int BestSellingModel;
    Vector<SharedPointer<ModelData>> Models;
};


#endif //DS_EX1_CARNODE_H
