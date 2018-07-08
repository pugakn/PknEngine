#include "pkn_utils.h"
#include <fstream>
namespace pugaknSDK {
  byte* Utils::CreateBitmapFileHeader(Int32 _w, Int32 _h) {
    Int32 fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + BPP*_w*_h;
    static unsigned char fileHeader[FILE_HEADER_SIZE];

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
  }

 byte* Utils::CreateBitmapInfoHeader(Int32 _w, Int32 _h) {
    static unsigned char infoHeader[INFO_HEADER_SIZE];

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(_w);
    infoHeader[5] = (unsigned char)(_w >> 8);
    infoHeader[6] = (unsigned char)(_w >> 16);
    infoHeader[7] = (unsigned char)(_w >> 24);
    infoHeader[8] = (unsigned char)(_h);
    infoHeader[9] = (unsigned char)(_h >> 8);
    infoHeader[10] = (unsigned char)(_h >> 16);
    infoHeader[11] = (unsigned char)(_h >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BPP * 8);

    return infoHeader;
  }
  void Utils::GenerateBitmapImage(byte *buffer, Int32 _w, Int32 _h, std::string _path) {

    byte* fileHeader = CreateBitmapFileHeader(_w, _h);
    byte* infoHeader = CreateBitmapInfoHeader(_w, _h);
    byte padding[3] = { 0, 0, 0 };
    int paddingSize = (4 - (_w*BPP) % 4) % 4;

    std::ofstream bmpFile(_path, std::ios::binary);

    bmpFile.write((char*)fileHeader, FILE_HEADER_SIZE);
    bmpFile.write((char*)infoHeader, INFO_HEADER_SIZE);

    for (size_t i = 0; i<_h; i++) {
      bmpFile.write((char*)buffer + (i*_w*BPP), _w * BPP);
      bmpFile.write((char*)padding, paddingSize);
    }

    bmpFile.close();
  }
}