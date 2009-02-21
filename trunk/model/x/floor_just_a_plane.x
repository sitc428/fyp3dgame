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
Frame pCube1 {
   FrameTransformMatrix {
7.683751,0.000000,0.000000,0.000000,
0.000000,4.577677,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
-0.109977,-0.494518,2.147024,1.000000;;
 }
Mesh pCube12 {
 24;
-7.555289;12.369718;-2.147024;,
7.555289;12.369718;-2.147024;,
-7.555289;12.369718;2.147024;,
7.555289;12.369718;2.147024;,
-7.555289;12.369718;2.147024;,
7.555289;12.369718;2.147024;,
-7.555289;-12.369718;2.147024;,
7.555289;-12.369718;2.147024;,
-7.555289;-12.369718;2.147024;,
7.555289;-12.369718;2.147024;,
-7.555289;-12.369718;-2.147024;,
7.555289;-12.369718;-2.147024;,
-7.555289;-12.369718;-2.147024;,
7.555289;-12.369718;-2.147024;,
-7.555289;12.369718;-2.147024;,
7.555289;12.369718;-2.147024;,
7.555289;12.369718;-2.147024;,
7.555289;-12.369718;-2.147024;,
7.555289;12.369718;2.147024;,
7.555289;-12.369718;2.147024;,
-7.555289;-12.369718;-2.147024;,
-7.555289;12.369718;-2.147024;,
-7.555289;-12.369718;2.147024;,
-7.555289;12.369718;2.147024;;

 12;
3;2,1,0;,
3;3,1,2;,
3;6,5,4;,
3;7,5,6;,
3;10,9,8;,
3;11,9,10;,
3;14,13,12;,
3;15,13,14;,
3;18,17,16;,
3;19,17,18;,
3;22,21,20;,
3;23,21,22;;
MeshMaterialList {
 1;
 12;
  0,
  0,
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
Material lambert1 {
 0.400000;0.400000;0.400000;1.000000;;
8.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 24;
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;;

 12;
3;2,1,0;,
3;3,1,2;,
3;6,5,4;,
3;7,5,6;,
3;10,9,8;,
3;11,9,10;,
3;14,13,12;,
3;15,13,14;,
3;18,17,16;,
3;19,17,18;,
3;22,21,20;,
3;23,21,22;;
 }
MeshTextureCoords {
 24;
0.375000;1.000000;,
0.625000;1.000000;,
0.375000;0.750000;,
0.625000;0.750000;,
0.375000;0.750000;,
0.625000;0.750000;,
0.375000;0.500000;,
0.625000;0.500000;,
0.375000;0.500000;,
0.625000;0.500000;,
0.375000;0.250000;,
0.625000;0.250000;,
0.375000;0.250000;,
0.625000;0.250000;,
0.375000;0.000000;,
0.625000;0.000000;,
0.625000;1.000000;,
0.875000;1.000000;,
0.625000;0.750000;,
0.875000;0.750000;,
0.125000;1.000000;,
0.375000;1.000000;,
0.125000;0.750000;,
0.375000;0.750000;;
}
}
 }
 }