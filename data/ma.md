# intro
comment - //

## commands as appear
requires 
//requires maya "1.0"

### currentUnit
//currentUnit -l centimeter -a degree -t film;

### fileinfo
//fileInfo "application" "maya";

### createNode
//some nodes exist in any maya scene, so -s used to avoid duplicate creation in
//case of import. -p is parent

//createNode transform -s -n "persp";
//setAttr ".v" no;
//setAttr ".t" -type "double3" 1.1735026665765096 5.9220720263848738 8.9758656194014179 ;
//setAttr ".r" -type "double3" -20.738352729602383 13.400000000000002 1.2260871514867887e-015 ;
//createNode camera -s -n "perspShape" -p "persp";
//setAttr -k off ".v" no;

just copy unimplemented nodes as a string
//createNode script -n "uiConfigurationScriptNode";

### setAttr
set nodes attributes

### select
//select -ne :time1;
//	setAttr ".o" 1;
//	setAttr ".unw" 1;

### connectAttr
//connectAttr "groupId1.id" "polySurfaceShape2.iog.og[0].gid";

#### relationship - WTF?
//relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";

## Nodes

### transform

#### standard view's
createNode transform -s -n "persp";
createNode transform -s -n "top";
createNode transform -s -n "front";
createNode transform -s -n "side";

### camera

#### standard view's
createNode camera -s -n "perspShape" -p "persp";
createNode camera -s -n "topShape" -p "top";
createNode camera -s -n "frontShape" -p "front";
createNode camera -s -n "sideShape" -p "side";

### mesh
mesh use parent transform
createNode transform -n "polySurface1";
createNode mesh -n "polySurfaceShape2" -p "polySurface1";

### script
### shade nodes
#### shadingEngine
#### materialInfo
#### phongE
#### lambert
#### place2dTexture
#### bump2d
#### groupId
