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
    let data = inp.split("\n").map(x => x.split(" "));
    data.pop();
    console.log(data);
    let statementNum = Number(data[0][0]);
    let studyNum = Number(data[0][1]);
    data.shift();
    console.log(statementNum, studyNum);
    let statements = {};
    let ans = "";
    for (let i = 0; i < statementNum; i++) {
        statements[i] = undefined;
    }
    let memo = {};
    function findNextStudy(originalKey, key, dataLeft, path = originalKey) {
        let ind = dataLeft.findIndex(x => x.includes(key));
        if (ind === -1) {
            return false;
        }
        // if (dataLeft.findIndex(x => x.includes(originalKey)) === -1) { console.log("This works"); return false }
        let key2 = dataLeft[ind][0] === key ? dataLeft[ind][1] : dataLeft[ind][0];
        if (key in memo && memo[key] === key2) {
            console.log("This works");
            return false;
        }
        else {
            memo[key] = key2;
            memo[key2] = key;
        }
        path += " " + key2;
        if (dataLeft[ind][2] === "1") {
            if (statements[key2] !== undefined && statements[key2] !== statements[key]) {
                let startInd = path.indexOf(key2);
                console.log(path.slice(startInd));
                ans = path.slice(startInd);
                return true;
            }
            statements[key2] = statements[key];
        }
        else {
            if (statements[key2] !== undefined && statements[key2] === statements[key]) {
                let startInd = path.indexOf(key2);
                console.log(path.slice(startInd));
                ans = path.slice(startInd);
                return true;
            }
            statements[key2] = !statements[key];
        }
        dataLeft.splice(ind, 1);
        // if (Number(key) < Number(originalKey)) return false
        findNextStudy(originalKey, key2, dataLeft, path);
        return false;
    }
    for (let i in statements) {
        console.log(i);
        statements[i] = true;
        // console.log(i, Object.keys(memo).length)
        findNextStudy(i, i, [...data]);
        if (ans.length > 1) {
            break;
        }
        // for (let i = 0; i < statementNum; i++) {
        //     statements[i] = undefined;
        // }
    }
    let ansLength = ans.split(" ").length;
    let writeOut = ansLength + "\n" + ans;
    console.log(ans);
    fs.writeFile(file + "txt", writeOut, err => console.log(err));
});
//# sourceMappingURL=main.js.map