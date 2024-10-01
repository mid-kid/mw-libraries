#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct file {
    size_t size;
    unsigned char data[];
};

struct file *file_read(const char *name)
{
    FILE *f = fopen(name, "rb");
    if (!f) return NULL;

    long size;
    if (fseek(f, 0, SEEK_END) == -1 ||
            (size = ftell(f)) == -1 ||
            fseek(f, 0, SEEK_SET) == -1) {
        fclose(f);
        return NULL;
    }

    struct file *file = malloc(sizeof(struct file) + size);
    if (!file) {
        fclose(f);
        return NULL;
    }
    file->size = size;

    if (fread(file->data, file->size, 1, f) != 1) {
        free(file);
        fclose(f);
        return NULL;
    }
    fclose(f);
    return file;
}

bool file_write(const char *name, const struct file *file)
{
    FILE *f = fopen(name, "wb");
    if (!f) return false;
    if (fwrite(file->data, file->size, 1, f) != 1) {
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}

struct name {
    char name[16];
};

struct name *build_names(unsigned count, char *innames[])
{
    struct name *names = malloc(sizeof(struct name) * count);

    for (unsigned i = 0; i < count; i++) {
        // Grab source filename
        char *s = innames[i];

        // Strip the path component
        size_t l = strlen(s);
        char *p = s + l;
        while (p > s) if (strchr("/\\", *--p)) break;
        s = p + 1;

        // Strip the filename extension
        char *d = s;
        while (d < s + l) if (*d++ == '.') break;
        d--;

        // Convert to lowercase and append .o
        char *n = names[i].name;
        char *e = n + sizeof(names->name);
        while (n < e && s < d) *n++ = (*s >= 'A' && *s <= 'Z') ? *s++ - 'A' + 'a' : *s++;
        if (n < e) *n++ = '.';
        if (n < e) *n++ = 'o';
        while (n < e) *n++ = ' ';
    }

    return names;
}

bool parse_arfile(struct file *arfile, unsigned names_len, struct name *names)
{
    if (arfile->size < 8) return false;
    if (memcmp(arfile->data, "!<arch>\n", 8) != 0) return false;

    unsigned name_cur = 0;

    unsigned char *p = arfile->data + 8;
    unsigned char *e = arfile->data + arfile->size;
    while (p < e) {
        if (p + 60 >= e) return false;

        if (name_cur < names_len) {
            memcpy(p, names[name_cur++].name, sizeof(names->name));
        }

        p += 48;
        char size_str[11];
        memcpy(size_str, p, 10);
        size_str[10] = 0;
        unsigned long size = strtoul(size_str, NULL, 10);
        p += 10;

        if (*p++ != '`') return false;
        if (*p++ != '\n') return false;
        if (!size) return false;
        if (p + size - 1 >= e) return false;
        p += size;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <output> <input> [filenames...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *fname_in = argv[2];
    char *fname_out = argv[1];

    unsigned names_len = argc - 3;
    struct name *names = build_names(names_len, argv + 3);

    struct file *arfile = file_read(fname_in);
    if (!parse_arfile(arfile, names_len, names)) {
        fprintf(stderr, "%s: Failed to parse\n", fname_in);
        free(arfile);
        free(names);
        return EXIT_FAILURE;
    }

    file_write(fname_out, arfile);

    free(arfile);
    free(names);
    return EXIT_SUCCESS;
}
