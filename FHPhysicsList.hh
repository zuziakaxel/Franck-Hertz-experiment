#ifndef FHPHYSICSLIST_HH
#define FHPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class FHPhysicsList: public G4VUserPhysicsList {
    
public:
    
    // Constructor
    FHPhysicsList();
    
    // Destructor
    virtual ~FHPhysicsList();
    
protected:
    
    // Construct particles and physics processes
    void ConstructParticle();
    void ConstructProcess();
    
    void SetCuts();
    
private:
    
    // Helper methods
    void ConstructGeneral();
    void ConstructEM();
    
};

#endif



