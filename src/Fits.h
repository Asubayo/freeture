/*
								Fits.h

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*	This file is part of:	freeture
*
*	Copyright:		(C) 2014 Yoan Audureau -- FRIPON-GEOPS-UPSUD
*
*	License:		GNU General Public License
*
*	FreeTure is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*	FreeTure is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*	You should have received a copy of the GNU General Public License
*	along with FreeTure. If not, see <http://www.gnu.org/licenses/>.
*
*	Last modified:		21/10/2014
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @file    Fits.h
 * @author  Yoan Audureau -- FRIPON-GEOPS-UPSUD
 * @version 1.0
 * @date    28/11/2014
 */

#pragma once

#include "includes.h"
#include "Configuration.h"

#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

/*
    1.  SIMPLE      = T                                         / file does conform to FITS standard
    2.  BITPIX      = 8                                         / number of bits per pixel
    3.  NAXIS       = 2                                         / number of data axes
    4.  NAXIS1      = 1280                                      / length of data axis 1
    5.  NAXIS2      = 960                                       / length of data axis 2
    6.  EXTEND      = T                                         / FITS dataset may contain extensions

    7.  FILENAME    = 'stationOrsay_YYYYMMJJ_HHMMSS_UT.fits'    / name of the fits file
    8.  DATE        = 'YYYY-MM-JJT HH:MM:SS.SS'                 / date of the creation of the fits file
    9.  DATE-OBS    = 'YYYY-MM-JJT HH:MM:SS.SS'                 / acquisition date of the first frame
    10. OBS_MODE    = SINGLE                                    / observation method to get this fits file 'SINGLE' 'SUM' 'AVERAGE' ('MEDIAN')
    11. ELAPTIME    = 60                                        / end observation date - start observation date (sec.)
    12. EXPOSURE    = 0.033                                     / integration time : 1/fps * nb_frames (sec.)
    13. ONTIME      = 0.033                                     / frame exposure time (sec.)
    14. FILTER      = "NONE"
    15. TELESCOP    = "<Code station>"                          / station <stationName>
    16. OBSERVER    = "<responsable camera>"
    17. INSTRUME    = 'FRIPON-CAM'
    18. CAMERA      = 'BASLER 1300gm'
    19. FOCAL       = 1.25
    20. APERTURE    = 2.0
    21. SITELONG    = 2.1794397                                 / longitude observatory
    22. SITELAT     = 48.7063906                                / latuitude observatory
    23. SITEELEV    = 90                                        / observatory elevation (meter)
    24. XPIXEL      = 3.75
    25. YPIXEL      = 3.75
    26. GAINDB      = 400                                       / detector gain
    27. SATURATE    = 4095                                      / saturation value or max value (not saturated) in case where OBS_MODE = SUM
    28. PROGRAM     = 'FreeTure v0.1'                           / name of the acquisition software
    29. CREATOR     = 'FRIPON TEAM'                             / http://fripon.org
    30. BZERO       = 0
    31. BSCALE      = 1
    32. RADESYS     = 'ICRS'
    33. TIMESYS     = 'UTC'
    34. EQUINOX     = 2.000000000000E+03                        / equinox of equatorial coordinates
    35. CTYPE1      = 'RA---ARC'                                / projection and reference system
    36. CTYPE2      = 'DEC--ARC'                                / projection and reference system
    37. CTYPE3      = 'UTC '                                    / time reference system (pour les 'videos' des detections)
    38. TIMEUNIT    = 's '
    39. CD1_1       = 0.0                                       / deg/px
    40. CD1_2       = 0.17                                      / deg/px
    41. CD2_1       = 0.17                                      / deg/pix
    42. CD2_2       = 0.0                                       / deg/pix
    43. CD3_3       = 30                                        / fps
    44. CD1_3       = 0.0
    45. CD2_3       = 0.0
    46. CD3_1       = 0.0
    47. CD3_2       = 0.0
    48. CRPIX1      = 640
    49. CRPIX2      = 480
    50. CRPIX3      = 0
    51. CRVAL1      =                                           / Sidereal time (decimal degree)
    52. CRVAL2      =                                           / latitude observatory (decimal degree)
    53. K1          =
    54. K2          =

*/

class Fits{

    public:

        Fits();
        ~Fits();

        bool loadKeywordsFromConfigFile(string configFile);

