import com.sun.deploy.util.ArrayUtil;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

import static java.lang.Math.abs;

public class Main {

    static void shuffleArray(int[] ar)
    {
        // If running on Java 6 or older, use `new Random()` on RHS here
        Random rnd = ThreadLocalRandom.current();
        for (int i = ar.length - 1; i > 0; i--)
        {
            int index = rnd.nextInt(i + 1);
            // Simple swap
            int a = ar[index];
            ar[index] = ar[i];
            ar[i] = a;
        }
    }

    private static void lecturaPizza(String path) throws Exception {
        File file = new File(path);
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line = br.readLine();
        int numFotos= Integer.parseInt(line);
        HashMap<Integer,ArrayList<String>> listaHoriz = new HashMap<Integer,ArrayList<String>>();
        HashMap<Integer,ArrayList<String>> listaVertic = new HashMap<Integer,ArrayList<String>>();
        int i = 0;
        while ((line = br.readLine()) != null) {
            String[] chars=line.split(" ");
            if( chars [0] .equals("H")){
                ArrayList<String> tags = new ArrayList<>();
                for (int j=0; j< Integer.parseInt(chars[1]);j++){
                    tags.add( chars [j+2]);
                }
                listaHoriz.put(i,tags);
            }
            else{
                ArrayList<String> tags = new ArrayList<>();
                for (int j=0; j< Integer.parseInt(chars[1]);j++){
                    tags.add(chars[j+2]);
                }
                listaVertic.put(i,tags);
            }
            i++;
        }
        int total= listaHoriz.size()+(listaVertic.size()/2);
        int[] slices= new int[listaHoriz.size()];
        i=0;
        for ( int iter: listaHoriz.keySet()){
                slices[i] = iter;
                i++;
        }
        int[] slices2= new int[listaVertic.size()];
        ArrayList<int[]> parejas = agrupaVerticales(listaVertic);
        i=0;
        for ( int iter: listaVertic.keySet()){
            slices2[i] = iter;
            i++;
        }
        ArrayList<Integer> slices3 = new ArrayList<>();
        for (int x=0; x<slices2.length; ++x) {
            if(slices2[x]!=0) {
                slices3.add(slices2[x]);
            }
        }
        //writeSolution("outputs/e.out", total, slices,slices2);
        writeSolutionBETA("outputs/dBETA.out", parejas.size()+slices.length+slices3.size()/2, slices,parejas,slices3);
    }

    private static <T> List<T> intersection(List<T> list1, List<T> list2) {
        List<T> list = new ArrayList<T>();

        for (T t : list1) {
            if(list2.contains(t)) {
                list.add(t);
            }
        }

        return list;
    }

    private static ArrayList<int[]> agrupaVerticales(HashMap<Integer,ArrayList<String>> listaVertic) {
        int j;
        int diferenciapar = 16;
        int diferenciaimpar = 17;
        int limiteinterseccion;
        boolean found = false;
        Integer tam2;
        Integer tam;
        ArrayList<int[]> parejas = new ArrayList<>();
        ArrayList<String> chars ;
        ArrayList<String> chars2;
        int iter = 0;
        while (iter < listaVertic.size()) {
            chars = listaVertic.get(iter);
            if (chars!=null)tam = chars.size();
            else tam = null;
            j = iter + 1;
            if (tam != null && tam % 2 == 0) {
                while (!found) {
                    chars2 = listaVertic.get(j);
                    if (chars2 != null) tam2 = chars2.size();
                    else tam2 = null;
                    if ( tam2 != null&& tam2 % 2 == 0) {
                        if (abs(tam2 - tam) < diferenciapar && !found) {
                            if (tam > tam2) limiteinterseccion = tam / 16;
                            else limiteinterseccion = tam2 / 16;
                            int taminter = intersection(chars, chars2).size();
                            if (taminter < limiteinterseccion) {
                                parejas.add(new int[]{iter, j});
                                listaVertic.remove(iter);
                                listaVertic.remove(j);
                                found = true;
                            }
                        }
                    }
                    j += 1;
                    if (j == listaVertic.size()) found = true;
                }
            } else {
                if (tam!=null) {
                    while (!found) {
                        chars2 = listaVertic.get(j);
                        if (chars2 != null) tam2 = chars2.size();
                        else tam2 = null;
                        if (tam2 != null && tam2 % 2 != 0) {
                            if (abs(tam2 - tam) < diferenciaimpar && !found) {
                                if (tam > tam2) limiteinterseccion = tam / 16;
                                else limiteinterseccion = tam2 / 16;
                                int taminter = intersection(chars, chars2).size();
                                if (taminter < limiteinterseccion) {
                                    parejas.add(new int[]{iter, j});
                                    listaVertic.remove(iter);
                                    listaVertic.remove(j);
                                    found = true;
                                }
                            }
                        }
                        j += 1;
                        if (j == listaVertic.size()) found = true;
                    }
                }
            }
            found = false;
            iter++;
        }
        return parejas;
    }

    private static void writeSolution(String path, int par1, int[] par2, int[] par3) throws Exception{
        BufferedWriter writer = new BufferedWriter(new FileWriter(path));
        writer.write(Integer.toString(par1) + "\n");
        for (int value : par2) {
            writer.write(Integer.toString(value) + "\n");
        }
        int paridad=0;
        for (int value : par3) {
            if(paridad ==0){
                writer.write(Integer.toString(value) + " ");
                paridad=1;
            }
            else{
                writer.write(Integer.toString(value) + "\n");
                paridad=0;
            }
        }
        writer.close();
    }
    private static void writeSolutionBETA(String path, int par1, int[] par2,  ArrayList<int[]> par3, ArrayList<Integer> par4) throws Exception{
        BufferedWriter writer = new BufferedWriter(new FileWriter(path));
        System.out.println(par1);
        writer.write(Integer.toString(par1) + "\n");
        shuffleArray(par2);
        shuffleArray(par2);
        shuffleArray(par2);
        for (int value : par2) {
            writer.write(Integer.toString(value) + "\n");
        }
        for (int[] value : par3) {
                writer.write(Integer.toString(value[0]) + " " + Integer.toString(value[1]) + "\n");
        }
        int paridad=0;
        for (int value : par4) {
                if (paridad == 0) {
                    writer.write(Integer.toString(value) + " ");
                    paridad = 1;
                } else {
                    writer.write(Integer.toString(value) + "\n");
                    paridad = 0;
                }
        }
        writer.close();
    }

    public static void main(String[] args)throws Exception {
        String path = "inputs/d_pet_pictures.txt";
        lecturaPizza(path);
        //writeSolution("outputs/a_example.out", 5, new int[]{1, 3, 5});
    }

}
