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
#include "G4NistManager.hh"
#include "G4Ellipsoid.hh"
#include "FHAcceleratingElectricField.hh"

#include "G4AutoDelete.hh"

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
    
    // Field Setup
    SetupElectricFields();
    
    
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
    
    //Mercury
    G4NistManager *nistman = G4NistManager::Instance();
    nistman->FindOrBuildElement(20);
    new G4Material("Mercury", 20., 200.59*g/mole, 8*g/cm3);
    // Dump material information
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void FHDetectorConstruction::SetupGeometry()
{
    // NIST definition of air
    G4Material* mercury = G4Material::GetMaterial("Mercury");
//    G4Material* mercury = new G4Material("Mercury", 20., 200.59*g/mole, 8*g/cm3);
    
    // World volume
    G4Box* worldSolid = new G4Box("World_Solid",           // Name
                                  2.0*m, 2.0*m, 2.0*m);    // Half lengths
    
    fpWorldLogical = new G4LogicalVolume(worldSolid,	 // Solid
                                         mercury,	         // Material
                                         "World_Logical"); // Name
    
    fpWorldPhysical = new G4PVPlacement(0,	         // Rotation matrix pointer
                                        G4ThreeVector(),   // Translation vector
                                        fpWorldLogical,	 // Logical volume
                                        "World_Physical",	 // Name
                                        0,		 // Mother volume
                                        false,		 // Unused boolean parameter
                                        0);		 // Copy number
    
    ////////////////////////////////////////////////////////////////////////
    // - Katode (-)
    //TODO: Change material for elements below!
    
    G4Material* titan = G4Material::GetMaterial("Titanium");
    G4Box* katode = new G4Box("katode_solid", 2.5*cm , 5.0*cm, 0.1*cm);
    
    G4LogicalVolume *katodeLogical = new G4LogicalVolume(katode, titan, "katode_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,-(20*cm)), katodeLogical, "katode_physical", fpWorldLogical, false, 0);
    
    // Grid (+)
    
    G4Box* grid = new G4Box("grid_solid", 2.5*cm , 5.0*cm, 0.1*cm);
    
    G4LogicalVolume *gridLogical = new G4LogicalVolume(grid, titan, "grid_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,16.*cm), gridLogical, "grid_physical", fpWorldLogical, false, 0);
    
    
    // Anode

    G4Box* anode = new G4Box("anode_solid", 2.5*cm , 5.0*cm, 0.1*cm);
    
    G4LogicalVolume *anodeLogical = new G4LogicalVolume(anode, titan, "anode_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,20.*cm), anodeLogical, "anode_physical", fpWorldLogical, false, 0);
    
    
    // Lamp
    
    G4Ellipsoid *lamp = new G4Ellipsoid("lamp_solid", 10*cm, 20*cm, 40*cm, 0*cm, 0*cm);
    
    G4LogicalVolume *lampLogical = new G4LogicalVolume(lamp, mercury, "lamp_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,0.*cm), lampLogical, "lamp_logical", fpWorldLogical, false, 0);
    
    
                                        
                                        
    ////////////////////////////////////////////////////////////////////////
    // Visualisation attributes
    
    // Invisible world volume.
    fpWorldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    
    
    // Vis attributes
    G4VisAttributes* katodeAttributes = new G4VisAttributes(G4Colour::Red());
    katodeLogical->SetVisAttributes(katodeAttributes);
    
    G4VisAttributes* gridAttributes = new G4VisAttributes(G4Colour::Gray());
    gridLogical->SetVisAttributes(gridAttributes);
    
    G4VisAttributes* anodeAttributes = new G4VisAttributes(G4Colour::Blue());
    anodeLogical->SetVisAttributes(anodeAttributes);
    
    G4VisAttributes* lampAttributes = new G4VisAttributes(G4Colour::G4Colour(1.,1.,1.,0.3));
    lampLogical->SetVisAttributes(lampAttributes);
    
}


void FHDetectorConstruction::SetupElectricFields() {
    
//    G4ElectricField
    
//    G4UniformElectricField* acceleratingField = new G4UniformElectricField(G4ThreeVector(0.,0.,20.));
//    G4FieldManager *fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
//    fieldManager->SetDetectorField(acceleratingField);
    
    
    FHAcceleratingElectricField* fieldSetup = new FHAcceleratingElectricField(G4ThreeVector(0.,0.,0.1));
    G4AutoDelete::Register(fieldSetup); //Kernel will delete the messenger
    fEmFieldSetup.Put(fieldSetup);
    
    
}


