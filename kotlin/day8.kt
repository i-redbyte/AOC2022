typealias Matrix<T> = List<List<T>>
typealias MutableMatrix<T> = MutableList<MutableList<T>>

fun <T, R> Matrix<T>.mapMatrixIndexed(modify: (Int, Int, T) -> R): Matrix<R> =
    this.mapIndexed { i, row -> row.mapIndexed { j, col -> modify(i, j, col) } }

fun <T> Matrix<T>.getRowToEnd(row: Int, col: Int): List<List<T>> =
    this[row].let { listOf(it.subList(0, col), it.subList(col + 1, it.size)) }

fun <T> Matrix<T>.getColumn(col: Int): List<T> = getCol(this, col)

fun <T> Matrix<T>.count(predicate: (T) -> Boolean) = this.sumOf { it.count(predicate) }

fun <T> Matrix<T>.getPlaceToEnd(row: Int, col: Int) = getColumnToEnd(row, col) + getRowToEnd(row, col)

fun <T> Matrix<T>.getColumnToEnd(row: Int, col: Int): List<List<T>> =
    this.getColumn(col).let { listOf(it.subList(0, row), it.subList(row + 1, it.size)) }

fun <T> getCol(array: List<List<T>>, col: Int): List<T> {
    val rows = array.size
    val column = mutableListOf<T>()
    (0 until rows).forEach {
        try {
            column.add(array[it][col])
        } catch (_: IndexOutOfBoundsException) {
        }
    }
    return column
}

fun <T> matrixOf(rows: List<List<T>>): Matrix<T> = List(rows.size) { i -> rows[i] }

fun main() {
    val input = readInput("day8")
    val forest = matrixOf(input.map { row -> row.map { it.digitToInt() } })
    println("Solution:")
    println("Part 1: ${solution1(forest)}")

}

fun solution1(forest: Matrix<Int>) =
    forest.mapMatrixIndexed { i, j, tree ->
        forest.getPlaceToEnd(i, j).any { it.isEmpty() || it.all { t -> t < tree } }
    }.count { it}

