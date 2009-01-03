//Maya ASCII 5.0ff03 scene
//Name: CalmSea.ma
//Last modified: Thu, Jan 09, 2003 11:29:46 AM
requires maya "5.0ff03";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 5.0 Beta";
fileInfo "version" "5.0Beta2";
fileInfo "cutIdentifier" "200301080105";
fileInfo "osv" "Microsoft Windows 2000 Professional Service Pack 3 (Build 2195)\n";
createNode transform -n "nurbsPlane1";
	setAttr ".s" -type "double3" 574.57863598027541 574.57863598027541 574.57863598027541 ;
createNode nurbsSurface -n "nurbsPlaneShape1" -p "nurbsPlane1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".tw" yes;
	setAttr -s 121 ".cp[0:120]" -type "double3" 0.14677356245004036 
		4.1577566360353477e-017 -0.14677356245004036 0.13166760969656849 3.4190198363577702e-017 
		-0.12069530888852098 0.098944563191612989 2.1021535180232667e-017 -0.074208422393709728 
		0.053414235837186408 7.5655107705930314e-018 -0.026707117918593204 0.010632473589959279 
		7.529836587766168e-019 -0.0026581183974898198 0 0 0 0.010632473589959279 
		-7.529836587766168e-019 0.0026581183974898198 0.053414235837186408 -7.5655107705930314e-018 
		0.026707117918593204 0.098944563191612989 -2.1021535180232667e-017 0.074208422393709728 
		0.13166760969656849 -3.4190198363577702e-017 0.12069530888852098 0.14677356245004036 
		-4.1577566360353477e-017 0.14677356245004036 0.12069530888852098 3.7298398214811989e-017 
		-0.13166760969656849 0.22334387636476571 6.3268170954803047e-017 -0.22334387636476571 
		0.20528885641474087 4.7580218233829302e-017 -0.16796360979387873 0.18328848333292425 
		2.8320764504006899e-017 -0.099975536363413248 0.16953425189925797 1.3097766799348588e-017 
		-0.046236614154343061 0.16847234378759496 0 0 0.16953425189925797 -1.3097766799348588e-017 
		0.046236614154343061 0.18328848333292425 -2.8320764504006899e-017 0.099975536363413248 
		0.20528885641474087 -4.7580218233829302e-017 0.16796360979387873 0.22334387636476571 
		-6.3268170954803047e-017 0.22334387636476571 0.12069530888852098 -3.7298398214811989e-017 
		0.13166760969656849 0.074208422393709728 2.802871357364368e-017 -0.098944563191612989 
		0.16796360979387873 5.8153600063569208e-017 -0.20528885641474087 0.25261524985034939 
		7.1560076208310855e-017 -0.25261524985034939 0.2328661834254368 4.3977080671454716e-017 
		-0.15524412228362444 0.21975098660657011 2.0750129373600711e-017 -0.073250328868856712 
		0.21711251513877425 0 0 0.21975098660657011 -2.0750129373600717e-017 0.07325032886885674 
		0.2328661834254368 -4.3977080671454716e-017 0.15524412228362444 0.25261524985034939 
		-7.1560076208310855e-017 0.25261524985034939 0.16796360979387873 -5.8153600063569208e-017 
		0.20528885641474087 0.074208422393709728 -2.802871357364368e-017 0.098944563191612989 
		0.026707117918593204 1.5131021541186063e-017 -0.053414235837186408 0.099975536363413248 
		5.1921401590679278e-017 -0.18328848333292425 0.15524412228362444 6.596562100718207e-017 
		-0.2328661834254368 0.19453643315744718 5.5107686453160644e-017 -0.19453643315744718 
		0.18854460657107269 2.6705170061753666e-017 -0.094272303285536346 0.18509276456554621 
		0 0 0.18854460657107269 -2.6705170061753672e-017 0.094272303285536374 0.19453643315744718 
		-5.5107686453160644e-017 0.19453643315744718 0.15524412228362444 -6.596562100718207e-017 
		0.2328661834254368 0.099975536363413248 -5.1921401590679278e-017 0.18328848333292425 
		0.026707117918593204 -1.5131021541186063e-017 0.053414235837186408 0.0026581183974898198 
		3.0119346351064672e-018 -0.010632473589959279 0.046236614154343061 4.8025144930944805e-017 
		-0.16953425189925797 0.073250328868856712 6.225038812080218e-017 -0.21975098660657011 
		0.094272303285536346 5.3410340123507332e-017 -0.18854460657107269 0.10796038170857056 
		3.0582687098741499e-017 -0.10796038170857056 0.10450853970304411 4.6659014702819536e-034 
		-1.0506676061454628e-018 0.10796038170857056 -3.0582687098741499e-017 0.10796038170857059 
		0.094272303285536346 -5.3410340123507332e-017 0.18854460657107269 0.073250328868856712 
		-6.225038812080218e-017 0.21975098660657011 0.046236614154343061 -4.8025144930944805e-017 
		0.16953425189925797 0.0026581183974898198 -3.0119346351064672e-018 0.010632473589959279 
		0 0 0 0 4.7724330845327099e-017 -0.16847234378759496 0 6.1502969984245581e-017 
		-0.21711251513877425 0 5.2432512865965072e-017 -0.18509276456554621 1.0506676061454628e-018 
		2.9604859841199233e-017 -0.10450853970304411 1.0506676061454628e-018 4.6659014702819536e-034 
		-1.0506676061454628e-018 1.0506676061454628e-018 -2.9604859841199233e-017 
		0.10450853970304413 0 -5.2432512865965072e-017 0.18509276456554621 0 -6.1502969984245581e-017 
		0.21711251513877425 0 -4.7724330845327099e-017 0.16847234378759496 0 0 0 
		-0.0026581183974898198 3.0119346351064672e-018 -0.010632473589959279 -0.046236614154343061 
		4.8025144930944805e-017 -0.16953425189925797 -0.07325032886885674 6.225038812080218e-017 
		-0.21975098660657011 -0.094272303285536374 5.3410340123507332e-017 -0.18854460657107269 
		-0.10796038170857059 3.0582687098741499e-017 -0.10796038170857056 -0.10450853970304413 
		4.6659014702819536e-034 -1.0506676061454628e-018 -0.10796038170857059 -3.0582687098741499e-017 
		0.10796038170857059 -0.094272303285536374 -5.3410340123507332e-017 0.18854460657107269 
		-0.07325032886885674 -6.225038812080218e-017 0.21975098660657011 -0.046236614154343061 
		-4.8025144930944805e-017 0.16953425189925797 -0.0026581183974898198 -3.0119346351064672e-018 
		0.010632473589959279 -0.026707117918593204 1.5131021541186063e-017 -0.053414235837186408 
		-0.099975536363413248 5.1921401590679278e-017 -0.18328848333292425 -0.15524412228362444 
		6.596562100718207e-017 -0.2328661834254368 -0.19453643315744718 5.5107686453160644e-017 
		-0.19453643315744718 -0.18854460657107269 2.6705170061753666e-017 -0.094272303285536346 
		-0.18509276456554621 0 0 -0.18854460657107269 -2.6705170061753672e-017 0.094272303285536374 
		-0.19453643315744718 -5.5107686453160644e-017 0.19453643315744718 -0.15524412228362444 
		-6.596562100718207e-017 0.2328661834254368 -0.099975536363413248 -5.1921401590679278e-017 
		0.18328848333292425 -0.026707117918593204 -1.5131021541186063e-017 0.053414235837186408 
		-0.074208422393709728 2.802871357364368e-017 -0.098944563191612989 -0.16796360979387873 
		5.8153600063569208e-017 -0.20528885641474087 -0.25261524985034939 7.1560076208310855e-017 
		-0.25261524985034939 -0.2328661834254368 4.3977080671454716e-017 -0.15524412228362444 
		-0.21975098660657011 2.0750129373600711e-017 -0.073250328868856712 -0.21711251513877425 
		0 0 -0.21975098660657011 -2.0750129373600717e-017 0.07325032886885674 -0.2328661834254368 
		-4.3977080671454716e-017 0.15524412228362444 -0.25261524985034939 -7.1560076208310855e-017 
		0.25261524985034939 -0.16796360979387873 -5.8153600063569208e-017 0.20528885641474087 
		-0.074208422393709728 -2.802871357364368e-017 0.098944563191612989 -0.12069530888852098 
		3.7298398214811989e-017 -0.13166760969656849 -0.22334387636476571 6.3268170954803047e-017 
		-0.22334387636476571 -0.20528885641474087 4.7580218233829302e-017 -0.16796360979387873 
		-0.18328848333292425 2.8320764504006899e-017 -0.099975536363413248 -0.16953425189925797 
		1.3097766799348588e-017 -0.046236614154343061 -0.16847234378759496 0 0 -0.16953425189925797 
		-1.3097766799348588e-017 0.046236614154343061 -0.18328848333292425 -2.8320764504006899e-017 
		0.099975536363413248 -0.20528885641474087 -4.7580218233829302e-017 0.16796360979387873 
		-0.22334387636476571 -6.3268170954803047e-017 0.22334387636476571 -0.12069530888852098 
		-3.7298398214811989e-017 0.13166760969656849 -0.14677356245004036 4.1577566360353477e-017 
		-0.14677356245004036 -0.13166760969656849 3.4190198363577702e-017 -0.12069530888852098 
		-0.098944563191612989 2.1021535180232667e-017 -0.074208422393709728 -0.053414235837186408 
		7.5655107705930314e-018 -0.026707117918593204 -0.010632473589959279 7.529836587766168e-019 
		-0.0026581183974898198 0 0 0 -0.010632473589959279 -7.529836587766168e-019 
		0.0026581183974898198 -0.053414235837186408 -7.5655107705930314e-018 0.026707117918593204 
		-0.098944563191612989 -2.1021535180232667e-017 0.074208422393709728 -0.13166760969656849 
		-3.4190198363577702e-017 0.12069530888852098 -0.14677356245004036 -4.1577566360353477e-017 
		0.14677356245004036;
	setAttr ".fbda" no;
	setAttr ".dvu" 0;
	setAttr ".dvv" 0;
	setAttr ".cpr" 4;
	setAttr ".cps" 1;
	setAttr ".ucr" no;
	setAttr ".nu" 10;
	setAttr ".nv" 10;
	setAttr ".eta" yes;
	setAttr ".nufa" 4.5;
	setAttr ".nvfa" 4.5;
	setAttr ".nts" -type "string" (
		"This node is used to render the ocean surface. It is designed to concentrate more triangles in the center so that one can can have the ocean extend to the horizon, and yet still see reasonable resolution in the local displacement. The draw overrides have been set to disable interactive shading of this surface, which would slow down playback.For best resolution you may wish to translate this surface so that the center is just in front of the view. Scale it as small as is acceptable, based on the horizon.\r\n"
		+ "The heightfield node oceanPreviewPlane1 has been set up to allow one to interactively preview the ocean at a defined location.\r\n"
		+ "Render time: $");
