//Maya ASCII 5.0 scene
//Name: OceanNurbPreviewPlane.ma
//Last modified: Wed, Apr 16, 2003 02:12:01 PM
requires maya "5.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 5.0";
fileInfo "version" "5.0";
fileInfo "cutIdentifier" "200304040010";
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
		"Preset Goal:\r\n"
		+ "To create a nurb surface that follows the ocean shape over time. \r\n"
		+ "\r\n"
		+ "Basic Construction:\r\n"
		+ "To accomplish this you must run the script, giving it the resolution of the nurb you want and the ocean shader it is to apply itself to.  The script is called oceanNurbsPreviewPlane.mel.  Put it in your scripts directory, so that it may be sourced when you run the appropriate command. You could also copy and paste it from below and run it in the script editor so maya is familiar with the procedure it contains. Once you have sourced/run the script use the command:\r\n"
		+ "oceanNurbsPreviewPlane 10 10 oceanShader1 ;\r\n"
		+ "This will build a 10*10 nurb surface that conforms to the ocean. You will probably want to scale it up. \r\n"
		+ "The purpose of this surface is to allow intersections with the ocean in order to generate spray from the water contacting a boat or other surface.  You can do this by assigning a paint effects brush such as sprinkle to the intersection curve, or have it emit particles. Edit Nurbs> Intersection will create a curve for you between the new nurb preview plane and some other nurb.\r\n"
		+ "\r\n"
		+ "Finer Points:\r\n"
		+ "You may want to go with a world space curve and not a curve on surface since they tend to be easier to modify. Just create a curve on the boat surface,  you don't need two. This tecnhnique is applied in the presets that have spray coming off of a surface.\r\n"
		+ "\r\n"
		+ "The script:\r\n"
		+ "\r\n"
		+ "global proc oceanNurbsPreviewPlane(int $xres, int $zres, string $oceanShader)\r\n"
		+ "{\r\n"
		+ "\t//string $result[] = `polyPlane -w 1 -h 1 -sx $res -sy $res -ax 0 1 0 -tx 1 -ch 1`;\r\n"
		+ "\tstring $result[] = `nurbsPlane -w 1 -lr 1 -d 1 -u $xres -v $zres -ax 0 1 0 -ch 0`;\r\n"
		+ "\tstring $plane = $result[0];\r\n"
		+ "\tsetAttr -l true ( $plane+\".rotate\");\r\n"
		+ "\tsetAttr -l true ( $plane+\".scaleY\");\r\n"
		+ "\tsetAttr -l true ( $plane+\".translateY\");\r\n"
		+ "\tif( $zres < $xres ){\r\n"
		+ "\t\tsetAttr ($plane+\".scaleZ\") ((float)$zres/(float)$xres);\r\n"
		+ "\t} else {\r\n"
		+ "\t\tsetAttr ($plane+\".scaleX\") ((float)$xres/(float)$zres);\r\n"
		+ "\t}\r\n"
		+ "\r\n"
		+ "\tint $x,$y;\r\n"
		+ "\tint $xSize = $xres+1;\r\n"
		+ "\tint $zSize = $zres+1;\r\n"
		+ "\tint $planeZ, $planeX;\r\n"
		+ "\r\n"
		+ "\tstring $exp = ( \"float $u, $v;\\n\"\r\n"
		+ "\t\t\t//  + $plane + \".rotateX = 0;\\n\"\r\n"
		+ "\t\t\t  + \"float $minx = \" +$plane+ \".scaleX * -0.5 + \" + $plane + \".translateX;\\n\"\r\n"
		+ "\t\t\t  + \"float $maxx = \" +$plane+ \".scaleX *  0.5 + \" + $plane + \".translateX;\\n\"\r\n"
		+ "\t\t\t  + \"float $minz = \" +$plane+ \".scaleZ * -0.5 + \" + $plane + \".translateZ;\\n\"\r\n"
		+ "\t  \t\t  + \"float $maxz = \" +$plane+ \".scaleZ *  0.5 + \" + $plane + \".translateZ;\\n\"\r\n"
		+ "                    + \"float $disp[] = `colorAtPoint -o A -su \"+$xSize+\" -sv \"+$zSize\r\n"
		+ "\t\t\t      +\" -mu $minx -mv $minz -xu $maxx -xv $maxz \"+$oceanShader+\"`;\\n\"\r\n"
		+ "      );\r\n"
		+ "\t// unfold loop and use output connections \r\n"
		+ "\tint $i=0;\r\n"
		+ "\tfor( $x = 0; $x < $xSize; $x++ ){\r\n"
		+ "\t\t// $planeZ = ($zSize - $z - 1) * $xSize;\r\n"
		+ "\t\t$planeX = $x * $zSize;\r\n"
		+ "\t\tfor( $z = 0; $z < $zSize; $z++ ){\r\n"
		+ "\t\t\t$planeZ= $zSize - $z - 1;\r\n"
		+ "\t\t\t// $exp +=  ($plane + \".pnts[\" + ($planeZ + $x) + \"].pnty = $disp[\"+$i+\"];\\n\");\r\n"
		+ "\t\t\t$exp +=  ($plane + \".cv[\" + ($planeX + $planeZ) + \"].yv = $disp[\"+$i+\"];\\n\");\r\n"
		+ "\t\t\t$i++;\r\n"
		+ "\t\t}\r\n"
		+ "\t}\r\n"
		+ "\r\n"
		+ "\texpression -s $exp;\r\n"
		+ "\tselect ($plane+\".cv[0][0]\");\r\n"
		+ "\tselect $plane;\r\n"
		+ "}\r\n"
		+ "\r\n"
		+ "\r\n"
		+ "\r\n");
