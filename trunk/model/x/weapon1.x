xof 0302txt 0032
Header {
 1;
 0;
 1;
}
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}
template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}
Frame jyu00 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh jyu001 {
 264;
0.101086;0.005320;0.006941;,
0.101089;0.005320;0.006932;,
0.101071;0.005320;0.006928;,
0.101075;0.005320;0.006947;,
0.101039;0.005320;0.006934;,
0.101037;0.005320;0.006955;,
0.101003;0.005320;0.006944;,
0.101006;0.005320;0.006963;,
0.100969;0.005320;0.006957;,
0.100977;0.005320;0.006974;,
0.100956;0.005320;0.006984;,
0.100942;0.005320;0.006972;,
0.100935;0.005320;0.007000;,
0.100922;0.005320;0.006987;,
0.100908;0.005320;0.007014;,
0.100925;0.005320;0.007017;,
0.100910;0.005320;0.007045;,
0.100926;0.005320;0.007039;,
0.100929;0.005320;0.007076;,
0.100944;0.005320;0.007066;,
0.100955;0.005320;0.007097;,
0.100959;0.005320;0.007079;,
0.100980;0.005320;0.007091;,
0.100983;0.005320;0.007112;,
0.101014;0.005320;0.007107;,
0.101002;0.005320;0.007121;,
0.101036;0.005320;0.007133;,
0.101038;0.005320;0.007116;,
0.101111;0.005320;0.007071;,
0.101103;0.005320;0.007067;,
0.101093;0.005320;0.007079;,
0.101099;0.005320;0.007097;,
0.101087;0.005320;0.007058;,
0.101079;0.005320;0.007053;,
0.101066;0.005320;0.007067;,
0.101073;0.005320;0.007143;,
0.101067;0.005320;0.007127;,
0.101080;0.005320;0.007134;,
0.101051;0.005320;0.007122;,
0.101057;0.005320;0.007083;,
0.100834;0.005320;0.007132;,
0.100819;0.005320;0.007131;,
0.100822;0.005320;0.007145;,
0.100717;0.005320;0.007019;,
0.100710;0.005320;0.007005;,
0.100700;0.005320;0.007013;,
0.100836;0.005320;0.007145;,
0.100722;0.005320;0.007000;,
0.100729;0.005320;0.007014;,
0.100828;0.005320;0.007106;,
0.100799;0.005320;0.007008;,
0.100805;0.005320;0.006995;,
0.100794;0.005320;0.006988;,
0.100784;0.005320;0.006998;,
0.100775;0.005320;0.007013;,
0.100787;0.005320;0.007027;,
0.100710;0.005320;0.007024;,
0.100690;0.005320;0.007026;,
0.100702;0.005320;0.007039;,
0.100686;0.005320;0.007038;,
0.100683;0.005320;0.007052;,
0.100755;0.005320;0.007000;,
0.100752;0.005320;0.007017;,
0.100767;0.005320;0.007027;,
0.100701;0.005320;0.007063;,
0.100692;0.005320;0.007086;,
0.100815;0.005320;0.007115;,
0.100807;0.005320;0.007091;,
0.100819;0.005320;0.007082;,
0.100793;0.005320;0.007063;,
0.100801;0.005320;0.007048;,
0.100778;0.005320;0.007040;,
0.100871;0.005320;0.006982;,
0.100862;0.005320;0.006981;,
0.100859;0.005320;0.006987;,
0.100709;0.005320;0.007085;,
0.100716;0.005320;0.007121;,
0.100724;0.005320;0.007105;,
0.100862;0.005320;0.006996;,
0.100902;0.005320;0.007019;,
0.100889;0.005320;0.007030;,
0.100695;0.005320;0.007172;,
0.100695;0.005320;0.007183;,
0.100700;0.005320;0.007185;,
0.100712;0.005320;0.007174;,
0.100702;0.005320;0.007152;,
0.100730;0.005320;0.007134;,
0.100823;0.005320;0.007199;,
0.100830;0.005320;0.007202;,
0.100836;0.005320;0.007198;,
0.100839;0.005320;0.007180;,
0.100822;0.005320;0.007168;,
0.100838;0.005320;0.007161;,
0.100895;0.005320;0.007050;,
0.100908;0.005320;0.007100;,
0.100892;0.005320;0.007094;,
0.100878;0.005320;0.007122;,
0.100890;0.005320;0.007134;,
0.100863;0.005320;0.007135;,
0.100864;0.005320;0.007153;,
0.100822;0.005320;0.007163;,
0.100783;0.005320;0.007158;,
0.100785;0.005320;0.007141;,
0.100738;0.005320;0.007118;,
0.101719;-0.002100;0.003552;,
0.093319;0.002100;0.003552;,
0.093319;-0.002100;0.003552;,
0.101719;0.002100;0.003552;,
0.093319;-0.002100;0.003552;,
0.090586;0.002100;-0.004397;,
0.090586;-0.002100;-0.004397;,
0.093319;0.002100;0.003552;,
0.087859;0.002100;-0.006388;,
0.087859;-0.002100;-0.006388;,
0.087859;-0.002100;-0.006388;,
0.055939;0.002100;-0.005268;,
0.055939;-0.002100;-0.005268;,
0.087859;0.002100;-0.006388;,
0.042219;0.002100;-0.006948;,
0.042219;-0.002100;-0.006948;,
0.031299;0.002100;-0.011148;,
0.031299;-0.002100;-0.011148;,
0.031299;-0.002100;-0.011148;,
0.032979;0.002100;-0.015068;,
0.032979;-0.002100;-0.015068;,
0.031299;0.002100;-0.011148;,
0.032979;-0.002100;-0.015068;,
0.046139;0.002100;-0.012828;,
0.046139;-0.002100;-0.012828;,
0.032979;0.002100;-0.015068;,
0.056219;0.002100;-0.012548;,
0.056219;-0.002100;-0.012548;,
0.091499;0.002100;-0.015068;,
0.091499;-0.002100;-0.015068;,
0.091499;-0.002100;-0.015068;,
0.096259;0.002100;-0.010868;,
0.096259;-0.002100;-0.010868;,
0.091499;0.002100;-0.015068;,
0.101719;0.002100;0.003552;,
0.101719;-0.002100;0.003552;,
0.042219;0.002100;-0.006948;,
0.032979;0.002100;-0.015068;,
0.031299;0.002100;-0.011148;,
0.046139;0.002100;-0.012828;,
0.055939;0.002100;-0.005268;,
0.056219;0.002100;-0.012548;,
0.091499;0.002100;-0.015068;,
0.087859;0.002100;-0.006388;,
0.090586;0.002100;-0.004397;,
0.096259;0.002100;-0.010868;,
0.093319;0.002100;0.003552;,
0.101719;0.002100;0.003552;,
0.093319;-0.002100;0.003552;,
0.096259;-0.002100;-0.010868;,
0.101719;-0.002100;0.003552;,
0.091499;-0.002100;-0.015068;,
0.090586;-0.002100;-0.004397;,
0.087859;-0.002100;-0.006388;,
0.056219;-0.002100;-0.012548;,
0.055939;-0.002100;-0.005268;,
0.046139;-0.002100;-0.012828;,
0.042219;-0.002100;-0.006948;,
0.032979;-0.002100;-0.015068;,
0.031299;-0.002100;-0.011148;,
0.192523;-0.004628;-0.000965;,
0.099843;-0.009257;0.007052;,
0.099843;-0.004628;-0.000965;,
0.192523;-0.009257;0.007052;,
0.192523;-0.009257;0.007052;,
0.099843;-0.004628;0.015068;,
0.099843;-0.009257;0.007052;,
0.192523;-0.004628;0.015068;,
0.192523;-0.004628;0.015068;,
0.099843;0.004628;0.015068;,
0.099843;-0.004628;0.015068;,
0.192523;0.004628;0.015068;,
0.192523;0.004628;0.015068;,
0.099843;0.009257;0.007052;,
0.099843;0.004628;0.015068;,
0.192523;0.009257;0.007052;,
0.192523;0.009257;0.007052;,
0.099843;0.004628;-0.000965;,
0.099843;0.009257;0.007052;,
0.192523;0.004628;-0.000965;,
0.192523;0.004628;-0.000965;,
0.099843;-0.004628;-0.000965;,
0.099843;0.004628;-0.000965;,
0.192523;-0.004628;-0.000965;,
0.099843;0.009257;0.007052;,
0.099843;-0.004628;0.015068;,
0.099843;0.004628;0.015068;,
0.099843;-0.009257;0.007052;,
0.099843;0.004628;-0.000965;,
0.099843;-0.004628;-0.000965;,
0.192523;-0.009257;0.007052;,
0.192523;0.004628;0.015068;,
0.192523;-0.004628;0.015068;,
0.192523;0.009257;0.007052;,
0.192523;-0.004628;-0.000965;,
0.192523;0.004628;-0.000965;,
0.100683;-0.002660;0.002444;,
-0.202557;-0.005320;0.007052;,
-0.202557;-0.002660;0.002444;,
0.100683;-0.005320;0.007052;,
0.100683;-0.005320;0.007052;,
-0.202557;-0.002660;0.011659;,
-0.202557;-0.005320;0.007052;,
0.100683;-0.002660;0.011659;,
0.100683;-0.002660;0.011659;,
-0.202557;0.002660;0.011659;,
-0.202557;-0.002660;0.011659;,
0.100683;0.002660;0.011659;,
0.100683;0.002660;0.011659;,
-0.202557;0.005320;0.007052;,
-0.202557;0.002660;0.011659;,
-0.202557;0.002660;0.002444;,
-0.202557;0.005320;0.007052;,
0.100683;0.002660;0.002444;,
0.100683;0.002660;0.002444;,
-0.202557;-0.002660;0.002444;,
-0.202557;0.002660;0.002444;,
0.100683;-0.002660;0.002444;,
-0.202557;-0.005320;0.007052;,
-0.202557;0.002660;0.002444;,
-0.202557;-0.002660;0.002444;,
-0.202557;0.005320;0.007052;,
-0.202557;-0.002660;0.011659;,
-0.202557;0.002660;0.011659;,
0.100683;-0.002660;0.002444;,
0.100683;0.002660;0.002444;,
0.100683;-0.005320;0.007052;,
0.100683;0.005320;0.007052;,
0.100683;-0.002660;0.011659;,
0.100683;0.002660;0.011659;,
0.202557;-0.003564;0.000879;,
0.189993;-0.007128;0.007052;,
0.189993;-0.003564;0.000879;,
0.202557;-0.007128;0.007052;,
0.202557;-0.007128;0.007052;,
0.189993;-0.003564;0.013224;,
0.189993;-0.007128;0.007052;,
0.202557;-0.003564;0.013224;,
0.202557;-0.003564;0.013224;,
0.189993;0.003564;0.013224;,
0.189993;-0.003564;0.013224;,
0.202557;0.003564;0.013224;,
0.202557;0.003564;0.013224;,
0.189993;0.007128;0.007052;,
0.189993;0.003564;0.013224;,
0.202557;0.007128;0.007052;,
0.202557;0.007128;0.007052;,
0.189993;0.003564;0.000879;,
0.189993;0.007128;0.007052;,
0.202557;0.003564;0.000879;,
0.202557;0.003564;0.000879;,
0.189993;-0.003564;0.000879;,
0.189993;0.003564;0.000879;,
0.202557;-0.003564;0.000879;,
0.202557;-0.007128;0.007052;,
0.202557;0.003564;0.013224;,
0.202557;-0.003564;0.013224;,
0.202557;0.007128;0.007052;,
0.202557;-0.003564;0.000879;,
0.202557;0.003564;0.000879;;

 205;
3;2,1,0;,
3;2,0,3;,
3;4,2,3;,
3;4,3,5;,
3;6,4,5;,
3;6,5,7;,
3;8,6,7;,
3;8,7,9;,
3;8,9,10;,
3;11,8,10;,
3;11,10,12;,
3;13,11,12;,
3;14,13,12;,
3;14,12,15;,
3;16,14,15;,
3;16,15,17;,
3;18,16,17;,
3;18,17,19;,
3;20,18,19;,
3;20,19,21;,
3;20,21,22;,
3;23,20,22;,
3;23,22,24;,
3;25,23,24;,
3;26,25,24;,
3;26,24,27;,
3;30,29,28;,
3;30,28,31;,
3;34,33,32;,
3;35,26,27;,
3;36,30,31;,
3;36,31,37;,
3;36,37,35;,
3;38,36,35;,
3;34,32,38;,
3;38,35,27;,
3;39,34,38;,
3;27,39,38;,
3;42,41,40;,
3;45,44,43;,
3;42,40,46;,
3;43,44,47;,
3;48,43,47;,
3;49,40,41;,
3;52,51,50;,
3;53,52,50;,
3;54,53,50;,
3;54,50,55;,
3;45,43,56;,
3;57,45,56;,
3;57,56,58;,
3;59,57,58;,
3;60,59,58;,
3;48,47,61;,
3;62,48,61;,
3;62,61,54;,
3;63,62,54;,
3;63,54,55;,
3;60,58,64;,
3;65,60,64;,
3;49,41,66;,
3;49,66,67;,
3;68,49,67;,
3;68,67,69;,
3;70,68,69;,
3;70,69,71;,
3;55,70,71;,
3;74,73,72;,
3;65,64,75;,
3;76,65,75;,
3;76,75,77;,
3;78,74,72;,
3;78,72,79;,
3;80,78,79;,
3;80,79,16;,
3;83,82,81;,
3;84,83,81;,
3;84,81,85;,
3;86,84,85;,
3;86,85,76;,
3;86,76,77;,
3;89,88,87;,
3;90,89,87;,
3;90,87,91;,
3;92,90,91;,
3;93,80,16;,
3;93,16,94;,
3;95,93,94;,
3;96,95,94;,
3;96,94,97;,
3;98,96,97;,
3;98,97,99;,
3;46,98,99;,
3;46,99,92;,
3;42,46,92;,
3;92,91,100;,
3;42,92,100;,
3;42,100,101;,
3;102,42,101;,
3;102,101,86;,
3;103,102,86;,
3;103,86,77;,
3;63,55,71;,
3;77,63,71;,
3;71,103,77;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;113,112,110;,
3;112,109,110;,
3;116,115,114;,
3;115,117,114;,
3;119,118,116;,
3;118,115,116;,
3;121,120,119;,
3;120,118,119;,
3;124,123,122;,
3;123,125,122;,
3;128,127,126;,
3;127,129,126;,
3;131,130,128;,
3;130,127,128;,
3;133,132,131;,
3;132,130,131;,
3;136,135,134;,
3;135,137,134;,
3;139,138,136;,
3;138,135,136;,
3;142,141,140;,
3;143,140,141;,
3;140,143,144;,
3;143,145,144;,
3;146,144,145;,
3;146,147,144;,
3;147,146,148;,
3;149,148,146;,
3;149,150,148;,
3;150,149,151;,
3;154,153,152;,
3;155,152,153;,
3;152,155,156;,
3;156,155,157;,
3;158,157,155;,
3;157,158,159;,
3;160,159,158;,
3;159,160,161;,
3;162,161,160;,
3;161,162,163;,
3;166,165,164;,
3;165,167,164;,
3;170,169,168;,
3;169,171,168;,
3;174,173,172;,
3;173,175,172;,
3;178,177,176;,
3;177,179,176;,
3;182,181,180;,
3;181,183,180;,
3;186,185,184;,
3;185,187,184;,
3;190,189,188;,
3;189,191,188;,
3;188,191,192;,
3;192,191,193;,
3;196,195,194;,
3;195,197,194;,
3;194,197,198;,
3;198,197,199;,
3;202,201,200;,
3;201,203,200;,
3;206,205,204;,
3;205,207,204;,
3;210,209,208;,
3;209,211,208;,
3;214,213,212;,
3;213,60,212;,
3;216,215,60;,
3;215,217,60;,
3;220,219,218;,
3;219,221,218;,
3;224,223,222;,
3;225,222,223;,
3;222,225,226;,
3;226,225,227;,
3;230,229,228;,
3;229,230,231;,
3;232,231,230;,
3;231,232,233;,
3;236,235,234;,
3;235,237,234;,
3;240,239,238;,
3;239,241,238;,
3;244,243,242;,
3;243,245,242;,
3;248,247,246;,
3;247,249,246;,
3;252,251,250;,
3;251,253,250;,
3;256,255,254;,
3;255,257,254;,
3;260,259,258;,
3;259,261,258;,
3;258,261,262;,
3;262,261,263;;
MeshMaterialList {
 1;
 205;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
Material Default {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 264;
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-0.996037;0.088936;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.945667;0.000000;-0.325136;,
0.862161;0.000000;-0.506634;,
0.738449;0.000000;-0.674309;,
0.945667;0.000000;-0.325136;,
0.589667;0.000000;-0.807646;,
0.589667;0.000000;-0.807646;,
-0.035066;0.000000;-0.999385;,
0.017183;0.000000;-0.999852;,
0.069529;0.000000;-0.997580;,
-0.035066;0.000000;-0.999385;,
0.202036;0.000000;-0.979378;,
0.281714;0.000000;-0.959498;,
0.358979;0.000000;-0.933346;,
0.358979;0.000000;-0.933346;,
0.919145;0.000000;0.393920;,
0.919145;0.000000;0.393920;,
0.919145;0.000000;0.393920;,
0.919145;0.000000;0.393920;,
-0.167799;0.000000;0.985821;,
-0.121389;0.000000;0.992605;,
-0.074609;0.000000;0.997213;,
-0.167799;0.000000;0.985821;,
0.005243;0.000000;0.999986;,
0.038284;0.000000;0.999267;,
0.071247;0.000000;0.997459;,
0.071247;0.000000;0.997459;,
-0.661622;0.000000;0.749838;,
-0.772957;0.000000;0.634459;,
-0.866591;0.000000;0.499020;,
-0.661622;0.000000;0.749838;,
-0.935205;0.000000;0.354107;,
-0.935205;0.000000;0.354107;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;0.866008;0.500031;,
0.000000;0.866008;0.500031;,
0.000000;0.866008;0.500031;,
0.000000;0.866008;0.500031;,
0.000000;0.865981;-0.500078;,
0.000000;0.865981;-0.500078;,
0.000000;0.865981;-0.500078;,
0.000000;0.865981;-0.500078;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;-0.865981;-0.500078;,
0.000000;-0.865981;-0.500078;,
0.000000;-0.865981;-0.500078;,
0.000000;-0.865981;-0.500078;,
0.000000;-0.866008;0.500031;,
0.000000;-0.866008;0.500031;,
0.000000;-0.866008;0.500031;,
0.000000;-0.866008;0.500031;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;0.866060;0.499939;,
0.000000;0.866060;0.499939;,
0.000000;0.866060;0.499939;,
0.000000;0.866060;0.499939;,
0.000000;0.866013;-0.500021;,
0.000000;0.866013;-0.500021;,
0.000000;0.866013;-0.500021;,
0.000000;0.866013;-0.500021;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;-0.866013;-0.500021;,
0.000000;-0.866013;-0.500021;,
0.000000;-0.866013;-0.500021;,
0.000000;-0.866060;0.499939;,
0.000000;-0.866060;0.499939;,
0.000000;-0.866060;0.499939;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;0.866024;0.500002;,
0.000000;0.866024;0.500002;,
0.000000;0.866024;0.500002;,
0.000000;0.866024;0.500002;,
0.000000;0.865989;-0.500063;,
0.000000;0.865989;-0.500063;,
0.000000;0.865989;-0.500063;,
0.000000;0.865989;-0.500063;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;-0.865989;-0.500063;,
0.000000;-0.865989;-0.500063;,
0.000000;-0.865989;-0.500063;,
0.000000;-0.865989;-0.500063;,
0.000000;-0.866024;0.500002;,
0.000000;-0.866024;0.500002;,
0.000000;-0.866024;0.500002;,
0.000000;-0.866024;0.500002;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;;

 205;
3;2,1,0;,
3;2,0,3;,
3;4,2,3;,
3;4,3,5;,
3;6,4,5;,
3;6,5,7;,
3;8,6,7;,
3;8,7,9;,
3;8,9,10;,
3;11,8,10;,
3;11,10,12;,
3;13,11,12;,
3;14,13,12;,
3;14,12,15;,
3;16,14,15;,
3;16,15,17;,
3;18,16,17;,
3;18,17,19;,
3;20,18,19;,
3;20,19,21;,
3;20,21,22;,
3;23,20,22;,
3;23,22,24;,
3;25,23,24;,
3;26,25,24;,
3;26,24,27;,
3;30,29,28;,
3;30,28,31;,
3;34,33,32;,
3;35,26,27;,
3;36,30,31;,
3;36,31,37;,
3;36,37,35;,
3;38,36,35;,
3;34,32,38;,
3;38,35,27;,
3;39,34,38;,
3;27,39,38;,
3;42,41,40;,
3;45,44,43;,
3;42,40,46;,
3;43,44,47;,
3;48,43,47;,
3;49,40,41;,
3;52,51,50;,
3;53,52,50;,
3;54,53,50;,
3;54,50,55;,
3;45,43,56;,
3;57,45,56;,
3;57,56,58;,
3;59,57,58;,
3;60,59,58;,
3;48,47,61;,
3;62,48,61;,
3;62,61,54;,
3;63,62,54;,
3;63,54,55;,
3;60,58,64;,
3;65,60,64;,
3;49,41,66;,
3;49,66,67;,
3;68,49,67;,
3;68,67,69;,
3;70,68,69;,
3;70,69,71;,
3;55,70,71;,
3;74,73,72;,
3;65,64,75;,
3;76,65,75;,
3;76,75,77;,
3;78,74,72;,
3;78,72,79;,
3;80,78,79;,
3;80,79,16;,
3;83,82,81;,
3;84,83,81;,
3;84,81,85;,
3;86,84,85;,
3;86,85,76;,
3;86,76,77;,
3;89,88,87;,
3;90,89,87;,
3;90,87,91;,
3;92,90,91;,
3;93,80,16;,
3;93,16,94;,
3;95,93,94;,
3;96,95,94;,
3;96,94,97;,
3;98,96,97;,
3;98,97,99;,
3;46,98,99;,
3;46,99,92;,
3;42,46,92;,
3;92,91,100;,
3;42,92,100;,
3;42,100,101;,
3;102,42,101;,
3;102,101,86;,
3;103,102,86;,
3;103,86,77;,
3;63,55,71;,
3;77,63,71;,
3;71,103,77;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;113,112,110;,
3;112,109,110;,
3;116,115,114;,
3;115,117,114;,
3;119,118,116;,
3;118,115,116;,
3;121,120,119;,
3;120,118,119;,
3;124,123,122;,
3;123,125,122;,
3;128,127,126;,
3;127,129,126;,
3;131,130,128;,
3;130,127,128;,
3;133,132,131;,
3;132,130,131;,
3;136,135,134;,
3;135,137,134;,
3;139,138,136;,
3;138,135,136;,
3;142,141,140;,
3;143,140,141;,
3;140,143,144;,
3;143,145,144;,
3;146,144,145;,
3;146,147,144;,
3;147,146,148;,
3;149,148,146;,
3;149,150,148;,
3;150,149,151;,
3;154,153,152;,
3;155,152,153;,
3;152,155,156;,
3;156,155,157;,
3;158,157,155;,
3;157,158,159;,
3;160,159,158;,
3;159,160,161;,
3;162,161,160;,
3;161,162,163;,
3;166,165,164;,
3;165,167,164;,
3;170,169,168;,
3;169,171,168;,
3;174,173,172;,
3;173,175,172;,
3;178,177,176;,
3;177,179,176;,
3;182,181,180;,
3;181,183,180;,
3;186,185,184;,
3;185,187,184;,
3;190,189,188;,
3;189,191,188;,
3;188,191,192;,
3;192,191,193;,
3;196,195,194;,
3;195,197,194;,
3;194,197,198;,
3;198,197,199;,
3;202,201,200;,
3;201,203,200;,
3;206,205,204;,
3;205,207,204;,
3;210,209,208;,
3;209,211,208;,
3;214,213,212;,
3;213,60,212;,
3;216,215,60;,
3;215,217,60;,
3;220,219,218;,
3;219,221,218;,
3;224,223,222;,
3;225,222,223;,
3;222,225,226;,
3;226,225,227;,
3;230,229,228;,
3;229,230,231;,
3;232,231,230;,
3;231,232,233;,
3;236,235,234;,
3;235,237,234;,
3;240,239,238;,
3;239,241,238;,
3;244,243,242;,
3;243,245,242;,
3;248,247,246;,
3;247,249,246;,
3;252,251,250;,
3;251,253,250;,
3;256,255,254;,
3;255,257,254;,
3;260,259,258;,
3;259,261,258;,
3;258,261,262;,
3;262,261,263;;
 }
}
 }