createNode transform -n "directionalLight1";
	setAttr ".r" -type "double3" -98.858148882505958 42.061561619902029 19.55847015885481 ;
createNode directionalLight -n "directionalLightShape1" -p "directionalLight1";
	setAttr -k off ".v";
createNode transform -n "fluid1";
	setAttr ".t" -type "double3" 0 6.5585462355014172 0 ;
	setAttr ".s" -type "double3" 40.52571793131704 40.52571793131704 40.52571793131704 ;
createNode fluidShape -n "fluidShape1" -p "fluid1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".rt" 1;
	setAttr ".vf" 0;
	setAttr ".iss" yes;
	setAttr ".rw" 30;
	setAttr ".rh" 3;
	setAttr ".rd" 30;
	setAttr ".dw" 20;
	setAttr ".dh" 2;
	setAttr ".dd" 20;
	setAttr ".dmt" 0;
	setAttr ".vmt" 0;
	setAttr ".qua" 0.0010000000474974513;
	setAttr ".cl[0].clp" 0;
	setAttr ".cl[0].clc" -type "float3" 0 0 0 ;
	setAttr ".cl[0].cli" 1;
	setAttr -s 6 ".opa[0:5]"  0 0 1 0.61428571 0.81999999 
		1 0.84285712 0 1 0.74285716 0.36000001 1 0.064285718 0.62 1 0.31428573 
		0.83999997 1;
	setAttr ".opi" 2;
	setAttr ".t" -type "float3" 0.89411765 0.89411765 0.89411765 ;
	setAttr -s 4 ".i";
	setAttr ".i[0].ip" 0.60000002384185791;
	setAttr ".i[0].ic" -type "float3" 0.41279998 0.94350404 1.2 ;
	setAttr ".i[0].ii" 1;
	setAttr ".i[1].ip" 0;
	setAttr ".i[1].ic" -type "float3" 0.036703985 0.29038173 0.59200001 ;
	setAttr ".i[1].ii" 1;
	setAttr ".i[2].ip" 0.22857142984867096;
	setAttr ".i[2].ic" -type "float3" 0.078595988 0.50335461 0.80199999 ;
	setAttr ".i[2].ii" 1;
	setAttr ".i[3].ip" 0.4285714328289032;
	setAttr ".i[3].ic" -type "float3" 0.236 0.72164929 1 ;
	setAttr ".i[3].ii" 1;
	setAttr ".ili" 2;
	setAttr ".env[0].envp" 0;
	setAttr ".env[0].envc" -type "float3" 0 0 0 ;
	setAttr ".env[0].envi" 1;
	setAttr ".dos" 1;
	setAttr ".edr" 0.038839999586343765;
	setAttr ".smpm" 0;
	setAttr ".rl" no;
	setAttr ".nts" -type "string" (
		"This fluid provides the mist above the ocean and creates the effect of a sky.");
