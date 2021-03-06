#include "AudioType.h"
#include "AudioMTKStreamInClient.h"

#define LOG_TAG "AudioMTKStreamInClient"
#ifndef ANDROID_DEFAULT_CODE
    #include <cutils/xlog.h>
    #ifdef ALOGE
    #undef ALOGE
    #endif
    #ifdef ALOGW
    #undef ALOGW
    #endif ALOGI
    #undef ALOGI
    #ifdef ALOGD
    #undef ALOGD
    #endif
    #ifdef ALOGV
    #undef ALOGV
    #endif
    #define ALOGE XLOGE
    #define ALOGW XLOGW
    #define ALOGI XLOGI
    #define ALOGD XLOGD
    #define ALOGV XLOGV
#else
    #include <utils/Log.h>
#endif

#define AUDIO_MTKSTREAMIN_BUFFER_SIZE (0x8000)
#define AUDIO_MTKSTREAMIN_BUFFER_MAXE (0x10000)

namespace android
{

AudioMTKStreamInClient::AudioMTKStreamInClient(uint32 BuffeSize, uint32 clientid)
{
    memset((void *)&mRingBuf, 0, sizeof(RingBuf));
    if (BuffeSize == 0  || BuffeSize >  AUDIO_MTKSTREAMIN_BUFFER_MAXE) {
        BuffeSize = AUDIO_MTKSTREAMIN_BUFFER_SIZE;
    }
    mRingBuf.pBufBase = new char[BuffeSize];
    if (mRingBuf.pBufBase  == NULL) {
        ALOGW("mRingBuf.pBufBase allocate fail");
    }
    mRingBuf.bufLen = BuffeSize;
    mRingBuf.pRead = mRingBuf.pBufBase ;
    mRingBuf.pWrite = mRingBuf.pBufBase ;
    mClientId = clientid;
    mEnable = false;

    mBliHandlerBuffer = NULL;
    mBliOutputLinearBuffer = new char[BuffeSize]; // tmp buffer for blisrc out
    ASSERT(mBliOutputLinearBuffer != NULL);
    mMemDataType = 0;//by Changqing

#ifdef MTK_VOIP_ENHANCEMENT_SUPPORT
    mEnableBesRecord = true;
    mStreamIn = NULL;
#endif

    ALOGD("AudioMTKStreamInClient constructor pBufBase = 0x%x  mClientId = %d",
          mRingBuf.pBufBase, mClientId);
}

AudioMTKStreamInClient::~AudioMTKStreamInClient()
{
    if (mBliOutputLinearBuffer)
        delete[] mBliOutputLinearBuffer;

    if (mRingBuf.pBufBase) {
        delete[] mRingBuf.pBufBase;
    }
    mRingBuf.bufLen = 0;
    mRingBuf.pRead = NULL;
    mRingBuf.pWrite = NULL;
}


}




