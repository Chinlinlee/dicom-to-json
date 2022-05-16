/*
 *
 *  Copyright (C) 2002-2021, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  dcmdata
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose: Convert the contents of a DICOM file to XML format
 *
 */


#include "dcmtk/config/osconfig.h"      /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/cmdlnarg.h"
#include "dcmtk/ofstd/ofstd.h"
#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/ofstd/ofconapp.h"

#ifdef WITH_ZLIB
#include <zlib.h>                       /* for zlibVersion() */
#endif
#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
#include "dcmtk/ofstd/ofchrenc.h"       /* for OFCharacterEncoding */
#endif

#define OFFIS_CONSOLE_APPLICATION "dcm2xml"
#define OFFIS_CONSOLE_DESCRIPTION "Convert DICOM file and data set to XML"

#define DOCUMENT_TYPE_DEFINITION_FILE "dcm2xml.dtd"

static OFLogger dcm2xmlLogger = OFLog::getLogger("dcmtk.apps." OFFIS_CONSOLE_APPLICATION);

static char rcsid[] = "$dcmtk: " OFFIS_CONSOLE_APPLICATION " v"
  OFFIS_DCMTK_VERSION " " OFFIS_DCMTK_RELEASEDATE " $";

// ********************************************
#include <assert.h>
#include <node_api.h>
#include "dcm2xml.h"

