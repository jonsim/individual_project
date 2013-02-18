/**
 * @file        Vision.h
 * @brief       Functions to manage and control the vision (from the Kinect).
 */
#ifndef VISION_H
#define VISION_H

/*-------------------- INCLUDES --------------------*/
#include "Common.h"
// openni (note warnings are suppressed (and boy are there a lot of them).
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wreorder"
    #include <XnOpenNI.h>
    #include <XnLog.h>
    #include <XnCppWrapper.h>
    #include <XnFPSCalculator.h>
#pragma GCC diagnostic pop
// opencv
#include <cv.h>
#include <highgui.h>


/*-------------------- DEFINES  --------------------*/
#define VISION_XML_CONFIG_PATH       "CameraConfiguration.xml"
#define VISION_XML_CONFIG_PATH_LOCAL "/home/jon/individual_project/CameraConfiguration.xml"
#define DEPTH_STREAM
#define COMPRESSION_QUALITY 20    // quality of streamed images. can be 0-100 with a higher number representing a larger file size but a higher quality image.
#define MAX_DEPTH 10000           // maximum depth the kinect sensor can read. must be in the openni libraries somewhere but i cant find it.
//#define COLOR_STREAM
#if COLOR_STREAM
    #error "NO COLOUR STREAM PLESE :(... or write it yourself"
#endif


/*--------------------  MACROS  --------------------*/
// None.


/*---------------- CLASS DEFINITION ----------------*/
using namespace xn; // TODO GET RID OF THIS LINE!


class Vision
{
public:
    Vision (void);
    ~Vision (void);
    
    void  captureFrame  (void);
    const std::vector<uint8_t>* compressFrame (void);
    void  compressFrameToDisk (const char* filename);
    void  buildDepthHistogram (void);
    uint32_t queryDepthHistogram (uint16_t v);
    float getFPS (void);
    

private:
    void loadCameraConfiguration   (void);
    void initialiseCamera          (void);
    void shutdownCamera            (void);
    void setupServers              (void);
    void setupServer               (void);
    void checkForClientConnections (void);
    
    void   createColourDepthImage (cv::Mat* dst, const uint16_t* src);
    XnBool fileExists             (const char *fn);
    
    // Vision Variables
    Context         mContext;
    ScriptNode      mScriptNode;
    // OpenNI image containers
    DepthGenerator  mDepthGenerator;
    ImageGenerator  mColorGenerator;
    DepthMetaData   mDepthMetaData;
    ImageMetaData   mColorMetaData;
    const uint16_t* mDepthData;
    XnFPSData       mXnFPS;
    //const uint8_t*  mColorData;
    // OpenCV image containers
    cv::Mat              mStreamingDepthRaw;
    std::vector<uint8_t> mStreamingDepthJPEG;
    // Other image algorithm datas
    uint32_t        mDepthHistogram[MAX_DEPTH];
};

#endif