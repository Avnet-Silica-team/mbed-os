/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __BLE_ADVGATEWAY_H__
#define __BLE_ADVGATEWAY_H__

#include "cmsis_compiler.h"
#include "ble/BLE.h"

/**
* @class advGateway
* @brief advGateway Service. This sets up a device to broadcast advertising packets to an Gateway.
*/
class advGateway
{
public:
    typedef const uint8_t LocationUUID_t[22];

    union Payload {
		uint8_t raw[22];
        struct {
            uint8_t proximityUUID[22];
        };


        Payload(LocationUUID_t uuid)
        {
            memcpy(proximityUUID, uuid, sizeof(LocationUUID_t));
        }
    };

public:
    advGateway(BLE            &_ble,
            LocationUUID_t  uuid) :
        ble(_ble), data(uuid)
	{
        // Generate the 0x020106 part of the advGateway Prefix.
        ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE );
        // Generate the part of the advGateway Prefix.
        ble.accumulateAdvertisingPayload(GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA, data.raw, sizeof(data.raw));
        // Set advertising type.
        ble.setAdvertisingType(GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);
    }

	void updatePayload( LocationUUID_t  uuid )
	{
		ble.clearAdvertisingPayload();
		ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE );
		memcpy(data.proximityUUID, uuid, sizeof(LocationUUID_t));
		ble.accumulateAdvertisingPayload(GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA, data.raw, sizeof(data.raw));
		ble.setAdvertisingType(GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);
	}

protected:
    BLE     &ble;
    Payload  data;
};

typedef advGateway advGatewayService; /* This type-alias is deprecated. Please use advGateway directly. This alias may be dropped from a future release. */

#endif //__BLE_ADVGATEWAY_H__
