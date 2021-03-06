// colorspace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "colorspaceConvert.h"

//数据来源
//http://en.wikipedia.org/wiki/Standard_illuminant
struct WHITE_POINT_ST White_Point_Table[WHITE_POINT_MAX_NUM]=
{
	{0.44757,	0.40745,	0.45117,	0.40594,	0.25594,	0.524332,	2856},	//a
	{0.34842,	0.35161,	0.34980,	0.35270,	0.213662,	0.485243,	4874},	//b
	{0.31006,	0.31616,	0.31039,	0.31905,	0.200868,	0.460983,	6774},	//c
	{0.33333,	0.33333,	0.33333,	0.33333,	0.210527,	0.473684,	5454},	//e
	{0.42426,	0.40263,	NULL,	NULL,	0.243023,	0.518924,	3203},	//d32
	{0.34567,	0.35850,	0.34773,	0.35952,	0.20916,	0.488073,	5003},	//d50
	{0.33242,	0.34743,	0.33411,	0.34877,	0.204375,	0.480795,	5503},	//d55
	{0.33016,	0.34554,	NULL,	NULL,	0.203609,	0.479461,	5603},	//d56
	{0.31271,	0.32902,	0.31382,	0.33100,	0.197835,	0.468326,	6504},	//d65
	{0.29902,	0.31485,	0.29968,	0.31740,	0.193495,	0.458572,	7504},	//d75
	{0.28314,	0.29711,	NULL,	NULL,	0.18879,	0.445736,	9304},	//d93
	{0.31310,	0.33727,	0.31811,	0.33559,	NULL,	NULL,	6430},	//f1
	{0.37208,	0.37529,	0.37925,	0.36733,	NULL,	NULL,	4230},	//f2
	{0.40910,	0.39430,	0.41761,	0.38324,	NULL,	NULL,	3450},	//f3
	{0.44018,	0.40329,	0.44920,	0.39074,	NULL,	NULL,	2940},	//f4
	{0.31379,	0.34531,	0.31975,	0.34246,	NULL,	NULL,	6350},	//f5
	{0.37790,	0.38835,	0.38660,	0.37847,	NULL,	NULL,	4150},	//f6
	{0.31292,	0.32933,	0.31569,	0.32960,	NULL,	NULL,	6500},	//f7
	{0.34588,	0.35875,	0.34902,	0.35939,	NULL,	NULL,	5000},	//f8
	{0.37417,	0.37281,	0.37829,	0.37045,	NULL,	NULL,	4150},	//f9
	{0.34609,	0.35986,	0.35090,	0.35444,	NULL,	NULL,	5000},	//f10
	{0.38052,	0.37713,	0.38541,	0.37123,	NULL,	NULL,	4000},	//f11
	{0.43695,	0.40441,	0.44256,	0.39717,	NULL,	NULL,	3000},	//f12
	{0.314,	0.351,	0.190765,	0.4798,	0.197835,	0.468326,	5900},	//dcip3 gamma2.6
};
//数据来源
//http://www.tftcentral.co.uk/articles/content/pointers_gamut.htm
struct ColorSpace1931_ST ColorSpace_CIE1931[COLOR_SPACE_MAX_NUM]=
{
	{WP_E,1,0,0,1,0,0},	//CS_CIEXYZ
	{WP_D65,0.64,0.33,0.3,0.6,0.15,0.06},//CS_sRGB_HDTVr709
	{WP_D65,0.64,0.33,0.21,0.71,0.15,0.06},//CS_AdobeRGB98
	{WP_D65,0.64,0.33,0.29,0.6,0.15,0.06},//CS_PAL_SECAM_EBU_r470BG
	{WP_D65,0.63,0.34,0.31,0.595,0.155,0.07},//CS_NTSC1987_SMPTEC
	{WP_D93,0.63,0.34,0.31,0.595,0.155,0.07},//CS_JapanNTSC
	{WP_D65,0.625,0.34,0.28,0.595,0.155,0.07},//CS_AppleRGB
	{WP_C,0.67,0.33,0.21,0.71,0.14,0.08},//CS_NTSC1953_FCC_r470M
	{WP_D65,0.70792,0.29203,0.17024,0.79652,0.13137,0.04588},//CS_UHDTV_r2020
	{WP_D50,0.73469,0.26531,0.11416,0.82621,0.15664,0.0177},//CS_AdobeWideRGB
	{WP_D50,0.7347,0.2653,0.1596,0.8404,0.0366,0.0001},//CS_ROMMRGB ProPhoto
	{WP_E,0.7347,0.2653,0.2738,0.7174,0.1666,0.0089},//CS_CIERGB
	{WP_D65,0.64,0.33,0.29,0.6,0.15,0.06},//CS_ITUr601_625Line
	{WP_D65,0.63,0.34,0.31,0.595,0.155,0.07},//CS_ITUr601_525Line
	{WP_Dcip3,0.68,0.32,0.265,0.69,0.15,0.06},//CS_DCIP3
};
//数据来源
//http://www.tftcentral.co.uk/articles/content/pointers_gamut.htm
struct ColorSpace1976_ST ColorSpace_CIE1976[COLOR_SPACE_MAX_NUM]=
{
	{WP_E,1,0,0,1,0,0},	//CS_CIEXYZ
	{WP_D65,0.451,0.523,0.125,0.563,0.175,0.158},//CS_sRGB_HDTVr709-

