#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define Ancho 160
#define MAX_SIZE 19200 // Tamaño máximo del arreglo, ajusta según necesites

void processRGBFile(const char *filename, int outputCount) {
    char inputPath[100]; // Ruta completa al archivo de entrada
    snprintf(inputPath, sizeof(inputPath), "Binarios/%s", filename); // Ruta completa a la carpeta Binarios

    FILE *archivo;
    archivo = fopen(inputPath, "rb"); // Abre el archivo en modo lectura binaria ("rb")

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", filename);
        return;
    }

    unsigned char bytes[MAX_SIZE]; // Cambiado a unsigned char para interpretar como bytes sin signo
    unsigned char byte; // Cambiado a int para poder detectar EOF correctamente
    int i = 0;

    // Lee el archivo byte por byte y almacena los bytes en el arreglo 'bytes'
    while ((byte = fgetc(archivo)) != EOF && i < MAX_SIZE) {
        bytes[i] = (unsigned char)byte; // Almacena el byte en el arreglo
        i++;
    }

    //printf("Longitud del arreglo 'bytes' para el archivo %s: %d bytes\n", filename, i); // Imprime la longitud del arreglo

    fclose(archivo); // Cierra el archivo
    
    char outputFilename[100]; // Nombre del archivo de salida
    snprintf(outputFilename, sizeof(outputFilename), "Bin_out/Salida_%d.bin", outputCount); // Nombre de salida independiente del nombre del archivo original
    
    FILE *archivo_escritura;
    archivo_escritura = fopen(outputFilename, "wb"); // Abre el archivo en modo escritura binaria ("wb")

    if (archivo_escritura == NULL) {
        printf("No se pudo crear el archivo de salida para %s.\n", filename);
        return;
    }

    for (int a = 0; a < 3200; a++) {
        // Escribe un solo byte en el archivo
        fwrite(&bytes[0 + a], sizeof(unsigned char), 1, archivo_escritura);
        fwrite(&bytes[3200 + a], sizeof(unsigned char), 1, archivo_escritura);
        fwrite(&bytes[6400 + a], sizeof(unsigned char), 1, archivo_escritura);
        fwrite(&bytes[9600 + a], sizeof(unsigned char), 1, archivo_escritura);
        fwrite(&bytes[12800 + a], sizeof(unsigned char), 1, archivo_escritura);
        fwrite(&bytes[16000 + a], sizeof(unsigned char), 1, archivo_escritura);
    }
    
    fclose(archivo_escritura); // Cierra el archivo
}

int main() {
    DIR *dir;
    struct dirent *ent;
    int outputCount = 1; // Contador para los nombres de archivo de salida

    // Abre el directorio "Binarios"
    if ((dir = opendir("Binarios")) != NULL) {
        // Crea el directorio "Bin_out" si no existe
        system("mkdir -p Bin_out");

        // Lee todos los archivos en el directorio "Binarios"
        while ((ent = readdir(dir)) != NULL) {
            // Verifica si el archivo es de tipo .rgb
            if (strstr(ent->d_name, ".rgb") != NULL) {
                processRGBFile(ent->d_name, outputCount); // Procesa el archivo .rgb
                outputCount++; // Incrementa el contador para el próximo archivo
            }
        }
        closedir(dir); // Cierra el directorio
    } else {
        // No se pudo abrir el directorio "Binarios"
        perror("");
        return 1;
    }

    return 0;
}

