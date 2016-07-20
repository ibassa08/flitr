/* Framework for Live Image Transformation (FLITr)
 * Copyright (c) 2010 CSIR
 *
 * This file is part of FLITr.
 *
 * FLITr is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * FLITr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FLITr. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef FIP_MOTION_DETECT_H
#define FIP_MOTION_DETECT_H 1

#include <flitr/image_processor.h>
#include <flitr/image_processor_utils.h>
#include <math.h>

namespace flitr {
    
    /*! Applies Gaussian filter. */
    class FLITR_EXPORT FIPMotionDetect : public ImageProcessor
    {
    public:
        
        /*! Constructor given the upstream producer.
         *@param upStreamProducer The upstream image producer.
         *@param images_per_slot The number of images per image slot from the upstream producer.
         *@param buffer_size The size of the shared image buffer of the downstream producer.*/
        FIPMotionDetect(ImageProducer& upStreamProducer, uint32_t images_per_slot, uint32_t buffer_size=FLITR_DEFAULT_SHARED_BUFFER_NUM_SLOTS);
        
        /*! Virtual destructor */
        virtual ~FIPMotionDetect();
        
        /*!Sets the filter radius of the Gaussian filter. Has no effect if intImgApprox>0.
        @sa getStandardDeviation */
        virtual void setFilterRadius(const float filterRadius);
        
        /*!Sets the kernel width of both the Gaussian and the approx BoxFilter Gaussian! Also affects the BoxFilter Gaussian's standard deviation
         @sa getStandardDeviation */
        virtual void setKernelWidth(const int kernelWidth);
        
        //Returns the Gaussian standard deviation or approximate boxfilter Gaussian.
        float getStandardDeviation() const
        {
            if (intImgApprox_==0)
            {
                return gaussianFilter_.getStandardDeviation();
            } else
            {//Gaussian approximated by multiple average filters.
                const size_t kernelWidth_=boxFilter_.getKernelWidth();                
                return sqrtf(intImgApprox_ * (kernelWidth_*kernelWidth_ - 1) * (1.0f/12.0f));
            }
        }
        
        /*! Method to initialise the object.
         *@return Boolean result flag. True indicates successful initialisation.*/
        virtual bool init();
        
        /*!Synchronous trigger method. Called automatically by the trigger thread in ImageProcessor base class if started.
         *@sa ImageProcessor::startTriggerThread*/
        virtual bool trigger();


        void setTitle(const std::string &title)
        {
            Title_=title;
        }

        void setRadius(float r)//radius = sd * 2
        {
            FilterRadius_ = r;
            setFilterRadius(FilterRadius_);
        }

        void setWidth(float r)
        {
            KernelWidth_ = r;
            setKernelWidth(r);
        }

        float getRadius() const //radius = sd * 2
        {
            return FilterRadius_;
        }

        float getWidth() const
        {
            return KernelWidth_;
        }

        virtual int getNumberOfParms()
        {
            return 2;
        }

        virtual flitr::Parameters::EParmType getParmType(int id)
        {
            return flitr::Parameters::PARM_FLOAT;
        }

        virtual std::string getParmName(int id)
        {
            switch (id)
            {
            case 0 :return std::string("Filter Radius");
            case 1 :return std::string("Kernel Width");
            }
            return std::string("???");
        }

        virtual std::string getTitle()
        {
            return Title_;
        }

        virtual float getFloat(int id)
        {
            switch (id)
            {
            case 0 : return getRadius();
            case 1 : return getWidth();
            }

            return 0.0f;
        }

        virtual bool getFloatRange(int id, float &low, float &high)
        {
            if (id==0)
            {
                low=1.0; high=100.0;
                return true;
            }
            if (id==1)
            {
                low=1.0; high=32.0;
                return true;
            }

            return false;
        }

        virtual bool setFloat(int id, float v)
        {
            switch (id)
            {
                case 0 : setRadius(v); return true;
                case 1 : setWidth(v); return true;
            }

            return false;
        }

        virtual void enable(bool state=true)
        {
            Enabled_ = state;
        }

        virtual bool isEnabled()
        {
            return Enabled_;
        }

    private:
        short intImgApprox_;
        
        uint8_t *scratchData_;
        
        double *intImageScratchData_;
        
        GaussianFilter gaussianFilter_; //No significant state associated with this.

        BoxFilterII boxFilter_; //No significant state associated with this.
        
        bool Enabled_;
        std::string Title_;
        float FilterRadius_;
        float KernelWidth_;

    };
    
}

#endif //FIP_MOTION_DETECT_H
