/****************************************************************************
 *
 *   Copyright (c) 2013-2015 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file mc_att_control_params.c
 * Parameters for multicopter attitude controller.
 *
 * @author Lorenz Meier <lorenz@px4.io>
 * @author Anton Babushkin <anton@px4.io>
 */

/**
 * Roll P gain
 *
 * Roll proportional gain, i.e. desired angular speed in rad/s for error 1 rad.
 *
 * @unit 1/s
 * @min 0.0
 * @max 12
 * @decimal 2
 * @increment 0.1
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_ROLL_P, 6.5f);

/**
 * Pitch P gain
 *
 * Pitch proportional gain, i.e. desired angular speed in rad/s for error 1 rad.
 *
 * @unit 1/s
 * @min 0.0
 * @max 12
 * @decimal 2
 * @increment 0.1
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_PITCH_P, 6.5f);

/**
 * Yaw P gain
 *
 * Yaw proportional gain, i.e. desired angular speed in rad/s for error 1 rad.
 *
 * @unit 1/s
 * @min 0.0
 * @max 5
 * @decimal 2
 * @increment 0.1
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_YAW_P, 2.8f);

/**
 * Yaw weight
 *
 * A fraction [0,1] deprioritizing yaw compared to roll and pitch in non-linear attitude control.
 * Deprioritizing yaw is necessary because multicopters have much less control authority
 * in yaw compared to the other axes and it makes sense because yaw is not critical for
 * stable hovering or 3D navigation.
 *
 * For yaw control tuning use MC_YAW_P. This ratio has no inpact on the yaw gain.
 *
 * @unit 1/s
 * @min 0.0
 * @max 1.0
 * @decimal 2
 * @increment 0.1
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_YAW_WEIGHT, 0.4f);

/**
 * Max roll rate
 *
 * Limit for roll rate in manual and auto modes (except acro).
 * Has effect for large rotations in autonomous mode, to avoid large control
 * output and mixer saturation.
 *
 * This is not only limited by the vehicle's properties, but also by the maximum
 * measurement rate of the gyro.
 *
 * @unit deg/s
 * @min 0.0
 * @max 1800.0
 * @decimal 1
 * @increment 5
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_ROLLRATE_MAX, 220.0f);

/**
 * Max pitch rate
 *
 * Limit for pitch rate in manual and auto modes (except acro).
 * Has effect for large rotations in autonomous mode, to avoid large control
 * output and mixer saturation.
 *
 * This is not only limited by the vehicle's properties, but also by the maximum
 * measurement rate of the gyro.
 *
 * @unit deg/s
 * @min 0.0
 * @max 1800.0
 * @decimal 1
 * @increment 5
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_PITCHRATE_MAX, 220.0f);

/**
 * Max yaw rate
 *
 * @unit deg/s
 * @min 0.0
 * @max 1800.0
 * @decimal 1
 * @increment 5
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_YAWRATE_MAX, 200.0f);

/**
 * Threshold for Rattitude mode
 *
 * Manual input needed in order to override attitude control rate setpoints
 * and instead pass manual stick inputs as rate setpoints
 *
 * @min 0.0
 * @max 1.0
 * @decimal 2
 * @increment 0.01
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(MC_RATT_TH, 0.8f);

/**
 * Manual tilt input filter time constant
 * Setting this parameter to 0 disables the filter
 *
 * @unit s
 * @min 0.0
 * @max 2.0
 * @decimal 2
 * @group Multicopter Position Control
 */
PARAM_DEFINE_FLOAT(MC_MAN_TILT_TAU, 0.0f);

/**
 * Maximum direct-force (horizontal) scaled thrust for omnidirectional vehicles
 *
 * Specifies the maximum horizontal thrust compared to the maximum possible
 * thrust generated by the vehicle for an omnidirectional multirotor. The
 * value of this parameter does not affect the behavior if the attitude mode
 * is not set to one of omni-directional modes (if OMNI_ATT_MODE is 0).
 *
 * @min 0
 * @max 1
 * @decimal 2
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(OMNI_DFC_MAX_THR, 0.15f);

/**
 * Omni-directional attitude setpoint mode
 *
 * Specifies the type of attitude setpoint sent to the attitude controller.
 * The parameter can be set to a normal attitude setpoint, where the tilt
 * of the vehicle (roll and pitch) are calculated from the desired thrust
 * vector. This should be the behavior for the non-omnidirectional vehicles,
 * such as quadrotors and other multirotors with coplanar rotors.
 * The "constant zero tilt" mode enforces zero roll and pitch and can only be
 * used for omnidirectional vehicles. The min-tilt mode enforces zero tilt
 * up to a maximum set acceleration (thrust) and tilts the vehicle as small
 * as possible if the thrust vector is larger than the maximum. The "constant
 * tilt" and "constant roll/pitch" modes enforce a given tilt or roll/pitch
 * for the vehicle. The estimation modes estimate the optimal tilt or roll/pitch
 * to counteract with the external force (e.g., wind).
 *
 * @min 0
 * @max 6
 * @value 0 tilted attitude
 * @value 1 min-tilt attitude
 * @value 2 constant zero tilt
 * @value 3 constant tilt
 * @value 4 constant roll/pitch
 * @value 5 estimate tilt
 * @value 6 estimate roll/pitch
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_INT32(OMNI_ATT_MODE, 0);

/**
 * Omni-directional attitude setpoint tilt angle
 *
 * Specifies the tilt angle in degrees for the constant-tilt attitude
 * setpoint generation mode (OMNI_ATT_MODE=3).
 *
 * @min 0
 * @max 90
 * @decimal 2
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(OMNI_ATT_TLT_ANG, 15.0f);

/**
 * Omni-directional attitude setpoint tilt direction angle
 *
 * Specifies the direction of the tilt in degrees for the constant-tilt
 * attitude setpoint generation mode (OMNI_ATT_MODE=3). The direction is
 * measured from North.
 *
 * @min -360
 * @max 360
 * @decimal 2
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(OMNI_ATT_TLT_DIR, 0.0f);

/**
 * Omni-directional attitude setpoint roll angle
 *
 * Specifies the roll angle in degrees for the constant-roll/pitch attitude
 * setpoint generation mode (OMNI_ATT_MODE=4).
 *
 * @min -90
 * @max 90
 * @decimal 2
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(OMNI_ATT_ROLL, 0.0f);

/**
 * Omni-directional attitude setpoint pitch angle
 *
 * Specifies the pitch angle in degrees for the constant-roll/pitch attitude
 * setpoint generation mode (OMNI_ATT_MODE=4).
 *
 * @min -90
 * @max 90
 * @decimal 2
 * @group Multicopter Attitude Control
 */
PARAM_DEFINE_FLOAT(OMNI_ATT_PITCH, 0.0f);
