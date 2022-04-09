const { dcm2json } = require("../index");
const path=  require('path');

dcm2json(path.join(__dirname, "/0003.dcm") , function (json) {
    console.log(json);
});
