#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libstream.h"

static int Q_mode(const char *mode)
{
    if (strcmp(mode, "r") == 0)
    {
        return O_RDONLY;
    }
    else if (strcmp(mode, "r+") == 0)
    {
        return O_RDWR;
    }
    else if (strcmp(mode, "w") == 0)
    {
        return O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "w+") == 0)
    {
        return O_RDWR | O_CREAT | O_TRUNC;
    }
    else
    {
        return -1;
    }
}

struct stream *lbs_fopen(const char *path, const char *mode)
{
    if (path == NULL || mode == NULL)
    {
        return NULL;
    }
    int mode_c = Q_mode(mode);
    if (mode_c == -1)
    {
        return NULL;
    }
    int fd = open(path, mode_c);
    if (fd == -1)
    {
        return NULL;
    }
    struct stream *stream1 = malloc(sizeof(struct stream));
    if (stream1 == NULL)
    {
        close(fd);
        return NULL;
    }
    stream1->flags = mode_c;
    stream1->error = 0;
    stream1->fd = fd;
    stream1->io_operation = STREAM_READING;
    if (isatty(fd) == 1)
    {
        stream1->buffering_mode = STREAM_LINE_BUFFERED;
    }
    else
    {
        stream1->buffering_mode = STREAM_BUFFERED;
    }
    stream1->buffered_size = 0;
    stream1->already_read = 0;
    return stream1;
}

struct stream *lbs_fdopen(int fd, const char *mode)
{
    if (fd < 0 || mode == NULL)
    {
        return NULL;
    }
    int mode_c = Q_mode(mode);
    if (mode_c == -1)
    {
        return NULL;
    }
    struct stream *stream1 = malloc(sizeof(struct stream));
    if (stream1 == NULL)
        return NULL;
    stream1->flags = mode_c;
    stream1->error = 0;
    stream1->fd = fd;
    stream1->io_operation = STREAM_READING;
    if (isatty(fd) == 1)
    {
        stream1->buffering_mode = STREAM_LINE_BUFFERED;
    }
    else
    {
        stream1->buffering_mode = STREAM_BUFFERED;
    }
    stream1->buffered_size = 0;
    stream1->already_read = 0;
    return stream1;
}

int lbs_fclose(struct stream *file)
{
    lbs_fflush(file);
    close(file->fd);
    free(file);
    return 0;
}

int lbs_fputc(int c, struct stream *stream)
{
    if (stream == NULL)
    {
        return -1;
    }
    if (stream_writable(stream))
    {
        if (stream->io_operation == STREAM_READING)
        {
            lbs_fflush(stream);
            if (stream->error == 1)
            {
                return -1;
            }
            stream->io_operation = STREAM_WRITING;
        }
        stream->buffer[stream->buffered_size++] = c;
        if (stream->buffering_mode == STREAM_LINE_BUFFERED && c == '\n')
        {
            lbs_fflush(stream);
        }
        else if (stream->buffering_mode == STREAM_UNBUFFERED
                 || stream->buffered_size == LBS_BUFFER_SIZE)
        {
            lbs_fflush(stream);
        }
        if (stream->error == 1)
        {
            return -1;
        }
        return c;
    }
    return -1;
}

int lbs_fgetc(struct stream *stream)
{
    unsigned char save = 0;
    if (stream == NULL)
    {
        return -1;
    }
    if (stream_readable(stream))
    {
        if (stream->io_operation == STREAM_WRITING)
        {
            lbs_fflush(stream);
            if (stream->error == 1)
                return -1;
            stream->io_operation = STREAM_READING;
        }
        if (stream->buffered_size == 0)
        {
            ssize_t size = read(stream->fd, stream->buffer, LBS_BUFFER_SIZE);
            if (size <= 0)
            {
                return -1;
            }
            stream->buffered_size = size;
            stream->already_read = 0;
        }
        save = stream->buffer[stream->already_read++];
        if (stream->already_read == stream->buffered_size)
        {
            lbs_fflush(stream);
            if (stream->error == 1)
                return -1;
        }
        return save;
    }
    else
        return -1;
}

static int ff(struct stream *stream)
{
    if (stream_remaining_buffered(stream) != 0)
    {
        int a = lseek(stream->fd, -stream_remaining_buffered(stream), SEEK_CUR);
        if (a < 0)
        {
            stream->error = 1;
            return -1;
        }
    }
    stream->buffered_size = 0;
    stream->already_read = 0;
    stream->error = 0;
    return 0;
}

static int ff15(struct stream *stream)
{
    ssize_t a = write(stream->fd, stream->buffer, stream->buffered_size);
    if (a < 0)
    {
        stream->error = 1;
        return -1;
    }
    stream->buffered_size = 0;
    stream->already_read = 0;
    stream->error = 0;
    return 0;
}

int lbs_fflush(struct stream *stream)
{
    if (stream->io_operation == STREAM_READING)
    {
        return ff(stream);
    }
    else
    {
        return ff15(stream);
    }
}
