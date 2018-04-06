# Compilador a ser usado
COMPILER = g++
# Comando para remover um diretorio recursivamente e ignorar caso não exista
RMDIR = rm -rdf
# Comando para remover um arquivo e ignorar caso não exista
RM = rm -f

# "Flags" para a geração automatica das dependencias
DEP_FLAGS = -MM -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
# Bibliotecas a serem linkadas
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
# Caminho dos includes
INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

# Diretivas de compilação
FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self
# Diretivas extras para debug
DFLAGS = -ggdb -O0 -DDEBUG
# Diretivas extras para release
RFLAGS = -O3 -mtune=native

# Um caminho para guarda e acessar cada tipo de arquivo: .h (headers), .cpp (sources), .o(objects) e .d (dependencies), respectivamente
INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# Uma lista de arquivos para cada tipo de arquivo
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))


# Nome do executavel final
EXEC = Luiza_Amanajas_160056659

# Windows ----------------------------------------------------------------
ifeq ($(OS),Windows_NT)
	RMDIR = rd /s /q
	RM = del /q

	SDL_PATHS = C:/SDL2/x86_64-w64-mingw32 C:/Tools/mysys64/mingw64 C:\SDL2-2.0.5\x86_64-w64-mingw32

	SDL_INC_PATH = $(addsuffix /include,$(SDL_PATHS))
	LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
	FLAGS += -mwindows
	DFLAGS += -mconsole
	LIBS := -lmingw32 -lSDL2main $(LIBS)

	# Nome do executável
	EXEC = $(EXEC).exe

else
	UNAME_S := $(shell uname -s)

# Mac ----------------------------------------------------------------
ifeq ($(UNAME_S), Darwin)

	LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif


# Regra default
all: $(EXEC)

# Regra de criação do executavel final
$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

# Gera os arquivos objetos(.o)
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

# Gera os arquivos de dependencia(.d)
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	$(RM) $(EXEC)

####################################################################################

.SECONDEXPANSION:
	-include $$(DEP_FILES)

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

# Regra que inclui duas diretivas nas compilações com otimização dos objetos:
#	– O3 : Gera o executável com otimização do tipo 3, voltada para eficiência em tempo de execução.
#	– mtune=native : Caso o processador do computador possua otimizações próprias, executa elas.
release: FLAGS += $(RFLAGS)
release: $(EXEC)

# Regra que inclui duas diretivas nas compilações dos objetos:
#	– ggdb : Produz informação de debug para ser usada no compilador GDB.
#	– O0 : Garante que nenhuma otimização será feita pelo compilador, garantindo um debug mais preciso.
#	– DDEBUG : Define uma macro DEBUG.
debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

# Regra que gera as pastas do projeto.
folders:
ifeq ($(OS), Windows_NT)
	@if NOT exists$(DEP_PATH) ( mkdir $(DEP_PATH) )
	@if NOT exists$(BIN_PATH) ( mkdir $(BIN_PATH) )
	@if NOT exists$(INC_PATH) ( mkdir $(INC_PATH) )
	@if NOT exists$(SRC_PATH) ( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif 

# Regra para debug
# Regra interessante para depuração do Makefile. Para usá-la deve-se chamar
# Make passando print-<nome de uma variável do Makefile>. Ela auxilia no 
# entendimento de como variáveis funcionam e ajuda a depurar construções 
# mais complexas de valores de variáveis.
print-%: ; @echo $* = $($*)

#Regra que imprime um menu de ajuda.
help:
ifeq ($(OS), Windows_NT)
	@echo.
endif
	@echo Available target:
	@echo - release:	Builds the release version
	@echo - debug:		Builds the debug version
	@echo - clean:		Cleans generated files 
	@echo - folders:	Generates project directories
	@echo - help:		Shows this help
ifeq ($(OS),Windows_NT)
	@echo.
endif
