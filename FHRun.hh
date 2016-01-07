#ifndef FHRun_HH
#define FHRun_HH

#include "G4Run.hh"
#include "G4THitsMap.hh"

class FHRun : public G4Run {

public:

    // Constructor
    FHRun();

    // Destructor
    virtual ~FHRun();


    void RecordEvent(const G4Event*);
    
    G4int fMapId;
    G4THitsMap<G4double> frunHitsMap;

};

#endif