	{WP_D65,0.451,0.523,0.076,0.576,0.175,0.158},//CS_AdobeRGB98-

	{WP_D65,0.64,0.33,0.29,0.6,0.15,0.06},//CS_PAL_SECAM_EBU_r470BG
	{WP_D65,0.63,0.34,0.31,0.595,0.155,0.07},//CS_NTSC1987_SMPTEC
	{WP_D93,0.63,0.34,0.31,0.595,0.155,0.07},//CS_JapanNTSC
	{WP_D65,0.625,0.34,0.28,0.595,0.155,0.07},//CS_AppleRGB

	{WP_C,0.477,0.528,0.076,0.576,0.152,0.196},//CS_NTSC1953_FCC_r470M-

	{WP_D65,0.55649,0.51651,0.05573,0.58674,0.15983,0.12558},//CS_UHDTV_r2020-

	{WP_D50,0.62337,0.50650,0.036,0.58614,0.21612,0.05496},//CS_AdobeWideRGB-


	{WP_D50,0.6234,0.5065,0.05,0.5925,0.05,0.0003},//CS_ROMMRGB ProPhoto-

	{WP_E,0.7347,0.2653,0.2738,0.7174,0.1666,0.0089},//CS_CIERGB  
	{WP_D65,0.64,0.33,0.29,0.6,0.15,0.06},//CS_ITUr601_625Line
	{WP_D65,0.63,0.34,0.31,0.595,0.155,0.07},//CS_ITUr601_525Line

	{WP_Dcip3,0.496,0.526,0.099,0.578,0.175,0.158},//CS_DCIP3-
};

//收藏！！
//http://www.tftcentral.co.uk/articles/calibrating.htm
//http://www.tftcentral.co.uk/reviews/spyder3elite.htm


//数据来源
//http://en.wikipedia.org/wiki/Planckian_locus
bool CCT_to_CIE_xy(double K,double *x,double *y)
{
	if(K<1667 || K>25000)
		return false;

	if(K>=1667 && K<4000)
	{
		(*x)=-266123900.0/(K*K*K)-234358.0/(K*K)+877.6956/K+0.17991;
	}
	else 	if(K>=4000 && K<=25000)
	{
		(*x)=-3025846900.0/(K*K*K)+2107037.9/(K*K)+222.6347/K+0.24039;
	}
	else
		return false;

	if(K>=1667 && K<2222)
	{
		(*y)=-1.1063814*(*x)*(*x)*(*x)-1.34811020*(*x)*(*x)+2.18555832*(*x)-0.20219683;
	}
	else if(K>=2222 && K<4000)
	{
		(*y)=-0.9549476*(*x)*(*x)*(*x)-1.37418593*(*x)*(*x)+2.09137015*(*x)-0.16748867;
	}
	else 	if(K>=4000 && K<=25000)
	{
		(*y)=3.0817580*(*x)*(*x)*(*x)-5.87338670*(*x)*(*x)+3.75112997*(*x)-0.37001483;
	}
	else
		return false;

	return true;
}

