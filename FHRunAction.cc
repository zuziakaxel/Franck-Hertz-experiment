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
    while( iter != theRun->frunHitsMap.GetMap()->end() ) {
        G4cout<< "FHLog:      value of HitsMap for run: "<< *iter->second << " index of value: "<< iter->first << G4endl;
        iter++;
    }

}
G4Run* FHRunAction::GenerateRun() {
    return new FHRun();
}