/*
 ******************************************************************************
  Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

#ifndef SPARK_WIRING_LOCATION_H
#define	SPARK_WIRING_LOCATION_H

#include "spark_wiring_string.h"
#include "cellular_hal.h"

namespace spark {

enum class LocationSource {
  Any,
  WiFi,
  Cell,
  GPS
};

class LocationClass
{
  static const unsigned short DefaultTimeout = 120; /* seconds */
  static const unsigned int DefaultTargetAccuracy = 10000; /* meters */

public:

  LocationClass() :
    _ready(false), _source(LocationSource::Any), _timeout(DefaultTimeout),
    _targetAccuracy(DefaultTargetAccuracy) {}

  void begin(unsigned short timeout = DefaultTimeout,
      unsigned int targetAccuracy = DefaultTargetAccuracy);

  bool find(LocationSource source = LocationSource::Any);
  bool ready();

  const String latitude();
  const String longitude();
  const String altitude();
  const String uncertainty();
  const String date();
  const String time();

protected:

  bool _ready;
  LocationSource _source;

  unsigned short _timeout;
  unsigned int _targetAccuracy;

  CellularLocation _location;

  bool findWiFi();
  bool findCell();
  bool findGPS();

  bool readyCell();
};


extern LocationClass Location;

}   // namespace Spark

#endif	/* SPARK_WIRING_LOCATION_H */