//色彩空间转色度
//http://wenku.baidu.com/link?url=60xVPEkNJunahc1AF_EG5boUuOaPAgo6OResKYdSV2F7u1dZtLlbg-GLPHbyq0kZZLqRrD2-wM7Fq7-ANpZqTHkrWMmCYkpTIxb-rDeGc8O
//https://en.wikipedia.org/wiki/CIE_1931_color_space
void CIE_XYZ_1931_to_CIE_xy(double X,double Y,double Z,double *x,double *y,double *z)
{
	(*x)=X/(X+Y+Z);
	(*y)=Y/(X+Y+Z);
	(*z)=1-(*x)-(*y);
}

void CIE_XYZ_1931_to_CIE_RGB(double X,double Y,double Z,double *R,double *G,double *B)
{
	(*R)=X*0.41847+Y*(-0.15866)+Z*(-0.082835);
	(*G)=X*(-0.091169)+Y*(0.25253)+Z*(0.015708);
	(*B)=X*(0.0009209)+Y*(-0.0025498)+Z*(0.1786);
}

//配色函数（刺激值）转换公式
//显示色彩工程学http://wenku.baidu.com/link?url=60xVPEkNJunahc1AF_EG5boUuOaPAgo6OResKYdSV2F7u1dZtLlbg-GLPHbyq0kZZLqRrD2-wM7Fq7-ANpZqTHkrWMmCYkpTIxb-rDeGc8O
//https://en.wikipedia.org/wiki/CIE_1931_color_space
void CIE_RGB_to_CIE_XYZ_1931(double R,double G,double B,double *X,double *Y,double *Z)
{
#if 0
	(*X)=R*2.7689+G*(1.7517)+B*(1.1302);
	(*Y)=R*(1.0002)+G*(4.5907)+B*(0.0601);
	(*Z)=G*(0.0565)+B*(5.5943);
#else
	double a=0.17697;

	(*X)=R*0.49/a+G*0.31/a+B*0.2/a;
	(*Y)=R*0.17697/a+G*0.8124/a+B*0.1063/a;
	(*Z)=G*0.01/a+B*0.99/a;

#endif
}


void CIE_RGB_to_CIE_xyz_1931(double r,double g,double b,double *x,double *y,double *z)
{
	double a=0.66697*r+1.1324*g+1.20063*b;

	(*x)=(0.49*r+0.31*g+0.2*b)/a;
	(*y)=(0.17697*r+0.8124*g+0.01063*b)/a;
	(*z)=(0.01*g+0.99*b)/a;
}
void CIE_RGB_to_CIE_XYZ_1964(double R,double G,double B,double *X,double *Y,double *Z)
{
	(*X)=R*0.341427+G*(0.188273)+B*(0.390202);
	(*Y)=R*(0.138972)+G*(0.837182)+B*(0.073588);
	(*Z)=R+G*(0.0375154)+B*(2.038878);
}


void CIE_XYZ_1931_to_CIE_1958_L(double X,double Y,double Z,double *L)
{
	(*L)=25.29*pow(Y,1.0/3.0)-18.38;
}


void CIE_Y_Yn1931_to_CIE_L(double Y,double Yn,double *L)
{
	double e=0.008856;

	double yr=Y/Yn;
	double f;

	if(yr>e)
		f=pow(yr,1.0/3.0);
	else 
		f=841.0/108.0*yr+4.0/29.0;

	(*L)=116*f-16;
}


//https://en.wikipedia.org/wiki/CIELUV 
void CIE_xy_1931_to_CIE1976_upvp(double x,double y,double *up,double *vp)
{
	double a=(-2*x+12*y+3);

	(*up)=4*x/a;
	(*vp)=9*y/a;
}

//https://en.wikipedia.org/wiki/CIELUV 
void CIE_XYZ_1931_to_CIE1976_upvp(double X,double Y,double Z,double *up,double *vp)
{
	double a=(X+15*Y+3*Z);

	(*up)=4*X/a;
	(*vp)=9*Y/a;
}
//https://en.wikipedia.org/wiki/CIELUV 
void CIE1976_upvp_to_CIE_xy_1931(double up,double vp,double *x,double *y)
{
	double a=(6*up-16*vp+12);

	(*x)=9*up/a;
	(*y)=4*vp/a;
}


