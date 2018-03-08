#include "keyframe.h"

Keyframe::Keyframe(const Keyframe &frame)
{
    position = frame.position;
    originalPosition = frame.originalPosition;
    filename = frame.filename;
    modified = frame.modified;
}
