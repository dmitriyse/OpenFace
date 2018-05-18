///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Tadas Baltrusaitis, all rights reserved.
//
// ACADEMIC OR NON-PROFIT ORGANIZATION NONCOMMERCIAL RESEARCH USE ONLY
//
// BY USING OR DOWNLOADING THE SOFTWARE, YOU ARE AGREEING TO THE TERMS OF THIS LICENSE AGREEMENT.  
// IF YOU DO NOT AGREE WITH THESE TERMS, YOU MAY NOT USE OR DOWNLOAD THE SOFTWARE.
//
// License can be found in OpenFace-license.txt

//     * Any publications arising from the use of this software, including but
//       not limited to academic journal and conference publications, technical
//       reports and manuals, must cite at least one of the following works:
//
//       OpenFace: an open source facial behavior analysis toolkit
//       Tadas Baltrušaitis, Peter Robinson, and Louis-Philippe Morency
//       in IEEE Winter Conference on Applications of Computer Vision, 2016  
//
//       Rendering of Eyes for Eye-Shape Registration and Gaze Estimation
//       Erroll Wood, Tadas Baltrušaitis, Xucong Zhang, Yusuke Sugano, Peter Robinson, and Andreas Bulling 
//       in IEEE International. Conference on Computer Vision (ICCV),  2015 
//
//       Cross-dataset learning and person-speci?c normalisation for automatic Action Unit detection
//       Tadas Baltrušaitis, Marwa Mahmoud, and Peter Robinson 
//       in Facial Expression Recognition and Analysis Challenge, 
//       IEEE International Conference on Automatic Face and Gesture Recognition, 2015 
//
//       Constrained Local Neural Fields for robust facial landmark detection in the wild.
//       Tadas Baltrušaitis, Peter Robinson, and Louis-Philippe Morency. 
//       in IEEE Int. Conference on Computer Vision Workshops, 300 Faces in-the-Wild Challenge, 2013.    
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma unmanaged

// Include all the unmanaged things we need.

#include <opencv2/core/core.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <set>

#include <OpenCVWrappers.h>
#include "ImageManipulationHelpers.h"

#pragma managed

using namespace OpenCVWrappers;


namespace UtilitiesOF {

	public ref class GrayscaleRawImageConverter : System::IDisposable
	{
	private:

		cv::Mat_<uchar> * gray_buffer;

	public:

		GrayscaleRawImageConverter()
		{
			gray_buffer = new cv::Mat_<uchar>();
		}

		RawImage ^ Convert(RawImage^ colorImage) {
			Utilities::ConvertToGrayscale_8bit(colorImage->Mat, *gray_buffer);

			auto gray_frame = gcnew OpenCVWrappers::RawImage(gray_buffer->size().width, gray_buffer->size().width, CV_8UC3);

			gray_buffer->copyTo(gray_frame->Mat);

			return gray_frame;
		}

		// Finalizer. Definitely called before Garbage Collection,
		// but not automatically called on explicit Dispose().
		// May be called multiple times.
		!GrayscaleRawImageConverter()
		{
			// Automatically closes capture object before freeing memory.	
			if (gray_buffer != nullptr)
			{
				delete gray_buffer;
			}
		}

		// Destructor. Called on explicit Dispose() only.
		~GrayscaleRawImageConverter()
		{
			this->!GrayscaleRawImageConverter();
		}
	};
}