void CIE_xy_1931_to_CIE1960_uv(double x,double y,double *u,double *v)
{
	double a=(-2*x+12*y+3);

	(*u)=4*x/a;
	(*v)=6*y/a;
}

void CIE_XYZ_1931_to_CIE1960_uv(double X,double Y,double Z,double *u,double *v)
{
	double a=(X+15*Y+3*Z);

	(*u)=4*X/a;
	(*v)=6*Y/a;
}

void CIE1976_upvp_to_CIE1960_uv(double up,double vp,double *u,double *v)
{
	(*u)=up;
	(*v)=2.0/3.0*vp;
}

void GammaLine(double gamma,double Input,double *Output)
{
	// 2.222 = 1.0/0.45
	(*Output)=pow(Input,gamma);
}

//http://www.fourmilab.ch/documents/specrend/
void gamma_correct(	double gamma, double *c)
{

#if 0
	if (gamma == GAMMA_REC709) 
	{
		/* Rec. 709 gamma correction. */
		double cc = 0.018;

		if (*c < cc) 
		{
			*c *= ((1.099 * pow(cc, 0.45)) - 0.099) / cc;
		} else 
		{
			*c = (1.099 * pow(*c, 0.45)) - 0.099;
		}
	}
	else 
#else
	{
		/* Nonlinear colour = (Linear colour)^(1/gamma) */
		*c = pow(*c, 1.0 / gamma);
	}
#endif
}

//http://www.fourmilab.ch/documents/specrend/
void gamma_correct_RGB(	double gamma,  double *r, double *g, double *b)
{
	gamma_correct(gamma, r);
	gamma_correct(gamma, g);
	gamma_correct(gamma, b);
}

/*  	    	    	    NORM_RGB

Normalise RGB components so the most intense (unless all
are zero) has a value of 1.
//http://www.fourmilab.ch/documents/specrend/
*/
void norm_RGB(double *r, double *g, double *b)
{
#define Max(a, b)   (((a) > (b)) ? (a) : (b))
	double greatest = Max(*r, Max(*g, *b));

	if (greatest > 0) {
		*r /= greatest;
		*g /= greatest;
		*b /= greatest;
	}
#undef Max
}
/*                          CONSTRAIN_RGB

If the requested RGB shade contains a negative weight for
one of the primaries, it lies outside the colour gamut 
accessible from the given triple of primaries.  Desaturate
it by adding white, equal quantities of R, G, and B, enough
to make RGB all positive.  The function returns 1 if the
components were modified, zero otherwise.
//http://www.fourmilab.ch/documents/specrend/
*/

int constrain_RGB(double *r, double *g, double *b)
{
	double w;

	/* Amount of white needed is w = - min(0, *r, *g, *b) */

	w = (0 < *r) ? 0 : *r;
	w = (w < *g) ? w : *g;
	w = (w < *b) ? w : *b;
	w = -w;

	/* Add just enough white to make r, g, b all positive. */

	if (w > 0) {
		*r += w;  *g += w; *b += w;
		return 1;                     /* Colour modified to fit RGB gamut */
	}

	return 0;                         /* Colour within RGB gamut */
}

/*                             XYZ_TO_RGB

Given an additive tricolour system CS, defined by the CIE x
and y chromaticities of its three primaries (z is derived
trivially as 1-(x+y)), and a desired chromaticity (XC, YC,
ZC) in CIE space, determine the contribution of each
primary in a linear combination which sums to the desired
chromaticity.  If the  requested chromaticity falls outside
the Maxwell  triangle (colour gamut) formed by the three
primaries, one of the r, g, or b weights will be negative. 

Caller can use constrain_rgb() to desaturate an
outside-gamut colour to the closest representation within
the available gamut and/or norm_rgb to normalise the RGB
components so the largest nonzero component has value 1.
//http://www.fourmilab.ch/documents/specrend/
*/

