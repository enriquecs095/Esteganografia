#ifndef BITMAP_H
#define BITMAP_H
#include "stdint.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#define SIZEHEADER 54


class Bitmap{

public:
Bitmap();
char NameFile[100];
char NameFileNew[100];
char Type[3];
int SizeData;
int Limit=0;
uint8_t Padding; //el alineamiento
uint32_t Size;
uint16_t Reserved1;
uint16_t Reserved2;
uint32_t Info;
//-----
uint32_t SizeHead;
uint32_t Widht;
uint32_t Height;
uint16_t NumberP;
uint16_t SizeP; //tamaño pixel
uint32_t Compresion;
uint32_t SizeImage;
uint32_t ResoX;
uint32_t ResoY;
uint32_t SizeTableColor;
uint32_t CountColor;
void RGB();
void Print();
bool SaveString(char*);
void ReadString();
void SaveStringFile(char*);
void ReadMetadata();

private:
#pragma pack(push,1)
void UnPack();
void Pack();
void Write();
void setHeader(const char*);
void setData(const char*);
char* int2bit(int);
void TurnOnBit();
void TurnOffBit();
int bit2int(char*);
std::ifstream BMPRead;
std::ofstream BMPWrite;
int LengthString;
uint16_t NewReserved;
unsigned char* ImageData;
char* NewData;
char* HeaderData;
char* Message;
int PData=2;
#pragma pack(pop)
};

#endif
