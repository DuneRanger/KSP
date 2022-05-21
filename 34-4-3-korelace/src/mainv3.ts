import * as fs from "fs";

let file = "inOut/05."

fs.readFile(file + "in", "utf8", (err, inp: string) => {

    let data: string[][] = inp.split("\n").map(x => x.split(" "))
    data.pop()
    // console.log(data)
    let statementNum: number = Number(data[0][0]);
    let studyNum: number = Number(data[0][1]);
    data.shift();
    console.log(statementNum, studyNum);
    let statements: {[key: string]: boolean | undefined} = {};
    let ans = "Something went wrong"
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    let memo: any = {}
    let num: number = 0;
    let temp: number = 0;
    function findNextStudy(dataLeft: string[][], path: string[]): string {
        num++
        let key = path[path.length-1]
        let ind = dataLeft.findIndex(x => x.includes(key));
        if (ind === -1)  {
            num--
            return "false"
        }
        if (path.length > 5000 || num > 5000 || path.length == 0) {
            num--
            return "what"
        }
        // while (ind === -1) {
        //     console.log("Couldn't find " + key + "\nNow searching " + path[path.length-2] + " again\t"
        //     + path.length + "\t" + num)
        //     path.pop();
        //     key = path[path.length-1];
        //     ind = dataLeft.findIndex(x => x.includes(key));
        // }
        let key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0]
        if (key in memo && memo[key] === key2) {
            console.log("memo")
            return "what"
        } else {
            memo[key] = key2
            memo[key2] = key
        }
        path.push(key2)
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd = path.indexOf(key2);
                console.log("Got here")
                ans = path.slice(startInd).join(" ")
                num--
                return "true"
            }
            statements[key2] = statements[key]
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd = path.indexOf(key2);
                console.log("Got here")
                ans = path.slice(startInd).join(" ")
                num--
                return "true"
            }
            statements[key2] = !statements[key]
        }
        dataLeft.splice(ind, 1)
        let i = findNextStudy(dataLeft, path)
        while (i === "false") {
            // console.log("Couldn't find " + key2 + "\nNow searching " + path[path.length-2] + " again\t"
            // + path.length + "\t" + num)
            path.pop()
            i = findNextStudy(dataLeft, path);
        }
        if (i === "what") {
            num--
            // console.log(num);
            if (num === 1) {
                temp++;
                statements[temp] = true;
                console.log("Starting again at " + temp)
                for (let x in statements) {
                    statements[x] = undefined
                }
                i = findNextStudy(data, [temp.toString()])
            }
            else return "what"
        }
        num--
        console.log("What")
        return "true"
    }
    statements[temp] = true;
    try {
        findNextStudy(data, [temp.toString()])
        console.log("TEST1")
    } catch(e) {
        console.log(e)
        console.log("TEST2")
    } finally {
        let ansLength = ans.split(" ").length
        let writeOut: string = ansLength + "\n" + ans;
        console.log("TEST3")
        // console.log(ans);
        console.log(writeOut);
        // fs.writeFile(file + "txt", writeOut, err => console.log(err));
    }
});