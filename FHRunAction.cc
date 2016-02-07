//
//  FHRunAction.c
//  B1
//
//  Created by Axel Zuziak on 06.01.2016.
//
//

#include "FHRunAction.hh"
#include "G4Run.hh"
#include "FHRun.hh"
#include "globals.hh"
#include "FHRun.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include <iomanip>
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "FHFieldManager.hh"

FHRunAction::FHRunAction() { }

FHRunAction::~FHRunAction() { }

void FHRunAction::BeginOfRunAction(const G4Run* aRun) {
    G4cout << "FHLog:   Begin of run" << G4endl;
}

void FHRunAction::EndOfRunAction(const G4Run* aRun) {
    
    FHRun* theRun = (FHRun*) aRun;
    G4cout << "FHLog: number of map entries in run: " << theRun->frunHitsMap.entries() << G4endl;
    
    std::map<int,double*>::iterator iter;
    iter = theRun->frunHitsMap.GetMap()->begin();
    double electronsCount = 0.0;
    while( iter != theRun->frunHitsMap.GetMap()->end() ) {
        G4cout<< "FHLog:      value of HitsMap for run: "<< *iter->second << " index of value: "<< iter->first << G4endl;
        electronsCount = *iter->second;
        
        iter++;
    }
//    G4THitsMap<double>* hitsMap =  (G4THitsMap<double>*) (hce->GetHC(fMapId));
//    G4cout << "FHLog: number of entries " << hitsMap->entries() << G4endl;
    std::ofstream outputFile;
    outputFile.open ("wyniki3.dat", std::ios_base::app);
    outputFile << FHFieldManager::getInstance()->getFieldValue() << "\t" << electronsCount << "\n";
    outputFile.close();

}
G4Run* FHRunAction::GenerateRun() {
    return new FHRun();
}