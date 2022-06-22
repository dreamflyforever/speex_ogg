LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := speex
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.././ogg/include ../speex/include
LOCAL_SRC_FILES:= ../interface.c ../ogg/src/framing.c ../ogg/src/bitwise.c ../speex/libspeex/fftwrap.c ../speex/libspeex/exc_8_128_table.c ../speex/libspeex/resample.c ../speex/libspeex/speex.c ../speex/libspeex/modes_wb.c ../speex/libspeex/exc_20_32_table.c ../speex/libspeex/exc_5_64_table.c ../speex/libspeex/speex_header.c ../speex/libspeex/lpc.c ../speex/libspeex/vq.c ../speex/libspeex/jitter.c ../speex/libspeex/gain_table_lbr.c ../speex/libspeex/lsp.c ../speex/libspeex/vbr.c ../speex/libspeex/cb_search.c ../speex/libspeex/preprocess.c ../speex/libspeex/filters.c ../speex/libspeex/exc_10_32_table.c ../speex/libspeex/gain_table.c ../speex/libspeex/window.c ../speex/libspeex/scal.c ../speex/libspeex/hexc_table.c ../speex/libspeex/modes.c ../speex/libspeex/sb_celp.c ../speex/libspeex/lsp_tables_nb.c ../speex/libspeex/exc_10_16_table.c ../speex/libspeex/high_lsp_tables.c ../speex/libspeex/stereo.c ../speex/libspeex/kiss_fft.c ../speex/libspeex/quant_lsp.c ../speex/libspeex/nb_celp.c ../speex/libspeex/exc_5_256_table.c ../speex/libspeex/filterbank.c ../speex/libspeex/buffer.c ../speex/libspeex/kiss_fftr.c ../speex/libspeex/hexc_10_32_table.c ../speex/libspeex/speex_callbacks.c ../speex/libspeex/ltp.c ../speex/libspeex/smallft.c ../speex/libspeex/mdf.c ../speex/libspeex/bits.c ../speex/src/wave_out.c ../speex/src/getopt.c ../speex/src/getopt1.c ../speex/src/array.c ../speex/src/skeleton.c ../speex/src/wav_io.c
include $(BUILD_SHARED_LIBRARY)
