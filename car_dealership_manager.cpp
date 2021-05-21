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

        if (carNode.isEmpty() || !carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }

        // remove type from zero grades tree in O(log(n))
        ZeroGradeTypeNode zeroNode(typeID);
        ZeroGrades.remove(zeroNode);

        // remove all models from grades & sells trees
        // O(m*log(M))
        for (int i = 0; i < carNode->Value.Models.getCount(); i++) {
            ModelData model = carNode->Value.Models[i];

            // remove from grades tree
            if (model.Grade != 0) {
                GradeNode gradeNode{.TypeID=typeID,.ModelID=i,.Grade=model.Grade};
                Grades.remove(gradeNode);
            }

            SellsNode sellsNode{.TypeID=typeID,.ModelID=i,.Sells=model.Sells};
            Sells.remove(sellsNode);
        }

        // remove car in type tree
        // O(log(n))
        Cars.remove(carNode->Value);

        return SUCCESS;
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
}

void CarDealershipManager::UpdateGrade(CarNode* carNode, int modelID, int oldGrade, int newGrade) {
    carNode->Models[modelID].Grade = newGrade;

    // move from non-zero to zero grade (if new grade is zero, old grade def not zero)
    // O(log(n) + log(m) + log(M)) = O(log(n) + log(M))
    if (newGrade == 0) {
        Grades.remove({carNode->TypeID, modelID, oldGrade});
        auto zeroGradeTypeNode = ZeroGrades.find(ZeroGradeTypeNode(carNode->TypeID));
        zeroGradeTypeNode->Value.ModelsTree.insert(modelID);
        return;
    }

    // move from zero to non-zero grade
    // O(log(n) + log(m) + log(M)) = O(log(n) + log(M))
    else if(oldGrade == 0) {
        auto zeroGradeTypeNode = ZeroGrades.find(ZeroGradeTypeNode(carNode->TypeID));
        zeroGradeTypeNode->Value.ModelsTree.remove(modelID);
        Grades.insert({.TypeID=carNode->TypeID, .ModelID=modelID, .Grade=newGrade});
        return;
    }

    // stay non-zero, O(log(M))
    Grades.remove({carNode->TypeID, modelID, oldGrade});
    Grades.insert({carNode->TypeID, modelID, newGrade});
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

        if (carNode.isEmpty() || !carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }

        if (carNode->Value.Models.getCount() <= modelID) {
            return FAILURE;
        }

        ModelData modelData = carNode->Value.Models[modelID];

        // update sells, O(log(M))
        Sells.remove({.TypeID=typeID, .ModelID=modelID, .Sells = modelData.Sells++});
        Sells.insert({.TypeID=typeID, .ModelID=modelID, .Sells = modelData.Sells});

        // update sells in model data, O(1)
        carNode->Value.Models[modelID].Sells = modelData.Sells;

        // update best seller for same type id, O(1)
        auto bestSellingModel = carNode->Value.BestSellingModel;
        auto sellsForBestSelling = carNode->Value.Models[bestSellingModel].Sells;

        if (modelData.Sells > sellsForBestSelling ||
            (modelData.Sells == sellsForBestSelling && modelID <= bestSellingModel)) {
            carNode->Value.BestSellingModel = modelID;
        }

        // update grade, O(log(n) + log(M))
        int newGrade = modelData.Grade + 10;
        UpdateGrade(&(carNode->Value), modelID, modelData.Grade, newGrade);
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

        if (carNode.isEmpty() || !carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }

        if (carNode->Value.Models.getCount() <= modelID) {
            return FAILURE;
        }

        ModelData modelData = carNode->Value.Models[modelID];
        // O(log(n) + log(M))
        UpdateGrade(&(carNode->Value), modelID, modelData.Grade, modelData.Grade - int(100/t));

    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID) {
    if (typeID < 0) {
        return INVALID_INPUT;
    }
    try {
        if (typeID == 0){
            // Get highest seller from all models,
            // first leaf from Sells tree in O(1)
            if (!Sells.isEmpty()) {
                *modelID = Sells.getSmallestChild()->Value.ModelID;
                return SUCCESS;
            }
            if (Cars.isEmpty()) {
                return FAILURE;
            }
            // There are cars but they are all with grade 0, so model id 0 is def correct
            else {
                *modelID = 0; // doesn't matter the car type, it'll be model id 0
                return SUCCESS;
            }
        }

        // find car in type tree
        // O(log(n))
        SharedPointer<TreeNode<CarNode>> carNode =
                Cars.find(CarNode(typeID));

        if (carNode.isEmpty() || !carNode->isLeaf()) {
            // provided type isn't in the cars tree
            return FAILURE;
        }
        // After finding car node, get best seller in O(1)
        *modelID = carNode->Value.BestSellingModel;

    }catch (std::bad_alloc& e){
            return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models) {
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }

    // Start from the first leaf of Grades in O(1)
    TreeNode<GradeNode>* iter = Grades.getSmallestChild().rawPointer();
    // Start from the first leaf of ZeroGrades in O(1)
    TreeNode<ZeroGradeTypeNode>* zero_iter = ZeroGrades.getSmallestChild().rawPointer();

    // Iterate through all models
    for (int i = 0; i < numOfModels; i++){
        // Start in negative grades from Grades tree, iterate leaves in O(m)
        if(iter != nullptr && iter->Value.Grade < 0){
            types[i] = iter->Value.TypeID;
            models[i] = iter->Value.ModelID;
            iter = iter->Next;
        }
        // When no negative grades left go through zero grades,
        // iterating through ZeroGrades leaves and leaves of the models tree in each node in O(m)
        else if(zero_iter != nullptr){
            // need a loop for every zero grade node that goes through all nodes in tree - zero models
            auto models_iter = zero_iter->Value.ModelsTree.getSmallestChild().rawPointer();

            while(models_iter != nullptr && i < numOfModels){
                types[i] = zero_iter->Value.TypeID;
                models[i] = models_iter->Value;
                i++;
                models_iter = models_iter->Next;
            }
            i--;
            zero_iter = zero_iter->Next;
        }
        // When no zero grades left go through positive grades,
        // iterate leaves in O(m)
        else if(iter != nullptr){
            types[i] = iter->Value.TypeID;
            models[i] = iter->Value.ModelID;
            iter = iter->Next;
        } else {
            return FAILURE; // not enough models
        }
    }
    return SUCCESS;
}
