#include "Bitmap.h"


bool Validacion1(char** argv){
Bitmap bitmap;
std::ifstream File;
File.open(argv[2]);
    if(File.fail()){ std::cout<<"Archivo \""<<argv[2]<<"\" no existe\n"; return false;}
strcpy(bitmap.NameFile,argv[2]);
bitmap.ReadMetadata();
    if(strcmp(bitmap.Type,"BM")!=0 || bitmap.SizeP!=24){std::cout<<"Formato de archivo no soportado\n";
    return false;}
    if(bitmap.Reserved1>0){std::cout<<"Imagen ya contiene mensaje\n"; return false;}
    return true;
}

bool Validacion2(char** argv){
int c=0;
   if(strcmp(argv[3],"-m")==0){c=1;}
   if(strcmp(argv[3],"-f")==0){c=2;}
   if(c==0){ std::cout<<"Commando \""<<argv[3]<<"\" no existe\n"; return false;}
   return true;
}

bool Validacion3(char** argv){
Bitmap bitmap;
std::ifstream File;
File.open(argv[2]);
    if(File.fail()){ std::cout<<"Archivo \""<<argv[2]<<"\" no existe\n"; return false;}
strcpy(bitmap.NameFile,argv[2]);
bitmap.ReadMetadata();
    if(strcmp(bitmap.Type,"BM")!=0 || bitmap.SizeP!=24){std::cout<<"Formato de archivo no soportado\n";
    return false;}
    if(bitmap.Reserved1==0){
        std::cout<<"Archivo \""<<argv[2]<<"\" no contiene mensaje\n";
        return false;
    }
    return true;
}

void IniciarComando1(char** argv){
Bitmap bitmap;
if(bitmap.SaveString(argv[4])){ std::cout<<"Datos guardados\n";};
}

void IniciarComando2(char** argv){
Bitmap bitmap;
std::ifstream File;
std::string aux1;
std::string aux2;
File.open(argv[4]);
    if(File.fail()){std::cout<<"Archivo \""<<argv[4]<<"\" no existe\n";return;}
    while(!File.eof()){
        getline(File,aux1);
        aux2+=aux1;
}
    if(aux2.length()>0){
        char* aux3=new char[aux2.length()+1];
        aux3[aux2.length()]=0;
        strcpy(aux3,aux2.c_str());
        if(bitmap.SaveString(aux3)){std::cout<<"Datos guardados\n";};
    }
}

void IniciarComando3(char** argv){
Bitmap bitmap;
strcpy(bitmap.NameFile,argv[2]);
bitmap.ReadString();
}

void PrintError(){
    std::cout<<"Faltan mas comando\n";
}

int main(int argc, char**argv){
    std::string command[4];
    int c=0;
        if(argc==1){
            PrintError();
            return 0;
        }
            if(strcmp(argv[1],"-o")==0){c=1;}
            if(strcmp(argv[1],"-e")==0){c=2;}
            if(strcmp(argv[1],"-t")==0){c=3;}
            if(strcmp(argv[1],"-v")==0){c=4;}
        switch(c){
            case 0:
            std::cout<<"Commando \""<<argv[1]<<"\" no existe\n";
            break;    

            case 1:
                if(argc==2){PrintError();return 0;}
                if(!Validacion1(argv)){ return 0;}
                if(argc==3){PrintError();return 0;}
                if(!Validacion2(argv)){ return 0;}
                if(argc==4){PrintError();return 0;}
                if(strcmp(argv[3],"-m")==0){
                    IniciarComando1(argv);
                }else{
                    IniciarComando2(argv);
                }
                break;

            case 2:
             if(argc==2){PrintError();return 0;}
                 if(!Validacion3(argv)){return 0;
                 }else{ IniciarComando3(argv);}
                break;

            case 3:
     
                break;

            case 4: 
       
                break;
        }

    /*
int opcion;
bool salir;
Bitmap bitmap;
    do{
std::cout<<"Lectora BMP\n"<<
         "1. Leer encabezado\n"<<
         "2. Leer codigos RGB\n"<<
         "3. Guardar cadena\n"<<
         "4. Leer cadena\n"<<
         "5. Salir\n"<<
         "Ingrese una opcion: ";       
        std::cin>>opcion;
        switch(opcion){
            case 1: 
            std::cout<<"Ingrese el nombre del archivo: ";
            std::cin>>bitmap.NameFile;
                bitmap.Read();
                bitmap.Print();
                break;

            case 2:
                std::cout<<"Ingrese el nombre del archivo: ";
                std::cin>>bitmap.NameFile;
                bitmap.RGB();
                break;
             case 3:
                bitmap.NameFile[99]=0;
                bitmap.NameFileNew[99]=0;
                std::cout<<"Ingrese el nombre del archivo: ";
                std::cin>>bitmap.NameFile;

                std::cout<<"Ingrese la cadena: ";
                std::cin>>bitmap.Cadena;
                
                std::cout<<"Ingrese el nombre del archivo nuevo: ";
                std::cin>>bitmap.NameFileNew;
                bitmap.SaveString();
                break;

            case 4:
                std::cout<<"Ingrese el nombre del archivo: ";
                std::cin>>bitmap.NameFile;
                bitmap.ReadString();
                break;
 
            case 5:
                salir=false;
                break;
        }

    }while(salir);
*/
}
