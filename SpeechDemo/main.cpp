
#include <iostream>
#include <sapi.h>
//#include <sphelper.h>

using namespace std;

int main()
{

    ISpVoice *pVoice = NULL;
    if (FAILED(::CoInitialize(NULL)))
        return FALSE;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if (SUCCEEDED(hr))
    {
        //如果生成音频文件，在WTX[]中输入音频文本内容
        if ((true))
        {
            CComPtr <ISpStream> cpWavStream;
            CComPtr <ISpStreamFormat> cpOldStream;
            CSpStreamFormat originalFmt;
            pVoice->GetOutputStream(&cpOldStream);
            originalFmt.AssignFormat(cpOldStream);
            hr = SPBindToFile(L"output.wav", SPFM_CREATE_ALWAYS, &cpWavStream, &originalFmt.FormatId(), originalFmt.WaveFormatExPtr());
            if (SUCCEEDED(hr))
            {
                pVoice->SetOutput(cpWavStream, TRUE);
                WCHAR WTX[] = L"凡事何必都看淡，自己理解就很好，决定我们一生的，是我们的选择。我们时刻都在失去，我们努力的想去拥有更多的精彩，可惜只有两只手，所以必须学会选择，学会放弃。要清楚哪些是我们不需要的，如果心的欲望太大，什么都想抓，可能最后什么知足心灵。只平淡命运无奈";
                pVoice->Speak(WTX, SPF_IS_XML, nullptr);
                pVoice->Release();
                pVoice = nullptr;
            }
        }
        else
        {
            hr = pVoice->Speak(L"Hello world", 0, nullptr);
            pVoice->Release();
            pVoice = nullptr;
        }


    }

    ::CoUninitialize();
    return TRUE;
}
