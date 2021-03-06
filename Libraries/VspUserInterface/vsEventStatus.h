/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef __vsEventStatus_h
#define __vsEventStatus_h

namespace vs
{
  enum EventStatus
    {
    UnverifiedEvent,
    VerifiedEvent,
    RejectedEvent
    };
}

typedef enum vs::EventStatus vsEventStatus;

#endif
