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
 154;
 3.50489;0.00201;-0.99020;,
 3.50489;-0.99799;1.00980;,
 3.50489;-0.99799;-0.99020;,
 3.50489;0.00201;1.00980;,
 3.50489;1.00201;-0.99020;,
 3.50489;0.00201;1.00980;,
 3.50489;0.00201;-0.99020;,
 3.50489;1.00201;1.00980;,
 2.50489;-7.99799;-0.99020;,
 2.50489;-8.99799;2.00980;,
 2.50489;-8.99799;-1.99020;,
 2.50489;-7.99799;1.00980;,
 2.50489;-5.99799;-0.99020;,
 2.50489;-5.99799;-0.99020;,
 2.50489;-7.99799;1.00980;,
 2.50489;-7.99799;-0.99020;,
 2.50489;-5.99799;1.00980;,
 2.50489;-5.99799;1.00980;,
 2.50489;-4.99799;-1.99020;,
 2.50489;-4.99799;2.00980;,
 2.50489;0.00201;-0.99020;,
 2.50489;-0.99799;-0.99020;,
 2.50489;-0.99799;-1.99020;,
 2.50489;0.00201;1.00980;,
 2.50489;-0.99799;2.00980;,
 2.50489;-0.99799;1.00980;,
 2.50489;1.00201;-1.99020;,
 2.50489;1.00201;-0.99020;,
 2.50489;1.00201;1.00980;,
 2.50489;1.00201;2.00980;,
 2.50489;2.00201;-0.99020;,
 2.50489;1.00201;1.00980;,
 2.50489;1.00201;-0.99020;,
 2.50489;2.00201;1.00980;,
 1.50489;-2.99799;-0.99020;,
 1.50489;-4.99799;1.00980;,
 1.50489;-4.99799;-0.99020;,
 1.50489;-2.99799;1.00980;,
 1.50489;1.00201;-2.99020;,
 1.50489;-0.99799;-1.99020;,
 1.50489;-0.99799;-2.99020;,
 1.50489;1.00201;-1.99020;,
 1.50489;1.00201;2.00980;,
 1.50489;-0.99799;3.00980;,
 1.50489;-0.99799;2.00980;,
 1.50489;1.00201;3.00980;,
 1.50489;2.00201;-1.99020;,
 1.50489;1.00201;-0.99020;,
 1.50489;1.00201;-1.99020;,
 1.50489;2.00201;-0.99020;,
 1.50489;2.00201;1.00980;,
 1.50489;1.00201;2.00980;,
 1.50489;1.00201;1.00980;,
 1.50489;2.00201;2.00980;,
 1.50489;3.00201;-0.99020;,
 1.50489;2.00201;1.00980;,
 1.50489;2.00201;-0.99020;,
 1.50489;3.00201;1.00980;,
 0.50489;-1.99799;-0.99020;,
 0.50489;-2.99799;1.00980;,
 0.50489;-2.99799;-0.99020;,
 0.50489;-1.99799;1.00980;,
 2.50489;0.00201;-0.99020;,
 2.50489;0.00201;1.00980;,
 1.50489;-8.99799;-0.99020;,
 1.50489;-8.99799;1.00980;,
 1.50489;-7.99799;-0.99020;,
 1.50489;-7.99799;1.00980;,
 1.50489;-7.99799;-0.99020;,
 1.50489;-7.99799;1.00980;,
 1.50489;-6.99799;-0.99020;,
 1.50489;-6.99799;1.00980;,
 1.50489;-0.99799;-0.99020;,
 1.50489;1.00201;-0.99020;,
 1.50489;-0.99799;1.00980;,
 1.50489;1.00201;1.00980;,
 0.50489;-8.99799;-1.99020;,
 0.50489;-8.99799;-0.99020;,
 0.50489;-7.99799;-1.99020;,
 0.50489;-7.99799;-0.99020;,
 0.50489;-8.99799;1.00980;,
 0.50489;-8.99799;2.00980;,
 0.50489;-7.99799;1.00980;,
 0.50489;-7.99799;2.00980;,
 0.50489;-7.99799;-1.99020;,
 0.50489;-7.99799;-0.99020;,
 0.50489;-6.99799;-1.99020;,
 0.50489;-6.99799;-0.99020;,
 0.50489;-7.99799;1.00980;,
 0.50489;-7.99799;2.00980;,
 0.50489;-6.99799;1.00980;,
 0.50489;-6.99799;2.00980;,
 0.50489;-4.99799;-0.99020;,
 0.50489;-4.99799;1.00980;,
 0.50489;-0.99799;-2.99020;,
 0.50489;-0.99799;-1.99020;,
 0.50489;1.00201;-2.99020;,
 0.50489;1.00201;-1.99020;,
 0.50489;-0.99799;2.00980;,
 0.50489;-0.99799;3.00980;,
 0.50489;1.00201;2.00980;,
 0.50489;1.00201;3.00980;,
 0.50489;2.00201;-0.99020;,
 0.50489;2.00201;1.00980;,
 0.50489;3.00201;-0.99020;,
 0.50489;3.00201;1.00980;,
 -0.49511;-6.99799;-1.99020;,
 -0.49511;-6.99799;-0.99020;,
 -0.49511;-4.99799;-1.99020;,
 -0.49511;-4.99799;-0.99020;,
 -0.49511;-6.99799;1.00980;,
 -0.49511;-6.99799;2.00980;,
 -0.49511;-4.99799;1.00980;,
 -0.49511;-4.99799;2.00980;,
 -0.49511;-3.99799;-0.99020;,
 -0.49511;-3.99799;1.00980;,
 -0.49511;-3.99799;-0.99020;,
 -0.49511;-3.99799;1.00980;,
 -0.49511;-1.99799;-0.99020;,
 -0.49511;-1.99799;1.00980;,
 -0.49511;1.00201;-1.99020;,
 -0.49511;1.00201;-0.99020;,
 -0.49511;2.00201;-1.99020;,
 -0.49511;2.00201;-0.99020;,
 -0.49511;1.00201;1.00980;,
 -0.49511;1.00201;2.00980;,
 -0.49511;2.00201;1.00980;,
 -0.49511;2.00201;2.00980;,
 1.50489;-7.99799;-1.99020;,
 1.50489;-5.99799;-1.99020;,
 1.50489;-5.99799;-1.99020;,
 1.50489;-7.99799;-1.99020;,
 0.50489;-5.99799;-1.99020;,
 0.50489;-5.99799;-1.99020;,
 0.50489;-4.99799;-1.99020;,
 0.50489;1.00201;-1.99020;,
 0.50489;-4.99799;-1.99020;,
 0.50489;-4.99799;-0.99020;,
 0.50489;-3.99799;-0.99020;,
 0.50489;-3.99799;-0.99020;,
 0.50489;2.00201;1.00980;,
 0.50489;2.00201;-0.99020;,
 0.50489;-4.99799;1.00980;,
 0.50489;-3.99799;1.00980;,
 0.50489;-3.99799;1.00980;,
 1.50489;-7.99799;2.00980;,
 1.50489;-5.99799;2.00980;,
 1.50489;-7.99799;2.00980;,
 1.50489;-5.99799;2.00980;,
 0.50489;-5.99799;2.00980;,
 0.50489;-5.99799;2.00980;,
 0.50489;-4.99799;2.00980;,
 0.50489;1.00201;2.00980;,
 0.50489;-4.99799;2.00980;;
 
 244;
 3;0,1,2;,
 3;3,1,0;,
 3;4,5,6;,
 3;7,5,4;,
 3;8,9,10;,
 3;11,9,8;,
 3;12,8,10;,
 3;13,14,15;,
 3;16,9,11;,
 3;17,14,13;,
 3;18,12,10;,
 3;18,16,12;,
 3;19,9,16;,
 3;19,16,18;,
 3;20,21,22;,
 3;23,24,25;,
 3;26,20,22;,
 3;27,20,26;,
 3;28,24,23;,
 3;29,24,28;,
 3;30,31,32;,
 3;33,31,30;,
 3;34,35,36;,
 3;37,35,34;,
 3;38,39,40;,
 3;41,39,38;,
 3;42,43,44;,
 3;45,43,42;,
 3;46,47,48;,
 3;49,47,46;,
 3;50,51,52;,
 3;53,51,50;,
 3;54,55,56;,
 3;57,55,54;,
 3;58,59,60;,
 3;61,59,58;,
 3;21,25,20;,
 3;20,25,23;,
 3;62,63,32;,
 3;32,63,31;,
 3;64,65,66;,
 3;66,65,67;,
 3;68,69,70;,
 3;70,69,71;,
 3;39,72,41;,
 3;41,72,73;,
 3;74,44,75;,
 3;75,44,42;,
 3;47,52,49;,
 3;49,52,50;,
 3;76,77,78;,
 3;78,77,79;,
 3;80,81,82;,
 3;82,81,83;,
 3;84,85,86;,
 3;86,85,87;,
 3;88,89,90;,
 3;90,89,91;,
 3;87,90,92;,
 3;92,90,93;,
 3;94,95,96;,
 3;96,95,97;,
 3;98,99,100;,
 3;100,99,101;,
 3;102,103,104;,
 3;104,103,105;,
 3;106,107,108;,
 3;108,107,109;,
 3;110,111,112;,
 3;112,111,113;,
 3;109,112,114;,
 3;114,112,115;,
 3;116,117,118;,
 3;118,117,119;,
 3;120,121,122;,
 3;122,121,123;,
 3;124,125,126;,
 3;126,125,127;,
 3;94,38,40;,
 3;96,38,94;,
 3;128,18,10;,
 3;129,18,128;,
 3;39,26,22;,
 3;41,26,39;,
 3;76,128,10;,
 3;84,130,131;,
 3;78,128,76;,
 3;86,130,84;,
 3;132,18,129;,
 3;133,130,86;,
 3;134,18,132;,
 3;135,46,48;,
 3;106,136,133;,
 3;106,133,86;,
 3;108,136,106;,
 3;120,46,135;,
 3;122,46,120;,
 3;21,0,2;,
 3;62,4,6;,
 3;20,0,21;,
 3;32,4,62;,
 3;47,30,32;,
 3;49,30,47;,
 3;137,34,36;,
 3;138,34,137;,
 3;60,34,138;,
 3;102,54,56;,
 3;104,54,102;,
 3;109,139,92;,
 3;116,58,60;,
 3;114,139,109;,
 3;116,60,138;,
 3;118,58,116;,
 3;74,23,25;,
 3;74,28,23;,
 3;75,28,74;,
 3;80,67,65;,
 3;88,71,69;,
 3;82,67,80;,
 3;90,71,88;,
 3;140,50,52;,
 3;110,93,90;,
 3;112,93,110;,
 3;124,140,52;,
 3;126,140,124;,
 3;98,42,44;,
 3;100,42,98;,
 3;39,41,95;,
 3;95,41,97;,
 3;21,20,72;,
 3;20,27,72;,
 3;72,27,73;,
 3;64,66,77;,
 3;68,70,85;,
 3;77,66,79;,
 3;85,70,87;,
 3;47,49,141;,
 3;87,92,107;,
 3;107,92,109;,
 3;47,141,121;,
 3;121,141,123;,
 3;1,3,25;,
 3;5,7,63;,
 3;25,3,23;,
 3;63,7,31;,
 3;31,33,52;,
 3;52,33,50;,
 3;35,37,142;,
 3;142,37,143;,
 3;143,37,59;,
 3;55,57,103;,
 3;103,57,105;,
 3;93,144,112;,
 3;59,61,117;,
 3;112,144,115;,
 3;143,59,117;,
 3;117,61,119;,
 3;9,19,145;,
 3;145,19,146;,
 3;24,29,44;,
 3;44,29,42;,
 3;9,145,81;,
 3;147,148,89;,
 3;81,145,83;,
 3;89,148,91;,
 3;146,19,149;,
 3;91,148,150;,
 3;149,19,151;,
 3;51,53,152;,
 3;150,153,111;,
 3;91,150,111;,
 3;111,153,113;,
 3;152,53,125;,
 3;125,53,127;,
 3;43,45,99;,
 3;99,45,101;,
 3;64,76,10;,
 3;77,76,64;,
 3;65,64,10;,
 3;9,65,10;,
 3;9,80,65;,
 3;81,80,9;,
 3;87,106,86;,
 3;107,106,87;,
 3;71,87,70;,
 3;90,87,71;,
 3;91,110,90;,
 3;111,110,91;,
 3;93,109,92;,
 3;112,109,93;,
 3;39,94,40;,
 3;95,94,39;,
 3;21,39,22;,
 3;72,39,21;,
 3;1,21,2;,
 3;25,21,1;,
 3;24,74,25;,
 3;44,74,24;,
 3;43,98,44;,
 3;99,98,43;,
 3;47,135,48;,
 3;47,120,135;,
 3;121,120,47;,
 3;31,47,32;,
 3;52,47,31;,
 3;51,124,52;,
 3;152,124,51;,
 3;125,124,152;,
 3;55,102,56;,
 3;103,102,55;,
 3;18,134,36;,
 3;136,108,92;,
 3;36,134,137;,
 3;92,108,109;,
 3;18,36,35;,
 3;18,35,19;,
 3;35,142,19;,
 3;93,112,153;,
 3;19,142,151;,
 3;153,112,113;,
 3;34,60,37;,
 3;37,60,59;,
 3;58,118,61;,
 3;61,118,119;,
 3;38,96,41;,
 3;41,96,97;,
 3;26,41,27;,
 3;27,41,73;,
 3;4,32,7;,
 3;7,32,31;,
 3;28,75,29;,
 3;29,75,42;,
 3;42,100,45;,
 3;45,100,101;,
 3;46,122,49;,
 3;49,122,141;,
 3;141,122,123;,
 3;30,49,33;,
 3;33,49,50;,
 3;140,126,53;,
 3;50,140,53;,
 3;53,126,127;,
 3;54,104,57;,
 3;57,104,105;;
 
 MeshMaterialList {
  1;
  244;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  6;
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  244;
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
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
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
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
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
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;;
 }
 MeshTextureCoords {
  154;
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.099610;0.500000;;
 }
}
