class Slice(var startRow: Int = 0, var startColumn: Int = 0, var endRow: Int, var endColumn: Int) {

    val score: Int
        get() = (endRow - startRow + 1) * (endColumn - startColumn + 1)

    fun isValid(problemData: ProblemData): Boolean {
        if (endRow >= problemData.rowNumber || endColumn >= problemData.columnNumber) return false

        var numOfMushroom = 0
        var numOfTomato = 0

        for (i in startRow..endRow) {
            for (j in startColumn..endColumn) {
                when (problemData.pizza[i][j]) {
                    ProblemData.SliceContent.TOMATO -> ++numOfTomato
                    ProblemData.SliceContent.MUSHROOM -> ++numOfMushroom
                    else ->
                        // Posicion ocupada por otro slice
                        return false
                }
            }
        }

        return numOfMushroom >= problemData.minOfEachIngredient
                && numOfTomato >= problemData.minOfEachIngredient
                && numOfMushroom + numOfTomato <= problemData.maxSliceSize
    }
}
