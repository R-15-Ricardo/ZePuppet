#pragma once 

void hsv(int hue, float sat, float val, float& r, float& g, float& b)
{
    hue %= 360;
    while(hue<0) hue += 360;

    if(sat<0.f) sat = 0.f;
    if(sat>1.f) sat = 1.f;

    if(val<0.f) val = 0.f;
    if(val>1.f) val = 1.f;

    int h = hue/60;
    float f = float(hue)/60-h;
    float p = val*(1.f-sat);
    float q = val*(1.f-sat*f);
    float t = val*(1.f-sat*(1-f));

    switch(h)
    {
        default:
        case 0:
        case 6: 
			r = val;
			g = t;
			b = p;
			return;
        case 1: 
			r = q;
			g = val;
			b = p;
			return; 
        case 2: 
			r = p;
			g = val;
			b = t;
			return;
        case 3: 
			r = p;
			g = q;
			b = val;
			return;
        case 4: 
			r = t;
			g = p;
			b = val;
			return;
        case 5: 
			r = val;
			g = p;
			b = q;
			return;
    }
}
