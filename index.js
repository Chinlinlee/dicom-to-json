const dicomModule = require('bindings')("dcmtk.node");
module.exports.dcm2json = dicomModule.dcm2json;
module.exports.dcm2xml = dicomModule.dcm2xml;