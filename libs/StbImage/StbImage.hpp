//
// Created by ivan on 2024/5/3.
//

#ifndef STBIMAGE_HPP
#define STBIMAGE_HPP

#include <string>

namespace lgl {

class StbImage {
public:
    StbImage() = default;
    StbImage(const StbImage&) = default;
    StbImage(StbImage&& rhs) {
        m_image_ = rhs.m_image_;
        rhs.m_image_ = nullptr;
        m_width_ = rhs.m_width_;
        m_height_ = rhs.m_height_;
        m_channel_ = rhs.m_channel_;
        rhs.m_width_ = rhs.m_height_ = rhs.m_channel_ = -1;
    }
    StbImage(const std::string& path, bool bFlip = false);

    int width() const { return m_width_; }
    int height() const { return m_height_; }
    int channel() const { return m_channel_; }
    const unsigned char* image() const { return m_image_; }
    const unsigned char* operator()() const { return image(); }
    operator const void*() const { return image(); }

    void release();
    ~StbImage();

private:
    unsigned char* m_image_ = nullptr;
    int m_width_ = -1;
    int m_height_ = -1;
    int m_channel_ = -1;
};

}

#endif //STBIMAGE_HPP
