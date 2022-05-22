import * as fs from "fs";

let file = "inOut/05.";


fs.readFile(file + "in", "utf8", (err: any, inp: string) => {
    console.time("lol");
    if (err) throw err;
    let data: string[][] = inp.split("\n").map(x => x.split(" "))
    data.pop();
    // console.log(data)
    let statementNum: number = Number(data[0][0]);
    let studyNum: number = Number(data[0][1]);
    data.shift();
    console.log(statementNum, studyNum);
    let statements: {[key: string]: boolean | undefined} = {};
    let ans = "";
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    let justInCase: number = 0;
    let num: number = 0;
    let dataLeft = [...data];
    let path = ["67621"];
    statements["67621"] = true;
    let key: string = "";
    let ind: number; let key2: string = "";
    let lastOne: number = 0;
    while (ans.length < 1) {
        // console.time("lol2")
        num++;
        key = path[path.length-1];
        ind = dataLeft.findIndex(x => x.includes(key));
        if (!(path.length%1000)) {
            let temp: number = num-path.length;
            console.log("path length:", path.length, "iterations:", num, "paths removed since last log:", (temp-lastOne), "paths removed total:", (temp));
            lastOne = temp;
        }
        while (ind === -1)  {
            path.pop();
            if (path.length === 0) {
                justInCase++;
                path.push(justInCase.toString());
            }
            key = path[path.length-1];
            ind = dataLeft.findIndex(x => x.includes(key));
        }
        key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0];
        path.push(key2);
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd = path.indexOf(key2);
                ans = path.slice(startInd).join(" ");
                break
            }
            else statements[key2] = statements[key];
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd = path.indexOf(key2);
                ans = path.slice(startInd).join(" ");
                break;
            }
            else statements[key2] = !statements[key];
        }
        dataLeft.splice(ind, 1);
        // console.timeEnd("lol2")
        }
        // if (key in memo && memo[key] === key2) {
        //     console.log("memo")
        //     return "what"
        // } else {
        //     memo[key] = key2
        //     memo[key2] = key
        // }
    let ansLength: number = ans.split(" ").length;
    let writeOut: string = ansLength + "\n" + ans;
    console.log(ansLength, key2);
    // console.log(writeOut);
    fs.writeFile(file + "txt", writeOut, err => console.log(err));
    console.timeEnd("lol");
    return 
});
