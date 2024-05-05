#ifndef COMPLEX_H
#define COMPLEX_H

struct complex
{
    float real;
    float img;
};

// Print
void print_complex(struct complex a);

// Operations
struct complex neg_complex(struct complex a);
struct complex add_complex(struct complex a, struct complex b);
struct complex sub_complex(struct complex a, struct complex b);
struct complex mul_complex(struct complex a, struct complex b);
struct complex div_complex(struct complex a, struct complex b);

#endif /* !COMPLEX_H */
