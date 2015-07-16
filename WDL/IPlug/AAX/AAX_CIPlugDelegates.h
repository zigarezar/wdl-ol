#ifndef AAX_CIPlugDelegates_H
#define AAX_CIPlugDelegates_H

#include "AAX_ITaperDelegate.h"
#include "AAX_IDisplayDelegate.h"
#include "AAX_CString.h"
#include "AAX.h"

#include <cmath>

template <typename T>
class AAXWrapperTaperDelegate : public AAX_ITaperDelegate<T>
{
public:
  AAXWrapperTaperDelegate(IPlugBase* pPlug, int pParamIdx);
  
  //Virtual AAX_ITaperDelegate Overrides
  AAXWrapperTaperDelegate<T>* Clone() const;
  T GetMinimumValue() const { return mPlug->GetParam(mParamIdx)->GetMin(); }
  T GetMaximumValue() const { return mPlug->GetParam(mParamIdx)->GetMax(); }
  T ConstrainRealValue(T value) const;
  T NormalizedToReal(double normalizedValue) const;
  double RealToNormalized(T realValue) const;

private:
  IPlugBase* mPlug;
  int mParamIdx;
};

template <typename T>
AAXWrapperTaperDelegate<T>::AAXWrapperTaperDelegate(IPlugBase* pPlug, int pParamIdx)
: mPlug(pPlug)
, mParamIdx(pParamIdx)
{
}

template <typename T>
AAXWrapperTaperDelegate<T>* AAXWrapperTaperDelegate<T>::Clone() const
{
  return new AAXWrapperTaperDelegate(*this);
}

template <typename T>
T  AAXWrapperTaperDelegate<T>::ConstrainRealValue(T value) const
{
  double max = mPlug->GetParam(mParamIdx)->GetMax();
  double min = mPlug->GetParam(mParamIdx)->GetMin();

  if (value > max)
    return max;
  if (value < min)
    return min;
  
  return value;
}

template <typename T>
T   AAXWrapperTaperDelegate<T>::NormalizedToReal(double normalizedValue) const
{
  return mPlug->GetParam(mParamIdx)->GetNonNormalized(normalizedValue);
}

template <typename T>
double  AAXWrapperTaperDelegate<T>::RealToNormalized(T realValue) const
{
  return mPlug->GetParam(mParamIdx)->GetNormalized(realValue);
}

#pragma mark Display Delegate

template <typename T>
class AAXWrapperDisplayDelegate : public AAX_IDisplayDelegate<T>
{
public:
  AAXWrapperDisplayDelegate(IPlugBase* pPlug, int pParamIdx);
  //Virtual Overrides
  AAXWrapperDisplayDelegate*  Clone() const;
  bool ValueToString(T value, AAX_CString* valueString) const;
  bool ValueToString(T value, int32_t maxNumChars, AAX_CString* valueString) const ;
  bool StringToValue(const AAX_CString& valueString, T* value) const;
  
private:
  IPlugBase* mPlug;
  int mParamIdx;
};

template <typename T>
AAXWrapperDisplayDelegate<T>::AAXWrapperDisplayDelegate(IPlugBase* pPlug, int pParamIdx)
: mPlug(pPlug)
, mParamIdx(pParamIdx)
{
}

template <typename T>
AAXWrapperDisplayDelegate<T>* AAXWrapperDisplayDelegate<T>::Clone() const
{
  return new AAXWrapperDisplayDelegate(*this);
}

template <typename T>
bool AAXWrapperDisplayDelegate<T>::ValueToString(T value, AAX_CString* valueString) const
{
  char str[32];
  mPlug->GetParam(mParamIdx)->GetDisplayForHost(value, false, str);
  
  if (CSTR_NOT_EMPTY(str))
  {
    valueString->Set(str);
    return true;
  }
  
  return false;
}

//TODO: handle maxNumChars
template <typename T>
bool AAXWrapperDisplayDelegate<T>::ValueToString(T value, int32_t maxNumChars, AAX_CString* valueString) const
{
  char str[32];
  mPlug->GetParam(mParamIdx)->GetDisplayForHost(value, false, str);
  
  if (CSTR_NOT_EMPTY(str))
  {
    valueString->Set(str);
    return true;
  }
  
  return false;
}

template <typename T>
bool AAXWrapperDisplayDelegate<T>::StringToValue(const AAX_CString& valueString, T* value) const
{
//  TChar tString[1024] = {0};
//  String tmp (valueString.Get());
//  tmp.copyTo16 (tString, 0, 1023);
//  
//  ParamValue normalizedValue;
//  if (mPlug->getParamValueByString(mParamIdx, tString, normalizedValue) == kResultOk)
//  {
//    ParamValue nonNormalizedParamValue = mPlug->normalizedParamToPlain(mParamIdx, normalizedValue);
//
//    *value = static_cast<T> (nonNormalizedParamValue);
//    return true;
//  }
//  *value = 0;
  return false;
}

#endif //AAX_CIPlugDelegates_H