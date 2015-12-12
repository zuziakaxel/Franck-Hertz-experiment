#ifndef FHPrimaryGeneratorAction_HH
#define FHPrimaryGeneratorAction_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class FHPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
    
public:
    
    // Constructor
    FHPrimaryGeneratorAction();
    
    // Destructor
    virtual ~FHPrimaryGeneratorAction();
    
    // Method
    void GeneratePrimaries(G4Event*);
    
private:
    
    // Data member
    G4ParticleGun* particleGun;
    
};

#endif
