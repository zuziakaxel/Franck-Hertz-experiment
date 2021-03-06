
#include "FHPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

FHPrimaryGeneratorAction::FHPrimaryGeneratorAction() {
    G4int n_particle = 200;
    particleGun  = new G4ParticleGun(n_particle);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
    
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    particleGun->SetParticleEnergy(0.00001*eV);
    particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-20.*mm));
}

FHPrimaryGeneratorAction::~FHPrimaryGeneratorAction() {
    delete particleGun;
}

void FHPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    particleGun->GeneratePrimaryVertex(anEvent);
}
