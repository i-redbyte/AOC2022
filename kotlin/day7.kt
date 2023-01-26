private data class Dir(val name: String, val parent: Dir?) {
    val files = mutableMapOf<String, Int>()
    val subDir = mutableSetOf<Dir>()
    val size: Int by lazy { subDir.sumOf { it.size } + files.values.sum() }
}

private const val TOTAL_DISK_SPACE = 70000000
private const val UNUSED_SPACE = 30000000
private const val AT_MOST_SIZE = 100000

fun main() {
    val dirs = createFileSystem(readInput("day7"))
    solution(dirs)
}

private fun solution(dirs: Set<Dir>) {
    println("Part #1:\n\t\t${dirs.filter { it.size <= AT_MOST_SIZE }.sumOf { it.size }}")

    val spaceStillNeeded = UNUSED_SPACE - (TOTAL_DISK_SPACE - dirs.first().size)
    println("Part #2:\n\t\t${dirs.filter { it.size >= spaceStillNeeded }.minByOrNull { it.size }?.size}")
}

private fun createFileSystem(data: List<String>): Set<Dir> {
    val fs = Dir("/", null)
    val dirs = mutableSetOf(fs)
    var currentDir = fs
    data.forEach {
        if (it.first().isDigit()) {
            val commandLineComposition = it.split(" ")
            currentDir.files[commandLineComposition.last()] = commandLineComposition.first().toInt()
            return@forEach
        }
        if (it.startsWith("dir")) {
            val commandLineComposition = it.split(" ")
            val newDir = Dir(commandLineComposition.last(), currentDir)
            currentDir.subDir.add(newDir)
            dirs.add(newDir)
            return@forEach
        }
        if (it == "$ cd ..") {
            currentDir = currentDir.parent ?: throw NullPointerException()
            return@forEach
        }
        if (it == "$ cd /" || it == "$ ls") {
            return@forEach
        }
        if (it.startsWith("$ cd ")) {
            val name = it.split(" ").last()
            currentDir = currentDir.subDir.find { dir -> dir.name == name } ?: throw NullPointerException()
            return@forEach
        }
    }
    return dirs
}


