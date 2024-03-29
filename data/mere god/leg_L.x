xof 0302txt 0064
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

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
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

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
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

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 63;
 -1.00000;-9.00000;-2.00000;,
 -1.00000;-10.00000;-2.00000;,
 -1.00000;-10.00000;-1.00000;,
 -1.00000;-9.00000;-1.00000;,
 -1.00000;-10.00000;-1.00000;,
 -1.00000;-10.00000;1.00000;,
 -1.00000;-9.00000;-1.00000;,
 -1.00000;-9.00000;1.00000;,
 -1.00000;-10.00000;1.00000;,
 -1.00000;-10.00000;2.00000;,
 -1.00000;-9.00000;1.00000;,
 -1.00000;-9.00000;2.00000;,
 -1.00000;-8.00000;-2.00000;,
 -1.00000;-9.00000;-2.00000;,
 -1.00000;-9.00000;2.00000;,
 -1.00000;-8.00000;-1.00000;,
 -1.00000;-8.00000;0.00000;,
 -1.00000;-8.00000;2.00000;,
 -1.00000;-7.00000;0.00000;,
 -1.00000;0.00000;-1.00000;,
 -1.00000;-7.00000;1.00000;,
 -1.00000;0.00000;1.00000;,
 0.00000;-7.00000;0.00000;,
 0.00000;-8.00000;0.00000;,
 0.00000;-8.00000;1.00000;,
 0.00000;-7.00000;1.00000;,
 0.00000;-8.00000;-1.00000;,
 0.00000;-6.00000;-1.00000;,
 0.00000;-6.00000;0.00000;,
 1.00000;-10.00000;1.00000;,
 1.00000;-9.00000;1.00000;,
 1.00000;-10.00000;2.00000;,
 1.00000;-9.00000;2.00000;,
 1.00000;-9.00000;-2.00000;,
 1.00000;-8.00000;-2.00000;,
 1.00000;-9.00000;-1.00000;,
 1.00000;-8.00000;-1.00000;,
 1.00000;-9.00000;1.00000;,
 1.00000;-8.00000;1.00000;,
 1.00000;-9.00000;2.00000;,
 1.00000;-8.00000;2.00000;,
 1.00000;-8.00000;0.00000;,
 1.00000;-6.00000;0.00000;,
 1.00000;-6.00000;-1.00000;,
 1.00000;0.00000;-1.00000;,
 1.00000;0.00000;1.00000;,
 2.00000;-10.00000;-2.00000;,
 2.00000;-9.00000;-2.00000;,
 2.00000;-10.00000;-1.00000;,
 2.00000;-10.00000;-1.00000;,
 2.00000;-9.00000;-1.00000;,
 2.00000;-10.00000;1.00000;,
 2.00000;-9.00000;-1.00000;,
 2.00000;-9.00000;1.00000;,
 2.00000;-8.00000;-1.00000;,
 2.00000;-9.00000;1.00000;,
 2.00000;-8.00000;1.00000;,
 1.00000;-10.00000;-2.00000;,
 1.00000;-9.00000;-2.00000;,
 1.00000;-10.00000;-2.00000;,
 1.00000;-10.00000;-1.00000;,
 1.00000;-10.00000;-1.00000;,
 1.00000;-10.00000;1.00000;;
 
 94;
 3;0,1,2;,
 3;3,4,5;,
 3;6,0,2;,
 3;7,8,9;,
 3;10,3,5;,
 3;11,7,9;,
 3;12,13,3;,
 3;12,3,10;,
 3;12,10,14;,
 3;15,12,14;,
 3;16,15,14;,
 3;17,16,14;,
 3;18,15,16;,
 3;19,15,18;,
 3;19,18,20;,
 3;21,19,20;,
 3;22,23,24;,
 3;25,22,24;,
 3;26,27,23;,
 3;27,28,23;,
 3;29,30,31;,
 3;30,32,31;,
 3;33,34,35;,
 3;34,36,35;,
 3;37,38,39;,
 3;38,40,39;,
 3;41,42,38;,
 3;43,44,42;,
 3;42,45,38;,
 3;44,45,42;,
 3;46,47,48;,
 3;49,50,51;,
 3;47,52,48;,
 3;50,53,51;,
 3;52,54,55;,
 3;54,56,55;,
 3;57,1,0;,
 3;33,13,12;,
 3;58,57,0;,
 3;34,33,12;,
 3;46,59,33;,
 3;47,46,33;,
 3;26,15,19;,
 3;27,26,19;,
 3;43,27,19;,
 3;44,43,19;,
 3;52,35,36;,
 3;54,52,36;,
 3;41,23,28;,
 3;42,41,28;,
 3;16,23,18;,
 3;23,22,18;,
 3;20,25,21;,
 3;24,38,25;,
 3;25,45,21;,
 3;38,45,25;,
 3;29,51,30;,
 3;37,55,38;,
 3;51,53,30;,
 3;55,56,38;,
 3;9,31,11;,
 3;14,39,17;,
 3;31,32,11;,
 3;39,40,17;,
 3;2,1,57;,
 3;60,59,46;,
 3;61,2,57;,
 3;48,60,46;,
 3;5,4,60;,
 3;29,61,49;,
 3;62,5,60;,
 3;51,29,49;,
 3;9,8,29;,
 3;31,9,29;,
 3;20,18,22;,
 3;25,20,22;,
 3;28,27,43;,
 3;42,28,43;,
 3;33,35,47;,
 3;35,52,47;,
 3;12,15,34;,
 3;15,26,34;,
 3;26,36,34;,
 3;36,23,54;,
 3;26,23,36;,
 3;23,41,54;,
 3;16,24,23;,
 3;41,38,54;,
 3;38,56,54;,
 3;16,17,24;,
 3;24,17,38;,
 3;17,40,38;,
 3;19,21,44;,
 3;21,45,44;;
 
 MeshMaterialList {
  1;
  94;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "obj\\knight.png";
   }
  }
 }
 MeshNormals {
  7;
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;;
  94;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;;
 }
 MeshTextureCoords {
  63;
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;,
  0.935547;0.500000;,
  0.908203;0.500000;,
  0.935547;0.500000;;
 }
}
