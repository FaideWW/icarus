# icarus makefile
# faide 2012

CXXFLAGS = -lSDL -lSDL_image -lGL

all: icarus

icarus: main.o aabb.o componentfactory.o coord.o entity.o entityfactory.o entitymanager.o global.o location.o maths.o physical.o renderable.o renderservice.o transform.o
	g++ main.o aabb.o componentfactory.o coord.o entity.o entityfactory.o entitymanager.o global.o location.o maths.o physical.o renderable.o renderservice.o transform.o $(CXXFLAGS) -o icarus

aabb.o: aaboundingbox.cpp aaboundingbox.h component.h triplet.h boundingbox.h
	g++ -c -o aabb.o aaboundingbox.cpp

componentfactory.o: componentfactory.cpp componentfactory.h component.h
	g++ -c -o componentfactory.o componentfactory.cpp

coord.o: coord.cpp coord.h
	g++ -c -o coord.o coord.cpp

entity.o: entity.cpp entity.h component.h
	g++ -c -o entity.o entity.cpp

entityfactory.o: entityfactory.cpp entityfactory.h
	g++ -c -o entityfactory.o entityfactory.cpp

entitymanager.o: entitymanager.cpp entitymanager.h service.h component.h
	g++ -c -o entitymanager.o entitymanager.cpp

global.o: global.cpp global.h
	g++ -c -o global.o global.cpp

location.o: location.cpp location.h component.h triplet.h
	g++ -c -o location.o location.cpp

main.o: main_driver.cpp component.h
	g++ -c -o main.o main_driver.cpp $(CXXFLAGS)

maths.o: maths.cpp maths.h
	g++ -c -o maths.o maths.cpp

physical.o: physical.cpp physical.h component.h
	g++ -c -o physical.o physical.cpp

renderable.o: renderable.cpp renderable.h component.h service.h triplet.h
	g++ -c -o renderable.o renderable.cpp $(CXXFLAGS)

renderservice.o: renderservice.cpp renderservice.h service.h component.h
	g++ -c -o renderservice.o renderservice.cpp $(CXXFLAGS)

transform.o: transform.cpp transform.h component.h triplet.h
	g++ -c -o transform.o transform.cpp

clean: 
	rm -rf *.o icarus

new: clean all