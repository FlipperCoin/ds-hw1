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
    BTree23<CarNode> Cars;
    BTree23<GradeNode> Grades;
    BTree23<ZeroGradeTypeNode> ZeroGrades;
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