void ChromaticityCoordinates_to_RGB(struct ColorSpace1931_ST cs,
									double xc, double yc, double zc,
									double *r, double *g, double *b)
{
	double xr, yr, zr, xg, yg, zg, xb, yb, zb;
	double xw, yw, zw;
	double rx, ry, rz, gx, gy, gz, bx, by, bz;
	double rw, gw, bw;

	xr = cs.Xr;    yr = cs.Yr;    zr = 1 - (xr + yr);
	xg = cs.Xg;  yg = cs.Yg;  zg = 1 - (xg + yg);
	xb =cs.Xb;   yb = cs.Yb;   zb = 1 - (xb + yb);

	xw = White_Point_Table[cs.W].x2;  yw = White_Point_Table[cs.W].y2;  zw = 1 - (xw + yw);

	/* xyz -> rgb matrix, before scaling to white. */

	rx = (yg * zb) - (yb * zg);  ry = (xb * zg) - (xg * zb);  rz = (xg * yb) - (xb * yg);
	gx = (yb * zr) - (yr * zb);  gy = (xr * zb) - (xb * zr);  gz = (xb * yr) - (xr * yb);
	bx = (yr * zg) - (yg * zr);  by = (xg * zr) - (xr * zg);  bz = (xr * yg) - (xg * yr);

	/* White scaling factors.
	Dividing by yw scales the white luminance to unity, as conventional. */

	rw = ((rx * xw) + (ry * yw) + (rz * zw)) / yw;
	gw = ((gx * xw) + (gy * yw) + (gz * zw)) / yw;
	bw = ((bx * xw) + (by * yw) + (bz * zw)) / yw;

	/* xyz -> rgb matrix, correctly scaled to white. */

	rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
	gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
	bx = bx / bw;  by = by / bw;  bz = bz / bw;

	/* rgb of the desired point */

	*r = (rx * xc) + (ry * yc) + (rz * zc);
	*g = (gx * xc) + (gy * yc) + (gz * zc);
	*b = (bx * xc) + (by * yc) + (bz * zc);
}
//波长 色温转亮度公式  用于刺激色转色度
//http://www.fourmilab.ch/documents/specrend/
double CCT_spectrum(double CCT,double wavelength)
{
	double wlm = wavelength * 1e-9;   /* Wavelength in meters */

	return (3.74183e-16 * pow(wlm, -5.0)) /
		(exp(1.4388e-2 / (wlm * CCT)) - 1.0);
}
/*                          SPECTRUM_TO_XYZ

Calculate the CIE X, Y, and Z coordinates corresponding to
a light source with spectral distribution given by  the
function SPEC_INTENS, which is called with a series of
wavelengths between 380 and 780 nm (the argument is 
expressed in meters), which returns emittance at  that
wavelength in arbitrary units.  The chromaticity
coordinates of the spectrum are returned in the x, y, and z
arguments which respect the identity:

x + y + z = 1.
*/
//刺激色转色度
//http://www.fourmilab.ch/documents/specrend/
void spectrum_to_xyz(double CCT,struct ColourMatchingFunctions_ST *cmf,
					 double *x, double *y, double *z)
{
	int i;
	double wavelength, X = 0, Y = 0, Z = 0, XYZ;
	double Me;
	/* CIE colour matching functions xBar, yBar, and zBar for
	wavelengths from 380 through 780 nanometers, every 5
	nanometers.  For a wavelength lambda in this range:

	cie_colour_match[(lambda - 380) / 5][0] = xBar
	cie_colour_match[(lambda - 380) / 5][1] = yBar
	cie_colour_match[(lambda - 380) / 5][2] = zBar

	To save memory, this table can be declared as floats
	rather than doubles; (IEEE) float has enough 
	significant bits to represent the values. It's declared
	as a double here to avoid warnings about "conversion
	between floating-point types" from certain persnickety
	compilers. */
	struct ColourMatchingFunctions_Lite_ST *datap=(struct ColourMatchingFunctions_Lite_ST *)cmf->data;
	for (i = 0,	wavelength= datap[0].nm ; i < cmf->total; i++, wavelength += cmf->step) 
	{
		Me = CCT_spectrum(CCT,wavelength);
		X += Me * datap[i].x;
		Y += Me * datap[i].y;
		Z += Me * datap[i].z;
	}
	XYZ = (X + Y + Z);
	(*x) = X / XYZ;
	(*y) = Y / XYZ;
	(*z) = Z / XYZ;
}


///////////////////////////////////////////////
