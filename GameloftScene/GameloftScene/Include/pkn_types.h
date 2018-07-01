#pragma once
#include <stdint.h>
namespace pugaknSDK {
  using  UInt8 = uint8_t;  //8-bit  unsigned.
  using  UInt16 = uint16_t; //16-bit unsigned.
  using  UInt32 = uint32_t; //32-bit unsigned.
  using  UInt64 = uint64_t; //64-bit unsigned.

  using Int8 = int8_t; //8-bit  signed.
  using Int16 = int16_t; //16-bit signed.
  using Int32 = int32_t; //32-bit signed.
  using Int64 = int64_t; //64-bit signed.

  using Float64 = double;
  using byte = unsigned char;

  using NullType = Int32;
  using SizeT = size_t;

  typedef void(*Callback)(void);
}