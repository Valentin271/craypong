craypong:
	gcc src/*.c src/screens/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c99 -s -O2 -o craypong

clean:
	rm --verbose craypong