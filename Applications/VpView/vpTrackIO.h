/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef __vpTrackIO_h
#define __vpTrackIO_h

#include <vtkSmartPointer.h>

class vpFrameMap;

class vtkVgTimeStamp;
class vtkVgTrack;
class vtkVgTrackModel;
class vtkVgTrackTypeRegistry;

class vtkMatrix4x4;

class vpTrackIO
{
protected:
  enum TimeStampFlag
    {
    TSF_Time        = 1 << 0,
    TSF_FrameNumber = 1 << 1
    };

public:
  enum TrackStorageMode
    {
    TSM_ImageCoords,
    TSM_InvertedImageCoords,
    TSM_TransformedGeoCoords,
    TSM_HomographyTransformedImageCoords
    };

  enum TrackTimeStampMode
    {
    TTM_TimeOnly           = TSF_Time,
    TTM_FrameNumberOnly    = TSF_FrameNumber,
    TTM_TimeAndFrameNumber = TSF_Time | TSF_FrameNumber
    };

public:
  vpTrackIO(vtkVgTrackModel* trackModel,
            TrackStorageMode storageMode,
            TrackTimeStampMode timeStampMode,
            vtkVgTrackTypeRegistry* trackTypes,
            vtkMatrix4x4* geoTransform,
            vpFrameMap* frameMap);

  virtual ~vpTrackIO();

  void SetOverrideColor(const double color[3]);

  virtual bool ReadTracks() = 0;
  virtual bool ReadTrackTraits();

  virtual bool ImportTracks(vtkIdType idsOffset, float offsetX, float offsetY);

  virtual bool WriteTracks(const char* filename,
                           bool writeSceneElements) const = 0;

  virtual bool GetNextValidTrackFrame(vtkVgTrack* track,
                                      unsigned int startFrame,
                                      vtkVgTimeStamp& timeStamp) const;

  virtual bool GetPrevValidTrackFrame(vtkVgTrack* track,
                                      unsigned int startFrame,
                                      vtkVgTimeStamp& timeStamp) const;

  virtual vtkIdType GetModelTrackId(unsigned int sourceId) const;

  static void GetDefaultTrackColor(int trackId, double (&color)[3]);

protected:
  virtual unsigned int GetImageHeight() const = 0;

protected:
  friend class vpFileTrackIOImpl;

  vtkVgTrackModel* TrackModel;
  vtkVgTrackTypeRegistry* TrackTypes;

  TrackStorageMode StorageMode;
  TrackTimeStampMode TimeStampMode;
  vtkSmartPointer<vtkMatrix4x4> GeoTransform;
  vpFrameMap* FrameMap;
  double OverrideColor[3];
  bool HasOverrideColor;
};

#endif // __vpTrackIO_h
