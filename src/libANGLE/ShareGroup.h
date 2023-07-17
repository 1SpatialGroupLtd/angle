//
// Copyright 2023 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// ShareGroup.h: Defines the egl::ShareGroup class, representing the collection of contexts in a
// share group.

#ifndef LIBANGLE_SHAREGROUP_H_
#define LIBANGLE_SHAREGROUP_H_

#include <mutex>
#include <vector>

#include "libANGLE/Context.h"

namespace gl
{
class Context;
}  // namespace gl

namespace rx
{
class EGLImplFactory;
class ShareGroupImpl;
}  // namespace rx

namespace egl
{
using ContextMap = angle::HashMap<GLuint, gl::Context *>;

class ShareGroup final : angle::NonCopyable
{
  public:
    ShareGroup(rx::EGLImplFactory *factory);

    void addRef();

    void release(const egl::Display *display);

    rx::ShareGroupImpl *getImplementation() const { return mImplementation; }

    rx::UniqueSerial generateFramebufferSerial() { return mFramebufferSerialFactory.generate(); }

    angle::FrameCaptureShared *getFrameCaptureShared() { return mFrameCaptureShared.get(); }

    void finishAllContexts();

    const ContextMap &getContexts() const { return mContexts; }
    void addSharedContext(gl::Context *context);
    void removeSharedContext(gl::Context *context);

    size_t getShareGroupContextCount() const { return mContexts.size(); }

  protected:
    ~ShareGroup();

  private:
    size_t mRefCount;
    rx::ShareGroupImpl *mImplementation;
    rx::UniqueSerialFactory mFramebufferSerialFactory;

    // Note: we use a raw pointer here so we can exclude frame capture sources from the build.
    std::unique_ptr<angle::FrameCaptureShared> mFrameCaptureShared;

    // The list of contexts within the share group
    ContextMap mContexts;
};

}  // namespace egl

#endif  // LIBANGLE_SHAREGROUP_H_
