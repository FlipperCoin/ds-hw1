//
// Created by Itai on 08/05/2021.
//

#include "car_dealership_manager.h"

CarDealershipManager::CarDealershipManager() {

}

StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels) {
    if (typeID <= 0 || numOfModels <= 0) {
        return INVALID_INPUT;
    }
    try {
        CarNode car = {.TypeID=typeID,.BestSellingModel=-1,.Models=Vector<SharedPointer<ModelData>>(numOfModels)};
        // The models do not exist until they are sold or complained about
        // so init to null
        // O(m)
        for (int i = 0; i < numOfModels; i++) {
            car.Models.add(SharedPointer<ModelData>());
        }
        // insert & check if succeeded (empty means the node already existed)
        // O(log(n))
        if (Cars.insert(car).isEmpty()) {
            return FAILURE;
        }
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::RemoveCarType(int typeID) {
    if (typeID <= 0) {
        return INVALID_INPUT;
    }

    // find car in type tree
    // O(log(n))
    SharedPointer<TreeNode<CarNode>> carNode =
            Cars.find({.TypeID=typeID,.Models=Vector<SharedPointer<ModelData>>()});

    // remove all models from grades tree
    // O(m*log(M))
    for (int i = 0; i < carNode->Value.Models.getCount(); i++) {
        SharedPointer<ModelData> model = carNode->Value.Models[i];
        if (model.isEmpty()) continue;

        GradeNode gradeNode = model->Grade->Value;
        Grades.remove(gradeNode);
    }

    // remove car in type tree
    // O(log(n))

}

StatusType CarDealershipManager::SellCar(int typeID, int modelID) {
    return FAILURE;
}

StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t) {
    return FAILURE;
}

StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID) {
    return FAILURE;
}

StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models) {
    return FAILURE;
}
