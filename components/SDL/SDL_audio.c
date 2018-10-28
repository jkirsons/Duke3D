#include "SDL_audio.h"

SDL_AudioSpec as;
unsigned char *sdl_buffer;
void *user_data;
bool paused = true;
bool locked = false;
xSemaphoreHandle xSemaphoreAudio = NULL;

void updateTask(void *arg)
{
  size_t bytesWritten;
  while(1)
  {
	  if(!paused && /*xSemaphoreAudio != NULL*/ !locked){
			// clear buffer
		  //xSemaphoreTake( xSemaphoreAudio, portMAX_DELAY );
		  memset(sdl_buffer, 0, SAMPLECOUNT*SAMPLESIZE);
		  (*as.callback)(NULL, sdl_buffer, SAMPLECOUNT*SAMPLESIZE );
		  i2s_write(I2S_NUM_0, sdl_buffer, SAMPLECOUNT*SAMPLESIZE, &bytesWritten, 5000 / portTICK_PERIOD_MS);
		  //xSemaphoreGive( xSemaphoreAudio );
		  //vTaskDelay( 1 );
	  } else
		  vTaskDelay( 5 );
  }
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
	static const i2s_config_t i2s_config = {
	.mode = I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN,
	.sample_rate = SAMPLERATE,
	.bits_per_sample = SAMPLESIZE*8, /* the DAC module will only take the 8bits from MSB */
	.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
	.communication_format = I2S_COMM_FORMAT_I2S_LSB,
	.intr_alloc_flags = 0, // default interrupt priority
	.dma_buf_count = 6,
	.dma_buf_len = 512,
	.use_apll = false
	};

	i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);   //install and start i2s driver
	i2s_pin_config_t pc =
	{
		.data_out_num = 25
	};
	i2s_set_pin(I2S_NUM_0, &pc); //for internal DAC, this will enable both of the internal channels
	i2s_set_clk(I2S_NUM_0, SAMPLERATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
	i2s_set_dac_mode(I2S_DAC_CHANNEL_RIGHT_EN);

	sdl_buffer = malloc(SAMPLECOUNT * SAMPLESIZE);

	memset(obtained, 0, sizeof(SDL_AudioSpec)); /* or SDL_zero(want) */
	obtained->freq = SAMPLERATE;
	obtained->format = 16;
	obtained->channels = 1;
	obtained->samples = SAMPLECOUNT;
	obtained->callback = desired->callback;
	memcpy(&as,obtained,sizeof(SDL_AudioSpec));
	//xSemaphoreAudio = xSemaphoreCreateBinary();
	xTaskCreatePinnedToCore(&updateTask, "updateTask", 8000, NULL, 3, NULL, 1);
	return 0;
}

void SDL_PauseAudio(int pause_on)
{
	paused = pause_on;
}

void SDL_CloseAudio(void)
{
	  i2s_driver_uninstall(I2S_NUM_0); //stop & destroy i2s driver
	  free(sdl_buffer);
}

int SDL_BuildAudioCVT(SDL_AudioCVT *cvt, Uint16 src_format, Uint8 src_channels, int src_rate, Uint16 dst_format, Uint8 dst_channels, int dst_rate)
{
	cvt->len_mult = 1;
	return 0;
}

int SDL_ConvertAudio(SDL_AudioCVT *cvt)
{
	Sint16 *sbuf = cvt->buf;
	Uint8 *ubuf = cvt->buf;
	for(int i = 0; i < cvt->len*2; i+=2)
	{
		ubuf[i] =   ((Sint32)sbuf[i/2] + (Sint32)0x8000) >> 8 ;
		ubuf[i+1] = ((Sint32)sbuf[i/2] + (Sint32)0x8000) >> 8;
	}
	return 0;
}

void SDL_LockAudio(void)
{
	locked = true;
	//if( xSemaphoreAudio != NULL )
	//	xSemaphoreTake( xSemaphoreAudio, 100 );
}

void SDL_UnlockAudio(void)
{
    locked = false;
	//if( xSemaphoreAudio != NULL )
	//	 xSemaphoreGive( xSemaphoreAudio );
}

