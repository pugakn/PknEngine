#pragma once
#include "pkn_prerequiites.h"
#include <string>
namespace pugaknSDK {
  struct Utils {
    static const int BPP = 3;
    static const int FILE_HEADER_SIZE = 14;
    static const int INFO_HEADER_SIZE = 40;

    static byte* CreateBitmapFileHeader(Int32 _w, Int32 _h);
    static byte* CreateBitmapInfoHeader(Int32 _w, Int32 _h);

    static void GenerateBitmapImage(byte *buffer, Int32 _w, Int32 _h, std::string _path);
  };
}