// Generated by gencpp from file piksi_rtk_msgs/VelEcef.msg
// DO NOT EDIT!


#ifndef PIKSI_RTK_MSGS_MESSAGE_VELECEF_H
#define PIKSI_RTK_MSGS_MESSAGE_VELECEF_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace piksi_rtk_msgs
{
template <class ContainerAllocator>
struct VelEcef_
{
  typedef VelEcef_<ContainerAllocator> Type;

  VelEcef_()
    : header()
    , tow(0)
    , x(0)
    , y(0)
    , z(0)
    , accuracy(0)
    , n_sats(0)
    , flags(0)  {
    }
  VelEcef_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , tow(0)
    , x(0)
    , y(0)
    , z(0)
    , accuracy(0)
    , n_sats(0)
    , flags(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint32_t _tow_type;
  _tow_type tow;

   typedef int32_t _x_type;
  _x_type x;

   typedef int32_t _y_type;
  _y_type y;

   typedef int32_t _z_type;
  _z_type z;

   typedef uint16_t _accuracy_type;
  _accuracy_type accuracy;

   typedef uint8_t _n_sats_type;
  _n_sats_type n_sats;

   typedef uint8_t _flags_type;
  _flags_type flags;





  typedef boost::shared_ptr< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> const> ConstPtr;

}; // struct VelEcef_

typedef ::piksi_rtk_msgs::VelEcef_<std::allocator<void> > VelEcef;

typedef boost::shared_ptr< ::piksi_rtk_msgs::VelEcef > VelEcefPtr;
typedef boost::shared_ptr< ::piksi_rtk_msgs::VelEcef const> VelEcefConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace piksi_rtk_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'piksi_rtk_msgs': ['/home/jacksubuntu/philbart_ws/src/ethz_piksi_ros/piksi_rtk_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b632ba03d94241cc519a3a3e4885b973";
  }

  static const char* value(const ::piksi_rtk_msgs::VelEcef_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb632ba03d94241ccULL;
  static const uint64_t static_value2 = 0x519a3a3e4885b973ULL;
};

template<class ContainerAllocator>
struct DataType< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
{
  static const char* value()
  {
    return "piksi_rtk_msgs/VelEcef";
  }

  static const char* value(const ::piksi_rtk_msgs::VelEcef_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This message reports the velocity in Earth Centered Earth Fixed (ECEF) coordinates. The full GPS time\n\
# is given by the preceding MSG GPS TIME with the matching time-of-week (tow).\n\
\n\
Header header\n\
\n\
uint32 tow      # GPS Time of Week.\n\
int32 x         # Velocity ECEF X coordinate [mm/s].\n\
int32 y         # Velocity ECEF Y coordinate [mm/s].\n\
int32 z         # Velocity ECEF Z coordinate [mm/s].\n\
uint16 accuracy # Velocity accuracy estimate (not implemented). Defaults to 0.\n\
uint8 n_sats    # Number of satellites used in solution.\n\
uint8 flags     # Status flags (reserved), see MSG_VEL_ECEF message description in SBP documentation.\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::piksi_rtk_msgs::VelEcef_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.tow);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
      stream.next(m.accuracy);
      stream.next(m.n_sats);
      stream.next(m.flags);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VelEcef_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::piksi_rtk_msgs::VelEcef_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::piksi_rtk_msgs::VelEcef_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "tow: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.tow);
    s << indent << "x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<int32_t>::stream(s, indent + "  ", v.z);
    s << indent << "accuracy: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.accuracy);
    s << indent << "n_sats: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.n_sats);
    s << indent << "flags: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.flags);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PIKSI_RTK_MSGS_MESSAGE_VELECEF_H
