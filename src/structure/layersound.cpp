/*

Pencil - Traditional Animation Software
Copyright (C) 2005-2007 Patrick Corrieri & Pascal Naidon

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation;

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/
#include <QDebug>
#include "layersound.h"
#include "object.h"

LayerSound::LayerSound(Object* object) : LayerImage(object)
{
    type = Layer::SOUND;
    name = QString("Sound Layer");
}

LayerSound::~LayerSound()
{
}


void LayerSound::paintImages(QPainter& painter, TimeLineCells* cells, int x, int y, int width, int height, bool selected, int frameSize)
{
    Q_UNUSED(cells);
    Q_UNUSED(width);
    Q_UNUSED(selected);
}

bool LayerSound::addImageAtFrame(int frameNumber)
{
    int index = getIndexAtFrame(frameNumber);
    if (index == -1)
    {
        soundFilepath.append("");
        framesPosition.append(frameNumber);
        framesOriginalPosition.append(frameNumber);
        framesSelected.append(false);
        framesFilename.append("");
        framesModified.append(false);
        soundSize.append(0);
        bubbleSort();
        return true;
    }
    else
    {
        return false;
    }
}

void LayerSound::removeImageAtFrame(int frameNumber)
{
    int index = getIndexAtFrame(frameNumber);
    if (index != -1  && framesPosition.size() != 0)
    {
        soundFilepath.removeAt(index);
        framesPosition.removeAt(index);
        framesOriginalPosition.removeAt(index);
        framesSelected.removeAt(index);
        framesFilename.removeAt(index);
        framesModified.removeAt(index);
        soundSize.removeAt(index);
        bubbleSort();
    }
}

void LayerSound::loadSoundAtFrame(QString filePathString, int frameNumber)
{
//	if (getIndexAtFrame(frameNumber) == -1) addImageAtFrame(frameNumber);
    int index = getIndexAtFrame(frameNumber);
    if (index == -1)
        addImageAtFrame(frameNumber);
    index = getIndexAtFrame(frameNumber);

    QFileInfo fi(filePathString);
    if (fi.exists())
    {
    }
}

void LayerSound::swap(int i, int j)
{
    LayerImage::swap(i, j);
}


bool LayerSound::saveImage(int index, QString path, int layerNumber)
{
    Q_UNUSED(layerNumber);
    QFile originalFile( soundFilepath.at(index) );
    originalFile.copy( path + "/" + framesFilename.at(index) );
    framesModified[index] = false;

    return true;
}


void LayerSound::playSound(int frame,int fps)
{
}



void LayerSound::stopSound()
{
}


QDomElement LayerSound::createDomElement(QDomDocument& doc)
{
    QDomElement layerTag = doc.createElement("layer");
    layerTag.setAttribute("id",id);
    layerTag.setAttribute("name", name);
    layerTag.setAttribute("visibility", visible);
    layerTag.setAttribute("type", type);
    for(int index=0; index < framesPosition.size() ; index++)
    {
        QDomElement soundTag = doc.createElement("sound");
        soundTag.setAttribute("position", framesPosition.at(index));
        soundTag.setAttribute("src", framesFilename.at(index));
        layerTag.appendChild(soundTag);
    }
    return layerTag;
}

void LayerSound::loadDomElement(QDomElement element, QString filePath)
{
    if (!element.attribute("id").isNull()) id = element.attribute("id").toInt();
    name = element.attribute("name");
    visible = (element.attribute("visibility") == "1");
    type = element.attribute("type").toInt();

    QDomNode soundTag = element.firstChild();
    while (!soundTag.isNull())
    {
        QDomElement soundElement = soundTag.toElement();
        if (!soundElement.isNull())
        {
            if (soundElement.tagName() == "sound")
            {
                QString path = filePath + ".data/" + soundElement.attribute("src"); // the file is supposed to be in the data directory
                QFileInfo fi(path);
                if (!fi.exists()) path = soundElement.attribute("src");
                int position = soundElement.attribute("position").toInt();
                loadSoundAtFrame( path, position );
            }
        }
        soundTag = soundTag.nextSibling();
    }
}

void LayerSound::addTimelineKey(qint64 newTotalTime)
{
}
