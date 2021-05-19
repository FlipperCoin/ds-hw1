//
// Created by Itai on 08/05/2021.
//

#include "car_dealership_manager.h"
#include "car_node.h"

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
            car.Models.add({});
        }
        // insert & check if succeeded (empty means the node already existed)
        // O(log(n))
        if (Cars.insert(car).isEmpty()) {
            return FAILURE;
        }
        // if the first car type inserted to the system,
        // or no sells were made and this type id is lower,
        // set it as the best selling
        if (BestSellingCarType == NO_CAR_TYPE ||
            (BestSellingCarType > typeID && SellsForBestSelling == 0)) {
            BestSellingCarType = typeID;
            BestSellingCarModel = 0;
        }
        // all models have grade zero, init o(m) zero grade model tree
        ZeroGradeTypeNode zeroGradesNode(typeID, numOfModels);
        // insert log(n) into zero grade type tree
        ZeroGrades.insert(zeroGradesNode);

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

        // remove all models from grades & sells trees
        // O(m*log(M))
        for (int i = 0; i < carNode->Value.Models.getCount(); i++) {
            ModelData model = carNode->Value.Models[i];

            // remove from zero tree
            if (model.Grade == 0) {
                ZeroGradeTypeNode zeroNode(typeID);
                ZeroGrades.remove(zeroNode);
            }
            // remove from grades tree
            else {
                GradeNode gradeNode{.TypeID=typeID,.ModelID=i,.Grade=model.Grade};
                Grades.remove(gradeNode);
            }

            SellsNode sellsNode{.TypeID=typeID,.ModelID=i,.Sells=model.Sells};
            Sells.remove(sellsNode);
        }

        // remove car in type tree
        // O(log(n))
        Cars.remove(carNode->Value);

        // update best seller
        if (BestSellingCarType == typeID) {
            SharedPointer<TreeNode<SellsNode>> nextBestSeller = Sells.getSmallestChild();
            BestSellingCarType = nextBestSeller->Value.Sells;
        }

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
        if (shouldSwitchBestSelling(SellsForBestSelling, BestSellingCarModel, BestSellingCarType,
                                    modelData->Sells, modelID, typeID)) {
            SellsForBestSelling = modelData->Sells;
            BestSellingCarModel = modelID;
            BestSellingCarType = typeID;
        }
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t) {
    if (typeID <= 0 || modelID < 0 || t <= 0) {
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

        // check with itai!
        if (carNode->Value.Models.getCount() <= modelID) {
            return FAILURE;
        }

        SharedPointer<ModelData> modelData = carNode->Value.Models[modelID];

        // remove and add grade node with new score (to reorder in tree)
        GradeNode gradeNode = modelData->Grade->Value;
        Grades.remove(gradeNode);
        ZeroGrades.remove(gradeNode); // need to make a conversion

        gradeNode.Grade -= int(100/t); // should round down
        if(gradeNode.Grade == 0) ZeroGrades.insert(gradeNode);
        else Grades.insert(gradeNode);

    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID) {
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
        *modelID = carNode->Value.BestSellingModel;

    }catch (std::bad_alloc& e){
            return ALLOCATION_ERROR;
    }
    return FAILURE;
}
// get smallest child should return a regular pointer
StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models) {
    if (numOfModels <= 0) { // need to check if DS is NULL
        return INVALID_INPUT;
    }
    TreeNode<GradeNode>* iter = Grades.getSmallestChild().rawPointer();
    TreeNode<ZeroGradeTypeNode>* zero_iter = ZeroGrades.getSmallestChild().rawPointer();
    for (int i = 0; i < numOfModels; i++){
        if(iter != nullptr && iter->Value.Grade < 0){
            types[i] = iter->Value.TypeID;
            models[i] = iter->Value.ModelID;
            iter = iter->Next;
        }
        else{
            // need a loop for every zero grade node that goes through all nodes in tree4 - zero models.

            types[i] = zero_iter->Value.TypeID;
            models[i] = zero_iter->Value.ModelID;
            zero_iter = zero_iter->Next;
        }
    }
    return FAILURE;
}
