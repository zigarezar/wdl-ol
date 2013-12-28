#include "IPlugFaust.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

//FAUST_2_IPLUG_INCLUDE

const int kNumPrograms = 1;

enum EParams
{
  //FAUST_IPLUG_PARAMID_START
  //FAUST_IPLUG_PARAMID_END

  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,
};

IPlugFaust::IPlugFaust(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  TRACE;

  mDSP = new mydsp();

  //FAUST_IPLUG_PARAMDECL_START
  //FAUST_IPLUG_PARAMDECL_END

  MakeDefaultPreset((char *) "-", kNumPrograms);
}

IPlugFaust::~IPlugFaust() 
{
  delete mDSP;
}

void IPlugFaust::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.
  AVOIDDENORMALS;

  mDSP->compute(nFrames, inputs, outputs);
}

void IPlugFaust::Reset()
{
  TRACE;
  IMutexLock lock(this);
  
  mDSP->init(GetSampleRate());
}

void IPlugFaust::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);
  mydsp* dsp = (mydsp*) mDSP;

  switch (paramIdx)
  {
    //FAUST_IPLUG_PARAMCHANGE_START
    //FAUST_IPLUG_PARAMCHANGE_END
    default:
      break;
  }
}