        string  getCamera();
        string  getFilename();
        double  getExposure();
        string  getTelescop();
        string  getObserver();
        string  getInstrument();
        double  getFocal();
        string  getFilter();
        string  getProgram();
        string  getCreator();
        double  getAperture();
        double  getXpixel();
        double  getYpixel();
        double  getSitelong();
        double  getSitelat();
        double  getSiteelev();
        int     getGaindb();
        int     getCrpix1();
        int     getCrpix2();
        double  getK1();
        double  getK2();
        string  getComment();
        double  getCd1_1();
        double  getCd1_2();
        double  getCd2_1();
        double  getCd2_2();
        string  getObsmode();
        string  getDateobs();
        double  getSaturate();
        double  getOntime();
        string  getRadesys();
        double  getEquinox();
        string  getCtype1();
        string  getCtype2();
        int     getElaptime();
        double  getCrval2();
        double  getCrval1();

        void setFilename(string filename);
        void setExposure(double exposure);
        void setTelescop(string telescope);
        void setObserver(string observer);
        void setInstrument(string instrument);
        void setCamera(string camera);
        void setFocal(double focal);
        void setFilter(string filter);
        void setProgram(string program);
        void setCreator(string creator);
        void setAperture(double aperture);
        void setXpixel(double xpixel);
        void setYpixel(double ypixel);
        void setSitelong(double sitelong);
        void setSitelat(double sitelat);
        void setSiteelev(double siteelev);
        void setGaindb(int gaindb);
        void setCrpix1(int crpix1);
        void setCrpix2(int crpix2);
        void setK1(double k1);
        void setK2(double k2);
        void setComment(string comment);
        void setCd1_1(double cd1_1);
        void setCd1_2(double cd1_2);
        void setCd2_1(double cd2_1);
        void setCd2_2(double cd2_2);
        void setObsmode(string obsmode);
        void setDateobs(string dateobs);
        void setSaturate(double saturate);
        void setOntime(double ontime);
        void setRadesys(string radesys);
        void setEquinox(double equinox);
        void setCtype1(string ctype1);
        void setCtype2(string ctype2);
        void setElaptime(int elaptime);
        void setCrval2(double crval2);
        void setCrval1(double crval1);
        void setStation(string name);

    protected:

        string  STATION;

        /// Fits Header Keywords Name.

		string  kFILENAME;
		string  kDATE;
		string  kDATEOBS;
		string  kOBSMODE;
		int     kELAPTIME;
		double  kEXPOSURE;
        double  kONTIME;
        string  kFILTER;
		string  kTELESCOP;
		string  kOBSERVER;
		string  kINSTRUME;
		string  kCAMERA;
		double  kFOCAL;
		double  kAPERTURE;
		double  kSITELONG;
		double  kSITELAT;
		double  kSITEELEV;
		double  kXPIXEL;
		double  kYPIXEL;
		int     kGAINDB;
		double  kSATURATE;
		string  kPROGRAM;
		string  kCREATOR;
		double  kBZERO;
		double  kBSCALE;
		string  kRADESYS;
		string  kTIMESYS;
		double  kEQUINOX;
		string  kCTYPE1;
		string  kCTYPE2;
		string  kCTYPE3;
		string  kTIMEUNIT;
		double  kCD1_1;
		double  kCD1_2;
		double  kCD2_1;
		double  kCD2_2;
		double  kCD3_3;
        double  kCD1_3;
        double  kCD2_3;
        double  kCD3_1;
        double  kCD3_2;
		int     kCRPIX1;
		int     kCRPIX2;
		int     kCRPIX3;
        double  kCRVAL1;
		double  kCRVAL2;
		double  kK1;
		double  kK2;
		string  kCOMMENT;

		/// Fits Header Keywords Comments.

		string  cFILENAME;
		string  cDATE;
		string  cDATEOBS;
		string  cOBSMODE;
		string  cELAPTIME;
		string  cEXPOSURE;
        string  cONTIME;
        string  cFILTER;
		string  cTELESCOP;
		string  cOBSERVER;
		string  cINSTRUME;
		string  cCAMERA;
		string  cFOCAL;
		string  cAPERTURE;
		string  cSITELONG;
		string  cSITELAT;
		string  cSITEELEV;
		string  cXPIXEL;
		string  cYPIXEL;
		string  cGAINDB;
		string  cSATURATE;
		string  cPROGRAM;
		string  cCREATOR;
		string  cBZERO;
		string  cBSCALE;
		string  cRADESYS;
		string  cTIMESYS;
		string  cEQUINOX;
		string  cCTYPE1;
		string  cCTYPE2;
		string  cCTYPE3;
		string  cTIMEUNIT;
		string  cCD1_1;
		string  cCD1_2;
		string  cCD2_1;
		string  cCD2_2;
		string  cCD3_3;
        string  cCD1_3;
        string  cCD2_3;
        string  cCD3_1;
        string  cCD3_2;
		string  cCRPIX1;
		string  cCRPIX2;
		string  cCRPIX3;
		string  cCRVAL1;
		string  cCRVAL2;
		string  cK1;
		string  cK2;
		string  cCOMMENT;

};

