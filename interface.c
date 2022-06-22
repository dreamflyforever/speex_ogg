#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <speex/speex.h>

static void *st = 0;
static SpeexBits bits;
static int speex_headersz = 2;

static int _write_header(uint8_t *frame, int pdu_len, int headersz)
{
	switch (headersz) {
	case 1:
		*frame = pdu_len;
		break;

	case 2:
		*(frame + 0) = pdu_len & 0xff;
		*(frame + 1) = (pdu_len >> 8) & 0xff;
		break;

	case 4:
		*(frame + 0) = pdu_len & 0xff;
		*(frame + 1) = (pdu_len >> 8) & 0xff;
		*(frame + 2) = (pdu_len >> 16) & 0xff;
		*(frame + 3) = (pdu_len >> 24) & 0xff;
		break;
	}

	return 0;
}

int speex_init()
{
	int mode;
	uint32_t samplespersec = 16000;
	if (samplespersec > 12500) mode = SPEEX_MODEID_WB;
	else mode = SPEEX_MODEID_NB;

	st = speex_encoder_init(speex_lib_get_mode(mode));
	

	
	spx_int32_t tmp;

	tmp = 1;
	speex_encoder_ctl(st, SPEEX_SET_COMPLEXITY, &tmp);
	speex_encoder_ctl(st, SPEEX_SET_DTX, &tmp);
	speex_encoder_ctl(st, SPEEX_SET_VBR, &tmp);

	tmp = 8;
	speex_encoder_ctl(st, SPEEX_SET_QUALITY, &tmp);
	tmp = samplespersec;
	speex_encoder_ctl(st, SPEEX_SET_SAMPLING_RATE, &tmp);

	/* Speex encoding initializations */
	speex_bits_init(&bits);
	return 0;
}

int pcm2speex(spx_int16_t *pcm_frame, char *spx_frame)
{
	speex_bits_reset(&bits);
	speex_encode_int(st, pcm_frame, &bits);
	int length = speex_bits_write(&bits,
			&spx_frame[speex_headersz],
			128 - speex_headersz);
	_write_header(spx_frame, length, speex_headersz);
	return length;
}

int speex_deinit()
{
	speex_encoder_destroy(st);
	speex_bits_destroy(&bits);
}

spx_int16_t pcm_frame[320];
uint8_t spx_frame[128];
int main(int argc, char** argv)
{
	int in_fd, out_fd;
	int frame_size = 640;
	in_fd = open(argv[1], O_RDONLY, 0);
	if (in_fd < 0) {
		printf("open wav failed!\n");
		return -1;
	}

	if (argc == 3)
		out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		out_fd = open("dummy.spx", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd < 0) {
		printf("open speex file failed!\n");
		close(in_fd);
		return -1;
	}

	speex_init();

	while (1) {
		int length = read(in_fd, pcm_frame, frame_size);
		if (length != frame_size) break;
		length = pcm2speex(pcm_frame, spx_frame);
		//printf("length: %d\n", length);
		write(out_fd, spx_frame, length + speex_headersz);
	}
	speex_deinit();
	close(in_fd);
	close(out_fd);
	return 0;
}
