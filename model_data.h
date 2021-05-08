//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_MODELDATA_H
#define DS_EX1_MODELDATA_H

#include "list_node.h"
#include "tree_node.h"

struct ModelData {
    SharedPointer<ListNode<ModelNode>> Model;
    SharedPointer<TreeNode<GradeNode>> Grade;
    int Sells;
};


#endif //DS_EX1_MODELDATA_H
