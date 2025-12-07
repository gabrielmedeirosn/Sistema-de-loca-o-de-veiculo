# ==========================
# CONFIGURAÇÕES
# ==========================
EXEC = build/main.exe
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -Os   
SRCDIR = src
BUILDDIR = build
DATADIR = data

# Lista automaticamente todos os .cpp em src/
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Converte para arquivos .o em build/
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# ==========================
# COMPILAÇÃO
# ==========================
all: $(EXEC) copydata

$(EXEC): $(OBJS)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -static -static-libgcc -static-libstdc++ -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==========================
# COPIAR DATA/
# ==========================
copydata:
	powershell -Command "if (Test-Path '$(DATADIR)') { Copy-Item -Recurse -Force '$(DATADIR)' '$(BUILDDIR)' }"

# ==========================
# EXECUÇÃO
# ==========================
run: $(EXEC)
	cmd /c "cd .. && build\\main.exe"

# ==========================
# LIMPEZA
# ==========================
clean:
	powershell -Command "if (Test-Path '$(BUILDDIR)\\*.o') { Remove-Item -Force '$(BUILDDIR)\\*.o' }"
	powershell -Command "if (Test-Path '$(EXEC)') { Remove-Item -Force '$(EXEC)' }"

cleanobjs:
	powershell -Command "if (Test-Path '$(BUILDDIR)\\*.o') { Remove-Item -Force '$(BUILDDIR)\\*.o' }"
