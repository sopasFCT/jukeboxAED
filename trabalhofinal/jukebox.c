#include <stdlib.h>
#include <string.h>

#include "dicionario.h"
#include "musica.h"
#include "playlist.h"
#include "jukebox.h"

struct _jukebox{
    dicionario playlists;
    dicionario musicas;
}

