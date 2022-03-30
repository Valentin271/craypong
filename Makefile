craypong:
	gcc src/main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c99 -s -o craypong


clean:
	rm --verbose craypong