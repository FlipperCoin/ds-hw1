//
// Created by Itai on 08/05/2021.
//

#include "car_dealership_manager.h"

StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels) {
    if (typeID <= 0 || numOfModels <= 0) {
        return INVALID_INPUT;
    }
    try {
        CarNode car(typeID);
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
        // if the first car type inserted to the system,
        // set it as the best selling
        if (CarTypeOfBestSelling == NO_CAR_TYPE) {
            CarTypeOfBestSelling = typeID;
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

    try {
        // find car in type tree
        // O(log(n))
        SharedPointer<TreeNode<CarNode>> carNode =
                Cars.find(CarNode(typeID));

        if (!carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }

        // remove all models from grades tree
        // O(m*log(M))
        for (int i = 0; i < carNode->Value.Models.getCount(); i++) {
            SharedPointer<ModelData> model = carNode->Value.Models[i];

            if (model.isEmpty()) {
                // model wasn't sold or complained about, so isn't in grades tree
                continue;
            }

            GradeNode gradeNode = model->Grade->Value;
            Grades.remove(gradeNode);
        }

        // remove car in type tree
        // O(log(n))
        Cars.remove(carNode->Value);

        return SUCCESS;
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
}

static bool shouldSwitchBestSelling(int sellsForBestSelling, int bestSellingModel,
                                    int sells, int modelID) {
    return sellsForBestSelling < sells ||
           (sellsForBestSelling == sells &&
            bestSellingModel > modelID);
}

static bool shouldSwitchBestSelling(int sellsForBestSelling, int bestSellingModel, int bestSellingType,
                                    int sells, int modelID, int typeID) {
    return sellsForBestSelling < sells ||
           (sellsForBestSelling == sells &&
            bestSellingType > typeID) ||
            (sellsForBestSelling == sells &&
             bestSellingType == typeID &&
                bestSellingModel > modelID);
}

StatusType CarDealershipManager::SellCar(int typeID, int modelID) {
    if (typeID <= 0 || modelID < 0) {
        return INVALID_INPUT;
    }

    try {
        // find car in type tree
        // O(log(n))
        SharedPointer<TreeNode<CarNode>> carNode =
                Cars.find(CarNode(typeID));

        if (!carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }

        if (carNode->Value.Models.getCount() >= modelID) {
            return INVALID_INPUT;
        }

        SharedPointer<ModelData> modelData = carNode->Value.Models[modelID];
        if (carNode->Value.Models[modelID].isEmpty()) {
            // the model was never sold or complained about,
            // need to init for the first time
            SharedPointer<TreeNode<GradeNode>> gradeNode = Grades.insert(
            {
                     .TypeID=typeID,
                     .ModelID=modelID,
                     .Grade=10
                 });

            auto newModelData = SharedPointer<ModelData>(new ModelData());
            newModelData->Grade = gradeNode;
            newModelData->Sells = 1;
            carNode->Value.Models[modelID] = newModelData;
            modelData = newModelData;
        }
        else {
            // increase sells by 1
            // remove and add grade node with an increase in score (to reorder in tree)
            modelData->Sells += 1;
            GradeNode gradeNode = modelData->Grade->Value;
            Grades.remove(gradeNode);
            gradeNode.Grade += 10;
            Grades.insert(gradeNode);
        }

        // Keep car node most sold invariant updated
        if (shouldSwitchBestSelling(carNode->Value.SellsForBestSelling,
                                    carNode->Value.BestSellingModel,
                                    modelData->Sells,
                                    modelID))
        {
            carNode->Value.SellsForBestSelling = modelData->Sells;
            carNode->Value.BestSellingModel = modelID;
        }

        // Keep most sold overall invariant updated
        if (shouldSwitchBestSelling(SellsForBestSelling, BestSellingModelOverall, CarTypeOfBestSelling,
                                    modelData->Sells, modelID, typeID)) {
            SellsForBestSelling = modelData->Sells;
            BestSellingModelOverall = modelID;
            CarTypeOfBestSelling = typeID;
        }
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
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
