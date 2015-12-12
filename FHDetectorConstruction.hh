
#ifndef FHDETECTORCONSTRUCTION_HH
#define FHDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

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
    
    // World logical and physical volumes
    G4LogicalVolume*   fpWorldLogical;
    G4VPhysicalVolume* fpWorldPhysical;
    
};

#endif

