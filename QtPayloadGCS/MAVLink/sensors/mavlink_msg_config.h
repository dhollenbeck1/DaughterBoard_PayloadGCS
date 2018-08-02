#pragma once
// MESSAGE CONFIG PACKING

#define MAVLINK_MSG_ID_CONFIG 150

MAVPACKED(
typedef struct __mavlink_config_t {
 uint8_t windSensorStatus; /*< Tells whether the Wind Sensor is (1) or is not (0) used in the current configuration.*/
 uint8_t windSensorType; /*< The type of wind sensor used: 0 (FT205), 1 (FT742) or 2 (Trisonica).*/
 uint8_t windSensorComPortNum; /*< The serial port number for the wind sensor.*/
 uint8_t lidarStatus; /*< Tells whether the Lidar is (1) or is not (0) used in the current configuration.*/
 uint8_t pyranometerStatus; /*< Tells whether the Pyranometer is (1) or is not (0) used in the current configuration.*/
 uint8_t oplsStatus; /*< Tells whether the OPLS is (1) or is not (0) used in the current configuration.*/
 uint8_t oplsComPortNum; /*< The serial port number for the OPLS.*/
}) mavlink_config_t;

#define MAVLINK_MSG_ID_CONFIG_LEN 7
#define MAVLINK_MSG_ID_CONFIG_MIN_LEN 7
#define MAVLINK_MSG_ID_150_LEN 7
#define MAVLINK_MSG_ID_150_MIN_LEN 7

#define MAVLINK_MSG_ID_CONFIG_CRC 86
#define MAVLINK_MSG_ID_150_CRC 86



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CONFIG { \
    150, \
    "CONFIG", \
    7, \
    {  { "windSensorStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_config_t, windSensorStatus) }, \
         { "windSensorType", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_config_t, windSensorType) }, \
         { "windSensorComPortNum", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_config_t, windSensorComPortNum) }, \
         { "lidarStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_config_t, lidarStatus) }, \
         { "pyranometerStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_config_t, pyranometerStatus) }, \
         { "oplsStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_config_t, oplsStatus) }, \
         { "oplsComPortNum", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_config_t, oplsComPortNum) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CONFIG { \
    "CONFIG", \
    7, \
    {  { "windSensorStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_config_t, windSensorStatus) }, \
         { "windSensorType", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_config_t, windSensorType) }, \
         { "windSensorComPortNum", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_config_t, windSensorComPortNum) }, \
         { "lidarStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_config_t, lidarStatus) }, \
         { "pyranometerStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_config_t, pyranometerStatus) }, \
         { "oplsStatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_config_t, oplsStatus) }, \
         { "oplsComPortNum", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_config_t, oplsComPortNum) }, \
         } \
}
#endif

