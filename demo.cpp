#include <cstdio>

#include "exif.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: demo <JPEG file>\n");
    return -1;
  }

  // Read the JPEG file into a buffer
  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    printf("Can't open file.\n");
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  unsigned long fsize = ftell(fp);
  rewind(fp);
  unsigned char *buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, fp) != fsize) {
    printf("Can't read file.\n");
    fclose(fp);
    delete[] buf;
    return -2;
  }
  fclose(fp);

  // Parse EXIF
  easyexif::EXIFInfo result;
  easyexif::ParseError code = result.parseFrom(buf, fsize);
  delete[] buf;
  if (code != easyexif::ParseError::None) {
    printf("Error parsing EXIF: code %d\n", static_cast<int>(code));
    return -3;
  }

  // Dump EXIF information
  if (result.isValid(result.Make)) {
    printf("Camera make          : %s\n", result.Make.c_str());
  }

  if (result.isValid(result.Model)) {
    printf("Camera model         : %s\n", result.Model.c_str());
  }

  if (result.isValid(result.Software)) {
    printf("Software             : %s\n", result.Software.c_str());
  }

  if (result.isValid(result.BitsPerSample)) {
    printf("Bits per sample      : %d\n", result.BitsPerSample);
  }

  if (result.isValid(result.XResolution)) {
    printf("XResolution          : %.1f\n", result.XResolution);
  }

  if (result.isValid(result.YResolution)) {
    printf("YResolution          : %.1f\n", result.YResolution);
  }

  if (result.isValid(result.ResolutionUnit)) {
    printf("ResolutionUnit       : %u\n", result.ResolutionUnit);
  }

  if (result.isValid(result.ColorSpace)) {
    printf("Color space          : %u\n", result.ColorSpace);
  }

  if (result.isValid(result.WhiteBalance)) {
    printf("White balance        : %u\n", result.WhiteBalance);
  }

  if (result.isValid(result.ImageWidth)) {
    printf("Image width          : %u\n", result.ImageWidth);
  }

  if (result.isValid(result.ImageHeight)) {
    printf("Image height         : %u\n", result.ImageHeight);
  }

  if (result.isValid(result.ImageDescription)) {
    printf("Image description    : %s\n", result.ImageDescription.c_str());
  }

  if (result.isValid(result.Orientation)) {
    printf("Image orientation    : %d\n", result.Orientation);
  }

  if (result.isValid(result.Copyright)) {
    printf("Image copyright      : %s\n", result.Copyright.c_str());
  }

  if (result.isValid(result.DateTime)) {
    printf("Image date/time      : %s\n", result.DateTime.c_str());
  }

  if (result.isValid(result.DateTimeOriginal)) {
    printf("Original date/time   : %s\n", result.DateTimeOriginal.c_str());
  }

  if (result.isValid(result.DateTimeDigitized)) {
    printf("Digitize date/time   : %s\n", result.DateTimeDigitized.c_str());
  }

  if (result.isValid(result.SubSecTimeOriginal)) {
    printf("Subsecond time       : %s\n", result.SubSecTimeOriginal.c_str());
  }

  if (result.isValid(result.ExposureTime)) {
    printf("Exposure time        : 1/%u s\n",
           static_cast<unsigned int>(1.0 / result.ExposureTime));
  }

  if (result.isValid(result.FNumber)) {
    printf("F-stop               : f/%.1f\n", result.FNumber);
  }

  if (result.isValid(result.ExposureProgram)) {
    printf("Exposure program     : %d\n", result.ExposureProgram);
  }

  if (result.isValid(result.ExposureMode)) {
    printf("Exposure mode        : %d\n", result.ExposureMode);
  }

  if (result.isValid(result.ISOSpeedRatings)) {
    printf("ISO speed            : %d\n", result.ISOSpeedRatings);
  }

  if (result.isValid(result.SubjectDistance)) {
    printf("Subject distance     : %f m\n", result.SubjectDistance);
  }

  if (result.isValid(result.ExposureBiasValue)) {
    printf("Exposure bias        : %f EV\n", result.ExposureBiasValue);
  }

  if (result.isValid(result.Flash)) {
    printf("Flash used?          : %d\n", result.Flash);
  }

  if (result.isValid(result.FlashReturnedLight)) {
    printf("Flash returned light : %d\n", result.FlashReturnedLight);
  }

  if (result.isValid(result.FlashMode)) {
    printf("Flash mode           : %d\n", result.FlashMode);
  }

  if (result.isValid(result.MeteringMode)) {
    printf("Metering mode        : %d\n", result.MeteringMode);
  }

  if (result.isValid(result.FocalLength)) {
    printf("Lens focal length    : %f mm\n", result.FocalLength);
  }

  if (result.isValid(result.FocalLengthIn35mm)) {
    printf("35mm focal length    : %u mm\n", result.FocalLengthIn35mm);
  }

  if (result.isValid(result.GeoLocation.Latitude)) {
    printf("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)\n",
           result.GeoLocation.Latitude,
           result.GeoLocation.LatComponents.degrees,
           result.GeoLocation.LatComponents.minutes,
           result.GeoLocation.LatComponents.seconds,
           result.GeoLocation.LatComponents.direction);
  }

  if (result.isValid(result.GeoLocation.Longitude)) {
    printf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)\n",
           result.GeoLocation.Longitude,
           result.GeoLocation.LonComponents.degrees,
           result.GeoLocation.LonComponents.minutes,
           result.GeoLocation.LonComponents.seconds,
           result.GeoLocation.LonComponents.direction);
  }

  if (result.isValid(result.GeoLocation.Altitude)) {
    printf("GPS Altitude         : %f m\n", result.GeoLocation.Altitude);
  }

  if (result.isValid(result.GeoLocation.DOP)) {
    printf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
  }

  if (result.isValid(result.LensInfo.FocalLengthMin)) {
    printf("Lens min focal length: %f mm\n", result.LensInfo.FocalLengthMin);
  }

  if (result.isValid(result.LensInfo.FocalLengthMax)) {
    printf("Lens max focal length: %f mm\n", result.LensInfo.FocalLengthMax);
  }

  if (result.isValid(result.LensInfo.FStopMin)) {
    printf("Lens f-stop min      : f/%.1f\n", result.LensInfo.FStopMin);
  }

  if (result.isValid(result.LensInfo.FStopMax)) {
    printf("Lens f-stop max      : f/%.1f\n", result.LensInfo.FStopMax);
  }

  if (result.isValid(result.LensInfo.Make)) {
    printf("Lens make            : %s\n", result.LensInfo.Make.c_str());
  }

  if (result.isValid(result.LensInfo.Model)) {
    printf("Lens model           : %s\n", result.LensInfo.Model.c_str());
  }

  if (result.isValid(result.LensInfo.FocalPlaneXResolution)) {
    printf("Focal plane XRes     : %f\n",
           result.LensInfo.FocalPlaneXResolution);
  }

  if (result.isValid(result.LensInfo.FocalPlaneYResolution)) {
    printf("Focal plane YRes     : %f\n",
           result.LensInfo.FocalPlaneYResolution);
  }

  return 0;
}
