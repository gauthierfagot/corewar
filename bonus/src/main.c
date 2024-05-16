/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for corewar
*/

#include <SDL2/SDL.h>
#include "macros.h"
#include "libmy.h"
#include "functions.h"

static int load_music(SDL_AudioSpec *wavSpec, Uint32 *wavLength,
    Uint8 **wavBuffer, SDL_AudioDeviceID *deviceId)
{
    if (SDL_LoadWAV("./assets/tf_nemesis.wav", wavSpec,
    wavBuffer, wavLength) == NULL)
    {
        fprintf(stderr, "Could not load sound file: %s\n", SDL_GetError());
        return ERROR;
    }
    *deviceId = SDL_OpenAudioDevice(NULL, 0, wavSpec, NULL, 0);
    if (deviceId == 0)
    {
        fprintf(stderr, "Failed to open audio: %s\n", SDL_GetError());
        return ERROR;
    }
    int success = SDL_QueueAudio(*deviceId, *wavBuffer, *wavLength);
    if (success < 0)
    {
        fprintf(stderr, "Failed to queue audio: %s\n", SDL_GetError());
        return ERROR;
    }
    SDL_PauseAudioDevice(*deviceId, 0);
    return SUCCESS;
}

static int launch_game(int argc, char **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        print_help();
        return SUCCESS;
    }
    return corewar(argv);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
    int return_value = 0;

    if (load_music(&wavSpec, &wavLength, &wavBuffer, &deviceId) == ERROR)
        return ERROR;
    return_value = launch_game(argc, argv);
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
    return return_value;
}
