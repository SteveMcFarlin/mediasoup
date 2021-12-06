#define MS_CLASS "RTC::Codecs::AV1"
// #define MS_LOG_DEV_LEVEL 3

#include "RTC/Codecs/AV1.hpp"
#include "Logger.hpp"

namespace RTC
{
	namespace Codecs
	{
		/* Class methods. */

		AV1::PayloadDescriptor* AV1::Parse(
		  const uint8_t* data,
		  size_t len,
		  RTC::RtpPacket::FrameMarking* /*frameMarking*/,
		  uint8_t /*frameMarkingLen*/)
		{
			MS_TRACE();

			return nullptr;
		}

		void AV1::ProcessRtpPacket(RTC::RtpPacket* packet)
		{
			MS_TRACE();
			MS_DUMP("AV1 Process packet\n");
		}

		/* Instance methods. */

		void AV1::PayloadDescriptor::Dump() const
		{
			MS_TRACE();
			/*
			MS_DUMP("<PayloadDescriptor>");
			MS_DUMP(
			  "  i:%" PRIu8 "|p:%" PRIu8 "|l:%" PRIu8 "|f:%" PRIu8 "|b:%" PRIu8 "|e:%" PRIu8 "|v:%" PRIu8,
			  this->i,
			  this->p,
			  this->l,
			  this->f,
			  this->b,
			  this->e,
			  this->v);
			MS_DUMP("  pictureId            : %" PRIu16, this->pictureId);
			MS_DUMP("  slIndex              : %" PRIu8, this->slIndex);
			MS_DUMP("  tlIndex              : %" PRIu8, this->tlIndex);
			MS_DUMP("  tl0PictureIndex      : %" PRIu8, this->tl0PictureIndex);
			MS_DUMP("  interLayerDependency : %" PRIu8, this->interLayerDependency);
			MS_DUMP("  switchingUpPoint     : %" PRIu8, this->switchingUpPoint);
			MS_DUMP("  isKeyFrame           : %s", this->isKeyFrame ? "true" : "false");
			MS_DUMP("  hasPictureId         : %s", this->hasPictureId ? "true" : "false");
			MS_DUMP("  hasOneBytePictureId  : %s", this->hasOneBytePictureId ? "true" : "false");
			MS_DUMP("  hasTwoBytesPictureId : %s", this->hasTwoBytesPictureId ? "true" : "false");
			MS_DUMP("  hasTl0PictureIndex   : %s", this->hasTl0PictureIndex ? "true" : "false");
			MS_DUMP("  hasSlIndex           : %s", this->hasSlIndex ? "true" : "false");
			MS_DUMP("  hasTlIndex           : %s", this->hasTlIndex ? "true" : "false");
			MS_DUMP("</PayloadDescriptor>");
			 */
		}

		AV1::PayloadDescriptorHandler::PayloadDescriptorHandler(AV1::PayloadDescriptor* payloadDescriptor)
		{
			MS_TRACE();

			this->payloadDescriptor.reset(payloadDescriptor);
		}

		bool AV1::PayloadDescriptorHandler::Process(
		  RTC::Codecs::EncodingContext* encodingContext, uint8_t* /*data*/, bool& marker)
		{
			MS_TRACE();

			auto* context = static_cast<RTC::Codecs::AV1::EncodingContext*>(encodingContext);

			return false;
		}

		void AV1::PayloadDescriptorHandler::Restore(uint8_t* /*data*/)
		{
			MS_TRACE();
		}
	} // namespace Codecs
} // namespace RTC
