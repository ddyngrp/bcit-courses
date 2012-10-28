libiconv
--------
curl -O http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.13.1.tar.gz
tar xvzf libiconv-1.13.1.tar.gz
cd libiconv-1.13.1
CFLAGS="-isysroot /Developer/SDKs/MacOSX10.6.sdk -arch i386" \
     ./configure --disable-shared --disable-dependency-tracking
make
sudo make install
cd ..


gnupg
-----
curl -O ftp://ftp.gnupg.org/gcrypt/gnupg/gnupg-1.4.10.tar.gz
tar -xvzf gnupg-1.4.10.tar.gz
cd gnupg-1.4.10
./configure CC="gcc -arch i386"
make
sudo make install
cd ..


gettext
-------
curl -O http://ftp.gnu.org/gnu/gettext/gettext-0.17.tar.gz
tar xvzf gettext-0.17.tar.gz
cd gettext-0.17
CFLAGS="-isysroot /Developer/SDKs/MacOSX10.6.sdk -arch i386" \
     ./configure --disable-shared --disable-dependency-tracking \
     --disable-java --disable-native-java --disable-csharp \
     --with-included-gettext --with-included-glib \
     --with-included-libcroco --with-included-libxml --disable-libasprintf --with-libiconv-prefix=shared,/usr/local 
make
sudo make install
cd ..

libgpg-error
------------
curl -O ftp://ftp.gnupg.org/gcrypt/libgpg-error/libgpg-error-1.7.tar.bz2
tar xvjf libgpg-error-1.7.tar.bz2
cd libgpg-error-1.7
CFLAGS="-isysroot /Developer/SDKs/MacOSX10.6.sdk -arch i386" \
	LDFLAGS="-framework CoreFoundation" \
     ./configure --disable-shared --disable-dependency-tracking 
make
sudo make install
cd ..


gpgme
-----
curl -O ftp://ftp.gnupg.org/gcrypt/gpgme/gpgme-1.2.0.tar.bz2
tar xjvf gpgme-1.2.0.tar.bz2
cd gpgme-1.2.0
CFLAGS="-isysroot /Developer/SDKs/MacOSX10.6.sdk -arch i386" \
    ./configure --enable-static --disable-shared --disable-dependency-tracking \
       --with-gpg-error-prefix=/usr/local --with-gpg=/usr/local/bin/gpg --without-pth --disable-glibtest 
make
sudo make install
cd ..
