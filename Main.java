import java.io.*;
public class Main {

    private static void lecturaPizza(String path) throws Exception {
        File file = new File(path);
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line = br.readLine();
        int numFotos= Integer.parseInt(line);
        HashMap<Integer,ArrayList<String>> listaHoriz = new HashMap<Integer,ArrayList<String>>();
        HashMap<Integer,ArrayList<String>> listaVertic = new HashMap<Integer,ArrayList<String>>();
        int i = 0;
        while ((line = br.readLine()) != null) {
            String lines=br.readLine();
            String[] chars=lines.split(" ");
            if( chars [0] == "H"){
                ArrayList<String> tags = new ArrayList<>();
                for (int j=1; j<= chars [2] +1 ;j++){
                    tags.add( chars [j+1]);
                }
                listaHoriz.put(i,tags);
            }
            else{
                ArrayList<String> tags = new ArrayList<>();
                for (int j=1; j<= chars [2] +1 ;j++){
                    tags.add( chars [j+1]);
                }
                listaVertic.put(i,tags);
            }
        }
    }

    private static void writeSolution(String path, int par1, int[] par2) throws Exception{
        BufferedWriter writer = new BufferedWriter(new FileWriter(path));
        writer.write(Integer.toString(par1) + "\n");
        for (int value : par2) {
            writer.write(Integer.toString(value) + " ");
        }
        writer.close();
    }

    public static void main(String[] args)throws Exception {
        String path = "inputs/a_example.in";
        lecturaPizza(path);
        writeSolution("outputs/a_example.out", 5, new int[]{1, 3, 5});
    }

}
