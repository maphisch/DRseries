/********************************************************************
   The Image Processing Library 98 - IPL98
   Copyright (C) by Ren� Dencker Eriksen - edr@mip.sdu.dk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation. Only
   addition is, that if the library is used in proprietary software
   it must be stated that IPL98 was used.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   More details can be found in the file licence.txt distributed
   with this library.
*********************************************************************/

#ifndef _IPL98_MORPHOLOGY_H
#define _IPL98_MORPHOLOGY_H

#include "../../ipl98_setup.h" /* always include the setup file */
#include "../std_image.h"

namespace ipl{ // use namespace if C++

/** @ingroup algorithms
@{ */

/** CMorphology Simple morphological methods, Last updated 5/1/2003.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CMorphology ipl98/cpp/algorithms/morphology.h
	@version 1.01
	@author Ivar Balslev ivb@mip.sdu.dk and Ren� Dencker Eriksen edr@mip.sdu.dk */
class CMorphology{
	private: // attributes
	public: // methods
		/// default constructor
		CMorphology();
		/// default destructor
		~CMorphology();

		/** Performes a dilatation using a 3x3 mask specificed by three numbers
		q10,q20,q30, whose binary representation specifies the mask.
		Color index 0 is background, outside image, background is assumed.
		This function is very fast.
		@param Img Source-target image. Must be 1 b/p.
		@param q10 Bitmask for the first row in mask (values from 0 to 7). 
		@param q20 Bitmask for the second row in mask (values from 0 to 7). 
		@param q30 Bitmask for the third row in mask (values from 0 to 7).
		@return False, if source/target image is empty or not 1 b/p.
		@version 0.90
		@author Implementation by Ivar Balslev (ivb@mip.sdu.dk)
		@see Dilate */
		static bool DilateFast(CStdImage& Img,unsigned short q10,unsigned short q20,unsigned short q30);

		/** Performes an erotion using a 3x3 mask specificed by three numbers
		q10,q20,q30, whose binary representation specifies the mask.
		Color index 0 is background, outside image, background is assumed.
		This function is very fast.
		@param Img Source-target image. Must be 1 b/p.
		@param q10 Bitmask for the first row in mask (values from 0 to 7). 
		@param q20 Bitmask for the second row in mask (values from 0 to 7). 
		@param q30 Bitmask for the third row in mask (values from 0 to 7).
		@return False, if source/target image is empty or not 1 b/p.
		@version 0.90
		@author Implementation by Ivar Balslev (ivb@mip.sdu.dk)
		@see Erode */
		static bool ErodeFast(CStdImage& Img,unsigned short q10,unsigned short q20,unsigned short q30);

		/** Performs an erosion using "ImgMask" as the mask where active positions are pixel
		values different from 0. The central pixel
		(w/2,h/2) is the effektive origin of the erosion process.
		@param ImgMask The mask to performe erotion with.
		@param Img pointer to the source-target image. If the image is 8 b/p the resulting
			image contains 0 for background pixels and 255 for foreground pixels.
		@return False, if either ImgMask or Img is empty or if Img is not 1 or 8 b/p.
		@version 0.90
		@author Implementation by Ivar Balslev (ivb@mip.sdu.dk)
		@see ErodeFast */
		static bool Erode(const CStdImage& ImgMask, CStdImage& Img);

		/** Performs a dilatation using "ImgMask" as the mask where active positions are pixel
		values different from 0. The central pixel
		(w/2,h/2) is the effektive origin of the dilatation process.
		@param ImgMask The mask to performe erotion with.
		@param Img pointer to the source-target image. If the image is 8 b/p the resulting
			image contains 0 for background pixels and 255 for foreground pixels.
		@return False, if either ImgMask or Img is empty or if Img is not 1 or 8 b/p.
		@version 0.90
		@author Implementation by Ivar Balslev (ivb@mip.sdu.dk)
		@see DilateFast */
		static bool Dilate(const CStdImage& ImgMask, CStdImage& Img);

		/** Reduces all black components in a binary image to single pixel wide branches and
		preserves the following properties: 1) Does not remove end points, 2) does not
		break connectedness, and 3) does not cause excessive erosion of the region. The
		algorithm is described in detail in Gonzales and Woods page 491-494. Note: A
		thinning algorithm is not the same as a medial axis transform (MAT).
		@return Total number of iterations (one iteration is when step 1 and 2 have been performed)
			or -1 if the image is empty or not 1 b/p.
		@version 0.50
		@author Implementation by Ren� Dencker Eriksen (edr@mip.sdu.dk)
		@see Skeletonizing
		@see SkeletonZhou */
		static int Thinning(CStdImage& Img);

		/** Transforms all black components in a binary image to a skeleton defined by
		the medial axis transform (MAT). Algorithm implemented with the method explained
		in Gonzales and Woods page 535-538.
		@return Total number of iterations (1 iteration is when all 8 masks have been used)
			or -1 if the image is empty or not 1 b/p.
		@version 0.50
		@author Implementation by Ren� Dencker Eriksen (edr@mip.sdu.dk)
		@see Thinning
		@see SkeletonZhou */
		static int Skeletonizing(CStdImage& Img);
		
		/** A skeleton somewhere between the results of Thinning() and Skeletonizing() is produced.
		The resultning skeleton is more roboust to noise on edges, i.e. it produces less small
		unwanted branches arising from noise on edges. But the skeleton is closer to a real
		MAT compared to the Thinning() algorithm.
		The algorithm is explained in detail in the article "A novel single-pass thinning
		algorithm and an effective set of performance criteria" by C. Quek & G. S. Ng. R. W.
		Zhou. Pattern Recognition Letters, 16:1267-1275, 1995.
		The parameter PreserveCorners is an additional feature to the original algorithm. It prevents
		the algorithm from eroding corners and the result is then very close to a MAT.
		@param Img Both source and target image. Must be 1 b/p.
		@param PreserveCorners An additional feature to the algorithm preventing it from eroding corners.
			If set to false, the algorithm is exactly as the one described in the article. To get more
			information about this contact Ren� Dencker at edr@mip.sdu.dk.
		@return Total number of iterations or -1 if the image is empty or not 1 b/p.
		@version 0.50
		@author Implementation by Ren� Dencker Eriksen (edr@mip.sdu.dk)
		@see Thinning
		@see Skeletonizing */
		static int SkeletonZhou(CStdImage& Img, bool PreserveCorners);
};

/////////////////////////////////////////////////
//// Inline methods
/////////////////////////////////////////////////

/*@}*/ /* end group "algorithms" */

} // end namespace ipl

#endif //_IPL98_MORPHOLOGY_H
