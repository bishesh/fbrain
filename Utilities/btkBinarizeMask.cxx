/*==========================================================================

  © Université de Strasbourg - Centre National de la Recherche Scientifique

  Date: 29/08/2012
  Author(s): Marc Schweitzer (marc.schweitzer@unistra.fr)

  This software is governed by the CeCILL-B license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL-B
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited
  liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.

  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL-B license and that you accept its terms.

==========================================================================*/

/* ITK */
#include "itkImage.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageRegionConstIteratorWithIndex.h"

/* BTK */

#include "btkImageHelper.h"

/* OTHERS */
#include "iostream"
#include <tclap/CmdLine.h>

int main(int argc, char * argv[] )
{
    typedef itk::Image< float, 3 > FloatImage;
    typedef itk::Image< short, 3> ShortImage;

    typedef itk::ImageRegionIteratorWithIndex< ShortImage  >  Iterator;
    typedef itk::ImageRegionConstIteratorWithIndex< FloatImage >  ConstIterator;

     TCLAP::CmdLine cmd("Binarize a float mask into short", ' ', "Unversioned");
     TCLAP::ValueArg<std::string> inputArg("i","input", "input image in float",true,"","string",cmd);
     TCLAP::ValueArg<std::string> outputArg("o","output", "output image in short",true,"","string",cmd);
     TCLAP::ValueArg<float> threshArg("t","threshold","threshold for the binarization (default 0.9)",false,0.5,"float",cmd);



     cmd.parse(argc,argv);
     std::string inputName = inputArg.getValue();
     std::string outputName = outputArg.getValue();
     float threshold = threshArg.getValue();

     FloatImage::ConstPointer floatImage = btk::ImageHelper<FloatImage>::ReadConstImage(inputName);
     ShortImage::Pointer shortImage = ShortImage::New();

     shortImage = btk::ImageHelper<FloatImage, ShortImage>::CreateNewImageFromPhysicalSpaceOfConst(floatImage);

     Iterator shortIt(shortImage, shortImage->GetLargestPossibleRegion());

     ConstIterator floatIt(floatImage, floatImage->GetLargestPossibleRegion());

     for(shortIt.GoToBegin(), floatIt.GoToBegin(); !shortIt.IsAtEnd() && !floatIt.IsAtEnd(); ++shortIt, ++floatIt)
     {
         if(floatIt.Get() > threshold )
         {
             shortIt.Set(1);
         }
         else
         {
             shortIt.Set(0);
         }
     }

     btk::ImageHelper<ShortImage>::WriteImage(shortImage, outputName);

}

