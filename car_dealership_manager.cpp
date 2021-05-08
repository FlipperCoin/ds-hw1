//
// Created by Itai on 08/05/2021.
//

#include "car_dealership_manager.h"

CarDealershipManager::CarDealershipManager() {

}

StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels) {
    return FAILURE;
}

StatusType CarDealershipManager::RemoveCarType(int typeID) {
    return FAILURE;
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
