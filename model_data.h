//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_MODELDATA_H
#define DS_EX1_MODELDATA_H

#include "tree_node.h"
#include "model_node.h"
#include "grade_node.h"

struct ModelData {
    SharedPointer<TreeNode<GradeNode>> Grade;
    int Sells;
};


#endif //DS_EX1_MODELDATA_H
