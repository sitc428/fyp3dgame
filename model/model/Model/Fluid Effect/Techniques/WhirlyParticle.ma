//Maya ASCII 4.5 scene
//Name: WhirlyParticle.ma
//Last modified: Thu, Jul 25, 2002 10:27:08 AM
requires maya "4.5";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "/usr/alias_cuts/maya_main_irix_r+d/bin/maya.bin";
fileInfo "product" "Maya Unlimited 4.5";
fileInfo "version" "4.5CG";
fileInfo "cutIdentifier" "200207240603";
fileInfo "osv" "IRIX64 6.5 04151556 IP30";
createNode transform -n "whirlyFluid";
createNode fluidShape -n "whirlyFluidShape" -p "whirlyFluid";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".iss" yes;
	setAttr ".dw" 10;
	setAttr ".dh" 10;
	setAttr ".dd" 10;
	setAttr ".vld" yes;
	setAttr ".vmt" 1;
	setAttr ".cl[0].clp" 0;
	setAttr ".cl[0].clc" -type "float3" 1 1 1 ;
	setAttr ".cl[0].cli" 1;
	setAttr -s 2 ".opa[0:1]"  0 0 1 1 1 1;
	setAttr -s 3 ".i";
	setAttr ".i[0].ip" 0;
	setAttr ".i[0].ic" -type "float3" 0 0 0 ;
	setAttr ".i[0].ii" 1;
	setAttr ".i[1].ip" 0.80000001192092896;
	setAttr ".i[1].ic" -type "float3" 0.89999998 0.2 0 ;
	setAttr ".i[1].ii" 1;
	setAttr ".i[2].ip" 1;
	setAttr ".i[2].ic" -type "float3" 1.5 1 0 ;
	setAttr ".i[2].ii" 1;
	setAttr ".env[0].envp" 0;
	setAttr ".env[0].envc" -type "float3" 0 0 0 ;
	setAttr ".env[0].envi" 1;
	setAttr ".nts" -type "string" (
		"This fluid requires the initial state cache: whirlyParticle.mcfi Drag and drop it from the Fluid Initial State tab, in the Motion directory in Visor, onto this fluid. The particle shape conserve parameter has been adjusted so that the particles maintain some of their momentum, but not all. Otherwise some would fly out of the fluid container. The fluid has been applied to the particles as a force, using the Dynamic relatioinship Editor. The Velocity in the fluid was created with a mel script, and preserved in the cache. It doesn't change over time because velocity is set to Contents Method> Velocity> Static Grid.");
createNode pointEmitter -n "testy";
	setAttr ".t" -type "double3" 1.9273898917254284 -2.0828192482600238 -2.9382355783190715 ;
	setAttr ".rp" -type "double3" -1.9273898917254284 2.0828192482600238 2.9382355783190715 ;
	setAttr ".sp" -type "double3" -1.9273898917254284 2.0828192482600238 2.9382355783190715 ;
	setAttr ".emt" 4;
	setAttr ".rat" 40;
	setAttr ".sro" no;
	setAttr -l on ".urpp";
	setAttr ".d" -type "double3" 0 -1 0 ;
	setAttr ".spd" 5;
	setAttr ".nspd" 0;
	setAttr ".vol" 1;
