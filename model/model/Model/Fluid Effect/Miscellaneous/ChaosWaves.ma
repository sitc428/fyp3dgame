//Maya ASCII 5.0 scene
//Name: ChaosWaves.ma
//Last modified: Mon, Apr 14, 2003 10:00:11 PM
requires maya "5.0";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 5.0";
fileInfo "version" "5.0";
fileInfo "cutIdentifier" "200303260009";
fileInfo "osv" "Microsoft Windows 2000 Professional Service Pack 2 (Build 2195)\n";
createNode transform -n "ChaosWavesFluid";
createNode fluidShape -n "ChaosWavesFluidShape" -p "ChaosWavesFluid";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".vf" 0;
	setAttr ".iss" yes;
	setAttr ".rw" 100;
	setAttr ".rh" 100;
	setAttr ".dw" 10;
	setAttr ".dh" 10;
	setAttr ".dd" 1;
	setAttr ".sli" 1;
	setAttr ".ots" 2;
	setAttr ".srs" 2;
	setAttr ".sol" 2;
	setAttr ".rin" 3;
	setAttr -s 5 ".cl";
	setAttr ".cl[0].clp" 0.48571428656578064;
	setAttr ".cl[0].clc" -type "float3" 0.13800001 0.36714828 1 ;
	setAttr ".cl[0].cli" 1;
	setAttr ".cl[1].clp" 0.5;
	setAttr ".cl[1].clc" -type "float3" 0.0070000002 0.0070000002 0.0070000002 ;
	setAttr ".cl[1].cli" 1;
	setAttr ".cl[2].clp" 0.51428574323654175;
	setAttr ".cl[2].clc" -type "float3" 1 0.10985734 0.092000008 ;
	setAttr ".cl[2].cli" 1;
	setAttr ".cl[3].clp" 0.014000000432133675;
	setAttr ".cl[3].clc" -type "float3" 0.19099998 1 0.20583163 ;
	setAttr ".cl[3].cli" 1;
	setAttr ".cl[4].clp" 0.97100001573562622;
	setAttr ".cl[4].clc" -type "float3" 1 0.98250002 0 ;
	setAttr ".cl[4].cli" 1;
	setAttr ".coi" 5;
	setAttr -s 3 ".opa";
	setAttr ".opa[0:1]" 0 1 1 1 1 1;
	setAttr ".opa[4].opap" 0.5;
	setAttr ".opa[4].opafv" 0;
	setAttr ".opa[4].opai" 1;
	setAttr ".t" -type "float3" 0.0082599996 0.0082599996 0.0082599996 ;
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
	setAttr ".dos" 0;
	setAttr ".nts" -type "string" (
		"Preset Goal:\r\n"
		+ "Kaleidoscopic effect.\r\n"
		+ "\r\n"
		+ "Basic Construction:\r\n"
		+ "The fluid uses the new spring mesh solver with a fluid emitter in the middle of the 3D container. The density drives the colour ramp which has tight cusps to give clean delineations between the colours in the fluid. The Opacity graph is also driven by the density. It emphasizes the opacity of the high and low densities, while de-emphasizin the mid range densities. The nature of the spring mesh solver is to propagate the density emitted out from the point where it is emitted from, giving the outward movement of the fluid.\r\n"
		+ "\r\n"
		+ "Finer Points:\r\n"
		+ "The simulation rate scale is set at 2. the default is 1. This is to speed up the simulation, effectively skipping frames. The simulation doesn't suffer for it. There is no texturing or self shadowing. Render time: $\r\n");
createNode fluidEmitter -n "fluidEmitter1" -p "ChaosWavesFluid";
	setAttr -k off ".rat";
	setAttr -k off ".sro";
	setAttr -l on -k off ".urpp";
	setAttr -k off ".npuv";
	setAttr ".max" 1;
	setAttr -k off ".dx";
	setAttr -k off ".dy";
	setAttr -k off ".dz";
	setAttr -k off ".spr";
	setAttr -k off ".spd";
	setAttr -k off ".srnd";
	setAttr -k off ".tspd";
	setAttr -k off ".nspd";
	setAttr -k off ".afc";
	setAttr -k off ".afa";
	setAttr -k off ".alx";
	setAttr -k off ".arx";
	setAttr -k off ".rnd";
	setAttr -k off ".drs";
	setAttr -k off ".ssz";
	setAttr -k off ".dss";
	setAttr ".fhe" 1;
	setAttr ".ffe" 1;
