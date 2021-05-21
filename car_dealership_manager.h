//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_CAR_DEALERSHIP_MANAGER_H
#define DS_EX1_CAR_DEALERSHIP_MANAGER_H

#include "btree_23.h"
#include "car_node.h"
#include "grade_node.h"
#include "library.h"
#include "zero_grade_type_node.h"
#include "sells_node.h"

class CarDealershipManager {
private:
    /**
     * Tree containing all car nodes
     */
    BTree23<CarNode> Cars;
    /**
     * Tree containing all non-zero grades (negative and positive),
     * ordered from lowest to highest grade, type id & model id
     */
    BTree23<GradeNode> Grades;
    /**
     * Tree containing all car types,
     * in each node we have an integer tree for all models with grade 0 (fast consecutive init)
     */
    BTree23<ZeroGradeTypeNode> ZeroGrades;
    /**
     * Tree containing all sells of all models,
     * ordered from highest sell count to lowest, then lowest to highest type id & model id
     */
    BTree23<SellsNode> Sells;

    void UpdateGrade(CarNode* carNode, int modelID, int oldGrade, int newGrade);
public:
    CarDealershipManager() = default;
    StatusType AddCarType(int typeID, int numOfModels);
    StatusType RemoveCarType(int typeID);
    StatusType SellCar(int typeID, int modelID);
    StatusType MakeComplaint(int typeID, int modelID, int t);
    StatusType GetBestSellerModelByType(int typeID, int * modelID);
    StatusType GetWorstModels(int numOfModels, int *types, int *models);
};


#endif //DS_EX1_CAR_DEALERSHIP_MANAGER_H
