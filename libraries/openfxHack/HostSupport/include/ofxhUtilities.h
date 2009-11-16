#ifndef _ofxhUtilities_h_
#define _ofxhUtilities_h_

/*
Software License :

Copyright (c) 2007-2009, The Open Effects Association Ltd. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
* Neither the name The Open Effects Association Ltd, nor the names of its 
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <vector>
#include "ofxCore.h"
#include "ofxImageEffect.h"


/**
 * @def   INFOS
 * @brief contient les infos : nom de fichier, numero de ligne, nom de fonction
**/
#define INFOS  "file: " << __FILE__ << ",  line: " << __LINE__ << std::endl << "function: " << __PRETTY_FUNCTION__


/**
 * @def   COUT(...)
 * @param[in] ... : prend tous les parametres pour lesquel l'operator << est definit
 * @brief affichage sur la console uniquement en mode debug
**/
#define COUT(...)  std::cout << __VA_ARGS__ << std::endl

#define COUT_VAR( a )  std::cout << #a << ": " << a << std::endl
#define COUT_VAR2( a, b )  std::cout << #a << ": " << a << ", " << #b << ": " << b << std::endl
#define COUT_VAR3( a, b, c )  std::cout << #a << ": " << a << ", " << #b << ": " << b << ", " << #c << ": " << c << std::endl
#define COUT_VAR4( a, b, c, d )  std::cout << #a << ": " << a << ", " << #b << ": " << b << ", " << #c << ": " << c << ", " << #d << ": " << d << std::endl

/**
 * @def   COUT_INFOS_DEBUG
 * @brief affichage les infos : nom de fichier, numero de ligne, nom de fonction
**/
#define COUT_INFOS COUT(INFOS)

/**
 * @def   COUT_INFOS_DEBUG(...)
 * @param[in] ... : prend tous les parametres pour lesquel l'operator << est definit
 * @brief affichage sur la console uniquement en mode debug (avec des infos : fichier, ligne, fonction)
**/
#define COUT_WITHINFOS(...)  \
	COUT( INFOS << \
	std::endl << "\t" << __VA_ARGS__ )

#define COUT_WARNING(...)  \
	std::cerr << "Warning:" << \
	std::endl << INFOS << \
	std::endl << "\t" << __VA_ARGS__  << std::endl

#define COUT_ERROR(...)  \
	std::cerr << "Error:" << \
	std::endl << INFOS << \
	std::endl << "\t" << __VA_ARGS__  << std::endl

#define COUT_FATALERROR(...)  \
	std::cerr << "Fatal error:" << \
	std::endl << INFOS << \
	std::endl << "\t" << __VA_ARGS__  << std::endl

#define COUT_EXCEPTION(...)  \
	std::cerr << "Exception:" << \
	std::endl << INFOS << \
	std::endl << "\t" << __VA_ARGS__  << std::endl




namespace OFX {

  /// class that is a std::vector of std::strings
  typedef std::vector<std::string> StringVec;

  /// class that is a std::vector of std::strings
  inline void SetStringVecValue(StringVec &sv, const std::string &value, size_t index = 0) 
  {
    size_t size = sv.size();
    if(size <= index) {
      while(size < index) {
        sv.push_back("");
        ++size;
      }
      sv.push_back(value);
    }
    else 
      sv[index] = value;
  }

  /// get me deepest bit depth 
  std::string FindDeepestBitDepth(const std::string &s1, const std::string &s2);

  /// get the min value
  template<class T> inline T Minimum(const T &a, const T &b)
  {
    return a < b ? a : b;
  }

  /// get the min value
  template<class T> inline T Maximum(const T &a, const T &b)
  {
    return a > b ? a : b;
  }

  /// clamp the value
  template<class T> inline T Clamp(const T &v, const T &mn, const T &mx)
  {
    if(v < mn) return mn;
    if(v > mx) return mx;
    return v;
  }

  /// clamp the rect in v to the given bounds
  inline OfxRectD Clamp(const OfxRectD &v,
                        const OfxRectD &bounds)
  {
    OfxRectD r;
    r.x1 = Clamp(v.x1, bounds.x1, bounds.x2);
    r.x2 = Clamp(v.x2, bounds.x1, bounds.x2);
    r.y1 = Clamp(v.y1, bounds.y1, bounds.y2);
    r.y2 = Clamp(v.y2, bounds.y1, bounds.y2);
    return r;
  }

  /// get the union of the two rects
  inline OfxRectD Union(const OfxRectD &a,
                        const OfxRectD &b)
  {
    OfxRectD r;
    r.x1 = Minimum(a.x1, b.x1);
    r.x2 = Maximum(a.x2, b.x2);
    r.y1 = Minimum(a.y1, b.y1);
    r.y2 = Maximum(a.y2, b.y2);
    return r;
  }

  
}

/** @brief maps status to a string */
const std::string mapStatusToString(const OfxStatus stat);

#endif


