#import "IPlugFaustAppDelegate.h"
#include "IOSLink.h"

IOSLink::IOSLink(void* appDelegate)
{
  mAppDelegate = appDelegate;
}

void IOSLink::SendMidiMsg(IMidiMsg* pMsg)
{
  [((IPlugFaustAppDelegate*)mAppDelegate) sendMidiMsg:pMsg];
}