/* mbed Microcontroller Library
 * Copyright (c) 2015 ARM Limited
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

#ifndef JOYSTICK_SERVICE_H_
#define JOYSTICK_SERVICE_H_

#include "mbed.h"

#include "HIDServiceBase.h"

static const char DEVICE_NAME[] = "uJoy";
static const char SHORT_DEVICE_NAME[] = "joystick0";

enum ButtonState
{
    BUTTON_UP,
    BUTTON_DOWN
};

enum JoystickButton
{
    JOYSTICK_BUTTON_1       = 0x1,
    JOYSTICK_BUTTON_2       = 0x2,
};

report_map_t JOYSTICK_REPORT_MAP = {
    USAGE_PAGE(1),      0x01,         // Generic Desktop
    USAGE(1),           0x04,         // Joystick
    COLLECTION(1),      0x01,         // Application
    COLLECTION(1),      0x00,         //  Physical
    USAGE_PAGE(1),      0x09,         //   Buttons
    USAGE_MINIMUM(1),   0x01,
    USAGE_MAXIMUM(1),   0x03,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_COUNT(1),    0x03,         //   2 bits (Buttons)
    REPORT_SIZE(1),     0x01,
    INPUT(1),           0x02,         //   Data, Variable, Absolute
    REPORT_COUNT(1),    0x01,         //   6 bits (Padding)
    REPORT_SIZE(1),     0x05,
    INPUT(1),           0x01,         //   Constant
    USAGE_PAGE(1),      0x01,         //   Generic Desktop
    USAGE(1),           0x30,         //   X
    USAGE(1),           0x31,         //   Y
    USAGE(1),           0x32,         //   Z
    USAGE(1),           0x33,         //   Rx
    LOGICAL_MINIMUM(1), 0x81,         //   -127
    LOGICAL_MAXIMUM(1), 0x7f,         //   127
    REPORT_SIZE(1),     0x08,         //   Three bytes
    REPORT_COUNT(1),    0x04,
    INPUT(1),           0x02,         //   Data, Variable, Absolute (unlike mouse)
    END_COLLECTION(0),
    END_COLLECTION(0),
};

class JoystickService: public HIDServiceBase
{
public:
    JoystickService(BLE &_ble);

    int setSpeed(int8_t x, int8_t y, int8_t z);

    int setButton(JoystickButton button, ButtonState state);
    void pressButton(JoystickButton button);
    virtual void sendCallback(void);
protected:
    uint8_t buttonsState;
    uint8_t speed[4];

public:
    uint32_t failedReports;
};

#endif /* !JOYSTICK_SERVICE_H_ */
