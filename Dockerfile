# Imagen base con soporte para C++
FROM ubuntu:24.04

# Instalar g++, make, etc.
RUN apt-get update && apt-get install -y g++ make

# Crear directorio de trabajo
WORKDIR /app

# Copiar todo el contenido del proyecto
COPY . .

# Compilar el programa
RUN g++ -Iinclude -o scanner scr/main.cpp

# Ejecutar el binario
CMD ["./scanner"]
