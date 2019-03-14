class ProblemData(val minOfEachIngredient: Int, val maxSliceSize: Int, val rowNumber: Int, val columnNumber: Int) {

    val pizza: Array<Array<SliceContent>>

    enum class SliceContent {
        MUSHROOM, TOMATO, EMPTY
    }

    init {
        this.pizza = Array(rowNumber) { Array(columnNumber) { SliceContent.EMPTY } }
    }

    fun clone() : ProblemData {
        val toReturn = ProblemData(minOfEachIngredient, maxSliceSize, rowNumber, columnNumber)

        for (i in 0 until rowNumber){
            for (j in 0 until columnNumber){
                toReturn.pizza[i][j]=pizza[i][j]
            }
        }
        return toReturn
    }
}
