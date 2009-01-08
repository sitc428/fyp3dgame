//Maya ASCII 4.5 scene
//Name: SunsetClouds.ma
//Last modified: Tue, Jul 23, 2002 12:03:34 PM
requires maya "4.5";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "/usr/alias_cuts/maya_main_irix_r+d/bin/maya.bin";
fileInfo "product" "Maya Unlimited 4.5";
fileInfo "version" "4.5CG";
fileInfo "cutIdentifier" "200207220603";
fileInfo "osv" "IRIX64 6.5 04151556 IP30";
createNode transform -n "cloudLayer";
	setAttr ".t" -type "double3" 0 4.3193967419989026 0 ;
	setAttr ".s" -type "double3" 4.39149377555787 4.39149377555787 4.39149377555787 ;
createNode fluidShape -n "cloudLayerShape" -p "cloudLayer";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".vf" 0;
	setAttr ".csh" no;
	setAttr ".rcsh" no;
	setAttr ".sso" yes;
	setAttr ".vso" yes;
	setAttr ".vss" 4;
	setAttr ".iss" yes;
	setAttr ".rw" 80;
	setAttr ".rh" 4;
	setAttr ".rd" 80;
	setAttr ".dw" 20;
	setAttr ".dh" 1;
	setAttr ".dd" 20;
	setAttr ".bod" 4;
	setAttr ".wdp" 0;
	setAttr ".dmt" 0;
	setAttr ".dgr" 6;
	setAttr ".vmt" 0;
	setAttr ".ss" yes;
	setAttr ".qua" 1.5;
	setAttr ".cl[0].clp" 0;
	setAttr ".cl[0].clc" -type "float3" 1.5 0.39238125 0.19049996 ;
	setAttr ".cl[0].cli" 1;
	setAttr -s 6 ".opa[0:5]"  0.43571427 0.02 1 1 0.94 1 0.478571 0.36000001 
		1 0.59285712 0.60000002 1 0.80000001 0.81999999 1 0.37857142 0 1;
	setAttr ".opi" 2;
	setAttr ".oib" 0.15219999849796295;
	setAttr ".t" -type "float3" 0.149 0.11911309 0.11175001 ;
	setAttr ".shp" 0.82524001598358154;
	setAttr -s 6 ".i";
	setAttr ".i[0].ip" 0.66428571939468384;
	setAttr ".i[0].ic" -type "float3" 0.0042000022 0.026376002 0.105 ;
	setAttr ".i[0].ii" 1;
	setAttr ".i[1].ip" 0.13571429252624512;
	setAttr ".i[1].ic" -type "float3" 0.27222398 0.33097851 0.37599999 ;
	setAttr ".i[1].ii" 1;
	setAttr ".i[3].ip" 0.52857142686843872;
	setAttr ".i[3].ic" -type "float3" 0.035909999 0.048153989 0.07 ;
	setAttr ".i[3].ii" 1;
	setAttr ".i[4].ip" 0.41428571939468384;
	setAttr ".i[4].ic" -type "float3" 0.060755998 0.09743353 0.16599999 ;
	setAttr ".i[4].ii" 1;
	setAttr ".i[5].ip" 0.28571429848670959;
	setAttr ".i[5].ic" -type "float3" 0.104652 0.14033449 0.204 ;
	setAttr ".i[5].ii" 1;
	setAttr ".i[6].ip" 0.79285717010498047;
	setAttr ".i[6].ic" -type "float3" 0 0 0 ;
	setAttr ".i[6].ii" 1;
	setAttr ".ili" 2;
	setAttr ".env[0].envp" 0;
	setAttr ".env[0].envc" -type "float3" 0 0 0 ;
	setAttr ".env[0].envi" 0;
	setAttr ".edr" 0.16505999863147736;
	setAttr ".ctl" 0.019999999552965164;
	setAttr ".rl" no;
	setAttr ".dl" -type "float3" 0.69999999 0.0099999998 0.1 ;
	setAttr ".itx" yes;
	setAttr ".itxg" 0.77667999267578125;
	setAttr ".otx" yes;
	setAttr ".otxg" 1.1261999607086182;
	setAttr ".a" 0.98057997226715088;
	setAttr ".ra" 0.42717999219894409;
	setAttr ".dm" 4;
	setAttr ".fq" 4.1261601448059082;
	setAttr ".fr" 2.2000000476837158;
	setAttr ".in" yes;
	setAttr ".nts" -type "string" (
		"This fluid creates a bank of volumetric cumulus clouds. There are no grids used, just the internal fluid texturing. The single internal light is used, and a textured Y Gradient incandescence helps simulate the blue ambient sky lighting. The effects of atmosphere are handled by a second fluid \"skyFog\", and volumeSamplesOverride is set to 4 to provide better depth integration between the two fluids.\n"
		+ "The general density of clouds can be controlled using the opacity Input bias, and the scale of the clouds with the texture Frequency.\n"
		+ "If one wished to paint the cloud regions then a density grid could be used. Set density to grid and change the opacity input from y gradient to density. Textured clouds will then appear where one paints density.\n"
		+ "The clouds could be animated effectively by keying the textureTime and possibly the texture origin. A SpaceTime noiseType may also provide a better animated effect than Perlin. If one wishes to swirl the clouds animating the coordinate grid will work. To do this set the coordinateMethod to Grid and the density to dynamicGrid. (The density currently needs to be on, although you don't need to define any density) One can then push the coordinates with turbulence, velocity gradients or a dynamic velocity grid.\n"
		+ "This node is slow to render, so one may wish to try rendering in hardware instead. There are no used grids on this node, so increasing the resolution only affects the hardware draw. Simply scale up the resolution (for example 240 16 240) and render in the hardware render buffer window. One may get better hardware results by using an imageplane background and hiding the skyFog node. Note that the hardware self shadowing currently has a fixed light direction and ignores any other lights in the scene. ");
