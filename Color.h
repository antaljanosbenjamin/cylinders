//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_COLOR_H
#define CYLINDERS_COLOR_H

struct Color {
    float r, g, b;

    Color() {
        r = g = b = 0;
    }

    Color( float r0, float g0, float b0 ) {
        r = r0;
        g = g0;
        b = b0;
    }

    Color operator*( float a ) {
        return Color( r * a, g * a, b * a );
    }

    Color operator*( const Color &c ) {
        return Color( r * c.r, g * c.g, b * c.b );
    }

    Color operator/( float a ) {
        return Color( r / a, g / a, b / a );
    }

    Color operator/( const Color &c ) {
        return Color( r / c.r, g / c.g, b / c.b );
    }

    Color operator+( float a ) {
        return Color( r + a, g + a, b + a );
    }

    Color operator+( const Color &c ) {
        return Color( r + c.r, g + c.g, b + c.b );
    }

    Color operator-( float a ) {
        return Color( r - a, g - a, b - a );
    }

    Color operator-( const Color &c ) {
        return Color( r - c.r, g - c.g, b - c.b );
    }

    float getMaxIntensity() {
        if( r >= g ){
            if( r >= b )
                return r;
            else
                return b;
        }
        else{
            if( g >= b )
                return g;
            else
                return b;
        }
    }

    float getLuminance() {
        return 0.21f * r + 0.72f * g + 0.07f * b;
    }
};

#endif //CYLINDERS_COLOR_H
