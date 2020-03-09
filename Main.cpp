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
        File.close();
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
        File.close();
    return true;
}

bool Validacion4(char**argv){
    Bitmap bitmap;
    std::ifstream File;
    File.open(argv[2]);
        if(File.fail()){ std::cout<<"Archivo \""<<argv[2]<<"\" no existe\n"; return false;}
    strcpy(bitmap.NameFile,argv[2]);
    bitmap.ReadMetadata();
        if(strcmp(bitmap.Type,"BM")!=0 || bitmap.SizeP!=24){std::cout<<"Formato de archivo no soportado\n";
            return false;}
    return true;
}

bool Validacion5(char**argv){
    Bitmap bitmap;
    std::ifstream File;
    File.open(argv[2]);
        if(File.fail()){ std::cout<<"Archivo \""<<argv[2]<<"\" no existe\n"; return false;}
    strcpy(bitmap.NameFile,argv[2]);
    bitmap.ReadMetadata();
        if(strcmp(bitmap.Type,"BM")!=0){std::cout<<"Archivo o imagen no es BMP\n";return false;} 
        if(bitmap.SizeP!=24){std::cout<<"Imagen no valida para ocultar el mensaje\n";return false;}
        if(bitmap.Reserved1>0){std::cout<<"Imagen ya contiene un mensaje de "<<bitmap.Reserved1<<" caracteres\n"; return false;}
        File.close();
            return true;
}



void IniciarComando1(char** argv){
    Bitmap bitmap;
    int len=strlen(argv[4]);
    argv[4][len]=0;
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
        File.close();
}

void IniciarComando3(char** argv){
    Bitmap bitmap;
    strcpy(bitmap.NameFile,argv[2]);
    bitmap.ReadString();

}

void IniciarComando4(char** argv){
    Bitmap bitmap;
    strcpy(bitmap.NameFile,argv[2]);
    bitmap.SaveStringFile(argv[4]);
}

void IniciarComando5(char**argv){
    Bitmap bitmap;
    strcpy(bitmap.NameFile,argv[2]);
    std::cout<<"Cantidad maxima de caracteres a ocultar es: "<<bitmap.SizeData/8<<"\n";
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
                 if(argc==3){
                 if(!Validacion3(argv)){return 0;
                 }else{ IniciarComando3(argv); return 0;}}
                     if(strcmp(argv[3],"-f")!=0){ 
                         std::cout<<"Comando \""<<argv[3]<<"\" no existe\n"; return 0;}
                     if(argc==4){ PrintError(); return 0;}
                        IniciarComando4(argv);
                break;

            case 3:
                    if(argc==2){PrintError();return 0;}
                            if(!Validacion4(argv)){return 0;}
                             IniciarComando5(argv);          
                break;

            case 4: 
                if(argc==2){PrintError();return 0;}
                if(Validacion5(argv)){std::cout<<"Imagen valida para ocultar mensaje\n";}
                break;
        }
}
