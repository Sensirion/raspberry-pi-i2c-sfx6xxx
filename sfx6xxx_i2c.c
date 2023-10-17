/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:     sensirion-driver-generator 0.32.0
 * Product:       sfx6xxx
 * Model-Version: 2.2.0
 */
/*
 * Copyright (c) 2023, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sfx6xxx_i2c.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"
#include "sensirion_i2c_hal.h"

#define sensirion_hal_sleep_us sensirion_i2c_hal_sleep_usec

static uint8_t communication_buffer[18] = {0};

static uint8_t _i2c_address;
static int16_t _flow_offset = 0.0;
static int16_t _flow_scale_factor = 1.0;
static uint16_t _flow_unit = 0;
static int16_t _full_flow = 0;
static uint16_t _gas_id = 0;

void sfx6xxx_init(uint8_t i2c_address) {
    _i2c_address = i2c_address;
}

float signal_temperature(int16_t temperature_raw) {
    float temperature = 0.0;
    temperature = temperature_raw / 200.0;
    return temperature;
}

float signal_flow(int16_t flow_raw, int16_t flow_scale_factor,
                  int16_t flow_offset) {
    float flow = 0.0;
    float scale_factor = (float)(flow_scale_factor);
    flow = (float)(flow_raw - flow_offset) / scale_factor;
    return flow;
}

int16_t signal_raw_flow(float flow, int16_t flow_scale_factor,
                        int16_t flow_offset) {
    int16_t raw_flow = 0;
    raw_flow = (int16_t)((int)(flow * flow_scale_factor) + flow_offset);
    return raw_flow;
}

int16_t sfx6xxx_get_gas_calibration(uint16_t measurement_command,
                                    int16_t* flow_scale_factor,
                                    int16_t* flow_offset, uint16_t* flow_unit,
                                    int16_t* full_scale_flow,
                                    uint16_t* gas_id) {
    int16_t local_error = 0;
    local_error = sfx6xxx_prepare_read_gas_calibration(measurement_command);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sfx6xxx_read_gas_calibration(
        flow_scale_factor, flow_offset, flow_unit, full_scale_flow, gas_id);
    return local_error;
}

int16_t sfx6xxx_start_o2_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_O2_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sfx6xxx_start_o2_continuous_measurement();
    return local_error;
}

int16_t sfx6xxx_start_air_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_AIR_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sfx6xxx_start_air_continuous_measurement();
    return local_error;
}

int16_t sfx6xxx_start_co2_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_CO2_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sfx6xxx_start_co2_continuous_measurement();
    return local_error;
}

int16_t sfx6xxx_start_n2o_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_N2O_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sfx6xxx_start_n2o_continuous_measurement();
    return local_error;
}

int16_t sfx6xxx_start_ar_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_AR_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sfx6xxx_start_ar_continuous_measurement();
    return local_error;
}

int16_t
sfx6xxx_start_o2_in_air_continuous_measurement(uint16_t volume_fraction) {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_O2_IN_AIR_CONTINUOUS_MEASUREMENT_CMD_ID, &_flow_scale_factor,
        &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error =
        ll_sfx6xxx_start_o2_in_air_continuous_measurement(volume_fraction);
    return local_error;
}

int16_t sfx6xxx_start_raw_thermal_conductivity_continuous_measurement() {
    int16_t local_error = 0;
    local_error = sfx6xxx_get_gas_calibration(
        START_RAW_THERMAL_CONDUCTIVITY_CONTINUOUS_MEASUREMENT_CMD_ID,
        &_flow_scale_factor, &_flow_offset, &_flow_unit, &_full_flow, &_gas_id);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error =
        ll_sfx6xxx_start_raw_thermal_conductivity_continuous_measurement();
    return local_error;
}

int16_t sfx6xxx_read_measurement_data_raw(int16_t* arg_0,
                                          uint16_t* a_status_word) {
    int16_t flow_raw = 0;
    int16_t reserved = 0;
    uint16_t status = 0u;
    int16_t local_error = 0;
    local_error =
        ll_sfx6xxx_read_measurement_data(&flow_raw, &reserved, &status);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *arg_0 = flow_raw;
    *a_status_word = (uint16_t)(status);
    return local_error;
}

int16_t sfx6xxx_read_measurement_data(float* a_flow, uint16_t* a_status_word) {
    int16_t raw_flow = 0;
    uint16_t status_word = 0u;
    int16_t local_error = 0;
    local_error = sfx6xxx_read_measurement_data_raw(&raw_flow, &status_word);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *a_flow = signal_flow(raw_flow, _flow_scale_factor, _flow_offset);
    *a_status_word = status_word;
    return local_error;
}

int16_t sfx6xxx_read_flow_raw(int16_t* arg_0) {
    int16_t flow_raw = 0;
    int16_t local_error = 0;
    local_error = ll_sfx6xxx_read_flow(&flow_raw);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *arg_0 = flow_raw;
    ;
    return local_error;
}

int16_t sfx6xxx_read_flow(float* a_flow) {
    int16_t raw_flow = 0;
    int16_t local_error = 0;
    local_error = sfx6xxx_read_flow_raw(&raw_flow);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *a_flow = signal_flow(raw_flow, _flow_scale_factor, _flow_offset);

    return local_error;
}

int16_t sfx6xxx_read_raw_temperature(int16_t* arg_0) {
    int16_t raw_temperature = 0;
    int16_t local_error = 0;
    local_error = sfx6xxx_get_raw_temperature(&raw_temperature);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sfx6xxx_reset_pointer_to_measurement_buffer();
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *arg_0 = raw_temperature;
    ;
    return local_error;
}

int16_t sfx6xxx_read_temperature(float* a_temperature) {
    int16_t raw_temperature = 0;
    int16_t local_error = 0;
    local_error = sfx6xxx_read_raw_temperature(&raw_temperature);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *a_temperature = signal_temperature(raw_temperature);

    return local_error;
}

int16_t sfx6xxx_update_setpoint(float flow) {
    int16_t raw_flow = 0;
    int16_t local_error = 0;
    raw_flow = signal_raw_flow(flow, _flow_scale_factor, _flow_offset);
    local_error = ll_sfx6xxx_update_setpoint(raw_flow);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sfx6xxx_reset_pointer_to_measurement_buffer();
    return local_error;
}

int16_t sfx6xxx_read_product_identifier(uint32_t* product_identifier,
                                        uint8_t* serial_number,
                                        uint16_t serial_number_size) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe102);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 12);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *product_identifier = sensirion_common_bytes_to_uint32_t(&buffer_ptr[0]);
    sensirion_common_copy_bytes(&buffer_ptr[4], (uint8_t*)serial_number,
                                serial_number_size);
    return local_error;
}

int16_t sfx6xxx_reset_pointer_to_measurement_buffer() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe000);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t ll_sfx6xxx_update_setpoint(int16_t setpoint) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xf054);
    local_offset =
        sensirion_i2c_add_int16_t_to_buffer(buffer_ptr, local_offset, setpoint);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_update_init_step(uint16_t init_step) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe1b9);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, init_step);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_update_customer_gain(uint16_t customer_gain) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe1b2);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, customer_gain);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t ll_sfx6xxx_start_o2_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3603);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_start_air_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3608);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_start_co2_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3615);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_start_n2o_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x361e);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_start_ar_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3624);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_start_raw_thermal_conductivity_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3624);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(50 * 1000);
    return local_error;
}

int16_t
ll_sfx6xxx_start_o2_in_air_continuous_measurement(uint16_t volume_fraction) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3650);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, volume_fraction);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t sfx6xxx_stop_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3ff9);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t ll_sfx6xxx_read_measurement_data(int16_t* flow, int16_t* reserved,
                                         uint16_t* status_word) {
    int16_t local_error = NO_ERROR;
    uint8_t buffer_ptr[9] = {0};
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 6);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *flow = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *reserved = sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *status_word = sensirion_common_bytes_to_uint16_t(&buffer_ptr[4]);
    return local_error;
}

int16_t ll_sfx6xxx_read_flow(int16_t* flow) {
    int16_t local_error = NO_ERROR;
    uint8_t buffer_ptr[3] = {0};
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *flow = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t sfx6xxx_get_raw_temperature(int16_t* temperature) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe102);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *temperature = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t sfx6xxx_force_open_valve() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3fe4);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_reset_force_open_valve() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3f65);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_force_close_valve() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3fef);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_reset_force_close_valve() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3f6e);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_update_gas_concentration(uint16_t volume_fraction) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe17d);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, volume_fraction);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_prepare_read_gas_calibration(uint16_t measurement_command) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3661);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, measurement_command);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_read_gas_calibration(int16_t* flow_scale_factor,
                                     int16_t* flow_offset, uint16_t* flow_unit,
                                     int16_t* full_scale_flow,
                                     uint16_t* gas_id) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe151);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 10);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *flow_scale_factor = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *flow_offset = sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *flow_unit = sensirion_common_bytes_to_uint16_t(&buffer_ptr[4]);
    *full_scale_flow = sensirion_common_bytes_to_int16_t(&buffer_ptr[6]);
    *gas_id = sensirion_common_bytes_to_uint16_t(&buffer_ptr[8]);
    return local_error;
}

int16_t sfx6xxx_enable_raw_flow_values() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3fde);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sfx6xxx_disable_raw_flow_values() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3f5f);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}