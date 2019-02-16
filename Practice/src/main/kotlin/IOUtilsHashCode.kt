import java.io.File
import java.io.FileNotFoundException
import java.io.IOException
import java.nio.file.Files
import java.nio.file.Paths
import java.util.Scanner

object IOUtilsHashCode {
    @Throws(FileNotFoundException::class)
    internal fun loadInput(fileName: String): ProblemData {
        val scanner = Scanner(File(fileName))

        val rowNumber = scanner.nextInt()
        val columnNumber = scanner.nextInt()
        val minOfEachIngredient = scanner.nextInt()
        val maxSliceSize = scanner.nextInt()

        val problemData = ProblemData(minOfEachIngredient, maxSliceSize, rowNumber, columnNumber)

        // Read \n
        scanner.nextLine()

        for (i in 0 until problemData.rowNumber) {

            val actualLine = scanner.nextLine()
            for (j in 0 until actualLine.length) {
                val c = actualLine[j]
                when (c) {
                    'T' -> problemData.pizza[i][j] = ProblemData.SliceContent.TOMATO
                    'M' -> problemData.pizza[i][j] = ProblemData.SliceContent.MUSHROOM
                }
            }
        }
        return problemData
    }


    @Throws(IOException::class)
    internal fun saveOutput(toSave: OutputData, fileName: String) {
        var resultString = "${toSave.result.size}\n"
        for (i in toSave.result) {
            resultString = "$resultString${i.startRow} ${i.startColumn} ${i.endRow} ${i.endColumn}\n"
        }
        Files.write(Paths.get(fileName), resultString.toByteArray())
    }

    fun obtainScore(toSave: OutputData): Int {
        return toSave.result.fold(0) { acc, actual -> acc + actual.score }
    }
}
