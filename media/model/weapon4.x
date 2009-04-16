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
Frame root {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,-0.000000,-1.000000,0.000000,
0.000000,1.000000,-0.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Frame yaa00 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,-0.000000,1.000000,0.000000,
0.000000,-1.000000,-0.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh yaa002 {
 286;
0.363858;0.000000;-0.000030;,
0.363859;0.000000;-0.000033;,
0.363854;0.000000;-0.000034;,
0.363855;0.000000;-0.000029;,
0.363845;0.000000;-0.000032;,
0.363844;0.000000;-0.000027;,
0.363835;0.000000;-0.000030;,
0.363836;0.000000;-0.000024;,
0.363825;0.000000;-0.000026;,
0.363827;0.000000;-0.000021;,
0.363822;0.000000;-0.000018;,
0.363817;0.000000;-0.000022;,
0.363816;0.000000;-0.000014;,
0.363812;0.000000;-0.000017;,
0.363808;0.000000;-0.000010;,
0.363813;0.000000;-0.000009;,
0.363809;0.000000;-0.000001;,
0.363813;0.000000;-0.000003;,
0.363814;0.000000;0.000007;,
0.363818;0.000000;0.000004;,
0.363821;0.000000;0.000013;,
0.363822;0.000000;0.000008;,
0.363828;0.000000;0.000011;,
0.363829;0.000000;0.000017;,
0.363838;0.000000;0.000016;,
0.363834;0.000000;0.000020;,
0.363844;0.000000;0.000023;,
0.363844;0.000000;0.000019;,
0.363865;0.000000;0.000006;,
0.363863;0.000000;0.000005;,
0.363860;0.000000;0.000008;,
0.363861;0.000000;0.000013;,
0.363858;0.000000;0.000002;,
0.363856;0.000000;0.000001;,
0.363852;0.000000;0.000005;,
0.363854;0.000000;0.000026;,
0.363852;0.000000;0.000022;,
0.363856;0.000000;0.000023;,
0.363848;0.000000;0.000020;,
0.363850;0.000000;0.000009;,
0.363787;0.000000;0.000023;,
0.363783;0.000000;0.000023;,
0.363784;0.000000;0.000027;,
0.363755;0.000000;-0.000009;,
0.363753;0.000000;-0.000013;,
0.363750;0.000000;-0.000010;,
0.363788;0.000000;0.000026;,
0.363756;0.000000;-0.000014;,
0.363758;0.000000;-0.000010;,
0.363786;0.000000;0.000016;,
0.363778;0.000000;-0.000012;,
0.363779;0.000000;-0.000015;,
0.363776;0.000000;-0.000017;,
0.363773;0.000000;-0.000015;,
0.363771;0.000000;-0.000010;,
0.363774;0.000000;-0.000006;,
0.363753;0.000000;-0.000007;,
0.363747;0.000000;-0.000007;,
0.363750;0.000000;-0.000003;,
0.363746;0.000000;-0.000003;,
0.363745;0.000000;0.000000;,
0.363765;0.000000;-0.000014;,
0.363765;0.000000;-0.000009;,
0.363769;0.000000;-0.000006;,
0.363750;0.000000;0.000004;,
0.363748;0.000000;0.000010;,
0.363782;0.000000;0.000018;,
0.363780;0.000000;0.000011;,
0.363783;0.000000;0.000009;,
0.363776;0.000000;0.000003;,
0.363778;0.000000;0.000000;,
0.363772;0.000000;-0.000003;,
0.363798;0.000000;-0.000019;,
0.363795;0.000000;-0.000019;,
0.363794;0.000000;-0.000018;,
0.363752;0.000000;0.000010;,
0.363755;0.000000;0.000020;,
0.363757;0.000000;0.000015;,
0.363795;0.000000;-0.000015;,
0.363807;0.000000;-0.000009;,
0.363803;0.000000;-0.000006;,
0.363749;0.000000;0.000034;,
0.363749;0.000000;0.000037;,
0.363750;0.000000;0.000038;,
0.363753;0.000000;0.000035;,
0.363751;0.000000;0.000029;,
0.363758;0.000000;0.000023;,
0.363784;0.000000;0.000042;,
0.363786;0.000000;0.000042;,
0.363788;0.000000;0.000041;,
0.363789;0.000000;0.000036;,
0.363784;0.000000;0.000033;,
0.363789;0.000000;0.000031;,
0.363804;0.000000;0.000000;,
0.363808;0.000000;0.000014;,
0.363804;0.000000;0.000012;,
0.363800;0.000000;0.000020;,
0.363803;0.000000;0.000023;,
0.363795;0.000000;0.000024;,
0.363796;0.000000;0.000029;,
0.363784;0.000000;0.000031;,
0.363773;0.000000;0.000030;,
0.363774;0.000000;0.000025;,
0.363761;0.000000;0.000019;,
0.595010;-0.004123;0.004123;,
0.595010;-0.001000;0.005416;,
0.575000;-0.004123;0.004123;,
0.589000;-0.001000;0.005416;,
0.589000;0.000000;0.005830;,
0.575000;0.000000;0.005830;,
0.589000;0.000000;0.005830;,
0.575000;0.004123;0.004123;,
0.575000;0.000000;0.005830;,
0.589000;0.001000;0.005416;,
0.595010;0.001000;0.005416;,
0.595010;0.004123;0.004123;,
0.595010;0.004123;-0.004123;,
0.575000;0.000000;-0.005830;,
0.575000;0.004123;-0.004123;,
0.589000;0.001000;-0.005416;,
0.589000;0.000000;-0.005830;,
0.595010;0.001000;-0.005416;,
0.595010;-0.004123;-0.004123;,
0.589000;-0.001000;-0.005416;,
0.595010;-0.001000;-0.005416;,
0.589000;0.000000;-0.005830;,
0.575000;0.000000;-0.005830;,
0.575000;-0.004123;-0.004123;,
0.595010;0.001000;-0.005416;,
0.595010;0.004123;0.004123;,
0.595010;0.001000;0.005416;,
0.595010;0.005830;0.000000;,
0.595010;0.004123;-0.004123;,
0.595010;-0.001000;0.005416;,
0.595010;-0.004123;-0.004123;,
0.595010;-0.001000;-0.005416;,
0.595010;-0.005830;0.000000;,
0.595010;-0.004123;0.004123;,
0.589000;-0.001000;0.005416;,
0.595010;-0.001000;-0.005416;,
0.589000;-0.001000;-0.005416;,
0.595010;-0.001000;0.005416;,
0.589000;0.001000;0.005416;,
0.595010;0.001000;-0.005416;,
0.595010;0.001000;0.005416;,
0.589000;0.001000;-0.005416;,
0.589000;0.001000;-0.005416;,
0.589000;-0.001000;-0.005416;,
0.589000;0.000000;-0.005830;,
0.589000;0.001000;0.005416;,
0.589000;-0.001000;0.005416;,
0.589000;0.000000;0.005830;,
-0.575230;-0.005830;0.000000;,
0.575000;-0.004123;-0.004123;,
0.575000;-0.005830;0.000000;,
-0.575230;-0.004123;-0.004123;,
0.595010;-0.005830;0.000000;,
0.595010;-0.004123;-0.004123;,
-0.575230;-0.004123;0.004123;,
0.575000;-0.005830;0.000000;,
0.575000;-0.004123;0.004123;,
-0.575230;-0.005830;0.000000;,
0.595010;-0.004123;0.004123;,
0.595010;-0.005830;0.000000;,
-0.575230;0.000000;0.005830;,
-0.575230;-0.004123;0.004123;,
-0.575230;0.004123;0.004123;,
-0.575230;0.000000;0.005830;,
-0.575230;0.005830;0.000000;,
0.575000;0.004123;0.004123;,
0.575000;0.005830;0.000000;,
-0.575230;0.004123;0.004123;,
0.595010;0.005830;0.000000;,
0.595010;0.004123;0.004123;,
-0.575230;0.004123;-0.004123;,
0.575000;0.005830;0.000000;,
0.575000;0.004123;-0.004123;,
-0.575230;0.005830;0.000000;,
0.595010;0.004123;-0.004123;,
0.595010;0.005830;0.000000;,
-0.575230;0.000000;-0.005830;,
-0.575230;0.004123;-0.004123;,
-0.575230;-0.004123;-0.004123;,
-0.575230;0.000000;-0.005830;,
-0.575230;0.004123;-0.004123;,
-0.575230;-0.004123;-0.004123;,
-0.575230;0.000000;-0.005830;,
-0.575230;-0.005830;0.000000;,
-0.575230;0.005830;0.000000;,
-0.575230;-0.004123;0.004123;,
-0.575230;0.004123;0.004123;,
-0.575230;0.000000;0.005830;,
-0.577010;0.000000;0.000000;,
-0.575230;-0.004123;-0.004123;,
-0.575230;-0.005830;0.000000;,
-0.575230;-0.004123;0.004123;,
-0.575230;0.000000;0.005830;,
-0.575230;0.004123;0.004123;,
-0.575230;0.005830;0.000000;,
-0.575230;0.004123;-0.004123;,
-0.575230;0.000000;-0.005830;,
0.363745;0.000000;0.000000;,
0.570745;-0.029878;-0.017250;,
0.536245;0.000000;0.000000;,
0.398245;-0.029878;-0.017250;,
0.363745;0.000000;0.000000;,
0.570745;-0.029878;-0.017250;,
0.398245;-0.029878;-0.017250;,
0.536245;0.000000;0.000000;,
0.363745;0.000000;0.000000;,
0.570745;0.029878;-0.017250;,
0.536245;0.000000;0.000000;,
0.398245;0.029878;-0.017250;,
0.363745;0.000000;0.000000;,
0.570745;0.029878;-0.017250;,
0.398245;0.029878;-0.017250;,
0.536245;0.000000;0.000000;,
0.570745;0.000000;0.034500;,
0.536245;0.000000;0.000000;,
0.398245;0.000000;0.034500;,
0.363745;0.000000;0.000000;,
0.570745;0.000000;0.034500;,
0.398245;0.000000;0.034500;,
0.536245;0.000000;0.000000;,
-0.580749;0.001026;0.006030;,
-0.587870;0.001800;0.000000;,
-0.622150;0.000000;0.004471;,
-0.632950;0.000000;0.000000;,
-0.628450;0.000000;0.003145;,
-0.587870;-0.001800;0.000000;,
-0.628450;0.000000;0.003145;,
-0.632950;0.000000;0.000000;,
-0.622150;0.000000;0.004471;,
-0.580749;-0.001026;0.006030;,
-0.622150;0.000000;-0.004558;,
-0.587870;0.001800;0.000000;,
-0.580749;0.001026;-0.006030;,
-0.628450;0.000000;-0.003181;,
-0.632950;0.000000;0.000000;,
-0.632950;0.000000;0.000000;,
-0.628450;0.000000;-0.003181;,
-0.587870;-0.001800;0.000000;,
-0.622150;0.000000;-0.004558;,
-0.580749;-0.001026;-0.006030;,
-0.543850;0.000000;0.000000;,
-0.568150;-0.001062;-0.001530;,
-0.568150;0.001062;-0.001530;,
-0.578050;0.001062;-0.001530;,
-0.578050;-0.001062;-0.001530;,
-0.578050;-0.001062;-0.001530;,
-0.580749;0.001026;-0.006030;,
-0.578050;0.001062;-0.001530;,
-0.580749;-0.001026;-0.006030;,
-0.580749;-0.001026;-0.006030;,
-0.622150;0.000000;-0.004558;,
-0.580749;0.001026;-0.006030;,
-0.580749;0.001026;-0.006030;,
-0.587870;0.001800;0.000000;,
-0.578050;0.001062;-0.001530;,
-0.567250;0.001062;0.000000;,
-0.568150;0.001062;-0.001530;,
-0.568150;-0.001062;-0.001530;,
-0.567250;-0.001062;0.000000;,
-0.578050;-0.001062;-0.001530;,
-0.580749;-0.001026;-0.006030;,
-0.587870;-0.001800;0.000000;,
-0.543850;0.000000;0.000000;,
-0.543850;0.000000;0.000000;,
-0.543850;0.000000;0.000000;,
-0.568150;0.001062;0.001530;,
-0.568150;-0.001062;0.001530;,
-0.578050;0.001062;0.001530;,
-0.578050;-0.001062;0.001530;,
-0.578050;-0.001062;0.001530;,
-0.580749;0.001026;0.006030;,
-0.580749;-0.001026;0.006030;,
-0.578050;0.001062;0.001530;,
-0.580749;-0.001026;0.006030;,
-0.580749;0.001026;0.006030;,
-0.622150;0.000000;0.004471;,
-0.578050;0.001062;0.001530;,
-0.580749;0.001026;0.006030;,
-0.568150;0.001062;0.001530;,
-0.568150;-0.001062;0.001530;,
-0.578050;-0.001062;0.001530;,
-0.580749;-0.001026;0.006030;;

 231;
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
3;106,107,105;,
3;106,108,107;,
3;108,106,109;,
3;112,111,110;,
3;110,111,113;,
3;113,111,114;,
3;114,111,115;,
3;118,117,116;,
3;116,117,119;,
3;119,117,120;,
3;116,119,121;,
3;124,123,122;,
3;126,123,125;,
3;126,122,123;,
3;127,122,126;,
3;130,129,128;,
3;129,131,128;,
3;131,132,128;,
3;135,134,133;,
3;134,136,133;,
3;136,137,133;,
3;140,139,138;,
3;139,141,138;,
3;144,143,142;,
3;143,145,142;,
3;148,147,146;,
3;146,147,149;,
3;147,150,149;,
3;149,150,151;,
3;154,153,152;,
3;153,155,152;,
3;157,153,156;,
3;153,154,156;,
3;160,159,158;,
3;159,161,158;,
3;163,159,162;,
3;159,160,162;,
3;109,106,164;,
3;106,165,164;,
3;111,112,166;,
3;112,167,166;,
3;170,169,168;,
3;169,171,168;,
3;173,169,172;,
3;169,170,172;,
3;176,175,174;,
3;175,177,174;,
3;179,175,178;,
3;175,176,178;,
3;117,118,180;,
3;118,181,180;,
3;127,126,182;,
3;126,183,182;,
3;186,185,184;,
3;187,184,185;,
3;184,187,188;,
3;189,188,187;,
3;188,189,190;,
3;190,189,191;,
3;194,193,192;,
3;195,194,192;,
3;196,195,192;,
3;197,196,192;,
3;198,197,192;,
3;199,198,192;,
3;200,199,192;,
3;193,200,192;,
3;186,185,184;,
3;187,184,185;,
3;184,187,188;,
3;189,188,187;,
3;188,189,190;,
3;190,189,191;,
3;203,202,201;,
3;202,204,201;,
3;207,206,205;,
3;206,208,205;,
3;211,210,209;,
3;210,212,209;,
3;215,214,213;,
3;214,216,213;,
3;218,217,60;,
3;217,219,60;,
3;222,221,220;,
3;221,223,220;,
3;226,225,224;,
3;225,226,227;,
3;226,228,227;,
3;231,230,229;,
3;230,232,229;,
3;233,229,232;,
3;236,235,234;,
3;234,235,237;,
3;237,235,238;,
3;241,240,239;,
3;241,242,240;,
3;243,242,241;,
3;246,245,244;,
3;246,247,245;,
3;247,248,245;,
3;251,250,249;,
3;250,252,249;,
3;255,254,253;,
3;258,257,256;,
3;257,258,259;,
3;258,260,259;,
3;263,262,261;,
3;265,263,264;,
3;265,262,263;,
3;259,260,266;,
3;261,262,267;,
3;270,269,268;,
3;272,271,270;,
3;271,269,270;,
3;275,274,273;,
3;274,276,273;,
3;279,278,277;,
3;281,257,280;,
3;280,257,282;,
3;282,257,259;,
3;265,283,262;,
3;265,284,283;,
3;265,285,284;,
3;282,259,266;,
3;262,283,267;;
MeshMaterialList {
 1;
 231;
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
 286;
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
0.000000;0.382535;-0.923941;,
0.000000;0.382535;-0.923941;,
0.000001;0.382529;-0.923943;,
0.000003;0.382525;-0.923945;,
0.000003;0.382523;-0.923946;,
0.000000;0.382530;-0.923943;,
0.000003;-0.382523;-0.923946;,
0.000001;-0.382529;-0.923944;,
0.000000;-0.382530;-0.923943;,
0.000003;-0.382525;-0.923945;,
0.000000;-0.382535;-0.923941;,
0.000000;-0.382535;-0.923941;,
0.000001;-0.382534;0.923941;,
0.000000;-0.382528;0.923944;,
0.000000;-0.382530;0.923943;,
0.000001;-0.382529;0.923943;,
0.000000;-0.382515;0.923949;,
0.000000;-0.382535;0.923941;,
0.000001;0.382534;0.923941;,
0.000001;0.382529;0.923943;,
0.000000;0.382535;0.923941;,
0.000000;0.382515;0.923949;,
0.000000;0.382529;0.923944;,
0.000000;0.382530;0.923943;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.923943;-0.382530;,
0.000000;0.382530;-0.923943;,
0.000000;0.382530;-0.923943;,
0.000000;-0.382530;-0.923943;,
0.000000;-0.382530;-0.923943;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;-0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.923943;0.382530;,
0.000000;-0.382530;0.923943;,
0.000000;-0.382530;0.923943;,
0.000000;0.382530;0.923943;,
0.000000;0.382530;0.923943;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.956428;0.206454;0.206454;,
0.956416;0.292006;0.000000;,
0.956428;0.206454;-0.206454;,
0.956416;0.000000;-0.292006;,
0.956428;-0.206454;-0.206454;,
0.956416;-0.292006;0.000000;,
0.956428;-0.206454;0.206454;,
0.956416;0.000000;0.292006;,
0.000000;0.499998;-0.866026;,
0.000000;0.499998;-0.866026;,
0.000000;0.499998;-0.866026;,
0.000000;0.499998;-0.866026;,
0.000000;-0.499998;0.866026;,
0.000000;-0.499998;0.866026;,
0.000000;-0.499998;0.866026;,
0.000000;-0.499998;0.866026;,
0.000000;0.499998;0.866026;,
0.000000;0.499998;0.866026;,
0.000000;0.499998;0.866026;,
0.000000;0.499998;0.866026;,
0.000000;-0.499998;-0.866026;,
0.000000;-0.499998;-0.866026;,
0.000000;-0.499998;-0.866026;,
0.000000;-0.499998;-0.866026;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.030566;-0.986205;-0.162684;,
0.035160;-0.990971;-0.129382;,
0.023483;-0.995983;-0.086411;,
0.019883;-0.998648;-0.048030;,
0.000000;-1.000000;0.000000;,
0.034181;0.991682;-0.124087;,
0.035970;0.993854;-0.104695;,
0.039832;0.997580;-0.056994;,
0.031296;0.987035;-0.157422;,
0.030566;0.986205;-0.162684;,
0.031243;-0.987425;0.154969;,
0.034144;-0.991914;0.122230;,
0.030212;-0.986283;0.162276;,
0.036092;-0.994118;0.102111;,
0.039834;-0.997616;0.056351;,
0.039834;0.997616;0.056351;,
0.036092;0.994118;0.102111;,
0.034144;0.991914;0.122230;,
0.031243;0.987425;0.154969;,
0.030212;0.986283;0.162276;,
-0.062839;0.000000;0.998024;,
-0.020955;0.000000;0.999780;,
-0.031435;0.000000;0.999506;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
-0.857581;0.000000;0.514350;,
-0.857581;0.000000;0.514350;,
-0.857581;0.000000;0.514350;,
-0.857581;0.000000;0.514350;,
0.035532;0.000000;0.999369;,
0.035532;0.000000;0.999369;,
0.035532;0.000000;0.999369;,
-0.067358;-0.996556;0.048371;,
-0.042119;-0.998176;-0.043256;,
-0.034221;-0.994566;0.098322;,
-0.032392;-0.998462;0.044995;,
-0.022669;-0.999654;0.013334;,
-0.022669;0.999654;0.013334;,
-0.032392;0.998462;0.044995;,
-0.034221;0.994566;0.098322;,
-0.067358;0.996556;0.048371;,
-0.042119;0.998176;-0.043256;,
-0.045338;-0.998972;0.000000;,
-0.045338;0.998972;0.000000;,
-0.062839;0.000000;-0.998024;,
-0.031435;0.000000;-0.999506;,
-0.020955;0.000000;-0.999780;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
-0.857581;0.000000;-0.514350;,
-0.857581;0.000000;-0.514350;,
-0.857581;0.000000;-0.514350;,
-0.857581;0.000000;-0.514350;,
0.037629;0.000000;-0.999292;,
0.037629;0.000000;-0.999292;,
0.037629;0.000000;-0.999292;,
-0.034386;-0.968538;-0.246480;,
-0.067358;-0.996556;-0.048371;,
-0.027584;-0.986070;-0.164029;,
-0.027584;0.986070;-0.164029;,
-0.034386;0.968538;-0.246480;,
-0.067358;0.996556;-0.048371;;

 231;
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
3;106,107,105;,
3;106,108,107;,
3;108,106,109;,
3;112,111,110;,
3;110,111,113;,
3;113,111,114;,
3;114,111,115;,
3;118,117,116;,
3;116,117,119;,
3;119,117,120;,
3;116,119,121;,
3;124,123,122;,
3;126,123,125;,
3;126,122,123;,
3;127,122,126;,
3;130,129,128;,
3;129,131,128;,
3;131,132,128;,
3;135,134,133;,
3;134,136,133;,
3;136,137,133;,
3;140,139,138;,
3;139,141,138;,
3;144,143,142;,
3;143,145,142;,
3;148,147,146;,
3;146,147,149;,
3;147,150,149;,
3;149,150,151;,
3;154,153,152;,
3;153,155,152;,
3;157,153,156;,
3;153,154,156;,
3;160,159,158;,
3;159,161,158;,
3;163,159,162;,
3;159,160,162;,
3;109,106,164;,
3;106,165,164;,
3;111,112,166;,
3;112,167,166;,
3;170,169,168;,
3;169,171,168;,
3;173,169,172;,
3;169,170,172;,
3;176,175,174;,
3;175,177,174;,
3;179,175,178;,
3;175,176,178;,
3;117,118,180;,
3;118,181,180;,
3;127,126,182;,
3;126,183,182;,
3;186,185,184;,
3;187,184,185;,
3;184,187,188;,
3;189,188,187;,
3;188,189,190;,
3;190,189,191;,
3;194,193,192;,
3;195,194,192;,
3;196,195,192;,
3;197,196,192;,
3;198,197,192;,
3;199,198,192;,
3;200,199,192;,
3;193,200,192;,
3;186,185,184;,
3;187,184,185;,
3;184,187,188;,
3;189,188,187;,
3;188,189,190;,
3;190,189,191;,
3;203,202,201;,
3;202,204,201;,
3;207,206,205;,
3;206,208,205;,
3;211,210,209;,
3;210,212,209;,
3;215,214,213;,
3;214,216,213;,
3;218,217,60;,
3;217,219,60;,
3;222,221,220;,
3;221,223,220;,
3;226,225,224;,
3;225,226,227;,
3;226,228,227;,
3;231,230,229;,
3;230,232,229;,
3;233,229,232;,
3;236,235,234;,
3;234,235,237;,
3;237,235,238;,
3;241,240,239;,
3;241,242,240;,
3;243,242,241;,
3;246,245,244;,
3;246,247,245;,
3;247,248,245;,
3;251,250,249;,
3;250,252,249;,
3;255,254,253;,
3;258,257,256;,
3;257,258,259;,
3;258,260,259;,
3;263,262,261;,
3;265,263,264;,
3;265,262,263;,
3;259,260,266;,
3;261,262,267;,
3;270,269,268;,
3;272,271,270;,
3;271,269,270;,
3;275,274,273;,
3;274,276,273;,
3;279,278,277;,
3;281,257,280;,
3;280,257,282;,
3;282,257,259;,
3;265,283,262;,
3;265,284,283;,
3;265,285,284;,
3;282,259,266;,
3;262,283,267;;
 }
}
 }
 }