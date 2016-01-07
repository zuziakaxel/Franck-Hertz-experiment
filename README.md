#Franck-Hertz experiment
##Geant4 implementation


####Reference:
http://hyperphysics.phy-astr.gsu.edu/hbase/FrHz.html#FH

####Plan (in polish):
1. Implementacja w GEANT4 układu pomiarowego który zapewnia uzyskanie wyników
    zbliżonych do oryginalnego eksperymentu.
2. Wykonanie symulacji z zapisaniem odpowiednich wyników pomiarowych.
3. Porównanie wyników symulacji z oryginalnymi danymi pomiarowymi (jeśli dostępne)
4. Porównanie wyników symulacji z przewidywaniami teoretycznymi.
5. Napisanie poleceń interfejsu użytkownika umożliwiającego łatwą zmianę parametrów symulacji, wizualizacji
    i analizy wyników.



####How to run:

- Optionally build using Xcode 🤓
- Locate executable file: `debug/exampleB1`
- run: `./exampleB1`
- `Idle> /control/execute run.mac`
Note that run.mac file should be in `debug` folder.
or simply:
`./exampleB1 run.mac`

Now, you can also specify z-value of uniform electric field: `field/setAcceleration 15` (V) or `field/setValue` (V/m).

Type: `/control/loop sim.mac var 1 15 1` to get electrons count for voltage in range (1,2,3...15).

####Environment variables needed:

- *G4ENSDFSTATEDATA* : `path/to/G4ENSDFSTATE1.2`
- *G4LEDATA* : `path/to/G4EMLOW6.48`

####State

- Still needs improvements in units.
- `G4THitsMap.entries()` always returns `count = 5`, why? 😵
- Application is crashing when mercury vapor density > 0.7 > g/cm3 (safety)
