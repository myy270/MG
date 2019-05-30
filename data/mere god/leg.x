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
 52;
 2.08000;-4.28000;-0.85000;,
 2.08000;-6.28000;1.15000;,
 2.08000;-6.28000;-0.85000;,
 2.08000;-4.28000;1.15000;,
 1.08000;-5.28000;-1.85000;,
 1.08000;-6.28000;-0.85000;,
 1.08000;-6.28000;-1.85000;,
 1.08000;-5.28000;-0.85000;,
 1.08000;-4.28000;-1.85000;,
 1.08000;-5.28000;-0.85000;,
 1.08000;-5.28000;-1.85000;,
 1.08000;-4.28000;-0.85000;,
 1.08000;-4.28000;1.15000;,
 1.08000;-6.28000;2.15000;,
 1.08000;-6.28000;1.15000;,
 1.08000;-4.28000;2.15000;,
 1.08000;0.72000;-0.85000;,
 1.08000;-4.28000;1.15000;,
 1.08000;0.72000;1.15000;,
 -0.92000;-6.28000;-1.85000;,
 -0.92000;-6.28000;-0.85000;,
 -0.92000;-5.28000;-1.85000;,
 -0.92000;-5.28000;-0.85000;,
 -0.92000;-5.28000;-1.85000;,
 -0.92000;-5.28000;-0.85000;,
 -0.92000;-4.28000;-1.85000;,
 -0.92000;-4.28000;-0.85000;,
 -0.92000;-6.28000;1.15000;,
 -0.92000;-6.28000;2.15000;,
 -0.92000;-4.28000;1.15000;,
 -0.92000;-4.28000;2.15000;,
 -0.92000;-4.28000;1.15000;,
 -0.92000;0.72000;-0.85000;,
 -0.92000;0.72000;1.15000;,
 -1.92000;-6.28000;-0.85000;,
 -1.92000;-6.28000;1.15000;,
 -1.92000;-4.28000;-0.85000;,
 -1.92000;-4.28000;1.15000;,
 1.08000;-6.28000;-0.85000;,
 1.08000;-5.28000;-0.85000;,
 1.08000;-4.28000;-0.85000;,
 -0.92000;-5.28000;-0.85000;,
 -0.92000;-6.28000;-0.85000;,
 -0.92000;-4.28000;-0.85000;,
 1.08000;-6.28000;1.15000;,
 1.08000;-4.28000;1.15000;,
 -0.92000;-6.28000;1.15000;,
 -0.92000;-4.28000;1.15000;,
 1.08000;-6.28000;1.15000;,
 -0.92000;-6.28000;-0.85000;,
 1.08000;-6.28000;-0.85000;,
 -0.92000;-6.28000;1.15000;;
 
 60;
 3;0,1,2;,
 3;3,1,0;,
 3;4,5,6;,
 3;7,5,4;,
 3;8,9,10;,
 3;11,9,8;,
 3;12,13,14;,
 3;15,13,12;,
 3;16,17,11;,
 3;18,17,16;,
 3;19,20,21;,
 3;21,20,22;,
 3;23,24,25;,
 3;25,24,26;,
 3;27,28,29;,
 3;29,28,30;,
 3;26,31,32;,
 3;32,31,33;,
 3;34,35,36;,
 3;36,35,37;,
 3;19,4,6;,
 3;23,8,10;,
 3;21,4,19;,
 3;25,8,23;,
 3;38,0,2;,
 3;39,0,38;,
 3;40,0,39;,
 3;26,16,11;,
 3;32,16,26;,
 3;34,41,42;,
 3;34,43,41;,
 3;36,43,34;,
 3;1,3,44;,
 3;44,3,45;,
 3;17,18,31;,
 3;31,18,33;,
 3;46,47,35;,
 3;35,47,37;,
 3;13,15,28;,
 3;28,15,30;,
 3;5,19,6;,
 3;20,19,5;,
 3;1,38,2;,
 3;48,49,50;,
 3;44,38,1;,
 3;46,34,42;,
 3;51,49,48;,
 3;35,34,46;,
 3;13,27,14;,
 3;28,27,13;,
 3;8,25,11;,
 3;11,25,26;,
 3;0,40,3;,
 3;3,40,45;,
 3;43,36,47;,
 3;47,36,37;,
 3;12,29,15;,
 3;15,29,30;,
 3;16,32,18;,
 3;18,32,33;;
 
 MeshMaterialList {
  1;
  60;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "knight.png";
   }
  }
 }
 MeshNormals {
  8;
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  60;
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
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,5;,
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
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;;
 }
 MeshTextureCoords {
  52;
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.869140;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;,
  0.935550;0.500000;;
 }
}
