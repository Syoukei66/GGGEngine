#include "RenderCommand.h"
#include "CommandBuffer.h"

RenderCommand::RenderCommand(CommandBuffer* buffer)
  : buffer_(buffer)
{
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::Release()
{
  this->buffer_->Remove(this);
  delete this;
}


