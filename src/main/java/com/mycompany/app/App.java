// PARA EJECUTAR
// Instalar maven: https://maven.apache.org/install.html
// Ejecutar: mvn -Dmaven.test.skip=true install && java -cp target/my-app-1.0-SNAPSHOT.jar com.mycompany.app.App

package com.mycompany.app;

import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

// Definicion de entidades

class Photo {
    Number id;
    String orientation;
    int tagsNumber;
    ArrayList<String> tagsList = new ArrayList<String>();

    Photo(int id, String orientation, int tagsNumber, ArrayList<String> tagsList) {
        this.id = id;
        this.orientation = orientation;
        this.tagsNumber = tagsNumber;
        this.tagsList = tagsList;
    }
}

class Slide {
    private Integer photo1;
    private Integer photo2;

    Slide(Integer photo1, Integer photo2) {
        this.photo1 = photo1;
        this.photo2 = photo2;
    }

    @Override
    public String toString() {
        String salida = photo1.toString();
        if (photo2 != null){
            salida = salida.concat(" " + photo2);
        }
        return salida.concat("\n");
    }
}

public class App {

    public static void main(String[] args) throws Exception {
        String fichero = "a_example";

        // Leer Fichero Entrada
        String fileString = readFileAsString(fichero + ".txt");
        System.out.println("    ---> readFileAsString: ");
        System.out.println(fileString);

        // Separar String por Saltos de Línea
        List<String> stringArray = splitString(fileString, "\n");
        System.out.println("    ---> splitStringBySeparator: ");

        ArrayList<Photo> photoList = new ArrayList<Photo>();

        int i = 0;
        for (String string : stringArray) {
            if (i != 0) {
                List<String> listaElementos = splitString(string, " ");
                photoList.add(new Photo(i - 1, listaElementos.get(0), Integer.parseInt(listaElementos.get(1)), new ArrayList<>(listaElementos.subList(2, listaElementos.size()))));
            }
            i++;
        }

        ArrayList<Slide> salida = new ArrayList<>();

        for (Photo actual_photo : photoList) {
            if (actual_photo.orientation.equals("H")) {
                salida.add(new Slide(actual_photo.tagsNumber, null));
            }
        }

        String string_output = salida.size() + "\n";

        for (Slide actual_slice : salida) {
            string_output = string_output.concat(actual_slice.toString());
        }

        saveFile(string_output, fichero + ".out");
    }

    public static String readFileAsString(String fileName) throws Exception {
        String data = "";
        data = new String(Files.readAllBytes(Paths.get(fileName)));
        return data;
    }

    public static void saveFile(String text, String fileName) throws Exception {
        PrintWriter out = new PrintWriter(fileName);
        out.println(text);
        out.close();
    }

    public static List<String> splitString(String string, String separator) {
        return Arrays.asList(string.split(separator));
    }
}
