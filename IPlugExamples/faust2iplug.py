#!/usr/bin/python
# create an IPlug Project from a faust .dsp file

#TODO PLUG_CHANNEL_IO

import duplicate, sys, os

def faust2iplug(faustdsp, base, outputpath):
  cppbasename = base + "-dsp.cpp"
  gencpp = outputpath + "/" + cppbasename
  iplugclasscpp = outputpath + "/" + base + ".cpp"
  os.system("faust " + "-double -a ./../WDL/IPlug/IPlugFaust.cpp " + faustdsp + " -o " + gencpp)
  
  duplicate.replacestrs(iplugclasscpp, "//FAUST_2_IPLUG_INCLUDE", '#include "' + cppbasename + '"')
  duplicate.replacestrs(gencpp, "private:", "public:")

  #work out number of IPlug Parameters
  f = open(gencpp)
  params = []
  for line in f:
    if "		interface->addHorizontalSlider(" in line:
      line = line.lstrip("		interface->addHorizontalSlider(")
      line = line.rstrip(");\n")
      elements = line.split(',')
      elements.append("double")
      params.append(elements)
    if "		interface->addVerticalSlider(" in line:
      line = line.lstrip("		interface->addVerticalSlider(")
      line = line.rstrip(");\n")
      elements = line.split(',')
      elements.append("double")
      params.append(elements)
    if "		interface->addNumEntry(" in line:
      line = line.lstrip("		interface->addNumEntry(")
      line = line.rstrip(");\n")
      elements = line.split(',')
      elements.append("double")
      params.append(elements)
    if "		interface->addButton(" in line:
      print "button not added"
    if "		interface->addCheckButton(" in line:
      print "check button not added"
      
  f.close()

  paramIDStr = "//FAUST_IPLUG_PARAMID_START\n"
  paramDeclStr = "//FAUST_IPLUG_PARAMDECL_START\n"
  paramChangeStr = "//FAUST_IPLUG_PARAMCHANGE_START\n"
  idx = 0
  for p in params:
    paramIDStr = paramIDStr + "  kParam" + `idx` + ",\n"
    if p[6] == "double":
      paramDeclStr = paramDeclStr + "  GetParam(kParam" + `idx` + ")->InitDouble(" + p[0] + "," + p[2] + "," + p[3] + "," + p[4] + "," + p[5] + ', "");\n'
    elif p[6] == "enum":
      #InitEnum("L1 PEG End PT", 0, 7, "", group);
      #void IParam::InitEnum(const char* name, int defaultVal, int nEnums, const char* label, const char* group)
      paramDeclStr = paramDeclStr + "  GetParam(kParam" + `idx` + ")->InitEnum(" + p[0] + "," + p[2] + "," + p[3] + "," + p[4] + "," + p[5] + ', "");\n'

    p[1] = p[1].lstrip(" &")
    paramChangeStr = paramChangeStr + "    case kParam" + `idx` + ":\n      dsp->" + p[1] + " = GetParam(kParam" + `idx` + ")->Value();\n      break;\n"
    idx = idx+1

  paramIDStr = paramIDStr + "  //FAUST_IPLUG_PARAMID_END\n"
  paramDeclStr = paramDeclStr + "  //FAUST_IPLUG_PARAMDECL_END\n"
  paramChangeStr = paramChangeStr + "    //FAUST_IPLUG_PARAMCHANGE_END\n"

  duplicate.replacestrs(iplugclasscpp, "//FAUST_IPLUG_PARAMID_START", paramIDStr)
  duplicate.replacestrs(iplugclasscpp, "//FAUST_IPLUG_PARAMDECL_START", paramDeclStr)
  duplicate.replacestrs(iplugclasscpp, "//FAUST_IPLUG_PARAMCHANGE_START", paramChangeStr)

if __name__ == "__main__":
   if len(sys.argv) == 3:
      faustdsp = os.path.abspath(sys.argv[1])
      path, ext = os.path.splitext(faustdsp)
      base = os.path.basename(path); 
      manufacturer = sys.argv[2]
      if(ext == ".dsp"):
        #duplicate the IPlugFaust template project
        duplicate.main("IPlugFaust", base, manufacturer)
        
        # generate the faust c++ and setup the new IPlug project 
        faust2iplug(faustdsp, base, path)
        
      else:
        print "error - not a faust dsp" 
   else:
      print "error"
