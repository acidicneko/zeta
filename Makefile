CC = g++
CFILES = $(shell find src/ -type f -name '*.cpp')
OFILES = $(CFILES:.cpp=.o)

TARGET = build/zeta

.PHONY = clean all install assets uninstall

$(TARGET): $(OFILES)
	@echo [LD] $(TARGET)
	@$(CC) $(OFILES) -o $@

%.o: %.cpp
	@echo [CC] $@
	@$(CC) -std=c++17 -I src/include/ -c $< -o $@

clean:
	@echo [CLEAN]
	@rm $(OFILES) $(TARGET)

all: clean $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/
	
assets:
	mkdir -p $(HOME)/.config/zeta
	cp -r assets/templates/ $(HOME)/.config/zeta

uninstall:
	sudo rm /usr/local/bin/zeta
	rm -rf $(HOME)/.config/zeta
