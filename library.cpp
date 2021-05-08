//
// Created by Itai on 08/05/2021.
//

#include "library.h"
#include "car_dealership_manager.h"

void *Init() {
    return (void*)(new CarDealershipManager());
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) {
    return ((CarDealershipManager*)DS)->AddCarType(typeID, numOfModels);
}

StatusType RemoveCarType(void *DS, int typeID) {
    return ((CarDealershipManager*)DS)->RemoveCarType(typeID);
}

StatusType SellCar(void *DS, int typeID, int modelID) {
    return ((CarDealershipManager*)DS)->SellCar(typeID, modelID);
}

StatusType MakeComplaint(void *DS, int typeID, int modelID, int t) {
    return ((CarDealershipManager*)DS)->MakeComplaint(typeID, modelID, t);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID) {
    return ((CarDealershipManager*)DS)->GetBestSellerModelByType(typeID, modelID);
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models) {
    return ((CarDealershipManager*)DS)->GetWorstModels(numOfModels, types, models);
}

void Quit(void** DS) {
    delete ((CarDealershipManager*)DS);
}