createNode transform -n "KaleidascopeCam";
	addAttr -ci true -h true -sn "dfm" -ln "miDeriveFromMaya" -bt "UNKN" -dv 
		1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "hde" -ln "miHide" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "vsb" -ln "miVisible" -bt "UNKN" -dv 2 -at "short";
	addAttr -ci true -sn "trc" -ln "miTrace" -bt "UNKN" -dv 2 -at "short";
	addAttr -ci true -sn "shd" -ln "miShadow" -bt "UNKN" -dv 2 -at "short";
	addAttr -ci true -sn "cst" -ln "miCaustic" -bt "UNKN" -dv 5 -at "short";
	addAttr -ci true -sn "glb" -ln "miGlobillum" -bt "UNKN" -dv 5 -at "short";
	addAttr -ci true -sn "mieg" -ln "miExportGeoShader" -bt "UNKN" -min 0 -max 
		1 -at "bool";
	addAttr -ci true -sn "migs" -ln "miGeoShader" -bt "UNKN" -at "message";
	setAttr ".t" -type "double3" -0.033555854848339957 -0.043899383442213148 
		9.6130052597770241 ;
	setAttr ".r" -type "double3" 0.26164727039761931 -0.19999999999998824 -9.7063417315951675e-020 ;
createNode camera -n "KaleidascopeCamShape" -p "KaleidascopeCam";
	setAttr -k off ".v";
	setAttr ".ovr" 1.3;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 9.6131640616272804;
	setAttr ".imn" -type "string" "persp1";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
	setAttr ".dr" yes;
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "fluidShape1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lightLinker -n "lightLinker1";
select -ne :time1;
	setAttr ".o" 20;
select -ne :renderPartition;
	setAttr -s 3 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -sn "currentRenderer" -ln "currentRenderer" -dt "string";
	setAttr ".mcfr" 500;
	setAttr ".pfm" -type "string" "";
	setAttr ".top" 82;
	setAttr ".left" 184;
	setAttr ".bot" 50;
	setAttr ".rght" 202;
	setAttr ".an" yes;
	setAttr ".fs" 1;
	setAttr ".ef" 60;
	setAttr ".oft" -type "string" "";
	setAttr ".pff" yes;
	setAttr ".prm" -type "string" "";
	setAttr ".pom" -type "string" "";
	setAttr ".currentRenderer" -type "string" "mayaSoftware";
select -ne :defaultRenderQuality;
	setAttr ".mss" 1;
select -ne :defaultResolution;
	setAttr ".h" 320;
	setAttr ".dar" 1;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr ":time1.o" "ChaosWavesFluidShape.cti";
connectAttr "fluidEmitter1.ef" "ChaosWavesFluidShape.eml[0].emfr";
connectAttr "fluidEmitter1.efc" "ChaosWavesFluidShape.fce[0]";
connectAttr ":time1.o" "fluidEmitter1.ct";
connectAttr "ChaosWavesFluidShape.ifl" "fluidEmitter1.full[0]";
connectAttr "ChaosWavesFluidShape.ots" "fluidEmitter1.dt[0]";
connectAttr "ChaosWavesFluidShape.inh" "fluidEmitter1.inh[0]";
connectAttr "ChaosWavesFluidShape.sti" "fluidEmitter1.stt[0]";
connectAttr "ChaosWavesFluidShape.sd[0]" "fluidEmitter1.sd[0]";
connectAttr "fluidShape1SG.msg" "materialInfo1.sg";
connectAttr "ChaosWavesFluidShape.ocl" "fluidShape1SG.vs";
connectAttr "ChaosWavesFluidShape.iog" "fluidShape1SG.dsm" -na;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "fluidShape1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr "fluidShape1SG.pa" ":renderPartition.st" -na;
connectAttr "ChaosWavesFluidShape.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of ChaosWaves.ma
