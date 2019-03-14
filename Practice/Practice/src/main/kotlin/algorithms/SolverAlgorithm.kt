package algorithms

import OutputData
import ProblemData

interface SolverAlgorithm {
    fun algorithm(problemData: ProblemData): OutputData
}