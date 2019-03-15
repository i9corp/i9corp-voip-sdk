//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_COMMON_EXPORT_H
#define I9CORP_VOIP_SDK_COMMON_EXPORT_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#ifdef I9CORP_VOIP_SDK_COMMONBUILDLIBRARY_H
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#ifdef __cplusplus
}
#endif

#endif //I9CORP_VOIP_SDK_COMMON_EXPORT_H
