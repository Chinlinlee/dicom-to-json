#pragma once

#include <node_api.h>

class DCM2JSON 
{
    public: 
        static napi_value dcm2json(napi_env env, napi_callback_info info);
};