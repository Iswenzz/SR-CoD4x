#include "Speex.hpp"

namespace SR
{
	void Speex::Initialize()
	{
		bool perceptualEnhancement = false;

		speex_bits_init(&Bits);

		Decoder = speex_decoder_init(&speex_nb_mode);
		speex_decoder_ctl(Decoder, SPEEX_SET_ENH, &perceptualEnhancement);

		Encoder = speex_encoder_init(&speex_nb_mode);
	}

	void Speex::Shutdown()
	{
		speex_bits_destroy(&Bits);
		if (Decoder)
			speex_decoder_destroy(Decoder);
		if (Encoder)
			speex_encoder_destroy(Encoder);
	}

	std::vector<short> Speex::Decode(VoicePacket_t *packet)
	{
		std::vector<short> decodedData;
		decodedData.resize(SPEEX_FRAME_SIZE);
		int packetDataSize = packet->dataSize;

		speex_bits_read_from(&Bits, packet->data, packetDataSize);
		speex_decode_int(Decoder, &Bits, decodedData.data());
		int decodedDataSize = SPEEX_CHANNELS * SPEEX_FRAME_SIZE * sizeof(short);

		return decodedData;
	}

	VoicePacket_t Speex::Encode(std::vector<short> &packet)
	{
		VoicePacket_t encodedData;
		int packetDataSize = packet.size();

		speex_bits_reset(&Bits);
		speex_encode_int(Encoder, packet.data(), &Bits);
		encodedData.dataSize = speex_bits_write(&Bits, encodedData.data, packetDataSize);

		return encodedData;
	}
}
