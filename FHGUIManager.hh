
#ifndef FHGUIManager_h
#define FHGUIManager_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithADouble.hh"

class F04GlobalField;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class F04DetectorConstruction;

class FHGUIManager: public G4UImessenger
{
  public:
    FHGUIManager();
    virtual ~FHGUIManager();

    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
 
    G4UIdirectory*             fDetDir;

    G4UIcmdWithADouble* fFieldValue;
    G4UIcmdWithADouble* fFieldAcceleration;

};

#endif
