"use strict";
// import * as fs from "fs";
// let file = "inOut/05."
// fs.readFile(file + "in", "utf8", (err, inp: string) => {
//     if (err) throw err
//     let data: string[][] = inp.split("\n").map(x => x.split(" "))
//     data.pop()
//     // let statementNum: number = Number(data[0][0]);
//     // let studyNum: number = Number(data[0][1]);
//     data.shift();
//     // let statements: {[key: string]: [boolean | undefined, string[]]} = {};
//     console.log(data.filter(x => x.includes("25588")))
//     // let temp = [
//     //     [ '49979', '41', '-1' ],
//     //     [ '66545', '49979', '-1' ],
//     //     [ '38646', '66545', '1' ],
//     //     [ '92077', '38646', '1' ],
//     //     [ '79644', '92077', '-1' ],
//     //     [ '79644', '48193', '-1' ],
//     //     [ '8058', '48193', '1' ],
//     //     [ '59139', '8058', '1' ],
//     //     [ '59139', '79644', '-1' ],
//     //     [ '53', '51026', '-1' ],
//     //     [ '499', '51026', '1' ],
//     //     [ '499', '70882', '1' ],
//     //     [ '87051', '70882', '1' ],
//     //     [ '87051', '79666', '-1' ],
//     //     [ '68842', '79666', '-1' ],
//     //     [ '68842', '45817', '1' ],
//     //     [ '6497', '45817', '-1' ],
//     //     [ '6497', '68270', '1' ],
//     //     [ '68270', '74287', '1' ],
//     //     [ '85356', '74287', '-1' ],
//     //     [ '85356', '38808', '-1' ],
//     //     [ '38808', '1918', '-1' ],
//     //     [ '76045', '1918', '-1' ],
//     //     [ '73073', '76045', '1' ],
//     //     [ '50887', '73073', '1' ],
//     //     [ '50887', '81206', '-1' ],
//     //     [ '81206', '11062', '1' ],
//     //     [ '38646', '11062', '1' ]
//     //   ]
// }, );
let linebreak;
const recurse = (num = 0) => {
    context.num++;
    recurse(++num);
};
const context = {
    num: 0
};
try {
    recurse(context);
}
catch (e) {
    console.log('Took ' + context.num + ' trips before bailing');
}
//# sourceMappingURL=test.js.map