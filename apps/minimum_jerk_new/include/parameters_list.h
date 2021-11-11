#pragma once

namespace parameters {

// Setpoint 
float x_start{};
float y_start{};
float z_start{};

float x_mid{};
float y_mid{};
float z_mid{};

float x_final{};
float y_final{};
float z_final{};

float mid_velocity{};

// Quadcopter properties

float motor_thrust_max{}; 
float motor_thrust_min{};

float quad_thrust_max{}; 
float quad_thrust_min{};

float angular_rate_max{};

// Controller properties
float dt{};
float completion_time{};

} // namespace parameters