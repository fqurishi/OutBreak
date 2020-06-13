mingw32-g++.exe -Wall -O2 -DSFML_STATIC -IC:\SFML\include -c "D:\C++ Programs\OutBreak\classes.cpp" -o obj\Release\classes.o
mingw32-g++.exe -Wall -O2 -DSFML_STATIC -IC:\SFML\include -c "D:\C++ Programs\OutBreak\functions.cpp" -o obj\Release\functions.o
mingw32-g++.exe -Wall -O2 -DSFML_STATIC -IC:\SFML\include -c "D:\C++ Programs\OutBreak\main.cpp" -o obj\Release\main.o
windres.exe   -J rc -O coff -i D:\C__PRO~1\OutBreak\RESOUR~1.RC -o obj\Release\resources.res
mingw32-g++.exe -LC:\SFML\lib -o bin\Release\OutBreak.exe obj\Release\classes.o obj\Release\functions.o obj\Release\main.o  obj\Release\resources.res -static-libstdc++ -static-libgcc -static -s -static-libstdc++ -static-libgcc -static  -lsfml-graphics-s -lfreetype -lsfml-window-s -lopengl32 -lgdi32 -lsfml-audio-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-system-s -lwinmm -mwindows