createNode transform -n "CalmSeaCam";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 13.390011960000001 1.5377586700000001 -2.8261140830000002 ;
	setAttr ".r" -type "double3" -8.1383527299999994 101.8 0 ;
createNode camera -n "CalmSeaCamShape" -p "CalmSeaCam";
	setAttr -k off ".v" no;
	setAttr ".cap" -type "double2" 1.41732 0.94488000000000005 ;
	setAttr ".coi" 13.384528749999999;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
	setAttr ".col" -type "float3" 0.085631989 0.323535 0.44600001 ;
createNode transform -n "transform1";
	setAttr -l on ".ty";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr ".s" -type "double3" 5 1 5 ;
	setAttr -l on ".sy";
createNode heightField -n "oceanPreviewPlane1" -p "transform1";
	addAttr -ci true -sn "nts" -ln "notes" -dt "string";
	setAttr -k off ".v";
	setAttr ".cl" -type "float3" 0.2 0.5 0.5 ;
	setAttr ".nts" -type "string" (
		"This node is used to preview the ocean's surface. It does not appear in renders.Translate and scale it to preview different parts of the ocean.\r\n"
		+ "One may increase the resolution to better judge the fine details on the surface, or lower it to provide faster playback performance.\r\n");
createNode makeNurbPlane -n "makeNurbPlane1";
	setAttr ".ax" -type "double3" 0 1 0 ;
	setAttr ".u" 8;
	setAttr ".v" 8;
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "oceanShader1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode oceanShader -n "oceanShader1";
	setAttr ".rfi" 1.3300000429153442;
	setAttr ".dc" 0.60193997621536255;
	setAttr ".wc" -type "float3" 0.074509807 0.34509805 0.52549022 ;
	setAttr ".tc" 0.087379999458789825;
	setAttr ".trsd" 20;
	setAttr ".ec" 0.058260001242160797;
	setAttr ".spl" 0.81554001569747925;
	setAttr ".rfl" 0.8737800121307373;
	setAttr -s 5 ".env";
	setAttr ".env[0].envp" 0.38571429252624512;
	setAttr ".env[0].envc" -type "float3" 0.010972 0.022776494 0.026000001 ;
	setAttr ".env[0].envi" 2;
	setAttr ".env[1].envp" 0.52142858505249023;
	setAttr ".env[1].envc" -type "float3" 0.33906099 0.66936159 0.829 ;
	setAttr ".env[1].envi" 2;
	setAttr ".env[2].envp" 0.70714282989501953;
	setAttr ".env[2].envc" -type "float3" 0.34399998 0.67221868 1 ;
	setAttr ".env[2].envi" 2;
	setAttr ".env[3].envp" 1;
	setAttr ".env[3].envc" -type "float3" 0.11993 0.37299028 0.89499998 ;
	setAttr ".env[3].envi" 2;
	setAttr ".env[4].envp" 0.092857144773006439;
	setAttr ".env[4].envc" -type "float3" 0.016899999 0.026000001 0.0258453 ;
	setAttr ".env[4].envi" 2;
	setAttr ".wi" -type "float2" 0.69999999 0.30000001 ;
	setAttr ".wd" 0.59223997592926025;
	setAttr ".nf" 5;
	setAttr ".wlx" 25;
	setAttr -s 3 ".wh";
	setAttr ".wh[0].whfv" 0.05000000074505806;
	setAttr ".wh[0].whi" 1;
	setAttr ".wh[2].whp" 1;
	setAttr ".wh[2].whfv" 0.029999999329447746;
	setAttr ".wh[2].whi" 1;
	setAttr ".wh[4].whp" 0.16428571939468384;
	setAttr ".wh[4].whfv" 0.039999999105930328;
	setAttr ".wh[4].whi" 1;
	setAttr -s 2 ".wtb";
	setAttr ".wtb[3].wtbp" 0.10000000149011612;
	setAttr ".wtb[3].wtbfv" 0.43999999761581421;
	setAttr ".wtb[3].wtbi" 0;
	setAttr ".wtb[5].wtbp" 0.44999998807907104;
	setAttr ".wtb[5].wtbfv" 0;
	setAttr ".wtb[5].wtbi" 0;
	setAttr -s 2 ".wp";
	setAttr ".wp[0].wpfv" 0.31999999284744263;
	setAttr ".wp[0].wpi" 1;
	setAttr ".wp[2].wpp" 0.74285715818405151;
	setAttr ".wp[2].wpfv" 0;
	setAttr ".wp[2].wpi" 1;
	setAttr ".tsh" 0;
	setAttr ".fc" -type "float3" 1.5 1.5 1.5 ;
	setAttr ".fmt" 0;
	setAttr ".d" -0.094124771654605865;
	setAttr ".bbl" 0.30000001192092896;
