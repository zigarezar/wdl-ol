import("music.lib"); 
import("filter.lib");

gain = hslider("gain", 1., 0, 1, 0.01) : smooth(0.999);

process(l,r) = noise *(gain), noise *(gain);