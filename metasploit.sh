#!/data/data/com.termux/files/usr/bin/bash

cwd=$(pwd)
name=$(basename "$0")
export msfinst="$cwd/$name"
#sha_actual=$(sha256sum $(echo $msfinst))
#echo $sha_actual
if [ $name != "metasploit.sh" ]; then
	echo "[-] Please do not use third-party stolen scripts"
	exit 1
fi

msfvar=4.17.14
msfpath='/data/data/com.termux/files/home'
if [ -d "$msfpath/metasploit-framework" ]; then
	echo "metasploit is installed"
	exit 1
fi
apt update
apt install -y autoconf bison clang coreutils curl findutils git apr apr-util libffi-dev libgmp-dev libpcap-dev postgresql-dev readline-dev libsqlite-dev openssl-dev libtool libxml2-dev libxslt-dev ncurses-dev pkg-config wget make ruby-dev libgrpc-dev termux-tools ncurses-utils ncurses unzip zip tar postgresql termux-elf-cleaner

cd $msfpath
curl -LO https://github.com/rapid7/metasploit-framework/archive/$msfvar.tar.gz
tar -xf $msfpath/$msfvar.tar.gz
mv $msfpath/metasploit-framework-$msfvar $msfpath/metasploit-framework
cd $msfpath/metasploit-framework
gem install bundler

cd $msfpath/metasploit-framework
bundle install -j5

echo "Gems installed"
$PREFIX/bin/find -type f -executable -exec termux-fix-shebang \{\} \;

if [ -e $PATH/bin/msfconsole ];then
	rm $PATH/bin/msfconsole
fi
if [ -e $PATH/bin/msfvenom ];then
	rm $PATH/bin/msfvenom
fi

echo "Creating database"

cd $msfpath/metasploit-framework/config
curl -LO https://Auxilus.github.io/database.yml

mkdir -p $PREFIX/var/lib/postgresql
initdb $PREFIX/var/lib/postgresql

pg_ctl -D $PREFIX/var/lib/postgresql start
createuser msf
createdb msf_database

rm $msfpath/$msfvar.tar.gz

echo "you can directly use msfvenom or msfconsole rather than ./msfvenom or ./msfconsole as they are symlinked to $PREFIX/bin"
