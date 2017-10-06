#include "graphviz.h"
#include "uthash/uthash.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef linux

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

#endif

#ifdef _WIN32
short int is_windows = 1;
#else
short int is_windows = 0;
#endif

struct col {
    int id;            /* we'll use this field as the key */
    char cor[15];
    UT_hash_handle hh; /* makes this structure hashable */
};

struct col *colors = NULL;

//*****************************************************************************
//                          FUN합ES P/ GRAPHVIZ
//*****************************************************************************

void add_color(int color_id, char *cor) {
    struct col *s;
    HASH_FIND_INT(colors, &color_id, s);
    if (s == NULL) {
        s = (struct col *) malloc(sizeof(struct col));
        s->id = color_id;
        strcpy(s->cor, cor);
        HASH_ADD_INT(colors, id, s);
    }
}

struct col *find_color(int color_id) {
    struct col *s;

    HASH_FIND_INT(colors, &color_id, s);
    return s;
}

void fill_colors() {
    int i;
    char cor[25];
    for (i = 1; i <= 10; i++) {
        switch (i) {
            case 1:
                strcpy(cor, "black");
                break;
            case 2:
                strcpy(cor, "blue");
                break;
            case 3:
                strcpy(cor, "brown1");
                break;
            case 4:
                strcpy(cor, "cadetblue1");
                break;
            case 5:
                strcpy(cor, "chartreuse");
                break;
            case 6:
                strcpy(cor, "crimson");
                break;
            case 7:
                strcpy(cor, "darkolivegreen1");
                break;
            case 8:
                strcpy(cor, "darkorchid");
                break;
            case 9:
                strcpy(cor, "deeppink");
                break;
            case 10:
                strcpy(cor, "gold");
                break;
            default:
                break;
        }
        add_color(i, cor);
    }
}

