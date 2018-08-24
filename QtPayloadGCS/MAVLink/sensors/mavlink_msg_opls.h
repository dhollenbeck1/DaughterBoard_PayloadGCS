#pragma once
// MESSAGE OPLS PACKING

#define MAVLINK_MSG_ID_OPLS 154

MAVPACKED(
typedef struct __mavlink_opls_t {
 double time; /*< Time.*/
 double ch4; /*< CH4.*/
 double et; /*< Et.*/
 double h2o; /*< H20.*/
 double p; /*< Pressure.*/
 double t; /*< Temperature.*/
 double rf; /*< Range finder.*/
 double lon; /*< Longitude.*/
 double lat; /*< Latitude.*/
 double lsr; /*< Laser power.*/
 uint32_t sec; /*< Epoch number of seconds.*/
 uint32_t usec; /*< Number of microseconds. usec divided by 1e6 plus sec field provides current time with microseconds precision*/
}) mavlink_opls_t;

#define MAVLINK_MSG_ID_OPLS_LEN 88
#define MAVLINK_MSG_ID_OPLS_MIN_LEN 88
#define MAVLINK_MSG_ID_154_LEN 88
#define MAVLINK_MSG_ID_154_MIN_LEN 88

#define MAVLINK_MSG_ID_OPLS_CRC 181
#define MAVLINK_MSG_ID_154_CRC 181



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_OPLS { \
    154, \
    "OPLS", \
    12, \
    {  { "sec", NULL, MAVLINK_TYPE_UINT32_T, 0, 80, offsetof(mavlink_opls_t, sec) }, \
         { "usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 84, offsetof(mavlink_opls_t, usec) }, \
         { "time", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_opls_t, time) }, \
         { "ch4", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_opls_t, ch4) }, \
         { "et", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_opls_t, et) }, \
         { "h2o", NULL, MAVLINK_TYPE_DOUBLE, 0, 24, offsetof(mavlink_opls_t, h2o) }, \
         { "p", NULL, MAVLINK_TYPE_DOUBLE, 0, 32, offsetof(mavlink_opls_t, p) }, \
         { "t", NULL, MAVLINK_TYPE_DOUBLE, 0, 40, offsetof(mavlink_opls_t, t) }, \
         { "rf", NULL, MAVLINK_TYPE_DOUBLE, 0, 48, offsetof(mavlink_opls_t, rf) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 56, offsetof(mavlink_opls_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 64, offsetof(mavlink_opls_t, lat) }, \
         { "lsr", NULL, MAVLINK_TYPE_DOUBLE, 0, 72, offsetof(mavlink_opls_t, lsr) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_OPLS { \
    "OPLS", \
    12, \
    {  { "sec", NULL, MAVLINK_TYPE_UINT32_T, 0, 80, offsetof(mavlink_opls_t, sec) }, \
         { "usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 84, offsetof(mavlink_opls_t, usec) }, \
         { "time", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_opls_t, time) }, \
         { "ch4", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_opls_t, ch4) }, \
         { "et", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_opls_t, et) }, \
         { "h2o", NULL, MAVLINK_TYPE_DOUBLE, 0, 24, offsetof(mavlink_opls_t, h2o) }, \
         { "p", NULL, MAVLINK_TYPE_DOUBLE, 0, 32, offsetof(mavlink_opls_t, p) }, \
         { "t", NULL, MAVLINK_TYPE_DOUBLE, 0, 40, offsetof(mavlink_opls_t, t) }, \
         { "rf", NULL, MAVLINK_TYPE_DOUBLE, 0, 48, offsetof(mavlink_opls_t, rf) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 56, offsetof(mavlink_opls_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 64, offsetof(mavlink_opls_t, lat) }, \
         { "lsr", NULL, MAVLINK_TYPE_DOUBLE, 0, 72, offsetof(mavlink_opls_t, lsr) }, \
         } \
}
#endif

