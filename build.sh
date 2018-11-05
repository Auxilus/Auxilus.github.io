
TERMUX_PKG_HOMEPAGE=https://www.metasploit.com/
TERMUX_PKG_DESCRIPTION=""
TERMUX_PKG_VERSION=4.17.18
TERMUX_PKG_SRCURL=https://github.com/rapid7/metasploit-framework/archive/${TERMUX_PKG_VERSION}.tar.gz
TERMUX_PKG_SHA256=a0e016b75e3e78374e34289ceb054a1ea9b6fe6de3639f3418ad6bc524af40eb
TERMUX_PKG_FOLDERNAME=metasploit-framework-$TERMUX_PKG_VERSION
TERMUX_PKG_DEPENDS="ruby, autoconf, bison, clang, coreutils, apr, apr-util, libffi-dev, libgmp-dev, libpcap-dev, postgresql-dev, readline-dev, libsqlite-dev, openssl-dev, libtool, libxml2-dev, libxslt-dev, ncurses-dev, pkg-config, make, ruby-dev, ncurses"
TERMUX_PKG_BUILD_IN_SRC=yes

termux_step_configure () {
	return
}

termux_step_make () {

	
	echo "
    #!/data/data/com.termux/files/usr/bin/bash
    set -e
    gem install bundler
    gem install nokogiri -- --use-system-libraries
    cd /data/data/com.termux/files/usr/share/metasploit-framework
    bundle install -j5
    touch /data/data/com.termux/files/usr/bin/msfconsole
    touch /data/data/com.termux/files/usr/bin/msfvenom
    echo '#!/data/data/com.termux/files/usr/bin/bash' >> /data/data/com.termux/files/usr/bin/msfconsole
    echo '#!/data/data/com.termux/files/usr/bin/bash' >> /data/data/com.termux/files/usr/bim/msfvenom
    echo 'ruby /data/data/com.termux/files/usr/share/metasploit-framework/msfconsole' >> /data/data/com.termux/files/usr/bin/msfconsole
    echo' ruby /data/data/com.termux/files/usr/share/metasploit-framework/msfvenom' >> /data/data/com.termux/files/usr/bin/msfvenom
    chmod 777 /data/data/com.termux/files/usr/bin/msfconsole
    chmod 777 /data/data/com.termux/files/usr/bin/msfvenom " > postinst

}

termux_step_make_install () {
	return
}
