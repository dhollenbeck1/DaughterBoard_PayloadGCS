#pragma once
// MESSAGE PYRANOMETER PACKING

#define MAVLINK_MSG_ID_PYRANOMETER 153

MAVPACKED(
typedef struct __mavlink_pyranometer_t {
 uint32_t solarIrradiance; /*< The solar iradiance measured by the Pyranometer (in W.m-2).*/
 uint8_t status; /*< Status of the Pyranometer. 0 indicates on and 0xFF indicates off.*/
}) mavlink_pyranometer_t;

#define MAVLINK_MSG_ID_PYRANOMETER_LEN 5
#define MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN 5
#define MAVLINK_MSG_ID_153_LEN 5
#define MAVLINK_MSG_ID_153_MIN_LEN 5

#define MAVLINK_MSG_ID_PYRANOMETER_CRC 246
#define MAVLINK_MSG_ID_153_CRC 246



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PYRANOMETER { \
    153, \
    "PYRANOMETER", \
    2, \
    {  { "solarIrradiance", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_pyranometer_t, solarIrradiance) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_pyranometer_t, status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PYRANOMETER { \
    "PYRANOMETER", \
    2, \
    {  { "solarIrradiance", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_pyranometer_t, solarIrradiance) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_pyranometer_t, status) }, \
         } \
}
#endif

/**
 * @brief Pack a pyranometer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param solarIrradiance The solar iradiance measured by the Pyranometer (in W.m-2).
 * @param status Status of the Pyranometer. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pyranometer_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t solarIrradiance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PYRANOMETER_LEN];
    _mav_put_uint32_t(buf, 0, solarIrradiance);
    _mav_put_uint8_t(buf, 4, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PYRANOMETER_LEN);
#else
    mavlink_pyranometer_t packet;
    packet.solarIrradiance = solarIrradiance;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PYRANOMETER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PYRANOMETER;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
}

/**
 * @brief Pack a pyranometer message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param solarIrradiance The solar iradiance measured by the Pyranometer (in W.m-2).
 * @param status Status of the Pyranometer. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pyranometer_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t solarIrradiance,uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PYRANOMETER_LEN];
    _mav_put_uint32_t(buf, 0, solarIrradiance);
    _mav_put_uint8_t(buf, 4, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PYRANOMETER_LEN);
#else
    mavlink_pyranometer_t packet;
    packet.solarIrradiance = solarIrradiance;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PYRANOMETER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PYRANOMETER;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
}

/**
 * @brief Encode a pyranometer struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pyranometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pyranometer_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pyranometer_t* pyranometer)
{
    return mavlink_msg_pyranometer_pack(system_id, component_id, msg, pyranometer->solarIrradiance, pyranometer->status);
}

/**
 * @brief Encode a pyranometer struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pyranometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pyranometer_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pyranometer_t* pyranometer)
{
    return mavlink_msg_pyranometer_pack_chan(system_id, component_id, chan, msg, pyranometer->solarIrradiance, pyranometer->status);
}

/**
 * @brief Send a pyranometer message
 * @param chan MAVLink channel to send the message
 *
 * @param solarIrradiance The solar iradiance measured by the Pyranometer (in W.m-2).
 * @param status Status of the Pyranometer. 0 indicates on and 0xFF indicates off.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pyranometer_send(mavlink_channel_t chan, uint32_t solarIrradiance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PYRANOMETER_LEN];
    _mav_put_uint32_t(buf, 0, solarIrradiance);
    _mav_put_uint8_t(buf, 4, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PYRANOMETER, buf, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
#else
    mavlink_pyranometer_t packet;
    packet.solarIrradiance = solarIrradiance;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PYRANOMETER, (const char *)&packet, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
#endif
}

/**
 * @brief Send a pyranometer message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pyranometer_send_struct(mavlink_channel_t chan, const mavlink_pyranometer_t* pyranometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pyranometer_send(chan, pyranometer->solarIrradiance, pyranometer->status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PYRANOMETER, (const char *)pyranometer, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
#endif
}

#if MAVLINK_MSG_ID_PYRANOMETER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pyranometer_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t solarIrradiance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, solarIrradiance);
    _mav_put_uint8_t(buf, 4, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PYRANOMETER, buf, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
#else
    mavlink_pyranometer_t *packet = (mavlink_pyranometer_t *)msgbuf;
    packet->solarIrradiance = solarIrradiance;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PYRANOMETER, (const char *)packet, MAVLINK_MSG_ID_PYRANOMETER_MIN_LEN, MAVLINK_MSG_ID_PYRANOMETER_LEN, MAVLINK_MSG_ID_PYRANOMETER_CRC);
#endif
}
#endif

#endif

// MESSAGE PYRANOMETER UNPACKING


/**
 * @brief Get field solarIrradiance from pyranometer message
 *
 * @return The solar iradiance measured by the Pyranometer (in W.m-2).
 */
static inline uint32_t mavlink_msg_pyranometer_get_solarIrradiance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field status from pyranometer message
 *
 * @return Status of the Pyranometer. 0 indicates on and 0xFF indicates off.
 */
static inline uint8_t mavlink_msg_pyranometer_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a pyranometer message into a struct
 *
 * @param msg The message to decode
 * @param pyranometer C-struct to decode the message contents into
 */
static inline void mavlink_msg_pyranometer_decode(const mavlink_message_t* msg, mavlink_pyranometer_t* pyranometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pyranometer->solarIrradiance = mavlink_msg_pyranometer_get_solarIrradiance(msg);
    pyranometer->status = mavlink_msg_pyranometer_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PYRANOMETER_LEN? msg->len : MAVLINK_MSG_ID_PYRANOMETER_LEN;
        memset(pyranometer, 0, MAVLINK_MSG_ID_PYRANOMETER_LEN);
    memcpy(pyranometer, _MAV_PAYLOAD(msg), len);
#endif
}
