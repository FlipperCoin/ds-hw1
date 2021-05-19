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
        // all models start with no sales & grade 0
        // O(m)
        for (int i = 0; i < numOfModels; i++) {
            car.Models.add({});
        }
        // insert & check if succeeded (empty means the node already existed)
        // O(log(n))
        if (Cars.insert(car).isEmpty()) {
            return FAILURE;
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
            BestSellingCarType = nextBestSeller->Value.TypeID;
            BestSellingCarModel = nextBestSeller->Value.ModelID;
            SellsForBestSelling = nextBestSeller->Value.Sells;
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

void CarDealershipManager::UpdateGrade(CarNode carNode, int modelID, int oldGrade, int newGrade) {
    carNode.Models[modelID].Grade = newGrade;

    // move from non-zero to zero grade (if new grade is zero, old grade def not zero)
    if (newGrade == 0) {
        Grades.remove({carNode.TypeID, modelID, oldGrade});
        auto zeroGradeTypeNode = ZeroGrades.find(ZeroGradeTypeNode(carNode.TypeID));
        zeroGradeTypeNode->Value.ModelsTree.insert(modelID);
        return;
    }

    // move from zero to non-zero grade
    else if(oldGrade == 0) {


        return;
    }

    // stay non-zero

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

        ModelData modelData = carNode->Value.Models[modelID];

        Sells.remove({.TypeID=typeID, .ModelID=modelID, .Sells = modelData.Sells++});
        Sells.insert({.TypeID=typeID, .ModelID=modelID, .Sells = modelData.Sells});

        UpdateGrade(carNode, modelID, modelData.Grade, modelData.Grade + 10);

//        if (carNode->Value.Models[modelID].isEmpty()) {
//            // the model was never sold or complained about,
//            // need to init for the first time
//            SharedPointer<TreeNode<GradeNode>> gradeNode = Grades.insert(
//            {
//                     .TypeID=typeID,
//                     .ModelID=modelID,
//                     .Grade=10
//                 });
//
//            auto newModelData = SharedPointer<ModelData>(new ModelData());
//            newModelData->Grade = gradeNode;
//            newModelData->Sells = 1;
//            carNode->Value.Models[modelID] = newModelData;
//            modelData = newModelData;
//        }
//        else {
//            // increase sells by 1
//            // remove and add grade node with an increase in score (to reorder in tree)
//            modelData->Sells += 1;
//            GradeNode gradeNode = modelData->Grade->Value;
//            Grades.remove(gradeNode);
//            gradeNode.Grade += 10;
//            Grades.insert(gradeNode);
//        }
//
//        // Keep car node most sold invariant updated
//        if (shouldSwitchBestSelling(carNode->Value.SellsForBestSelling,
//                                    carNode->Value.BestSellingModel,
//                                    modelData->Sells,
//                                    modelID))
//        {
//            carNode->Value.SellsForBestSelling = modelData->Sells;
//            carNode->Value.BestSellingModel = modelID;
//        }
//
//        // Keep most sold overall invariant updated
//        if (shouldSwitchBestSelling(SellsForBestSelling, BestSellingCarModel, BestSellingCarType,
//                                    modelData->Sells, modelID, typeID)) {
//            SellsForBestSelling = modelData->Sells;
//            BestSellingCarModel = modelID;
//            BestSellingCarType = typeID;
//        }
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t) {

    return FAILURE;
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
        *modelID = carNode->Value.BestSellingModel; // but whyyyy???

    }catch (std::bad_alloc& e){
            return ALLOCATION_ERROR;
    }
    return FAILURE;
}

StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models) {
    return FAILURE;
}