createNode transform -n "directionalLight1";
	setAttr ".r" -type "double3" -98.858148882505958 42.061561619902029 19.55847015885481 ;
createNode directionalLight -n "directionalLightShape1" -p "directionalLight1";
	addAttr -ci true -sn "milt" -ln "miExportMrLight" -bt "UNKN" -min 0 -max 
		1 -at "bool";
	addAttr -ci true -sn "mils" -ln "miLightShader" -bt "UNKN" -at "message";
	addAttr -ci true -sn "mipe" -ln "miPhotonEmitter" -bt "UNKN" -at "message";
	addAttr -ci true -sn "phot" -ln "emitPhotons" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "eng" -ln "energy" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "engr" -ln "energyR" -bt "UNKN" -dv 8000 -at "float" 
		-p "energy";
	addAttr -ci true -sn "engg" -ln "energyG" -bt "UNKN" -dv 8000 -at "float" 
		-p "energy";
	addAttr -ci true -sn "engb" -ln "energyB" -bt "UNKN" -dv 8000 -at "float" 
		-p "energy";
	addAttr -ci true -sn "exp" -ln "exponent" -bt "UNKN" -dv 2 -at "float";
	addAttr -ci true -sn "cph" -ln "causticPhotons" -bt "UNKN" -dv 10000 -at "long";
	addAttr -ci true -sn "gph" -ln "globIllPhotons" -bt "UNKN" -dv 10000 -at "long";
	addAttr -ci true -sn "phy" -ln "physical" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "usm" -ln "shadowMap" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "smr" -ln "smapResolution" -bt "UNKN" -dv 256 -at "long";
	addAttr -ci true -sn "smsa" -ln "smapSamples" -bt "UNKN" -dv 1 -at "short";
	addAttr -ci true -sn "smso" -ln "smapSoftness" -bt "UNKN" -at "float";
	addAttr -ci true -sn "smf" -ln "smapFilename" -bt "UNKN" -dt "string";
	setAttr -k off ".v";
createNode transform -n "fluid1";
	setAttr ".t" -type "double3" 0 6.5585462355014172 0 ;
	setAttr ".s" -type "double3" 40.52571793131704 40.52571793131704 40.52571793131704 ;
createNode fluidShape -n "fluidShape1" -p "fluid1";
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
	setAttr ".ots" 1;
	setAttr ".dmt" 0;
	setAttr ".vmt" 0;
	setAttr ".qua" 0.0010000000474974513;
	setAttr ".cl[0].clp" 0;
	setAttr ".cl[0].clc" -type "float3" 0 0 0 ;
	setAttr ".cl[0].cli" 1;
	setAttr -s 6 ".opa[0:5]"  0 0 1 0.57857144 0.54000002 
		1 0.84285712 0 1 0.74285716 0.36000001 1 0.17142899 0.5 1 0.31428573 
		0.83999997 1;
	setAttr ".opi" 2;
	setAttr ".t" -type "float3" 0.69803923 0.69803923 0.69803923 ;
	setAttr -s 3 ".i";
	setAttr ".i[0].ip" 0.61428570747375488;
	setAttr ".i[0].ic" -type "float3" 0.65821701 0.69958502 0.70700002 ;
	setAttr ".i[0].ii" 1;
	setAttr ".i[1].ip" 0;
	setAttr ".i[1].ic" -type "float3" 0.37885201 0.43941703 0.48199999 ;
	setAttr ".i[1].ii" 1;
	setAttr ".i[2].ip" 0.34285715222358704;
	setAttr ".i[2].ic" -type "float3" 0.531102 0.59799242 0.61900002 ;
	setAttr ".i[2].ii" 1;
	setAttr ".ili" 2;
	setAttr ".env[0].envp" 0;
	setAttr ".env[0].envc" -type "float3" 0 0 0 ;
	setAttr ".env[0].envi" 1;
	setAttr ".dos" 1;
	setAttr ".edr" 0.038839999586343765;
	setAttr ".smpm" 0;
	setAttr ".rl" no;
