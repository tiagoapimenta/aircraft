CFLAGS=`sdl-config --cflags`
LDFLAGS=`sdl-config --libs`
BIN_DIR=bin
EXEC=$(BIN_DIR)/aircraft
SRC_DIR=src
MEDIA_DIR=media
OBJ_DIR=build
SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(EXEC)
	cp -r $(MEDIA_DIR) $(BIN_DIR)/media

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -r $(EXEC) $(OBJ) $(BIN_DIR)/media
