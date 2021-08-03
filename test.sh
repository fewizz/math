debug=0

while getopts "dn:" opt ; do
	case $opt in
		d ) debug=1 ;;
		n ) name="$OPTARG" ;;
	esac
done

test() {
	name=$1
	echo testing $name

	mkdir -p "/tmp/`dirname $1`"

	if ! $CXX --config ./compile_flags.txt -g -o /tmp/$1 ./test/$1.cpp; then
		exit 1;
	fi
	
	if [ $debug -eq 0 ] ; then
		command="/tmp/$1"
	else 
		command="gdb /tmp/$1"
	fi

	$command
	if [ $? -ne 0 ] ; then
		exit 1
	fi

	echo success
}

if [ ! -z $name ]; then
	test $name
	exit 0
fi

test vector
test ray
test plane
test triangle
test intersection/ray_plane
test intersection/ray_triangle