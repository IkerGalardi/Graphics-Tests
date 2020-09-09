#include "framebuffer.h"

framebuffer_t create_framebuffer(framebuffer_settings_t settings) {
    framebuffer_t result;
    result.settings = settings;

    glCreateFramebuffers(1, &result.id);
    glBindFramebuffer(GL_FRAMEBUFFER, result.id);

    // Create the color texture and bind to the framebuffer
    glCreateTextures(GL_TEXTURE_2D, 1, &result.color_texture);
    glBindTexture(GL_TEXTURE_2D, result.color_texture);
    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 GL_RGBA8, 
                 settings.width, settings.height, 
                 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, 
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result.color_texture, 0);

    // Create the depth/stencil texture and bind to the framebuffer
    glCreateTextures(GL_TEXTURE_2D, 1, &result.depth_texture);
    glBindTexture(GL_TEXTURE_2D, result.depth_texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, settings.width, settings.height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, result.depth_texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        printf("Incomplete framebuffer with id: %i", result.id);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}