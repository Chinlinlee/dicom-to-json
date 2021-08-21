const dcm2json = require("../index");
const path=  require('path');

dcm2json(path.join(__dirname, "/000001.dcm") , function (json) {
    console.log(json);
})