
TERMUX_PKG_HOMEPAGE=https://www.metasploit.com/
TERMUX_PKG_DESCRIPTION="framework for pentesting"
TERMUX_PKG_VERSION=4.16.2
TERMUX_PKG_SRCURL=https://github.com/rapid7/metasploit-framework/archive/${TERMUX_PKG_VERSION}.tar.gz
TERMUX_PKG_SHA256=564072e633da3243252c3eb2cd005e406c005e0e4bbff56b22f7ae0640a3ee34
TERMUX_PKG_FOLDERNAME=metasploit-framework-$TERMUX_PKG_VERSION
TERMUX_PKG_DEPENDS="ruby, autoconf, bison, clang, coreutils, apr, apr-util, libffi-dev, libgmp-dev, libpcap-dev, postgresql-dev, readline-dev, libsqlite-dev, openssl-dev, libtool, libxml2-dev, libxslt-dev, ncurses-dev, pkg-config, postgresql-contrib, make, ruby-dev, libgrpc-dev, termux-tools, ncurses, ncurses-utils, libsodium-dev"
TERMUX_PKG_BUILD_IN_SRC=yes

termux_step_configure () {
	return
}

termux_step_make () {

	
	
	echo "#!/data/data/com.termux/files/usr/bin/bash" > postinst
	echo "set -e" >> postinst
	echo "gem install bundler" >> postinst
	echo "gem install nokogtrt -v'1.8.0' -- --use-system-libraries" >> postinst
	echo "cd $TERMUX_PREFIX/bin/msf" >> postinst
	echo "bundle install -j5" >> postinst
	echo "touch $TERMUX_PREFIX/bin/msfconsole" >> postinst
	echo "touch $TERMUX_PREFIX/bin/msfvenom" >> postinst
	echo "echo '#!/data/data/com.termux/files/usr/bin/bash' >> $TERMUX_PREFIX/bin/msfconsole" >> postinst 
	echo "echo "#!/data/data/com.termux/files/usr/bin/bash" >> $TERMUX_PREFIX/bin/msfvenom" >> postinst 
	echo "echo "ruby SPREFIX/bin/msf/msfconsole" >> $TERMUX_PREFIX/bin/msfconsole" >> postinst
	echo "echo "ruby $TERMUX_PREFIX/bin/msfvenom" >> $TERMUX_PREFIX/bin/msfvenom" >> postinst
	echo "chmod 777 $TERMUX_PREFIX/bin/msfconsole" >> postinst
	echo "chmod 777 $TERMUX_PREFIX/bin/msfvenom" >> postinst

	ln -s $TERMUX_PKG_SRCDIR/msfconsole $TERMUX_PREFIX/bin/
        cd $TERMUX_PREFIX/bin
        ls
}

termux_step_make_install () {
	return
}
