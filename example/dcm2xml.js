const { dcm2xml } = require("../index");
const path=  require('path');

dcm2xml(path.join(__dirname, "/0003.dcm") , function (json) {
    console.log(json);
})