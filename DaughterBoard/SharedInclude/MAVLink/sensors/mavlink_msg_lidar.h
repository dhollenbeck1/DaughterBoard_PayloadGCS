#pragma once
// MESSAGE LIDAR PACKING

#define MAVLINK_MSG_ID_LIDAR 152

MAVPACKED(
typedef struct __mavlink_lidar_t {
 uint16_t distance; /*< The distance measured by the Lidar (in cm).*/
 uint8_t status; /*< Status of the Lidar. 0 indicates on and 0xFF indicates off.*/
}) mavlink_lidar_t;

#define MAVLINK_MSG_ID_LIDAR_LEN 3
#define MAVLINK_MSG_ID_LIDAR_MIN_LEN 3
#define MAVLINK_MSG_ID_152_LEN 3
#define MAVLINK_MSG_ID_152_MIN_LEN 3

#define MAVLINK_MSG_ID_LIDAR_CRC 86
#define MAVLINK_MSG_ID_152_CRC 86



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LIDAR { \
    152, \
    "LIDAR", \
    2, \
    {  { "distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_lidar_t, distance) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_lidar_t, status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LIDAR { \
    "LIDAR", \
    2, \
    {  { "distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_lidar_t, distance) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_lidar_t, status) }, \
         } \
}
#endif

/**
 * @brief Pack a lidar message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param distance The distance measured by the Lidar (in cm).
 * @param status Status of the Lidar. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t distance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_LEN];
    _mav_put_uint16_t(buf, 0, distance);
    _mav_put_uint8_t(buf, 2, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_LEN);
#else
    mavlink_lidar_t packet;
    packet.distance = distance;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
}

/**
 * @brief Pack a lidar message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param distance The distance measured by the Lidar (in cm).
 * @param status Status of the Lidar. 0 indicates on and 0xFF indicates off.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t distance,uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_LEN];
    _mav_put_uint16_t(buf, 0, distance);
    _mav_put_uint8_t(buf, 2, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_LEN);
#else
    mavlink_lidar_t packet;
    packet.distance = distance;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
}

/**
 * @brief Encode a lidar struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lidar C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lidar_t* lidar)
{
    return mavlink_msg_lidar_pack(system_id, component_id, msg, lidar->distance, lidar->status);
}

/**
 * @brief Encode a lidar struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lidar C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lidar_t* lidar)
{
    return mavlink_msg_lidar_pack_chan(system_id, component_id, chan, msg, lidar->distance, lidar->status);
}

/**
 * @brief Send a lidar message
 * @param chan MAVLink channel to send the message
 *
 * @param distance The distance measured by the Lidar (in cm).
 * @param status Status of the Lidar. 0 indicates on and 0xFF indicates off.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lidar_send(mavlink_channel_t chan, uint16_t distance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_LEN];
    _mav_put_uint16_t(buf, 0, distance);
    _mav_put_uint8_t(buf, 2, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR, buf, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
#else
    mavlink_lidar_t packet;
    packet.distance = distance;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR, (const char *)&packet, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
#endif
}

/**
 * @brief Send a lidar message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_lidar_send_struct(mavlink_channel_t chan, const mavlink_lidar_t* lidar)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lidar_send(chan, lidar->distance, lidar->status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR, (const char *)lidar, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
#endif
}

#if MAVLINK_MSG_ID_LIDAR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lidar_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t distance, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, distance);
    _mav_put_uint8_t(buf, 2, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR, buf, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
#else
    mavlink_lidar_t *packet = (mavlink_lidar_t *)msgbuf;
    packet->distance = distance;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR, (const char *)packet, MAVLINK_MSG_ID_LIDAR_MIN_LEN, MAVLINK_MSG_ID_LIDAR_LEN, MAVLINK_MSG_ID_LIDAR_CRC);
#endif
}
#endif

#endif

// MESSAGE LIDAR UNPACKING


/**
 * @brief Get field distance from lidar message
 *
 * @return The distance measured by the Lidar (in cm).
 */
static inline uint16_t mavlink_msg_lidar_get_distance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field status from lidar message
 *
 * @return Status of the Lidar. 0 indicates on and 0xFF indicates off.
 */
static inline uint8_t mavlink_msg_lidar_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a lidar message into a struct
 *
 * @param msg The message to decode
 * @param lidar C-struct to decode the message contents into
 */
static inline void mavlink_msg_lidar_decode(const mavlink_message_t* msg, mavlink_lidar_t* lidar)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    lidar->distance = mavlink_msg_lidar_get_distance(msg);
    lidar->status = mavlink_msg_lidar_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LIDAR_LEN? msg->len : MAVLINK_MSG_ID_LIDAR_LEN;
        memset(lidar, 0, MAVLINK_MSG_ID_LIDAR_LEN);
    memcpy(lidar, _MAV_PAYLOAD(msg), len);
#endif
}
