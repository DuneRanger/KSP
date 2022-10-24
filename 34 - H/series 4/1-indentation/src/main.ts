import * as fs from "fs";

let file = "inOut/00."

fs.readFile(file + "in", "utf8", (err, inp: string) => {
    let data: any = inp.split("\r\n");
    // let lines: number = Number(data[0]);
    data.shift();
    let indentations: number[] = [];
    let ans: number = 0;
    let temp: number = 0;
    for (let x of data) {
        if (x[x.length-1] == ":") {temp++}
        else if (temp !== 0) {
            indentations.push(temp);
        }
    }
    temp = indentations.length-2;
    let pointer: number = indentations.length-2;
    let temp2: number[] = indentations.slice(pointer);
    let copy = [...indentations];
    while(true) {
        ans += copy[copy.length-1];
        for (let x = pointer; x < copy.length; x++) {
            copy[x] -= 1;
        }
        console.log(copy, temp, pointer, temp2, ans)
        if (copy[pointer] == 0) {
            for (let x: number = 0; x < temp2.length; x++) {
                copy[pointer+x] = temp2[x];
            }
            pointer--;
            if (pointer == temp) {
                temp -=1;
                copy = [...indentations];
                pointer = indentations.length-2;
            }
            temp2 = indentations.slice(pointer);
        }
        console.log(copy, temp, pointer, temp2, ans)
        if (copy[pointer] === 0 && pointer <= 0 ) break;
    }
    // console.log(data);
    // console.log(indentations);
});