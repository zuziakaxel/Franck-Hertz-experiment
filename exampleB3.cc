#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "Randomize.hh"

#include "FHDetectorConstruction.hh"
#include "FHPhysicsList.hh"
#include "FHPrimaryGeneratorAction.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "FHRunAction.hh"


int main(int argc,char** argv) {
    
// Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    
// Construct the default run manager
#ifdef G4MULTITHREADED
    std::cout<<"multi";
    G4MTRunManager* runManager = new G4MTRunManager;
#else
    std::cout<<"single core";
    G4RunManager* runManager = new G4RunManager;
#endif

    // Mandatory initialization classes
    runManager->SetUserInitialization(new FHDetectorConstruction);
    runManager->SetUserInitialization(new FHPhysicsList);

    // User action classes
    runManager->SetUserAction(new FHPrimaryGeneratorAction());
    runManager->SetUserAction(new FHRunAction());

    // Initialize visualization
    //
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //

    if ( ! ui ) { 
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
//        UImanager->ApplyCommand("/control/execute /Users/zuziakaxel/Development/Geant4/projects/FH/Debug/run1.mac");
//        UImanager->ApplyCommand("/control/loop sim.mac var 1 15 1");
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
//        UImanager->ApplyCommand("/control/execute /Users/zuziakaxel/Development/Geant4/projects/FH/Debug/run1.mac");
//        UImanager->ApplyCommand("/control/loop sim.mac var 1 15 1");
        ui->SessionStart();

        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !

    delete visManager;
    delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
