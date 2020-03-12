# Esteganografia
Desarrollado en c++ con Visual Studio Code

Para Compilarlo en Linux deben hacer los siguientes comandos en la consola donde esta guardado el archivo:

1-g++ -c Main.cpp. 
2- g++ Main.cpp Bitmap.cpp -o run.out (run.out es el archivo ejecutable del programa)
3-
  ./run.out -o cuadro.bmp -m "Mensaje Aqui"  (para guardar el mensaje en la imagen)
  ./run.out -o cuadro.bmp -f Mensaje.txt   (para guardar el mensaje en la imagen, extrayendo los datos de un archivo de texto)
  
  ./run.out -e cuadro.bmp (para imprimir el mensaje en la consola)
  ./run.out -e cuadro.bmp -f Mensaje.txt (para guardar el mensaje en un archivo de texto)
  
  ./run.out -t cuadro.bmp (despliega la cantidad maxima de caracteres que se pueden guardar en la imagen)
  
  ./run.out -v cuadro.bmp (valida si la imagen es valida para guardar los datos y si la imagen ya contiene un mensaje)
  
  Solo se pueden guardar los datos en imagenes bmp de 24 bits, la cantidad de caracteres se guardan en el encabezado de la metada: Reserved1 (2 bytes)
  
  Proyecto desarrollado por Enrique Cruz- Estudiante de Ingenieria en Sistemas en universidad UNITEC de Honduras.
  
  