createNode materialInfo -n "materialInfo2";
createNode shadingEngine -n "fluidShape1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lightLinker -n "lightLinker1";
select -ne :time1;
	setAttr ".o" 169;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
select -ne :lightList1;
select -ne :initialShadingGroup;
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -sn "currentRenderer" -ln "currentRenderer" -dt "string";
	setAttr ".pfm" -type "string" "";
	setAttr ".top" 481;
	setAttr ".rght" 715;
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr ".oft" -type "string" "";
	setAttr -k on ".mbf";
	setAttr ".prm" -type "string" "";
	setAttr ".pom" -type "string" "";
	setAttr ".currentRenderer" -type "string" "mayaSoftware";
select -ne :defaultRenderQuality;
	setAttr ".eaa" 0;
select -ne :defaultResolution;
	setAttr ".w" 720;
	setAttr ".h" 486;
	setAttr ".dar" 1.3329999446868896;
	setAttr ".ldar" yes;
select -ne :defaultLightSet;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "makeNurbPlane1.os" "nurbsPlaneShape1.cr";
connectAttr ":time1.o" "fluidShape1.cti";
connectAttr "oceanShader1.d" "oceanPreviewPlane1.dis";
connectAttr "oceanShader1SG.msg" "materialInfo1.sg";
connectAttr "oceanShader1.oc" "oceanShader1SG.ss";
connectAttr "oceanShader1.d" "oceanShader1SG.ds";
connectAttr "nurbsPlaneShape1.iog" "oceanShader1SG.dsm" -na;
connectAttr ":time1.o" "oceanShader1.ti";
connectAttr "fluidShape1SG.msg" "materialInfo2.sg";
connectAttr "fluidShape1.ocl" "fluidShape1SG.vs";
connectAttr "fluidShape1.iog" "fluidShape1SG.dsm" -na;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "oceanShader1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr "fluidShape1SG.msg" "lightLinker1.lnk[3].olnk";
connectAttr "oceanShader1SG.pa" ":renderPartition.st" -na;
connectAttr "fluidShape1SG.pa" ":renderPartition.st" -na;
connectAttr "oceanShader1.msg" ":defaultShaderList1.s" -na;
connectAttr "fluidShape1.msg" ":defaultShaderList1.s" -na;
connectAttr "oceanPreviewPlane1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "directionalLightShape1.ltd" ":lightList1.l" -na;
connectAttr "directionalLight1.iog" ":defaultLightSet.dsm" -na;
// End of CalmSea.ma
