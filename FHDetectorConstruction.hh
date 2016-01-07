
#ifndef FHDETECTORCONSTRUCTION_HH
#define FHDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// Fields
#include "FHAcceleratingElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4ChordFinder.hh"
#include "G4Cache.hh"
#include "FHGUIManager.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class FHGUIManager;

class FHDetectorConstruction : public G4VUserDetectorConstruction {
    
public:
    
    // Constructor
    FHDetectorConstruction();
    
    // Destructor
    virtual ~FHDetectorConstruction();
    
    // Method
    virtual G4VPhysicalVolume* Construct();
    
private:
    
    // Helper methods
    void DefineMaterials();
    void SetupGeometry();
    void SetupElectricFields();
    void SetupScoring(G4LogicalVolume* scoringVolume);
    
    // World logical and physical volumes
    G4LogicalVolume*   fpWorldLogical;
    G4VPhysicalVolume* fpWorldPhysical;
    
    G4Cache<FHAcceleratingElectricField*> fEmFieldSetup;
    FHGUIManager guiManager;
};

#endif