static OFCondition writeFile(STD_NAMESPACE ostream &out,
                             const char *ifname,
                             DcmFileFormat *dfile,
                             const E_FileReadMode readMode,
                             const OFBool loadIntoMemory,
                             const char *dtdFilename,
                             const char *defaultCharset,
                             /*const*/ size_t writeFlags,
                             const OFBool checkAllStrings)
{
    OFCondition result = EC_IllegalParameter;
    if ((ifname != NULL) && (dfile != NULL))
    {
        DcmDataset *dset = dfile->getDataset();
        if (loadIntoMemory)
            dset->loadAllDataIntoMemory();
        /* determine dataset character encoding */
        OFString encString;
        OFString csetString;
        if (dset->findAndGetOFStringArray(DCM_SpecificCharacterSet, csetString).good())
        {
            if (csetString == "ISO_IR 6")   // should never be present in a dataset, but ...
                encString = "UTF-8";
            else if (csetString == "ISO_IR 192")
                encString = "UTF-8";
            else if (csetString == "ISO_IR 100")
                encString = "ISO-8859-1";
            else if (csetString == "ISO_IR 101")
                encString = "ISO-8859-2";
            else if (csetString == "ISO_IR 109")
                encString = "ISO-8859-3";
            else if (csetString == "ISO_IR 110")
                encString = "ISO-8859-4";
            else if (csetString == "ISO_IR 148")
                encString = "ISO-8859-9";
            else if (csetString == "ISO_IR 144")
                encString = "ISO-8859-5";
            else if (csetString == "ISO_IR 127")
                encString = "ISO-8859-6";
            else if (csetString == "ISO_IR 126")
                encString = "ISO-8859-7";
            else if (csetString == "ISO_IR 138")
                encString = "ISO-8859-8";
            else {
                if (!csetString.empty())
                {
                    OFLOG_WARN(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": SpecificCharacterSet (0008,0005) "
                        << "value '" << csetString << "' not supported ... quoting non-ASCII characters");
#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
                    OFLOG_DEBUG(dcm2xmlLogger, "using option --convert-to-utf8 to convert the DICOM file to "
                        "UTF-8 encoding might also help to solve this problem more appropriately");
#endif
                }
                /* make sure that non-ASCII characters are quoted appropriately */
                writeFlags |= DCMTypes::XF_convertNonASCII;
            }
        } else {
            /* SpecificCharacterSet is not present in the dataset */
            if (dset->containsExtendedCharacters(checkAllStrings))
            {
                if (defaultCharset == NULL)
                {
                    /* the dataset contains non-ASCII characters that really should not be there */
                    OFLOG_ERROR(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": SpecificCharacterSet (0008,0005) "
                        << "element absent (on the main data set level) but extended characters used in file: " << ifname);
                    OFLOG_DEBUG(dcm2xmlLogger, "use option --charset-assume to manually specify an appropriate character set");
                    return makeOFCondition(OFM_dcmdata, EC_CODE_CannotSelectCharacterSet, OF_error, "Missing Specific Character Set");
                } else {
                    OFString sopClass;
                    csetString = defaultCharset;
                    /* use the default character set specified by the user */
                    if (csetString == "ISO_IR 192")
                        encString = "UTF-8";
                    else if (csetString == "ISO_IR 100")
                        encString = "ISO-8859-1";
                    else if (csetString == "ISO_IR 101")
                        encString = "ISO-8859-2";
                    else if (csetString == "ISO_IR 109")
                        encString = "ISO-8859-3";
                    else if (csetString == "ISO_IR 110")
                        encString = "ISO-8859-4";
                    else if (csetString == "ISO_IR 148")
                        encString = "ISO-8859-9";
                    else if (csetString == "ISO_IR 144")
                        encString = "ISO-8859-5";
                    else if (csetString == "ISO_IR 127")
                        encString = "ISO-8859-6";
                    else if (csetString == "ISO_IR 126")
                        encString = "ISO-8859-7";
                    else if (csetString == "ISO_IR 138")
                        encString = "ISO-8859-8";
                    else {
                        OFLOG_FATAL(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": Character set '"
                            << defaultCharset << "' specified with option --charset-assume not supported");
                        return makeOFCondition(OFM_dcmdata, EC_CODE_CannotSelectCharacterSet, OF_error, "Cannot select character set");
                    }
                    /* check whether this file is a DICOMDIR */
                    if (dfile->getMetaInfo()->findAndGetOFString(DCM_MediaStorageSOPClassUID, sopClass).bad() ||
                        (sopClass != UID_MediaStorageDirectoryStorage))
                    {
                        OFLOG_INFO(dcm2xmlLogger, "inserting SpecificCharacterSet (0008,0005) element with value '"
                            << defaultCharset << "'");
                        /* insert the SpecificCharacterSet (0008,0005) element */
                        dset->putAndInsertString(DCM_SpecificCharacterSet, defaultCharset);
                    }
                }
            } else {
                if (defaultCharset != NULL)
                {
                    /* use "debug" instead of "warn" in order to avoid too much output in default mode */
                    OFLOG_DEBUG(dcm2xmlLogger, "ignoring character set '" << defaultCharset
                        << "' specified with option --charset-assume since it is not needed for this data set");
                }
                /* by default, we use UTF-8 encoding */
                encString = "UTF-8";
            }
        }

        /* write XML document header */
        out << "<?xml version=\"1.0\"";
        /* optional character set */
        if (!encString.empty())
            out << " encoding=\"" << encString << "\"";
        out << "?>" << OFendl;
        /* add document type definition (DTD) */
        if (writeFlags & DCMTypes::XF_addDocumentType)
        {
            out << "<!DOCTYPE ";
            if (readMode == ERM_dataset)
               out << "data-set";
            else
               out << "file-format";
            /* embed DTD */
            if (writeFlags & DCMTypes::XF_embedDocumentType)
            {
                out << " [" << OFendl;
                /* copy content from DTD file */
                STD_NAMESPACE ifstream dtdFile(dtdFilename, OFopenmode_in_nocreate);
                if (dtdFile)
                {
                    char c;
                    /* copy all characters */
                    while (dtdFile.get(c))
                        out << c;
                } else {
                    OFLOG_WARN(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": cannot open DTD file: " << dtdFilename);
                }
                out << "]";
            } else { /* reference DTD */
                out << " SYSTEM \"" << DOCUMENT_TYPE_DEFINITION_FILE << "\"";
            }
            out << ">" << OFendl;
        }
        /* write XML document content */
        if (readMode == ERM_dataset)
            result = dset->writeXML(out, writeFlags);
        else
            result = dfile->writeXML(out, writeFlags);
    }
    return result;
}