/**
 * @brief Pack a config message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param windSensorStatus Tells whether the Wind Sensor is (1) or is not (0) used in the current configuration.
 * @param windSensorType The type of wind sensor used: 0 (FT205), 1 (FT742) or 2 (Trisonica).
 * @param windSensorComPortNum The serial port number for the wind sensor.
 * @param lidarStatus Tells whether the Lidar is (1) or is not (0) used in the current configuration.
 * @param pyranometerStatus Tells whether the Pyranometer is (1) or is not (0) used in the current configuration.
 * @param oplsStatus Tells whether the OPLS is (1) or is not (0) used in the current configuration.
 * @param oplsComPortNum The serial port number for the OPLS.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_config_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t windSensorStatus, uint8_t windSensorType, uint8_t windSensorComPortNum, uint8_t lidarStatus, uint8_t pyranometerStatus, uint8_t oplsStatus, uint8_t oplsComPortNum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint8_t(buf, 0, windSensorStatus);
    _mav_put_uint8_t(buf, 1, windSensorType);
    _mav_put_uint8_t(buf, 2, windSensorComPortNum);
    _mav_put_uint8_t(buf, 3, lidarStatus);
    _mav_put_uint8_t(buf, 4, pyranometerStatus);
    _mav_put_uint8_t(buf, 5, oplsStatus);
    _mav_put_uint8_t(buf, 6, oplsComPortNum);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONFIG_LEN);
#else
    mavlink_config_t packet;
    packet.windSensorStatus = windSensorStatus;
    packet.windSensorType = windSensorType;
    packet.windSensorComPortNum = windSensorComPortNum;
    packet.lidarStatus = lidarStatus;
    packet.pyranometerStatus = pyranometerStatus;
    packet.oplsStatus = oplsStatus;
    packet.oplsComPortNum = oplsComPortNum;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONFIG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
}

/**
 * @brief Pack a config message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param windSensorStatus Tells whether the Wind Sensor is (1) or is not (0) used in the current configuration.
 * @param windSensorType The type of wind sensor used: 0 (FT205), 1 (FT742) or 2 (Trisonica).
 * @param windSensorComPortNum The serial port number for the wind sensor.
 * @param lidarStatus Tells whether the Lidar is (1) or is not (0) used in the current configuration.
 * @param pyranometerStatus Tells whether the Pyranometer is (1) or is not (0) used in the current configuration.
 * @param oplsStatus Tells whether the OPLS is (1) or is not (0) used in the current configuration.
 * @param oplsComPortNum The serial port number for the OPLS.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_config_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t windSensorStatus,uint8_t windSensorType,uint8_t windSensorComPortNum,uint8_t lidarStatus,uint8_t pyranometerStatus,uint8_t oplsStatus,uint8_t oplsComPortNum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint8_t(buf, 0, windSensorStatus);
    _mav_put_uint8_t(buf, 1, windSensorType);
    _mav_put_uint8_t(buf, 2, windSensorComPortNum);
    _mav_put_uint8_t(buf, 3, lidarStatus);
    _mav_put_uint8_t(buf, 4, pyranometerStatus);
    _mav_put_uint8_t(buf, 5, oplsStatus);
    _mav_put_uint8_t(buf, 6, oplsComPortNum);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONFIG_LEN);
#else
    mavlink_config_t packet;
    packet.windSensorStatus = windSensorStatus;
    packet.windSensorType = windSensorType;
    packet.windSensorComPortNum = windSensorComPortNum;
    packet.lidarStatus = lidarStatus;
    packet.pyranometerStatus = pyranometerStatus;
    packet.oplsStatus = oplsStatus;
    packet.oplsComPortNum = oplsComPortNum;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONFIG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
}

/**
 * @brief Encode a config struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_config_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_config_t* config)
{
    return mavlink_msg_config_pack(system_id, component_id, msg, config->windSensorStatus, config->windSensorType, config->windSensorComPortNum, config->lidarStatus, config->pyranometerStatus, config->oplsStatus, config->oplsComPortNum);
}

/**
 * @brief Encode a config struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_config_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_config_t* config)
{
    return mavlink_msg_config_pack_chan(system_id, component_id, chan, msg, config->windSensorStatus, config->windSensorType, config->windSensorComPortNum, config->lidarStatus, config->pyranometerStatus, config->oplsStatus, config->oplsComPortNum);
}

/**
 * @brief Send a config message
 * @param chan MAVLink channel to send the message
 *
 * @param windSensorStatus Tells whether the Wind Sensor is (1) or is not (0) used in the current configuration.
 * @param windSensorType The type of wind sensor used: 0 (FT205), 1 (FT742) or 2 (Trisonica).
 * @param windSensorComPortNum The serial port number for the wind sensor.
 * @param lidarStatus Tells whether the Lidar is (1) or is not (0) used in the current configuration.
 * @param pyranometerStatus Tells whether the Pyranometer is (1) or is not (0) used in the current configuration.
 * @param oplsStatus Tells whether the OPLS is (1) or is not (0) used in the current configuration.
 * @param oplsComPortNum The serial port number for the OPLS.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_config_send(mavlink_channel_t chan, uint8_t windSensorStatus, uint8_t windSensorType, uint8_t windSensorComPortNum, uint8_t lidarStatus, uint8_t pyranometerStatus, uint8_t oplsStatus, uint8_t oplsComPortNum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint8_t(buf, 0, windSensorStatus);
    _mav_put_uint8_t(buf, 1, windSensorType);
    _mav_put_uint8_t(buf, 2, windSensorComPortNum);
    _mav_put_uint8_t(buf, 3, lidarStatus);
    _mav_put_uint8_t(buf, 4, pyranometerStatus);
    _mav_put_uint8_t(buf, 5, oplsStatus);
    _mav_put_uint8_t(buf, 6, oplsComPortNum);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, buf, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#else
    mavlink_config_t packet;
    packet.windSensorStatus = windSensorStatus;
    packet.windSensorType = windSensorType;
    packet.windSensorComPortNum = windSensorComPortNum;
    packet.lidarStatus = lidarStatus;
    packet.pyranometerStatus = pyranometerStatus;
    packet.oplsStatus = oplsStatus;
    packet.oplsComPortNum = oplsComPortNum;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)&packet, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}

/**
 * @brief Send a config message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_config_send_struct(mavlink_channel_t chan, const mavlink_config_t* config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_config_send(chan, config->windSensorStatus, config->windSensorType, config->windSensorComPortNum, config->lidarStatus, config->pyranometerStatus, config->oplsStatus, config->oplsComPortNum);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)config, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}

#if MAVLINK_MSG_ID_CONFIG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_config_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t windSensorStatus, uint8_t windSensorType, uint8_t windSensorComPortNum, uint8_t lidarStatus, uint8_t pyranometerStatus, uint8_t oplsStatus, uint8_t oplsComPortNum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, windSensorStatus);
    _mav_put_uint8_t(buf, 1, windSensorType);
    _mav_put_uint8_t(buf, 2, windSensorComPortNum);
    _mav_put_uint8_t(buf, 3, lidarStatus);
    _mav_put_uint8_t(buf, 4, pyranometerStatus);
    _mav_put_uint8_t(buf, 5, oplsStatus);
    _mav_put_uint8_t(buf, 6, oplsComPortNum);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, buf, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#else
    mavlink_config_t *packet = (mavlink_config_t *)msgbuf;
    packet->windSensorStatus = windSensorStatus;
    packet->windSensorType = windSensorType;
    packet->windSensorComPortNum = windSensorComPortNum;
    packet->lidarStatus = lidarStatus;
    packet->pyranometerStatus = pyranometerStatus;
    packet->oplsStatus = oplsStatus;
    packet->oplsComPortNum = oplsComPortNum;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)packet, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}
#endif

#endif

// MESSAGE CONFIG UNPACKING


/**
 * @brief Get field windSensorStatus from config message
 *
 * @return Tells whether the Wind Sensor is (1) or is not (0) used in the current configuration.
 */
