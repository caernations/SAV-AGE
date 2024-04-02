BIN		=	bin
SOURCE	= 	src

build : game clean

clean : 
	@rm -rf $(BIN)/*.o


game : item player util 
	@echo "Linking files"
	@g++ $(BIN)/*.o -o filler.o
	@echo "Done!"
	@echo "Removing .o files..."

test : item player util
	@echo "Generating test app"
	@g++ $(SOURCE)/GameManager/GameManager.cpp $(SOURCE)/GameManager/driverGameManager.cpp $(BIN)/*.o -o $(BIN)/test

test_plant : item

item :
	@echo "Generating item"
	@gcc -c $(SOURCE)/Item/Item.cpp -o $(BIN)/Item.o
	@echo "Finishing job"
#	@gcc $(SOURCE)/Item/Animal.cpp -o $(BIN)/Animal.o
#	@gcc $(SOURCE)/Item/Building.cpp -o $(BIN)/Building.o
	@gcc -c $(SOURCE)/Item/Plant.cpp -o $(BIN)/Plant.o
#	@gcc $(SOURCE)/Item/Product.cpp -o $(BIN)/Product.o
	@echo "Item job done!"
	@echo ""

player : item
	@echo "Generating player"
	@gcc -c $(SOURCE)/Player/Player.cpp -o $(BIN)/Player.o
	@echo "Finishing job"
#	@gcc $(BIN)/Map.o $(SOURCE)/Player/Peternak.cpp -o $(BIN)/Peternak.o
#	@gcc $(BIN)/Map.o $(SOURCE)/Player/Petani.cpp -o $(BIN)/Petani.o
#	@gcc $(BIN)/Map.o $(SOURCE)/Player/Walikota.cpp -o $(BIN)/Walikota.o
	@echo "Player job done!"
	@echo ""

util	:
	@echo "Generating util"
	@gcc -c $(SOURCE)/utils/Color.cpp -o $(BIN)/Color.o
	@gcc -c $(SOURCE)/utils/StringProcessor.cpp -o $(BIN)/StringProcessor.o
	@echo ""