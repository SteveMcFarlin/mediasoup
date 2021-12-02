#ifndef MS_RTC_CODECS_AV1_HPP
#define MS_RTC_CODECS_AV1_HPP

#include "common.hpp"
#include "RTC/Codecs/PayloadDescriptorHandler.hpp"
#include "RTC/RtpPacket.hpp"
#include "RTC/SeqManager.hpp"

 // https://tools.ietf.org/html/draft-ietf-payload-vp9-06
 // AV1 format:
 //
 // RTP payload syntax:
 //     0 1 2 3 4 5 6 7
 //    +-+-+-+-+-+-+-+-+
 //    |Z|Y| W |N|-|-|-| (REQUIRED)
 //    +=+=+=+=+=+=+=+=+ (REPEATED W-1 times, or any times if W = 0)
 //    |1|             |
 //    +-+ OBU fragment|
 //    |1|             | (REQUIRED, leb128 encoded)
 //    +-+    size     |
 //    |0|             |
 //    +-+-+-+-+-+-+-+-+
 //    |  OBU fragment |
 //    |     ...       |
 //    +=+=+=+=+=+=+=+=+
 //    |     ...       |
 //    +=+=+=+=+=+=+=+=+ if W > 0, last fragment MUST NOT have size field
 //    |  OBU fragment |
 //    |     ...       |
 //    +=+=+=+=+=+=+=+=+
 //
 //
 // OBU syntax:
 //     0 1 2 3 4 5 6 7
 //    +-+-+-+-+-+-+-+-+
 //    |0| type  |X|S|-| (REQUIRED)
 //    +-+-+-+-+-+-+-+-+
 // X: | TID |SID|-|-|-| (OPTIONAL)
 //    +-+-+-+-+-+-+-+-+
 //    |1|             |
 //    +-+ OBU payload |
 // S: |1|             | (OPTIONAL, variable length leb128 encoded)
 //    +-+    size     |
 //    |0|             |
 //    +-+-+-+-+-+-+-+-+
 //    |  OBU payload  |
 //    |     ...       |

namespace RTC
{
	namespace Codecs
	{
		class AV1
		{
		public:
			struct PayloadDescriptor : public RTC::Codecs::PayloadDescriptor
			{
				/* Pure virtual methods inherited from RTC::Codecs::PayloadDescriptor. */
				~PayloadDescriptor() = default;

				void Dump() const override;
				
				uint8_t z : 1;
				uint8_t y : 1;
				uint8_t w : 2;
				uint8_t n : 1;
			};

		public:
			static AV1::PayloadDescriptor* Parse(
			  const uint8_t* data,
			  size_t len,
			  RTC::RtpPacket::FrameMarking* frameMarking = nullptr,
			  uint8_t frameMarkingLen                    = 0);
			static void ProcessRtpPacket(RTC::RtpPacket* packet);

		public:
			class EncodingContext : public RTC::Codecs::EncodingContext
			{
			public:
				explicit EncodingContext(RTC::Codecs::EncodingContext::Params& params)
				  : RTC::Codecs::EncodingContext(params)
				{
				}
				~EncodingContext() = default;

				/* Pure virtual methods inherited from RTC::Codecs::EncodingContext. */
			public:
				void SyncRequired() override
				{
					this->syncRequired = true;
				}

			public:
				RTC::SeqManager<uint16_t> pictureIdManager;
				bool syncRequired{ false };
			};

			class PayloadDescriptorHandler : public RTC::Codecs::PayloadDescriptorHandler
			{
			public:
				explicit PayloadDescriptorHandler(PayloadDescriptor* payloadDescriptor);
				~PayloadDescriptorHandler() = default;

			public:
				void Dump() const override
				{
					this->payloadDescriptor->Dump();
				}
				bool Process(RTC::Codecs::EncodingContext* encodingContext, uint8_t* data, bool& marker) override;
				void Restore(uint8_t* data) override;
				uint8_t GetSpatialLayer() const override
				{
					return 0u;
				}
				uint8_t GetTemporalLayer() const override
				{
					return 0u;
				}
				bool IsKeyFrame() const override
				{
					return false;
				}

			private:
				std::unique_ptr<PayloadDescriptor> payloadDescriptor;
			};
		};
	} // namespace Codecs
} // namespace RTC

#endif
