/******************************************************************************
 * Copyright 2023 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/canbus_vehicle/demo/protocol/ultr_sensor_2_508.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace demo {

using ::apollo::drivers::canbus::Byte;

Ultrsensor2508::Ultrsensor2508() {}
const int32_t Ultrsensor2508::ID = 0x508;

void Ultrsensor2508::Parse(const std::uint8_t* bytes, int32_t length,
                           Demo* chassis) const {
  chassis->mutable_ultr_sensor_2_508()->set_uiuss9_tof_indirect(
      uiuss9_tof_indirect(bytes, length));
  chassis->mutable_ultr_sensor_2_508()->set_uiuss8_tof_indirect(
      uiuss8_tof_indirect(bytes, length));
  chassis->mutable_ultr_sensor_2_508()->set_uiuss11_tof_indirect(
      uiuss11_tof_indirect(bytes, length));
  chassis->mutable_ultr_sensor_2_508()->set_uiuss10_tof_indirect(
      uiuss10_tof_indirect(bytes, length));
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name':
// 'uiuss9_tof_indirect', 'offset': 0.0, 'order': 'motorola', 'physical_range':
// '[0|65535]', 'physical_unit': 'cm', 'precision': 0.01724, 'type': 'double'}
double Ultrsensor2508::uiuss9_tof_indirect(const std::uint8_t* bytes,
                                           int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.017240;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name':
// 'uiuss8_tof_indirect', 'offset': 0.0, 'order': 'motorola', 'physical_range':
// '[0|65535]', 'physical_unit': 'cm', 'precision': 0.01724, 'type': 'double'}
double Ultrsensor2508::uiuss8_tof_indirect(const std::uint8_t* bytes,
                                           int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.017240;
  return ret;
}

// config detail: {'bit': 55, 'is_signed_var': False, 'len': 16, 'name':
// 'uiuss11_tof_indirect', 'offset': 0.0, 'order': 'motorola', 'physical_range':
// '[0|65535]', 'physical_unit': 'cm', 'precision': 0.01724, 'type': 'double'}
double Ultrsensor2508::uiuss11_tof_indirect(const std::uint8_t* bytes,
                                            int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 7);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.017240;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name':
// 'uiuss10_tof_indirect', 'offset': 0.0, 'order': 'motorola', 'physical_range':
// '[0|65535]', 'physical_unit': 'cm', 'precision': 0.01724, 'type': 'double'}
double Ultrsensor2508::uiuss10_tof_indirect(const std::uint8_t* bytes,
                                            int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.017240;
  return ret;
}
}  // namespace demo
}  // namespace canbus
}  // namespace apollo
