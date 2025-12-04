const input = `..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.`

let matrix = [...input.replaceAll("\n", "")]

function adjacents(i, ln) {
    let arr = [];
    if (i % ln !== 0) {
        arr.push(i - 1, i - ln - 1, i + ln - 1)
    }
    if (i % ln !== ln - 1) {
        arr.push(i + 1, i - ln + 1, i + ln + 1)
    }
    arr.push(i + ln, i - ln);
    return arr
}

function nbr_adj(i, ln) {
    return adjacents(i, ln).map((x) => {
        if (matrix[x] === '@') return 1; else return 0;
    }).reduce((acc, x) => acc += x, 0)
}

console.log(matrix.map((x, i) => {
    if (x === '@') return nbr_adj(i, 140)
    else return 67;
}).filter((x) => x < 4).length)