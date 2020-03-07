#include "Bitmap.h"



void Menu1(char** argv){
std::ifstream File;
File.open(argv[2]);
if(File.fail()){ std::cout<<"Archivo no existe\n"; return;}




}

void Menu2(char** argv){

    
}

void Menu3(char** argv){

    
}
void Menu4(char** argv){

    
}


bool FileExist(char * name){
std::ifstream File;
File.open(name);
if(File.fail()){
    std::cout<<"Archivo no existe\n";
    return false;
}
return true;
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
                if(argc==2){
                    PrintError();
                    return 0;
                }
                Menu1(argv);
                break;

            case 2:
             if(argc==2){
                    PrintError();
                    return 0;
                }
                Menu2(argv);
                break;

            case 3:
             if(argc==2){
                    PrintError();
                    return 0;
                }
                Menu3(argv);
                break;

            case 4: 
                 if(argc==2){
                    PrintError();
                    return 0;
                }
                Menu4(argv);
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