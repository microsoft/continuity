#import "UIColor+String.h"

BOOL hexDecodeDigit(const char digit, uint8_t* value)
{
    if (digit >= '0' && digit <= '9')
    {
        *value = digit - '0';
        return YES;
    }
    else if (digit >= 'a' && digit <= 'f')
    {
        *value = digit - 'a' + 10;
        return YES;
    }
    else if (digit >= 'A' && digit <= 'F')
    {
        *value = digit - 'A' + 10;
        return YES;
    }

    return NO;
}

BOOL hexDecodeByte(const char digitHigh, const char digitLow, uint8_t* value)
{
    uint8_t valueHigh, valueLow;
    if (hexDecodeDigit(digitHigh, &valueHigh) &&
        hexDecodeDigit(digitLow, &valueLow))
    {
        *value = (valueHigh << 4) | valueLow;
        return YES;
    }

    return NO;
}

struct RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

BOOL parseRGBShort(const char *color, struct RGB *value)
{
    struct RGB shortValue;
    if (hexDecodeDigit(color[0], &shortValue.red) &&
        hexDecodeDigit(color[1], &shortValue.green) &&
        hexDecodeDigit(color[2], &shortValue.blue))
    {
        value->red = (shortValue.red << 4) | shortValue.red;
        value->green = (shortValue.green << 4) | shortValue.green;
        value->blue = (shortValue.blue << 4) | shortValue.blue;
        return YES;
    }

    return NO;
}

BOOL parseRGB(const char *color, struct RGB *value)
{
    if (hexDecodeByte(color[0], color[1], &value->red) &&
        hexDecodeByte(color[2], color[3], &value->green) &&
        hexDecodeByte(color[4], color[5], &value->blue))
    {
        return YES;
    }

    return NO;
}

BOOL parseHashColor(NSString *colorString, struct RGB *value)
{
    if (!colorString || colorString.length < 1)
        return NO;

    const char *colorStringUTF8 = [colorString UTF8String];

    if (colorStringUTF8[0] != '#')
        return NO;

    if (colorString.length == 4)
        return parseRGBShort(colorStringUTF8 + 1, value);
    else if (colorString.length == 7)
        return parseRGB(colorStringUTF8 + 1, value);

    return NO;
}


@implementation UIColor (String)

+ (UIColor *)colorFromString:(NSString*)colorString
{
    struct RGB value;
    if (parseHashColor(colorString, &value))
    {
        CGFloat r = (CGFloat)value.red / 255;
        CGFloat g = (CGFloat)value.green / 255;
        CGFloat b = (CGFloat)value.blue / 255;

        return [UIColor colorWithRed:r green:g blue:b alpha:1];
    }

    return nil;
}

@end
