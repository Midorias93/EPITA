#ifndef LIBSTREAM_H
#define LIBSTREAM_H

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

/*
** /!\ DO NOT MODIFY THIS FILE, AS IT WILL BE OVERRIDDEN DURING CORRECTION. /!\
**
** You can add your own functions declarations to OTHER HEADER FILES.
*/

/* the value returned when end of file is reached */
#define LBS_EOF (-1)

/* the size of the buffer */
#define LBS_BUFFER_SIZE 32

/*
** Describes the current operation:
**  - if reading, the buffer contains read-buffered data
**  - if writing, the buffer contains write-buffered data
*/
enum stream_io_operation
{
    STREAM_READING = 0,
    STREAM_WRITING,
};

/*
** Controls when to flush the buffer:
**  - when unbuffered, flush every time a character is written
**  - when buffered, flush when the buffer is full
**  - when line buffered, flush when the buffer is full or when a \n
**    character is written
*/
enum stream_buffering
{
    STREAM_UNBUFFERED = 0,
    STREAM_LINE_BUFFERED,
    STREAM_BUFFERED,
};

struct stream
{
    /* the flags passed to open */
    int flags;

    /*
    ** Initially, this variable is 0.
    ** When a function such as fgetc fails, it is set to 1 to indicate
    ** something went wrong. This is useful to make the difference between
    ** reaching the end of file and read errors while using fgetc and
    ** some others.
    ** It is often referred to as the error indicator.
    */
    int error;

    /* the file descriptor, as returned by open(2) */
    int fd;

    /*
    ** the kind of data stored by the buffer.
    ** The default value shouldn't matter.
    */
    enum stream_io_operation io_operation;

    /*
    ** defines when to flush **output**.
    ** This field does not control input buffering (which is always fully
    ** buffered).
    **
    ** The default value is LINE_BUFFERED if isatty(fd), BUFFERED otherwise.
    */
    enum stream_buffering buffering_mode;

    /* the amount of used bytes in the buffer */
    size_t buffered_size;

    /*
    ** /!\ This field only makes sense when io_operation is STREAM_READING /!\
    ** the amount of data already read from the buffer by the user.
    */
    size_t already_read;

    /*
    **                   buffer
    **               -------------->
    ** +==============+====================+---------------------+
    ** | already_read | remaining_buffered | unused_buffer_space |
    ** +==============+====================+---------------------+
    **   \_______________________________/
    **             buffered_size
    **
    ** /!\ The buffer can contain either read-buffered or write-buffered
    *data,data
    **     depending on the value of io_operation /!\
    */
    char buffer[LBS_BUFFER_SIZE];
};

/*
** These functions are defined in a header for optimization reasons:
** each .c file that includes this header will get its own copy of the
** function's code, thus easily make optimizations.
**
** ``static`` means each compilation unit (.c file) will have its own copy
** of the function without them clashing.
**
** ``inline`` means the content of the function should be "copy pasted"
** where it's called. It also tells the compiler not to complain when the
** function isn't used.
**
** They're just like a macro, except the type of arguments is checked.
*/

static inline size_t stream_remaining_buffered(struct stream *stream)
{
    return stream->buffered_size - stream->already_read;
}

static inline size_t stream_unused_buffer_space(struct stream *stream)
{
    return sizeof(stream->buffer) - stream->buffered_size;
}

static inline bool stream_readable(struct stream *stream)
{
    int access_mode = stream->flags & O_ACCMODE;
    if (access_mode == O_RDWR)
        return true;
    return access_mode == O_RDONLY;
}

static inline bool stream_writable(struct stream *stream)
{
    int access_mode = stream->flags & O_ACCMODE;
    if (access_mode == O_RDWR)
        return true;
    return access_mode == O_WRONLY;
}

static inline int lbs_ferror(struct stream *stream)
{
    return stream->error;
}

static inline void lbs_clearerr(struct stream *stream)
{
    stream->error = 0;
}

static inline void lbs_setbufmode(struct stream *stream,
                                  enum stream_buffering mode)
{
    stream->buffering_mode = mode;
}

/*
** Opens the file at some path with the flags described by mode, and wrap it in
** a buffered stream. It works just like fopen(3), except you only have to
** handle the modes r, r+, w and w+
*/
struct stream *lbs_fopen(const char *path, const char *mode);

/*
** Initializes a stream structure with the given file descriptor and mode. It
** works just like lbs_fopen() except it takes the file descriptor instead of
** the path.
**
** It can be used by lbs_fopen() to make implementation clearer.
** It will also be useful to initialize streams to already open file
** descriptors, such as stdin, stdout and stderr.
**
** It may fail when calling isatty() and the file descriptor is invalid.
** Returns NULL on failure.
*/
struct stream *lbs_fdopen(int fd, const char *mode);

/*
** Closes the stream and underlying file descriptor, flushing buffered data.
** No other function should be called on the stream after lbs_fclose(), as
** the stream is freed if the function returns successfully.
** Works just like fclose(3).
*/
int lbs_fclose(struct stream *file);

/*
** Writes a single character to some stream.
** It may cause the stream to flush if the buffer is full or the current
** buffering policy requires it.
** Works just like fputc(3). May set the error indicator.
*/
int lbs_fputc(int c, struct stream *stream);

/*
** Reads a new character from the stream's buffer.
** If the buffer it empty, it should be refilled.
** Works just like fgetc(3). May set the error indicator.
*/
int lbs_fgetc(struct stream *stream);

/*
** Flushes the stream's buffer to the underlying file descriptor, making sure
** the stream position is correct. When there is some write data buffered, it
** has to be written. When there is some read data buffered, it has to be
** discarded and the process must seek the file descriptor back to the
** position the user expects.
**
** Works just like fflush(3), except:
**  - lbs_fflush() *DOES NOT* flush all open output streams if stream is NULL.
** May set the error indicator.
*/
int lbs_fflush(struct stream *stream);

#endif /* !LIBSTREAM_H */
