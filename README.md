# dicom-to-json

The nodejs dcm2json native modules of dcmtk.

## Complier environment
- nodejs v14.15.0
### Windows
- Windows 10 64bits (vs 2019)

### Linux
- Ubuntu 20.04 (g++ 9.3.0)

## example
```dotnetcli
const dcm2json = require("../index");
const path=  require('path');

dcm2json(path.join(__dirname, "/000001.dcm") , function (json) {
    console.log(json);
})
```