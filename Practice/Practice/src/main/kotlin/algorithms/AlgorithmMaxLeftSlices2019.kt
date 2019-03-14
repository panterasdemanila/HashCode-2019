package algorithms

import OutputData
import ProblemData
import Slice
import java.util.ArrayList
import kotlin.math.abs

object AlgorithmMaxLeftSlices2019 : SolverAlgorithm {
    private fun obtainAvailableSlices(problemData: ProblemData): List<Slice> {
        val result = ArrayList<Slice>()

        for (i in 1 until problemData.maxSliceSize + 1) {
            for (j in 1 until problemData.maxSliceSize + 1) {
                if (i * j >= 2 * problemData.minOfEachIngredient && i * j <= problemData.maxSliceSize) {
                    result.add(Slice(endColumn = j - 1, endRow = i - 1))
                }

            }
        }
        result.sortWith(compareBy { it.score })
        result.reverse()

        return result
    }

    private fun canSlice(
        pizza: Array<Array<ProblemData.SliceContent>>,
        slice: Slice,
        problemData: ProblemData
    ): Boolean {
        if (slice.endRow >= problemData.rowNumber || slice.endColumn >= problemData.columnNumber) return false
        else {
            var mushroomCount = 0
            var tomatoCount = 0
            for (i in slice.startRow..slice.endRow) {
                for (j in slice.startColumn..slice.endColumn) {
                    when (pizza[i][j]) {
                        ProblemData.SliceContent.EMPTY -> return false
                        ProblemData.SliceContent.MUSHROOM -> ++mushroomCount
                        ProblemData.SliceContent.TOMATO -> ++tomatoCount
                    }
                }
            }
            return mushroomCount >= problemData.minOfEachIngredient && tomatoCount >= problemData.minOfEachIngredient
        }
    }

    private fun doSlice(
        pizza: Array<Array<ProblemData.SliceContent>>,
        slice: Slice
    ) {
        for (i in slice.startRow..slice.endRow) {
            for (j in slice.startColumn..slice.endColumn) {
                pizza[i][j] = ProblemData.SliceContent.EMPTY
            }
        }
    }

    fun heuristic(
        slice: Slice,
        leftSlices: HashSet<Slice>
    ): Int {
        return leftSlices.count{!it.overlaps(slice)}
    }

    override fun algorithm(problemData: ProblemData): OutputData {
        val outputData = OutputData()
        val posibleSlices = obtainAvailableSlices(problemData)

        val allPosibleSlices = HashSet<Slice>()

        var numberMushroom = 0
        var numberTomatos = 0

        // Obtain all slices
        for (actualRow in 0 until problemData.rowNumber ) {
            for (actualColumn in 0 until problemData.columnNumber) {
                for (actualPosibleSlice in posibleSlices) {
                    val actualSlice = Slice(
                        actualPosibleSlice.startRow + actualRow, actualPosibleSlice.startColumn + actualColumn,
                        actualPosibleSlice.endRow + actualRow, actualPosibleSlice.endColumn + actualColumn
                    )
                    if (canSlice(problemData.pizza, actualSlice, problemData)) {
                        allPosibleSlices.add(actualSlice)
                    }
                }
                if (problemData.pizza[actualRow][actualColumn] == ProblemData.SliceContent.MUSHROOM) ++numberMushroom
                else ++numberTomatos
            }
        }

        while (allPosibleSlices.isNotEmpty()) {
            val actualMax = allPosibleSlices.maxBy { heuristic(it, allPosibleSlices) }

            var mushroomsTakens = 0
            var tomatoTakens = 0

            for (i in actualMax!!.startRow..actualMax.endRow) {
                for (j in actualMax.startColumn..actualMax.endColumn) {
                    if (problemData.pizza[i][j] == ProblemData.SliceContent.MUSHROOM) ++tomatoTakens
                    else ++mushroomsTakens
                }
            }

            numberMushroom -= mushroomsTakens
            numberTomatos -= tomatoTakens

            doSlice(problemData.pizza, actualMax)
            outputData.result.add(actualMax)
            allPosibleSlices.removeAll { it.isValid(problemData) }
        }

        return outputData
    }

}