static inline uint8_t mavlink_msg_config_get_windSensorStatus(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field windSensorType from config message
 *
 * @return The type of wind sensor used: 0 (FT205), 1 (FT742) or 2 (Trisonica).
 */
static inline uint8_t mavlink_msg_config_get_windSensorType(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field windSensorComPortNum from config message
 *
 * @return The serial port number for the wind sensor.
 */
static inline uint8_t mavlink_msg_config_get_windSensorComPortNum(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field lidarStatus from config message
 *
 * @return Tells whether the Lidar is (1) or is not (0) used in the current configuration.
 */
static inline uint8_t mavlink_msg_config_get_lidarStatus(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field pyranometerStatus from config message
 *
 * @return Tells whether the Pyranometer is (1) or is not (0) used in the current configuration.
 */
static inline uint8_t mavlink_msg_config_get_pyranometerStatus(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field oplsStatus from config message
 *
 * @return Tells whether the OPLS is (1) or is not (0) used in the current configuration.
 */
static inline uint8_t mavlink_msg_config_get_oplsStatus(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field oplsComPortNum from config message
 *
 * @return The serial port number for the OPLS.
 */
static inline uint8_t mavlink_msg_config_get_oplsComPortNum(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Decode a config message into a struct
 *
 * @param msg The message to decode
 * @param config C-struct to decode the message contents into
 */
static inline void mavlink_msg_config_decode(const mavlink_message_t* msg, mavlink_config_t* config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    config->windSensorStatus = mavlink_msg_config_get_windSensorStatus(msg);
    config->windSensorType = mavlink_msg_config_get_windSensorType(msg);
    config->windSensorComPortNum = mavlink_msg_config_get_windSensorComPortNum(msg);
    config->lidarStatus = mavlink_msg_config_get_lidarStatus(msg);
    config->pyranometerStatus = mavlink_msg_config_get_pyranometerStatus(msg);
    config->oplsStatus = mavlink_msg_config_get_oplsStatus(msg);
    config->oplsComPortNum = mavlink_msg_config_get_oplsComPortNum(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CONFIG_LEN? msg->len : MAVLINK_MSG_ID_CONFIG_LEN;
        memset(config, 0, MAVLINK_MSG_ID_CONFIG_LEN);
    memcpy(config, _MAV_PAYLOAD(msg), len);
#endif
}
