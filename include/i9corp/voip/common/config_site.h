#define PJ_EXPORT_SPECIFIER  __declspec(dllexport)
#define PJ_IMPORT_SPECIFIER  __declspec(dllimport)

// Uncomment to get minimum footprint (suitable for 1-2 concurrent calls only)
#define PJ_CONFIG_MINIMAL_SIZE

// Uncomment to get maximum performance
//#define PJ_CONFIG_MAXIMUM_SPEED
#define PJMEDIA_HAS_ILBC_CODEC              1
#define PJMEDIA_HAS_GSM_CODEC               1
#define PJMEDIA_HAS_G711_CODEC              1
#define PJMEDIA_HAS_GSM_CODEC               1
#define PJMEDIA_HAS_INTEL_IPP               0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_G729    0
#define PJMEDIA_HAS_VIDEO                   0
#define PJMEDIA_HAS_SRTP                    0
#define PJMEDIA_HAS_G722_CODEC              0
#define PJMEDIA_HAS_SPEEX_CODEC             0
#define PJMEDIA_HAS_OPUS_CODEC              0
#define PJMEDIA_HAS_L16_CODEC               0
#define PJMEDIA_HAS_G722_CODEC              0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_AMR     0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_AMRWB   0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_G723_1  0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_G726    0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_G728    0
#define PJMEDIA_HAS_INTEL_IPP_CODEC_G722_1  0
#define PJSIP_REGISTER_CLIENT_CHECK_CONTACT 0

#include <pj/config_site_sample.h>
