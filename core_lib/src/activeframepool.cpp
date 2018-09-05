/*

Pencil - Traditional Animation Software
Copyright (C) 2005-2007 Patrick Corrieri & Pascal Naidon
Copyright (C) 2012-2018 Matthew Chiawen Chang

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/

#include "activeframepool.h"
#include "keyframe.h"
#include <QDebug>


ActiveFramePool::ActiveFramePool(int maxSize)
{
    Q_ASSERT(maxSize > 10);
    mMaxSize = maxSize;

    mBackgroundWorker = std::move(std::thread([this]
    {
        while(true)
        {
            std::unique_lock<std::mutex> lock(mMutex);
        }
    }));
}

ActiveFramePool::~ActiveFramePool()
{

}

void ActiveFramePool::put(KeyFrame* key)
{
    if (key == nullptr)
        return;

    Q_ASSERT(key->pos() > 0);

    std::lock_guard<std::mutex> lock(mMutex);

    key->loadFile();

    auto it = mCacheFramesMap.find(key);
    mCacheFramesList.push_front(key);
    if (it != mCacheFramesMap.end())
    {
        mCacheFramesList.erase(it->second);
    }
    mCacheFramesMap[key] = mCacheFramesList.begin();
    key->addEventListener(this);
    key->loadFile();

    if (mCacheFramesMap.size() > mMaxSize)
    {
        list_iterator_t last = mCacheFramesList.end();
        last--;
        
        KeyFrame* lastKeyFrame = *last;
        unloadFrame(lastKeyFrame);

        mCacheFramesMap.erase(lastKeyFrame);
        mCacheFramesList.pop_back();

        lastKeyFrame->removeEventListner(this);
    }
}

size_t ActiveFramePool::size() const
{
    return mCacheFramesMap.size();
}

void ActiveFramePool::clear()
{
    std::lock_guard<std::mutex> lock(mMutex);

    for (KeyFrame* key : mCacheFramesList)
    {
        key->removeEventListner(this);
    }
    mCacheFramesList.clear();
    mCacheFramesMap.clear();
}

bool ActiveFramePool::isFrameInPool(KeyFrame* key)
{
    auto it = mCacheFramesMap.find(key);
    return (it != mCacheFramesMap.end());
}

void ActiveFramePool::onKeyFrameDestroy(KeyFrame* key)
{
    std::lock_guard<std::mutex> lock(mMutex);

    auto it = mCacheFramesMap.find(key);
    if (it != mCacheFramesMap.end())
    {
        mCacheFramesList.erase(it->second);
        mCacheFramesMap.erase(it);
    }
}

void ActiveFramePool::unloadFrame(KeyFrame* key)
{
    //qDebug() << "Unload frame:" << key->pos();
    key->unloadFile();
}
