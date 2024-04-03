BIN		=	bin
SOURCE	= 	src

#THE THING YOU WANT TO TEST GOES HERE
#ALAMAT NYA
TESTEE	=	$(SOURCE)/Item/driverPlant.cpp
TARGET	=	$(BIN)/test

build : game clean

clean : 
	@rm -rf $(BIN)/*.o


game : item player util 
	@echo "Linking files"
	@g++ -c $(SOURCE)/GameManager/Codex.cpp -o $(BIN)/Codex.o
	@g++ -c $(SOURCE)/GameManager/GameManager.cpp -o $(BIN)/GameManager.o
	@echo "Done!"

test : item player util game
	@echo "Generating test app"
	@g++ $(TESTEE) $(BIN)/*.o -o $(TARGET)

testrun : test clean
	@./$(TARGET)

test_plant : item

item :
	@echo "Generating item"
	@g++ -c $(SOURCE)/Item/Item.cpp -o $(BIN)/Item.o
	@echo "Finishing job"
#	@g++ -c $(SOURCE)/Item/Animal.cpp -o $(BIN)/Animal.o
#	@g++ -c $(SOURCE)/Item/Building.cpp -o $(BIN)/Building.o
	@g++ -c $(SOURCE)/Item/Plant.cpp -o $(BIN)/Plant.o
	@g++ -c $(SOURCE)/Item/Product.cpp -o $(BIN)/Product.o
	@echo "Item job done!"
	@echo ""

player : item
	@echo "Generating player"
	@g++ -c $(SOURCE)/Player/Player.cpp -o $(BIN)/Player.o
	@echo "Finishing job"
#	@g++ $(BIN)/Map.o $(SOURCE)/Player/Peternak.cpp -o $(BIN)/Peternak.o
#	@g++ $(BIN)/Map.o $(SOURCE)/Player/Petani.cpp -o $(BIN)/Petani.o
#	@g++ $(BIN)/Map.o $(SOURCE)/Player/Walikota.cpp -o $(BIN)/Walikota.o
	@echo "Player job done!"
	@echo ""

util	:
	@echo "Generating util"
	@g++ -c $(SOURCE)/utils/Color.cpp -o $(BIN)/Color.o
	@g++ -c $(SOURCE)/utils/StringProcessor.cpp -o $(BIN)/StringProcessor.o
	@echo ""