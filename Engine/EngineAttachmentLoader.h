#pragma once

#include <spine/AtlasAttachmentLoader.h>

class EngineAttachmentLoader
{
public:
  EngineAttachmentLoader(spAtlas* atlas);

public:
  spAttachmentLoader super;
  spAtlasAttachmentLoader* atlas_attachment_loader_;
};

