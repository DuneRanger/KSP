import * as fs from "fs";

let file = "inOut/05."

fs.readFile(file + "in", "utf8", (err, inp: string) => {
    if (err) throw err
    let data: string[][] = inp.split("\n").map(x => x.split(" "))
    data.pop()
    let statementNum: number = Number(data[0][0]);
    let studyNum: number = Number(data[0][1]);
    data.shift();
    let statements: {[key: string]: [boolean | undefined, string[], any]} = {};
    let memo: {[key: string]: string} = {}
    let end: string[] = []
    let endKey: string = ""
    let terribleTemp: number = -1;
    let dataToWrite = new Set<string[]> ([]);
    function findNextStudy(originalKey: string, key: string, dataLeft: string[][], dataUsed: string[][] = []): any {
        let ind = dataLeft.findIndex(x => x.includes(key));
        if (ind === -1) { return false }
        // if (dataLeft.findIndex(x => x.includes(originalKey)) === -1) { console.log("This works"); return false }
        let key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0]
        if (statements[key2] === undefined) {
            statements[key2] = [undefined, dataLeft[ind], dataUsed]
        }
        if (key in memo && memo[key] === key2) {
            console.log("This works")
            return false
        }
        else { memo[key] = key2; memo[key2] = key }
        if (dataLeft[ind][2] === "1") {
            if (statements[key2][0] !== undefined && statements[key2][0] !== statements[key][0]) {
                console.log(dataLeft[ind])
                for (let x of dataUsed) {
                    if (!statements[key2][2].includes(x)) {
                        statements[key2][2].push(x)
                    }
                }
                statements[key2][2].push(dataLeft[ind])
                end = dataLeft[ind]
                endKey = key2
                terribleTemp = ind
                return true
            }
            statements[key2][0] = statements[key][0]
        }
        else {
            if (statements[key2][0] !== undefined && statements[key2][0] === statements[key][0]) {
                console.log(dataLeft[ind])
                for (let x of dataUsed) {
                    if (!statements[key2][2].includes(x)) {
                        statements[key2][2].push(x)
                    }
                }
                statements[key2][2].push(dataLeft[ind])
                end = dataLeft[ind]
                endKey = key2
                terribleTemp = ind
                return true
            }
            statements[key2][0] = !statements[key][0]
        }
        let temp: string[] = dataLeft.splice(ind, 1).flat()
        dataUsed.push(temp);
        dataToWrite.add(temp);
        // if (Number(key) < Number(originalKey)) return false
        findNextStudy(originalKey, key2, dataLeft, dataUsed)
        return false
    }
    for (let i = 0; i < statementNum; i++) {
        let n = i.toString();
        console.log(i)
        if (statements[i] === undefined) {
            let temp = data.find(x => x.includes(i.toString()))
            if (temp === undefined) { console.log("What the fuck", i); continue; }
            else statements[i] = [true, temp, data];
        }
        findNextStudy(n, n, [...data])
        if (end.length > 1) {
            break;
        }
    }
    console.log(statements[endKey][1], end)
    // let ans: string = "";
    // function terribleIdea(end: string[], key: string, dataLeft: string[][], path: string, tempKey = ""): any {
    //     if (tempKey.length > 1) {
    //         let ind = dataLeft.findIndex(x => x.includes(key) && x.includes(tempKey));
    //         dataLeft.splice(ind, 1)
    //         path += " " + tempKey
    //         terribleIdea(end, tempKey, dataLeft, path)
    //     }
    //     else {
    //         let toCheck = [...dataLeft].filter(x => x.includes(key));
    //         console.log(key)
    //         // if (ind === -1) { return false }
    //         for (let i of toCheck) {
    //             // console.log(i)
    //             let ind = dataLeft.findIndex(x => x.toString() === i.toString())
    //             let key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0];
    //             path += " " + key2
    //             if (dataLeft[ind].toString() === end.toString()) { ans = path; return console.log(path) }
    //             dataLeft.splice(ind, 1)
    //             terribleIdea(end, key2, dataLeft, path)
    //         }
    //         // if (dataLeft.findIndex(x => x.includes(originalKey)) === -1) { console.log("This works"); return false }
    //         // if (statements[key2] === undefined) {
    //         //     statements[key2] = [undefined, dataLeft[ind]]
    //         // }
    //         // if (dataLeft[ind][2] === "1") {
    //         //     if (statements[key2][0] !== undefined && statements[key2][0] !== statements[key][0]) {
    //         //         console.log(dataLeft[ind])
    //         //         end = dataLeft[ind]
    //         //         endKey = key2
    //         //         return true
    //         //     }
    //         //     statements[key2][0] = statements[key][0]
    //         // }
    //         // else {
    //         //     if (statements[key2][0] !== undefined && statements[key2][0] === statements[key][0]) {
    //         //         console.log(dataLeft[ind])
    //         //         end = dataLeft[ind]
    //         //         endKey = key2
    //         //         return true
    //         //     }
    //         //     statements[key2][0] = !statements[key][0]
    //         // }
    //     }
    //     return
    // }
    // function lazy(endKey: string, key: string, dataLeft: string[][], path: string) {
    //     let study = dataLeft[dataLeft.length-1];
    //     let key2 = study[0] === key ? study[1] : study[0];
    //     path += " " + key2
    //     dataLeft.pop()
    //     console.log(study)
    //     if (key2 === endKey) { ans = path; return console.log(path) }
    //     else lazy(endKey, key2, dataLeft, path)
    // }
    // terribleTemp = data.findIndex(x => x.toString() === end.toString())
    // let pleh = data[terribleTemp][0] === endKey ? data[terribleTemp][1] : data[terribleTemp][0]
    // console.log(statements[endKey][2], end, endKey, pleh)
    // terribleIdea(statements[endKey][1], pleh, [...statements[endKey][2]], pleh)
    // lazy(endKey, endKey, [...statements[endKey][2]], endKey)
    // let ansLength = ans.split(" ").length
    // let writeOut: string = ansLength + "\n" + ans;
    // console.log(ans);
    let dataString: string = statementNum + " " + studyNum + " " + endKey + "\n" 
    for (let x of dataToWrite) {
        dataString += x.join(" ") + "\n"
    }
    fs.writeFile("inOut/05short.txt", dataString, err => console.log(err));
});
