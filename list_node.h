//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_LIST_NODE_H
#define DS_EX1_LIST_NODE_H

template<typename DataType>
struct ListNode {
    SharedPointer<ListNode> NextNode;
    SharedPointer<ListNode> PreviousNode;
    SharedPointer<DataType> Value;
};


#endif //DS_EX1_LIST_NODE_H
