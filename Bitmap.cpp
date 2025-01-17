#include "Bitmap.h"

Bitmap::Bitmap(){}


void Bitmap::UnPack(){
  char *copy=HeaderData;
  memcpy(&Type[0],copy,1);
  copy+=1;
  memcpy(&Type[1],copy,1);
  copy+=1;
  Type[2]=0;
  memcpy(&Size,copy,4);
  copy+=4;
  memcpy(&Reserved1,copy,2);
  copy+=2;
  memcpy(&Reserved2,copy,2);
  copy+=2;
  memcpy(&Info,copy,4);
  copy+=4;
  memcpy(&SizeHead,copy,4);
  copy+=4;
  memcpy(&Widht,copy,4);//69
  copy+=4;
  memcpy(&Height,copy,4);//32
  copy+=4;
  memcpy(&NumberP,copy,2);
  copy+=2;
  memcpy(&SizeP,copy,2);
  copy+=2;
  memcpy(&Compresion,copy,4);
  copy+=4;
  memcpy(&SizeImage,copy,4);
  copy+=4;
  memcpy(&ResoX,copy,4);
  copy+=4;
  memcpy(&ResoY,copy,4);
  copy+=4;
  memcpy(&SizeTableColor,copy,4);
  copy+=4;
  memcpy(&CountColor,copy,4);
  copy+=4;
  if(Widht%4!=0){Padding=4-(Widht%4);}//el padding
  SizeData=Height*Widht*3;
  Limit=Height*Widht/8;
}


void Bitmap::ReadMetadata(){
  char verificar[3];
  verificar[2]=0;
  char header[SIZEHEADER];
  BMPRead.open(NameFile,std::ifstream::in | std::ifstream::binary);
  BMPRead.read(verificar,2);
    if(strcmp(verificar,"BM")!=0){return;}
  BMPRead.seekg(0,std::ios::beg);
  BMPRead.read(header,sizeof(header));
  setHeader(header);
  UnPack();
  char data[SizeData];
  BMPRead.seekg(Info,std::ios::beg);
  BMPRead.read(data,SizeData);
  setData(data);
  BMPRead.close();
}


void Bitmap::setHeader(const char* header){
  HeaderData=new char[SIZEHEADER];
  memcpy(HeaderData, header,SIZEHEADER);
}


void Bitmap::setData(const char* data){

  ImageData=new unsigned char[SizeData];
 memcpy(ImageData, data,SizeData);
}


void Bitmap::RGB(){
  ReadMetadata();
  unsigned char R;
  unsigned char G;
  unsigned char B;
  int *Red=new int[SizeData];
  int *Green=new int[SizeData];
  int *Blue=new int[SizeData];
  int count=0;
  for (int i =0; i < SizeData; i+=3){
    R=ImageData[i];
    G=ImageData[i+1];
    B=ImageData[i+2];
    Red[count]=R;
    Green[count]=G;
    Blue[count]=B;
    count++;
    }
    count=0;
           for(int j=Height-1;j>=0;j--) {
                for(int i=0; i<Widht;i++) {
                std::cout<<"B: "<<Blue[count]<<" G: "<<Green[count]<<" R: "<<Red[count]<<std::endl;
                  count++;
     }
      count++;
  }
  delete []Red;
  delete []Green;
  delete []Blue; 
  delete []ImageData;
  delete []HeaderData;
}


void Bitmap::Print(){
  std::cout<<"Type: "<<Type<<"\n"
  <<"Size: "<<Size<<"\n"
  <<"Reservado1: "<<Reserved1<<"\n"
  <<"Reservado2: "<<Reserved2<<"\n"
  <<"Info: "<<Info<<"\n"
  <<"Tamaño de cabecera: "<< SizeHead<<"\n"
  <<"Anchura: "<<Widht<<"\n"
  <<"Altura: "<<Height<<"\n"
  <<"Numero Plano: "<<NumberP<<"\n"
  <<"Bits: "<<SizeP<<"\n"
  <<"Compresion: "<<Compresion<<"\n"
  <<"Tamaño Imagen: "<<SizeImage<<"\n"
  <<"Resolucion X: "<<ResoX<<"\n"
  <<"Resolucion Y: "<<ResoY<<"\n"
  <<"Tamaño de la tabla de colores: "<<SizeTableColor<<"\n"
  <<"Cantidad de colores: "<<CountColor<<"\n";
}


bool Bitmap::SaveString(char * cadena){
  ReadMetadata();
  NewReserved=strlen(cadena);
  LengthString=((strlen(cadena)));//cantidad de pixeles que voy a modificar
  int length=strlen(cadena);
  if(LengthString>Limit){std::cout<<"Tamaño de la cadena excede el limite\n"; return false;}
  char *copy=new char[9];
  for (int i = 0; i < length; i++){
    copy=int2bit(cadena[i]); 
    for (int i = 0; i < 8; i++){
      (copy[i]=='1') ? TurnOnBit() : TurnOffBit();//si la posicion de mi bits es 1 0 cero ejecuto cualquiera de las dos funciones
    }
  }
  Pack();
  Write();
  delete copy;
  return true;
}


