//
//  FHRunAction.h
//  B1
//
//  Created by Axel Zuziak on 06.01.2016.
//
//

#ifndef FHRunAction_h
#define FHRunAction_h

#include <stdio.h>


#include "G4UserRunAction.hh"

class G4Run;

class FHRunAction : public G4UserRunAction {
    
public:
    
    // Constructor
    FHRunAction();
    
    // Destructor
    virtual ~FHRunAction();
    
    // Method
    void BeginOfRunAction(const G4Run* );
    void EndOfRunAction(const G4Run* );
    G4Run* GenerateRun();
    
};




#endif /* FHRunAction_h */
