//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4UnionSolid.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction() 
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
  fKillVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
  static const double     pi  = 3.14159265358979323846;

  // Elements

  G4double A, Z, nel, natoms, density;
  G4String name;

  G4Element* elNa = new G4Element("Sodium",  "Na", Z=11., A= 22.989768*g/mole);
  G4Element* elI  = new G4Element("Iodine",  "I",  Z=53., A= 126.90447*g/mole);
  G4Element* elAl = new G4Element("Aluminium",  "Al", Z=13., A= 26.981539*g/mole);
  G4Element* elO  = new G4Element("Oxygene",  "O",  Z=8., A= 15.9994*g/mole);
  G4Element* elC = new G4Element("Carbon",  "C", Z=6., A= 12.0106*g/mole);
  G4Element* elH  = new G4Element("Hydrogene",  "H",  Z=1., A= 1.0000*g/mole);
  G4Element* elSi  = new G4Element("Silicium",  "Si",  Z=14., A= 28.085*g/mole);
  G4Element* elPb = new G4Element("Plomb",  "Pb", Z=82., A= 207.2*g/mole);
  G4Element* elCa = new G4Element("Calcium",  "Ca", Z=20., A= 40.078*g/mole);
  G4Element* elK = new G4Element("Potassium",  "K", Z=19., A= 39.0983*g/mole);

  // Materials

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Cu_mat = nist->FindOrBuildMaterial("G4_Cu");

  density = 3.67 *g/cm3;
  G4Material* NaI_mat = new G4Material(name="NaI", density, nel=2);
  NaI_mat -> AddElement(elNa, natoms=0.5);
  NaI_mat -> AddElement(elI,  natoms=0.5);

  density = 3.97 *g/cm3;
  G4Material* Al2O3_mat = new G4Material(name="Al2O3", density, nel=2);
  Al2O3_mat -> AddElement(elAl, natoms=0.4);
  Al2O3_mat -> AddElement(elO,  natoms=0.6);

  density = 2.329 *g/cm3;
  G4Material* Silicon_mat = new G4Material(name="Silicon", density, nel=4);
  Silicon_mat -> AddElement(elC, natoms=0.2);
  Silicon_mat -> AddElement(elO,  natoms=0.1);
  Silicon_mat -> AddElement(elH,  natoms=0.6);
  Silicon_mat -> AddElement(elSi,  natoms=0.1);

  density = 2.7 *g/cm3;
  G4Material* Al_mat = new G4Material(name="Al", density, nel=1);
  Al_mat -> AddElement(elAl, natoms=1);

  density = 11.35 *g/cm3;
  G4Material* Pb_mat = new G4Material(name="Plomb", density, nel=1);
  Pb_mat -> AddElement(elPb, natoms=1);

  density = 0.2120 *g/cm3;
  G4Material* Cendres_mat = new G4Material(name="Cendres", density, nel=4);
  Cendres_mat -> AddElement(elC, natoms=0.6);
  Cendres_mat -> AddElement(elCa, natoms=0.3);
  Cendres_mat -> AddElement(elK, natoms=0.05);
  Cendres_mat -> AddElement(elO, natoms=0.05);

  // Colors

  G4Color red(1.0, 0.0, 0.0);
  G4VisAttributes* attrired = new G4VisAttributes(red);
  //attrired -> SetForceWireframe(true);
   
  G4Color green(0.0, 1.0, 0.0);
  G4VisAttributes* attrigreen = new G4VisAttributes(green);
  //attrigreen -> SetForceWireframe(true);

  G4Color blue(0.0, 0.0, 1.0);
  G4VisAttributes* attriblue = new G4VisAttributes(blue);
  //attriblue -> SetForceWireframe(true);

  G4Color purple(0.6, 0.3, 0.9);
  G4VisAttributes* attripurple = new G4VisAttributes(purple);
  //attripurple -> SetForceWireframe(true);

  G4Color orange(0.95, 0.6, 0.05);
  G4VisAttributes* attriorange = new G4VisAttributes(orange);
  //attriorange -> SetForceWireframe(true);

  // Rotation Matrix

  G4RotationMatrix* rot = new G4RotationMatrix;
  rot -> rotateX(90*deg);
  rot -> rotateY(0);
  rot -> rotateZ(0);

  //------------------------------------------------//
  //------------- Solides definition ---------------//
  //------------------------------------------------//

  // World
  
  G4Box* solidWorld = new G4Box("World", 110*mm, 160*mm, 110*mm);
      
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
                                   
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     

  // NaI crystal

  G4Tubs* solidNaI = new G4Tubs("NaI", 0*mm, 38*mm, 38*mm, 0, 2*pi);
      
  G4LogicalVolume* logicNaI =                         
    new G4LogicalVolume(solidNaI,            //its solid
                        NaI_mat,             //its material
                        "NaI");         //its name

  logicNaI -> SetVisAttributes(attrired);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicNaI,                //its logical volume
                    "NaI",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Al2O3

  G4Tubs* solidAl2O3Front = new G4Tubs("Al2O3Front", 0*mm, 40*mm, 0.655*mm, 0, 2*pi);
  G4Tubs* solidAl2O3Side = new G4Tubs("Al2O3Side", 38*mm, 40*mm, 38*mm, 0, 2*pi);

  G4ThreeVector TransAl2O3(0, 0, 38.655*mm);
  G4UnionSolid* UnionAl2O3 = new G4UnionSolid("UnionAl2O3", solidAl2O3Side, solidAl2O3Front, 0, TransAl2O3);

  G4LogicalVolume* logicAl2O3 =
  new G4LogicalVolume(UnionAl2O3,            //its solid
                        Al2O3_mat,             //its material
                        "Al2O3");         //its name

  logicAl2O3 -> SetVisAttributes(attripurple);

  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicAl2O3,                //its logical volume
                    "Al2O3",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Silicon_couvercle

  G4Tubs* solidSilicon = new G4Tubs("Silicon", 0*mm, 40*mm, 1*mm, 0, 2*pi);
      
  G4LogicalVolume* logicSilicon =
  new G4LogicalVolume(solidSilicon,            //its solid
                        Silicon_mat,             //its material
                        "Silicon");         //its name

  logicSilicon -> SetVisAttributes(attrigreen);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 40.31*mm, 0),         //at (0,0,0)
                    logicSilicon,                //its logical volume
                    "Silicon",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Aluminium

  G4Tubs* solidAlFront = new G4Tubs("AlFront", 0*mm, 41.5*mm, 0.75*mm, 0, 2*pi);
  G4Tubs* solidAlSide = new G4Tubs("AlSide", 40*mm, 41.5*mm, 39.655*mm, 0, 2*pi);
  G4Tubs* solidAlPm = new G4Tubs("AlPm", 0*mm, 41.5*mm, 15*mm, 0, 2*pi);

  G4ThreeVector TransAl(0, 0, 40.405*mm);
  G4UnionSolid* UnionAl = new G4UnionSolid("UnionAl", solidAlSide, solidAlFront, 0, TransAl);

  G4ThreeVector TransAlPm(0, 0, -54.655*mm);
  G4UnionSolid* UnionAlPm = new G4UnionSolid("UnionAlPm", UnionAl, solidAlPm, 0, TransAlPm);

  G4LogicalVolume* logicAlPm =
  new G4LogicalVolume(UnionAlPm,            //its solid
                        Al_mat,             //its material
                        "AlPm");         //its name

  logicAlPm -> SetVisAttributes(attriorange);

  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 1.655*mm, 0),         //at (0,0,0)
                    logicAlPm,                //its logical volume
                    "AlPm",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Copper shielding

  G4Tubs* solidCu1 = new G4Tubs("Cu1", 43.5*mm, 46.5*mm, 74.5*mm, 0, 2*pi);
  G4Tubs* solidCu2 = new G4Tubs("Cu2", 57*mm, 60*mm, 21*mm, 0, 2*pi);
  G4Tubs* solidCu3 = new G4Tubs("Cu3", 43.5*mm, 60*mm, 1.5*mm, 0, 2*pi);
  G4Tubs* solidCu4 = new G4Tubs("Cu4", 0*mm, 60*mm, 1.5*mm, 0, 2*pi);

  G4ThreeVector TransCu1(0, 0, 76*mm);
  G4UnionSolid* UnionCu1 = new G4UnionSolid("UnionCu1", solidCu1, solidCu3, 0, TransCu1);

  G4ThreeVector TransCu2(0, 0, 97*mm);
  G4UnionSolid* UnionCu2 = new G4UnionSolid("UnionCu2", UnionCu1, solidCu2, 0, TransCu2);

  G4ThreeVector TransCu3(0, 0, 119.5*mm); // 98.5
  G4UnionSolid* UnionCu3 = new G4UnionSolid("UnionCu3", UnionCu2, solidCu4, 0, TransCu3);

  G4LogicalVolume* logicCu =
  new G4LogicalVolume(UnionCu3,            //its solid
                        Cu_mat,             //its material
                        "Cu");         //its name

  logicCu -> SetVisAttributes(attrired);

  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, -34.5*mm, 0),         //at (0,0,0)
                    logicCu,                //its logical volume
                    "Cu",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Lead shielding

  G4Tubs* solidPb1 = new G4Tubs("Pb1", 46.5*mm, 105*mm, 74.5*mm, 0, 2*pi);
  G4Tubs* solidPb2 = new G4Tubs("Pb2", 60*mm, 105*mm, 22.5*mm, 0, 2*pi);
  G4Tubs* solidPb3 = new G4Tubs("Pb3", 60*mm, 105*mm, 1.5*mm, 0, 2*pi);
  G4Tubs* solidPb4 = new G4Tubs("Pb4", 0*mm, 105*mm, 30.5*mm, 0, 2*pi);

  G4ThreeVector TransPb1(0, 0, 76*mm);
  G4UnionSolid* UnionPb1 = new G4UnionSolid("UnionPb1", solidPb1, solidPb3, 0, TransPb1);

  G4ThreeVector TransPb2(0, 0, 98.5*mm);
  G4UnionSolid* UnionPb2 = new G4UnionSolid("UnionPb2", UnionPb1, solidPb2, 0, TransPb2);

  G4ThreeVector TransPb3(0, 0, 151.5*mm); // 129
  G4UnionSolid* UnionPb3 = new G4UnionSolid("UnionPb3", UnionPb2, solidPb4, 0, TransPb3);

  G4LogicalVolume* logicPb =
  new G4LogicalVolume(UnionPb3,            //its solid
                        Pb_mat,             //its material
                        "Pb");         //its name

  logicPb -> SetVisAttributes(attriblue);

  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, -34.5*mm, 0),         //at (0,0,0)
                    logicPb,                //its logical volume
                    "Pb",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
