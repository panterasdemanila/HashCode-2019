import algorithms.AlgorithmMaxLeftSlices2019
import algorithms.AlgorithmSimplest2019

object Main {
    @Throws(Exception::class)
    @JvmStatic
    fun main(args: Array<String>) {
        val problemSetName ="c_medium" // a_example b_small c_medium d_big
        val problemData = IOUtilsHashCode.loadInput("./input/$problemSetName.in")
        val beforeTime = System.currentTimeMillis()
        val outputData = AlgorithmSimplest2019.algorithm(problemData)
        val afterTime = System.currentTimeMillis()
        IOUtilsHashCode.saveOutput(outputData, "./output/$problemSetName.out")
        println("Tiempo = ${afterTime - beforeTime}0 ms")
        println("Posible resultado: ${IOUtilsHashCode.obtainScore(outputData)}")
        println("Maximo resultado posible: ${problemData.rowNumber * problemData.columnNumber}")
    }
}
