ffmpeg -i video.mp4 -r 12 -s 160x120 -f image2 Fotogramas/Fot%01d.png
carpeta="/home/jhonny/Documents/Pruebas_RGB_Binario_Video/Fotogramas"
if [ -d "$carpeta" ]; then
    # Bucle for para recorrer los archivos en la carpeta
    for archivo in "$carpeta"/*.png  # Cambiar la extensión según el tipo de archivo
    do
        if [ -f "$archivo" ]; then
            nombre_archivo=$(basename "$archivo")
            nombre_sin_extension="${nombre_archivo%.*}"  # Obtener el nombre sin la extensión

            # Ejecutar el comando ffmpeg con cada archivo de imagen
            ffmpeg -vcodec png -i "$archivo" -vcodec rawvideo -f rawvideo -pix_fmt rgb8 "Binarios/${nombre_sin_extension}.rgb"
        fi
    done
else
    echo "La ruta especificada no es un directorio válido."
fi

gcc -o Organiza Organiza_Todo.c 
./Organiza
#rm -r Fotogramas/*
#rm -r Binarios/*

