//Maya ASCII 4.5 scene
//Name: HeightField.ma
//Last modified: Wed, Jul 24, 2002 10:02:14 AM
requires maya "4.5";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "/usr/alias_cuts/maya_main_irix_r+d/bin/maya.bin";
fileInfo "product" "Maya Unlimited 4.5";
fileInfo "version" "4.5CG";
fileInfo "cutIdentifier" "200207220603";
fileInfo "osv" "IRIX64 6.5 04151556 IP30";
createNode transform -n "transform1";
	setAttr ".s" -type "double3" 72.6205848754866 1 72.6205848754866 ;
	setAttr -l on ".sy";
createNode heightField -n "heightField1" -p "transform1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".res" 60;
	setAttr -l on ".hc";
	setAttr ".nts" -type "string" (
		"This scene has a heightfield that is positioned to match a displaced plane. The idea is to provide good feedback on a displaced plane for terrain generation. If you playback you will notice that the time value on the noise texture is animated. The same noise texture feeds into both the heightfield and surface displacement. In addition a bumpmap provides for good detail. Look at the shading network of the noise texture in hypershade. By replacing the connections to this noise texture you can easily substitute any other 2D texture. \n"
		+ "A similar network can be built from scratch by applying a displacement to a plane and connecting the alphaOut of the displacement texture to a heightfield with the same transformation as the plane. Make sure, however, that the transform's yscale and the heightScale of the height field are both 1.0, or the displacement won't match.");
createNode transform -n "nurbsPlane1" -p "transform1";
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
	setAttr -l on ".shxy";
	setAttr -l on ".shxz";
	setAttr -l on ".shyz";
createNode nurbsSurface -n "nurbsPlaneShape1" -p "nurbsPlane1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".tw" yes;
	setAttr ".bbs" -type "float3" 21.209997 21.209997 21.209997 ;
	setAttr ".fbda" no;
	setAttr ".dvu" 0;
	setAttr ".dvv" 0;
	setAttr ".cpr" 4;
	setAttr ".cps" 1;
	setAttr ".eta" yes;
	setAttr ".nufa" 4.5;
	setAttr ".nvfa" 4.5;
	setAttr ".nts" -type "string" "See the heightfield node for info.";
createNode transform -n "HeightFieldCam";
	setAttr ".t" -type "double3" 28 21 28 ;
	setAttr ".r" -type "double3" -27.938352729602382 44.999999999999972 -5.172681101354183e-14 ;
createNode camera -n "HeightFieldCamShape" -p "HeightFieldCam";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 44.82186966202994;
	setAttr ".imn" -type "string" "persp1";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode noise -n "noise1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr ".f" 0;
	setAttr ".fo" 0.00390625;
	setAttr ".ail" yes;
	setAttr ".ag" 10;
	setAttr ".ra" 0.22329999506473541;
	setAttr ".dm" 4;
	setAttr ".fq" 3.8859999179840088;
	setAttr ".fr" 2.7478001117706299;
	setAttr ".in" yes;
	setAttr ".nty" 0;
	setAttr ".imp" -0.80584001541137695;
	setAttr ".nts" -type "string" (
		"This simulates a simple rolling boil by using inflection and animating the time value. The negative implode pushes the noise away from the center. See the heightfield node for more info.");
createNode place2dTexture -n "place2dTexture1";
createNode expression -n "expression1";
	setAttr -k on ".nds";
	setAttr ".ixp" -type "string" ".O[0]=time";
createNode makeNurbPlane -n "makeNurbPlane1";
	setAttr ".ax" -type "double3" 0 1 0 ;
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode blinn -n "blinn1";
	setAttr ".sc" -type "float3" 0 0 0 ;
createNode bump2d -n "bump2d1";
	setAttr ".bd" 0.69999998807907104;
	setAttr ".bf" 0;
	setAttr ".bfo" 0.0010000000474974513;
	setAttr ".vc1" -type "float3" 0 0.33699921 0 ;
	setAttr ".vc2" -type "float3" 0.001 0.001 0 ;
createNode displacementShader -n "displacementShader1";
createNode lightLinker -n "lightLinker1";
select -ne :time1;
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -s 3 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :lightList1;
select -ne :defaultTextureList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".sdf" -type "string" "";
	setAttr ".pfm" -type "string" "";
	setAttr ".top" 187;
	setAttr ".left" 54;
	setAttr ".bot" 140;
	setAttr ".rght" 142;
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr ".ofe" -type "string" "";
	setAttr ".efe" -type "string" "";
	setAttr ".lse" -type "string" "";
	setAttr ".rse" -type "string" "";
	setAttr ".oft" -type "string" "";
	setAttr ".ifp" -type "string" "";
	setAttr ".npu" 1;
	setAttr ".prm" -type "string" "";
	setAttr ".pom" -type "string" "";
	setAttr ".pfrm" -type "string" "";
	setAttr ".pfom" -type "string" "";
connectAttr "noise1.oa" "heightField1.dis";
connectAttr "makeNurbPlane1.os" "nurbsPlaneShape1.cr";
connectAttr "heightField1.res" "nurbsPlaneShape1.nu";
connectAttr "heightField1.res" "nurbsPlaneShape1.nv";
connectAttr "place2dTexture1.o" "noise1.uv";
connectAttr "place2dTexture1.ofs" "noise1.fs";
connectAttr "expression1.out[0]" "noise1.ti";
connectAttr ":time1.o" "expression1.tim";
connectAttr "blinn1SG.msg" "materialInfo1.sg";
connectAttr "blinn1.oc" "blinn1SG.ss";
connectAttr "nurbsPlaneShape1.iog" "blinn1SG.dsm" -na;
connectAttr "displacementShader1.d" "blinn1SG.ds";
connectAttr "bump2d1.o" "blinn1.n";
connectAttr "noise1.oa" "bump2d1.bv";
connectAttr "noise1.oa" "displacementShader1.d";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "blinn1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr "blinn1SG.pa" ":renderPartition.st" -na;
connectAttr "blinn1.msg" ":defaultShaderList1.s" -na;
connectAttr "displacementShader1.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "bump2d1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "heightField1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "noise1.msg" ":defaultTextureList1.tx" -na;
// End of HeightField.ma