createNode transform -n "fluid2";
	setAttr ".t" -type "double3" 0 12.486356426587321 -1 ;
	setAttr ".s" -type "double3" 6.5062086988273276 6.5062086988273276 6.5062086988273276 ;
	setAttr ".sp" -type "double3" 0 -1.4671968077991464 0 ;
	setAttr ".spt" -type "double3" 0 -10.006390589343384 0 ;
createNode fluidShape -n "skyFog" -p "fluid2";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".vf" 0;
	setAttr ".csh" no;
	setAttr ".rcsh" no;
	setAttr ".vss" 5;
	setAttr ".iss" yes;
	setAttr ".rw" 20;
	setAttr ".rh" 3;
	setAttr ".rd" 20;
	setAttr ".dw" 20;
	setAttr ".dh" 3;
	setAttr ".dd" 20;
	setAttr ".sli" 1;
	setAttr ".bod" 4;
	setAttr ".wdp" 0;
	setAttr ".dmt" 0;
	setAttr ".dgr" 6;
	setAttr ".vmt" 0;
	setAttr ".qua" 0.019999999552965164;
	setAttr ".cl[0].clp" 0;
	setAttr ".cl[0].clc" -type "float3" 0 0 0 ;
	setAttr ".cl[0].cli" 0;
	setAttr -s 4 ".opa[0:3]"  0 0 1 0.83571428 0.31999999 1 1 0 1 0.64285713 
		0.38 1;
	setAttr ".opi" 2;
	setAttr ".oib" -0.043480001389980316;
	setAttr ".t" -type "float3" 0.89411765 0.84313726 0.81960785 ;
	setAttr ".shp" 1;
	setAttr -s 6 ".i";
	setAttr ".i[0].ip" 0.92857140302658081;
	setAttr ".i[0].ic" -type "float3" 0.713 0.16215414 0.049197003 ;
	setAttr ".i[0].ii" 1;
	setAttr ".i[1].ip" 0.44999998807907104;
	setAttr ".i[1].ic" -type "float3" 0.16212 0.18844651 0.28 ;
	setAttr ".i[1].ii" 1;
	setAttr ".i[2].ip" 0;
	setAttr ".i[2].ic" -type "float3" 0.01764 0.035103597 0.147 ;
	setAttr ".i[2].ii" 1;
	setAttr ".i[4].ip" 1;
	setAttr ".i[4].ic" -type "float3" 0.26800001 0.24955155 0.24790001 ;
	setAttr ".i[4].ii" 1;
	setAttr ".i[6].ip" 0.25714287161827087;
	setAttr ".i[6].ic" -type "float3" 0.062663004 0.12439275 0.223 ;
	setAttr ".i[6].ii" 1;
	setAttr ".i[7].ip" 0.69999998807907104;
	setAttr ".i[7].ic" -type "float3" 0.29300001 0.28458485 0.214476 ;
	setAttr ".i[7].ii" 1;
	setAttr ".ili" 2;
	setAttr ".env[0].envp" 0;
	setAttr ".env[0].envc" -type "float3" 0 0 0 ;
	setAttr ".env[0].envi" 0;
	setAttr ".edr" 0.14565999805927277;
	setAttr ".ctl" 0.039999999105930328;
	setAttr ".smpm" 0;
	setAttr ".rl" no;
	setAttr ".dl" -type "float3" 0.5 0.30000001 0.40000001 ;
	setAttr ".a" 0.88349997997283936;
	setAttr ".ra" 0.59223997592926025;
	setAttr ".dm" 4;
	setAttr ".fq" 3.3494400978088379;
	setAttr ".in" yes;
	setAttr ".nts" -type "string" (
		"This simulates a simple atmosphere. The color of the sky comes from this node. The background is black( like outer space ). There is little contrast in this fluid so the quality setting can be very low so that it renders faster.");
createNode transform -n "SunsetCloudsCam";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -30.964221726380938 6.4472317792353744 46.72212357705002 ;
	setAttr ".r" -type "double3" -19.53835272960238 -32.60000000000003 0 ;
createNode camera -n "SunsetCloudsCamShape" -p "SunsetCloudsCam";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 55.456526539512183;
	setAttr ".imn" -type "string" "persp1";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "fluidShape1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode shadingEngine -n "fluidShape3SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lightLinker -n "lightLinker1";
	setAttr ".ihi" 0;
	setAttr -s 5 ".lnk";
select -ne :time1;
	setAttr ".o" 1;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".sdf" -type "string" "";
	setAttr ".pfm" -type "string" "";
	setAttr ".top" 173;
	setAttr ".left" 89;
	setAttr ".bot" 128;
	setAttr ".rght" 174;
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
connectAttr ":time1.o" "cloudLayerShape.cti";
connectAttr "fluidShape1SG.msg" "materialInfo1.sg";
connectAttr "cloudLayerShape.ocl" "fluidShape1SG.vs";
connectAttr "cloudLayerShape.iog" "fluidShape1SG.dsm" -na;
connectAttr "fluidShape3SG.msg" "materialInfo3.sg";
connectAttr "skyFog.ocl" "fluidShape3SG.vs";
connectAttr "skyFog.iog" "fluidShape3SG.dsm" -na;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "fluidShape1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr "fluidShape3SG.msg" "lightLinker1.lnk[4].olnk";
connectAttr "fluidShape1SG.pa" ":renderPartition.st" -na;
connectAttr "fluidShape3SG.pa" ":renderPartition.st" -na;
connectAttr "cloudLayerShape.msg" ":defaultShaderList1.s" -na;
connectAttr "skyFog.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of SunsetClouds.ma