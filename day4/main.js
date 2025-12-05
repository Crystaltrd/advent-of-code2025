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

let new_matrix = matrix;
let sum = 0;
do {
    matrix = new_matrix;
    new_matrix = matrix.map((x, i) => {
        if (x === '@') {
            if (nbr_adj(i, 10) < 4)
                return '.'
            else
                return '@'
        } else return '.';
    })
    if (sum === 0)
        console.log("Part 1 Solution: " + new_matrix.filter((x, i) => x !== matrix[i]).length);
    sum += new_matrix.filter((x, i) => x !== matrix[i]).length;
} while (new_matrix.filter((x, i) => x !== matrix[i]).length !== 0)
console.log("Part 2 Solution: "+sum)