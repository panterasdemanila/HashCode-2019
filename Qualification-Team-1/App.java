
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

// Definicion de entidades

class Photo {
    private int id;
    private String orientation;
    private ArrayList<String> tagsList;

    Photo(int id, String orientation, ArrayList<String> tagsList) {
        this.id = id;
        this.orientation = orientation;
        this.tagsList = tagsList;
    }

    int tagsNumber() {
        return tagsList.size();
    }

    int score(Photo p) {
        List<String> common = new ArrayList<>(tagsList);
        common.retainAll(p.tagsList);
        int common_min = Math.min(p.tagsList.size() - common.size(), tagsList.size() - common.size());
        return Math.min(common_min, common.size());
    }

    String getOrientation() {
        return orientation;
    }

    int getId() {
        return id;
    }

}

class Slide {
    private Photo photo1;
    private Photo photo2;

    Slide(Photo photo1) {
        this.photo1 = photo1;
    }

    Slide(Photo photo1, Photo photo2) {
        this.photo1 = photo1;
        this.photo2 = photo2;
    }

    int score(Slide b) {
        // TODO: Cambiar para soportar verticales
        return photo1.score(b.photo1);
    }

    @Override
    public String toString() {
        String salida = Integer.toString(photo1.getId());
        if (photo2 != null) {
            salida = salida.concat(" " + photo2.getId());
        }
        return salida.concat("\n");
    }
}

public class App {

    public static void main(String[] args) throws Exception {
        //String fichero = "c_memorable_moments";
        String fichero = "b_lovely_landscapes";
        //String fichero = "d_pet_pictures";
        //
        //
        //String fichero = "e_shiny_selfies";

        // Leer Fichero Entrada
        String fileString = readFileAsString("./entradas/" + fichero + ".txt");
        System.out.println("    ---> readFileAsString: ");
        System.out.println(fileString);

        // Separar String por Saltos de Línea
        List<String> stringArray = splitString(fileString, "\n");
        System.out.println("    ---> splitStringBySeparator: ");

        List<Photo> photoList = new ArrayList<Photo>();

        for (int i = 1; i < stringArray.size(); i++) {
            String string = stringArray.get(i);
            List<String> listaElementos = splitString(string, " ");
            photoList.add(new Photo(i - 1, listaElementos.get(0), new ArrayList<>(listaElementos.subList(2, listaElementos.size()))));
        }

        ArrayList<Slide> salida = new ArrayList<>();

        /**
         *
         * Algoritmo
         *
         * */

        photoList.sort(Comparator.comparingInt(Photo::tagsNumber));


        Photo last_photo = photoList.get(0);

        int divisiones = 8;
        int partition_size = photoList.size() / divisiones;

        for (int iter = 0; iter < divisiones; ++iter) {

            HashSet<Photo> horizontals = new HashSet<>(photoList.subList(iter * partition_size, (iter + 1) * partition_size - 1));

            horizontals.remove(last_photo);

            while (!horizontals.isEmpty()) {

                Photo mejor = last_photo;
                int mejor_punt = -1;
                for (Photo internal_photo : horizontals) {
                    int mm = last_photo.score(internal_photo);
                    if (mejor_punt < mm) {
                        mejor = internal_photo;
                        mejor_punt = mm;
                    }
                }

                last_photo = mejor;

                horizontals.remove(last_photo);
                salida.add(new Slide(last_photo));
                System.out.println(iter + "    " + horizontals.size());
            }

        }

        /**
         *
         * Salida
         *
         * */

        String string_output = salida.size() + "\n";

        for (Slide actual_slice : salida) {
            string_output = string_output.concat(actual_slice.toString());
        }

        saveFile(string_output, "./salidas/" + fichero + ".out");

        int punt_total = 0;

        Slide last_slide_score = salida.get(0);

        for (int i = 1; i < salida.size(); i++) {
            punt_total+= last_slide_score.score(salida.get(i));
            last_slide_score = salida.get(i);
        }

        System.out.println("Puntuación obtenida: " + punt_total);

    }

    private static String readFileAsString(String fileName) throws Exception {
        return  new String(Files.readAllBytes(Paths.get(fileName)));
    }

    private static void saveFile(String text, String fileName) throws Exception {
        PrintWriter out = new PrintWriter(fileName);
        out.println(text);
        out.close();
    }

    private static List<String> splitString(String string, String separator) {
        return Arrays.asList(string.split(separator));
    }
}
