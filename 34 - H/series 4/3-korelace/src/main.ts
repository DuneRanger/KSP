import * as fs from "fs";

let file = "inOut/05."

fs.readFile(file + "in", "utf8", (err, inp: string) => {

    let data: string[][] = inp.split("\n").map(x => x.split(" "))
    data.pop()
    console.log(data)
    let statementNum: number = Number(data[0][0]);
    let studyNum: number = Number(data[0][1]);
    data.shift();
    console.log(statementNum, studyNum);
    let statements: {[key: string]: boolean | undefined} = {};
    let ans = ""
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    let memo: {[key: string]: string} = {}
    function findNextStudy(originalKey: string, key: string, dataLeft: string[][], path = originalKey): any {
        let ind = dataLeft.findIndex(x => x.includes(key));
        if (ind === -1) { return false }
        // if (dataLeft.findIndex(x => x.includes(originalKey)) === -1) { console.log("This works"); return false }
        let key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0]
        if (key in memo && memo[key] === key2) {
            console.log("This works")
            return false
        }
        else { memo[key] = key2; memo[key2] = key }
        path += " " + key2
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd = path.indexOf(key2);
                console.log(path.slice(startInd))
                ans = path.slice(startInd)
                return true
            }
            statements[key2] = statements[key]
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd = path.indexOf(key2);
                console.log(path.slice(startInd))
                ans = path.slice(startInd)
                return true
            }
            statements[key2] = !statements[key]
        }
        dataLeft.splice(ind, 1)
        // if (Number(key) < Number(originalKey)) return false
        findNextStudy(originalKey, key2, dataLeft, path)
        return false
    }
    for (let i in statements) {
        console.log(i)
        statements[i] = true
        // console.log(i, Object.keys(memo).length)
        findNextStudy(i, i, [...data])
        if (ans.length > 1) {
            break;
        }
        // for (let i = 0; i < statementNum; i++) {
        //     statements[i] = undefined;
        // }
    }
    let ansLength = ans.split(" ").length
    let writeOut: string = ansLength + "\n" + ans;
    console.log(ans);
    fs.writeFile(file + "txt", writeOut, err => console.log(err));
});