void Bitmap::Pack(){
  NewData=new char[SizeData];
  int size=0;
  memcpy(&HeaderData[size],Type,2);
  size+=2;
  //Size=(Widht*Height*3)+54;
  memcpy(&HeaderData[size],&Size,4);
  size+=4;
  memcpy(&HeaderData[size],&NewReserved,2);
  size+=2;
  memcpy(&HeaderData[size],&Reserved2,2);
  size+=2;
  memcpy(&HeaderData[size],&Info,4);
  size+=4;
  memcpy(&HeaderData[size],&SizeHead,4);
  size+=4;
  memcpy(&HeaderData[size],&Widht,4);
  size+=4;  
  memcpy(&HeaderData[size],&Height,4);
  size+=4;
  memcpy(&HeaderData[size],&NumberP,2);
  size+=2;
  memcpy(&HeaderData[size],&SizeP,2);
  size+=2;
  memcpy(&HeaderData[size],&Compresion,4);
  size+=4;
  memcpy(&HeaderData[size],&SizeImage,4);
  size+=4;
  memcpy(&HeaderData[size],&ResoX,4);
  size+=4;
  memcpy(&HeaderData[size],&ResoY,4);
  size+=4;
  memcpy(&HeaderData[size],&SizeTableColor,4);
  size+=4;
  memcpy(&HeaderData[size],&CountColor,4);
  size+=4;
    for (int i = 0; i < SizeData; i++){
      memcpy(&NewData[i], &ImageData[i],1);
    }
}


void Bitmap::Write(){
  BMPWrite.open(NameFile,std::ios::binary);
  BMPWrite.seekp(0,std::ios::beg);
  BMPWrite.write(HeaderData,SIZEHEADER);
  BMPWrite.seekp(Info,std::ios::beg);
  BMPWrite.write(NewData,SizeData);
  BMPWrite.close();
  delete [] ImageData;
  delete [] NewData;
  delete [] HeaderData;
}

char* Bitmap::int2bit(int character){
  uint8_t mask=1<<7;
  char* bit=new char[9];
  bit[8]='\0';
  int count=0;
    while(mask){
      if(mask & character){
        bit[count]='1'; 
      }else{
        bit[count]='0';
      }
      mask>>=1;
      count++;
    }
  return bit;
}

void Bitmap::TurnOnBit(){
  char* aux=new char[9];
  aux[8]=0;
  aux=int2bit(ImageData[PData]);//la info de la imagen
    if(aux[7]=='1'){ PData+=3; return;}
  int a=ImageData[PData];
  int resultado=a|1;
  unsigned char aux2=resultado;
  memcpy(&ImageData[PData],&aux2,1);
  PData+=3;
}

void Bitmap::TurnOffBit(){
  char* aux=new char[9];
  aux[8]=0;
  aux=int2bit(ImageData[PData]);
    if(aux[7]=='0'){PData+=3; return;}
  int a=ImageData[PData];
  int resultado=a^1;
  unsigned char aux2=resultado;
  memcpy(&ImageData[PData],&aux2,1);
  PData+=3;
}

void Bitmap::ReadString(){
      ReadMetadata();
      char *copy=new char[9];
      char *copy2=new char[9];
      copy2[8]=0;
      char *copy3=new char[Reserved1+1];
      copy3[Reserved1]=0;
      int count=0;
    for (int i = 0; i < Reserved1; i++){
      for (int j = 0; j < 8; j++){
        copy=int2bit(ImageData[PData]);
        (copy[7]=='1') ? copy2[j]='1' : copy2[j]='0';
         PData+=3;
      }
    char aux=bit2int(copy2);
    memcpy(&copy3[count],&aux,1);
    count++;
    }
    std::cout<<copy3<<"\n"; 
}

void Bitmap::SaveStringFile(char* filename){
      ReadMetadata();
      std::ofstream File;
      File.open(filename,std::ios::app);
      if(File.fail()){ "Error al abrir archivo\n"; return;}
      char *copy=new char[9];
      char *copy2=new char[9];
      copy2[8]=0;
      Message=new char[Reserved1+1];
      Message[Reserved1]=0;
      int count=0;
    for (int i = 0; i < Reserved1; i++){
      for (int j = 0; j < 8; j++){
        copy=int2bit(ImageData[PData]);
        (copy[7]=='1') ? copy2[j]='1' : copy2[j]='0';
         PData+=3;
      }
    char aux=bit2int(copy2);
    memcpy(&Message[count],&aux,1);
    count++;
    }
    File.seekp(0,std::ios::beg);
    File.write(Message,Reserved1);
    std::cout<<"Datos guardados\n";
    File.close();
}


int Bitmap::bit2int(char *cadena){
  int aux=0;
  int aux2=0;
  int count=7;
  for (int i = 0; i < 8; i++){    
    if(cadena[i]=='1'){
      aux=pow(2,count);
      aux2+=aux;
    }
    count--;
  }
  return aux2;
}



