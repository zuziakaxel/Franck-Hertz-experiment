#include "FHDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"


FHDetectorConstruction::FHDetectorConstruction()
:fpWorldLogical(0)
,fpWorldPhysical(0)
{}

FHDetectorConstruction::~FHDetectorConstruction() {}

G4VPhysicalVolume* FHDetectorConstruction::Construct()
{
    // Material Definition
    DefineMaterials();
    
    // Geometry Definition
    SetupGeometry();
    
    // Return world volume
    return fpWorldPhysical;
}

void FHDetectorConstruction::DefineMaterials()
{
    G4String symbol;
    G4double a, z, density;
    G4int ncomponents;
    G4double fractionmass;
    
    // Define simple materials
    // Define beryllium, silicon and iron
    
    new G4Material("Titanium",  z=22., a=47.90*g/mole,    density=4.540*g/cm3);
    
    // Define elements
    G4Element* N = new G4Element("Nitrogen", symbol="N", z=7., a=14.01*g/mole);
    G4Element* O = new G4Element("Oxygen",   symbol="O", z=8., a=16.00*g/mole);
    
    // Define air
    G4Material* air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
    air->AddElement(N, fractionmass=0.7);
    air->AddElement(O, fractionmass=0.3);
    
    // Define vacuum
    G4Material* vacuum = new G4Material("Vacuum", density= 1.e-5*g/cm3,
                                        ncomponents=1, kStateGas, STP_Temperature,
                                        2.e-2*bar);
    
    vacuum->AddMaterial(air, fractionmass=1.);
    
    // Dump material information
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void FHDetectorConstruction::SetupGeometry()
{
    // NIST definition of air
    G4Material* air = G4Material::GetMaterial("Air");
    
    // World volume
    G4Box* worldSolid = new G4Box("World_Solid",           // Name
                                  2.0*m, 2.0*m, 2.0*m);    // Half lengths
    
    fpWorldLogical = new G4LogicalVolume(worldSolid,	 // Solid
                                         air,	         // Material
                                         "World_Logical"); // Name
    
    fpWorldPhysical = new G4PVPlacement(0,	         // Rotation matrix pointer
                                        G4ThreeVector(),   // Translation vector
                                        fpWorldLogical,	 // Logical volume
                                        "World_Physical",	 // Name
                                        0,		 // Mother volume
                                        false,		 // Unused boolean parameter
                                        0);		 // Copy number
    ////////////////////////////////////////////////////////////////////////
    // Beam Window (BW)
    G4Material* titanium = G4Material::GetMaterial("Titanium");
    
    G4VSolid* beamWindowSolid = new G4Tubs("BeamWindow_Solid", 0.*cm, 2.0*cm,
                                           0.0065*cm, 0.*deg, 360.*deg);
    
    G4LogicalVolume* beamWindowLogical =
    new G4LogicalVolume(beamWindowSolid, titanium, "BeamWindow_Logical");
    
    new G4PVPlacement(0, G4ThreeVector(0.,0.,-(3.0*cm+ 0.0065*cm)),
                      beamWindowLogical, "BeamWindow_Physical",
                      fpWorldLogical, false, 0);
    
    ////////////////////////////////////////////////////////////////////////
    // Beam Pipe
    G4Material* vacuum = G4Material::GetMaterial("Vacuum");
    
    G4VSolid* beamPipeSolid = new G4Tubs("BeamPipe_Solid", 0.*cm, 5.0*cm, 5.0*cm,
                                         0.*deg, 360.*deg);
    
    G4LogicalVolume* beamPipeLogical =
    new G4LogicalVolume(beamPipeSolid, vacuum, "BeamPipe_Logical");
    
    new G4PVPlacement(0, G4ThreeVector(0.,0., -(3.013*cm+5.0*cm)),
                      beamPipeLogical, "BeamPipe_Physical",
                      fpWorldLogical, false, 0);
    
    
    ////////////////////////////////////////////////////////////////////////
    // Visualisation attributes
    
    // Invisible world volume.
    fpWorldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    
    // Beam Window - brown
    G4VisAttributes* beamWindowAttributes = new G4VisAttributes(G4Colour(0.5,0.0,0.0,1.0));
    beamWindowAttributes->SetForceSolid(true);
    beamWindowLogical->SetVisAttributes(beamWindowAttributes);
    //
    // Beam Pipe Vacuum - yellow
    G4VisAttributes* beamPipeAttributes = new G4VisAttributes(G4Colour::Yellow());
    //beamPipeAttributes->SetForceSolid(true);
    beamPipeLogical->SetVisAttributes(beamPipeAttributes);
}