createNode transform -n "WhiteCapsCam";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 13.390011960000001 1.5377586700000001 -2.8261140830000002 ;
	setAttr ".r" -type "double3" -8.1383527299999994 101.8 0 ;
createNode camera -n "WhiteCapsCamShape" -p "WhiteCapsCam";
	setAttr -k off ".v" no;
	setAttr ".cap" -type "double2" 1.41732 0.94488000000000005 ;
	setAttr ".coi" 13.384528749999999;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp1_depth";
	setAttr ".man" -type "string" "persp1_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
	setAttr ".col" -type "float3" 0.17345101 0.27217829 0.32300001 ;
createNode makeNurbPlane -n "makeNurbPlane1";
	setAttr ".ax" -type "double3" 0 1 0 ;
	setAttr ".u" 8;
	setAttr ".v" 8;
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "oceanShader1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode oceanShader -n "oceanShader1";
	setAttr ".rfi" 1.3500000238418579;
	setAttr ".dc" 0.49513998627662659;
	setAttr ".wc" -type "float3" 0.2 0.80784315 0.83529413 ;
	setAttr ".tc" 0.28156000375747681;
	setAttr ".trsd" 20;
	setAttr ".ec" 0.16504000127315521;
	setAttr ".spl" 0.44659999012947083;
	setAttr ".rfl" 0.97087997198104858;
	setAttr -s 5 ".env";
	setAttr ".env[0].envp" 0.38571429252624512;
	setAttr ".env[0].envc" -type "float3" 0.010972 0.022776494 0.026000001 ;
	setAttr ".env[0].envi" 2;
	setAttr ".env[1].envp" 0.57142859697341919;
	setAttr ".env[1].envc" -type "float3" 0.73015797 0.82928872 0.85100001 ;
	setAttr ".env[1].envi" 2;
	setAttr ".env[2].envp" 0.75;
	setAttr ".env[2].envc" -type "float3" 0.22545302 0.50518328 0.66900003 ;
	setAttr ".env[2].envi" 2;
	setAttr ".env[3].envp" 0.97857099771499634;
	setAttr ".env[3].envc" -type "float3" 0.089160994 0.31624904 0.54699999 ;
	setAttr ".env[3].envi" 2;
	setAttr ".env[4].envp" 0.092857144773006439;
	setAttr ".env[4].envc" -type "float3" 0.016899999 0.026000001 0.0258453 ;
	setAttr ".env[4].envi" 2;
	setAttr ".wi" -type "float2" 0.69999999 0.30000001 ;
	setAttr ".nf" 12;
	setAttr ".wlx" 40.7760009765625;
	setAttr -s 4 ".wh";
	setAttr ".wh[0:2]" 0 0.05000000074505806 1 0.64999997615814209 
		0.18000000715255737 1 1 0.15999999642372131 1;
	setAttr ".wh[4].whp" 0.05714285746216774;
	setAttr ".wh[4].whfv" 0.14000000059604645;
	setAttr ".wh[4].whi" 1;
	setAttr ".wtb[3]"  0.12142857 1 1;
	setAttr -s 4 ".wp[0:3]"  0 0.28 1 1 0.56 1 0.34285715 
		0.94 1 0.121429 0.81999999 1;
	setAttr ".tsh" 1;
	setAttr ".fc" -type "float3" 1.5 1.5 1.5 ;
	setAttr ".fme" 0.2912600040435791;
	setAttr ".fmt" 0.61500000953674316;
	setAttr ".d" -0.9657256007194519;
	setAttr ".bbl" 0.05000000074505806;
createNode materialInfo -n "materialInfo2";
createNode shadingEngine -n "fluidShape1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lightLinker -n "lightLinker1";
select -ne :time1;
	setAttr ".o" 26;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
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
	setAttr -k on ".mbf";
	setAttr ".currentRenderer" -type "string" "mayaSoftware";
select -ne :defaultLightSet;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "makeNurbPlane1.os" "nurbsPlaneShape1.cr";
connectAttr ":time1.o" "fluidShape1.cti";
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
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "directionalLightShape1.ltd" ":lightList1.l" -na;
connectAttr "directionalLight1.iog" ":defaultLightSet.dsm" -na;
// End of OceanNurbPreviewPlane.ma
