/*
*
*  Copyright (C) 2016-2020, OFFIS e.V.
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
*  Author:  Sebastian Grallert
*
*  Purpose: Convert the contents of a DICOM file to JSON format
*
*/

#include "dcmtk/config/osconfig.h" /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/cmdlnarg.h"

#include "dcmtk/dcmdata/dcjson.h"
#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/ofstd/ofexit.h"

#ifdef WITH_ZLIB
#include <zlib.h> /* for zlibVersion() */
#endif
#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
#include "dcmtk/ofstd/ofchrenc.h" /* for OFCharacterEncoding */
#endif

#define OFFIS_CONSOLE_APPLICATION "dcm2json"
#define OFFIS_CONSOLE_DESCRIPTION "Convert DICOM file and data set to JSON"

#define EXITCODE_CANNOT_CONVERT_TO_UNICODE 80
#define EXITCODE_CANNOT_WRITE_VALID_JSON 81

static OFLogger dcm2jsonLogger = OFLog::getLogger("dcmtk.apps." OFFIS_CONSOLE_APPLICATION);

// ********************************************

/* Function to call all writeJson() functions in DCMTK */
static OFCondition writeFile(STD_NAMESPACE ostream &out,
                             const char *ifname,
                             DcmFileFormat *dfile,
                             const E_FileReadMode readMode,
                             const OFBool format,
                             const OFBool printMetaInfo,
                             const OFBool encode_extended)
{
    
    OFCondition result = EC_IllegalParameter;
    if ((ifname != NULL) && (dfile != NULL))
    {
        /* write JSON document content */
        DcmDataset *dset = dfile->getDataset();
        if (format)
        {
            DcmJsonFormatPretty fmt(printMetaInfo);
            fmt.setJsonExtensionEnabled(encode_extended);
            if (readMode == ERM_dataset)
                result = dset->writeJsonExt(out, fmt, OFTrue, OFTrue);
            else
                result = dfile->writeJson(out, fmt );
        }
        else
        {
            DcmJsonFormatCompact fmt(printMetaInfo);
            fmt.setJsonExtensionEnabled(encode_extended);
            if (readMode == ERM_dataset)
                result = dset->writeJsonExt(out, fmt, OFTrue, OFTrue );
            else
                result = dfile->writeJson(out, fmt );
        }
    }
    return result;
}

#define SHORTCOL 3
#define LONGCOL 20

static char rcsid[] = "$dcmtk: " OFFIS_CONSOLE_APPLICATION " v" OFFIS_DCMTK_VERSION " " OFFIS_DCMTK_RELEASEDATE " $";

#include <assert.h>
#include <node_api.h>
#include "dcm2json.h"


char *getDCMJson(char *ifname)
{
    OFBool opt_format = OFTrue;
    OFBool opt_addMetaInformation = OFTrue;
    OFBool opt_encode_extended = OFFalse;
    E_FileReadMode opt_readMode = ERM_autoDetect;
    E_TransferSyntax opt_ixfer = EXS_Unknown;
    OFString optStr;

    OFConsoleApplication app(OFFIS_CONSOLE_APPLICATION, OFFIS_CONSOLE_DESCRIPTION, rcsid);
    int result = 0;
    if ((ifname != NULL) && (strlen(ifname) > 0))
    {
        DcmFileFormat dfile;
        OFCondition status = dfile.loadFile(ifname, opt_ixfer, EGL_noChange, DCM_MaxReadLength, opt_readMode);
        if (status.good())
        {
            DcmDataset *dset = dfile.getDataset();
            OFString csetString;
            if (dset->findAndGetOFStringArray(DCM_SpecificCharacterSet, csetString).good())
            {
                if (csetString.compare("ISO_IR 6") == 0) 
                {
                    if (dset->containsExtendedCharacters(OFFalse /*checkAllStrings*/))
                    {
                        OFLOG_FATAL(dcm2jsonLogger, "dataset contains extended characters but SpecificCharacterSet (0008,0005) is 'ISO_IR 6'");
                        result = EXITCODE_CANNOT_CONVERT_TO_UNICODE;
                        return "80";
                    }
                }
                else if (csetString.compare("ISO_IR 192") == 0)
                {

                }
                else 
                {
                                        /* we have a character set other than ASCII or UTF-8. Perform conversion. */
#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
                    /* convert all DICOM strings to UTF-8 */
                    OFLOG_INFO(dcm2jsonLogger, "converting all element values that are affected by SpecificCharacterSet (0008,0005) to UTF-8");
                    status = dset->convertToUTF8();
                    if (status.bad())
                    {
                        OFLOG_FATAL(dcm2jsonLogger, status.text() << ": converting file to UTF-8: " << ifname);
                        result = EXITCODE_CANNOT_CONVERT_TO_UNICODE;
                        return "80";
                    }
#else
                    OFLOG_FATAL(dcm2jsonLogger, "character set conversion not available");
                    result = EXITCODE_CANNOT_CONVERT_TO_UNICODE;
#endif
                }
            }
            if (result == 0)
            {
                std::ostringstream stream;
                status = writeFile(stream, ifname, &dfile, opt_readMode, opt_format, opt_addMetaInformation, opt_encode_extended);
                if (status.bad())
                {
                    OFLOG_FATAL(dcm2jsonLogger, status.text() << ": " << ifname);
                    result = EXITCODE_CANNOT_WRITE_VALID_JSON;
                    return "81";
                }
                //COUT << stream.str();
                auto  streamStr = stream.str();
                char *item = new char[streamStr.size() +1 ];
                //important!
                //use strcpy avoid char* empty
                strcpy(item , streamStr.c_str());
                // OFLOG_INFO(dcm2jsonLogger , "get json success");
                return item;
            }
        }
        else
        {
            OFLOG_FATAL(dcm2jsonLogger, status.text() << ": " << ifname);
            return "2";
        }
    }
    return NULL;
}



napi_value DCM2JSON::dcm2json(napi_env env, napi_callback_info info)
{
    napi_status napiStatus;
    napi_value jsonResult[1];
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

    char* dcmjson = getDCMJson(ifname);
    if (dcmjson == "81") 
    {
        napiStatus = napi_throw_error(env, "81" , "EXITCODE_CANNOT_WRITE_VALID_JSON");
    }
    else if (dcmjson == "80") 
    {
        napiStatus = napi_throw_error(env, "80" , "EXITCODE_CANNOT_CONVERT_TO_UNICODE");
    }
    else if (dcmjson == "2") 
    {
        napiStatus = napi_throw_error(env, "404" , "No such file or directory or not a valid DICOM file");
    }
    else
    {
        napiStatus = napi_create_string_utf8(env, dcmjson, NAPI_AUTO_LENGTH, jsonResult);
        napi_value global;
        napiStatus = napi_get_global(env, &global);
        napi_value cbresult;
        napiStatus = napi_call_function(env, global, cb, 1, jsonResult, &cbresult);
    }
    free(ifname);
    return NULL;
}