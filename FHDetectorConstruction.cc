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
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSSphereSurfaceCurrent.hh"
#include "G4SDParticleFilter.hh"
#include "G4VSDFilter.hh"
#include "G4SDChargedFilter.hh"
#include "BeamTestScoreParameterisation.hh"

#include "FHFieldManager.hh"

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
    
//    guiManager = FHGUIManager();
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
    G4Element* merc  = new G4Element("Mercury",symbol="Hg" , z= 80., a=200*g/mole);

//    G4Element *merc = new G4Element("Mercury", "Hg", z=80., 200.59*g/mole, 70*mg/cm3);
//    G4String name, symbol;             // a=mass of a mole;
//    G4double a, z, density;            // z=mean number of protons;
//    G4int iz, n;                       //iz=nb of protons  in an isotope;
    // n=nb of nucleons in an isotope;
    
//    G4int ncomponents, natoms;
//    G4double abundance, fractionmass;
    G4double temperature, pressure;
    density     = 60*mg/cm3;
    pressure    = 100.*hep_pascal;
    temperature = 388.*kelvin;
    G4Material* mer = new G4Material("MercuryVapour", density, ncomponents=1,kStateGas,temperature,pressure);
    mer->AddElement(merc,0.9);
    
//NEON
    
    
    
    // Dump material information
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void FHDetectorConstruction::SetupGeometry()
{
    // NIST definition of air
    G4Material* mercury = G4Material::GetMaterial("MercuryVapour");
    G4Material* vacuum = G4Material::GetMaterial("Vacuum");
//    G4Material* mercury = new G4Material("Mercury", 20., 200.59*g/mole, 8*g/cm3);
    
    // World volume
    G4Box* worldSolid = new G4Box("World_Solid",           // Name
                                  2.0*m, 2.0*m, 2.0*m);    // Half lengths
    
    fpWorldLogical = new G4LogicalVolume(worldSolid,	 // Solid
                                         vacuum,	         // Material
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
    //TODO: Change materials for elements below!
    
    G4Box* katode = new G4Box("katode_solid", 2.5*mm , 5.0*mm, 0.1*mm);
    
    G4LogicalVolume *katodeLogical = new G4LogicalVolume(katode, mercury, "katode_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,-(20*mm)), katodeLogical, "katode_physical", fpWorldLogical, false, 0);
    
    // Grid (+)
    
    G4Box* grid = new G4Box("grid_solid", 2.5*mm , 5.0*mm, 0.1*mm);
    
    G4LogicalVolume *gridLogical = new G4LogicalVolume(grid, mercury, "grid_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,16.*mm), gridLogical, "grid_physical", fpWorldLogical, false, 0);
    
    
    // Anode

    G4Box* anode = new G4Box("anode_solid", 2.5*mm , 5.0*mm, 0.1*mm);
    
    G4LogicalVolume *anodeLogical = new G4LogicalVolume(anode, vacuum, "anode_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,20.*mm), anodeLogical, "anode_physical", fpWorldLogical, false, 0);
    
//    SetupScoring(anodeLogical);
    // Lamp
    
    G4Ellipsoid *lamp = new G4Ellipsoid("lamp_solid", 10*mm, 20*mm, 40*mm, 0*mm, 0*mm);
    
    G4LogicalVolume *lampLogical = new G4LogicalVolume(lamp, mercury, "lamp_logical");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,0.*mm), lampLogical, "lamp_logical", fpWorldLogical, false, 0);
    
    
                                        
                                        
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
    
    
    
    // Mother sphere
    G4double innerRadius = 1.5*cm;
    G4double outerRadius = 1.51*cm;
    
    G4VSolid* sphereSolid = new G4Sphere("Sphere_Solid",   // Name
                                         innerRadius,    // Inner radius
                                         outerRadius,    // Outer radius
                                         0.*deg,         // Starting phi
                                         360.*deg,       // Delta phi
                                         0.*deg,         // Starting theta
                                         180.*deg);      // Delta theta
    
    G4LogicalVolume* sphereLogical =
    new G4LogicalVolume(sphereSolid, mercury, "Sphere_Logical");
    
    
    new G4PVPlacement(0, G4ThreeVector(0.,0.,10.*mm), sphereLogical, "Sphere_Physical",
                      fpWorldLogical, false, 0);
    
    // 10 scoring rings
    G4double deltaTheta = 60.*deg;
    
    G4VSolid* scoreSolid = new G4Sphere("Score_Solid",   // Name
                                        innerRadius,   // Inner radius
                                        outerRadius,   // Outer radius
                                        0.*deg,        // Starting phi
                                        360.*deg,      // Delta phi
                                        0.*deg,        // Starting theta
                                        deltaTheta);   // Delta theta
    
    G4LogicalVolume* fScoreLogical =
    new G4LogicalVolume(scoreSolid, vacuum, "scoreLog");
    
    BeamTestScoreParameterisation* param =
    new BeamTestScoreParameterisation(innerRadius, outerRadius, deltaTheta);
    
    new G4PVParameterised("scorePhys",   // Name
                          fScoreLogical, // Logical volume
                          sphereLogical, // Mother volume
                          kZAxis,        // Axis
                          1,            // Number of replicas
                          param);        // Parameterisation
    
    // Mother sphere
    G4VisAttributes* sphereAttributes =
    new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.2));
    sphereAttributes->SetVisibility(false);
    sphereLogical->SetVisAttributes(sphereAttributes);
    
    // Ring scoring volumes. Green with transparancy.
    G4VisAttributes* scoreAttributes =
    new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.2));
    scoreAttributes->SetVisibility(true);
    fScoreLogical->SetVisAttributes(scoreAttributes);
    SetupScoring(fScoreLogical);
}


void FHDetectorConstruction::SetupElectricFields() {
    
//    G4ElectricField
    
//    G4UniformElectricField* acceleratingField = new G4UniformElectricField(G4ThreeVector(0.,0.,20.));
//    G4FieldManager *fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
//    fieldManager->SetDetectorField(acceleratingField);
    
    
//    FHAcceleratingElectricField* fieldSetup = new FHAcceleratingElectricField(G4ThreeVector(0.,0.,-14.*volt/m));
//    G4AutoDelete::Register(fieldSetup); //Kernel will delete the messenger
//    fEmFieldSetup.Put(fieldSetup);

    
    FHFieldManager::getInstance()->setFieldValue(G4ThreeVector(0.,0.,-300.*volt/m));
}

void FHDetectorConstruction::SetupScoring(G4LogicalVolume* scoringVolume) {
    // Create a new sensitive detector named "MyDetector"
    G4MultiFunctionalDetector* detector =
    new G4MultiFunctionalDetector("FHDetector");
//    fScoreLog->SetSensitiveDetector(detector);
    // Get pointer to detector manager
    G4SDManager* manager = G4SDManager::GetSDMpointer();
    
    // Register detector with manager
    manager->AddNewDetector(detector);
    
    // Attach detector to scoring volume
    scoringVolume->SetSensitiveDetector(detector);
    
    // Create a primitive Scorer named FHScorer
    G4PSSphereSurfaceCurrent* scorer =
    new G4PSSphereSurfaceCurrent("FHScorer",fCurrent_In);
    
//    G4VSDFilter* electronFilter = new G4SDChargedFilter("electronFilter");
//    G4SDChargedFilter
//    electronFilter->Add("e-");
//    scorer->SetFilter(electronFilter);
    
    // Register scorer with detector
    detector->RegisterPrimitive(scorer);  
}


