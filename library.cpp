//
// Created by Itai on 08/05/2021.
//

#include "library.h"
#include "car_dealership_manager.h"

void *Init() {
    try {
        return (void*)(new CarDealershipManager());
    }
    catch (std::bad_alloc& e) {
        return nullptr;
    }
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->AddCarType(typeID, numOfModels);
}

StatusType RemoveCarType(void *DS, int typeID) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->RemoveCarType(typeID);
}

StatusType SellCar(void *DS, int typeID, int modelID) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->SellCar(typeID, modelID);
}

StatusType MakeComplaint(void *DS, int typeID, int modelID, int t) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->MakeComplaint(typeID, modelID, t);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->GetBestSellerModelByType(typeID, modelID);
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->GetWorstModels(numOfModels, types, models);
}

void Quit(void** DS) {
    if (DS != nullptr) delete ((CarDealershipManager*)DS);
}