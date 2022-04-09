#pragma once

#include <node_api.h>

class DCM2XML 
{
    public: 
        static napi_value dcm2xml(napi_env env, napi_callback_info info);
};