//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_GRADENODE_H
#define DS_EX1_GRADENODE_H

#include "shared_pointer.h"
#include "model_node.h"
#include "list_node.h"

struct GradeNode {
    int Grade;
    SharedPointer<ListNode<ModelNode>> Models;
};

#endif //DS_EX1_GRADENODE_H
