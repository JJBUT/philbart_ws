// Generated by gencpp from file piksi_rtk_msgs/MeasurementState_V2_4_1.msg
// DO NOT EDIT!


#ifndef PIKSI_RTK_MSGS_MESSAGE_MEASUREMENTSTATE_V2_4_1_H
#define PIKSI_RTK_MSGS_MESSAGE_MEASUREMENTSTATE_V2_4_1_H


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
struct MeasurementState_V2_4_1_
{
  typedef MeasurementState_V2_4_1_<ContainerAllocator> Type;

  MeasurementState_V2_4_1_()
    : header()
    , sat()
    , code()
    , cn0()  {
    }
  MeasurementState_V2_4_1_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , sat(_alloc)
    , code(_alloc)
    , cn0(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _sat_type;
  _sat_type sat;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _code_type;
  _code_type code;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _cn0_type;
  _cn0_type cn0;



  enum {
    CODE_GPS_L1CA = 0u,
    CODE_GPS_L2CM = 1u,
    CODE_SBAS_L1CA = 2u,
    CODE_GLO_L1CA = 3u,
    CODE_GLO_L2CA = 4u,
    CODE_GPS_L1P = 5u,
    CODE_GPS_L2P = 6u,
    CODE_BDS2_B1 = 12u,
    CODE_BDS2_B2 = 13u,
    CODE_GAL_E1B = 14u,
    CODE_GAL_E7I = 20u,
  };


  typedef boost::shared_ptr< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> const> ConstPtr;

}; // struct MeasurementState_V2_4_1_

typedef ::piksi_rtk_msgs::MeasurementState_V2_4_1_<std::allocator<void> > MeasurementState_V2_4_1;

typedef boost::shared_ptr< ::piksi_rtk_msgs::MeasurementState_V2_4_1 > MeasurementState_V2_4_1Ptr;
typedef boost::shared_ptr< ::piksi_rtk_msgs::MeasurementState_V2_4_1 const> MeasurementState_V2_4_1ConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9b1254e4ea2ffaa4f03a8b48413ec9fd";
  }

  static const char* value(const ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9b1254e4ea2ffaa4ULL;
  static const uint64_t static_value2 = 0xf03a8b48413ec9fdULL;
};

template<class ContainerAllocator>
struct DataType< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
{
  static const char* value()
  {
    return "piksi_rtk_msgs/MeasurementState_V2_4_1";
  }

  static const char* value(const ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# The tracking message returns a variable-length array of tracking channel states. It reports status and\n\
# carrier-to-noise density measurements for all tracked satellites.\n\
\n\
# Message definition based on libsbp v2.4.1\n\
\n\
Header header\n\
\n\
uint8[] sat     # Constellation-specific satellite identifier.\n\
uint8[] code    # Signal constellation, band and code.\n\
uint8[] cn0     # Carrier-to-Noise density. Zero implies invalid cn0 [dB Hz / 4].\n\
\n\
\n\
uint8 CODE_GPS_L1CA     = 0\n\
uint8 CODE_GPS_L2CM     = 1\n\
uint8 CODE_SBAS_L1CA    = 2\n\
uint8 CODE_GLO_L1CA     = 3\n\
uint8 CODE_GLO_L2CA     = 4\n\
uint8 CODE_GPS_L1P      = 5\n\
uint8 CODE_GPS_L2P      = 6\n\
uint8 CODE_BDS2_B1      = 12\n\
uint8 CODE_BDS2_B2      = 13\n\
uint8 CODE_GAL_E1B      = 14\n\
uint8 CODE_GAL_E7I      = 20\n\
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

  static const char* value(const ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.sat);
      stream.next(m.code);
      stream.next(m.cn0);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MeasurementState_V2_4_1_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::piksi_rtk_msgs::MeasurementState_V2_4_1_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "sat[]" << std::endl;
    for (size_t i = 0; i < v.sat.size(); ++i)
    {
      s << indent << "  sat[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.sat[i]);
    }
    s << indent << "code[]" << std::endl;
    for (size_t i = 0; i < v.code.size(); ++i)
    {
      s << indent << "  code[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.code[i]);
    }
    s << indent << "cn0[]" << std::endl;
    for (size_t i = 0; i < v.cn0.size(); ++i)
    {
      s << indent << "  cn0[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.cn0[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // PIKSI_RTK_MSGS_MESSAGE_MEASUREMENTSTATE_V2_4_1_H
