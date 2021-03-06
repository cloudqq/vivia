/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include "vpFseIO.h"

#include "vpFseTrackIO.h"

#include <assert.h>

//-----------------------------------------------------------------------------
vpFseIO::vpFseIO() :
  ImageHeight(0)
{}

//-----------------------------------------------------------------------------
vpFseIO::~vpFseIO()
{
  delete this->TrackIO;
}

//-----------------------------------------------------------------------------
void vpFseIO::SetTrackModel(vtkVgTrackModel* trackModel,
                            vpTrackIO::TrackStorageMode storageMode,
                            vpTrackIO::TrackTimeStampMode timeStampMode,
                            vtkVgTrackTypeRegistry* trackTypes,
                            vtkMatrix4x4* geoTransform,
                            vpFrameMap* frameMap)
{
  delete this->TrackIO;
  vpFseTrackIO* io = new vpFseTrackIO(trackModel, storageMode, timeStampMode,
                                      trackTypes, geoTransform, frameMap);
  io->SetImageHeight(this->ImageHeight);
  io->SetTracksFileName(this->TracksFilename.c_str());
  this->TrackIO = io;
}

//-----------------------------------------------------------------------------
void vpFseIO::SetEventModel(vtkVgEventModel*,
                            vtkVgEventTypeRegistry*)
{
}

//-----------------------------------------------------------------------------
void vpFseIO::SetActivityModel(vtkVgActivityManager*,
                               vpActivityConfig*)
{
}

//-----------------------------------------------------------------------------
void vpFseIO::SetTracksFileName(const char* tracksFileName)
{
  this->TracksFilename = tracksFileName;
  if (this->TrackIO)
    {
    static_cast<vpFseTrackIO*>(this->TrackIO)->SetTracksFileName(tracksFileName);
    }
}

//-----------------------------------------------------------------------------
void vpFseIO::SetImageHeight(unsigned int imageHeight)
{
  this->ImageHeight = imageHeight;
  if (this->TrackIO)
    {
    static_cast<vpFseTrackIO*>(this->TrackIO)->SetImageHeight(imageHeight);
    }
}

//-----------------------------------------------------------------------------
unsigned int vpFseIO::GetImageHeight() const
{
  return this->ImageHeight;
}
