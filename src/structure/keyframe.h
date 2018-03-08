#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QString>

class Keyframe
{
public:
    Keyframe()
    {
    }

    Keyframe(const Keyframe &frame);

public:
    // keep public for now
    int position;
    int originalPosition;
    QString filename;
    bool modified;
};

#endif // KEYFRAME_H