createNode transform -n "particle1";
createNode particle -n "particleShape1" -p "particle1";
	addAttr -ci true -sn "lifespanPP" -ln "lifespanPP" -bt "life" -dt "doubleArray";
	addAttr -ci true -h true -sn "lifespanPP0" -ln "lifespanPP0" -bt "life" 
		-dt "doubleArray";
	addAttr -ci true -sn "lifespan" -ln "lifespan" -bt "life" -at "double";
	addAttr -is true -ci true -sn "colorAccum" -ln "colorAccum" -min 0 -max 
		1 -at "bool";
	addAttr -is true -ci true -sn "useLighting" -ln "useLighting" -min 0 -max 
		1 -at "bool";
	addAttr -is true -ci true -sn "pointSize" -ln "pointSize" -dv 2 -min 1 -max 
		60 -at "long";
	addAttr -is true -ci true -sn "normalDir" -ln "normalDir" -dv 2 -min 1 -max 
		3 -at "long";
	setAttr -k off ".v";
	setAttr ".pos0" -type "vectorArray" 0 ;
	setAttr ".vel0" -type "vectorArray" 0 ;
	setAttr ".acc0" -type "vectorArray" 0 ;
	setAttr ".mas0" -type "doubleArray" 0 ;
	setAttr ".id0" -type "doubleArray" 0 ;
	setAttr ".bt0" -type "doubleArray" 0 ;
	setAttr ".ag0" -type "doubleArray" 0 ;
	setAttr ".irx" -type "string" "";
	setAttr ".icx" -type "string" "";
	setAttr ".con" 0.8595;
	setAttr ".cts" 1;
	setAttr ".chw" 48;
	setAttr ".lifespanPP0" -type "doubleArray" 0 ;
	setAttr -k on ".lifespan" 1;
	setAttr -k on ".colorAccum";
	setAttr -k on ".useLighting";
	setAttr -k on ".pointSize" 11;
	setAttr -k on ".normalDir";
createNode transform -n "WhirlyParticleCam";
	setAttr ".t" -type "double3" 28 21 28 ;
	setAttr ".r" -type "double3" -27.938352729602382 44.999999999999972 -5.172681101354183e-14 ;
createNode camera -n "WhirlyParticleCamShape" -p "WhirlyParticleCam";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 44.82186966202994;
	setAttr ".imn" -type "string" "persp1";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode animCurveTA -n "testy_rotateX";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  0 0 48 130.98544418884902 84 204.87011879855592 
		120 389.52305762366018;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
	setAttr ".pst" 5;
createNode animCurveTA -n "testy_rotateY";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  0 0 48 -122.4808912138345 84 -164.47535246266295 
		120 -190.08637926663835;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
	setAttr ".pst" 5;
createNode animCurveTA -n "testy_rotateZ";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  0 0 48 0 84 68.665974452568307 120 68.665974452568307;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
	setAttr ".pst" 5;
createNode materialInfo -n "materialInfo9";
createNode shadingEngine -n "fluidShape9SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lightLinker -n "lightLinker1";
select -ne :time1;
	setAttr ".o" 1;
select -ne :renderPartition;
	setAttr -s 3 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
connectAttr ":time1.o" "whirlyFluidShape.cti";
connectAttr "particleShape1.fd" "whirlyFluidShape.ind[0]";
connectAttr ":time1.o" "testy.ct";
connectAttr "particleShape1.ifl" "testy.full[0]";
connectAttr "particleShape1.tss" "testy.dt[0]";
connectAttr "particleShape1.inh" "testy.inh[0]";
connectAttr "particleShape1.stt" "testy.stt[0]";
connectAttr "particleShape1.sd[0]" "testy.sd[0]";
connectAttr "testy_rotateX.o" "testy.rx";
connectAttr "testy_rotateY.o" "testy.ry";
connectAttr "testy_rotateZ.o" "testy.rz";
connectAttr ":time1.o" "particleShape1.cti";
connectAttr "testy.ot[0]" "particleShape1.npt[0]";
connectAttr "whirlyFluidShape.of[0]" "particleShape1.ifc[0]";
connectAttr "fluidShape9SG.msg" "materialInfo9.sg";
connectAttr "whirlyFluidShape.ocl" "fluidShape9SG.vs";
connectAttr "whirlyFluidShape.iog" "fluidShape9SG.dsm" -na;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "fluidShape9SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr "fluidShape9SG.pa" ":renderPartition.st" -na;
connectAttr "whirlyFluidShape.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "particleShape1.iog" ":initialParticleSE.dsm" -na;
// End of WhirlyParticle.ma
