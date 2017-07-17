#intro
comment - //

#commands as appear
requires 
//requires maya "1.0"

#currentUnit
//currentUnit -l centimeter -a degree -t film;

#fileinfo
//fileInfo "application" "maya";

#createNode
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

#select
//select -ne :time1;
//	setAttr ".o" 1;
//	setAttr ".unw" 1;

#connectAttr
//connectAttr "groupId1.id" "polySurfaceShape2.iog.og[0].gid";

#relationship - WTF?
//relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
