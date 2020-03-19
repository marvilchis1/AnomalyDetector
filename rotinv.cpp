unsigned char rotinv( unsigned char pattern ) {
    unsigned char test = pattern;
    unsigned char pmin = pattern;
    bool carry = false;

    for ( int i=0; i<7; i+=1 ) {
       carry = test & 0x01;
       test >>= 1; // test = test >> 1;
       if ( carry ) test &= 0x80;

       if ( test < pmin ) pmin = test;
    }

    return pmin;
}

