/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 IPlug faust architecture
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include <map>
#include <list>

#include "faust/gui/GUI.h"
#include "faust/misc.h"
#include "faust/audio/dsp.h"

using namespace std;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

<<includeclass>>

// actually it creates IPlug parameters, not an interface
// class IPlugUI : public UI
// {
// private:
//   PLUG_CLASS_NAME* mPlug;
//   
// public:
//   
//   IPlugUI(PLUG_CLASS_NAME* pPlug)
//   : mPlug(pPlug)
//   {}
//   
//   ~IPlugUI()
//   {}
//   
//   // -- widget's layouts
//   void openTabBox(const char* label) {};
//   void openHorizontalBox(const char* label) {};
//   void openVerticalBox(const char* label) {};
//   void closeBox() {};
//   
//   // -- active widgets
//   void addButton(const char* label, FAUSTFLOAT* zone) {};
//   void addCheckButton(const char* label, FAUSTFLOAT* zone) {};
//   void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {};
//   void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {};
//   void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {};
//   
//   // -- passive widgets
//   void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {} ;
//   void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {} ;
//   
//   // -- metadata declarations
//   
//   void declare(FAUSTFLOAT*, const char*, const char*) {}
// };