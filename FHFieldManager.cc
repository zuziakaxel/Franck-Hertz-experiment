

#include "FHFieldManager.hh"
#include "G4AutoDelete.hh"
#include "FHGUIManager.hh"

void FHFieldManager::setFieldValue(G4ThreeVector vecValue) {
    guiManager = new FHGUIManager();
    FHAcceleratingElectricField* fieldSetup = new FHAcceleratingElectricField(vecValue);
    G4AutoDelete::Register(fieldSetup); //Kernel will delete the messenger
    fEmFieldSetup.Put(fieldSetup);
    G4cout << "FHLog: New Electric field z-value " << vecValue.z() << G4endl;
    value = vecValue.z();
}


double FHFieldManager::getFieldValue() {
    return -value*0.0036;
}