/**
* Função para gerar o .png do grafo gerado quando o tipo de grafo for
* CHEIO.
**/
void gera_graphviz_matriz(int num_vertices, short int m[num_vertices][num_vertices], char * title) {
    FILE *fp;
    char *homepath = "";
    short int i, u;
    int id;
    struct col *color;
    char buf[200];

    //fp = fopen("../gerados/grafo1.gv", "w");
    if (is_windows == 1) {
        homepath = getenv("homepath");
        if (homepath == NULL) {
            return;
        }
    }
    char teste[10];
    strcpy(teste, "teste");
#ifdef linux
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    strcpy(homepath, homedir);
#endif // linux

    char sep[2];
    if (is_windows == 1) {
        strcpy(sep, "\\");
    } else {
        strcpy(sep, "/");
    }
    int suffix = 0, fd;
    sprintf(buf, "mkdir %s%sgrafosgerados", homepath, sep);
    system(buf);
    do {
        suffix++;
        sprintf(buf, "%s%sgrafosgerados%sgrafo%d.gv", homepath, sep, sep, suffix);
        fd = open(buf, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    } while (fd < 0);
    fp = fopen(buf, "w");
    printf("graph G1 {\n");
    fputs("graph G1 {\n", fp);
    printf("\tGraph [label = \"%s\"];\n", title);
    sprintf(buf, "\tGraph [label = \"%s\"];\n", title);
    fputs(buf, fp);
    for (i = 0; i < num_vertices; i++) {
        id = (i + 1) % 10;
        if ((i % 10) == 9) {
            id = 10;
        }
        color = find_color(id);
        printf("\tedge [color = ""%s"", fontcolor = ""%s""];\n",
               color->cor, color->cor);
        sprintf(buf, "\tedge [color = ""%s"", fontcolor = ""%s""];\n",
                color->cor, color->cor);
        fputs(buf, fp);

        printf("\t%hd [color = ""%s"", fontcolor = ""%s""];\n",
               i, color->cor, color->cor);
        sprintf(buf, "\t%hd [color = ""%s"", fontcolor = ""%s""];\n",
                i, color->cor, color->cor);
        fputs(buf, fp);
        for (u = i; u < num_vertices; u++) {
            if (m[i][u] == 1) {
                printf("\t%hd -- %hd;\n", i, u);
                sprintf(buf, "\t%hd -- %hd;\n", i, u);
                fputs(buf, fp);
            }
        }
    }
    printf("}\n");
    fputs("}\n", fp);
    fclose(fp);
    sprintf(buf,
            "dot -Tpng %s%sgrafosgerados%sgrafo%d.gv -o %s%sgrafosgerados%sgrafo%d.png",
            homepath, sep, sep, suffix, homepath, sep, sep, suffix);
    system(buf);
    if (is_windows == 1) {
        sprintf(buf, "%s%sgrafosgerados%sgrafo%d.png", homepath, sep, sep, suffix);
    } else {
        sprintf(buf, "eog %s%sgrafosgerados%sgrafo%d.png", homepath, sep, sep, suffix);
    }
    system(buf);
}

void graphviz_item_lista(FILE *fp, struct adj_list *e) {
    struct adj_list *e1;
    char buf[200];

    if (e->prox == NULL) {
        printf("\t%d;\n", e->cod);
        sprintf(buf, "\t%d;\n", e->cod);
        fputs(buf, fp);
        return;
    }

    e1 = e->prox;

    while (1) {
        printf("\t%d -- %d;\n", e->cod, e1->cod);
        sprintf(buf, "\t%d -- %d;\n", e->cod, e1->cod);
        fputs(buf, fp);

        if (e1->prox == NULL) {
            break;
        } else {
            e1 = e1->prox;
        }
    }
}

/**
* Função para gerar o .png do grafo gerado quando o tipo de grafo for
* VAZIO.
**/
void gera_graphviz_lista(int num_vertices, struct adj_list l[num_vertices], char * title) {
    FILE *fp;
    char *homepath = "";
    int i, id;
    struct col *color;
    char buf[200];

    if (is_windows == 1) {
        homepath = getenv("homepath");
        if (homepath == NULL) {
            return;
        }
    }
    char teste[10];
    strcpy(teste, "teste");
#ifdef linux
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    strcpy(homepath, homedir);
#endif // linux

    char sep[2];
    if (is_windows == 1) {
        strcpy(sep, "\\");
    } else {
        strcpy(sep, "/");
    }

    sprintf(buf, "mkdir %s%sgrafosgerados", homepath, sep);
    system(buf);
    int suffix = 0, fd;
    do {
        suffix++;
        sprintf(buf, "%s%sgrafosgerados%sgrafo%d.gv", homepath, sep, sep, suffix);
        fd = open(buf, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    } while (fd < 0);
    fp = fopen(buf, "w");
    printf("strict graph G1 {\n");
    fputs("strict graph G1 {\n", fp);
    printf("\tGraph [label = \"%s\"];\n", title);
    sprintf(buf, "\tGraph [label = \"%s\"];\n", title);
    fputs(buf, fp);
    for (i = 0; i < num_vertices; i++) {
        id = (i + 1) % 10;
        if ((i % 10) == 9) {
            id = 10;
        }
        color = find_color(id);
        printf("\tedge [color = ""%s"", fontcolor = ""%s""];\n",
               color->cor, color->cor);
        sprintf(buf, "\tedge [color = ""%s"", fontcolor = ""%s""];\n",
                color->cor, color->cor);
        fputs(buf, fp);

        printf("\t%hd [color = ""%s"", fontcolor = ""%s""];\n",
               i, color->cor, color->cor);
        sprintf(buf, "\t%hd [color = ""%s"", fontcolor = ""%s""];\n",
                i, color->cor, color->cor);
        fputs(buf, fp);
        graphviz_item_lista(fp, &l[i]);
    }

    printf("}\n");
    fputs("}\n", fp);
    fclose(fp);
    sprintf(buf,
            "dot -Tpng %s%sgrafosgerados%sgrafo%d.gv -o %s%sgrafosgerados%sgrafo%d.png",
            homepath, sep, sep, suffix, homepath, sep, sep, suffix);
    system(buf);
    if (is_windows == 1) {
        sprintf(buf, "%s%sgrafosgerados%sgrafo%d.png", homepath, sep, sep, suffix);
    } else {
        sprintf(buf, "eog %s%sgrafosgerados%sgrafo%d.png", homepath, sep, sep, suffix);
    }
    system(buf);
}
