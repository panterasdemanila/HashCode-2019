// PARA EJECUTAR
// Instalar maven: https://maven.apache.org/install.html
// Ejecutar: mvn package && java -cp target/my-app-1.0-SNAPSHOT.jar com.mycompany.app.App

package com.mycompany.app;

import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// Definicion de entidades
class Entity {
    String value;

    Entity(String value) {
        this.value = value;
    }
}

public class App {

    public static void main(String[] args) throws Exception {
        // Leer Fichero Entrada
        String fileString = readFileAsString("/Users/cokelas/Documents/my-app/fileName.txt");
        System.out.println("    ---> readFileAsString: ");
        System.out.println(fileString);
        // Separar String por Saltos de Línea
        List<String> stringArray = splitString(fileString, "\n");
        System.out.println("    ---> splitStringBySeparator: ");
        for (String string : stringArray) {
            System.out.println(string);
        }
        // Creación de Entidades
        System.out.println("    ---> splitStringBySeparator (with Type Entity): ");
        for (String string : stringArray) {
            Entity entity = new Entity(string);
            System.out.println(entity.toString());
        }
        // Filtrar objetos de un array
        List<String> filteredArray = filterArrayExample(stringArray);
        System.out.println("    ---> filterArrayExample: ");
        for (String string : filteredArray) {
            System.out.println(string);
        }
        // Concatenar elementos de array con saltos de línea
        System.out.println("    ---> joinString: ");
        String result = joinString(filteredArray, "\n");
        System.out.println(result);
        // Guarda string en fichero
        System.out.println("    ---> saveFile: ");
        saveFile(result, "resultFile.txt");
    }

    public static List<String> filterArrayExample(List<String> array) {
        List<String> result = new ArrayList<>();
        for (String string : array) {
            if (!string.contains("foo")) {
                result.add(string);
            }
        }
        return result;
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

    public static String joinString(List<String> array, String joiner) {
        return String.join(joiner, array);
    }
}
