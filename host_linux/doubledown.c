#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for getopt() & nice()
//#include "sound.h"

#define BUF_SIZE 1024 // alter the kilobytes logic if this changes
//#define ID_STRING "Cypress_Digital_Audio_DVK" // Bill has one of these
#define ID_STRING "REDOUBLER_Random_Number_Generator"
#define FALSE 0
#define TRUE 1

#define DEFAULT_HW_DEVICE           "hw:0"
#define DEFAULT_HW_ITEM             "capture"
#define DEFAULT_SAMPLE_RATE         48000
#define DEFAULT_SKIP_BYTES          (48000 * 4 * 1)
#define PAGE_SIZE 4096


/******************** start of sound.c, in-lined so just one .c file ****************/

/*
 * (c) 2008-2014 Nicholas J. Kain <njkain at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// Peter Allan <alwynallan@gmail.com> modified for use with REDOUBLER
// Original found in snd-egd package on Github

#include <alsa/asoundlib.h>
#include <linux/soundcard.h>
//#include "nk/log.h" not needed, APA
//#include "defines.h" needed parts brought in above
//#include "sound.h" needed parts brought in above

static char *cdevice = DEFAULT_HW_DEVICE;
static const char *cdev_id = DEFAULT_HW_ITEM;
static unsigned int sample_rate = DEFAULT_SAMPLE_RATE;
static snd_pcm_t *pcm_handle = NULL;
static size_t pcm_bytes_per_frame;
static int snd_format = -1;
static unsigned int skip_bytes = DEFAULT_SKIP_BYTES;
static int pcm_can_pause;

void suicide(const char * fmt, ...) // APA guess
{
  va_list args;

  va_start(args,fmt);
  vfprintf(stderr,fmt, args);
  fprintf(stderr,"\n");
  exit(1);
}

int sound_read(void *buf, size_t size)
{
    snd_pcm_sframes_t fr;

    fr = snd_pcm_readi(pcm_handle, buf, size / pcm_bytes_per_frame);
    /* Make sure we aren't hitting a disconnect/suspend case */
    if (fr < 0)
        fr = snd_pcm_recover(pcm_handle, fr, 0);
    /* Nope, something else is wrong. Bail. */
    if (fr < 0 || (fr == -1 && errno != EINTR))
        suicide("sound_read(): Read error: %m");
    return fr*pcm_bytes_per_frame;
}

void sound_stop(void)
{
    if (pcm_can_pause)
        snd_pcm_pause(pcm_handle, 1);
}

void sound_open(void)
{
    char buf[PAGE_SIZE];
    int err, i;
    snd_pcm_hw_params_t *ct_params;

    if ((err = snd_pcm_open(&pcm_handle, cdevice, SND_PCM_STREAM_CAPTURE, 0)) < 0)
        suicide("Error opening PCM device %s: %s", cdevice, snd_strerror(err));

    snd_pcm_hw_params_alloca(&ct_params);

    err = snd_pcm_hw_params_any(pcm_handle, ct_params);
    if (err < 0)
        suicide("Broken configuration for %s PCM: no configurations available: %s",
                   cdev_id, snd_strerror(err));

    /* Disable rate resampling */
    err = snd_pcm_hw_params_set_rate_resample(pcm_handle, ct_params, 0);
    if (err < 0)
        suicide("Could not disable rate resampling: %s", snd_strerror(err));

    /* Set access to SND_PCM_ACCESS_RW_INTERLEAVED -- NONINTERLEAVED would
     * be preferable, but it's uncommon on sound cards.*/
    err = snd_pcm_hw_params_set_access(pcm_handle, ct_params,
                                       SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0)
        suicide("Could not set access to SND_PCM_ACCESS_RW_INTERLEAVED: %s",
                   snd_strerror(err));

    /* Choose rate nearest to our target rate */
    err = snd_pcm_hw_params_set_rate_near(pcm_handle, ct_params, &sample_rate, 0);
    if (err < 0)
        suicide("Rate %iHz not available for %s: %s",
                   sample_rate, cdev_id, snd_strerror(err));

    /* Set sample format -- prefer endianness equal to that of the CPU */
#ifdef HOST_ENDIAN_BE
    snd_format = SND_PCM_FORMAT_S16_BE;
#else
    snd_format = SND_PCM_FORMAT_S16_LE;
#endif
    err = snd_pcm_hw_params_set_format(pcm_handle, ct_params, snd_format);
    if (err < 0) {
#ifdef HOST_ENDIAN_BE
        snd_format = SND_PCM_FORMAT_S16_LE;
#else
        snd_format = SND_PCM_FORMAT_S16_BE;
#endif
        err = snd_pcm_hw_params_set_format(pcm_handle, ct_params, snd_format);
    }
    if (err < 0)
        suicide("Sample format (SND_PCM_FORMAT_S16_BE and _LE) not available for %s: %s",
                   cdev_id, snd_strerror(err));

    /* Set stereo for faster sampling. */
    err = snd_pcm_hw_params_set_channels(pcm_handle, ct_params, 2);
    if (err < 0)
        suicide("Channels count (%i) not available for %s: %s",
                   2, cdev_id, snd_strerror(err));

    /* Apply settings to sound device */
    err = snd_pcm_hw_params(pcm_handle, ct_params);
    if (err < 0)
        suicide("Could not apply settings to sound device!");

    pcm_bytes_per_frame = snd_pcm_frames_to_bytes(pcm_handle, 1);
    //fprintf(stderr,"bytes-per-frame: %d\n", pcm_bytes_per_frame);
    pcm_can_pause = snd_pcm_hw_params_can_pause(ct_params);

    /* Discard the initial data; it may be a click or something else odd. */
    for (i = skip_bytes; i > 0; i -= (sizeof buf))
        sound_read(buf, sizeof buf);
    //fprintf(stderr,"skipped %d bytes of pcm input\n", skip_bytes);

    if (pcm_can_pause) {
        sound_stop();
        //fprintf(stderr,"alsa device supports pcm pause\n");
    }
}

