/*
TWC Manager for ESP32
Copyright (C) 2020 Jarl Nicolson
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "twc_connector.h"

TeslaConnector::TeslaConnector(uint16_t twcid, uint8_t max_charge_rate) :
    twcid(twcid),
    max_charge_rate_(max_charge_rate)
{
    vin_[17] = '\0';
}

uint8_t * TeslaConnector::GetVin() {
    return vin_;
}

void TeslaConnector::SetActualCurrent(uint16_t current) {
    actual_current_ = current;
}
