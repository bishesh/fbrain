/*==========================================================================
  
  © Université de Strasbourg - Centre National de la Recherche Scientifique
  
  Date: 09/07/2012
  Author(s): Julien Pontabry (pontabry@unistra.fr)
  
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

#ifndef BTK_DIFFUSION_MODEL_H
#define BTK_DIFFUSION_MODEL_H

// ITK includes
#include "itkSmartPointer.h"
#include "itkMacro.h"
#include "itkProcessObject.h"
#include "itkContinuousIndex.h"
#include "itkPoint.h"

// Local includes
#include "btkGradientDirection.h"

namespace btk
{

/**
 * @brief Diffusion MRI modelization.
 * @author Julien Pontabry
 * @ingroup Diffusion
 */
class DiffusionModel : public itk::ProcessObject
{
    public:
        typedef DiffusionModel                  Self;
        typedef itk::ProcessObject              Superclass;
        typedef itk::SmartPointer< Self >       Pointer;
        typedef itk::SmartPointer< const Self > ConstPointer;

        typedef itk::ContinuousIndex< float,3 > ContinuousIndex;
        typedef itk::Point< float,3 >           PhysicalPoint;

        itkTypeMacro(DiffusionModel,itk::ProcessObject);

        //        virtual void MainDirectionsAt(Point &p) = 0;

        /**
         * @brief Get modeling at continuous index and gradient direction.
         * @param cindex Location in the image space.
         * @param direction Gradient direction were the model response is wanted.
         * @return Model response in direction direction at cindex in image space.
         */
        virtual float ModelAt(ContinuousIndex cindex, btk::GradientDirection direction) = 0;

        /**
         * @brief Get modeling at physical point and gradient direction.
         * @param point Point in the physical space.
         * @param direction Gradient direction were the model response is wanted.
         * @return Model response in direction direction at point in physical space.
         */
        virtual float ModelAt(PhysicalPoint point, btk::GradientDirection direction) = 0;

        /**
         * @brief Get signal at continuous index and gradient direction.
         * @param cindex Location in the image space.
         * @param direction Gradient direction were the model response is wanted.
         * @return Signal response in direction direction at cindex in image space.
         */
        virtual float SignalAt(ContinuousIndex cindex, btk::GradientDirection direction) = 0;

        /**
         * @brief Get signal at physical point and gradient direction.
         * @param point Point in the physical space.
         * @param direction Gradient direction were the model response is wanted.
         * @return Signal response in direction direction at point in physical space.
         */
        virtual float SignalAt(PhysicalPoint point, btk::GradientDirection direction) = 0;

    protected:
        /**
         * @brief Print a message on output stream.
         * @param os Output stream where the message is printed.
         * @param indent Indentation.
         */
        virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;
};

} // namespace btk

#endif // BTK_DIFFUSION_MODEL_H
