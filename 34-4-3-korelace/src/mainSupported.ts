import * as fs from "fs";

let file = "inOut/05short.";


fs.readFile(file + "txt", "utf8", (err: any, inp: string) => {
    console.time("lol");
    if (err) throw err;
    let data: string[][] = inp.split("\n").map(x => x.split(" "))
    data.pop();
    // console.log(data)
    let statementNum: number = Number(data[0][0]);
    let studyNum: number = Number(data[0][1]);
    let startNum: string = data[0][2];
    data.shift();
    console.log(statementNum, studyNum);
    let statements: {[key: string]: boolean | undefined} = {};
    let ans = "";
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    // let justInCase: number = 0;
    let num: number = 0;
    let dataLeft = [...data];
    let path = [startNum];
    statements[startNum] = true;
    let key: string = startNum;
    let ind: number; let key2: string = startNum;
    let lastOne: number = 0;
    while (ans.length < 1 && dataLeft.length > 0) {
        // console.time("lol2")
        num++;
        key = key2;
        ind = dataLeft.findIndex(x => x.includes(key));
        // console.log(path)
        if (!(path.length%1000)) {
            let temp: number = num-path.length;
            console.log("path length:", path.length, "iterations:", num, "paths removed since last log:", (temp-lastOne), "paths removed total:", (temp));
            lastOne = temp;
        }
        while (ind === -1)  {
            path.pop();
            if (path.length === 0) {
                return;
            }
            key = path[path.length-1];
            ind = dataLeft.findIndex(x => x.includes(key));
        }
        key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0];
        path.push(key2);
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd: number = path.lastIndexOf(key2, path.length-2);
                ans = path.slice(startInd).join(" ");
                break
            }
            else statements[key2] = statements[key];
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd: number = path.lastIndexOf(key2, path.length-2);
                ans = path.slice(startInd).join(" ");
                break;
            }
            else statements[key2] = !statements[key];
        }
        dataLeft.splice(ind, 1);
        // console.timeEnd("lol2")
        }
    let ansLength: number = ans.split(" ").length;
    let writeOut: string = ansLength + "\n" + ans;
    console.log(ansLength, key2);
    // console.log(writeOut);
    fs.writeFile(file + "txt", writeOut, err => console.log(err));
    console.timeEnd("lol");
    return 
});