/*
// Cendres cylindre

  G4Tubs* solidCendres = new G4Tubs("Cendres", 0*mm, 45*mm, 10*mm, 0, 2*pi);
      
  G4LogicalVolume* logicCendres =                         
  new G4LogicalVolume(solidCendres,            //its solid
                        Cendres_mat,             //its material
                        "Cendres");         //its name

  logicCendres -> SetVisAttributes(attriblue);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 55.5*mm, 0),         //at (0,0,0)
                    logicCendres,                //its logical volume
                    "Cendres",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// Al_cendres

  G4Tubs* solidAl_cendres = new G4Tubs("Al_cendres", 45.001*mm, 46*mm, 10*mm, 0, 2*pi);
      
  G4LogicalVolume* logicAl_cendres =                         
  new G4LogicalVolume(solidAl_cendres,            //its solid
                        Al_mat,             //its material
                        "Al_cendres");         //its name

  logicAl_cendres -> SetVisAttributes(attriblue);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 55.5*mm, 0),         //at (0,0,0)
                    logicAl_cendres,                //its logical volume
                    "Al_cendres",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// Al_up

  G4Tubs* solidAl_up = new G4Tubs("Al_up", 0*mm, 46*mm, 0.5*mm, 0, 2*pi);
      
  G4LogicalVolume* logicAl_up =                         
  new G4LogicalVolume(solidAl_up,            //its solid
                        Al_mat,             //its material
                        "Al_up");         //its name

  logicAl_up -> SetVisAttributes(attriblue);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 66.001*mm, 0),         //at (0,0,0)
                    logicAl_up,                //its logical volume
                    "Al_up",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// Al_bottom

  G4Tubs* solidAl_bottom = new G4Tubs("Al_bottom", 0*mm, 46*mm, 0.5*mm, 0, 2*pi);
      
  G4LogicalVolume* logicAl_bottom =                         
  new G4LogicalVolume(solidAl_bottom,            //its solid
                        Al_mat,             //its material
                        "Al_bottom");         //its name

  logicAl_bottom -> SetVisAttributes(attriblue);
               
  new G4PVPlacement(rot,                       //no rotation
                    G4ThreeVector(0, 44.999*mm, 0),         //at (0,0,0)
                    logicAl_bottom,                //its logical volume
                    "Al_bottom",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
*/
  //
  fScoringVolume = logicNaI;
  fKillVolume = logicPb;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
