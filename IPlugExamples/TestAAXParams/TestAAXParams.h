#ifndef __TESTAAXPARAMS__
#define __TESTAAXPARAMS__

#include "IPlug_include_in_plug_hdr.h"

class TestAAXParams : public IPlug
{
public:
  TestAAXParams(IPlugInstanceInfo instanceInfo);
  ~TestAAXParams();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
};

#endif
