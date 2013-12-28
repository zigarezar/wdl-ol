#ifndef __IPLUGFAUST__
#define __IPLUGFAUST__

#include "IPlug_include_in_plug_hdr.h"
#include "faust/audio/dsp.h"

class IPlugFaust : public IPlug
{
public:
  IPlugFaust(IPlugInstanceInfo instanceInfo);
  ~IPlugFaust();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  dsp* mDSP;
};

#endif
