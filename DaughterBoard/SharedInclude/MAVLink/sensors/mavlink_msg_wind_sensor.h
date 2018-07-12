#pragma once
// MESSAGE WIND_SENSOR PACKING

#define MAVLINK_MSG_ID_WIND_SENSOR 150

MAVPACKED(
typedef struct __mavlink_wind_sensor_t {
 float wind_speed; /*< The speed of the wind for the specified angle (in m/s).*/
 uint16_t angle; /*< The angle from the wind (in degrees).*/
 uint8_t status; /*< Status of the wind sensor. 0 indicates on and 0xFF indicates off.*/
}) mavlink_wind_sensor_t;

#define MAVLINK_MSG_ID_WIND_SENSOR_LEN 7
#define MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN 7
#define MAVLINK_MSG_ID_150_LEN 7
#define MAVLINK_MSG_ID_150_MIN_LEN 7

#define MAVLINK_MSG_ID_WIND_SENSOR_CRC 253
#define MAVLINK_MSG_ID_150_CRC 253



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WIND_SENSOR { \
    150, \
    "WIND_SENSOR", \
    3, \
    {  { "angle", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_wind_sensor_t, angle) }, \
         { "wind_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_wind_sensor_t, wind_speed) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_wind_sensor_t, status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WIND_SENSOR { \
    "WIND_SENSOR", \
    3, \
    {  { "angle", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_wind_sensor_t, angle) }, \
         { "wind_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_wind_sensor_t, wind_speed) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_wind_sensor_t, status) }, \
         } \
}
#endif

/**
 * @brief Pack a wind_sensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param angle The angle from the wind (in degrees).
 * @param wind_speed The speed of the wind for the specified angle (in m/s).
 * @param status Status of the wind sensor. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wind_sensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t angle, float wind_speed, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIND_SENSOR_LEN];
    _mav_put_float(buf, 0, wind_speed);
    _mav_put_uint16_t(buf, 4, angle);
    _mav_put_uint8_t(buf, 6, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIND_SENSOR_LEN);
#else
    mavlink_wind_sensor_t packet;
    packet.wind_speed = wind_speed;
    packet.angle = angle;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIND_SENSOR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIND_SENSOR;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
}

/**
 * @brief Pack a wind_sensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param angle The angle from the wind (in degrees).
 * @param wind_speed The speed of the wind for the specified angle (in m/s).
 * @param status Status of the wind sensor. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wind_sensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t angle,float wind_speed,uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIND_SENSOR_LEN];
    _mav_put_float(buf, 0, wind_speed);
    _mav_put_uint16_t(buf, 4, angle);
    _mav_put_uint8_t(buf, 6, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIND_SENSOR_LEN);
#else
    mavlink_wind_sensor_t packet;
    packet.wind_speed = wind_speed;
    packet.angle = angle;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIND_SENSOR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIND_SENSOR;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
}

/**
 * @brief Encode a wind_sensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param wind_sensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wind_sensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_wind_sensor_t* wind_sensor)
{
    return mavlink_msg_wind_sensor_pack(system_id, component_id, msg, wind_sensor->angle, wind_sensor->wind_speed, wind_sensor->status);
}

/**
 * @brief Encode a wind_sensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param wind_sensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wind_sensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_wind_sensor_t* wind_sensor)
{
    return mavlink_msg_wind_sensor_pack_chan(system_id, component_id, chan, msg, wind_sensor->angle, wind_sensor->wind_speed, wind_sensor->status);
}

/**
 * @brief Send a wind_sensor message
 * @param chan MAVLink channel to send the message
 *
 * @param angle The angle from the wind (in degrees).
 * @param wind_speed The speed of the wind for the specified angle (in m/s).
 * @param status Status of the wind sensor. 0 indicates on and 0xFF indicates off.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_wind_sensor_send(mavlink_channel_t chan, uint16_t angle, float wind_speed, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIND_SENSOR_LEN];
    _mav_put_float(buf, 0, wind_speed);
    _mav_put_uint16_t(buf, 4, angle);
    _mav_put_uint8_t(buf, 6, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND_SENSOR, buf, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
#else
    mavlink_wind_sensor_t packet;
    packet.wind_speed = wind_speed;
    packet.angle = angle;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND_SENSOR, (const char *)&packet, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
#endif
}

/**
 * @brief Send a wind_sensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_wind_sensor_send_struct(mavlink_channel_t chan, const mavlink_wind_sensor_t* wind_sensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_wind_sensor_send(chan, wind_sensor->angle, wind_sensor->wind_speed, wind_sensor->status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND_SENSOR, (const char *)wind_sensor, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
#endif
}

#if MAVLINK_MSG_ID_WIND_SENSOR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_wind_sensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t angle, float wind_speed, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, wind_speed);
    _mav_put_uint16_t(buf, 4, angle);
    _mav_put_uint8_t(buf, 6, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND_SENSOR, buf, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
#else
    mavlink_wind_sensor_t *packet = (mavlink_wind_sensor_t *)msgbuf;
    packet->wind_speed = wind_speed;
    packet->angle = angle;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND_SENSOR, (const char *)packet, MAVLINK_MSG_ID_WIND_SENSOR_MIN_LEN, MAVLINK_MSG_ID_WIND_SENSOR_LEN, MAVLINK_MSG_ID_WIND_SENSOR_CRC);
#endif
}
#endif

#endif

// MESSAGE WIND_SENSOR UNPACKING


/**
 * @brief Get field angle from wind_sensor message
 *
 * @return The angle from the wind (in degrees).
 */
static inline uint16_t mavlink_msg_wind_sensor_get_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field wind_speed from wind_sensor message
 *
 * @return The speed of the wind for the specified angle (in m/s).
 */
static inline float mavlink_msg_wind_sensor_get_wind_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field status from wind_sensor message
 *
 * @return Status of the wind sensor. 0 indicates on and 0xFF indicates off.
 */
static inline uint8_t mavlink_msg_wind_sensor_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Decode a wind_sensor message into a struct
 *
 * @param msg The message to decode
 * @param wind_sensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_wind_sensor_decode(const mavlink_message_t* msg, mavlink_wind_sensor_t* wind_sensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    wind_sensor->wind_speed = mavlink_msg_wind_sensor_get_wind_speed(msg);
    wind_sensor->angle = mavlink_msg_wind_sensor_get_angle(msg);
    wind_sensor->status = mavlink_msg_wind_sensor_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WIND_SENSOR_LEN? msg->len : MAVLINK_MSG_ID_WIND_SENSOR_LEN;
        memset(wind_sensor, 0, MAVLINK_MSG_ID_WIND_SENSOR_LEN);
    memcpy(wind_sensor, _MAV_PAYLOAD(msg), len);
#endif
}
