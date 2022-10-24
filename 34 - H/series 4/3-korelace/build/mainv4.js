"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    Object.defineProperty(o, k2, { enumerable: true, get: function() { return m[k]; } });
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const fs = __importStar(require("fs"));
let file = "inOut/05.";
fs.readFile(file + "in", "utf8", (err, inp) => {
    console.time("lol");
    if (err)
        throw err;
    let data = inp.split("\n").map(x => x.split(" "));
    data.pop();
    // console.log(data)
    let statementNum = Number(data[0][0]);
    let studyNum = Number(data[0][1]);
    data.shift();
    console.log(statementNum, studyNum);
    let statements = {};
    let ans = "";
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    let justInCase = 0;
    let num = 0;
    let dataLeft = [...data];
    let path = ["67621"];
    statements["67621"] = true;
    let key = "";
    let ind;
    let key2 = "";
    let lastOne = 0;
    while (ans.length < 1) {
        // console.time("lol2")
        num++;
        key = path[path.length - 1];
        ind = dataLeft.findIndex(x => x.includes(key));
        if (!(path.length % 1000)) {
            let temp = num - path.length;
            console.log("path length:", path.length, "iterations:", num, "paths removed since last log:", (temp - lastOne), "paths removed total:", (temp));
            lastOne = temp;
        }
        while (ind === -1) {
            path.pop();
            if (path.length === 0) {
                justInCase++;
                path.push(justInCase.toString());
            }
            key = path[path.length - 1];
            ind = dataLeft.findIndex(x => x.includes(key));
        }
        key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0];
        path.push(key2);
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd = path.indexOf(key2);
                ans = path.slice(startInd).join(" ");
                break;
            }
            else
                statements[key2] = statements[key];
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd = path.indexOf(key2);
                ans = path.slice(startInd).join(" ");
                break;
            }
            else
                statements[key2] = !statements[key];
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
    let ansLength = ans.split(" ").length;
    let writeOut = ansLength + "\n" + ans;
    console.log(ansLength, key2);
    // console.log(writeOut);
    fs.writeFile(file + "txt", writeOut, err => console.log(err));
    console.timeEnd("lol");
    return;
});
//# sourceMappingURL=mainv4.js.map