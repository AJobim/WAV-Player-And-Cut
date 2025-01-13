#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>


#pragma comment(lib, "winmm.lib")

typedef struct
{
    char id_chunk[4];
    unsigned short tam_chunk;
    char formato[4];
    char id_subchunk[4];
    unsigned long tam_subchank;
    unsigned short formato_audio;
    unsigned short num_canais;
    unsigned long sample_rate;
    unsigned long byte_rate;
    unsigned short block_align;
    unsigned short bit_por_sample;
} HeaderWAV;

int main()
{
    FILE* fp;
    int botao, opcao;
    char audio[100];
    char nome_audio[100];
    char corte_audio[100];
    char nome_corte_audio[100];
    unsigned long inicio, fim;

    printf ("Digite aqui o nome do arquivo WAV que quer executar: ");
    fgets (audio, sizeof(audio), stdin);
    audio[strcspn(audio, "\n")] = '\0';
    strcpy (nome_audio, audio);
    strcat (audio, ".wav");

    fp = fopen(audio, "rb");
    if (fp == NULL)
    {
        printf ("\nArquivo não encontrado! :(");
        return 1;
    }

    HeaderWAV header;

    fread (&header, sizeof(HeaderWAV), 1, fp);

    printf ("\nInformações do arquivo: ");
    printf ("\nTaxa de sample: %d Hz\n", header.sample_rate);
    printf ("Bits por sample: %d\n", header.bit_por_sample);
    printf ("Numero de canais: %d\n", header.num_canais);

    printf ("\nReproduzindo a música em 3 segundos...");

    Sleep(1000);
    printf ("\n3...");
    Sleep(1000);
    printf ("\n2...");
    Sleep(1000);
    printf ("\n1...");
    Sleep(1000);

    printf("\n\nAgora tocando: %s\n", nome_audio);

    PlaySound(audio, NULL, SND_FILENAME | SND_ASYNC);

    printf ("\nENCERRAR MUSICA -> 1\n");
    scanf("%d", &botao);

    if (botao == 1)
    {
        PlaySound(NULL, 0, 0);
    }

    botao = 0;

    printf ("\nDeseja realizar um recorte na música?\n 0 Não || 1 Sim: ");
    scanf ("%d", &opcao);

    if (opcao==1)
    {

        printf ("\nDigite, em segundos, o tempo do inicio do recorte: ");
        scanf ("%d", &inicio);

        printf ("\nDigite, em segundos, o tempo do fim do recorte: ");
        scanf ("%d", &fim);
        getchar();


        printf ("\nQual nome deseja dar para este recorte? ");
        fgets(nome_corte_audio, sizeof(nome_corte_audio), stdin);
        nome_corte_audio[strcspn(nome_corte_audio, "\n")] = '\0';
        strcat (nome_corte_audio, ".wav");

        FILE* audio_original = fopen(audio, "rb");
        FILE* novo_audio = fopen(nome_corte_audio, "wb");

        if (audio_original == NULL || novo_audio == NULL)
        {
            printf ("\n Erro abrindo um dos arquivos");
            return 0;
        }
            HeaderWAV header;

            fread(&header, sizeof(HeaderWAV), 1, audio_original);
            fwrite(&header, sizeof(HeaderWAV), 1, novo_audio);

            unsigned long deslocamento = inicio * header.byte_rate;

            fseek (audio_original, deslocamento, SEEK_CUR);

            const int bufferSize = 1024;
            char buffer[bufferSize];

            unsigned long bytetotal = (fim - inicio) * header.byte_rate;

            while (bytetotal > 0)
                {
                int bytesLidos = fread(buffer, 1, sizeof(buffer), audio_original);
                int bytesParaCopiar = (bytesLidos < bytetotal) ? bytesLidos : bytetotal;
                fwrite(buffer, 1, bytesParaCopiar, novo_audio);
                bytetotal -= bytesParaCopiar;
                }
            fclose (audio_original);

    printf("\n\nAgora tocando: %s\n", nome_corte_audio);

    PlaySound(nome_corte_audio, NULL, SND_FILENAME | SND_ASYNC);

    printf ("\nENCERRAR MUSICA -> 1\n");
    scanf("%d", &botao);

    if (botao == 1)
    {
        PlaySound(NULL, 0, 0);
    }
        fclose (novo_audio);
    }


return 0;
}