/**
 * @brief Pack a opls message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param sec Epoch number of seconds.
 * @param usec Number of microseconds. usec divided by 1e6 plus sec field provides current time with microseconds precision
 * @param time Time.
 * @param ch4 CH4.
 * @param et Et.
 * @param h2o H20.
 * @param p Pressure.
 * @param t Temperature.
 * @param rf Range finder.
 * @param lon Longitude.
 * @param lat Latitude.
 * @param lsr Laser power.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_opls_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t sec, uint32_t usec, double time, double ch4, double et, double h2o, double p, double t, double rf, double lon, double lat, double lsr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPLS_LEN];
    _mav_put_double(buf, 0, time);
    _mav_put_double(buf, 8, ch4);
    _mav_put_double(buf, 16, et);
    _mav_put_double(buf, 24, h2o);
    _mav_put_double(buf, 32, p);
    _mav_put_double(buf, 40, t);
    _mav_put_double(buf, 48, rf);
    _mav_put_double(buf, 56, lon);
    _mav_put_double(buf, 64, lat);
    _mav_put_double(buf, 72, lsr);
    _mav_put_uint32_t(buf, 80, sec);
    _mav_put_uint32_t(buf, 84, usec);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPLS_LEN);
#else
    mavlink_opls_t packet;
    packet.time = time;
    packet.ch4 = ch4;
    packet.et = et;
    packet.h2o = h2o;
    packet.p = p;
    packet.t = t;
    packet.rf = rf;
    packet.lon = lon;
    packet.lat = lat;
    packet.lsr = lsr;
    packet.sec = sec;
    packet.usec = usec;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPLS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPLS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
}

/**
 * @brief Pack a opls message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sec Epoch number of seconds.
 * @param usec Number of microseconds. usec divided by 1e6 plus sec field provides current time with microseconds precision
 * @param time Time.
 * @param ch4 CH4.
 * @param et Et.
 * @param h2o H20.
 * @param p Pressure.
 * @param t Temperature.
 * @param rf Range finder.
 * @param lon Longitude.
 * @param lat Latitude.
 * @param lsr Laser power.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_opls_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t sec,uint32_t usec,double time,double ch4,double et,double h2o,double p,double t,double rf,double lon,double lat,double lsr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPLS_LEN];
    _mav_put_double(buf, 0, time);
    _mav_put_double(buf, 8, ch4);
    _mav_put_double(buf, 16, et);
    _mav_put_double(buf, 24, h2o);
    _mav_put_double(buf, 32, p);
    _mav_put_double(buf, 40, t);
    _mav_put_double(buf, 48, rf);
    _mav_put_double(buf, 56, lon);
    _mav_put_double(buf, 64, lat);
    _mav_put_double(buf, 72, lsr);
    _mav_put_uint32_t(buf, 80, sec);
    _mav_put_uint32_t(buf, 84, usec);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPLS_LEN);
#else
    mavlink_opls_t packet;
    packet.time = time;
    packet.ch4 = ch4;
    packet.et = et;
    packet.h2o = h2o;
    packet.p = p;
    packet.t = t;
    packet.rf = rf;
    packet.lon = lon;
    packet.lat = lat;
    packet.lsr = lsr;
    packet.sec = sec;
    packet.usec = usec;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPLS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPLS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
}

/**
 * @brief Encode a opls struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param opls C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_opls_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_opls_t* opls)
{
    return mavlink_msg_opls_pack(system_id, component_id, msg, opls->sec, opls->usec, opls->time, opls->ch4, opls->et, opls->h2o, opls->p, opls->t, opls->rf, opls->lon, opls->lat, opls->lsr);
}

/**
 * @brief Encode a opls struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param opls C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_opls_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_opls_t* opls)
{
    return mavlink_msg_opls_pack_chan(system_id, component_id, chan, msg, opls->sec, opls->usec, opls->time, opls->ch4, opls->et, opls->h2o, opls->p, opls->t, opls->rf, opls->lon, opls->lat, opls->lsr);
}

/**
 * @brief Send a opls message
 * @param chan MAVLink channel to send the message
 *
 * @param sec Epoch number of seconds.
 * @param usec Number of microseconds. usec divided by 1e6 plus sec field provides current time with microseconds precision
 * @param time Time.
 * @param ch4 CH4.
 * @param et Et.
 * @param h2o H20.
 * @param p Pressure.
 * @param t Temperature.
 * @param rf Range finder.
 * @param lon Longitude.
 * @param lat Latitude.
 * @param lsr Laser power.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_opls_send(mavlink_channel_t chan, uint32_t sec, uint32_t usec, double time, double ch4, double et, double h2o, double p, double t, double rf, double lon, double lat, double lsr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPLS_LEN];
    _mav_put_double(buf, 0, time);
    _mav_put_double(buf, 8, ch4);
    _mav_put_double(buf, 16, et);
    _mav_put_double(buf, 24, h2o);
    _mav_put_double(buf, 32, p);
    _mav_put_double(buf, 40, t);
    _mav_put_double(buf, 48, rf);
    _mav_put_double(buf, 56, lon);
    _mav_put_double(buf, 64, lat);
    _mav_put_double(buf, 72, lsr);
    _mav_put_uint32_t(buf, 80, sec);
    _mav_put_uint32_t(buf, 84, usec);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPLS, buf, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
#else
    mavlink_opls_t packet;
    packet.time = time;
    packet.ch4 = ch4;
    packet.et = et;
    packet.h2o = h2o;
    packet.p = p;
    packet.t = t;
    packet.rf = rf;
    packet.lon = lon;
    packet.lat = lat;
    packet.lsr = lsr;
    packet.sec = sec;
    packet.usec = usec;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPLS, (const char *)&packet, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
#endif
}

/**
 * @brief Send a opls message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_opls_send_struct(mavlink_channel_t chan, const mavlink_opls_t* opls)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_opls_send(chan, opls->sec, opls->usec, opls->time, opls->ch4, opls->et, opls->h2o, opls->p, opls->t, opls->rf, opls->lon, opls->lat, opls->lsr);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPLS, (const char *)opls, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
#endif
}

#if MAVLINK_MSG_ID_OPLS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_opls_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t sec, uint32_t usec, double time, double ch4, double et, double h2o, double p, double t, double rf, double lon, double lat, double lsr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, time);
    _mav_put_double(buf, 8, ch4);
    _mav_put_double(buf, 16, et);
    _mav_put_double(buf, 24, h2o);
    _mav_put_double(buf, 32, p);
    _mav_put_double(buf, 40, t);
    _mav_put_double(buf, 48, rf);
    _mav_put_double(buf, 56, lon);
    _mav_put_double(buf, 64, lat);
    _mav_put_double(buf, 72, lsr);
    _mav_put_uint32_t(buf, 80, sec);
    _mav_put_uint32_t(buf, 84, usec);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPLS, buf, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
#else
    mavlink_opls_t *packet = (mavlink_opls_t *)msgbuf;
    packet->time = time;
    packet->ch4 = ch4;
    packet->et = et;
    packet->h2o = h2o;
    packet->p = p;
    packet->t = t;
    packet->rf = rf;
    packet->lon = lon;
    packet->lat = lat;
    packet->lsr = lsr;
    packet->sec = sec;
    packet->usec = usec;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPLS, (const char *)packet, MAVLINK_MSG_ID_OPLS_MIN_LEN, MAVLINK_MSG_ID_OPLS_LEN, MAVLINK_MSG_ID_OPLS_CRC);
#endif
}
#endif

#endif

// MESSAGE OPLS UNPACKING


/**
 * @brief Get field sec from opls message
 *
 * @return Epoch number of seconds.
 */