char* getDCMXML(char *ifname) {
    size_t opt_writeFlags = 0;
    OFBool opt_loadIntoMemory = OFFalse;
    OFBool opt_checkAllStrings = OFFalse;
    OFBool opt_convertToUTF8 = OFTrue;
    const char *opt_defaultCharset = NULL;
    E_FileReadMode opt_readMode = ERM_autoDetect;
    E_TransferSyntax opt_ixfer = EXS_Unknown;
    OFCmdUnsignedInt opt_maxReadLength = 4096; // default is 4 KB
    const char *opt_dtdFilename = DEFAULT_SUPPORT_DATA_DIR DOCUMENT_TYPE_DEFINITION_FILE;
    OFString optStr;
    opt_writeFlags |= DCMTypes::XF_useNativeModel;

    /* make sure data dictionary is loaded */
    if (!dcmDataDict.isDictionaryLoaded())
    {
        OFLOG_WARN(dcm2xmlLogger, "no data dictionary loaded, check environment variable: "
            << DCM_DICT_ENVIRONMENT_VARIABLE);
    }

    /* make sure document type definition file exists */
    if ((opt_writeFlags & DCMTypes::XF_embedDocumentType) && !OFStandard::fileExists(opt_dtdFilename))
    {
        OFLOG_WARN(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": DTD file \"" << opt_dtdFilename
            << "\" does not exist ... adding reference instead");
        opt_writeFlags &= ~DCMTypes::XF_embedDocumentType;
    }

    int result = 0;
    if ((ifname != NULL) && (strlen(ifname) > 0))
    {
        DcmFileFormat dfile;
        OFCondition status = dfile.loadFile(ifname, opt_ixfer, EGL_noChange, DCM_MaxReadLength, opt_readMode);
        if (status.good())
        {
            DcmDataset *dset = dfile.getDataset();
            /* convert all DICOM strings to UTF-8 (if requested) */
            if (opt_convertToUTF8) 
            {
                OFLOG_INFO(dcm2xmlLogger, "converting all element values that are affected by SpecificCharacterSet (0008,0005) to UTF-8");
                // check whether SpecificCharacterSet is absent but needed
                if ((opt_defaultCharset != NULL) && !dset->tagExistsWithValue(DCM_SpecificCharacterSet) &&
                    dset->containsExtendedCharacters(OFFalse /*checkAllStrings*/))
                {
                    // use the manually specified source character set
                    status = dset->convertCharacterSet(opt_defaultCharset, OFString("ISO_IR 192"));
                } else {
                    // expect that SpecificCharacterSet contains the correct value
                    status = dset->convertToUTF8();
                }
                if (status.bad())
                {
                    OFLOG_FATAL(dcm2xmlLogger, status.text() << ": converting file to UTF-8: " << ifname);
                    result = 4;
                }
            }
            if (result == 0)
            {
                std::ostringstream stream;
                status = writeFile(stream, 
                                   ifname, 
                                   &dfile, 
                                   opt_readMode, 
                                   opt_loadIntoMemory, 
                                   opt_dtdFilename, 
                                   opt_defaultCharset,
                                   opt_writeFlags,
                                   opt_checkAllStrings);
                if (status.bad())
                {
                    OFLOG_ERROR(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": error (" << status.text() << ") writing to standard output");
                    result = 3;
                }
                auto streamStr = stream.str();
                char *item = new char[streamStr.size() +1 ];
                //important!
                //use strcpy avoid char* empty
                strcpy(item , streamStr.c_str());
                return item;
            }
        } 
        else 
        {
            OFLOG_ERROR(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": error (" << status.text() << ") reading file: "<< ifname);
            result = 5;
        }
    }
    else 
    {
        OFLOG_ERROR(dcm2xmlLogger, OFFIS_CONSOLE_APPLICATION << ": invalid filename: <empty string>");
        result = 6;
    }
}

napi_value DCM2XML::dcm2xml(napi_env env, napi_callback_info info)
{
    napi_status napiStatus;
    napi_value xmlResult[1];
    size_t argc = 2;
    napi_value args[2];
    napiStatus = napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    //Get the size of filename string
    size_t str_size;
    napiStatus = napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;

    // Get the callback function
    napi_value cb = args[1];

    /* Give char* memory address and initial zero value
     * The str_size+1 that because string is ['1', '2', \0], so need add 1 length for null value in tail
    */
    char *ifname =  (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napiStatus = napi_get_value_string_utf8(env, args[0], ifname, str_size+1 , &str_size_read);

    char* dcmXML = getDCMXML(ifname);
    if (dcmXML != NULL) 
    {
        napiStatus = napi_create_string_utf8(env, dcmXML, NAPI_AUTO_LENGTH, xmlResult);
        napi_value global;
        napiStatus = napi_get_global(env, &global);
        napi_value cbresult;
        napiStatus = napi_call_function(env, global, cb, 1, xmlResult, &cbresult);
    }
    else 
    {
        napiStatus = napi_throw_error(env, "404" , "The dcmtk status is bad , maybe is no such file");
    }
    free(ifname);
    return NULL;
}