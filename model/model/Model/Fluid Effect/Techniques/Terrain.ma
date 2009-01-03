//Maya ASCII 4.5 scene
//Name: Terrain.ma
//Last modified: Wed, Jul 24, 2002 10:50:09 AM
requires maya "4.5";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "/usr/alias_cuts/maya_main_irix_r+d/bin/maya.bin";
fileInfo "product" "Maya Unlimited 4.5";
fileInfo "version" "4.5CG";
fileInfo "cutIdentifier" "200207220603";
fileInfo "osv" "IRIX64 6.5 04151556 IP30";
createNode transform -n "directionalLight1";
	setAttr ".t" -type "double3" -2.4927137440454645 12.295935170804627 0.56932864582767273 ;
	setAttr ".r" -type "double3" -72.502756666422485 38.890318714050096 55.030721962660621 ;
createNode directionalLight -n "directionalLightShape1" -p "directionalLight1";
	setAttr -k off ".v";
	setAttr ".cl" -type "float3" 1 0.91620201 0.86800003 ;
createNode transform -n "transform1";
	setAttr ".s" -type "double3" 72.6205848754866 1 72.6205848754866 ;
	setAttr -l on ".sy";
createNode heightField -n "heightField1" -p "transform1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".res" 150;
	setAttr -l on ".hc";
	setAttr ".nts" -type "string" (
		"This scene has a heightfield that is positioned to match a displaced plane. The idea is to provide good feedback on a displaced plane for terrain generation. The same noise texture feeds into both the heightfield and surface displacement. In addition a bumpmap provides for good detail. Look at the shading network of the noise texture in hypershade. By replacing the connections to this noise texture you can easily substitute any other 2D texture. \n"
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
createNode transform -n "directionalLight2";
	setAttr ".t" -type "double3" 0 16.27305779420918 0 ;
	setAttr ".r" -type "double3" -262.3908469217979 87.342990100003036 -268.57292477178743 ;
createNode directionalLight -n "directionalLightShape2" -p "directionalLight2";
	setAttr -k off ".v";
	setAttr ".cl" -type "float3" 0.52100003 0.73327672 1 ;
	setAttr ".in" 0.38839998841285706;
createNode transform -n "environmentFog1";
createNode environmentFog -n "environmentFogShape1" -p "environmentFog1";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".vf" 0;
createNode ambientLight -n "envFogLight" -p "environmentFog1";
	setAttr -k off ".v";
	setAttr ".as" 0;
createNode transform -n "TerrainCam";
	setAttr ".t" -type "double3" 33.164936990442214 3.7980710422162112 33.285968272297346 ;
	setAttr ".r" -type "double3" -18.938352729602336 41.800000000000189 -1.0666187385028445e-15 ;
createNode camera -n "TerrainCamShape" -p "TerrainCam";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 46.664511568119906;
	setAttr ".imn" -type "string" "persp1";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode noise -n "noise1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr ".f" 0;
	setAttr ".fo" 0.0010000000474974513;
	setAttr ".i" yes;
	setAttr ".ail" yes;
	setAttr ".ag" 4.2565999031066895;
	setAttr ".a" 0.58253997564315796;
	setAttr ".ra" 0.53398001194000244;
	setAttr ".dm" 13;
	setAttr ".fq" 3.8859999179840088;
	setAttr ".fr" 1.611799955368042;
	setAttr ".in" yes;
	setAttr ".nty" 0;
	setAttr ".imp" 0.33980000019073486;
	setAttr ".nts" -type "string" (
		"This texture uses inflection along with invert to create a ridged mountain range. The filter settings on the bump map needed to be very low to capture fine detail resulting from the highest frequencies. To capture a range of detail from large peaks to small bumps a depthMax of 13 was needed.\n"
		+ "See the heightfield node for more info.");
createNode place2dTexture -n "place2dTexture1";
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
	setAttr ".bf" 0.33011999726295471;
	setAttr ".bfo" 9.9999997473787516e-05;
	setAttr ".vc2" -type "float3" 9.9999997e-05 9.9999997e-05 0 ;
createNode displacementShader -n "displacementShader1";
createNode materialInfo -n "materialInfo2";
createNode shadingEngine -n "envFogSE";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode envFog -n "envFogMaterial";
	setAttr ".sff" yes;
	setAttr ".ftp" 1;
	setAttr ".fdn" 0.019420000000000003;
	setAttr ".fop" -type "float3" 0.13333334 0.13333334 0.13333334 ;
	setAttr ".fxh" 0.097;
	setAttr ".flc" 0.6602;
	setAttr ".adn" 0.013592;
	setAttr ".acl" -type "float3" 0.37599999 0.63100815 1 ;
	setAttr ".aop" -type "float3" 0.34965599 0.35795057 0.40799999 ;
	setAttr ".axh" 19.42;
	setAttr ".alc" 0.6699;
	setAttr ".sin" 2.6214;
	setAttr ".saz" -26.214;
	setAttr ".sel" 32.33;
createNode lightLinker -n "lightLinker1";
	setAttr ".ihi" 0;
	setAttr -s 4 ".lnk";
select -ne :time1;
	setAttr ".o" 150;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :lightList1;
	setAttr -s 3 ".l";
select -ne :defaultTextureList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".sdf" -type "string" "";
	setAttr ".pfm" -type "string" "";
	setAttr ".top" 231;
	setAttr ".left" 145;
	setAttr ".bot" 188;
	setAttr ".rght" 211;
	setAttr ".an" yes;
	setAttr ".fs" 1;
	setAttr ".ef" 115;
	setAttr ".ofc" 1;
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
select -ne :defaultRenderQuality;
	setAttr ".rfl" 10;
	setAttr ".rfr" 10;
	setAttr ".sl" 10;
	setAttr ".eaa" 0;
	setAttr ".ufil" yes;
	setAttr ".ss" 2;
	setAttr ".rct" 0.20000000298023224;
	setAttr ".gct" 0.15000000596046448;
	setAttr ".bct" 0.30000001192092896;
select -ne :defaultLightSet;
	setAttr -s 2 ".dsm";
connectAttr "noise1.oa" "heightField1.dis";
connectAttr "makeNurbPlane1.os" "nurbsPlaneShape1.cr";
connectAttr "heightField1.res" "nurbsPlaneShape1.nu";
connectAttr "heightField1.res" "nurbsPlaneShape1.nv";
connectAttr "place2dTexture1.o" "noise1.uv";
connectAttr "place2dTexture1.ofs" "noise1.fs";
connectAttr "blinn1SG.msg" "materialInfo1.sg";
connectAttr "blinn1.oc" "blinn1SG.ss";
connectAttr "nurbsPlaneShape1.iog" "blinn1SG.dsm" -na;
connectAttr "displacementShader1.d" "blinn1SG.ds";
connectAttr "bump2d1.o" "blinn1.n";
connectAttr "noise1.oa" "bump2d1.bv";
connectAttr "noise1.oa" "displacementShader1.d";
connectAttr "envFogSE.msg" "materialInfo2.sg";
connectAttr "environmentFogShape1.iog" "envFogSE.dsm" -na;
connectAttr "envFogMaterial.oc" "envFogSE.vs";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "blinn1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr "envFogLight.msg" "lightLinker1.lnk[3].llnk";
connectAttr "envFogSE.msg" "lightLinker1.lnk[3].olnk";
connectAttr "blinn1SG.pa" ":renderPartition.st" -na;
connectAttr "envFogSE.pa" ":renderPartition.st" -na;
connectAttr "blinn1.msg" ":defaultShaderList1.s" -na;
connectAttr "displacementShader1.msg" ":defaultShaderList1.s" -na;
connectAttr "envFogMaterial.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "bump2d1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "heightField1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "directionalLightShape1.ltd" ":lightList1.l" -na;
connectAttr "directionalLightShape2.ltd" ":lightList1.l" -na;
connectAttr "envFogLight.ltd" ":lightList1.l" -na;
connectAttr "noise1.msg" ":defaultTextureList1.tx" -na;
connectAttr "environmentFogShape1.msg" ":defaultRenderGlobals.fg";
connectAttr "directionalLight1.iog" ":defaultLightSet.dsm" -na;
connectAttr "directionalLight2.iog" ":defaultLightSet.dsm" -na;
// End of Terrain.ma
