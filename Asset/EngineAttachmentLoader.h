#pragma once

#include <spine/AtlasAttachmentLoader.h>

//TODO:�A�Z�b�g�Ǘ��̕ύX�ɍ��킹�Ă����C������
class EngineAttachmentLoader
{
public:
  EngineAttachmentLoader(spAtlas* atlas);

public:
  spAttachmentLoader super;
  spAtlasAttachmentLoader* atlas_attachment_loader_;
};

