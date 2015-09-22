/**
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

#include "spark_wiring_location.h"
#include "spark_wiring_platform.h"

using namespace spark;

LocationClass spark::Location;

void LocationClass::begin(unsigned short timeout,
      unsigned int targetAccuracy) {
  _ready = false;
  _timeout = timeout;
  _targetAccuracy = targetAccuracy;
}

bool LocationClass::find(LocationSource source) {
  _ready = false;
  _source = source;

  switch(_source) {
    case LocationSource::WiFi:
      return findWiFi();
    case LocationSource::Cell:
      return findCell();
    case LocationSource::GPS:
      return findGPS();
    default:
      return findGPS() || findCell() || findWiFi();
  }
}

bool LocationClass::ready() {
  // Return true only on first call
  if(_ready) {
    return false;
  }

  switch(_source) {
    case LocationSource::Any:
    case LocationSource::Cell:
      _ready = readyCell();
      break;
  }

  return _ready;
}

bool LocationClass::findWiFi() {
  /* Not supported yet */
  return false;
}

#if Wiring_Cellular

bool LocationClass::findCell() {
  cellular_request_location(_timeout, _targetAccuracy, &_location);
  return true;
}

bool LocationClass::readyCell() {
  return cellular_has_location();
}

#else

bool LocationClass::findCell() {
  /* Not supported on this platform */
  return false;
}

bool LocationClass::readyCell() {
  return false;
}

#endif 

bool LocationClass::findGPS() {
  /* Not supported yet */
  return false;
}

const String LocationClass::latitude() {
  return String(_location.latitude);
}

const String LocationClass::longitude() {
  return String(_location.longitude);
}

const String LocationClass::altitude() {
  return String(_location.altitude);
}

const String LocationClass::uncertainty() {
  return String(_location.uncertainty);
}

const String LocationClass::date() {
  return String(_location.date);
}

const String LocationClass::time() {
  return String(_location.time);
}

