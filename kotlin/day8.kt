typealias Matrix<T> = List<List<T>>
typealias MutableMatrix<T> = MutableList<MutableList<T>>

val forest: Matrix<Int> = matrixOf(readInput("day8").map { row -> row.map { it.digitToInt() } })

fun main() {
    println("Solution:")
    println("Part 1: ${solution1()}")
    println("Part 2: ${solution2()}")

}

fun solution1() =
    forest.mapMatrixIndexed { i, j, tree ->
        forest.getPlaceToEnd(i, j).any { it.isEmpty() || it.all { t -> t < tree } }
    }.count { it }

fun solution2(): Int = forest.mapMatrixIndexed { i, j, tree -> calcViewScore(i, j, tree) }.matrixMax()

private fun <T, R> Matrix<T>.mapMatrixIndexed(modify: (Int, Int, T) -> R): Matrix<R> =
    this.mapIndexed { i, row -> row.mapIndexed { j, col -> modify(i, j, col) } }

private fun <T> Matrix<T>.getRowToEnd(row: Int, col: Int): Matrix<T> =
    this[row].let { listOf(it.subList(0, col), it.subList(col + 1, it.size)) }

private fun <T> Matrix<T>.getColumn(col: Int): List<T> = getColumnMatrix(this, col)

private fun <T> Matrix<T>.count(predicate: (T) -> Boolean) = this.sumOf { it.count(predicate) }

private fun <T> Matrix<T>.getPlaceToEnd(row: Int, col: Int) = getColumnToEnd(row, col) + getRowToEnd(row, col)

private fun <T> Matrix<T>.getColumnToEnd(row: Int, col: Int): Matrix<T> =
    this.getColumn(col).let { listOf(it.subList(0, row), it.subList(row + 1, it.size)) }

private fun <T : Comparable<T>> Matrix<T>.matrixMax(): T = this.mapNotNull { it.maxOrNull() }.maxOrNull()!!

private fun <T> getColumnMatrix(array: Matrix<T>, col: Int): List<T> {
    val rows = array.size
    val column = mutableListOf<T>()
    (0 until rows).forEach {
        try {
            column.add(array[it][col])
        } catch (_: IndexOutOfBoundsException) { /* no-op */
        }
    }
    return column
}

private fun <T> matrixOf(rows: Matrix<T>): Matrix<T> = List(rows.size) { i -> rows[i] }

private operator fun <T> Matrix<T>.get(p: Place): T = this[p.y][p.x]

private fun calcViewScore(row: Int, col: Int, tree: Int): Int =
    Place.ways.map { look(Place(col, row), it, tree) }.reduce(Int::times)

private fun look(place: Place, way: Place, tree: Int): Int {
    val next =  way + place
    return try {
        if (forest[next] < tree)
            1 + look(next, way, tree)
        else 1
    } catch (ex: IndexOutOfBoundsException) {
        0
    }
}


data class Place(var x: Int, var y: Int) {
    operator fun times(n: Int) = Place(x * n, y * n)
    operator fun plus(other: Place) = Place(other.x + x, other.y + y)

    companion object {
        val LEFT = Place(-1, 0)
        val RIGHT = Place(1, 0)
        val UP = Place(0, -1)
        val DOWN = Place(0, 1)
        val ways = listOf(RIGHT, DOWN, LEFT, UP)
    }
}