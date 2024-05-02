//
// Created by ivan on 2024/5/3.
//

#include "StbImage.hpp"
#include <stb_image.h>

namespace lgl {

StbImage::StbImage(const std::string &path, bool bFlip) {
    stbi_set_flip_vertically_on_load(bFlip);
    m_image_ = stbi_load(path.c_str(), &m_width_, &m_height_, &m_channel_, 0);
}

const unsigned char *StbImage::operator()() const {
    return image();
}

void StbImage::release() {
    if (m_image_) {
        stbi_image_free(m_image_);
        m_image_ = nullptr;
        m_width_ = m_height_ = m_channel_ = -1;
    }
}

StbImage::~StbImage() {
    release();
}

}