static inline uint32_t mavlink_msg_opls_get_sec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  80);
}

/**
 * @brief Get field usec from opls message
 *
 * @return Number of microseconds. usec divided by 1e6 plus sec field provides current time with microseconds precision
 */
static inline uint32_t mavlink_msg_opls_get_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  84);
}

/**
 * @brief Get field time from opls message
 *
 * @return Time.
 */
static inline double mavlink_msg_opls_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field ch4 from opls message
 *
 * @return CH4.
 */
static inline double mavlink_msg_opls_get_ch4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field et from opls message
 *
 * @return Et.
 */
static inline double mavlink_msg_opls_get_et(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  16);
}

/**
 * @brief Get field h2o from opls message
 *
 * @return H20.
 */
static inline double mavlink_msg_opls_get_h2o(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  24);
}

/**
 * @brief Get field p from opls message
 *
 * @return Pressure.
 */
static inline double mavlink_msg_opls_get_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  32);
}

/**
 * @brief Get field t from opls message
 *
 * @return Temperature.
 */
static inline double mavlink_msg_opls_get_t(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  40);
}

/**
 * @brief Get field rf from opls message
 *
 * @return Range finder.
 */
static inline double mavlink_msg_opls_get_rf(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  48);
}

/**
 * @brief Get field lon from opls message
 *
 * @return Longitude.
 */
static inline double mavlink_msg_opls_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  56);
}

/**
 * @brief Get field lat from opls message
 *
 * @return Latitude.
 */
static inline double mavlink_msg_opls_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  64);
}

/**
 * @brief Get field lsr from opls message
 *
 * @return Laser power.
 */
static inline double mavlink_msg_opls_get_lsr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  72);
}

/**
 * @brief Decode a opls message into a struct
 *
 * @param msg The message to decode
 * @param opls C-struct to decode the message contents into
 */
static inline void mavlink_msg_opls_decode(const mavlink_message_t* msg, mavlink_opls_t* opls)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    opls->time = mavlink_msg_opls_get_time(msg);
    opls->ch4 = mavlink_msg_opls_get_ch4(msg);
    opls->et = mavlink_msg_opls_get_et(msg);
    opls->h2o = mavlink_msg_opls_get_h2o(msg);
    opls->p = mavlink_msg_opls_get_p(msg);
    opls->t = mavlink_msg_opls_get_t(msg);
    opls->rf = mavlink_msg_opls_get_rf(msg);
    opls->lon = mavlink_msg_opls_get_lon(msg);
    opls->lat = mavlink_msg_opls_get_lat(msg);
    opls->lsr = mavlink_msg_opls_get_lsr(msg);
    opls->sec = mavlink_msg_opls_get_sec(msg);
    opls->usec = mavlink_msg_opls_get_usec(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_OPLS_LEN? msg->len : MAVLINK_MSG_ID_OPLS_LEN;
        memset(opls, 0, MAVLINK_MSG_ID_OPLS_LEN);
    memcpy(opls, _MAV_PAYLOAD(msg), len);
#endif
}
