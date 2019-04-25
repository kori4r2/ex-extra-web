#include <stdio.h>

char get_char( FILE *stream ) {
    char c;
    do
        c = getc(stream);
    while ( c == ' ' || c == '\n' || c == '\t' || c == '\r' );
    return c;
}

void fun( FILE *stream, FILE *out ) {   
    int counter = -1;
    char c;

    do {
        c = get_char(stream);
        if ( c == EOF )
            break;

        if ( c != '<' ) { // print text
            for ( int i = counter + 1; i; --i )
                putc( ' ', out );
            fprintf( out, "TEXT: " );
            do {
                if ( c == '\n' )
                    fprintf( out, "<BR>" ); // random separator
                else
                    putc( c, out );
                c = getc( stream );
            } while ( c != '<' );
            putc( '\n', out );
        }

        c = getc( stream );
        if ( c != '/' ) { // nest deeper
            ++counter;
            for ( int i = counter; i; --i )
                putc( ' ', out );
        } else { // go back in nesting
            --counter;
            // maybe here should be some exception handling
            do // assuming there's no strings in quotation marks here
                c = getc( stream );
            while ( c != '>' );
            continue;
        }

        ungetc( c, stream );
        do { // reading tag
            c = getc(stream);
            if( c == '/' ) { // checking if it's not a <blahblah/>
                c = getc(stream);
                if ( c == '>' ) {
                    --counter;
                    break;
                }
                putc( '/', out );
                putc( c, out );
            } else if ( c == '"' ) { // not parsing strings put in quotation marks
                do {
                    putc( c, out ); c = getc( stream );
                    if ( c == '\\' ) {
                        putc( c, out ); c = getc( stream );
                        if ( c == '"' ) {
                            putc( c, out ); c = getc( stream );
                        }
                    }
                } while ( c != '"' );
                putc( c, out );
            } else if ( c == '>' ) { // end of tag
                break;
            } else // standard procedure
                putc( c, out );
        } while ( true );
        putc( '\n', out );
    } while (true);
    fprintf( out, "Counter: %d", counter );
}

int main() {
    const char *name = "rfb.html";
    const char *oname = "out.txt";
    FILE *file = fopen(name, "r");
    FILE *out = fopen(oname, "w");
    fun( file, out );
    return 0;
}
