#include "include/factorial.h"

#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    <string.h>
#include    <errno.h>
#include    <memory.h>
#include    <float.h>
#include    <limits.h>

#define PRINTOUT
#define SAMPLING_RATE 48000
#define NORM_VOLUME_0DB      0.01  /* this value is to be determined */


void Tone_Generator_16bits(
    short *Output,    /* o: output tone file name                        */
    int Out_length,   /* i: output tone file length in number of samples */
    int Frequency,    /* i: tone frequency in Hz                         */
    double Volume_dB, /* i: tone magnitude in dB                         */
    int SampRate      /* i: tone signal sampling rate                    */
    );


/*-------------------------------------------------------------------*/
int main (int argc, char *argv[] )
    {
     FILE *f_Rv_Out=NULL;
     int Frequency, Out_length, Volume_dB;
     short *Output;
     
     /*-------------------------------------------------------------------*/
     /*              Input & Output setting                               */
     /*-------------------------------------------------------------------*/
     if (argc<5)
       {
       printf("\n ********************************************************  \n");
         printf(" *****************  Frequency Tone Generator    *********  \n");
         printf(" ********************************************************  \n\n");

         printf("\n%s  output_tone_file  output_length(samples)  Frequency(Hz)  Volume_dB(0-40dB)\n\n", argv[0]);
         exit (0);
       }

     /*necessary in/out*/
     if ( (f_Rv_Out = fopen(argv[1], "wb" ) ) == NULL) {
#ifdef PRINTOUT
         printf("\n  error_open_file (wb) : file_name : %s\n", argv[1]);
#endif
         exit(1);
     }
     Out_length = atoi(argv[2]);
     Frequency = atoi(argv[3]);
     Volume_dB = atoi(argv[4]);
#ifdef PRINTOUT
     if (Frequency>=SAMPLING_RATE/2) {
         printf("\n  error : Frequency>=SAMPLING_RATE/2 !, SAMPLING_RATE=%f\n", SAMPLING_RATE);
         exit(1);
     }
#endif

     printf("\n Executable :  %s\n", argv[0]);
     printf(" output_tone_file :  %s\n", argv[1]);
     printf(" output_length : %ld (samples)\n", Out_length);
     printf(" tone Frequency :  %ld (Hz)\n", Frequency);
     printf(" Volume_dB :  %ld (dB)\n", Volume_dB);
     printf(" SAMPLING_RATE : %ld (Hz)\n", SAMPLING_RATE);

     /* Parameters conversion */
      //Out_length *= SAMPLING_RATE;
     Output = (short *)calloc((unsigned)Out_length,sizeof(short));
     if (!Output) printf("allocation failure in Output[]");

     /* Tone Generator */
     Tone_Generator_16bits(Output, Out_length, Frequency, Volume_dB, SAMPLING_RATE);
     
     /* Write out */
     fwrite(Output, sizeof(short), Out_length, f_Rv_Out);

      /*  Close IO files */
     fclose(f_Rv_Out);

#ifdef PRINTOUT
     printf("\n---------------  End ---------------------\n");
#endif

     return 0;
     /*-------------------------------------------------------------------*/
    }








/*--------------------------------------------------------------------------------*/


void Tone_Generator_16bits(
    short *Output,    /* o: output tone file name                        */
    int Out_length,   /* i: output tone file length in number of samples */
    int Frequency,    /* i: tone frequency in Hz                         */
    double Volume_dB, /* i: tone magnitude in dB                         */
    int SampRate      /* i: tone signal saampling rate                   */
    )
{
int i;
double F, vol, Volume_norm;

    F= 2.*3.141592654*Frequency/SampRate; //normalized frequency
    Volume_norm = NORM_VOLUME_0DB*pow(10., Volume_dB/20.);
    if (Volume_norm>1) Volume_norm=1;
    vol = 32767.*Volume_norm; //normalized volume
    for (i=0;i<Out_length;i++) Output[i] = (short)(vol*sin(F*i));
    
    return;
}