int sound_bytes_per_frame(void)
{
    return pcm_bytes_per_frame;
}

void sound_start(void)
{
    if (pcm_can_pause)
        snd_pcm_pause(pcm_handle, 0);
}

void sound_close(void)
{
    snd_pcm_close(pcm_handle);
    pcm_handle = NULL;
}

int sound_is_le(void)
{
    if (snd_format == SND_PCM_FORMAT_S16_BE)
        return 0;
    return 1;
}

int sound_is_be(void)
{
    if (snd_format == SND_PCM_FORMAT_S16_LE)
        return 0;
    return 1;
}

void sound_set_device(char *str)
{
    cdevice = strdup(str);
}

void sound_set_port(char *str)
{
    cdev_id = strdup(str);
}

void sound_set_sample_rate(int rate)
{
    if (rate > 0)
        sample_rate = rate;
    else
        sample_rate = DEFAULT_SAMPLE_RATE;
}

void sound_set_skip_bytes(int sb)
{
    if (sb > -1)
        skip_bytes = sb;
    else
        skip_bytes = DEFAULT_SKIP_BYTES;
}
/********************************* end of original sound.c *******************************************/

int default_card(const int list)
{
  char buf[BUF_SIZE];
  char serial[80];
  int  card_num;
  int first=-1;
  FILE *fp;

  sprintf(buf,"ls -l /dev/snd/by-id | grep %s | sed -e 's/^.*%s_//' -e 's|-00 -> ../controlC|\t|'",ID_STRING,ID_STRING);
  fp=popen(buf,"r");
  if(fp==NULL){
    fprintf(stderr,"Could not open command: %s\n",buf);
    exit(9);
  }
  if(list) fprintf(stderr,"%-20s\t%-10s\t%-20s\n","Available REDOUBLERs:","Card #","Serial Number");
  while(fgets(buf,BUF_SIZE,fp)){
    sscanf(buf,"%s\t%d",serial,&card_num);
    if(list) fprintf(stderr,"%-20s\t%-10d\t%-20s\n","",card_num,serial);
    if(first==-1) first=card_num;
  }
  pclose(fp);
  return(first);
}

int main(int argc, char *argv[])
{
  unsigned char buf[BUF_SIZE];
  char device[80];
  int c, card_num,kilobytes=0,kb_out=0,n_opt=0;
  int actual_bytes;
  FILE *fo;

  card_num=default_card(FALSE);

  while((c=getopt(argc,argv,"lc:k:n"))!=-1){
    switch(c){
      case 'l':
        default_card(TRUE);
        exit(0);
      case 'c':
        card_num=atoi(optarg);
        break;
      case 'k':
        kilobytes=atoi(optarg)+1; // extra to account for the skipped bytes
        break;
      case 'n':
        n_opt=1;
        break;
      default:
        fprintf(stderr,"Usage: %s [-l] [-c card_num] [-k kilobytes]\n",argv[0]);
        exit(3);
    }
  }

  if(card_num<0) {
    fprintf(stderr,"%s: Valid REDOUBLER card_num neither found nor specified.\n",argv[0]);
    exit(9);
  }
  sprintf(device,"hw:%d",card_num);
  sound_set_device(device);
  sound_set_skip_bytes(960);
  sound_open();
  atexit(sound_close);

  fo=popen("cat | cat","w"); // quick-and-dirty double buffering, done before nice()
  if(n_opt) if(nice(-10)==-1) fprintf(stderr,"%s: Only root can increase priority.\n",argv[0]);
  if(fo == NULL){
    fprintf(stderr,"%s: Could not open ouput buffering process.\n",argv[0]);
    exit(11);
  }
  sound_start();
  while((kilobytes <= 0) || (kb_out < kilobytes)){
    actual_bytes=sound_read(buf,BUF_SIZE);
    if(actual_bytes==BUF_SIZE){
      fwrite(buf,1,BUF_SIZE,fo);
      kb_out++;
    }
    else fprintf(stderr,"%s: Read glitch, actual_bytes = %d\n",argv[0],actual_bytes);
  }
  sound_stop();
  pclose(fo);

  exit(0); // shoud trigger atexit()
}
