#include "FHRun.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include <iomanip>
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "FHFieldManager.hh"

FHRun::FHRun() {
    G4SDManager* manager = G4SDManager::GetSDMpointer();
    fMapId = manager->GetCollectionID("FHDetector/FHScorer");
    G4cout << "FHLog:  FHRun constructor: index of electron scorer map: " << fMapId << G4endl;
}

FHRun::~FHRun() { }


void FHRun::RecordEvent(const G4Event* evt) {
    numberOfEvent++;
    
    G4TrajectoryContainer* container = evt->GetTrajectoryContainer();
    
    G4cout << "FHLog: number of particle processed in this event "
    << container->size() << G4endl;
    
    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    
    G4THitsMap<double>* hitsMap =  (G4THitsMap<double>*) (hce->GetHC(fMapId));
    G4cout << "FHLog: number of entries " << hitsMap->entries() << G4endl;
    std::ofstream outputFile;
    outputFile.open ("wyniki.dat", std::ios_base::app);
    outputFile << FHFieldManager::getInstance()->getFieldValue() << "\t" << hitsMap->entries() << "\n";
    outputFile.close();
    std::map<int,double*>::iterator iter;
    iter = hitsMap->GetMap()->begin();
    while( iter != hitsMap->GetMap()->end() ) {
//        G4cout<< "FHLog:      value of HitsMap: "<< *iter->second << " index of value: "<< iter->first << G4endl;
        iter++;
    }
    
    frunHitsMap += *hitsMap;
    
//    G4cout << "FHLog: " << electronsCount << " passed through anode" << G4endl;
    
    
}
