class ProblemData(val minOfEachIngredient: Int, val maxSliceSize: Int, val rowNumber: Int, val columnNumber: Int) {

    val pizza: Array<Array<SliceContent>>

    enum class SliceContent {
        MUSHROOM, TOMATO, EMPTY
    }

    init {
        this.pizza = Array(rowNumber) { Array(columnNumber) { SliceContent.EMPTY } }
    }
}
