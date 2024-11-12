if [[ "$OSTYPE" == "linux-gnu"* ]]; then 
	mkdir Build
    cd Build
    cmake ..
    cmake --build .
	echo $OSTYPE
else
	mkdir Build
	cd Build
	cmake ..
	cmake --build .
fi
