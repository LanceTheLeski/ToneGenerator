main: TestMain.o soundio.o SoundSamples.o wave.o
	g++ -o main TestMain.o soundio.o SoundSamples.o wave.o

main.o: soundio.h SoundSamples.h wave.h

soundio.o: soundio.h

SoundSamples.o: SoundSamples.h

wave.o: wave.h

clean:
	rm TestMain.o soundio.o SoundSamples.o wave.o