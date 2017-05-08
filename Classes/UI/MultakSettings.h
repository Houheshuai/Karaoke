#ifndef _MULTAK_SETTINGA_H
#define _MULTAK_SETTINGA_H

enum VideoOutputMode
{
	VideoOutput_PAL,
	VideoOutput_NTSC,
	VideoOutput_HDMI,
};

enum AudioOutputMode
{
	AudioOutput_HDMI,
	AudioOutput_Codec,
};

enum ScreenMode
{
	ScreenMode_Single,
	ScreenMode_Dual,
};

class MultakSettings
{
public:
	static MultakSettings *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static MultakSettings instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    }

	void SetVideoOutputMode(enum VideoOutputMode vMode);
	enum VideoOutputMode GetVideoOutputMode();

	void SetAudioOutputMode(enum AudioOutputMode aMode);
	enum AudioOutputMode GetAudioOutputMode();

	void SetDualScreenMode(enum ScreenMode sMode);

	void ResetActivity();

	void StartWifiActivity();

private: 
    MultakSettings ();
    ~MultakSettings ();

	static MultakSettings *p_instance_; 

};


#endif