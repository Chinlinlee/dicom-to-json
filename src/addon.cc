#include <node_api.h>
#include "dcm2json.h"
#include "dcm2xml.h"

#define NAPI_CALL(env, call)                                      \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending) {                                          \
        const char* message = (error_info->error_message == NULL) \
            ? "empty error message"                               \
            : error_info->error_message;                          \
        napi_throw_error((env), NULL, message);                   \
        return NULL;                                              \
      }                                                           \
    }                                                             \
  } while(0)
  
#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }
static napi_value Init(napi_env env, napi_value exports)
{
    napi_value fnDCM2JSON;
    NAPI_CALL(env ,  napi_create_function(env,
                                          "", 
                                          NAPI_AUTO_LENGTH, 
                                          DCM2JSON::dcm2json, 
                                          NULL, 
                                          &fnDCM2JSON));
    NAPI_CALL(env, napi_set_named_property(env, exports, "dcm2json", fnDCM2JSON));

    napi_value fnDCM2XML;
                                    
    NAPI_CALL(env ,  napi_create_function(env,
                                          "", 
                                          NAPI_AUTO_LENGTH, 
                                          DCM2XML::dcm2xml, 
                                          NULL, 
                                          &fnDCM2XML));
    NAPI_CALL(env, napi_set_named_property(env, exports, "dcm2xml", fnDCM2XML));
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);