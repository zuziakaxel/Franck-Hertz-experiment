

#include "FHGUIManager.hh"

#include "FHAcceleratingElectricField.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "FHDetectorConstruction.hh"
#include "FHFieldManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FHGUIManager::FHGUIManager() {
    
    fDetDir = new G4UIdirectory("/field");

    fDetDir->SetGuidance(" Field tracking control ");

    fFieldValue = new G4UIcmdWithADouble("/field/setValue",this);
    fFieldValue->SetGuidance("Set Field Z-axis value");
    fFieldValue->SetParameterName("z_value",false);
    fFieldValue->AvailableForStates(G4State_PreInit,G4State_Idle);

    fFieldAcceleration = new G4UIcmdWithADouble("/field/setAcceleration",this);
    fFieldAcceleration->SetGuidance("Set Field Z-axis value [V]");
    fFieldAcceleration->SetParameterName("z_value",false);
    fFieldAcceleration->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FHGUIManager::~FHGUIManager() {
//    delete fDetDir;
//    delete fFieldValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FHGUIManager::SetNewValue( G4UIcommand* command, G4String newValue) {
    if( command == fFieldValue ) {
        FHFieldManager::getInstance()->setFieldValue(G4ThreeVector(0.,0.,-(fFieldValue->GetNewDoubleValue(newValue))*volt/m));
    }
    if (command == fFieldAcceleration) {
        double value = fFieldValue->GetNewDoubleValue(newValue);
        FHFieldManager::getInstance()->setFieldValue(G4ThreeVector(0.,0.,-(value/0.0036)));
    }
}
