#include <bits/stdc++.h>
#include <cstdint> // uchar
#include <cmath>
#include "../Pixel.h"

using namespace std;


// RGB to XYZ

void RGBtoXYZ(uint8_t R, uint8_t G, uint8_t B, double &X, double &Y, double &Z)
{
    // RGB Working Space: sRGB 
    // Reference White: D65
    double var_R = ( R / 255 );
    double var_G = ( G / 255 );
    double var_B = ( B / 255 );

    var_R = (var_R > 0.04045) ? pow((var_R + 0.055) / 1.055, 2.4) : var_R / 12.92;
    var_G = (var_G > 0.04045) ? pow((var_G + 0.055) / 1.055, 2.4) : var_G / 12.92;
    var_B = (var_B > 0.04045) ? pow((var_B + 0.055) / 1.055, 2.4) : var_B / 12.92;
    

    var_R = var_R * 100;
    var_G = var_G * 100;
    var_B = var_B * 100;

    X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
}



// XYZ to CIELab
void XYZtoCIELab(double X, double Y, double Z, double &L, double &a, double &b) {
  double ReferenceX = 95.047;
  double ReferenceY = 100.000;
  double ReferenceZ = 108.883;

  double var_X = X / ReferenceX;
  double var_Y = Y / ReferenceY;
  double var_Z = Z / ReferenceZ;

  var_X = (var_X > 0.008856) ? pow(var_X, 1.0/3.0) : (7.787 * var_X) + (16.0 / 116.0);
  var_Y = (var_Y > 0.008856) ? pow(var_Y, 1.0/3.0) : (7.787 * var_Y) + (16.0 / 116.0);
  var_Z = (var_Z > 0.008856) ? pow(var_Z, 1.0/3.0) : (7.787 * var_Z) + (16.0 / 116.0);

  L = (116.0 * var_Y) - 16.0;
  a = 500.0 * (var_X - var_Y);
  b = 200.0 * (var_Y - var_Z);
}

// CIELab to XYZ
void CIELabtoXYZ(double L, double a, double b, double &X, double &Y, double &Z) {
  double ReferenceX = 95.047;
  double ReferenceY = 100.000;
  double ReferenceZ = 108.883;

  double var_Y = (L + 16.0) / 116.0;
  double var_X = a / 500.0 + var_Y;
  double var_Z = var_Y - b / 200.0;

  var_X = (pow(var_X, 3.0) > 0.008856) ? pow(var_X, 3.0) : (var_X - 16.0 / 116.0) / 7.787;
  var_Y = (pow(var_Y, 3.0) > 0.008856) ? pow(var_Y, 3.0) : (var_Y - 16.0 / 116.0) / 7.787;
  var_Z = (pow(var_Z, 3.0) > 0.008856) ? pow(var_Z, 3.0) : (var_Z - 16.0 / 116.0) / 7.787;

  X = ReferenceX * var_X;
  Y = ReferenceY * var_Y;
  Z = ReferenceZ * var_Z;
}

// XYZ to RGB
void XYZtoRGB(double X, double Y, double Z, uint8_t &R, uint8_t &G, uint8_t &B)
{
    // RGB Working Space: sRGB 
    // Reference White: D65
    double var_X = X / 100;
    double var_Y = Y / 100;
    double var_Z = Z / 100;

    double var_R = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
    double var_G = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415;
    double var_B = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570;

    var_R = (var_R > 0.0031308) ? 1.055 * pow(var_R, 1.0 / 2.4) - 0.055 : 12.92 * var_R;
    var_G = (var_G > 0.0031308) ? 1.055 * pow(var_G, 1.0 / 2.4) - 0.055 : 12.92 * var_G;
    var_B = (var_B > 0.0031308) ? 1.055 * pow(var_B, 1.0 / 2.4) - 0.055 : 12.92 * var_B;

    R = (uint8_t)round(var_R * 255);
    G = (uint8_t)round(var_G * 255);
    B = (uint8_t)round(var_B * 255);
}

// RGB to CIELab
void RGBtoLab(double R, double G, double B, double &L, double &a, double &b)
{
    double X, Y, Z;
    RGBtoXYZ(R, G, B, X, Y, Z);
    XYZtoCIELab(X, Y, Z, L, a, b);
}

// CIELab to RGB
void LabtoRGB(double L, double a, double b, uint8_t &R, uint8_t &G, uint8_t &B)
{
    double X, Y, Z;
    CIELabtoXYZ(L, a, b, X, Y, Z);
    XYZtoRGB(X, Y, Z, R, G, B);
}

// Contrast
void contrast(vector< vector<Pixel> > *image, float amount) {
    int nrows = image->size();
    int ncols = image->at(0).size();
    double L, a, b;
    uint8_t R, G, B;
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {

            RGBtoLab(image->at(i).at(j).r, image->at(i).at(j).g, image->at(i).at(j).b, L, a, b);
            L = (L - 50) * amount + 50;
            LabtoRGB(L, a, b, R, G, B);

            image->at(i).at(j).r = R;
            image->at(i).at(j).g = G;
            image->at(i).at(j).b = B;
        }
    }
}