
#ifndef FHFieldManager_HH
#define FHFieldManager_HH

#include <stdio.h>
#include "FHAcceleratingElectricField.hh"
#include "G4Cache.hh"
#include "G4SystemOfUnits.hh"
#include "FHGUIManager.hh"

class FHAcceleratingElectricField;

class FHFieldManager {
public:
    static FHFieldManager* getInstance() {
        static FHFieldManager    instance;
        return &instance;
    }
    
    
    void setFieldValue(G4ThreeVector vecValue);
    double getFieldValue();
private:
    FHFieldManager() {}
    FHFieldManager(FHFieldManager const&);              // Don't Implement.
    void operator=(FHFieldManager const&); // Don't implement

    FHGUIManager *guiManager;
    double value = 0;
    G4Cache<FHAcceleratingElectricField*> fEmFieldSetup;
};

#endif