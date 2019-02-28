import java.io.*;
public class Main {

    private static void lecturaPizza(String path) throws Exception {
        File file = new File(path);
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line = br.readLine();
        String[] first = line.split(" ");
        int rowNumber = Integer.parseInt(first[0]);
        int colNumber = Integer.parseInt(first[1]);
        int minIngredient = Integer.parseInt(first[2]);
        int maxCells = Integer.parseInt(first[3]);
        int[][] pizza = new int[rowNumber][colNumber];
        int i = 0;
        while ((line = br.readLine()) != null) {
            for (int j = 0; j < line.length(); j++) {
                char c = line.charAt(j);
                if (c == 'T') {
                    pizza[i][j] = 0;
                } else {
                    pizza[i][j] = 1;
                }
            }
            i += 1;
        }
        for (int[] row : pizza)
        {
            for (int value : row)
            {
                System.out.print(value);
            }
            System.out.println("");
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
